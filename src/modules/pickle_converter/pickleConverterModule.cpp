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
    clearStdErrCache(settings.stderr_log_path);

    // Формирование команды запуска и запуск конвертации
    std::string exec = formCommand();

    int return_code = bp::system(
        exec.c_str(),
        bp::std_out > settings.out_log_path.c_str(),
        bp::std_err > settings.stderr_log_path.c_str()
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
void PickleConverterModule::clearStdErrCache(const Path& path) const {
    // Если файл с кэшем найден, то удаляем его
    bool is_cache_found = path.isExists();
    if (is_cache_found) boost::filesystem::remove(path.c_str());
}

// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void PickleConverterModule::checkFile(const Path& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!path.isExists()) {
        std::string err_desc = THROW_DESC;
        err_desc += "File ";
        err_desc += path.c_str();
        err_desc += " not found.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}

// Проверка настройки для выходного файла
void PickleConverterModule::checkOutFileProperty(const Path& path) const {
    // Директория ведущая к файлу должна существовать
    if (!path.isExistsPathDirectory()) {
        std::string err_desc = THROW_DESC;
        err_desc += "Directory ";
        err_desc += path.c_str();
        err_desc += " with file not found.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    if (path.back() == SLASH) {
        std::string err_desc = THROW_DESC;
        err_desc += "Path ";
        err_desc += path.c_str();
        err_desc += " maybe only file path, not directory!\n";
        throw std::runtime_error(err_desc.c_str());
    }
}

// Проверка корректности настроек
void PickleConverterModule::checkSettingsCorrectness() const {
    // Проверка наличия входного файла
    checkFile(settings.pickle_file_path);

    // Проверка корректности путей для выходных файлов
    checkOutFileProperty(settings.out_log_path);
    checkOutFileProperty(settings.reconstruct_log_path);
    checkOutFileProperty(settings.stderr_log_path);
    checkOutFileProperty(settings.weights_out_path);
}

// Добавление аргументов к команде запуска
void PickleConverterModule::addArguments(std::string& command) const {
    // Аргумент входного файла
    command += INPUT_ARG_NAME;
    command += settings.pickle_file_path.c_str();
    command += " ";

    // Аргумент выходного файла
    command += OUTPUT_ARG_NAME;
    command += settings.weights_out_path.c_str();
    command += " ";

    // Аргумент файла реконструкции
    command += RECONSTRUCT_ARG_NAME;
    command += settings.reconstruct_log_path.c_str();
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