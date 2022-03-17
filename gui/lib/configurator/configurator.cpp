#include "configurator.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <iostream>


// Выдать путь к директории с конфигурациями
std::string getConfigDir() {
    std::filesystem::path current_path = std::filesystem::current_path();
    return current_path.string() + "/configs";
}


// Инициализация контейнера с конфигурациями
void initConfigsContainer() {
    std::string cfg_dir(getConfigDir());
    configs[CONFIGURE_TYPE::CompilerSettings]   = {cfg_dir + "/compiler_settings.config"};
    configs[CONFIGURE_TYPE::RunnerSettings]     = {cfg_dir + "/runner_settings.config"};
    configs[CONFIGURE_TYPE::AnalysisSettings]   = {cfg_dir + "/analys_settings.config"};
}


// Инициализация директории с конфигурациями(Если не существует)
void initConfigDir() {

   std::string config_dir(getConfigDir());

   if (!std::filesystem::is_directory(config_dir))
       std::filesystem::create_directory(config_dir);

}

// Приведение настроек компиляции к базовым
void removeCompilerSettings(ConfigurationDesc& desc) {
    desc.cfg["JsonPathLineEdit"] = "/";
    desc.cfg["WeightsPathLineEdit"] = "/";
    desc.cfg["CatalogNamePathEdit"] = "/";
    desc.cfg["InputSizeLineEdit"] = "";
    desc.cfg["InputPadUpLineEdit"] = "";
    desc.cfg["InputPadDownLineEdit"] = "";
    desc.cfg["OutputSizeLineEdit"] = "";
    desc.cfg["OutputPadUpLineEdit"] = "";
    desc.cfg["OutputPadDownLineEdit"] = "";
    desc.cfg["AddCompilationLogCheckBox"] = "1";
    desc.cfg["AddBiasPreloadCheckBox"] = "1";
    desc.cfg["AddScalePreloadCheckBox"] = "1";
    desc.cfg["AddInputOptimizationCheckBox"] = "1";
    desc.cfg["AddReorderOptimizationCheckBox"] = "1";
    desc.cfg["AddDebugModeCheckBox"] = "1";
    desc.cfg["JsonConvertationCheckBox"] = "0";
    desc.cfg["PickleConvertationCheckBox"] = "1";
    desc.cfg["AddressCheckCheckBox"] = "1";
    desc.cfg["CompileProgrammCheckBox"] = "1";
    desc.cfg["MakeArchiveCheckBox"] = "1";


}


// Приведение настроек к базовым.
// CONFIGURE_TYPE    cfg_type - тип конфигурации
// ConfigurationDesc cfg_desc - Дескриптор конфигурации соответствующего типа
void removeToDefault(CONFIGURE_TYPE cfg_type, ConfigurationDesc& cfg_desc) {

    switch (cfg_type) {

    case CONFIGURE_TYPE::CompilerSettings:
        removeCompilerSettings(cfg_desc);
        break;

    case CONFIGURE_TYPE::RunnerSettings:
        break;

    case CONFIGURE_TYPE::AnalysisSettings:
        break;

    default:
        break;
    };
}


// Разделение строки по первому встретившемуся пробелу.
// Возвращает 2 части строки, либо исходную и пустую строку.
std::pair<std::string, std::string> firstSpaceSplit(const std::string& str) {
    // Ищем пробел
    size_t space_idx = str.find(' ');

    // Если пробел найден
    if (space_idx != std::string::npos)
    {
        // Случай, когда пробел в конце
        if (space_idx - str.size() + 1 == 0)
            return {str.substr(0, str.size() - 1), ""};

        // Случай когда пробел не в конце
        return {str.substr(0, space_idx), str.substr(space_idx + 1, std::string::npos)};

    }

    return {str, ""};
}


// Загрузка конфигураций из файла.
// CONFIGURE_TYPE config_type    - тип конфигурации
// ConfigurationDesc config_desc - дескриптор конфигурации соответствующего типа
void loadConfig(CONFIGURE_TYPE config_type, ConfigurationDesc& config_desc) {

    // Путь к файлу с конфигурациями
    std::string config_path = config_desc.cfg_path;

    // Если файл существует, считываем информацию.
    // В иных случаях перенаправляение на сброс к базовым настройкам
    if (std::filesystem::is_regular_file(config_path)) {
        std::ifstream fin(config_path);

        if (fin.is_open()) {

            std::string line;
            size_t idx = 0;
            while (getline(fin, line))
            {
                auto [widget_name, configuration] = firstSpaceSplit(line);

                config_desc.cfg[widget_name] = configuration;

                if (idx == 0 && line.empty()) {
                    removeToDefault(config_type, config_desc);
                    break;
                }
                idx++;
            }

        } else {
            removeToDefault(config_type, config_desc);
        }

        fin.close();

    } else {
        std::ofstream fout(config_path);
        removeToDefault(config_type, config_desc);
        fout.close();
    }


}


// Обновление состояния поля в конфигурации
// ConfigurationDesc cfg_desc - Дескриптор конфигурации
// std::string    widget_name - Название виджета(ключ)
// std::string      new_state - Новое сотояние
void Configurator::updateState(ConfigurationDesc& cfg_desc, std::string widget_name, std::string new_state) {
    try {
        cfg_desc.cfg.at(widget_name) = new_state;
    } catch (const std::exception& e){
        std::cout << "Failture in update state for widget " << widget_name << std::endl;
    }
}

// Сброс конкретной конфигурации в .config файл
void dumpConfig(const ConfigurationDesc& config_desc) {

    std::ofstream fout(config_desc.cfg_path);

    for (const auto& [key, value] : config_desc.cfg) {
        fout << key << " " << value << "\n";
    }

    fout.close();
}

// Сброс всех конфигураций в файлы
void Configurator::dumpConfigs() {
    initConfigDir();

    for (const auto& [cfg_type, cfg_desc] : configs)
        dumpConfig(cfg_desc);


}

// Загрузка всех конфигураций
void Configurator::loadConfigs() {

    initConfigDir();
    initConfigsContainer();

    for (auto& [cfg_type, cfg_desc] : configs)
        loadConfig(cfg_type, cfg_desc);

};
