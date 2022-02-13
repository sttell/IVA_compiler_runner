#ifndef _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_

#include <string>

// Структура для хранения настроек модуля Program Comparator Module
struct ProgramComparatorSettings
{
    // Флаг выгрузки логов компиляции в директорию с программой
    bool is_dump_test_data;

    // Пути к бинарным файлам программы
    std::string DTS_S0_file_path;
    std::string DTS_L0_file_path;
    std::string DTS_S1_file_path;
    std::string DTS_L1_file_path;
    std::string VE_file_path;
    std::string ME_file_path;

    // Путь к файлу с весами
    std::string weight_file_path;
    
    // Название директории для файла с весами
    std::string weight_dir_name;
    
    // Путь к файлу с метаданными
    std::string metadata_path;
    
    // Путь к файлу tpu_data с логами процесса компиляции сети
    std::string tpu_data_path;
    
    // Путь к файлу cache_data с логами процесса компиляции сети
    std::string cache_data_path;

    // Название архива с программой
    std::string program_archive_name;

    // Выходная директория с программой
    std::string program_out_dir_path;

    // Путь к логу работы модуля
    std::string out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_PROGRAMCOMPARATORSETTINGS_H_