#ifndef _INCLUDE_PIPELINE_H_
#define _INCLUDE_PIPELINE_H_

#include <cinttypes>
#include "aliases.h"
#include "modules.h"
#include <exception>
#include <iostream>

// Константы используемые для класса Pipeline
namespace PipelineConstants
{
// Значение для инициализации пайплайна
const module_t InitPipeline = 0b00000000;
}

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
    void setModule(module_t);

    // Снятие флага для модуля
    void deleteModule(module_t);

    // Проверка флага модуля
    bool isModuleExists(module_t) const;

    // Оператор копирования
    void operator=(const Pipeline&);

private:
    // Поле содержащее все выставленные флаги
    module_t pipeline;

    // Выставить бит соответствующий модулю
    void setModuleBit(const module_t&);
    
    // Получить бит соответствующий модулю
    module_t getModuleBit(const module_t&) const;
    
};

#endif // _INCLUDE_PIPELINE_H_