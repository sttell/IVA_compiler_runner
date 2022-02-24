#include "../include/timer.h"

// Конструктор
Timer::Timer() : ended(false) {};

// Деструктор
Timer::~Timer() {};

// Проверка возможности выдачи результата.
void Timer::checkMeasurement() const {
    // Если замер произведен, то разрешаем дальнейшие действия
    if (ended) return;

    // Иначе генерируется исключение
    std::string err_desc(TIMER_THROW_DESC);
    err_desc += "An attempt to get the execution time, while no time measurements were carried out.";
    throw std::runtime_error(err_desc);
}

// Старт замера. Фиксирует точку начала измерений времени
// и сбрасывает флаг окончания замера
void Timer::start() {
    ended = false;
    start_time = sc::system_clock::now();
}

// Конец замера. Фиксирует точку окончания изменерий времени
// и выставляет флаг окончания замера. Обновляет результат измерений.
void Timer::end() {
    end_time = sc::system_clock::now();
    time_measurement = end_time - start_time;
    ended = true;
}

// Подсчет времени в определенных единицах + проверка возможности получения измерений
// resolution - разрешение единицы времени относительно ms. Например: для секунд - 1000 ms.
// max_value  - максимальное количество единиц получаемого времени
time_t Timer::calcTimeWithVerify(uint64_t resolution, uint64_t max_value) const {
    checkMeasurement();
    return (static_cast<uint64_t>(time_measurement.count()) / resolution) % max_value;
}

// Возвращает количество миллисекунд в последнем замере времени
time_t Timer::getMilliseconds() const {
    return calcTimeWithVerify(_TimeConvertConstants::MS_TO_MS_RESOLUTION, 
                              _TimeConvertConstants::MS_MAX_VALUE);
}

// Возвращает количество секунд в последнем замере времени
time_t Timer::getSeconds() const {
    return calcTimeWithVerify(_TimeConvertConstants::MS_TO_SEC_RESOLUTION, 
                              _TimeConvertConstants::SEC_MAX_VALUE);
}

// Возвращает количество минут в последнем замере времени
time_t Timer::getMinutes() const {
    return calcTimeWithVerify(_TimeConvertConstants::MS_TO_MIN_RESOLUTION, 
                              _TimeConvertConstants::MIN_MAX_VALUE);
}

// Возвращает количество часов в последнем замере времени
time_t Timer::getHours() const {
    return calcTimeWithVerify(_TimeConvertConstants::MS_TO_HOUR_RESOLUTION, 
                              _TimeConvertConstants::HOUR_MAX_VALUE);
}

/* Возвращает строковое описание замера времени в пользовательском формате
*  Возможные идентификаторы в формате:
*   MS - milliseconds 
*   SS - seconds
*   MM - minutes
*   HH - hours
*  Примеры формата: "time: HH-MM-SS-MS", "HH hours MM minutes".
*  По умолчанию: "MM:SS:MS"
*/
std::string Timer::getStringFormat(std::string format) const {
    // При пустой строке возвращается она же
    if (format.empty()) return "";

    // Сбор информации о возможных единицах времени в последнем замере
    std::unordered_map<std::string, time_t> format_to_data;
    format_to_data["MS"] = this->getMilliseconds();
    format_to_data["SS"] = this->getSeconds();
    format_to_data["MM"] = this->getMinutes();
    format_to_data["HH"] = this->getHours();

    // Проходимся по хэш-таблице где ключ - формат времени, значение - количество единиц данного формата
    for (const std::pair<std::string, time_t>& item : format_to_data) {
        // Поиск первого вхождения данного формата времени в формате пользователя
        size_t start_pos = format.find(item.first);

        // Вставка значения вместо идентификатора формата.
        // Вставка продолжается до тех пор, пока все идентификаторы формата не будут заменены на значения
        while(start_pos != std::string::npos) {
            std::string left  = format.substr(0, start_pos);
            std::string right = format.substr(start_pos + item.first.size(), format.size() - 1);
            format = left + std::to_string(item.second) + right;
            start_pos = format.find(item.first);
        }
    }
    // Возврат формата с замененными значениями.
    return format;
}