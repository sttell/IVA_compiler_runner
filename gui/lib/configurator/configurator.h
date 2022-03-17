#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include <filesystem>
#include <string>
#include <map>

// Тип контейнера хранящего конфигурации
using cfg_container_t = std::map<std::string, std::string>;

// Перечисление типов возможных конфигураций
enum class CONFIGURE_TYPE {
    GlobalSettings,
    CompilerSettings,
    RunnerSettings,
    AnalysisSettings
};


// Дескриптор конфигураций.
// Предназначен для хранения общей информации о конфигурации
struct ConfigurationDesc {
    // Конструкторы
    ConfigurationDesc() : cfg_path("unknown.config") {};
    ConfigurationDesc(const std::string& _cfg_path) : cfg_path(_cfg_path) {};

    // Путь к cfg файлу
    std::string cfg_path;
    // Контейнер хранящий текущие параметры
    cfg_container_t cfg;
};

// Глобальная переменная с конфигурациями
inline std::map<CONFIGURE_TYPE, ConfigurationDesc> configs;


// Пространство имен для обращения к функционалу конфигураций
namespace Configurator
{

// Загрузка всех конфигураций
void loadConfigs();

// Выгрузка всех конфигураций
void dumpConfigs();

// Обновление состояния в конфигурации
void updateState(ConfigurationDesc& cfg_desc, std::string widget_name, std::string new_state);

}

#endif // CONFIGURATOR_H
