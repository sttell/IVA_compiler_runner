#include <iostream>
#include <boost/process.hpp>
#include <vector>
#include <string>
#include <exception>
#include "include/compilerCore.h"
#include "include/jsonHandler.h"
#include "include/timer.h"
#include <thread>

void init_pipeline(Pipeline& pipe) {
    // pipe.setModule(Modules::AddrChecker);
    // pipe.setModule(Modules::PickleConverter);
    // pipe.setModule(Modules::CompileRunner);
    // pipe.setModule(Modules::MetadataCreator);
    pipe.setModule(Modules::ProgramComparator);
}

void init_global_settings(GlobalSettings& settings) {
    std::string current_dir = boost::filesystem::current_path().generic_string();
    std::string compiler_dir = "/home/ilya/projects/work/IVA_compiler";

    settings.pickle_converter.out_log_path = current_dir + "/logs/pickle.log";
    settings.pickle_converter.pickle_file_path = compiler_dir + "/python_scripts/pickle/fpga_data.pickle";
    settings.pickle_converter.weights_out_path = compiler_dir + "/weights.bin";
    settings.pickle_converter.stderr_log_path = current_dir + "/logs/pickle_converter_stderr.log";
    settings.pickle_converter.reconstruct_log_path = current_dir + "/logs/pickle_reconstruct.log";

    settings.addr_checker.json_path = compiler_dir + "/test.json";
    settings.addr_checker.pickle_buffer_path = settings.pickle_converter.out_log_path;
    settings.addr_checker.out_log_path = current_dir + "/logs/addr_checker.log";
    settings.addr_checker.out_json_path = compiler_dir + "/test.json";
    settings.addr_checker.stderr_log_path = current_dir + "/logs/addr_checker_stderr.log";

    settings.compiler_runner.compiler_dir = compiler_dir;
    settings.compiler_runner.current_device = Device::MOBILE;
    settings.compiler_runner.input = {1, 224, 224, 4};
    settings.compiler_runner.output = {1, 112, 112, 256};
    settings.compiler_runner.make_n_jobs = 8;
    settings.compiler_runner.num_starts = 1;
    settings.compiler_runner.out_log_path = current_dir + "/logs/compiler_runner.log";
    settings.compiler_runner.path_to_json = settings.addr_checker.out_json_path;
    settings.compiler_runner.path_to_weights = settings.pickle_converter.weights_out_path;
    settings.compiler_runner.stderr_log_path = current_dir + "/logs/compiler_runner_stderr.log";

    settings.metadata_creator.compiler_dir = compiler_dir;
    settings.metadata_creator.input_map = {1, 224, 224, 4};
    settings.metadata_creator.output_map = settings.compiler_runner.output;
    settings.metadata_creator.api_version = "2.0.0";
    settings.metadata_creator.ip_version = "02.05.04";
    settings.metadata_creator.device_type = Device::MOBILE;
    settings.metadata_creator.input_map_scale = 0.8407199382781982;
    settings.metadata_creator.output_map_scales = 0.3444758653640747;
    settings.metadata_creator.out_log_path = current_dir + "/log/metadata_creator.log";
    settings.metadata_creator.stderr_log_path = current_dir + "/log/metadata_creator_stderr.log";

    settings.program_comparator.is_dump_test_data = false;
    settings.program_comparator.compiler_dir = compiler_dir;
    settings.program_comparator.out_log_path = current_dir + "/logs/program_comparator.log";
    settings.program_comparator.program_archive_name = "program.zip";
    settings.program_comparator.program_out_dir_path = "/home/ilya/projects/cpp/TestDir/program_comparator_test";
    settings.program_comparator.stderr_log_path = current_dir + "/logs/program_comparator_stderr.log";
}

int main() {
    Pipeline compiler_pipeline;
    CompilerCore& core = CompilerCore::getInstance();
    GlobalSettings settings;
    
    Timer t;
    t.start();
    init_pipeline(compiler_pipeline);
    init_global_settings(settings);

    core.setPipeline(compiler_pipeline);
    core.runCompileProcess(settings);
    t.end();

    std::cout << "Compile time:" << t.getStringFormat("MM min SS sec MS ms") << std::endl;
    return 0;
}