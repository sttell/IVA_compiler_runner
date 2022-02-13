#ifndef _INCLUDE_COMPILERCORE_H_
#define _INCLUDE_COMPILERCORE_H_

#include <exception>
#include "pipeline.h"
#include "modules.h"
#include "moduleExitStatus.h"
#include "settings/globalSettings.h"
#include "compileStatus.h"
#include <vector>

/* Ядро для запуска пайплайна компиляции.
*   
*  Ядро является Singletone классом.
*  Перед запуском необходимо инициализировать пайплайн компиляции.
*  После инициализации можно запускать процесс компиляции.
*  Настройки должны содержать корректные данные собранные из GUI.
*/
class CompilerCore
{
private:
    // Пайплайн компиляции
    Pipeline compile_pipe;
    // Текущий исполняемый модуль
    module_t current_module;
    // Текущий статус компиляции
    CompileStatus status_buffer;
    
    // Защищенные конструкторы. Реализация Mayers Singletone
    CompilerCore() : current_module(Modules::NoModules) {};
    CompilerCore(const CompilerCore&) : current_module(Modules::NoModules),
                                        status_buffer({Modules::NoModules, 
                                                       ModuleExitStatus::NORUNNED}
                                                       ) {};  
    CompilerCore& operator=(CompilerCore&) { return *this; };

    // Метод запуска модуля
    exit_module_status runModule(const module_t&, const GlobalSettings&);
    
    // Получение статуса исполняемого модуля
    exit_module_status getModuleStatus() const;


    // Обновление статуса компиляции
    void updateModuleStatus(const module_t&, exit_module_status);
    
    // Обновление текущего исполняемого модуля. Переход на следующий.
    bool updateCurrentModule(const module_t&);

    // Обновление current_module.
    bool getNextModule();

    // Методы запуска различных модулей
    exit_module_status runJsonConverterModule(const JsonConverterSettings&) const;
    exit_module_status runPickleConverterModule(const PickleConverterSettings&) const;
    exit_module_status runFileCheckerModule(const FileCheckerSettings&) const;
    exit_module_status runAddrCheckerModule(const AddrCheckerSettings&) const;
    exit_module_status runCompileRunnerModule(const CompileRunnerSettings&) const;
    exit_module_status runProgramComparatorModule(const ProgramComparatorSettings&) const;
    exit_module_status runProgramRunnerModule(const ProgramRunnerSettings&) const;
    
public:
    // Возврат объекта ядра. Mayer Singletone
    static CompilerCore& getInstance() {
        static CompilerCore instance;
        return instance;
    }

    // Установка пайплайна компиляции
    void setPipeline(const Pipeline& copied) { compile_pipe = copied; };
    // Запуск процесса компиляции
    void runCompileProcess(const GlobalSettings&);
    // Получение статуса компиляции
    CompileStatus getCompileStatus() const;
};

#endif // _INCLUDE_COMPILERCORE_H_