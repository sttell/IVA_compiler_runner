#ifndef SETTINGSBUFFER_H
#define SETTINGSBUFFER_H

/**
 * @file settingsbuffer.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Описание класса Settings Buffer.
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

// Qt includes
#include <QVariant>
#include <QString>
#include <QSettings>

// STL includes
#include <map>

/**
 * @brief группа с настройками.
 * @details Группы кнастроек содержат таблицу с настройками, где 
 * Ключ - QString ( Group Name ), Value - QVariant ( value )
 */
using settings_group = std::map<QString, QVariant>;

/**
 * @brief Тип общей таблицы с настройками.
 * @details Представляет собой объединение групп настроек.
 */
using settings_items = std::map<QString, settings_group>;


/**
 * @brief Буффер с настройками.
 * @details Предпологается использование одного буффера в главном окне.
 * Рекомендуется использовать один Settings Buffer на один файл.
 * Иначе возникнет неопределенное поведение.
 * 
 * Файл с настройками инициализируется в конструкторе объекта,
 * синхронизируется в деструкторе.
 * 
 * Буффер является более высокоуровневой абстракцией и API к 
 * QSettings.
 */
class SettingsBuffer
{

public:
    
    /* 
     * ----------------------------------------------------------------------------
     *                         Конструкторы и деструктор.
     * ----------------------------------------------------------------------------
     */

    /**
     * @brief Construct a new Settings Buffer object
     * @details Инициализирует настройки по умолчанию в глобальный файл указанный
     * в header'e include/settings_config.h
     */
    SettingsBuffer();
    
    /**
     * @brief Construct a new Settings Buffer object
     * @details Инициализирует настройки в переданном файле.
     * @param path_to_settings_file - Путь к файлу для сохранения настроек
     * @param format - Формат файла
     */
    SettingsBuffer(const QString& path_to_settings_file, QSettings::Format format);
    
    /**
     * @brief Destroy the Settings Buffer object
     * @details Синхронизирует настройки, сохраняет их и высвобождает ресурсы.
     */
    ~SettingsBuffer();

    
    /* 
     * ----------------------------------------------------------------------------
     *                             Public методы.
     * ----------------------------------------------------------------------------
     */

    
    /**
     * @brief Вход в группу настроек
     * @param group - имя группы
     */
    void beginGroup(const QString& group);
    
    /**
     * @brief Выдать текущую группу настроек
     * 
     * @return QString - имя группы настроек. Пустая строка, если текущей группы нет.
     */
    QString group() const;
    
    /**
     * @brief Закрытие текущей группы настроек, если она открыта
     */
    void endGroup();


    /**
     * @brief Установка нового значения ключу в открытой группе настроек
     * @details Перед обращением рекомендуется вызвать открытие группы.
     * В иных случаях не гарантируется корректное поведение.
     * 
     * @param key   - Имя параметра 
     * @param value - Значение параметра
     */
    void setValue(const QString& key, QVariant value);
    
    /**
     * @brief Выдать значение по ключу
     * @details Перед обращением рекомендуется вызвать открытие группы.
     * В иных случаях не гарантируется корректное поведение.
     * 
     * @param key - ключ, по которому хранится значение
     * @return QVariant - значение, хранящееся по ключу.
     */
    QVariant value(const QString& key);
    
    /**
     * @brief Выдать значение по ключу, либо default значение
     * 
     * @param key - ключ, по которому хранится значение
     * @param default_value - default значение
     * @return QVariant - значение, хранящееся по ключу, либо переданное базовое значение.
     */
    QVariant value(const QString& key, QVariant default_value);

    /**
     * @brief Синхронизация файла с текущими настройками.
     * @details Вызывает синхронизацию QSettings для сохранения текущих настроек в файл.
     */
    void sync();

private:

    /* 
     * ----------------------------------------------------------------------------
     *                Удаленные и заблокированные функции.
     * ----------------------------------------------------------------------------
     */

    /**
     * @brief Copy constructor Settings Buffer object (closed)
     */
    SettingsBuffer(SettingsBuffer&)  {};

    /**
     * @brief Move constructor Settings Buffer object (closed)
     */
    SettingsBuffer(SettingsBuffer&&) {};

    /**
     * @brief Copy operator Settings Buffer object (deleted)
     */
    void operator=(SettingsBuffer&)=delete;

    /* 
     * ----------------------------------------------------------------------------
     *                             Поля и члены-данные.
     * ----------------------------------------------------------------------------
     */

    /**
     * @brief Объект сохраняющий в себе настройки. База для настроек.
     */
    QSettings* settings;

    /**
     * @brief Текущая таблица с настройками, которая хранит в себе Real-Time
     * состояния настроек.
     */
    settings_items groups;

    /**
     * @brief Имя текущей группы настроек
     */
    QString current_group;


};

#endif // SETTINGSBUFFER_H
