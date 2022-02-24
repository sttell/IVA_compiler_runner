#ifndef _INCLUDE_MODULES_PICKLECONVERTERMODULE_H_
#define _INCLUDE_MODULES_PICKLECONVERTERMODULE_H_

#include <string>
#include <exception>
#include <boost/filesystem/operations.hpp>
#include <boost/process.hpp>
#include <fstream>
#include "../module.h"
#include "../settings/pickleConverterSettings.h"

#define PYTHON_INTERPRETATOR_CMD "python"
#define PYTHON_VERSION "3"
#define PICKLE_CONVERTER_SCRIPT "converter.py"
#define PICKLE_CONVERTER_DIR "src/modules/pickle_converter/"
#define INPUT_ARG_NAME "input_path="
#define OUTPUT_ARG_NAME "output_path="
#define RECONSTRUCT_ARG_NAME "reconstruct_pickle_path="
#define THROW_DESC "Pickle converter module error. "
#define ERROR_BUFFER "logs/pickle_converter_stderr.log"


/* Конвертер из формата pickle в формат bin
*  Инициализируется настройками. Встроен модуль проверки корректности
*  входящих настроек. Проверяется наличие директорий и входных файлов.
*  Запуск производится единственным методом runProcess который возвращает
*  код выхода работы модуля.
*
*  Конвертация осуществляется с помощью скрипта src/modules/pickle_converter/converter.py
*  Передача аргументов осуществляется запуском формированием соответствующей команды и запуском
*  процесса.
*/
class PickleConverterModule : public Module
{
public:
    // Конструктор инициализирует настройки
    explicit PickleConverterModule(const PickleConverterSettings& settings) : 
        settings(settings){};

    // Базовый деструктор
    ~PickleConverterModule(){};

    // Метод запуска конвертации
    exit_module_status runProcess();

protected:
    // Проверка корректности настроек
    void checkSettingsCorrectness() const;

    std::string throw_desc = THROW_DESC;

private:
    // Закрытый конструктор копирования
    PickleConverterModule& operator=(PickleConverterModule&) {return *this;};
    // Настройки модуля
    PickleConverterSettings settings;

    // Добавление аргументов к команде запуска
    void addArguments(std::string& command) const;

    // Формирование команды запуска
    std::string formCommand() const;
};

#endif // _INCLUDE_MODULES_PICKLECONVERTERMODULE_H_