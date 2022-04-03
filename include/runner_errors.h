/**
 * @file runner_errors.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Определение возможных ошибок при запуске программ
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef RUNNER_ERRORS_H
#define RUNNER_ERRORS_H

// STL includes 
#include <map>

/**
 * @brief Перечисление возможных ошибок запуска программы
 * @details Крайне желательно добавлять ко всем ошибкам
 * их текстовое описание в таблицу runner_error_desc.
 * В ином случае высока вероятность возникновения исключения
 * при использовании ошибки в связке с буффером статус баров.
 */
enum class RunnerError
{

    PROGRAM_DIR_NOT_EXIT,              // Не существует директории с программой
    WRONG_GENERATED_TENSOR_FORMAT,     // Неверный формат размера генерируемого тензора
    WRONG_GENERATED_TENSOR_SAVE_PATH,  // Неверный путь для сохранения генерируемого тензора

};


/**
 * @brief Глобальная переменная, которая хранит текстовые описания ошибок.
 */
inline const std::map<RunnerError, const char*> runner_error_desc {

    { RunnerError::PROGRAM_DIR_NOT_EXIT,             "Проверьте путь к директории с программой." },
    { RunnerError::WRONG_GENERATED_TENSOR_FORMAT,    "Проверьте размер генерируемого тензора." },
    { RunnerError::WRONG_GENERATED_TENSOR_SAVE_PATH, "Проверьте путь для сохранения генерируемого тензора." },

};

#endif // RUNNER_ERRORS_H