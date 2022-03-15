#ifndef _INCLUDE_PATH_H_
#define _INCLUDE_PATH_H_

#include <string>
#include <boost/filesystem/operations.hpp>

#define ERR_HEAD "Path type error. "

#ifdef _WIN32
#define SLASH '\\'
#endif // _WIN32

#ifdef __linux__
#define SLASH '/'
#endif // __linux__

// Типы возможных путей
enum class PathType {
    Directory,
    File,
    Unknown
};

// Класс для работы с путями к директориям и файлам
// реализован на базе std::string и имеет схожий интерфейс
class Path {
public:
    // Базовый конструктор
    Path(PathType type=PathType::Unknown);
    // Конструктор копирования строки
    Path(std::string, PathType type=PathType::Unknown);
    // Конструктор копирования С строки
    Path(const char*, PathType type=PathType::Unknown);
    ~Path();

    // Проверка на существования указанного пути и файла
    bool isExists() const;
    // Проверка существования директории указанной в пути без учета файла
    bool isExistsPathDirectory() const;

    // Оператор присваивания на различные типы
    const Path& operator=(const std::string&);
    const Path& operator=(const Path&);
    const Path& operator=(const char*);

    // Оператор сложения на различные типы
    Path operator+(const Path&) const;
    Path operator+(const std::string&) const;
    Path operator+(const char*) const;

    // Выставление типа нового пути при совмещении двух путей
    void setComparedPathType(Path&, const Path&, const Path&) const;

    // Возвращает директорию указанную в пути к файлу
    std::string getDirectory() const;

    // Возвращает тип пути
    PathType getType() const;

    // Устанавливает новый тип пути
    void setType(PathType);

    // Интерфейс к std::string
    const char* c_str() const;
    char back() const;
    char front() const;
    size_t size() const;

private:
    // Проверка наличия слэшей в пути
    bool isSlashInPath() const;
    
    // Проверка существования путей различных типов
    bool checkUnknownPathExists() const;
    bool checkFilePathExists() const;
    bool checkDirPathExists() const;

    // Расширение строки путем добавления слэша
    void extendSlashInEnd(std::string&) const;
    
    // Вырезание строки без учета ведущего слэша
    std::string extractWithoutBeginSlash(const std::string&) const;
    
    // Склейка двух строк определенным для пути образом
    std::string compareStrings(std::string, std::string) const;
    
    // Путь
    std::string path_data;
    
    // Тип пути
    PathType type;
};


#endif // _INCLUDE_PATH_H