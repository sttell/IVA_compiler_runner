#ifndef _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_

#include "../deviceTypes.h"
#include "../mapSize.h"
#include <string>

// Структура для хранения настроек модуля Compile Runner Module
struct CompileRunnerSettings
{
    // Количество ядер используемых при сборке программы
    int make_n_jobs;

    // Размеры входной карты признаков
    MapSize input;

    // Размеры выходной карты признаков
    MapSize output;

    // Тип устройства
    Device current_device;

    // Путь к выходному файлу компиляции
    std::string output_tpu_data_path;

    // Путь к файлу с логом работы модуля
    std::string out_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_