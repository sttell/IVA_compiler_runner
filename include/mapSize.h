#ifndef _INCLUDE_MAPSIZE_H_
#define _INCLUDE_MAPSIZE_H_

using axis_size_t = int64_t;

// Структура для хранения размеров карты признаков
struct MapSize
{
// Характеристические размеры
axis_size_t B, X, Y, L;
};

#endif // _INCLUDE_MAPSIZE_H_