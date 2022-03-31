#include "runnercore.h"


RunnerCore::~RunnerCore() {
    progress_buffer = nullptr;
    log = nullptr;

    delete progress_buffer;
    delete log;
}

void RunnerCore::runProcess() {
    progress_buffer->setStep(getProgressBarStep());

    if (settings.is_tensor_create) {
        TensorCreator creator(settings.tensor_create_settings, progress_buffer, log);
        creator.runProcess();
    }

    if (settings.is_remote) {
        log->writeMessage("Начат процесс удаленного выполнения программы.");
        RemoteRunner runner(settings.remote_settings, progress_buffer, log);
        runner.runProcess();
    } else {
        log->writeMessage("Начат процесс локального выполнения программы.");
        LocalRunner runner(settings.local_settings, progress_buffer, log);
        runner.runProcess();
    }

}


size_t RunnerCore::getProgressBarStep() {
    size_t range {100};
    size_t number_of_steps = 0;

    // Tensor create:
    // Step 1. Create tensor
    if (settings.is_tensor_create) number_of_steps++;
    // If need create tensor and transfer to remote host
    if (settings.is_tensor_create && settings.is_remote) number_of_steps++;

    // Local run:
    // Step 1. Check settings
    // Step 2. Run programm
    // Step 3. Process stdout
    if (!settings.is_remote) number_of_steps += 3;

    // Remote run:
    // Step 1. Check settings
    // Step 2. Connect to host
    // Step 3. Remote host authorization
    // Step 4. SFTP connection
    // Step 5. SFTP program transfer to remote host
    // Step 6. SSH remote run program
    // Step 7. SFTP callback transfer to local host
    if (settings.is_remote) number_of_steps += 7;
    if (!settings.remote_settings.is_remote_tensor) number_of_steps += 1;

    return static_cast<size_t>(range / number_of_steps);

}
