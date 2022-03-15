#ifndef _INCLUDE_COMPILERCORE_H_
#define _INCLUDE_COMPILERCORE_H_

#include <exception>
#include "pipeline.h"
#include "modules.h"
#include "moduleExitStatus.h"
#include "settings/globalSettings.h"
#include "modules/pickleConverterModule.h"
#include "modules/addressCheckerModule.h"
#include "modules/compilerRunnerModule.h"
#include "modules/programComparatorModule.h"
#include "modules/metadataCreatorModule.h"
#include "compileStatus.h"
#include <vector>
#include <memory>

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