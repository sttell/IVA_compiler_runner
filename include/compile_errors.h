#ifndef COMPILE_ERRORS_H
#define COMPILE_ERRORS_H

#include <map>

enum class CompileError
{
    JSON_NOT_FOUND,
    WEIGHTS_NOT_FOUND,
    WRONG_WEIGHTS_FORMAT,
    WRONG_CATALOG_NAME,
    WRONG_PADDINGS_FORMAT,
    WRONG_INPUT_SIZE,
    WRONG_OUTPUT_SIZE
};

inline const std::map<CompileError, const char*> compile_error_desc {
    { CompileError::JSON_NOT_FOUND,    "JSON файл с описание сети не найден." },
    { CompileError::WEIGHTS_NOT_FOUND, "Файл с весами не найден." },
    { CompileError::WRONG_WEIGHTS_FORMAT, "Файл с весами имеет формат не соответствующий пайплайну компиляции." },
    { CompileError::WRONG_CATALOG_NAME,   "Название каталога с программой имеет неверный формат." },
    { CompileError::WRONG_PADDINGS_FORMAT, "Неверный формат паддингов." },
    { CompileError::WRONG_INPUT_SIZE, "Неверный формат размеров входного тензора." },
    { CompileError::WRONG_OUTPUT_SIZE, "Неверный формат размеров выходного тензора." }
};

#endif // COMPILE_ERRORS_H