#ifndef _INCLUDE_PROGRAMFILEDESCRIPTOR_H_
#define _INCLUDE_PROGRAMFILEDESCRIPTOR_H_

#include <string>
#include "path.h"

// Дескриптор описывающий файлы программы
// Используется для удобного кэширования информации о файлах
// программы.
struct ProgramFileDesc {

public:
    // Конструкторы
    ProgramFileDesc() {init("Unknown file", 0, false, "/uknown_path"); }
    ProgramFileDesc(const std::string& filename) { init(filename, 0, false, "/unknown_path"); }
    ProgramFileDesc(const std::string& filename, const Path& path) { init(filename, 0, false, path); }
    ProgramFileDesc(const std::string& filename, const Path& path, bool is_exist) { init(filename, 0, is_exist, path); }
    ProgramFileDesc(const std::string& filename, const Path& path, bool is_exist, size_t size) { init(filename, size, is_exist, path); }

    // Имя файла
    std::string filename;
    // Размер файла в байтах
    size_t size;
    // Фалг присутствия файла по указанному пути
    bool is_exist;
    // Путь к файлу в ОС
    Path path;

private:
    // Внутренняя функция для инициализации параметров конструкторами
    void init(const std::string& _filename, size_t _size, 
              bool _is_exist, const Path& _file_path) {

        filename = _filename; size = _size;
        is_exist = _is_exist; path = _file_path;
    
    }
};

#endif // _INCLUDE_PROGRAMFILEDESCRIPTOR_H_