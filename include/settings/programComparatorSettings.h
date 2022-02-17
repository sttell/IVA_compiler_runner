#ifndef _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_

#include <string>
#include "../path.h"

// Структура для хранения настроек модуля Program Comparator Module
struct ProgramComparatorSettings
{
    ProgramComparatorSettings() : is_dump_test_data(false),
                                  DTS_S0_file_path(PathType::File),
                                  DTS_S1_file_path(PathType::File),
                                  DTS_L0_file_path(PathType::File),
                                  DTS_L1_file_path(PathType::File),
                                  ME_file_path(PathType::File),
                                  VE_file_path(PathType::File),
                                  weight_file_path(PathType::File),
                                  weight_dir_name("constants"),
                                  metadata_path(PathType::File),
                                  tpu_data_path(PathType::File),
                                  cache_data_path(PathType::File),
                                  program_archive_name("program.zip"),
                                  program_out_dir_path(PathType::Directory),
                                  out_log_path(PathType::File) {};

    // Флаг выгрузки логов компиляции в директорию с программой
    bool is_dump_test_data;

    // Пути к бинарным файлам программы
    Path DTS_S0_file_path;
    Path DTS_L0_file_path;
    Path DTS_S1_file_path;
    Path DTS_L1_file_path;
    Path VE_file_path;
    Path ME_file_path;

    // Путь к файлу с весами
    Path weight_file_path;
    
    // Название директории для файла с весами
    std::string weight_dir_name;
    
    // Путь к файлу с метаданными
    Path metadata_path;
    
    // Путь к файлу tpu_data с логами процесса компиляции сети
    Path tpu_data_path;
    
    // Путь к файлу cache_data с логами процесса компиляции сети
    Path cache_data_path;

    // Название архива с программой
    Path program_archive_name;

    // Выходная директория с программой
    Path program_out_dir_path;

    // Путь к логу работы модуля
    Path out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_