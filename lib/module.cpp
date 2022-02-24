#include "../include/module.h"


// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void Module::checkFileExist(const Path& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!path.isExists()) {
        std::string err_desc(throw_desc);
        err_desc += "File ";
        err_desc += path.c_str();
        err_desc += " not found.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}

// Очистка кэша потока ошибок. 
// Необходимо для корректного вывода ошибок при каждом запуске
void Module::clearStdErrCache(const Path& path) const {
    // Если файл с кэшем найден, то удаляем его
    bool is_cache_found = path.isExists();
    if (is_cache_found) boost::filesystem::remove(path.c_str());
}

// Проверка настройки для выходного файла
void Module::checkDirExist(const Path& path) const {
    // Директория ведущая к файлу должна существовать
    if (!path.isExistsPathDirectory()) {
        std::string err_desc(throw_desc);
        err_desc += "Directory ";
        err_desc += path.c_str();
        err_desc += " with file not found.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    if (path.back() == SLASH) {
        std::string err_desc(throw_desc);
        err_desc += "Path ";
        err_desc += path.c_str();
        err_desc += " maybe only file path, not directory!\n";
        throw std::runtime_error(err_desc.c_str());
    }
}

// Выбросить исключение с описанием description
void Module::throwWithDesc(const std::string& description) const {
    std::string err_desc(throw_desc);
    err_desc += description;
    throw std::runtime_error(err_desc);
}