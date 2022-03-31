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
                              num_starts(2),
                              path_to_json(PathType::File),
                              path_to_weights(PathType::File),
                              compiler_dir(PathType::Directory) {};
    // Количество ядер используемых при сборке программы
    int make_n_jobs;
    // Количество запусков компиляции
    int num_starts;

    // Размеры входной карты признаков
    MapSize input;

    // Размеры выходной карты признаков
    MapSize output;

    // Тип устройства
    Device current_device;

    // Путь к JSON описанию сети
    Path path_to_json;

    // Путь к weights.bin файлу
    Path path_to_weights;

    // Путь к выходному файлу компиляции
    Path compiler_dir;
};

#endif // _LIB_INCLDUE_SETTINGS_COMPILERRUNNERSETTINGS_H_
