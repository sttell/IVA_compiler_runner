#include <iostream>
#include <boost/process.hpp>
#include <vector>
#include <string>
#include <exception>
#include "include/compilerCore.h"

void init_pipeline(Pipeline& pipe) {
    pipe.setModule(Modules::PickleConverter);
    pipe.setModule(Modules::FileChecker);
    pipe.setModule(Modules::AddrChecker);
    pipe.setModule(Modules::ProgramComparator);
}

void init_global_settings(GlobalSettings& settings) {
    settings.pickle_converter.out_log_path = "logs/pickle.log";
    settings.pickle_converter.pickle_file_path = "fpga_data.pickle";
    settings.pickle_converter.weights_out_path = "weights.bin";
    settings.pickle_converter.strerr_log_path = "logs/pickle_converter_stderr.log";
    settings.pickle_converter.reconstruct_log_path = "logs/pickle_reconstruct.log";
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