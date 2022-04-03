/**
 * @file settingsbuffer.cpp
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Реализация Settings Buffer
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

// Include header file
#include "settingsbuffer.h"

// Include settings configuration
#include "include/settings_config.h"

// STL includes
#include <iostream>


/* 
* ----------------------------------------------------------------------------
*                         Конструкторы и деструктор.
* ----------------------------------------------------------------------------
*/

/**
 * @brief Construct a new Settings Buffer object
 * @details Инициализирует настройки по умолчанию в глобальный файл указанный
 * в header'e include/settings_config.h
 * Начальная группа - пустая.
 */
SettingsBuffer::SettingsBuffer() :
    settings(new QSettings(SETTINGS_CONFIGURATION_PATH, SETTINGS_CONFIGURATION_FORMAT)),
    current_group("") 
{

// *** EMPTY ***

};

/**
 * @brief Construct a new Settings Buffer object
 * @details Инициализирует настройки в переданном файле. Группа по умолчанию - пустая.
 * @param path_to_settings_file - Путь к файлу для сохранения настроек
 * @param format - Формат файла
 */
SettingsBuffer::SettingsBuffer(const QString& path_to_settings_file, QSettings::Format format) :
    settings(new QSettings(path_to_settings_file, format)),
    current_group("")
{

// *** EMPTY ***

}


/**
 * @brief Destroy the Settings Buffer object
 * @details Синхронизирует настройки, сохраняет их и высвобождает ресурсы.
 */
SettingsBuffer::~SettingsBuffer() 
{

    // Выходим из группы если она не пустая
    if (!current_group.isEmpty()) settings->endGroup();
    
    // Проходим по всем существующим группам настроек и вносим изменения в QSettings
    for (const auto& [group_name, settings_group] : groups) 
    {
    
        settings->beginGroup(group_name);
    
        for (const auto& [key, value] : settings_group)
            settings->setValue(key, value);
    
        settings->endGroup();

    }

    // синхронизируем настройки и освобождаем память
    settings->sync();
    
    // Высвобождаем ресурсы
    delete settings;

};


/* 
* ----------------------------------------------------------------------------
*                             Public методы.
* ----------------------------------------------------------------------------
*/


/**
 * @brief Вход в группу настроек
 * @param group - имя группы
 */
void SettingsBuffer::beginGroup(const QString& group) 
{

    // текущая группа обновляется
    current_group = group;

    settings->beginGroup(group);

    // Если буффер не содержит такой группы, то она инициализируется из QSettings
    if (!groups.count(current_group)) 
    {
    
        settings_group new_group;
    
        for (const auto& key : settings->allKeys())
            new_group[key] = settings->value(key);
        
        groups[current_group] = new_group;
    
    }

};


/**
 * @brief Выдать текущую группу настроек
 * 
 * @return QString - имя группы настроек. Пустая строка, если текущей группы нет.
 */
QString SettingsBuffer::group() const 
{

    return current_group;

};


/**
 * @brief Закрытие текущей группы настроек, если она открыта
 */
void SettingsBuffer::endGroup() 
{
    
    // Если текущая группа и так пуста, то возвращаем
    if (current_group.isEmpty()) return;

    // В иных случаях производим закрытие группы и обнуление текущей.

    current_group = "";

    settings->endGroup();

};

/**
 * @brief Установка нового значения ключу в открытой группе настроек
 * @details Перед обращением рекомендуется вызвать открытие группы.
 * В иных случаях не гарантируется корректное поведение.
 * 
 * @param key   - Имя параметра 
 * @param value - Значение параметра
 */
void SettingsBuffer::setValue(const QString& key, QVariant value) 
{

    groups[current_group][key] = value;

};

/**
 * @brief Выдать значение по ключу
 * @details Перед обращением рекомендуется вызвать открытие группы.
 * В иных случаях не гарантируется корректное поведение.
 * 
 * @param key - ключ, по которому хранится значение
 * @return QVariant - значение, хранящееся по ключу.
 */
QVariant SettingsBuffer::value(const QString& key) 
{

    // Если текущая группа отсутствует в группах, то инициализируем ее
    if (!groups[current_group].count(key))
        groups[current_group][key] = settings->value(key);

    return groups[current_group][key];

};


/**
 * @brief Выдать значение по ключу, либо default значение
 * 
 * @param key - ключ, по которому хранится значение
 * @param default_value - default значение
 * @return QVariant - значение, хранящееся по ключу, либо переданное базовое значение.
 */
QVariant SettingsBuffer::value(const QString& key, QVariant default_value) 
{
    
    // Если текущего ключа нет в группе, то устанавливаем его
    if (!groups[current_group].count(key))
        groups[current_group][key] = settings->value(key, default_value);

    return groups[current_group][key];

}


/**
 * @brief Синхронизация файла с текущими настройками.
 * @details Вызывает синхронизацию QSettings для сохранения текущих настроек в файл.
 */
void SettingsBuffer::sync() 
{

    // Выходим из группы
    if (!current_group.isEmpty())
        settings->endGroup();
    
    // Проходим по всем существующим группам настроек и вносим изменения в QSettings
    for (const auto& [group_name, settings_group] : groups) 
    {
    
        settings->beginGroup(group_name);

        for (const auto& [key, value] : settings_group)
            settings->setValue(key, value);
        
        settings->endGroup();

    }

    // синхронизируем настройки
    settings->sync();

}
