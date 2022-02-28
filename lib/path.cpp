#include "../include/path.h"

// Конструкторы
Path::Path(PathType type) : path_data(""), type(type) {};
Path::Path(std::string path, PathType type) : path_data(path), type(type) {};
Path::Path(const char* path, PathType type) : path_data(path), type(type) {};
Path::~Path() {};

// Проверка сузествования
bool Path::isExists() const {
    // Для каждого типа определен свой метод проверки
    // В случае неизвестного типа выбрасывает исключение
    switch (type)
    {
    case PathType::Unknown:
        return checkUnknownPathExists();
        break;
    case PathType::File:
        return checkFilePathExists();
        break;
    case PathType::Directory:
        return checkDirPathExists();
        break;
    default:
        std::string err_desc(ERR_HEAD);
        err_desc += "Undefinded path type in isExists() method.";
        throw std::runtime_error(err_desc);
        break;
    }
}

// Проверка для пути типа Unknown. Провеяет оба случая.
bool Path::checkUnknownPathExists() const {
    return boost::filesystem::is_directory(path_data) || 
           boost::filesystem::is_regular_file(path_data);
}

// Проверка на наличие файла
bool Path::checkFilePathExists() const {
    return boost::filesystem::is_regular_file(path_data);
}

// Проверка на наличие директории
bool Path::checkDirPathExists() const {
    return boost::filesystem::is_directory(path_data);
}

// Проверка существования директории
bool Path::isExistsPathDirectory() const {
    // Если слэш есть в пути, то проверяем наличие директории

    if (isSlashInPath()) {
        // В случае если директория существует
        std::string directory = getDirectory();
        if (boost::filesystem::is_directory(directory))
            return true;
        // В случае если нет
        return false;
    }
    // В случае когда слэшей нет в пути, то указан путь к исполняемой диреткории
    // и директория по умолчанию существует
    return true;
}

// Операторы присваивания

const Path& Path::operator=(const Path& copied) {
    this->path_data = copied.path_data;
    return *this;
}

const Path& Path::operator=(const std::string& copied) {
    this->path_data = copied;
    return *this;
}

const Path& Path::operator=(const char* copied_ptr) {
    this->path_data = copied_ptr;
    return *this;
}


// Удаление ведущего слэша при его наличии
std::string Path::extractWithoutBeginSlash(const std::string& str) const {
    if (str.front() == SLASH)
        return str.substr(1, str.size());
    return str;
}

// Добавление слэша в конец пути
void Path::extendSlashInEnd(std::string& str) const {
    if (str.back() != SLASH)
        str += SLASH;
}

// Соединение двух строк. Левая часть дополняется слэшем, правая удаляет ведущий слэш
std::string Path::compareStrings(std::string& left, const std::string& right) const {
    extendSlashInEnd(left);
    return left + extractWithoutBeginSlash(right);
}

void Path::setComparedPathType(Path& result, const Path& p1, const Path& p2) const {
    if (p1.type == p2.type) {
        result.setType(p1.type);
        return;
    } else if(p2.type == PathType::File) {
        result.setType(PathType::File);
        return;
    } else if (p2.type == PathType::Unknown || p1.type == PathType::Unknown) {
        result.setType(PathType::Unknown);
        return;
    }
    result.setType(PathType::Unknown);
}

// Операторы сложения - склеивают 2 пути в один с учетом слэшей
Path Path::operator+(const Path& right) {
    Path result;
    setComparedPathType(result, *this, right);
    result.path_data = compareStrings(this->path_data, right.path_data);
    return result;
}
Path Path::operator+(const std::string& right) {
    Path result;
    setComparedPathType(result, *this, right);
    result.path_data = compareStrings(this->path_data, right);
    return result;
}
Path Path::operator+(const char* right_ptr) {
    Path result;
    setComparedPathType(result, *this, right_ptr);
    result.path_data = compareStrings(this->path_data, right_ptr);
    return result;
}

// Вырезание директории из пути
std::string Path::getDirectory() const {
    // Поиск последнего слэша в пути
    int slash_idx = -1;
    for (size_t idx = path_data.size() - 1; idx > 0; idx--) {
        if (path_data[idx] == SLASH) {
            slash_idx = idx;
            break;
        }
    }
    // Если слэш найден, товозвращаем субстроку
    if (slash_idx != -1)
        return path_data.substr(0, slash_idx);

    // Иначе исходный путь
    return path_data;
}

// Возвращение типа пути
PathType Path::getType() const {
    return type;
}

// Установка нового пути
void Path::setType(PathType new_type) {
    type = new_type;
}

// Интерфейс к std::string
const char* Path::c_str() const {
    return path_data.c_str();
}

// Проверка наличия слэшей в пути
bool Path::isSlashInPath() const {
    if (path_data.find(SLASH) == std::string::npos) return false;
    return true;
}

// Интерфейс к std::string
char Path::front() const { return path_data.front(); }
char Path::back() const { return path_data.back(); }
size_t Path::size() const { return path_data.size(); }