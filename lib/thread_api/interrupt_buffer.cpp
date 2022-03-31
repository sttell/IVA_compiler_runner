#include "interrupt_buffer.h"

// сигнал остановки процесса
void InterruptBuffer::dumpInterruptSignal() {
    std::lock_guard lg(data_mutex);
    is_interrupt = true;
};

// проверить останавливали ли процесс
bool InterruptBuffer::isInterrupted() {
    std::lock_guard lg(data_mutex);
    return is_interrupt;
};

// принять сигнал об остановке
void InterruptBuffer::signalAccepted() {
    std::lock_guard lg(data_mutex);
    is_interrupt = false;
};

// начать отслеживание процесса
void InterruptBuffer::trackProcess() {
    std::lock_guard lg(data_mutex);
    is_process_started = true;
};

// закончить отслеживание процесса
void InterruptBuffer::endProcess() {
    std::lock_guard lg(data_mutex);
    is_process_started = false;
};

// проверка отслеживается ли процесс
bool InterruptBuffer::isProcessTracked() {
    std::lock_guard lg(data_mutex);
    return is_process_started;
};
