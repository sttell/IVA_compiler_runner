#include "warning_settings_dialog.h"
#include "warning_settings_dialog_ui.h"

// Конструктор принимает на вход родительский виджет + объект
// Содержащий настройки приложения.
WarningSettingsDialog::WarningSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WarningSettingsDialog)
{
    // Инициализация UI
    ui->setupUi(this);
}



WarningSettingsDialog::~WarningSettingsDialog()
{
    delete ui;
}

// :::::::: UI SLOTS ::::::::

void WarningSettingsDialog::on_ApplyButton_clicked()
{
    this->done(1);
}

void WarningSettingsDialog::on_CancelButton_clicked()
{
    this->done(0);
}
