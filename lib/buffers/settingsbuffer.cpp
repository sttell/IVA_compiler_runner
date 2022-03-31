#include "settingsbuffer.h"
#include <iostream>
// Конструктор буффера настроек. Читает ini файл с настройками
SettingsBuffer::SettingsBuffer() :
    settings(new QSettings(SETTINGS_CONFIGURATION_PATH, SETTINGS_CONFIGURATION_FORMAT)),
    current_group() {};

// Деструктор сохраняет все настройки в ini файл
SettingsBuffer::~SettingsBuffer() {
    // Выходим из группы
    if (!current_group.isEmpty()) {
        settings->endGroup();
    }
    // Проходим по всем существующим группам настроек и вносим изменения в QSettings
    for (const auto& [group_name, settings_group] : groups) {
        settings->beginGroup(group_name);
        for (const auto& [key, value] : settings_group) {
            settings->setValue(key, value);
        }
        settings->endGroup();

    }
    // синхронизируем настройки и освобождаем память
    settings->sync();
    delete settings;
};

// Вход в группу настроек
void SettingsBuffer::beginGroup(const QString& group) {
    // текущая группа обновляется
    current_group = group;
    settings->beginGroup(group);

    // Если буффер не содержит такой группы, то она инициализируется из QSettings
    if (!groups.contains(current_group)) {
        settings_group new_group;
        for (const auto& key : settings->allKeys()) {
            new_group[key] = settings->value(key);
        }
        groups[current_group] = new_group;
    }
};

// выдача текущей группы
QString SettingsBuffer::group() {
    return current_group;
};

// закрытие текущей группы
void SettingsBuffer::endGroup() {
    if (current_group.isEmpty()) return;

    current_group = "";
    settings->endGroup();
};

// Установка значения
void SettingsBuffer::setValue(const QString& key, QVariant value) {
    groups[current_group][key] = value;
};

// выдача значения по ключу
QVariant SettingsBuffer::value(const QString& key) {
    if (!groups[current_group].contains(key))
        groups[current_group][key] = settings->value(key);
    return groups[current_group][key];
};

// выдача значения по ключу или стандартное значение
QVariant SettingsBuffer::value(const QString& key, QVariant default_value) {
    if (!groups[current_group].contains(key))
        groups[current_group][key] = settings->value(key, default_value);
    return groups[current_group][key];
}

void SettingsBuffer::sync() {
    // Выходим из группы
    if (!current_group.isEmpty()) {
        settings->endGroup();
    }
    // Проходим по всем существующим группам настроек и вносим изменения в QSettings
    for (const auto& [group_name, settings_group] : groups) {
        settings->beginGroup(group_name);
        for (const auto& [key, value] : settings_group) {
            settings->setValue(key, value);
        }
        settings->endGroup();

    }
    // синхронизируем настройки
    settings->sync();
}
