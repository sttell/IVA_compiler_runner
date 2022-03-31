#ifndef COMPILER_SETTINGS_DIALOG_H
#define COMPILER_SETTINGS_DIALOG_H

#include <QDialog>
#include <QSettings>
#include "lib/buffers/settingsbuffer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CompilerSettingsDialog; }
QT_END_NAMESPACE

/*
 * CompilerSettingsDialog - форма для изменения настроек компиляции
 * программ. Инициализирует настройки ПО для процесса компиляции
 */
class CompilerSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    // Конструктор
    CompilerSettingsDialog(QWidget *parent = nullptr, SettingsBuffer* parent_settings=nullptr);
    // Деструктор
    ~CompilerSettingsDialog();

    // Слоты для UI
private slots:

    void on_ApplyButton_clicked();
    void on_CancelButton_clicked();
    void on_ChangeCompilerDirPushButton_clicked();
    void on_CompilerDirLineEdit_editingFinished();
    void on_ArchiveNameLineEdit_editingFinished();
    void on_CMakeNumRunsDecrementButton_clicked();
    void on_CMakeNumRunsIncrementButton_clicked();
    void on_CMakeNumRunsLineEdit_editingFinished();
    void on_MakeParallelCheckBox_stateChanged(int);
    void on_CMakeNumCoresLineEdit_editingFinished();
    void on_CMakeNumCoresDecrementButton_clicked();
    void on_CMakeNumCoresIncrementButton_clicked();
    void on_InputScaleLineEdit_editingFinished();
    void on_OutputScaleLineEdit_editingFinished();
    void on_KcuApiVersionEditLine_editingFinished();
    void on_KcuIpVersionEditLine_editingFinished();
    void on_MobileApiVersionEditLine_editingFinished();
    void on_MobileIpVersionEditLine_editingFinished();
    void on_ServerApiVersionEditLine_editingFinished();
    void on_ServerIpVersionEditLine_editingFinished();

private:

    // UI
    Ui::CompilerSettingsDialog *ui;

    // Settings
    SettingsBuffer *settings;

    // Инициализация состояний виджетов интерфейса
    void initUiStates();

    // Инициализация состояний индикаторов неверного формата
    void initWrongFormatIndicators();

    // Инициализация состояний виджетов из настроек(полей Line Edit, Check Boxes, etc.)
    void initStatesFromSettings();

    // Проверка всех форматов данных введенных в LineEdit
    void checkFormats();

    // Сохранение настроек
    void saveSettings();

};

#endif // COMPILER_SETTINGS_DIALOG_H
