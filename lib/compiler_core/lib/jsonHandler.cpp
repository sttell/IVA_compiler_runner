#include "../include/jsonHandler.h"

std::string indent(int n) {
    std::string ind;
    if (n < 0) throw std::runtime_error("JSON Write: Indentation level very small.");
    for(size_t i=0; i < n; i++) ind += " ";
    return ind;
}

// Считывание JSON файла в буффер по ссылке.
void JsonHandler::read(const Path& input_path, boost::property_tree::ptree& buffer) const {
    
    try {
        // Чтение JSON файла в буффер
        boost::property_tree::read_json(input_path.c_str(), buffer);
    }
    catch (std::exception const& e) {
        
        std::string err_desc(JSON_HANDLER_THROW_DESC);
        err_desc += e.what();
        throw std::runtime_error(err_desc.c_str());
    }
};

// Запись буффера в JSON формате
void JsonHandler::dump(const Path& out_path, const boost::property_tree::ptree& buffer, int indent) {
    
    if (indent >= 0) indentation_shift = indent;
    
    // Открытие файла
    std::ofstream fout(out_path.c_str());

    // При возникновении ошибки открытия выбрасываем исключение.
    // В случае нормально работы - выгружаем root узел
    if (fout.is_open())
        dumpNode(buffer, fout, NodeType::Root);
    else {
        std::string err_desc(JSON_HANDLER_THROW_DESC);
        err_desc += "Cannot open file: ";
        err_desc += out_path.c_str();
        throw std::runtime_error(err_desc);
    }

    fout.close();
}

// Определение типа записываемого поля
PropertyType JsonHandler::getPropertyType(const std::string& property_str) const {

    auto digits_and_points_comp = [](unsigned char property_str) { 
        return !(std::isdigit(property_str) || property_str == '.'); 
    };
    auto is_point_comparator = [](unsigned char sym) { return sym == '.'; };
    // Если
    // Это не пустая строка
    bool digit_condition = !property_str.empty();
    // Все символы - цифры или .
    digit_condition = digit_condition && (
        std::find_if(
            property_str.begin(), 
            property_str.end(), 
            digits_and_points_comp
            ) == property_str.end()
    );
    
    // Количество точек не больше 1
    digit_condition = digit_condition && (
        std::count_if(
            property_str.begin(), 
            property_str.end(),
            is_point_comparator
        ) < 2
    );

    if (digit_condition)
        return PropertyType::Number;
    
    if (property_str == "true" || property_str == "false") 
        return PropertyType::Bool;
    
    return PropertyType::String;
}

// Определение типа переданного узла
NodeType JsonHandler::getNodeType(const boost::property_tree::ptree& node) const {
    // Если узел не имеет множество детей, то это конечное значение
    if (node.size() == 0) {
        return NodeType::Value;
    }
    
    // В ином случае нужно посмотреть на первого ребенка узла
    for (const auto& child : node) {
        // Если он не имеет имени, то это список
        if (child.first.empty()) {
            return NodeType::List;
        }
        // Если имя есть, то это хэш-таблица
        return NodeType::Map;
    }
    // В базовом случае имеем ввиду, что это хэш-таблица
    return NodeType::Map;
}

// Запись имени узла при его наличии
void JsonHandler::dumpNodeName(const std::string& name, std::ofstream& fout) const {
    // Добавление кавычек для строковых аргументов
    fout << indent(indentation_level) << "\"" + name + "\" : ";
}

// Запись узла-хэш таблицы
void JsonHandler::dumpMap(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type) {

    // Ведется подсчет пройденных узлов. Для всех кроме последнего выставляется запятая в конце.
    if (parent_type == NodeType::List) fout << indent(indentation_level);
    fout << "{\n";
    int current_child = 0;
    for (const auto& child : node) {

        current_child++;
        // Запись имени узла и рекурсивный вызов записи дочерних узлов
        indentation_level += indentation_shift;
        dumpNodeName(child.first, fout);
        dumpNode(child.second, fout, NodeType::Map);
        
        if (current_child != node.size()) fout << ", \n";
        else                              fout << "\n";
        indentation_level -= indentation_shift;
    }
    fout << indent(indentation_level) << "}";
}

// Запись узла-списка
void JsonHandler::dumpList(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type) {
    // Подобно записи хэш-таблицы, но без записи имени узла
    if (parent_type == NodeType::List) fout << indent(indentation_level);
    fout << "[\n";

    int current_child = 0;
    for (const auto& child : node) {

        current_child++;
        indentation_level += indentation_shift;
        dumpNode(child.second, fout, NodeType::List);

        if (current_child != node.size()) fout << ", \n";
        else                              fout << "\n";
        indentation_level -= indentation_shift;
    }
    fout << indent(indentation_level) << "]";
}

bool JsonHandler::isHardWriteElement(const std::string& str) const {
    return str.find(JSON_HANDLER_HW_SPECIFIER) != std::string::npos;
}

// Запись конечного поля
void JsonHandler::dumpProperty(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type) const {
    // Определяем тип данных записи. В зависимости от типа предаем на запись определенным образом
    std::string node_data = node.data();
    bool is_hard_write_mode = isHardWriteElement(node_data);
    PropertyType ptype = getPropertyType(node_data);
    
    std::string local_indent("");

    if (parent_type == NodeType::List) local_indent += indent(indentation_level);

    if (ptype == PropertyType::Number || ptype == PropertyType::Bool) {
    
        fout << local_indent << node_data;
    
    } else if (is_hard_write_mode) {
        size_t specifier_start_idx = node_data.find(JSON_HANDLER_HW_SPECIFIER);
        std::string tmp = node_data.substr(0, specifier_start_idx);
        fout << local_indent << tmp;
    } else {
    
        fout << local_indent << "\"" << node_data << "\"";
    
    }
}

// Запись узла
void JsonHandler::dumpNode(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type) {
    // Определяем тип узла
    NodeType node_type = getNodeType(node);
    // Передаем рекурсивному обработчику в зависимости от типа
    switch (node_type) {

    case NodeType::Value:
        dumpProperty(node, fout, parent_type);
        break;

    case NodeType::List:
        dumpList(node, fout, parent_type);
        break;
    
    case NodeType::Map:
        dumpMap(node, fout, parent_type);
        break;
    
    default:
        // При неизвестном типе генерируем исключение
        std::string err_desc(JSON_HANDLER_THROW_DESC);
        err_desc += "Unknown Node Type in JSON dumpNode function.";
        throw std::runtime_error(err_desc);
        break;
    }
}