#ifndef SETTINGSBUFFER_H
#define SETTINGSBUFFER_H

#include "include/settings_config.h"
#include <QVariant>
#include <QSettings>
#include <map>

using settings_group = std::map<QString, QVariant>;
using settings_items = std::map<QString, settings_group>;

class SettingsBuffer
{
public:
    SettingsBuffer();
    ~SettingsBuffer();

    void beginGroup(const QString& group);
    QString group();
    void endGroup();

    void setValue(const QString& key, QVariant value);
    QVariant value(const QString& key);
    QVariant value(const QString& key, QVariant default_value);

    void sync();

private:
    QSettings* settings;
    settings_items groups;
    QString current_group;
};

#endif // SETTINGSBUFFER_H
