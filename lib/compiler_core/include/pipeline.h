#ifndef _INCLUDE_PIPELINE_H_
#define _INCLUDE_PIPELINE_H_

#include <cinttypes>
#include "aliases.h"
#include "modules.h"
#include <exception>
#include <iostream>
#include <queue>

/* Класс Pipeline - описание пайплайнов. Оперирует описанием модулей
*  в виде битовых флагов. Каждый выставленный бит кодирует запуск
*  соответствующего модуля на этапе компиляции.
*
*  Пример:
*   Предположим флаг запуска модуля закодирован значением 0b1;
*   Тогда вызов setModule(0b1) выставит нужный бит в пайплайне,
*   Который можно проверить методом isModuleExists(0b1) 
*   Или удалить методом deleteModule(0b1).
*
*  По умолчанию есть возможность закодировать 8 модулей. Для изменения количества
*  необходимо сменить тип алиаса module_t в файле aliases.h. Допустимый тип: uintXX_t.
*/
class Pipeline
{
public:
    explicit Pipeline();
    ~Pipeline();

    // Выставления флага запуска модуля
    void setModule(Modules);

    // Проверка на пустоту пайплайна
    bool isEmpty() const;

    // Выдача следующего модуля из очереди
    Modules getNextModule();

    // Оператор копирования
    void operator=(const Pipeline&);

private:
    // Очередь из модулей
    std::queue<Modules> pipeline;

};

#endif // _INCLUDE_PIPELINE_H_
