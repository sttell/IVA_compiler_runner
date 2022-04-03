#ifndef WRONG_FMT_CAPTURES_H
#define WRONG_FMT_CAPTURES_H

/**
 * @file wrong_fmt_captures.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Содержит текста для индикаторов неверного формата
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

// Qt includes
#include <QString>


/**
 * @brief Пространство имен хранящее константы с текстом для индикаторов неверного
 * формата ввода.
 */
namespace WRONG_FMT_TEXT 
{

// Общий текст для неверного формата
inline const QString bad_format = "Неверный формат";

// Текст выставляемый при наличии нуля там, где его быть не должно
inline const QString zero_value = "Тут не должно быть нуля";

// Неверный формат имени директории. Содержит недопустимые символы
inline const QString bad_dir_format = "Название директории не должно содержать символов *|:\"<>?/\\";

// Неверный формат имени директории (сокращенный текст). Содержит недопустимые символы
inline const QString bad_dir_format_short = "Название не должно содержать *|:\"<>?/\\";

// Указанной директории не существует
inline const QString directory_not_exist = "Директории по указанному пути не существует";

// Указанного файла не существует
inline const QString file_not_exist = "Файла по указанному пути не существует";

// Формат не *.json, хотя ожидался он
inline const QString not_json_fmt = "Указанный файл должен быть формата *.json";

// Формат не *.pickle, хотя ожидался он
inline const QString not_pickle_fmt = "Ожидается файл формата *.pickle";

// Формат не *.bin, хотя ожидался он
inline const QString not_bin_fmt = "Ожидается файл формата *.bin";

// Формат не *.zip, хотя ожидался он
inline const QString not_zip_fmt = "Название архива должно иметь .zip формат";

} // namespace WRONG_FMT_TEXT


#endif // WRONG_FMT_CAPTURES_H
