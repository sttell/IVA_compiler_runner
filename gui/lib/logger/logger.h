#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <filesystem>
#include <mutex>

// Внутренне пространство имен с переменными для работы
namespace __logger_impl__
{

// путь к директории с логами
inline const std::string logs_directory = std::filesystem::current_path().string() + "/logs/";

}

// Класс позволяющий проводить логгирование в удобном виде
class Logger
{

public:
    // Конструктор инициализирующий лог. Открывает лог с переданным именем.
    explicit Logger(std::string _logname) : logname(_logname), header("") { init(); };
    // Констуктор инициализирующий лог. Открывает лог с переданными именем + устанавливает соответствующий хэдер сообщений
    explicit Logger(std::string _logname, std::string _header) : logname(_logname), header(_header) { init(); };

    // Деструктор
    ~Logger();

    // Закрыть лог
    void close();
    // Проверить открыт ли лог
    bool is_open();
    // Открыть лог
    void open();
    // Очистка лога
    void clear();

    // Логировать сообщение
    void send(const char* message);
    // Логировать сообщение
    void send(const std::string& message);

private:
    // Инициализация лога
    void init();
    // Инициализация директории с логами
    void initLogDir();
    // Закрытый оператор копирования
    Logger* operator=(Logger&) {return this;}

    // Текущий лог
    std::ofstream current_log;

    // Название файла с логом
    std::string logname;
    // Хэдер сообщений
    std::string header;

    // Мьютекс записи
    std::mutex write_mutex;
    // Мьютекс открытия файла
    std::mutex open_mutex;
    // Мьютекс закрытия файла
    std::mutex close_mutex;

};

#endif // LOGGER_H
