#ifndef _LIB_INCLDUE_SETTINGS_GLOBALSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_GLOBALSETTINGS_H_

#include "compilerRunnerSettings.h"
#include "fileCheckerSettings.h"
#include "jsonConverterSettings.h"
#include "pickleConverterSettings.h"
#include "programComparatorSettings.h"
#include "programRunnerSettings.h"
#include "addrCheckerSettings.h"

// Структура для хранения глобальных настроек программы
struct GlobalSettings {
    // Настройки конвертации JSON файла
    JsonConverterSettings json_converter;

    // Настройки конвертации pickle файла с весами
    PickleConverterSettings pickle_converter;
    
    // Настройки модуля проверки наличия файлов
    FileCheckerSettings file_checker;
    
    // Настройки модуля проверки адресов весов
    AddrCheckerSettings addr_checker;

    // Настройки модуля компиляции
    CompileRunnerSettings compiler_runner;
    
    // Настройки модуля сборки программы
    ProgramComparatorSettings program_comparator;
    
    // Настройки модуля запуска программы
    ProgramRunnerSettings program_runner;

};

#endif // _LIB_INCLDUE_SETTINGS_GLOBALSETTINGS_H_