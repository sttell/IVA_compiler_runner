
#include "../include/pipeline.h"


// Конструктор
Pipeline::Pipeline() : pipeline() {}

// Деструктор
Pipeline::~Pipeline() {}

// Выставление флага запуска модуля
void Pipeline::setModule(Modules module) {
    pipeline.push(module);
}

bool Pipeline::isEmpty() const {
    return pipeline.empty();
}

Modules Pipeline::getNextModule() {
    if (!pipeline.empty()) {
        Modules current_module = pipeline.front();
        pipeline.pop();
        return current_module;
    } else {
        throw std::runtime_error("Pipeline empty.");
    }
}

// Оператор копирования 
void Pipeline::operator=(const Pipeline& copied) {
    pipeline = copied.pipeline;
}
