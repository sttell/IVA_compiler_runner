#include "../../../include/modules/pickleConverterModule.h"

namespace bp = boost::process;

/* Метод запуска конвертации обрабатывает различные ситуации:
* 1. Происходит проверка настроек
* 2. Обрабатываются исключения
* 3. Запуск конвертации
* 4. Очистка кэша потока ошибок
* 5. Проверка статуса завершения модуля
*/
exit_module_status PickleConverterModule::runProcess() {
    // Проверка ошибок в конфигурации модуля
    // При возникновении ошибки выводит описание в буффер
    try {

        checkSettingsCorrectness();
    
    } catch (const std::runtime_error& e) {
    
        std::ofstream err_log;
        err_log.open(ERROR_BUFFER);
        if (err_log.is_open()) {
            err_log << e.what() << std::endl;
        }

        // При возникновении исключения возвращается соответствующий статус
        return ModuleExitStatus::EXCEPTION;
    
    }
    
    // Очистка кэша буффера
    clearStdErrCache(settings.strerr_log_path);

    // Формирование команды запуска и запуск конвертации
    std::string exec = formCommand();

    int return_code = bp::system(
        exec.c_str(),
        bp::std_out > settings.out_log_path,
        bp::std_err > settings.strerr_log_path
    );

    // Если код возврата не нулевой, то возникло исключение при работе скрипта
    // Все исключительные ситуации записаны в соответствующий буффер, возвращаем
    // Соответствующий статус завершения
    if (return_code != 0) {
        return ModuleExitStatus::FAILTURE;
    }

    // Если все прошло хорошо, то возвращаем SUCCESS
    return ModuleExitStatus::SUCCESS;
}


// Очистка кэша потока ошибок. 
// Необходимо для корректного вывода ошибок при каждом запуске
void PickleConverterModule::clearStdErrCache(const std::string& path) const {
    // Если файл с кэшем найден, то удаляем его
    bool is_cache_found = boost::filesystem::is_regular_file(path);
    if (is_cache_found) boost::filesystem::remove(path);
}


// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void PickleConverterModule::checkFile(const std::string& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!boost::filesystem::is_regular_file(path)) {
        std::string err_desc = THROW_DESC;
        err_desc += "File ";
        err_desc += path + " not found.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}


// Проверка существования директории
bool PickleConverterModule::checkDir(const std::string& path) const {
    if (boost::filesystem::is_directory(path)) return true;
    return false;
}


// Проверка на принадлежность строки к типу "путь к директории"
// Если последний символ - слэш, то возвращаем true
bool PickleConverterModule::isDirectoryPath(const std::string& path) const {
    if (path.back() == SLASH) return true;
    return false;
}


// Проверка на присутствие слэшей в пути
bool PickleConverterModule::isDirectoryInPath(const std::string& path) const {
    for (int sym_id=0; sym_id < path.size(); sym_id++) {
        if (sym_id == SLASH) return true;
    }
    return false;
}


// Проверка настройки для выходного файла
void PickleConverterModule::checkOutFileProperty(const std::string& path) const {
    // Выходной файл не должен оканчиваться на слэш
    if (!isDirectoryInPath(path)) return;

    // Выходной файл не должен быть путем к директории
    if (isDirectoryPath(path)){
        std::string err_desc = THROW_DESC;
        err_desc += "Path ";
        err_desc += path + " maybe only path to file, not directory.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    // Директория ведущая к файлу должна существовать
    std::string directory = getDirectoryFromPath(path);
    if (!boost::filesystem::is_directory(directory)) {
        std::string err_desc = THROW_DESC;
        err_desc += "Directory ";
        err_desc += path + " with file not found.\n";
        throw std::runtime_error(err_desc.c_str());
    }
}

// Извлечение директории из пути
std::string PickleConverterModule::getDirectoryFromPath(const std::string& path) const {
    // Обратным проходом ищем первый слэш и обрезаем от начала до него
    size_t end_symbol = path.size() - 1;
    
    for (int sym_num=end_symbol; sym_num > 0; sym_num--) {
        if (path[sym_num] == SLASH) {
            end_symbol = sym_num;
            break;
        }
    }
    return path.substr(0, end_symbol);        
}

// Проверка корректности настроек
void PickleConverterModule::checkSettingsCorrectness() const {
    // Проверка наличия входного файла
    checkFile(settings.pickle_file_path);

    // Проверка корректности путей для выходных файлов
    checkOutFileProperty(settings.out_log_path);
    checkOutFileProperty(settings.reconstruct_log_path);
    checkOutFileProperty(settings.strerr_log_path);
    checkOutFileProperty(settings.weights_out_path);
}

// Добавление аргументов к команде запуска
void PickleConverterModule::addArguments(std::string& command) const {
    // Аргумент входного файла
    command += INPUT_ARG_NAME;
    command += settings.pickle_file_path;
    command += " ";

    // Аргумент выходного файла
    command += OUTPUT_ARG_NAME;
    command += settings.weights_out_path;
    command += " ";

    // Аргумент файла реконструкции
    command += RECONSTRUCT_ARG_NAME;
    command += settings.reconstruct_log_path;
    command += " ";
}

// Формирование команды запуска
std::string PickleConverterModule::formCommand() const {
    
    // Команда запуска интерпретатора
    std::string command = PYTHON_INTERPRETATOR_CMD;
    command += PYTHON_VERSION;
    command += " ";

    // Путь к скрипту конвертера
    command += PICKLE_CONVERTER_DIR;
    command += PICKLE_CONVERTER_SCRIPT;
    command += " ";
    
    // Добавление аргументов запуска
    addArguments(command);

    return command;
}