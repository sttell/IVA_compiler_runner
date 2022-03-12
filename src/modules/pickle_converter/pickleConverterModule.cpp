#include "../../../include/modules/pickleConverterModule.h"
#include <iostream>

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
    clearStdErrCache(settings.stderr_log_path);

    try {

        checkSettingsCorrectness();
    
    } catch (const std::runtime_error& e) {
    
        dumpStdErrToLog(e.what(), settings.stderr_log_path.c_str());

        // При возникновении исключения возвращается соответствующий статус
        return ModuleExitStatus::EXCEPTION;
    
    }

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

    if (boost::filesystem::is_empty(settings.stderr_log_path.c_str())) {
        clearStdErrCache(settings.stderr_log_path);
    }

    // Если все прошло хорошо, то возвращаем SUCCESS
    return ModuleExitStatus::SUCCESS;
}

// Проверка корректности настроек
void PickleConverterModule::checkSettingsCorrectness() const {
    // Проверка наличия входного файла
    checkFileExist(settings.pickle_file_path);

    // Проверка корректности путей для выходных файлов
    checkDirExist(settings.out_log_path);
    checkDirExist(settings.reconstruct_log_path);
    checkDirExist(settings.stderr_log_path);
    checkDirExist(settings.weights_out_path);
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