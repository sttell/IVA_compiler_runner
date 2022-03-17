#ifndef _INCLUDE_MODULES_H_
#define _INCLUDE_MODULES_H_

#include "aliases.h"

// Битовые позиции для флагов модуля.
// используется приемущественно для выставления Pipeline
namespace Modules
{
// Базовое значение. Все модули выключены
const module_t NoModules         = 0b00000000;

// Далее название каждой константы соответствует одноименному модулю
const module_t JsonConverter     = 0b00000001;
const module_t PickleConverter   = 0b00000010;
const module_t AddrChecker       = 0b00000100;
const module_t CompileRunner     = 0b00001000;
const module_t MetadataCreator   = 0b00010000;
const module_t ProgramComparator = 0b00100000;
const module_t ProgramRunner     = 0b01000000;
}

#endif // _INCLUDE_MODULES_H_