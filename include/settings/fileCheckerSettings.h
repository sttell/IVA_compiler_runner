#ifndef _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_

#include <string>

// Структура для хранения настроек модуля File Checker Module
struct FileCheckerSettings
{
    // Путь к json описанию сети
    std::string json_file_path;

    // Путь к файлу с весами сети
    std::string weights_file_path;

    // Путь к логу работы модуля
    std::string out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_