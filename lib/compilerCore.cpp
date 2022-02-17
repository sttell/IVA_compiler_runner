#include "../include/compilerCore.h"

// Пространство имен содержащее функции используемые в backend CompilerCore
namespace ShiftModuleFunc {

// Максимальная позиция флага модуля. Старший выставленный бит.
const module_t MAX_MODULE_POS = 1 << (sizeof(module_t) * 8 - 1);

// Смещение позиции флага модуля на следующий.
// Возвращает true, в случае успешного смещения, false в случае конца значений.
bool shift(module_t& pos) {
    // Если стоит нулевая позиция, то необходимо выставить младший бит.
    if (pos == Modules::NoModules) {
        pos = 0b1;
        return true;
    }

    // Если позиция меньше максимальной, то переставляем бит на следующую позицию
    if (pos < MAX_MODULE_POS) {
        pos = pos << 1;
        return true;
    }
    
    // В базовом случае бит сдвинут быть не может. Значит все возможные позиции перебраны.
    return false;
}

}

// Запуск метода отвечающего за выполнение module с настройками settings
exit_module_status CompilerCore::runModule(const module_t& module, const GlobalSettings& settings) {
     
     // Статус выполнения
     exit_module_status status;
     
     // Оператор выбора соответствуюшего метода
     switch (module) {
        case Modules::JsonConverter:
            status = runJsonConverterModule(settings.json_converter);
            break;
        
        case Modules::PickleConverter:
            status = runPickleConverterModule(settings.pickle_converter);
            break;
        
        case Modules::FileChecker:
            status = runFileCheckerModule(settings.file_checker);
            break;
        case Modules::AddrChecker:
            status = runAddrCheckerModule(settings.addr_checker);
            break;
        case Modules::CompileRunner:
            status = runCompileRunnerModule(settings.compiler_runner);
            break;
        
        case Modules::ProgramComparator:
            status = runProgramComparatorModule(settings.program_comparator);
            break;
        
        case Modules::ProgramRunner:
            status = runProgramRunnerModule(settings.program_runner);
            break;
        
        default:
            break;
        }
    
    // По завершении отправляем статус выбранного модуля.
    return status;
}

// Мультипоточное обновление буффера статуса выполнения компиляции.
// На данный момент не реализовано.
exit_module_status CompilerCore::getModuleStatus() const {
    // TODO Дописать мультипоточное обновление статус буффера
    return ModuleExitStatus::NORUNNED;
}

// Обновление статуса компиляции для однопоточного режима работы
void CompilerCore::updateModuleStatus(const module_t& module, exit_module_status status) {
    status_buffer.status = status;
    status_buffer.runned_module = module;
}

// Обновление текущего модуля в пайплайне компиляции. Возвращает true в случае успешной смены модулей.
bool CompilerCore::updateCurrentModule(const module_t& module) {
    // Если модуль присутствует в пайплайне, 
    // то обновляем текущий модуль на новый и удаляем его из пайплайна
    if (compile_pipe.isModuleExists(module)) {
        current_module = module;
        compile_pipe.deleteModule(current_module);
        return true;
    }
    
    // Если модуль не был обновлен, то возвращаем false
    return false;
}

// Получает следующий модуль из пайплайна компиляции.
bool CompilerCore::getNextModule() {
    
    // Базовая позиция модуля - нулевая
    module_t module_position = Modules::NoModules;
    // Статус обновления
    bool status = false;

    // Пока сдвиг битов возможен проходимся по всем позициям
    // и проверяем наличие флага запуска соответствующего модуля 
    // в пайплайне компиляции. Если запускаемый модуль найден, то возвращаем status == true
    while (ShiftModuleFunc::shift(module_position)) {
        status = updateCurrentModule(module_position);
        if (status) break;
    }

    return status;
}

// Запуск процесса компиляции
void CompilerCore::runCompileProcess(const GlobalSettings& settings) {
    // Пока следующий модуль обнаруживается выполняем обновление
    // статуса модуля, ожидаем завершения его работы и обновляем статус
    // в соответствии с exit_module_status
    while (getNextModule()) {
        updateModuleStatus(current_module, ModuleExitStatus::WAIT);
        exit_module_status status = runModule(current_module, settings);
        updateModuleStatus(current_module, status);
    }
}

// Запуск модуля Json Converter
exit_module_status CompilerCore::runJsonConverterModule(const JsonConverterSettings& settings) const {
    std::cout << "Module JSON Converter runned" << std::endl;
    return ModuleExitStatus::SUCCESS;
}

// Запуск модуля Pickle Converter
exit_module_status CompilerCore::runPickleConverterModule(const PickleConverterSettings& settings) const {
    std::cout << "Module Pickle Converter runned" << std::endl;
    PickleConverterModule module(settings);
    return module.runProcess();
}

// Запуск модуля File Checker
exit_module_status CompilerCore::runFileCheckerModule(const FileCheckerSettings& settings) const {
    std::cout << "Module File Checker runned" << std::endl;
    return ModuleExitStatus::SUCCESS;
}

// Запуск модуля Addr Checker
exit_module_status CompilerCore::runAddrCheckerModule(const AddrCheckerSettings& settings) const {
    std::cout << "Module Addr Checker runned" << std::endl;
    AddressCheckerModule module(settings);
    return module.runProcess();
}

// Запуск модуля Compile Runner
exit_module_status CompilerCore::runCompileRunnerModule(const CompileRunnerSettings& settings) const {
    std::cout << "Module Compile Runner runned" << std::endl;
    return ModuleExitStatus::SUCCESS;
}

// Запуск модуля Program Comparator
exit_module_status CompilerCore::runProgramComparatorModule(const ProgramComparatorSettings& settings) const {
    std::cout << "Module Program Comparator runned" << std::endl;
    return ModuleExitStatus::SUCCESS;
}

// Запуск модуля Program Runner
exit_module_status CompilerCore::runProgramRunnerModule(const ProgramRunnerSettings& settings) const {
    std::cout << "Module Program Runner runned" << std::endl;
    return ModuleExitStatus::SUCCESS;
}

// Запуск модуля Compile Status
CompileStatus CompilerCore::getCompileStatus() const {
    return status_buffer;
}