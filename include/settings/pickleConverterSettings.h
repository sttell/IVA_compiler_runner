#ifndef _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_

#include <string>

// Структура для хранения настроек модуля Pickle Converter Module
struct PickleConverterSettings
{
    // Путь к файлу с весами в формате Pickle
    std::string pickle_file_path;

    // Путь к файлу с весами в формате bin
    std::string weights_out_path;

    // Путь к логу работы модуля
    std::string out_log_path;

    // Путь к stderr логу
    std::string strerr_log_path;

    // Путь к реконструкции pickle файла
    std::string reconstruct_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_