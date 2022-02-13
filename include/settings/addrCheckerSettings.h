#ifndef _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_
#define _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_

#include <string>

// Структура для хранения настроек модуля Address Checker Module
struct AddrCheckerSettings
{

// Путь к логу pickle reader модуля
std::string log_path;

// Путь к JSON с описанием сети в формате hpm_scheduler
std::string json_path;

// Путь к output log для модуля Address Checker
std::string out_log_path;

};

#endif // _LIB_INCLDUE_SETTINGS_ADDRCHECKERSETTINGS_H_