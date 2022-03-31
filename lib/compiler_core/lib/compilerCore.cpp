#include "lib/compiler_core/include/compilerCore.h"

// запуск процесса компиляции
void CompilerCore::runProcess() {
    // Пока пайплайн не пусти или процесс не приостановлен запускаем модули
    while(!pipeline.isEmpty() && !interrupt_buffer->isInterrupted()) {
        runModule(pipeline.getNextModule());
    }

    // Если процесс приостановлен, то выводим сообщение в лог и принимаем сигнал
    if (interrupt_buffer->isInterrupted()) {
        log->writeMessage("Выполнение компиляции остановлено принудительно.", "auto", MessageColor::warning);
        interrupt_buffer->signalAccepted();
    }
    // Завершаем процессы
    interrupt_buffer->endProcess();
    log->endProcess();
};

// Запуск модуля
void CompilerCore::runModule(Modules module) {

    // Абстрактный метод. Объект типа модуль
    Module* current_module = nullptr;

    // Выбираем соответствующий модуль и инициализируем объект
    switch (module) {
    case Modules::AddrChecker:
        log->writeMessage("Запущена проверка соответствия адресов из Pickle и JSON.");
        current_module = new AddressCheckerModule(settings, log);
        break;
    case Modules::ChangeOptimizatons:
        log->writeMessage("Начато изменение назначенных оптимизаций.");
        current_module = new OptimizationChangerModule(settings, log);
        break;
    case Modules::CompileRunner:
        log->writeMessage("Начат процесс компиляции программы.");
        current_module = new CompilerRunnerModule(settings, log);
        break;
    case Modules::MetadataCreator:
        log->writeMessage("Начат процесс формирования файлов с метаданными.");
        current_module = new MetadataCreatorModule(settings, log);
        break;
    case Modules::JsonConverter:
        log->writeMessage("Начат процесс конвертации Json формата сети.");
        break;
    case Modules::PickleConverter:
        log->writeMessage("Начат процесс конвертации Pickle весов в формат bin.");
        current_module = new PickleConverterModule(settings, log);
        break;
    case Modules::ProgramComparator:
        log->writeMessage("Начат процесс сборки программы.");
        current_module = new ProgramComparatorModule(settings, log);
        break;
    }

    // Запускаем работу модуля под оберткой для отлавливания исключений
    if (current_module != nullptr)
        exceptionHandlerWrap(current_module);

    // Высвобождение памяти
    delete current_module;

};

// Обертка для отлавливания исключений на этапе запуска модуля
void CompilerCore::exceptionHandlerWrap(Module* module) {

    // Пытаемся запустить процесс. Если процесс срабатывает с исключением, то логгируем ошибку.
    try {
        module->runProcess();
    }  catch (const std::exception& e) {
        log->writeMessage(e.what(), CORE_EXCEPTION_HEADER, MessageColor::error);
        interrupt_buffer->dumpInterruptSignal();
    }
}
