/**
 * @file compile_errors.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Файл с определением возможных ошибок компиляции и их текстовым описанием.
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef COMPILE_ERRORS_H
#define COMPILE_ERRORS_H

// STL include
#include <map>

/**
 * @brief Перечисление возможных ошибок компиляции
 * @details Крайне желательно добавлять ко всем ошибкам
 * их текстовое описание в таблицу compile_error_desc.
 * В ином случае высока вероятность возникновения исключения
 * при использовании ошибки в связке с буффером статус баров.
 */
enum class CompileError
{

    JSON_NOT_FOUND,             // Не найден файл с JSON описанием сети
    WEIGHTS_NOT_FOUND,          // Не найден файл с весами сети
    WRONG_WEIGHTS_FORMAT,       // Формат весов не соответствует пайплайну компиляции
    WRONG_CATALOG_NAME,         // Недопустимое имя каталога с программой
    WRONG_PADDINGS_FORMAT,      // Недопустимый формат паддингов
    WRONG_INPUT_SIZE,           // Недопустимый формат размеров входного тензора
    WRONG_OUTPUT_SIZE,          // Недопустимый формат размеров выхоного тензора
    EMPTY_JSON_FILE,
    EMPTY_PICKLE_LOG,
};


/**
 * @brief Глобальная переменная, которая хранит текстовые описания ошибок.
 */
inline const std::map<CompileError, const char*> compile_error_desc {

    { CompileError::JSON_NOT_FOUND,        "JSON файл с описание сети не найден." },
    { CompileError::WEIGHTS_NOT_FOUND,     "Файл с весами не найден." },
    { CompileError::WRONG_WEIGHTS_FORMAT,  "Файл с весами имеет формат не соответствующий пайплайну компиляции." },
    { CompileError::WRONG_CATALOG_NAME,    "Название каталога с программой имеет неверный формат." },
    { CompileError::WRONG_PADDINGS_FORMAT, "Неверный формат паддингов." },
    { CompileError::WRONG_INPUT_SIZE,      "Неверный формат размеров входного тензора." },
    { CompileError::WRONG_OUTPUT_SIZE,     "Неверный формат размеров выходного тензора." },
    { CompileError::EMPTY_JSON_FILE,       "Файл с JSON описанием сети пуст." },
    { CompileError::EMPTY_PICKLE_LOG,      "Файл лога конвертации Pickle пуст." }

};

#endif // COMPILE_ERRORS_H