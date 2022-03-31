#include "../include/module.h"


// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void Module::checkFileExist(const Path& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!path.isExists()) {
        std::string err_desc(throw_desc);
        err_desc += "Файл ";
        err_desc += path.c_str();
        err_desc += " не найден.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}

// Проверка настройки для выходного файла
void Module::checkDirExist(const Path& path) const {
    // Директория ведущая к файлу должна существовать
    if (!path.isExistsPathDirectory()) {
        Path directory = path.getDirectory();
        std::string err_desc(throw_desc);
        err_desc += "Директория ";
        err_desc += directory.c_str();
        err_desc += " не найдена.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    if (path.getType() == PathType::File && path.back() == SLASH) {
        std::string err_desc(throw_desc);
        err_desc += "Путь ";
        err_desc += path.c_str();
        err_desc += " может быть только путем к файлу, а не директорией.\n";
        throw std::runtime_error(err_desc.c_str());
    }
}
