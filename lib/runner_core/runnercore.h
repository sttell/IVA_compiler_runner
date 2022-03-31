#ifndef RUNNERCORE_H
#define RUNNERCORE_H

#include "runner_settings.h"
#include "lib/thread_api/progressbar_buffer.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "local_runner/localrunner.h"

#include "local_runner/localrunner.h"
#include "tensor_creator/tensorcreator.h"
#include "remote_runner/remoterunner.h"

class RunnerCore
{
public:
    RunnerCore(const RunnerSettings& _settings, ProgressBarBuffer* _progress_buffer, StatusBufferCache* _log)
        : settings(_settings), progress_buffer(_progress_buffer), log(_log) {};
    
    ~RunnerCore();

    void runProcess();

private:
    RunnerSettings settings;
    ProgressBarBuffer* progress_buffer;
    StatusBufferCache* log;

    size_t getProgressBarStep();

};

#endif // RUNNERCORE_H
