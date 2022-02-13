#ifndef _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_

#include <string>

// Структура для хранения настроек модуля JSON Converter Module
struct JsonConverterSettings
{
    // Путь к JSON описанию сети в формате Tensorflow
    std::string input_json_path;

    // Путь к JSON описанию сети в формате HPM Shceduler
    std::string output_json_path;

    // Путь к логу работы модуля
    std::string out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_JSONCONVERTERSETTINGS_H_