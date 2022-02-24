#ifndef _INCLUDE_TIME_TIMER_H_
#define _INCLUDE_TIME_TIMER_H_

#include <chrono>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#define TIMER_THROW_DESC "Timer error. "

namespace sc = std::chrono;

// Константы используемые при конвертации миллисекунд в другие единицы
namespace _TimeConvertConstants
{
const uint64_t MS_TO_SEC_RESOLUTION  = 1000;
const uint64_t MS_TO_MIN_RESOLUTION  = 60*1000;
const uint64_t MS_TO_HOUR_RESOLUTION = 60*60*1000;
const uint64_t MS_TO_MS_RESOLUTION   = 1;

const uint64_t MS_MAX_VALUE   = 1000;
const uint64_t SEC_MAX_VALUE  = 60;
const uint64_t MIN_MAX_VALUE  = 60;
const uint64_t HOUR_MAX_VALUE = 24;
} // namespace _TimeConvertConstants


/* Класс Timer позволяет измерять время между двумя точками
* и конвертировать его в удобный строковый формат.
*
*   Getter методы недоступны до момента первого замера времени.
* В случае попытки обращения к ним без проведенного замера генерируется
* исключение std::runtime_error
*/
class Timer {
public:
    // Базовый конструктор
    Timer();
    // Базовый деструктор
    ~Timer();
    
    // Начало замера времени
    void start();
    // Конец замера времени
    void end();

    // Возвращает количество часов пройденных во время последнего измерения
    time_t getHours() const;
    // Возвращает количество минут пройденных во время последнего измерения
    time_t getMinutes() const;
    // Возвращает количество секунд пройденных во время последнего измерения
    time_t getSeconds() const;
    // Возвращает количество миллисекунд пройденных во время последнего измерения
    time_t getMilliseconds() const;

    // Возвращает время в удобном строковом формате. По умолчанию: "MM:SS:MS".
    std::string getStringFormat(std::string format="MM:SS:MS") const;

private:
    Timer& operator=(Timer&)=delete;//+
    
    // Возвращает количество единиц времени определенного разрешения в замере
    // + производит проверку на возможность выдачи результата.
    time_t calcTimeWithVerify(uint64_t resolution, uint64_t max_value) const;
    
    // Проверка возможности выдачи результата
    void checkMeasurement() const;
    
    // Флаг окончания замера. Влияет на возможность выдачи результата
    bool ended;

    // Точка времени начала замера
    sc::_V2::system_clock::time_point start_time;
    // Точка времени конца замера
    sc::_V2::system_clock::time_point end_time;
    // Разница полученная в результате замера
    sc::duration<double, std::milli> time_measurement;
};

#endif //_INCLUDE_TIME_TIMER_H_