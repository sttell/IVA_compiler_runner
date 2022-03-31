#ifndef WARNING_SETTINGS_DIALOG_H
#define WARNING_SETTINGS_DIALOG_H

#include <QDialog>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class WarningSettingsDialog; }
QT_END_NAMESPACE

/*
 * WarningSettingsDialog - Диалоговое окно, которое заставляет подтвердить
 * примененные настройки в случае неверных форматов данных в окне настроек.
 * Выводит предупреждающее сообщение и просит подтверждения или отклонения.
 */
class WarningSettingsDialog : public QDialog
{
    Q_OBJECT

public:

    // Конструктор
    WarningSettingsDialog(QWidget *parent = nullptr);
    // Деструктор
    ~WarningSettingsDialog();

private slots:
    // При нажатии на Подтвердить закрывает окно с кодом 1
    void on_ApplyButton_clicked();

    // При нажатии на Отклонить закрыват окно с кодом 0
    void on_CancelButton_clicked();
private:

    // UI
    Ui::WarningSettingsDialog *ui;

};

#endif // WARNING_SETTINGS_DIALOG_H
