#ifndef REMOTE_AUTH_DIALOG_H
#define REMOTE_AUTH_DIALOG_H

#include "remote_auth_dialog_ui.h"
#include <QDialog>
#include <QSettings>
#include "lib/buffers/settingsbuffer.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class RemoteAuthDialog; }
QT_END_NAMESPACE

struct RemoteConnectionDesc
{
    QString host_ip;
    QString username;
    QString password;
};

/*
 * CompilerSettingsDialog - форма для изменения настроек компиляции
 * программ. Инициализирует настройки ПО для процесса компиляции
 */
class RemoteAuthDialog : public QDialog
{
    Q_OBJECT

public:
    // Конструктор
    RemoteAuthDialog(QWidget *parent = nullptr, SettingsBuffer* parent_settings=nullptr, RemoteConnectionDesc* output=nullptr);
    // Деструктор
    ~RemoteAuthDialog();

    // Слоты для UI
private slots:
    void on_CancelButton_clicked();
    void on_ApplyButton_clicked();

private:

    void initUiStates();
    void saveUiStates();

    // UI
    Ui::RemoteAuthDialog *ui;

    // Settings
    SettingsBuffer *settings;

    // Output Buffer
    RemoteConnectionDesc* out_buffer;

};

#endif // REMOTE_AUTH_DIALOG_H
