#ifndef _INCLUDE_COMPILESTATUS_H_
#define _INCLUDE_COMPILESTATUS_H_

#include "moduleExitStatus.h"
#include "aliases.h"

// Структура хранящая текущий статус компиляции
struct CompileStatus
{
// Запущенный модуль
module_t runned_module;
// Статус работы и завершения
exit_module_status status;
};

#endif // _INCLUDE_COMPILESTATUS_H_