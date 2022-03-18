#include "logger.h"


// Деструктор высвободждает занятый файл
Logger::~Logger()
{
    close();
};

// Метод закрывает файл с логом предварительно логируя процесс
void Logger::close()
{
    this->send("log closed.");

    if(std::lock_guard<std::mutex> lg(close_mutex);current_log.is_open())
        current_log.close();

}

// Проверка открыт ли лог на данный момент
bool Logger::is_open() {
    return current_log.is_open();
}

// Открытие лога
void Logger::open() {
    // Инициализация директории и создание пути к логу
    initLogDir();
    
    std::string log_path = __logger_impl__::logs_directory + logname;
    // Открытие лога на добавление или создание файла
    if (std::lock_guard<std::mutex> open_lg(open_mutex); std::filesystem::is_regular_file(log_path)) {
        current_log.open(log_path, std::ios_base::app);
    } else {
        current_log.open(log_path);
    }


    // Логирование открытия
    this->send("log opened.");

}

// Инциализация логгера - открытие файла
void Logger::init() {
    this->open();
}

// Сброс сообщения в лог
void Logger::send(const char *message) {

    if (!current_log.is_open()) this->open();

    std::lock_guard<std::mutex> write_lg(write_mutex);
        current_log << header << message << "\n";

}

// Сброс сообшения в лог
void Logger::send(const std::string& message) {
    this->send(message.c_str());
}

// Инициализация директории с логами
void Logger::initLogDir() {
    if (!std::filesystem::is_directory(__logger_impl__::logs_directory))
        std::filesystem::create_directory(__logger_impl__::logs_directory);
}
