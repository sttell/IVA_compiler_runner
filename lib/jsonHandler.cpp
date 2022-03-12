#include "../include/jsonHandler.h"

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
void JsonHandler::dump(const Path& out_path, const boost::property_tree::ptree& buffer) const {
    // Открытие файла
    std::ofstream fout(out_path.c_str());

    // При возникновении ошибки открытия выбрасываем исключение.
    // В случае нормально работы - выгружаем root узел
    if (fout.is_open())
        dumpNode(buffer, fout);
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

    if (!property_str.empty() && 
        std::find_if(property_str.begin(), property_str.end(), 
            [](unsigned char property_str) { 
                return !(std::isdigit(property_str) || property_str == '.'); 
                }) == property_str.end())
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
    fout << "\"" + name + "\" : ";
}

// Запись узла-хэш таблицы
void JsonHandler::dumpMap(const boost::property_tree::ptree& node, std::ofstream& fout) const {

    // Ведется подсчет пройденных узлов. Для всех кроме последнего выставляется запятая в конце.
    fout << "\n{\n";
    int current_child = 0;
    for (const auto& child : node) {

        current_child++;
        // Запись имени узла и рекурсивный вызов записи дочерних узлов
        dumpNodeName(child.first, fout);
        dumpNode(child.second, fout);

        if (current_child != node.size()) fout << ", \n";
        else                              fout << "\n";
    }
    fout << "}";
}

// Запись узла-списка
void JsonHandler::dumpList(const boost::property_tree::ptree& node, std::ofstream& fout) const {
    // Подобно записи хэш-таблицы, но без записи имени узла
    fout << "[";
    int current_child = 0;
    for (const auto& child : node) {

        current_child++;
        
        dumpNode(child.second, fout);
        
        if (current_child != node.size()) fout << ", ";
    }
    fout << "]";
}

// Запись конечного поля
void JsonHandler::dumpProperty(const boost::property_tree::ptree& node, std::ofstream& fout) const {
    // Определяем тип данных записи. В зависимости от типа предаем на запись определенным образом
    std::string node_data = node.data();
    PropertyType ptype = getPropertyType(node_data);

    if (ptype == PropertyType::Number || ptype == PropertyType::Bool) {
    
        fout << node_data;
    
    } else {
    
        fout << "\"" << node_data << "\"";
    
    }
}

// Запись узла
void JsonHandler::dumpNode(const boost::property_tree::ptree& node, std::ofstream& fout) const {
    // Определяем тип узла
    NodeType node_type = getNodeType(node);
    
    // Передаем рекурсивному обработчику в зависимости от типа
    switch (node_type) {

    case NodeType::Value:
        dumpProperty(node, fout);
        break;

    case NodeType::List:
        dumpList(node, fout);
        break;
    
    case NodeType::Map:
        dumpMap(node, fout);
        break;
    
    default:
        // При неизвестном типе генерируем исключение
        std::string err_desc(JSON_HANDLER_THROW_DESC);
        err_desc += "Unknown Node Type in JSON dumpNode function.";
        throw std::runtime_error(err_desc);
        break;
    }
}