#ifndef _INCLUDE_MODULE_H_
#define _INCLUDE_MODULE_H_

#include "moduleExitStatus.h"
#include "path.h"

// Базовый класс Module содержащий обобщенные методы и интерфес всех модулей
class Module {
public:
    // Интерфейс всех классов принадлежащих Module
    virtual exit_module_status runProcess() = 0;
protected:
    // Хэдер описания исключения для каждого модуля
    std::string throw_desc;
    // Проверка корректности настроек
    virtual void checkSettingsCorrectness() const = 0;
    // Проверка наличия файла
    virtual void checkFileExist(const Path&) const;
    // Проверка наличия директории указанной в пути
    virtual void checkDirExist(const Path&) const;
    // Очищение кэша находящегося в std err log
    virtual void clearStdErrCache(const Path&) const;
};

#endif // _INCLUDE_MODULE_H_