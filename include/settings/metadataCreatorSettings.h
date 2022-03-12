#ifndef _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_

#include <string>
#include "../path.h"
#include "../mapSize.h"
#include "../deviceTypes.h"

#include <cinttypes>

struct Paddings {
    Paddings() : left(0), right(0), down(0), up(0) { };
    Paddings(uint8_t l, uint8_t r, uint8_t d, uint8_t u) : 
        left(l), right(r), down(d), up(u) { };
    
    uint8_t left;
    uint8_t right;
    uint8_t down;
    uint8_t up;   
};

// Структура для хранения настроек модуля File Checker Module
struct MetadataCreatorSettings
{
    MetadataCreatorSettings() : 
        paddings_in(0, 0, 0, 0), paddings_out(0, 0, 0, 0),
        input_map(), output_map(),
        compiler_dir(PathType::Directory),
        device_type(Device::MOBILE),
        out_log_path(PathType::File),
        stderr_log_path(PathType::File) {};
    
    // Паддинги для входной и выходной карт признаков
    Paddings paddings_in;
    Paddings paddings_out;

    // Размеры для входной и выходной карт признаков
    MapSize input_map;
    MapSize output_map;

    // Директория компилятора
    Path compiler_dir;

    // Тип устройства TPU
    Device device_type;

    // Путь к логу работы модуля
    Path out_log_path;

    // Путь к логу ошибок
    Path stderr_log_path;
};

#endif // _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_