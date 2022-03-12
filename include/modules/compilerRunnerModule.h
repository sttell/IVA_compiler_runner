#ifndef _INCLUDE_MODULES_COMPILERRUNNERMODULE_H_
#define _INCLUDE_MODULES_COMPILERRUNNERMODULE_H_

#include "../module.h"
#include "../settings/globalSettings.h"
#include "../path.h"
#include <fstream>
#include <iostream>
#include <boost/process.hpp>

#define COMPILER_RUNNER_THROW_DESC "Compiler runner error. "

// Имена файлов используемые при подготовке команды запуска
namespace _SpecificFileNames {

const std::string MetaDataInOutSize = "./MetaDataInOutSize.dat";
const std::string hpm_scheduler = "./hpm_scheduler";
}

// Пути ко вторичным файлам генерируемым при компиляции программы
namespace _SpecificPathes {

const std::string weights_verification_log = "./test_files/weights/w_ver*";
const std::string bias_verification_log = "./test_files/bias/w_ver*";
const std::string scale_verification_log = "./test_files/scale/w_ver*";
const std::string warning_data_log = "./test_files/warning_data";
const std::string runtime_data_log = "./test_files/run_time_data1";
const std::string tpu_data_log = "./test_files/tpu_data";

}

// Класс отвечающий за запуск программы на компиляцию.
class CompilerRunnerModule : public Module {
public:
    // Конструктор
    explicit CompilerRunnerModule(const GlobalSettings& _settings) : 
        settings(_settings.compiler_runner) {};
    
    // Деструктор
    ~CompilerRunnerModule() {};
    // Запуск процесса компиляции программы
    exit_module_status runProcess();

protected:
    // Хэдер исключения
    std::string throw_desc = COMPILER_RUNNER_THROW_DESC;
    // Проверка корректности настроек
    void checkSettingsCorrectness() const;

private:
    // Настройки модуля
    CompileRunnerSettings settings;
    // Путь к файлу с размерами тензоров
    Path MetadataInOutSize_path;
    // Путь к исполняемому файлу
    Path hpm_scheduler_path;
    // Итоговая команда запуска скрипта
    std::string exec_command;

    // Формирует внутренние используемые пути
    void formInternalPathes();
    // Формирует файл с размерами тензоров
    void formInOutSizeFile() const;
    // Добавляет аргумент вида --arg value к исполняемой команде
    void addArgument(const std::string&, const std::string&);
    // Формирует команды запуска
    void formCommands();
    // Вызов процесса компиляции
    void runCompile() const;
    // Проверка на наличие ошибок компиляции
    void checkCompileErrors() const;
    // Проверка целостности выходных файлов
    void checkOutputFiles() const; 
    // Проверка наличия строки в файле
    bool isStringInFile(const Path&, const std::string&) const;
};

#endif // _INCLUDE_MODULES_COMPILERRUNNERMODULE_H_