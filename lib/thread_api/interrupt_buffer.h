#ifndef INTERRUPTBUFFER_H
#define INTERRUPTBUFFER_H

#include <mutex>

class InterruptBuffer
{
public:
    InterruptBuffer() : is_interrupt(false), is_process_started(false) {};
    ~InterruptBuffer() {};

    void dumpInterruptSignal();
    bool isInterrupted();
    void signalAccepted();
    bool isProcessTracked();
    void trackProcess();
    void endProcess();
private:
    std::mutex data_mutex;
    volatile bool is_interrupt;
    volatile bool is_process_started;
};

#endif // INTERRUPTBUFFER_H
