#include <iostream>
#include <boost/process.hpp>
#include <vector>
#include <string>
#include <exception>
#include "include/compilerCore.h"
#include "include/jsonHandler.h"

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
    settings.pickle_converter.stderr_log_path = "logs/pickle_converter_stderr.log";
    settings.pickle_converter.reconstruct_log_path = "logs/pickle_reconstruct.log";

    settings.addr_checker.json_path = "test.json";
    settings.addr_checker.pickle_buffer_path = settings.pickle_converter.out_log_path;
    settings.addr_checker.out_log_path = "logs/addr_checker.log";
    settings.addr_checker.out_json_path = "checked_test.json";
    settings.addr_checker.stderr_log_path = "logs/addr_checker_stderr.log";
}

int main() {
    Pipeline compiler_pipeline;
    CompilerCore& core = CompilerCore::getInstance();
    GlobalSettings settings;
    
    init_pipeline(compiler_pipeline);
    init_global_settings(settings);

    core.setPipeline(compiler_pipeline);
    core.runCompileProcess(settings);
    
    JsonHandler jh;
    boost::property_tree::ptree json;
    Path test_input_json("test.json");
    Path test_output_json("out_test.json");
    jh.read(test_input_json, json);
    jh.dump(test_output_json, json);

    return 0;
}