#ifndef RUNNER_ERRORS_H
#define RUNNER_ERRORS_H

#include <map>

enum class RunnerError
{
    PROGRAM_DIR_NOT_EXIT,
    WRONG_GENERATED_TENSOR_FORMAT,
    WRONG_GENERATED_TENSOR_SAVE_PATH,
};

inline const std::map<RunnerError, const char*> runner_error_desc {
    { RunnerError::PROGRAM_DIR_NOT_EXIT,          "Проверьте путь к директории с программой." },
    { RunnerError::WRONG_GENERATED_TENSOR_FORMAT, "Проверьте размер генерируемого тензора." },
    { RunnerError::WRONG_GENERATED_TENSOR_SAVE_PATH, "Проверьте путь для сохранения генерируемого тензора." },
};

#endif // RUNNER_ERRORS_H