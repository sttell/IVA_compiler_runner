#include <iostream>

#include "include/compilerCore.h"

void init_pipeline(Pipeline& pipe) {
    pipe.setModule(Modules::PickleConverter);
    pipe.setModule(Modules::FileChecker);
    pipe.setModule(Modules::AddrChecker);
    pipe.setModule(Modules::ProgramComparator);
}

void init_global_settings(GlobalSettings& settings) {
    return;
}

int main() {
    Pipeline compiler_pipeline;
    CompilerCore& core = CompilerCore::getInstance();
    GlobalSettings settings;
    
    init_pipeline(compiler_pipeline);
    init_global_settings(settings);

    core.setPipeline(compiler_pipeline);
    core.runCompileProcess(settings);
    
    return 0;
}