#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/controllers/statusbar_controller.h"
#include "lib/buffers/settingsbuffer.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "lib/thread_api/interrupt_buffer.h"
#include "lib/correct_checkers/compile_runner_preprocessor.h"
#include "lib/thread_api/progressbar_buffer.h"

#include <QMainWindow>
#include <QSettings>
#include <QLineEdit>
#include <QLabel>
#include <QTextBrowser>
#include <QColor>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace WrongFmtText {

const QString base = "Неверный формат";
const QString directoryNotExist = "Директории не существует";
const QString fileNotExist = "Файла не существует";

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Проверка инициализации первого запуска ПО
    bool isFirstRunInited();

private slots:
    void on_JsonPathLineEdit_editingFinished();

    void on_WeightsPathLineEdit_editingFinished();

    void on_CatalogNameLineEdit_editingFinished();

    void on_InputSizeEditLine_editingFinished();

    void on_InputPadUpLineEdit_editingFinished();

    void on_InputPadDownLineEdit_editingFinished();

    void on_OutputSizeLineEdit_editingFinished();

    void on_OutputPadUpLineEdit_editingFinished();

    void on_OutputPadDownLineEdit_editingFinished();

    void on_ChangeJsonPathPushButton_clicked();

    void on_ChangeWeightsPathPushButton_clicked();

    void compilerSettingsAction();

    void on_RunProcessPushButton_clicked();

    void on_PickleConvertationCheckBox_stateChanged(int arg1);

    void on_OutputDirPathLineEdit_editingFinished();

    void on_OutputDirPathPushButton_clicked();

    void statusBufferUpdate();

    void updateCurrentTime();

    void on_RedactJsonPushButton_clicked();

    void on_CompilerTabButton_clicked();

    void on_RunnerTabButton_clicked();

    void on_SettingsButton_stateChanged(int arg1);

    void on_CompilerSettingsButton_clicked();

    void on_IsRemoteTensor_stateChanged(int arg1);

    void on_isGenerateTensor_stateChanged(int arg1);

    void on_TensorSizeLineEdit_editingFinished();

    void on_ProgramDirPathLineEdit_editingFinished();

    void runnerProgressUpdate();
    void on_ChangeProgramDirPathButton_clicked();
    void initUiRunnerPanelStates();

    void on_ChangeInputTensorPathButton_clicked();

    void on_ShowCmd0Button_clicked();

    void on_ShowCmd1Button_clicked();

    void on_ShowCmd2Button_clicked();

    void on_ShowCmd3Button_clicked();

    void on_ShowCmd4Button_clicked();

    void on_ShowCmd5Button_clicked();

    void on_ShowTpuDataButton_clicked();

    void on_ShowCacheDataButton_clicked();

    void on_ShowCmdJsonButton_clicked();

    void on_ShowMetadataButton_clicked();

    void on_ShowOutputTensorButton_clicked();

    void on_RunButton_clicked();

    void on_GeneratedTensorSavePathLineEdit_editingFinished();

    void on_ChangeGeneratedTensorSavePathButton_clicked();

private:
    Ui::MainWindow *ui;
    SettingsBuffer* settings;

    StatusBarController* compiler_status_controller;
    StatusBufferCache* compiler_status_cache;
    StatusBarController* runner_status_controller;
    StatusBufferCache* runner_status_cache;

    QTimer* update_timer;
    QTimer* update_runner_fast_panel_timer;

    InterruptBuffer* compile_interrupt_buffer;

    ProgressBarBuffer* runner_progress;

    bool is_first_run_inited;
    // Инициализация первого запуска приложения
    void firstRunInit();

    void initMainWindow();
    void initTimer();
    void initStatusBars();

    // Инициализация индикаторов неверного формата ввода UI
    void initWrongFormatIndicators();

    // Инициализация состояний вкладок из настроек
    void initUiStates();

    void initUiCompilerTabStates();

    void initUiRunnerTabStates();


    void initUiAnalysisTabStates();

    // TODO реализовать сохранение всех стейтов и вызвать в деструкторе.
    // Проверка формата размеров тензоров или паддингов.
    // QString text - текст из LineEdit.
    // QLabel wrong_fmt_label - индикатор неверного формата ввода
    // QString digits_regex - регулярное выражения для перечисленных через запятую параметров
    std::pair<bool, bool> checkSizesFormat(const QString& text, QString items_regex);

    bool checkCompilationInputStates();
    void formCompilationVariableSettingsDescriptor(CompileVarSettingsDescriptor&);

    std::pair<QString, QString> remoteAuthPanel();

    // Сохранение состояний полей UI в настройки
    void saveUiStates();
    void saveUiCompilerTabStates();
    void saveUiRunnerTabStates();


};
#endif // MAINWINDOW_H
