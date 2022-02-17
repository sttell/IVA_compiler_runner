#ifndef _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_

#include <string>
#include "../path.h"

// Структура для хранения настроек модуля File Checker Module
struct FileCheckerSettings
{
    FileCheckerSettings() : json_file_path(PathType::File),
                            weights_file_path(PathType::File),
                            out_log_path(PathType::File) {};
    // Путь к json описанию сети
    Path json_file_path;

    // Путь к файлу с весами сети
    Path weights_file_path;

    // Путь к логу работы модуля
    Path out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_FILECHECKERSETTINGS_H_