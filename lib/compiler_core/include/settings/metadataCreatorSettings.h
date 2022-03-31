#ifndef _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_

#include <string>
#include "../path.h"
#include "../mapSize.h"
#include "../deviceTypes.h"

#include <cinttypes>

using axes_padding_t = int16_t;

// Описание паддингов в доль одной оси. Хранит пару с правым и левым значением.
struct AxesPadding {
    AxesPadding() : left(0), right(0) {};
    AxesPadding(uint8_t _left, uint8_t _right) : left(_left), right(_right) {};

    axes_padding_t left;
    axes_padding_t right;
};

// Паддинги тензора. Хранит 4 пары паддингов для тензора изображений
struct Paddings {
    Paddings() {};
    Paddings(axes_padding_t Bl, axes_padding_t Br,
             axes_padding_t Xl, axes_padding_t Xr,
             axes_padding_t Yl, axes_padding_t Yr,
             axes_padding_t Ll, axes_padding_t Lr) : 
             B(Bl, Br), X(Xr, Xl), Y(Yl, Yr), L(Ll, Lr) {};
    
    AxesPadding B;
    AxesPadding X;
    AxesPadding Y;
    AxesPadding L;  
};

// Структура для хранения настроек модуля File Checker Module
struct MetadataCreatorSettings
{
    MetadataCreatorSettings() : 
        paddings_in(), paddings_out(),
        input_map(), output_map(),
        compiler_dir(PathType::Directory),
        device_type(Device::MOBILE),
        ip_version("unknown ip version"),
        api_version("unknown api version") {};
    
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

    // ip & api версии вычислителя
    std::string ip_version;
    std::string api_version;

    // Скейл для входного тензора
    double input_map_scale;

    // Скейл для выходного тензора
    double output_map_scales;
};

#endif // _LIB_INCLDUE_SETTINGS_METADATACREATORSETTINGS_H_
