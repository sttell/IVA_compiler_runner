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

    log->writeMessage("Проверка переданных настроек...");
    checkSettingsCorrectness();
    log->writeMessage("Настройки корректные.");

    // Формирование команды запуска и запуск конвертации
    log->writeMessage("Формирование команды конвертации весов.");
    std::string exec = formCommand();

    bp::ipstream std_stream;
    bp::ipstream err_stream;

    log->writeMessage("Запуск конвертации весов из Pickle формата.");
    int return_code = bp::system(
        exec.c_str(),
        bp::std_out > settings.out_log_path.c_str(),
        bp::std_err > err_stream
        );
    std::string return_code_message("Конвертация прошла со статусом: ");

    log->writeMessage((return_code_message + std::to_string(return_code)).c_str());
    // Если код возврата не нулевой, то возникло исключение при работе скрипта
    // Все исключительные ситуации записаны в соответствующий буффер, возвращаем
    // Соответствующий статус завершения
    if (return_code != 0) {
        std::string stderr_output(throw_desc);
        std::string line;

        while (err_stream && std::getline(err_stream, line) && !line.empty())
            stderr_output += line;

        throw std::runtime_error(stderr_output);
    }

    log->writeMessage("Конвертация весов прошла успешно.");
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
    command += boost::filesystem::current_path().generic_string() + PICKLE_CONVERTER_DIR;
    command += PICKLE_CONVERTER_SCRIPT;
    command += " ";
    
    // Добавление аргументов запуска
    addArguments(command);

    return command;
}
