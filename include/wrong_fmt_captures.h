#ifndef WRONG_FMT_CAPTURES_H
#define WRONG_FMT_CAPTURES_H

#include <QString>

namespace WRONG_FMT_TEXT {

inline const QString bad_format = "Неверный формат";
inline const QString zero_value = "Тут не должно быть нуля";
inline const QString bad_dir_format = "Название директории не должно содержать символов *|:\"<>?/\\";
inline const QString bad_dir_format_short = "Название не должно содержать *|:\"<>?/\\";
inline const QString directory_not_exist = "Директории по указанному пути не существует";
inline const QString file_not_exist = "Файла по указанному пути не существует";
inline const QString not_json_fmt = "Указанный файл должен быть формата *.json";
inline const QString not_pickle_fmt = "Ожидается файл формата *.pickle (см. Пайплайн компиляции)";
inline const QString not_bin_fmt = "Ожидается файл формата *.bin (см. Пайплайн компиляции)";
inline const QString not_zip_fmt = "Название архива должно иметь .zip формат";
}

#endif // WRONG_FMT_CAPTURES_H
