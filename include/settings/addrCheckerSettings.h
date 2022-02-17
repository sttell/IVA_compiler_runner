#ifndef _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_

#include <string>
#include "../path.h"

// Структура для хранения настроек модуля Address Checker Module
struct AddrCheckerSettings
{

AddrCheckerSettings() : log_path(PathType::File),
                        json_path(PathType::File),
                        out_log_path(PathType::File) {};

// Путь к логу pickle reader модуля
Path log_path;

// Путь к JSON с описанием сети в формате hpm_scheduler
Path json_path;

// Путь к output log для модуля Address Checker
Path out_log_path;

};

#endif // _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_