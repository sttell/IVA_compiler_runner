#ifndef _INCLUDE_MODULE_H_
#define _INCLUDE_MODULE_H_

#include "moduleExitStatus.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "path.h"
#include <fstream>
#include <iostream>

// Базовый класс Module содержащий обобщенные методы и интерфес всех модулей
class Module {
public:
    Module(StatusBufferCache* status_bar, std::string _throw_desc) : throw_desc(_throw_desc), log(status_bar) {};
    virtual ~Module() {log = nullptr; delete log;};

    // Интерфейс всех классов принадлежащих Module
    virtual exit_module_status runProcess() = 0;
protected:
    // Хэдер описания исключения для каждого модуля
    std::string throw_desc;
    // Лог
    StatusBufferCache* log;

    // Проверка корректности настроек
    virtual void checkSettingsCorrectness() const = 0;
    // Проверка наличия файла
    virtual void checkFileExist(const Path&) const;
    // Проверка наличия директории указанной в пути
    virtual void checkDirExist(const Path&) const;
};

#endif // _INCLUDE_MODULE_H_
