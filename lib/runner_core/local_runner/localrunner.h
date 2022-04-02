#ifndef LOCALRUNNER_H
#define LOCALRUNNER_H

#include <filesystem>
#include <string>
#include <boost/process.hpp>
#include <iostream>

#include "lib/runner_core/runner_settings.h"
#include "lib/thread_api/progressbar_buffer.h"
#include "lib/thread_api/statusbuffer_cache.h"

#define LOCAL_RUNNER_THROW_HEADER "Local Runner: "

class LocalRunner
{
public:
    LocalRunner(LocalRunnerSettings& _settings, ProgressBarBuffer* _progress, StatusBufferCache* _log)
        : settings(_settings), progress(_progress), log(_log) {};
    ~LocalRunner();

    void runProcess();

private:
    LocalRunnerSettings settings;
    ProgressBarBuffer* progress;
    StatusBufferCache* log;

    void checkSettingsCorrectness();

    void makeOutputDirectory();

    void formExecCommand(std::string& exec);

    void readPipe(boost::process::ipstream& pipe, std::string& text);

    void runProgramm();

    void stdoutPostprocess(boost::process::ipstream& out);
};

#endif // LOCALRUNNER_H
