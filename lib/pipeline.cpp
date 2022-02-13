
#include "../include/pipeline.h"

Pipeline::Pipeline() : pipeline(PipelineConstants::InitPipeline) {}

Pipeline::~Pipeline() {}

void Pipeline::setModule(module_t module) {
    setModuleBit(module);
}

bool Pipeline::isModuleExists(module_t module) const {
    return getModuleBit(module) != PipelineConstants::InitPipeline;
}

void Pipeline::setModuleBit(const module_t& module) {
    pipeline |= module;
}

module_t Pipeline::getModuleBit(const module_t& module) const {
    return pipeline & module;
}

void Pipeline::operator=(const Pipeline& copied) {
    pipeline = copied.pipeline;
}
