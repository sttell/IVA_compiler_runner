#ifndef _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_

#include <string>
#include "../path.h"

// Структура для хранения настроек модуля Program Comparator Module
struct ProgramComparatorSettings
{
    ProgramComparatorSettings() : is_dump_test_data(false),
                                  compiler_dir(PathType::Directory),
                                  program_archive_name("TestProgram"),
                                  program_out_dir_path(PathType::Directory),
                                  out_log_path(PathType::File),
                                  stderr_log_path(PathType::File) {};

    // Флаг выгрузки логов компиляции в директорию с программой
    bool is_dump_test_data;

    // Путь к директории компилятора
    Path compiler_dir;

    // Название архива с программой
    std::string program_archive_name;

    // Выходная директория с программой
    Path program_out_dir_path;

    // Путь к логу работы модуля
    Path out_log_path;

    // Путь к логу с ошибками
    Path stderr_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_