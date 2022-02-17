#ifndef _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_

#include "../deviceTypes.h"
#include "../mapSize.h"
#include "../path.h"
#include <string>

// Структура для хранения настроек модуля Compile Runner Module
struct CompileRunnerSettings
{
    CompileRunnerSettings() : make_n_jobs(1),
                              output_tpu_data_path(PathType::File),
                              out_log_path(PathType::File) {};
    // Количество ядер используемых при сборке программы
    int make_n_jobs;

    // Размеры входной карты признаков
    MapSize input;

    // Размеры выходной карты признаков
    MapSize output;

    // Тип устройства
    Device current_device;

    // Путь к выходному файлу компиляции
    Path output_tpu_data_path;

    // Путь к файлу с логом работы модуля
    Path out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_