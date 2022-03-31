#ifndef WELCOME_FORM_H
#define WELCOME_FORM_H

#include <QWizard>
#include <QSettings>
#include "lib/buffers/settingsbuffer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeWizard; }
QT_END_NAMESPACE

/*
 * WelcomeWizard - форма для первого запуска приложения
 * Инициализирует глобальные настройки (на данный момент только для
 * этапа компиляции программ)
 */
class WelcomeWizard : public QWizard
{
    Q_OBJECT

public:
    // Конструктор
    WelcomeWizard(QWidget *parent = nullptr, SettingsBuffer* parent_settings=nullptr);

    // Деструктор
    ~WelcomeWizard();

    // Слоты для UI
private slots:
    void on_ChangeCompilerPathPushButton_clicked();

    void on_NumberRunsLineEdit_editingFinished();

    void on_NumberCoresLineEdit_editingFinished();

    void on_InputCompilerPathLineEdit_editingFinished();

    void on_NumRunsIncrement_clicked();

    void on_NumRunsDecrement_clicked();

    void on_NumCoresIncrement_clicked();

    void on_NumCoresDecrement_clicked();

    void on_ArchiveNameLineEdit_editingFinished();

    void on_MakeParallelCheckBox_stateChanged(int arg1);

    void on_InputScaleLineEdit_editingFinished();

    void on_OutputScaleLineEdit_editingFinished();

private:

    // UI
    Ui::WelcomeWizard *ui;

    // Parent settings
    SettingsBuffer *settings;

    // Инициализация состояний виджетов в UI
    void initUiStates();

    // Инициализация состояний индикаторов неверного формата ввода
    void initWrongFormatIndicators();

    // Сохранение настроек
    void saveSettings();
};

#endif // WELCOME_FORM_H
