#ifndef _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_

// Структура хранящая данные для удаленного запуска
struct RemoteData {
    // IP адрес хоста
    std::string host_ip;
    
    // Имя пользователя хоста
    std::string host_user;
    
    // Пароль пользователя хоста
    std::string host_password;
    
    // Директория хоста для промежуточного хранения программы
    std::string host_directory;
    
    // Директория хоста для промежуточного хранения output программы
    std::string out_path;

    // Путь к входному файлу на сервере.
    std::string input_file_path;
};

// Структура для хранения настроек модуля Program Runner Module
struct ProgramRunnerSettings
{
    // Флаг удаленного запуска
    bool is_remote_run;
    
    // Флаг сравнения результатов с референсом
    bool is_compare_result;
    
    // Данные для удаленного запуска
    RemoteData remote_data;
    
    // Путь к входному тензору
    std::string input_path;
    
    // Путь к выходному тензору
    std::string output_path;
    
    // Размеры входного тензора
    MapSize input_size;
    
    // Размеры выходного тензора
    MapSize output_size;
    
    // Референсный файл для сравнения
    std::string compared_file;
};

#endif // _LIB_INCLDUE_SETTINGS_PROGRAMRUNNERSETTINGS_H_