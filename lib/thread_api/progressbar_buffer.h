#ifndef PROGRESSBARBUFFER_H
#define PROGRESSBARBUFFER_H

#include <stdint.h>
#include <QProgressBar>
#include <mutex>

class ProgressBarBuffer
{
public:
    ProgressBarBuffer() :
        step(0), current_value(0), max_value(100), min_value(0) {};
    ProgressBarBuffer(int _step) :
        step(_step), current_value(0), max_value(100), min_value(0) {};
    ProgressBarBuffer(int _min, int _max) :
        step(0), current_value(0), max_value(_max), min_value(_min) {};

    void setMax(int value);
    void setMin(int value);

    int getMax();
    int getMin();

    int getCurrent();
    void setCurrent(int value);

    void setStep(int value);
    int getStep(int value);

    ProgressBarBuffer& operator++(int val);
    ProgressBarBuffer& operator--(int val);

private:
    std::mutex data_mutex;
    int step;
    int current_value;
    int max_value;
    int min_value;
};

#endif // PROGRESSBARBUFFER_H
