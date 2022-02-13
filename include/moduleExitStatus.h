#ifndef _INCLUDE_MODULEEXITSTATUS_H_
#define _INCLUDE_MODULEEXITSTATUS_H_

#include <cinttypes>
#include <aliases.h>

// Статус выхода из модуля
namespace ModuleExitStatus
{
// Успешное завершение
const exit_module_status SUCCESS   = 0b00000000;

// Неудачное завершение
const exit_module_status FAILTURE  = 0b00000001;

// Ожидание завершения. Возможно получение при мультипоточном режиме
const exit_module_status WAIT      = 0b00000010;

// Завершение с исключением
const exit_module_status EXCEPTION = 0b00000100;

// Не начато
const exit_module_status NORUNNED  = 0b00001000;
}

#endif // _INCLUDE_MODULEEXITSTATUS_H_
