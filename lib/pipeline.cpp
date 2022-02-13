
#include "../include/pipeline.h"

// Конструктор
Pipeline::Pipeline() : pipeline(PipelineConstants::InitPipeline) {}

// Деструктор
Pipeline::~Pipeline() {}

// Выставление флага запуска модуля
void Pipeline::setModule(module_t module) {
    setModuleBit(module);
}

// Проверка наличия флага запуска модуля
bool Pipeline::isModuleExists(module_t module) const {
    return getModuleBit(module) != PipelineConstants::InitPipeline;
}

// Выставление бита в соответствующей позиции
void Pipeline::setModuleBit(const module_t& module) {
    pipeline |= module;
}

// Проверка наличия бита
module_t Pipeline::getModuleBit(const module_t& module) const {
    return pipeline & module;
}

// Оператор копирования 
void Pipeline::operator=(const Pipeline& copied) {
    pipeline = copied.pipeline;
}

// Удаление флага запуска модуля
void Pipeline::deleteModule(module_t module) {
    pipeline ^= module;
}
