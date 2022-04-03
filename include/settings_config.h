#ifndef SETTINGS_CONFIG_H
#define SETTINGS_CONFIG_H

/**
 * @file settings_config.h
 * @author Ilya Biro (st.tell@mail.ru)
 * 
 * @brief Описание всех пространств имен связанных с буффером настроек.
 * @details Здесь описаны пути сохранения настроек и формат, указаны имена групп
 * стандартные значения полей настроек и имена параметров глобальной группы.
 * 
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

// Includes
#include <string>
#include <unistd.h>


/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                         Имена групп для настроек разных типов
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/**
 * @brief Имя группы с настройками компиляции (Вариативные настройки).
 */
#define COMPILER_SETTINGS_GROUP "Compiler_Settings"

/**
 * @brief Имя группы с настройками запуска программы (Общие настройки).
 * @details Настройки аунтефикации пользователя хранятся в REMOTE_AUTH_GROUP
 */
#define RUNNER_SETTINGS_GROUP   "Runner_Settings"

/**
 * @brief Имя группы с настройками анализа программ.
 */
#define ANALYSIS_SETTINGS_GROUP "Analysis_Settings"

/**
 * @brief Имя глобальной группы настроек с общими настройками приложения и статическими настройками компиляции.
 */
#define GLOBAL_SETTINGS_GROUP   "Global_Settings"

/**
 * @brief Имя группы настроек с параметрами аунтефикации пользователя на удаленном хосте.
 */
#define REMOTE_AUTH_GROUP       "Remote_Auth_Settings"


/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                         Общие параметры файла с настройками
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/**
 * @brief Директория с настройками ПО.
 */
#define SETTINGS_DIRECTORY_PATH "cfg/"

/**
 * @brief Путь к основному файлу с настройками.
 */
#define SETTINGS_CONFIGURATION_PATH "cfg/settings.ini"

/**
 * @brief Формат сохранения настроек. По умолчанию - *.ini
 */
#define SETTINGS_CONFIGURATION_FORMAT QSettings::IniFormat



/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                             Имена полей с настройками
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


/**
 * @brief Пространство имен хранящее имена глоабльных параметров
 * находящихся в настройках. Принадлежит группе GLOBAL_SETTINGS_GROUP.
 */
namespace GlobalSettingName 
{
    // Bool parameter. Проводилась ли первичная инициализация ПО
    inline const char* isFirstRunInited   = "is_application_inited";

    // String parameter. Название архива с программой на этапе компиляции.
    inline const char* programArchiveName = "ArchiveName";

} // namespace GlobalSettingName

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                         Общие параметры файла с настройками
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/**
 * @brief Пространство имен для внутреннего использования.
 * @details Реализует некоторые функции, которые нужны для составления
 * настроек по умолчанию.
 */
namespace __DefaultSettingsImpl__
{

/**
 * @brief Выдает путь к домашней текущего пользователя
 * 
 * @return const char* Строковое представление пути.
 */
inline const char* get_user_folder() 
{

    std::string user_folder { "/home/" };
    return (user_folder + getlogin()).c_str();    

}

/**
 * @brief Выдает путь для сохранения тензора по умолчанию
 * @details Путь по умолчанию - /home/username/tensor.bin
 * 
 * @return const char* Строковое представление пути.
 */
inline const char* get_tensor_path()
{

    std::string user_folder { get_user_folder() };
    return (user_folder + "/tensor.bin").c_str();

}

} // namespace __DefaultSettingsImpl__


/**
 * @brief Стандартные значения для настроек Compiler Tab
 */
namespace CompilerSettingsDefault 
{

    // Путь к домашней директории пользователя
    inline const char* user_folder = __DefaultSettingsImpl__::get_user_folder();

    // Стандартное строковое представление паддингов
    inline const char* paddings    = "0,0,0,0";

    // Стандартное строковое представление размера тензора
    inline const char* tensor_size = "1,1,1,1";

    // Стандартное строковое представление названия директории с программой
    inline const char* program_dir = "TestProgram";

} // namespace CompilerSettingsDefault


/**
 * @brief Стандартные значения для настроек Runner Tab
 */
namespace RunnerSettingsDefault 
{

    // Путь к домашней директории пользователя
    inline const char* user_folder = __DefaultSettingsImpl__::get_user_folder();

    // Стандартное строковое представление размера тензора
    inline const char* tensor_size = "1,1,1,1";

    // Стандартное строковое представление пути для сохранения тензора
    inline const char* tensor_path = __DefaultSettingsImpl__::get_tensor_path();

} // namespace RunnerSettingsDefault


#endif // SETTINGS_CONFIG_H
