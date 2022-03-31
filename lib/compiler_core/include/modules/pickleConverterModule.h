#ifndef _INCLUDE_MODULES_PICKLECONVERTERMODULE_H_
#define _INCLUDE_MODULES_PICKLECONVERTERMODULE_H_

#include <string>
#include <exception>
#include <boost/filesystem/operations.hpp>
#include <boost/process.hpp>
#include <fstream>
#include "../module.h"
#include "../settings/globalSettings.h"

#define PYTHON_INTERPRETATOR_CMD "python"
#define PYTHON_VERSION "3"
#define PICKLE_CONVERTER_SCRIPT "converter.py"
#define PICKLE_CONVERTER_DIR "/src/pickle_converter_scripts/"
#define INPUT_ARG_NAME "input_path="
#define OUTPUT_ARG_NAME "output_path="
#define RECONSTRUCT_ARG_NAME "reconstruct_pickle_path="
#define PICKLE_CONVERTER_THROW_DESC "Pickle converter module error. "


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
    explicit PickleConverterModule(const GlobalSettings& _settings, StatusBufferCache* status_bar) :
        Module(status_bar, PICKLE_CONVERTER_THROW_DESC), settings(_settings.pickle_converter){};
    ~PickleConverterModule() {log=nullptr; delete log;};

    // Метод запуска конвертации
    exit_module_status runProcess();

protected:
    // Проверка корректности настроек
    void checkSettingsCorrectness() const;

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
