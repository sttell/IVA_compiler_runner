#ifndef _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_

#include <string>
#include "../path.h"
// Структура для хранения настроек модуля Pickle Converter Module
struct PickleConverterSettings
{
    PickleConverterSettings() : pickle_file_path(PathType::File),
                                weights_out_path(PathType::File),
                                out_log_path(PathType::File),
                                stderr_log_path(PathType::File),
                                reconstruct_log_path(PathType::File) {};

    // Путь к файлу с весами в формате Pickle
    Path pickle_file_path;

    // Путь к файлу с весами в формате bin
    Path weights_out_path;

    // Путь к логу работы модуля
    Path out_log_path;

    // Путь к stderr логу
    Path stderr_log_path;

    // Путь к реконструкции pickle файла
    Path reconstruct_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_PICKLECONVERTERSETTINGS_H_