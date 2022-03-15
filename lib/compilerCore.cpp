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
     exit_module_status status(ModuleExitStatus::NORUNNED);
     std::unique_ptr<Module> current_module;

     // Оператор выбора соответствуюшего метода
     switch (module) {
        // case Modules::JsonConverter:
        //     break;
        
        case Modules::PickleConverter:
            std::cout << "Pickle converter module" << std::endl;
            current_module.reset(new PickleConverterModule(settings));
            break;
        
        case Modules::MetadataCreator:
            std::cout << "Metadata creator module" << std::endl;
            current_module.reset(new MetadataCreatorModule(settings));
            break;
        
        case Modules::AddrChecker:
            std::cout << "Address checker module" << std::endl;
            current_module.reset(new AddressCheckerModule(settings));
            break;
        
        case Modules::CompileRunner:
            std::cout << "Compiler Runner module" << std::endl;
            current_module.reset(new CompilerRunnerModule(settings));
            break;
        
        case Modules::ProgramComparator:
            std::cout << "Program comparator module" << std::endl;
            current_module.reset(new ProgramComparatorModule(settings));
            break;
                
        default:
            break;
        }
    
    if (current_module.get() != nullptr) 
        status = current_module.get()->runProcess();

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
        if (status == ModuleExitStatus::EXCEPTION || status == ModuleExitStatus::FAILTURE)
            break;
    }
}

// Запуск модуля Compile Status
CompileStatus CompilerCore::getCompileStatus() const {
    return status_buffer;
}