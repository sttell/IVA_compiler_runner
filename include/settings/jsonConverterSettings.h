#ifndef _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_

#include <string>
#include "../path.h"

// Структура для хранения настроек модуля JSON Converter Module
struct JsonConverterSettings
{
    JsonConverterSettings() : input_json_path(PathType::File),
                              output_json_path(PathType::File),
                              out_log_path(PathType::File) {};

    // Путь к JSON описанию сети в формате Tensorflow
    Path input_json_path;

    // Путь к JSON описанию сети в формате HPM Shceduler
    Path output_json_path;

    // Путь к логу работы модуля
    Path out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_