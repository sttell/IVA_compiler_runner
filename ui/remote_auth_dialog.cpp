#include "remote_auth_dialog.h"
#include "include/settings_config.h"

// Конструктор принимает на вход родительский виджет + объект
// Содержащий настройки приложения.
RemoteAuthDialog::RemoteAuthDialog(QWidget *parent, SettingsBuffer* parent_settings, RemoteConnectionDesc* output)
    : QDialog(parent)
    , ui(new Ui::RemoteAuthDialog)
    , settings(parent_settings)
    , out_buffer(output)
{

    // Инициализация UI
    ui->setupUi(this);

    initUiStates();

}

RemoteAuthDialog::~RemoteAuthDialog() {



    settings = nullptr;
    out_buffer = nullptr;

    delete settings;
    delete out_buffer;
}

void RemoteAuthDialog::initUiStates() {

    settings->beginGroup(REMOTE_AUTH_GROUP);
    bool forgot_host_check = settings->value(ui->ForgotHostCheckBox->objectName(), false).toBool();
    bool forgot_user_check = settings->value(ui->ForgotMeCheckBox->objectName(), false).toBool();

    ui->ForgotHostCheckBox->setChecked(forgot_host_check);
    ui->ForgotMeCheckBox->setChecked(forgot_user_check);

    if (forgot_host_check) {
        QString host_ip = settings->value(ui->HostIPLineEdit->objectName(), "").toString();
        ui->HostIPLineEdit->setText(host_ip);
    }

    if (forgot_user_check) {
        QString name = settings->value(ui->usernameLineEdit->objectName(), "").toString();
        QString pass = settings->value(ui->PasswordLineEdit->objectName(), "").toString();
        ui->usernameLineEdit->setText(name);
        ui->PasswordLineEdit->setText(pass);
    }

    settings->endGroup();

}

void RemoteAuthDialog::saveUiStates() {

    settings->beginGroup(REMOTE_AUTH_GROUP);

    settings->setValue(ui->ForgotHostCheckBox->objectName(),
                       ui->ForgotHostCheckBox->isChecked()
                       );
    settings->setValue(ui->ForgotMeCheckBox->objectName(),
                       ui->ForgotMeCheckBox->isChecked()
                       );

    if (ui->ForgotHostCheckBox->isChecked()) {
        settings->setValue(ui->HostIPLineEdit->objectName(), ui->HostIPLineEdit->text());
    } else {
        settings->setValue(ui->HostIPLineEdit->objectName(), "");
    }

    if (ui->ForgotMeCheckBox->isChecked()) {
        settings->setValue(ui->usernameLineEdit->objectName(), ui->usernameLineEdit->text());
        settings->setValue(ui->PasswordLineEdit->objectName(), ui->PasswordLineEdit->text());
    } else {
        settings->setValue(ui->usernameLineEdit->objectName(), "");
        settings->setValue(ui->PasswordLineEdit->objectName(), "");
    }
    settings->sync();
    settings->endGroup();

}


void RemoteAuthDialog::on_CancelButton_clicked() {
    this->reject();
}

void RemoteAuthDialog::on_ApplyButton_clicked() {

    saveUiStates();

    out_buffer->host_ip = ui->HostIPLineEdit->text();
    out_buffer->username = ui->usernameLineEdit->text();
    out_buffer->password = ui->PasswordLineEdit->text();

    this->accept();
}
