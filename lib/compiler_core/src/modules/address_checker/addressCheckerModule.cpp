#include "../../../include/modules/addressCheckerModule.h"
#include <boost/filesystem.hpp>

exit_module_status AddressCheckerModule::runProcess() {

    // В любом из методов может возникнуть исключительная ситуация
    // которая записывается в лог с ошибками.
    // Все выбрасываемые исключения внутри методов необходимо
    // выбрасывать в виде std::runtime_error(description).
    try{

        // Проверка правильности настроек
        log->writeMessage("Проверка корректности настроек модуля.");
        checkSettingsCorrectness();
        log->writeMessage("Проверка корректности завершена успешно.");

        // Чтение буффера PickleConverter
        log->writeMessage("Чтение лога Pickle конвертации.");
        readPickleBuffer();
        log->writeMessage("Чтение лога конвертации прошло успешно");

        // Чтение Json файла с описанием сети в формате hpm_scheduler
        log->writeMessage("Чтение JSON описания сети в формате HPM.");
        readJSON();
        log->writeMessage("Чтение JSON описания прошло успешно.");

        // Корректировка адресов и размеров
        log->writeMessage("Коррекция размеров и адресов весов начата.");
        correctData();
        log->writeMessage("Коррекция завершена успешно.");

        // Выгрузка json файла с исправлениями
        log->writeMessage("Выгрузка корректированного описания JSON.");
        dumpJSON();
        log->writeMessage("Коррекция размеров и адресов в JSON описании прошла успешно.");

    } catch (const std::runtime_error& e) {
        // Выгружаем исключение в лог ошибок.
        throw std::runtime_error(throw_desc + e.what());
    }
    return ModuleExitStatus::SUCCESS;
};

// Проверка корректности настроек
void AddressCheckerModule::checkSettingsCorrectness() const {
    // Проверка наличия входных файлов
    checkFileExist(settings.json_path);
    checkFileExist(settings.pickle_buffer_path);

    // Проверка на размер
    if (boost::filesystem::file_size(settings.json_path.c_str()) == 0) {
        throw std::runtime_error("Файл с JSON описанием сети пуст.");
    }

    if (boost::filesystem::file_size(settings.pickle_buffer_path.c_str()) == 0) {
        throw std::runtime_error("Файл лога конвертации Pickle пуст.");
    }

    // Проверка существования директории
    checkDirExist(settings.out_json_path);
}

// Чтение Pickle Log
void AddressCheckerModule::readPickleBuffer() {
    // opening input file stream
    std::ifstream fin;
    fin.open(settings.pickle_buffer_path.c_str());

    std::string layer_name;
    std::string data_key;
    int address, size;
    std::string line;

    // reading first line as layer name
    while (std::getline(fin, line)) {
        if (line[0] == '\t') {
            std::istringstream iss(line);
            iss >> data_key >> address >> size;
            pickle_buffer[layer_name].insert({data_key, {address, size}});
        } else {
            layer_name = line;
            pickle_buffer.insert({layer_name, {}});
        }
    }

    fin.close();
}

// Чтение JSON описания сети в формате HPM
void AddressCheckerModule::readJSON() {
    json_handler.read(settings.json_path, json_buffer);
}

// Запись корректированного JSON файла сети
void AddressCheckerModule::dumpJSON() {
    json_handler.dump(settings.out_json_path, json_buffer);
}

// Формирование пары корректных значений
void AddressCheckerModule::correctPair(
    boost::property_tree::ptree& list_node,      // Узел, куда будут записаны новые данные
    const std::pair<int, int>& new_value) const  // Пара адрес - размер которые нужно записать
{
    // Распаковка пары
    auto [address, size] = new_value;
    // создание узлов [address_node, size_node]
    boost::property_tree::ptree address_node, size_node;
    // Заполнение узлов значениями
    address_node.put("", address);
    size_node.put("", size);
    // Заполнение списка [.., ..]
    list_node.push_back(std::make_pair("", address_node));
    list_node.push_back(std::make_pair("", size_node));
}

// Корректировка размеров и адресов в JSON файле
void AddressCheckerModule::correctData() {

    // Идем по всему описанию сети
    for (auto& [key, layer] : json_buffer) {
        // Имя слоя
        std::string layer_name = layer.get_child("name").data().c_str();
        // Флаги поиска нужных полей
        bool is_weights_found(false), is_scale_found(false),
            is_bias_found(false), is_neg_scale_found(false),
            one_of_found = false; // Если хотя бы одно поле найдено

        // Проходимся по узлам в конкретном слое и идентификаторы данных
        for (auto& [place_name, place_data] : layer) {
            if (place_name == HPM_WEIGHTS_STRID) {
                is_weights_found = true;
            } else if (place_name == HPM_BIAS_STRID) {
                is_bias_found = true;
            } else if (place_name == HPM_POSSCALE_STRID) {
                is_scale_found = true;
            } else if (place_name == HPM_NEGSCALE_STRID) {
                is_neg_scale_found = true;
            }
            // Если хотя бы один идентификатор найден, то выставляем флаг
            one_of_found = is_weights_found || is_scale_found || is_bias_found || is_neg_scale_found;
        }

        // Если хотя бы одно поле с весами найдено, то корректируем
        if (one_of_found) {
            // Если буффер пикль содержит имя текущего слоя, то все нормально. Иначе - выдаем исключение о не соответствии
            if (pickle_buffer.count(layer_name)) {
                // Корректировка весов
                if (is_weights_found) {
                    boost::property_tree::ptree weights_list;
                    correctPair(weights_list, pickle_buffer[layer_name][HPM_WEIGHTS_STRID]);
                    layer.get_child(HPM_WEIGHTS_STRID) = weights_list;
                }
                // Корректировка скейлов
                if (is_scale_found) {
                    boost::property_tree::ptree scales_list;
                    correctPair(scales_list, pickle_buffer[layer_name][HPM_POSSCALE_STRID]);
                    layer.get_child(HPM_POSSCALE_STRID) = scales_list;
                }
                // Корректировка биасов
                if (is_bias_found) {
                    boost::property_tree::ptree bias_list;
                    correctPair(bias_list, pickle_buffer[layer_name][HPM_BIAS_STRID]);
                    layer.get_child(HPM_BIAS_STRID) = bias_list;
                }
                // Корректировка отрицательных скейлов активации
                if (is_neg_scale_found) {
                    boost::property_tree::ptree neg_scale_list;
                    correctPair(neg_scale_list, pickle_buffer[layer_name][HPM_NEGSCALE_STRID]);
                    layer.get_child(HPM_NEGSCALE_STRID) = neg_scale_list;
                }

            } else {
                // исключение с обозначением слоя на котором произошло не соответствие
                std::string err_desc("Лог конвертации pickle не соответствует сети. Слой:");
                err_desc += layer_name + " не найден в pickle log.";
                throw std::runtime_error(err_desc);
            }
        }

    }
}
