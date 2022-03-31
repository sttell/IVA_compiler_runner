#ifndef _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_

#include "../path.h"
#include "../mapSize.h"

using ip_t = std::string;
using username_t = std::string;
using password_t = std::string;

// Структура хранящая данные для удаленного запуска
struct RemoteData {
    RemoteData() : host_ip("0.0.0.0"),
                   host_user("user"),
                   host_password("password"),
                   host_directory(PathType::Directory),
                   out_path(PathType::Directory),
                   input_file_path(PathType::File) {};

    // IP адрес хоста
    ip_t host_ip;
    
    // Имя пользователя хоста
    username_t host_user;
    
    // Пароль пользователя хоста
    password_t host_password;
    
    // Директория хоста для промежуточного хранения программы
    Path host_directory;
    
    // Директория хоста для промежуточного хранения output программы
    Path out_path;

    // Путь к входному файлу на сервере.
    Path input_file_path;
};

// Структура для хранения настроек модуля Program Runner Module
struct ProgramRunnerSettings
{
    ProgramRunnerSettings() : is_remote_run(false),
                              is_compare_result(false),
                              remote_data(),
                              input_path(PathType::File),
                              output_path(PathType::File),
                              input_size(),
                              output_size(),
                              compared_file(PathType::File) {};
    // Флаг удаленного запуска
    bool is_remote_run;
    
    // Флаг сравнения результатов с референсом
    bool is_compare_result;
    
    // Данные для удаленного запуска
    RemoteData remote_data;
    
    // Путь к входному тензору
    Path input_path;
    
    // Путь к выходному тензору
    Path output_path;
    
    // Размеры входного тензора
    MapSize input_size;
    
    // Размеры выходного тензора
    MapSize output_size;
    
    // Референсный файл для сравнения
    Path compared_file;
};

#endif // _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_