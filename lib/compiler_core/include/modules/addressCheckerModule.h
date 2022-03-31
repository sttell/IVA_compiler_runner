#ifndef _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_
#define _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_

#include "../module.h"
#include "../settings/globalSettings.h"
#include "../jsonHandler.h"
#include <boost/any.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>
#include <unordered_map>
#include <fstream>

// Идентификаторы типов данных в формате HPM Scheduler
#define HPM_WEIGHTS_STRID "filters"
#define HPM_BIAS_STRID "biases"
#define HPM_NEGSCALE_STRID "activation_coefficients"
#define HPM_POSSCALE_STRID "scale"

#define ADDR_CHECKER_THROW_DESC "Address Checker Module error. "

// Формат хранения JSON данных
using json_buffer_t = boost::property_tree::ptree;

// Pickle converter после окнвертации формирует буффер 
// с подсчитанными адресами весов и размерами данных.

// Формат хранения данных:
// layer_name_1\n
// \tdata_type *addr* *size*
// \tdata_type *addr* *size*
// ...
// layer_name_2\n
// \tdata_type *addr* *size*
// ....

// Наиболее оптимальный формат хранения данных в таком случае будет
// hashtable(str -> hashtable(str -> pair(int, int))).
// Наиболее часто используемая операция - поиск по строковому ключу.

// Формат хранения layer data в буффере pickle converter
using pickle_ld_t = std::unordered_map<std::string, std::pair<int, int>>;
// Формат хранения буффера pickle converter
using pickle_buffer_t = std::unordered_map<std::string, pickle_ld_t>;

class AddressCheckerModule : public Module {  
public:
    // Явный конструктор с инициализацией настроек
    explicit AddressCheckerModule(const GlobalSettings& _settings, StatusBufferCache* status_bar) :
        Module(status_bar, ADDR_CHECKER_THROW_DESC), settings(_settings.addr_checker) {};
    
    ~AddressCheckerModule() {log=nullptr; delete log;};
    // Метод запуска модуля
    exit_module_status runProcess();

protected:
    // Проверка корректности настроек
    void checkSettingsCorrectness() const;

private:
    // Настройки модуля
    AddrCheckerSettings settings;
    // Буффер json
    json_buffer_t json_buffer;
    // Буффер pickle
    pickle_buffer_t pickle_buffer;
    // Обработчик json файлов
    JsonHandler json_handler;

    // Чтение буффера Pickle
    void readPickleBuffer();
    // Чтение JSON описания сети
    void readJSON();
    // Запись JSON с корректированными данными
    void dumpJSON();
    // Коррекция данных
    void correctData();
    // Формирование пары корректных значений
    void correctPair(boost::property_tree::ptree& list_node, const std::pair<int, int>& new_value) const;
};

#endif // _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_
