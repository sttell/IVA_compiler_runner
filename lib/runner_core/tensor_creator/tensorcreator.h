#ifndef TENSORCREATOR_H
#define TENSORCREATOR_H

#include <string>
#include <iostream>
#include <fstream>

#include "lib/runner_core/runner_settings.h"
#include "lib/thread_api/progressbar_buffer.h"
#include "lib/thread_api/statusbuffer_cache.h"

#define TENSOR_CREATOR_THROW_HEADER "Tensor Creator: "

class TensorCreator
{
public:
    TensorCreator(TensorCreatorSettings& _settings, ProgressBarBuffer* _progress, StatusBufferCache* _log)
        : settings(_settings), progress(_progress), log(_log) {};
    ~TensorCreator();

    void runProcess();

private:
    TensorCreatorSettings settings;
    ProgressBarBuffer* progress;
    StatusBufferCache* log;

    void parseSizes(std::vector<size_t>& sizes);

    void generateTensor(const std::vector<size_t>& sizes);

};

#endif // TENSORCREATOR_H
