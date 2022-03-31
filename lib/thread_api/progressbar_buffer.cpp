#include "progressbar_buffer.h"


void ProgressBarBuffer::setMax(int value) {
    std::lock_guard lg(data_mutex);
    max_value = value;
};

void ProgressBarBuffer::setMin(int value) {
    std::lock_guard lg(data_mutex);
    min_value = value;
}

int ProgressBarBuffer::getMax() {
    std::lock_guard lg(data_mutex);
    return max_value;
}

int ProgressBarBuffer::getMin() {
    std::lock_guard lg(data_mutex);
    return min_value;
}

int ProgressBarBuffer::getCurrent() {
    std::lock_guard lg(data_mutex);
    return current_value;
}

void ProgressBarBuffer::setCurrent(int value) {
    std::lock_guard lg(data_mutex);
    current_value = value;
}

void ProgressBarBuffer::setStep(int value) {
    std::lock_guard lg(data_mutex);
    step = value;
}

int ProgressBarBuffer::getStep(int value) {
    std::lock_guard lg(data_mutex);
    return step;
}

ProgressBarBuffer& ProgressBarBuffer::operator++(int val) {
    std::lock_guard lg(data_mutex);
    int new_value = current_value + step;
    current_value = (new_value <= max_value) ? new_value : max_value;
    return *this;
};

ProgressBarBuffer& ProgressBarBuffer::operator--(int val) {
    std::lock_guard lg(data_mutex);
    int new_value = current_value - step;
    current_value = (new_value >= min_value) ? new_value : min_value;
    return *this;
};
