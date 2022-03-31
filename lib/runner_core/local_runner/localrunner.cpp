#include "localrunner.h"

LocalRunner::~LocalRunner() {
    progress = nullptr;
    log = nullptr;
    delete progress;
    delete log;
}

void LocalRunner::runProcess() {

    try {

        checkSettingsCorrectness();
        (*progress)++;
        boost::process::ipstream stdout_pipe = runProgramm();
        (*progress)++;
        stdoutPostprocess(stdout_pipe);
        (*progress)++;

    }  catch (const std::exception& e) {
        std::string err_desc(LOCAL_RUNNER_THROW_HEADER);
        log->writeMessage(err_desc + e.what(), "auto", MessageColor::error);
    }


}

void LocalRunner::checkSettingsCorrectness() {
    QString program_zip = settings.program_directory + "/" + settings.program_name;
    if (!std::filesystem::is_regular_file(program_zip.toStdString())) {
        std::string err_desc("Файл с программой ");
        err_desc += program_zip.toStdString() + " не найден.";
        throw std::runtime_error(err_desc);
    }

    if (!std::filesystem::is_regular_file(settings.input_tensor_path.toStdString())) {
        std::string err_desc("Файл со входным тензором ");
        err_desc += settings.input_tensor_path.toStdString() + " не найден.";
        throw std::runtime_error(err_desc);
    }

};

void LocalRunner::makeOutputDirectory() {
    std::string output_dir = settings.program_directory.toStdString() + "/output";

    if (!std::filesystem::is_directory(output_dir))
        std::filesystem::create_directory(output_dir);
}

void LocalRunner::formExecCommand(std::string& exec) {
    std::string output_dir = settings.program_directory.toStdString() + "/output";

    exec += "run_tpu -t -r -p ";
    exec += settings.program_directory.toStdString() + "/" + settings.program_name.toStdString();
    exec += " -i "; exec += settings.input_tensor_path.toStdString();
    exec += " -o "; exec += output_dir + "/output.bin";
}

void LocalRunner::readPipe(boost::process::ipstream& pipe, std::string& text) {
    std::string line;
    while (pipe && std::getline(pipe, line) && !line.empty())
        text += line + "\n";
}

boost::process::ipstream LocalRunner::runProgramm() {

    makeOutputDirectory();

    std::string exec;
    formExecCommand(exec);

    boost::process::ipstream stdout_pipe, stderr_pipe;

    log->writeMessage("Локальный запуск программы...");

    std::string debug_message("Исполняемая команда: "); debug_message += exec;
    log->writeMessage(debug_message);

    boost::process::system(
                exec,
                boost::process::std_out > stdout_pipe,
                boost::process::std_err > stderr_pipe
                );

    std::string stderr_text;

    readPipe(stderr_pipe, stderr_text);

    if (!stderr_text.empty()) {
        throw std::runtime_error(stderr_text);
    }

    log->writeMessage("Локальный запуск прошел успешно.");

    return stdout_pipe;
}

void LocalRunner::stdoutPostprocess(boost::process::ipstream& out) {
    log->writeMessage("Результат выполнения:");

    std::string line;

    while (out && std::getline(out, line)&& !line.empty())
        log->writeMessage(line);

}
