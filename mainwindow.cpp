#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "include/settings_config.h"
#include "include/wrong_fmt_captures.h"
#include "lib/controllers/statusbar_controller.h"
#include "lib/correct_checkers/compile_runner_preprocessor.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "lib/buffers/settingsbuffer.h"
#include "lib/runner_core/runnercore.h"
#include "ui/remote_auth_dialog.h"

#include "ui/welcome_form.h"
#include "ui/compiler_settings_dialog.h"

#include <boost/process.hpp>
#include <QSettings>
#include <QRegularExpression>
#include <QFileDialog>
#include <QObject>
#include <QColor>
#include <QSyntaxHighlighter>
#include <iostream>
#include <QTime>
#include <QRect>
#include <boost/filesystem.hpp>
#include <boost/process/posix.hpp>
#include <unistd.h>

#define FILE_EDITOR "code -r"
#define BINARY_EDITOR "ghex"

#define UPDATE_WINDOW_LATENCY_MS 100
#define UPDATE_RUNNER_FAST_PANEL_LATENCY_MS 1000

// Функция для запуска процесса компиляции в мультипоточном режиме. Запускает препроцессор компиляции.
// Input params:
//      const CompileVarSettingsDescriptor& settings_desc    - Дескриптор настроек собранных с окна CompilerTab
//      StatusBufferCache*                  status_bar       - Кэш статус бара для вывода лога компиляции.
//      SettingsBuffer*                     settings         - Общий буффер настроек
//      InterruptBuffer*                    interrupt_buffer - буффер для прерывания потока. (Временно не работает)
void run_compile(const CompileVarSettingsDescriptor& settings_desc,
                 StatusBufferCache* status_bar,
                 SettingsBuffer* settings,
                 InterruptBuffer* interrupt_buffer)
{
    CompileRunnerProcessor runner(settings_desc, status_bar, settings, interrupt_buffer);
    runner();
}


// Функция для запуска файла на редактирование.
// Input params:
//      const std::string& path     - путь к файлу для редактирования. (Должен существовать)
//      const std::string& redactor - команда реадктора для запуска стороннего ПО.
void redact_file(const std::string& path, const std::string& redactor) {
    // Формирование команды запуска
    std::string exec(redactor); exec += " "; exec += path;

    // pipe для потоков вывода
    boost::process::ipstream stdoutput, stderror;

    // Запуск процесса
    int retcode = boost::process::system(
                exec,
                boost::process::std_out > stdoutput,
                boost::process::std_err > stderror
    );
}

// Конструктор MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)                             // Родительское окно
    , ui(new Ui::MainWindow)                          // User Interface для MainWindow
    , settings(new SettingsBuffer())                  // Указатель на буффер настроек
    , is_first_run_inited(false)                      // Флаг первичной инициализации приложения
    , update_timer(new QTimer)                        // Таймер для вызова регулярного обновления (раз в 100 мс)
    , update_runner_fast_panel_timer(new QTimer)      // Таймер для обновления панели быстрого доступа вкладки Runner (раз в 1 сек)
    , compile_interrupt_buffer(new InterruptBuffer)   // Буффер для приостановки потоков
    , runner_progress(new ProgressBarBuffer(0, 100))  // Буффер для хранения состояний Progress Bar вкладки Runner Tab
{

    // Инициализация UI
    ui->setupUi(this);

    // Инициализация интерфейса и состояний MainWindow
    this->initMainWindow();

}

// Общий метод инициализации главного окна
void MainWindow::initMainWindow() {

    // Инициализация при первом запуске. Проверка первого запуска приложения.
    this->firstRunInit();

    // Инициализация таймера обновлений
    this->initTimer();

    // Инициализация статус баров
    this->initStatusBars();

    // Инициализация состояний полей из настроек
    this->initUiStates();

    // Инициализация индикаторов неверного формата(отключение видимости)
    this->initWrongFormatIndicators();
}

// Инициализация таймера обновлений главного окна
void MainWindow::initTimer() {
    // Установка интервала для таймеров обновлений
    update_timer->setInterval(UPDATE_WINDOW_LATENCY_MS);
    update_runner_fast_panel_timer->setInterval(UPDATE_RUNNER_FAST_PANEL_LATENCY_MS);

    // Подключение таймера к слотам
    connect(update_timer, SIGNAL(timeout()), this, SLOT(statusBufferUpdate()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(updateCurrentTime()));
    connect(update_timer, SIGNAL(timeout()), this, SLOT(runnerProgressUpdate()));
    connect(update_runner_fast_panel_timer, SIGNAL(timeout()), this, SLOT(initUiRunnerPanelStates()));

    // Запуск работы таймера
    update_timer->start();
    update_runner_fast_panel_timer->start();
}

// Инициализация Status баров главного окна
void MainWindow::initStatusBars() {
    // Кэш статус бара для компиляции
    compiler_status_cache = new StatusBufferCache();

    // Инициализация контроллера статус бара компилятора
    compiler_status_controller = new StatusBarController(ui->CompilerStatusBar);

    // Кэш статус бара для окна запуска программ
    runner_status_cache = new StatusBufferCache();

    // Статус бар контроллер для окна запуска программ
    runner_status_controller = new StatusBarController(ui->RunnerStatusBar);

}

// Деструктор MainWindow. Высвобождает занятые ресурсы и сохраняет состояния полей
MainWindow::~MainWindow()
{
    // Сохраняет состояние полей
    this->saveUiStates();

    // Освобождает ресурсы
    delete compiler_status_controller;
    delete compiler_status_cache;
    delete runner_status_controller;
    delete runner_status_cache;
    delete settings;
    delete ui;
}

// Проводит стартовую инициализацию настроек приложения
void MainWindow::firstRunInit() {

    // Открываем глобальные настройки
    settings->beginGroup(GLOBAL_SETTINGS_GROUP);

    // Проверка на инициализацию ранее
    bool is_inited = settings->value("is_application_inited", false).toBool();

    settings->endGroup();

    // Если ранее приложение не запускалось, то напрявляем в Welcome форму
    if (!is_inited) {
        // Создание welcome формы
        WelcomeWizard welcome_wizard(this, settings);
        welcome_wizard.show();
        int return_code = welcome_wizard.exec();

        // Если код возврата не нулевой, то была нажата кнопка finish
        bool is_welcome_inited = (return_code != 0);

        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        // Устанавливаем новое значение в настройках
        settings->setValue("is_application_inited", is_welcome_inited);

        settings->endGroup();
        // Устанавливаем новое значение флагу
        is_first_run_inited = is_welcome_inited;
    } else {
        // В случае, когда инициализация уже проводилась нужно выставить флаг true
        is_first_run_inited = true;
    }
}

// Проверка первичной инициализации приложения
bool MainWindow::isFirstRunInited() {
    // Возвращаем флаг
    return is_first_run_inited;
};

// Инициализация индикаторов неверного формата
void MainWindow::initWrongFormatIndicators()
{

    on_CatalogNameLineEdit_editingFinished();
    on_InputPadDownLineEdit_editingFinished();
    on_InputPadUpLineEdit_editingFinished();
    on_InputSizeEditLine_editingFinished();
    on_JsonPathLineEdit_editingFinished();
    on_OutputPadDownLineEdit_editingFinished();
    on_OutputPadUpLineEdit_editingFinished();
    on_OutputSizeLineEdit_editingFinished();
    on_WeightsPathLineEdit_editingFinished();
    on_OutputDirPathLineEdit_editingFinished();

}

// Инициализация состояний из настроек
void MainWindow::initUiStates() {
    // Инициализация состояний CompilerTab
    this->initUiCompilerTabStates();

    // Инициализация состояний Runner Tab
    this->initUiRunnerTabStates();

    // Инициализация состояний Analysis Tab
    this->initUiAnalysisTabStates();

    ui->CompilerTabWidget->setVisible(true);
    ui->CompilerTabButton->setChecked(true);
    ui->RunnerTabWidget->setVisible(false);

    // Инициализация начального состояния Settings Menu
    ui->SettingsButton->setChecked(false);
    ui->CompilerSettingsButton->setVisible(false);
    ui->RunnerSettingsButton->setVisible(false);
    ui->AnalysisSettingsButton->setVisible(false);

}

// Инициализация состояний полей вкладки Compiler Tab из настроек
void MainWindow::initUiCompilerTabStates() {
    // Переход в группу настроек
    settings->beginGroup(COMPILER_SETTINGS_GROUP);

    // Line Edits
    QString json_path = settings->value(ui->JsonPathLineEdit->objectName(), QString("/home/")).toString();
    QString weights_path = settings->value(ui->WeightsPathLineEdit->objectName(), QString("/home/")).toString();
    QString output_path = settings->value(ui->OutputDirPathLineEdit->objectName(), QString("/home/")).toString();
    QString program_directory_name = settings->value(ui->CatalogNameLineEdit->objectName(), QString("TestProgram")).toString();
    QString input_size = settings->value(ui->InputSizeEditLine->objectName(), QString("1, 1, 1, 1")).toString();
    QString output_size = settings->value(ui->OutputSizeLineEdit->objectName(), QString("1, 1, 1, 1")).toString();
    QString input_pad_up = settings->value(ui->InputPadUpLineEdit->objectName(), QString("0, 0, 0, 0")).toString();
    QString input_pad_down = settings->value(ui->InputPadDownLineEdit->objectName(), QString("0, 0, 0, 0")).toString();
    QString output_pad_up = settings->value(ui->OutputPadUpLineEdit->objectName(), QString("0, 0, 0, 0")).toString();
    QString output_pad_down = settings->value(ui->OutputPadDownLineEdit->objectName(), QString("0, 0, 0, 0")).toString();

    // Check Boxes
    bool is_add_compilation_logs = settings->value(ui->AddCompilationLogCheckBox->objectName(), true).toBool();
    bool is_add_bias_preload = settings->value(ui->AddBiasPreloadCheckBox->objectName(), true).toBool();
    bool is_add_input_optimization = settings->value(ui->AddInputOptimizationCheckBox->objectName(), true).toBool();
    bool is_add_reorder_optimization = settings->value(ui->AddReorderOptimizationCheckBox->objectName(), true).toBool();
    bool is_add_debug_mode = settings->value(ui->AddDebugModeCheckBox->objectName(), true).toBool();
    bool is_convert_json = settings->value(ui->JsonConvertationCheckBox->objectName(), false).toBool();
    bool is_convert_pickle = settings->value(ui->PickleConvertationCheckBox->objectName(), true).toBool();
    bool is_check_addresses = settings->value(ui->AddressCheckCheckBox->objectName(), true).toBool();
    bool is_compile_program = settings->value(ui->CompileProgrammCheckBox->objectName(), true).toBool();
    bool is_make_archive = settings->value(ui->MakeArchiveCheckBox->objectName(), true).toBool();
    bool is_make_metadata = settings->value(ui->MakeMetadataCheckBox->objectName(), true).toBool();
    bool is_preload_filters = settings->value(ui->AddFilterPreloadCheckBox->objectName(), true).toBool();

    // Combo Boxes
    unsigned int device_index = settings->value(ui->DeviceComboBox->objectName(), 0).toUInt();

    // Обновление состояний
    // Line Edits
    ui->JsonPathLineEdit->setText(json_path);
    ui->WeightsPathLineEdit->setText(weights_path);
    ui->OutputDirPathLineEdit->setText(output_path);
    ui->CatalogNameLineEdit->setText(program_directory_name);
    ui->InputSizeEditLine->setText(input_size);
    ui->OutputSizeLineEdit->setText(output_size);
    ui->InputPadDownLineEdit->setText(input_pad_down);
    ui->InputPadUpLineEdit->setText(input_pad_up);
    ui->OutputPadDownLineEdit->setText(output_pad_down);
    ui->OutputPadUpLineEdit->setText(output_pad_up);

    // Check Boxes
    ui->AddCompilationLogCheckBox->setChecked(is_add_compilation_logs);
    ui->AddBiasPreloadCheckBox->setChecked(is_add_bias_preload);
    ui->AddInputOptimizationCheckBox->setChecked(is_add_input_optimization);
    ui->AddReorderOptimizationCheckBox->setChecked(is_add_reorder_optimization);
    ui->AddDebugModeCheckBox->setChecked(is_add_debug_mode);
    ui->JsonConvertationCheckBox->setChecked(is_convert_json);
    ui->PickleConvertationCheckBox->setChecked(is_convert_pickle);
    ui->AddressCheckCheckBox->setChecked(is_check_addresses);
    ui->CompileProgrammCheckBox->setChecked(is_compile_program);
    ui->MakeArchiveCheckBox->setChecked(is_make_archive);
    ui->MakeMetadataCheckBox->setChecked(is_make_metadata);
    ui->AddFilterPreloadCheckBox->setChecked(is_preload_filters);

    // Combo Boxes
    ui->DeviceComboBox->setCurrentIndex(device_index);
    ui->JsonConvertationCheckBox->setEnabled(false);

    settings->endGroup();
}

// Инициализация состояний полей вкладки Runner Tab из настроек
void MainWindow::initUiRunnerTabStates() {
    settings->beginGroup(RUNNER_SETTINGS_GROUP);
    QString program_dir = settings->value(ui->ProgramDirPathLineEdit->objectName(), "/home/").toString();
    QString input_tensor_path = settings->value(ui->InputTensorPathLineEdit->objectName(), "").toString();
    QString input_tensor_size = settings->value(ui->TensorSizeLineEdit->objectName(), "1,1,1,1").toString();
    QString input_tensor_save = settings->value(ui->GeneratedTensorSavePathLineEdit->objectName(), "/home/tensor.bin").toString();
    bool is_remote_tensor = settings->value(ui->IsRemoteTensor->objectName(), true).toBool();
    bool is_generate_tensor = settings->value(ui->isGenerateTensor->objectName(), false).toBool();

    settings->endGroup();

    ui->ProgramDirPathLineEdit->setText(program_dir);
    ui->InputTensorPathLineEdit->setText(input_tensor_path);
    ui->TensorSizeLineEdit->setText(input_tensor_size);
    ui->GeneratedTensorSavePathLineEdit->setText(input_tensor_save);
    ui->IsRemoteTensor->setChecked(is_remote_tensor);
    ui->isGenerateTensor->setChecked(is_generate_tensor);

    // Check Boxes States
    on_IsRemoteTensor_stateChanged(ui->IsRemoteTensor->isChecked());
    on_isGenerateTensor_stateChanged(ui->isGenerateTensor->isChecked());

    // Wrong Format Indicators
    on_ProgramDirPathLineEdit_editingFinished();
    on_GeneratedTensorSavePathLineEdit_editingFinished();

    ui->RunnerProgressBar->setValue(runner_progress->getCurrent());
    ui->RunnerProgressBar->setMaximum(runner_progress->getMax());
    ui->RunnerProgressBar->setMinimum(runner_progress->getMin());

}

void MainWindow::initUiRunnerPanelStates(){
    if (ui->RunnerTabButton->isChecked()) {

        if (!ui->WrongFmtProgramDirPathLabel->isVisible()) {

            bool is_cmd0bin_found(false), is_cmdjson_found(false),
                 is_cmd1bin_found(false), is_metadata_found(false),
                 is_cmd2bin_found(false), is_cache_data_found(false),
                 is_cmd3bin_found(false), is_tpu_data_found(false),
                 is_cmd4bin_found(false), is_output_found(false),
                 is_cmd5bin_found(false);

            QString program_dir(ui->ProgramDirPathLineEdit->text());
            QString logs_dir = program_dir + "/logs";
            QString output_dir = program_dir + "/output";

            if (boost::filesystem::is_regular_file((program_dir + "/cmd0.bin").toStdString()))
                is_cmd0bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd1.bin").toStdString()))
                is_cmd1bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd2.bin").toStdString()))
                is_cmd2bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd3.bin").toStdString()))
                is_cmd3bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd4.bin").toStdString()))
                is_cmd4bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd5.bin").toStdString()))
                is_cmd5bin_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/cmd.json").toStdString()))
                is_cmdjson_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/metadata.json").toStdString()))
                is_metadata_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/logs/CashData").toStdString()))
                is_cache_data_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/logs/tpu_data").toStdString()))
                is_tpu_data_found = true;
            if (boost::filesystem::is_regular_file((program_dir + "/output/output.bin").toStdString()))
                is_output_found = true;

            ui->ShowCmd0Button->setEnabled(is_cmd0bin_found);
            ui->ShowCmd1Button->setEnabled(is_cmd1bin_found);
            ui->ShowCmd2Button->setEnabled(is_cmd2bin_found);
            ui->ShowCmd3Button->setEnabled(is_cmd3bin_found);
            ui->ShowCmd4Button->setEnabled(is_cmd4bin_found);
            ui->ShowCmd5Button->setEnabled(is_cmd5bin_found);
            ui->ShowCmdJsonButton->setEnabled(is_cmdjson_found);
            ui->ShowMetadataButton->setEnabled(is_metadata_found);
            ui->ShowCacheDataButton->setEnabled(is_cache_data_found);
            ui->ShowTpuDataButton->setEnabled(is_tpu_data_found);
            ui->ShowOutputTensorButton->setEnabled(is_output_found);
        }

    }
}

// Инициализация состояний полей вкладки Analysis Tab из настроек
void MainWindow::initUiAnalysisTabStates() {
    // TODO To do Task
}

// Сохранение состояний влкадок в настройки
void MainWindow::saveUiStates() {
    // Сохранение вкладки Compiler Tab
    saveUiCompilerTabStates();

    saveUiRunnerTabStates();
}

// Сохранение состояний для вкладки CompilerTab
void MainWindow::saveUiCompilerTabStates() {
    // Смена группы на настройки компиляции
    settings->beginGroup(COMPILER_SETTINGS_GROUP);

    // Save Edit Lines state
    settings->setValue(
                ui->JsonPathLineEdit->objectName(),
                ui->JsonPathLineEdit->text());
    settings->setValue(
                ui->WeightsPathLineEdit->objectName(),
                ui->WeightsPathLineEdit->text());
    settings->setValue(
                ui->OutputDirPathLineEdit->objectName(),
                ui->OutputDirPathLineEdit->text());
    settings->setValue(
                ui->CatalogNameLineEdit->objectName(),
                ui->CatalogNameLineEdit->text());
    settings->setValue(
                ui->InputSizeEditLine->objectName(),
                ui->InputSizeEditLine->text());
    settings->setValue(
                ui->OutputSizeLineEdit->objectName(),
                ui->OutputSizeLineEdit->text());
    settings->setValue(
                ui->InputPadDownLineEdit->objectName(),
                ui->InputPadDownLineEdit->text());
    settings->setValue(
                ui->InputPadUpLineEdit->objectName(),
                ui->InputPadUpLineEdit->text());
    settings->setValue(
                ui->WeightsPathLineEdit->objectName(),
                ui->WeightsPathLineEdit->text());
    settings->setValue(
                ui->OutputPadDownLineEdit->objectName(),
                ui->OutputPadDownLineEdit->text());
    settings->setValue(
                ui->OutputPadUpLineEdit->objectName(),
                ui->OutputPadUpLineEdit->text());

    // Save Check Boxes state
    settings->setValue(
                ui->AddCompilationLogCheckBox->objectName(),
                ui->AddCompilationLogCheckBox->isChecked());
    settings->setValue(
                ui->AddBiasPreloadCheckBox->objectName(),
                ui->AddBiasPreloadCheckBox->isChecked());
    settings->setValue(
                ui->AddInputOptimizationCheckBox->objectName(),
                ui->AddInputOptimizationCheckBox->isChecked());

    settings->setValue(
                ui->AddReorderOptimizationCheckBox->objectName(),
                ui->AddReorderOptimizationCheckBox->isChecked());
    settings->setValue(
                ui->AddDebugModeCheckBox->objectName(),
                ui->AddDebugModeCheckBox->isChecked());
    settings->setValue(
                ui->JsonConvertationCheckBox->objectName(),
                ui->JsonConvertationCheckBox->isChecked());
    settings->setValue(
                ui->PickleConvertationCheckBox->objectName(),
                ui->PickleConvertationCheckBox->isChecked());
    settings->setValue(
                ui->AddressCheckCheckBox->objectName(),
                ui->AddressCheckCheckBox->isChecked());
    settings->setValue(
                ui->CompileProgrammCheckBox->objectName(),
                ui->CompileProgrammCheckBox->isChecked());
    settings->setValue(
                ui->MakeArchiveCheckBox->objectName(),
                ui->MakeArchiveCheckBox->isChecked());
    settings->setValue(
                ui->MakeMetadataCheckBox->objectName(),
                ui->MakeMetadataCheckBox->isChecked());
    settings->setValue(
                ui->AddFilterPreloadCheckBox->objectName(),
                ui->AddFilterPreloadCheckBox->isChecked());

    // Save Combo Boxes state
    settings->setValue(
                ui->DeviceComboBox->objectName(),
                ui->DeviceComboBox->currentIndex());

    settings->endGroup();

}

void MainWindow::saveUiRunnerTabStates() {
    // Смена группы на настройки компиляции
    settings->beginGroup(RUNNER_SETTINGS_GROUP);

    settings->setValue(
                ui->ProgramDirPathLineEdit->objectName(),
                ui->ProgramDirPathLineEdit->text()
    );
    settings->setValue(
                ui->InputTensorPathLineEdit->objectName(),
                ui->InputTensorPathLineEdit->text()
    );
    settings->setValue(
                ui->TensorSizeLineEdit->objectName(),
                ui->TensorSizeLineEdit->text()
    );
    settings->setValue(
                ui->GeneratedTensorSavePathLineEdit->objectName(),
                ui->GeneratedTensorSavePathLineEdit->text()
    );
    settings->setValue(
                ui->IsRemoteTensor->objectName(),
                ui->IsRemoteTensor->isChecked()
    );
    settings->setValue(
                ui->isGenerateTensor->objectName(),
                ui->isGenerateTensor->isChecked()
    );

    settings->endGroup();
}

// Проверка соответствия формата введенных размеров тензора / паддингов
// Формат по умолчанию - +-b,+-x,+-y,+-l
// text - текст из LineEdit
// item_regex="" - регулярное выражение применяемое к элементам списка.
// Возвращает пару булевых значений, которые отображают соответствие обоим регулярным выражениям.
// Если основное регулярное выражение не попадает в формат, то вернется false в первой позиции
// Если любой из элементов не соответствует item_regex, то возращается false во второй позиции
// В случае когда все регулярные выражения попадают в формат, то возвращается [true, true]
std::pair<bool, bool> MainWindow::checkSizesFormat(const QString& text, QString items_regex) {
    // Регулярное выражение для d,d,d,d формата
    QRegularExpression rx("^(-?\\d+),(-?\\d+),(-?\\d+),(-?\\d+)$");

    // Копия переданного текста для обработки
    QString text_copy(text);

    // Удаление пробелов из текста
    text_copy.remove(' ');

    // Проверка на соответствие основному регулярному выражению
    bool is_matched = rx.match(text_copy).hasMatch();

    // Флаг чисел неверного формата
    bool is_matched_child(true);

    // Если основное регулярное выражение дало положительный результат
    // То проверяем на отсутствие неверных форматов для каждого айтема
    if (is_matched && !items_regex.isEmpty()) {
        // Регулярное выражение для айтемов
        QRegularExpression digit_rx(items_regex);
        // Разделение по запятой
        QStringList digits = text_copy.split(',');
        // Проверка соответствия каждого элемента выражению
        for (const auto& digit : digits) {
            if (!(digit_rx.match(digit).hasMatch())) {
                is_matched_child = false;
                break;
            }
        }
    }

    return {is_matched, is_matched_child};

}

// Действие выполняемое при нажатии в меню настреок компилятора
void MainWindow::compilerSettingsAction()
{
    // Открываем диалговое окно
    CompilerSettingsDialog dialog(this, settings);

    // Показываем его и ждем возврата
    dialog.show();

    // Код возврата диалогового окна
    int ret_code = dialog.exec();
}

// ::::СЛОТЫ ДЛЯ UI:::::
void MainWindow::on_JsonPathLineEdit_editingFinished()
{
    // Проверка существования файла

    // Путь указанный в LineEdit
    QString path = ui->JsonPathLineEdit->text();

    // Если файл существует
    bool is_exist = boost::filesystem::is_regular_file(path.toStdString());
    // Если файл нужного формата
    bool is_json = path.toLower().endsWith(".json");

    // Если файл нормальный, то выставляем видимость в false и выходим
    if (is_exist && is_json) {
        ui->WrongFmtJsonPathLabel->setVisible(false);
        return;
    }

    // Если есть ошибка, то выставляем нужный текст и видимость индикатора
    if (is_exist && (!is_json))
        ui->WrongFmtJsonPathLabel->setText(WRONG_FMT_TEXT::not_json_fmt);
    else if(!is_exist)
        ui->WrongFmtJsonPathLabel->setText(WRONG_FMT_TEXT::file_not_exist);

    ui->WrongFmtJsonPathLabel->setVisible(true);

}


void MainWindow::on_WeightsPathLineEdit_editingFinished()
{
    // Проверка существования файла

    // Путь указанный в LineEdit
    QString path = ui->WeightsPathLineEdit->text();

    // Ожидаемый формат файла
    QString current_format;

    if (ui->PickleConvertationCheckBox->isChecked()) current_format = ".pickle";
    else current_format = ".bin";

    // Если файл существует
    bool is_exist = boost::filesystem::is_regular_file(path.toStdString());
    // Если файл нужного формата
    bool is_weights = path.toLower().endsWith(current_format);

    // Если файл нормальный, то выставляем видимость в false и выходим
    if (is_exist && is_weights) {
        ui->WrongFmtWeightsPathLabel->setVisible(false);
        return;
    }


    // Если есть ошибка, то выставляем нужный текст и видимость индикатора
    if (is_exist && (!is_weights) && (current_format == ".pickle"))
        ui->WrongFmtWeightsPathLabel->setText(WRONG_FMT_TEXT::not_pickle_fmt);
    else if (is_exist && (!is_weights) && (current_format == ".bin"))
        ui->WrongFmtWeightsPathLabel->setText(WRONG_FMT_TEXT::not_bin_fmt);
    else if(!is_exist)
        ui->WrongFmtWeightsPathLabel->setText(WRONG_FMT_TEXT::file_not_exist);

    ui->WrongFmtWeightsPathLabel->setVisible(true);
}


void MainWindow::on_CatalogNameLineEdit_editingFinished()
{
    // Проверка имени директории на допустимый формат ОС

    // Недопустимые символы
    QString wrong_symbols("*|:\"<>?/\\");
    // Флаг соответствия имени директории формату
    bool is_wrong = false;

    // Проходимся по символам. Если имеются плохие значения, то выставляем флаг
    for(const QChar& sym : ui->CatalogNameLineEdit->text()) {
        if (wrong_symbols.contains(sym)) {
            is_wrong = true;
            break;
        }
    }

    // Если формат не допустимый, то устанавливаем индикатор
    if (is_wrong) {
        ui->WrongFmtCatalogNameLabel->setText(WRONG_FMT_TEXT::bad_dir_format);
        ui->WrongFmtCatalogNameLabel->setVisible(true);
    } else
        ui->WrongFmtCatalogNameLabel->setVisible(false);
}


void MainWindow::on_InputSizeEditLine_editingFinished()
{
    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->InputSizeEditLine->text(), "^[1-9]");
    if (!is_general) {
        ui->WrongFmtInputSizeLabel->setText("Неверный формат");
        ui->WrongFmtInputSizeLabel->setVisible(true);
        return;
    } else if (!is_child) {
        ui->WrongFmtInputSizeLabel->setText("Тут не должно быть нуля");
        ui->WrongFmtInputSizeLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtInputSizeLabel->setVisible(false);
    }
}


void MainWindow::on_InputPadUpLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->InputPadUpLineEdit->text(), "");
    if (!is_general) {
        ui->WrongFmtInputPadUpLabel->setText("Неверный формат");
        ui->WrongFmtInputPadUpLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtInputPadUpLabel->setVisible(false);
    }
}


void MainWindow::on_InputPadDownLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->InputPadDownLineEdit->text(), "");
    if (!is_general) {
        ui->WrongFmtInputPadDownLabel->setText("Неверный формат");
        ui->WrongFmtInputPadDownLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtInputPadDownLabel->setVisible(false);
    }
}


void MainWindow::on_OutputSizeLineEdit_editingFinished()
{
    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputSizeLineEdit->text(), "^[1-9]");
    if (!is_general) {
        ui->WrongFmtOutputSizeLabel->setText("Неверный формат");
        ui->WrongFmtOutputSizeLabel->setVisible(true);
        return;
    } else if (!is_child) {
        ui->WrongFmtOutputSizeLabel->setText("Тут не должно быть нуля");
        ui->WrongFmtOutputSizeLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtOutputSizeLabel->setVisible(false);
    }
}


void MainWindow::on_OutputPadUpLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputPadUpLineEdit->text(), "");
    if (!is_general) {
        ui->WrongFmtOutputPadUpLabel->setText("Неверный формат");
        ui->WrongFmtOutputPadUpLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtOutputPadUpLabel->setVisible(false);
    }
}


void MainWindow::on_OutputPadDownLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputPadDownLineEdit->text(), "");
    if (!is_general) {
        ui->WrongFmtOutputPadDownLabel->setText("Неверный формат");
        ui->WrongFmtOutputPadDownLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtOutputPadDownLabel->setVisible(false);
    }
}


void MainWindow::on_ChangeJsonPathPushButton_clicked()
{
    // Изменение пути к JSON файлу.
    QString current_path = ui->JsonPathLineEdit->text();
    // Проверка существования текущего пути или пути к директории
    bool is_path_exist = (boost::filesystem::is_regular_file(current_path.toStdString()) ||
                          boost::filesystem::is_directory(current_path.toStdString()));

    // Базовый стартовый путь
    QString start_path("/home/");

    // Если текущий введенный путь существует, то устанавливаем его в качестве стартового
    if (is_path_exist) start_path = current_path;

    // Запускаем проводник и ожидаем выбора файла
    QString file = QFileDialog::getOpenFileName(
                this,
                "Выбор файла с весами сети",
                start_path,
                "Все файлы (*.json)"
                );

    // Если полученный путь не пуст, то устанавливаем новый и запускаем проверку
    if (!file.isEmpty()) {
        ui->JsonPathLineEdit->setText(file);
        on_JsonPathLineEdit_editingFinished();
    }

}


void MainWindow::on_ChangeWeightsPathPushButton_clicked()
{
    // Текущее состояние введенного пути и проверка его существования
    QString current_path = ui->WeightsPathLineEdit->text();
    bool is_path_exist = (boost::filesystem::is_regular_file(current_path.toStdString()) ||
                          boost::filesystem::is_directory(current_path.toStdString()));
    // Базовый путь
    QString start_path("/home/");
    // Если текущий путь существует, то устанавливаем его в качестве стартового
    if (is_path_exist) start_path = current_path;

    // Запускаем проводник для поиска файлов
    QString file = QFileDialog::getOpenFileName(
                this,
                "Выбор файла с весами сети",
                start_path,
                "Все файлы (*.bin *.pickle);; Бинарные файлы (*.bin);; Pickle файлы (*.pickle)"
                );

    // Если путь не пуст, то устанавливаем новое состояние и проверяем корректность
    if (!file.isEmpty()) {
        ui->WeightsPathLineEdit->setText(file);
        on_WeightsPathLineEdit_editingFinished();
    }

}

bool MainWindow::checkCompilationInputStates() {

    // Обновление всех индикаторов предупреждений
    on_JsonPathLineEdit_editingFinished();
    on_WeightsPathLineEdit_editingFinished();
    on_CatalogNameLineEdit_editingFinished();
    on_InputSizeEditLine_editingFinished();
    on_OutputSizeLineEdit_editingFinished();
    on_InputPadDownLineEdit_editingFinished();
    on_OutputPadDownLineEdit_editingFinished();
    on_InputPadUpLineEdit_editingFinished();
    on_OutputPadUpLineEdit_editingFinished();

    // Если показан индикатор для JSON пути
    if (ui->WrongFmtJsonPathLabel->isVisible()) {
        compiler_status_cache->writeMessage("JSON файл не найден.", "auto", MessageColor::error);
        return false;
    }
    // Если показан индикатор для Weights пути
    if (ui->WrongFmtWeightsPathLabel->isVisible()) {
        compiler_status_cache->writeMessage("Файл с весами не найден.", "auto", MessageColor::error);
        return false;
    }

    // Проверка соответствия формата весов пайплайну компиляции
    QString weights_path(ui->WeightsPathLineEdit->text());
    QString expected_weights_format(".bin");

    if (ui->PickleConvertationCheckBox->isChecked())
        expected_weights_format = ".pickle";

    if (!(weights_path.endsWith(expected_weights_format))) {
        QString message = "Пайплайн компиляции предусматривает конвертирование Pickle весов. ";
        message += QString::fromUtf8("Необходимо указать Pickle файл с весами.");
        compiler_status_cache->writeMessage(message.toStdString(), "auto", MessageColor::error);
        return false;
    }

    // Если неверно указано имя каталога
    if (ui->WrongFmtCatalogNameLabel->isVisible()) {
        compiler_status_cache->writeMessage("Недопустимое имя каталога с выходом программы.", "auto", MessageColor::error);
        return false;
    }

    // Если неверно указан размер входного тензора
    if (ui->WrongFmtInputSizeLabel->isVisible()) {
        compiler_status_cache->writeMessage("Недопустимый формат размера входного тензора.", "auto", MessageColor::error);
        return false;
    }

    // Если неверно указан размер выходного тензора
    if(ui->WrongFmtOutputSizeLabel->isVisible())
    {
        compiler_status_cache->writeMessage("Недопустимый формат размера выходного тензора.", "auto", MessageColor::error);
        return false;
    }

    // Если неверно указано одно из полей паддингов
    if (ui->WrongFmtInputPadDownLabel->isVisible() ||
            ui->WrongFmtInputPadUpLabel->isVisible() ||
            ui->WrongFmtOutputPadDownLabel->isVisible() ||
            ui->WrongFmtOutputPadUpLabel->isVisible()) {
        compiler_status_cache->writeMessage("Недопустимый формат паддингов.", "auto", MessageColor::error);
        return false;
    }

    return true;
}

void MainWindow::formCompilationVariableSettingsDescriptor(CompileVarSettingsDescriptor& settings_desc) {
    settings_desc.json_path = ui->JsonPathLineEdit->text();
    settings_desc.weights_path = ui->WeightsPathLineEdit->text();
    settings_desc.output_directory_path = ui->OutputDirPathLineEdit->text();
    settings_desc.output_directory_name = ui->CatalogNameLineEdit->text();
    settings_desc.input_size = ui->InputSizeEditLine->text().remove(" ");
    settings_desc.output_size = ui->OutputSizeLineEdit->text().remove(" ");
    settings_desc.input_pad_up = ui->InputPadUpLineEdit->text().remove(" ");
    settings_desc.output_pad_up = ui->OutputPadUpLineEdit->text().remove(" ");
    settings_desc.input_pad_down = ui->InputPadDownLineEdit->text().remove(" ");
    settings_desc.output_pad_down = ui->OutputPadDownLineEdit->text().remove(" ");
    settings_desc.is_input_optimization = ui->AddInputOptimizationCheckBox->isChecked();
    settings_desc.is_add_logs = ui->AddCompilationLogCheckBox->isChecked();
    settings_desc.is_preload_bias_scales = ui->AddBiasPreloadCheckBox->isChecked();
    settings_desc.is_preload_filters = ui->AddFilterPreloadCheckBox->isChecked();
    settings_desc.is_reorder_data = ui->AddReorderOptimizationCheckBox->isChecked();
    settings_desc.device_index = ui->DeviceComboBox->currentIndex();
    settings_desc.pipe_json_convert = ui->JsonConvertationCheckBox->isChecked();
    settings_desc.pipe_weights_convert = ui->PickleConvertationCheckBox->isChecked();
    settings_desc.pipe_address_check = ui->AddressCheckCheckBox->isChecked();
    settings_desc.pipe_compile = ui->CompileProgrammCheckBox->isChecked();
    settings_desc.pipe_create_metadata = ui->MakeMetadataCheckBox->isChecked();
    settings_desc.pipe_make_output = ui->MakeArchiveCheckBox->isChecked();
}

// Запуск процесса компиляции
void MainWindow::on_RunProcessPushButton_clicked()
{

   // Проверка состояний всех введенных пользователем параметров
   bool is_normal_states = this->checkCompilationInputStates();

   // Если параметры в норме, то запускаем процесс
   if (is_normal_states) {
        // Дескриптор вариативных настроек компиляции
        CompileVarSettingsDescriptor settings_desc;
        // Формирование дескриптора
        this->formCompilationVariableSettingsDescriptor(settings_desc);

        // Запуск процесса компиляции в отдельный поток
        std::thread compiler_thread(run_compile, settings_desc, compiler_status_cache, settings, compile_interrupt_buffer);

        // Отсоединение потока(Он должен завершить работу сам)
        compiler_thread.detach();
   }

   // Восстановление фокуса на кнопке запуска
   ui->RunProcessPushButton->setFocus();

}

void MainWindow::on_PickleConvertationCheckBox_stateChanged(int arg1)
{
    // Когда устанавливается новое состояние нужно проверять формат весов.
    on_WeightsPathLineEdit_editingFinished();
}


void MainWindow::on_OutputDirPathLineEdit_editingFinished()
{
    // Проверка существования указанной директории.
    QString current_path(ui->OutputDirPathLineEdit->text());
    if (!boost::filesystem::is_directory(current_path.toStdString())) {
        ui->WrongFmtOutputDirPathLabel->setText("Указанной директории не существует.");
        ui->WrongFmtOutputDirPathLabel->setVisible(true);
    } else {
        ui->WrongFmtOutputDirPathLabel->setVisible(false);
    }
}


void MainWindow::on_OutputDirPathPushButton_clicked()
{
    // Установка нового пути
    QString current_path(ui->OutputDirPathLineEdit->text());
    QString start_path("/home/");

    if (boost::filesystem::is_directory(current_path.toStdString())) start_path = current_path;

    QString path = QFileDialog::getExistingDirectory(this, "Выберите директорию для программ", start_path);

    if (!path.isEmpty())
        ui->OutputDirPathLineEdit->setText(path);

    on_OutputDirPathLineEdit_editingFinished();
}

void MainWindow::statusBufferUpdate() {

    // обновление статус буфферов по таймеру.
    // Пока очередь сообщений не пуста выводим сообщения через контроллер соответствующего окна
    while(!compiler_status_cache->isQueueEmpty()) {
        auto [message, header, color] = compiler_status_cache->getNext();
        compiler_status_controller->writeMessage(message.c_str(), header.c_str(), color);
    }

    while(!runner_status_cache->isQueueEmpty()) {
        auto [message, header, color] = runner_status_cache->getNext();
        runner_status_controller->writeMessage(message.c_str(), header.c_str(), color);
    }
}


void MainWindow::on_RedactJsonPushButton_clicked()
{
    // Редактирование json файла
    // Если формат соответствует и файл существует, то запускаем редактирование файла отдельным потоком
    on_JsonPathLineEdit_editingFinished();
    if (!ui->WrongFmtJsonPathLabel->isVisible()) {
        std::thread edit_thread(redact_file, ui->JsonPathLineEdit->text().toStdString(), FILE_EDITOR);
        edit_thread.detach();
    }
}


void MainWindow::on_CompilerTabButton_clicked()
{
    // Установка состояний виджетов при нажатии
    ui->CompilerTabWidget->setVisible(true);

    ui->RunnerTabWidget->setVisible(false);
}


void MainWindow::on_RunnerTabButton_clicked()
{
    // Установка состояний виджетов при нажатии
    ui->CompilerTabWidget->setVisible(false);
    ui->RunnerTabWidget->setVisible(true);
}

void MainWindow::updateCurrentTime()
{
    // обновление часов на главной панели
    QTime time = QTime::currentTime();
    QString time_str = time.toString("hh:mm:ss");
    ui->CurrentTime->setText(time_str);
}

void MainWindow::on_SettingsButton_stateChanged(int new_state)
{
    // Изменение меню бара при нажатии на кнопку настроек.
    // Если новое состояние 1, то
    if (new_state) {
        // Берем текущую геометрию
        QRect current_geometry = ui->SettingsButton->geometry();
        // Производим сдвиг вверх на 3 размера(3 кнопки настроек)
        QRect new_geometry(
                    current_geometry.x(),
                    current_geometry.y() - 3 * current_geometry.height(),
                    current_geometry.width(),
                    current_geometry.height());
        // Устанавливаем новую геометрию
        ui->SettingsButton->setGeometry(new_geometry);

        // Изменяем видимость кнопок настроек
        ui->CompilerSettingsButton->setVisible(true);
        ui->RunnerSettingsButton->setVisible(true);
        ui->AnalysisSettingsButton->setVisible(true);
    } else {
        // Берем текущую геометрию
        QRect current_geometry = ui->SettingsButton->geometry();
        // Производим сдвиг вниз на 3 размера(3 кнопки настроек)
        QRect new_geometry(
                    current_geometry.x(),
                    current_geometry.y() + 3 * current_geometry.height(),
                    current_geometry.width(),
                    current_geometry.height());
        // Устанавливаем новую геометрию
        ui->SettingsButton->setGeometry(new_geometry);

        // Изменяем видимость кнопок настроек
        ui->CompilerSettingsButton->setVisible(false);
        ui->RunnerSettingsButton->setVisible(false);
        ui->AnalysisSettingsButton->setVisible(false);
    }
    // обновляем окно
    this->update();
}


void MainWindow::on_CompilerSettingsButton_clicked()
{
    // При нажатии на кнопку изменения настроек вызываем соответствующий слот
    compilerSettingsAction();
}


void MainWindow::on_IsRemoteTensor_stateChanged(int is_checked)
{
    if (is_checked) {
        ui->InputTensorPathLabel->setText("Путь к входному тензору на удаленном хосте:");
        ui->ChangeInputTensorPathButton->setEnabled(false);
    } else {
        ui->InputTensorPathLabel->setText("Путь к входному тензору на локальном хосте:");
        ui->ChangeInputTensorPathButton->setEnabled(true);
    }
}


void MainWindow::on_isGenerateTensor_stateChanged(int is_checked)
{
    if(is_checked) {
        ui->GeneratedTensorSizeLabel->setVisible(true);
        ui->TensorSizeLineEdit->setVisible(true);
        ui->GeneratedTensorSavePathLineEdit->setVisible(true);
        ui->GeneratedTensorSavePathLabel->setVisible(true);
        ui->ChangeGeneratedTensorSavePathButton->setVisible(true);
        on_TensorSizeLineEdit_editingFinished();
        on_GeneratedTensorSavePathLineEdit_editingFinished();
    } else {
        ui->GeneratedTensorSizeLabel->setVisible(false);
        ui->TensorSizeLineEdit->setVisible(false);
        ui->GeneratedTensorSavePathLineEdit->setVisible(false);
        ui->GeneratedTensorSavePathLabel->setVisible(false);
        ui->ChangeGeneratedTensorSavePathButton->setVisible(false);
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(false);
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(false);
    }
}


void MainWindow::on_TensorSizeLineEdit_editingFinished()
{
    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->TensorSizeLineEdit->text(), "^[1-9]");
    if (!is_general) {
        ui->WrongFmtGeneratedTensorSizeLabel->setText("Неверный формат");
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(true);
        return;
    } else if (!is_child) {
        ui->WrongFmtGeneratedTensorSizeLabel->setText("Тут не должно быть нуля");
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(true);
        return;
    } else {
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(false);
    }
}

void MainWindow::on_ProgramDirPathLineEdit_editingFinished()
{
    QString current_text(ui->ProgramDirPathLineEdit->text());

    if (!boost::filesystem::is_directory(current_text.toStdString())) {
        ui->WrongFmtProgramDirPathLabel->setVisible(true);
    } else {
        ui->WrongFmtProgramDirPathLabel->setVisible(false);
    }

}

void MainWindow::runnerProgressUpdate() {

    ui->RunnerProgressBar->setValue(runner_progress->getCurrent());

}

void MainWindow::on_ChangeProgramDirPathButton_clicked()
{
    QString current_path(ui->ProgramDirPathLineEdit->text());
    QString start("/home/"); start += getlogin();

    if (boost::filesystem::is_directory(current_path.toStdString())) start = current_path;

    QString new_path = QFileDialog::getExistingDirectory(this,
                                                         "Выберите директорию с программой",
                                                         start);
    if (!new_path.isEmpty()) ui->ProgramDirPathLineEdit->setText(new_path);
    on_ProgramDirPathLineEdit_editingFinished();
}


void MainWindow::on_ChangeInputTensorPathButton_clicked()
{
    QString current_path(ui->InputTensorPathLineEdit->text());
    QString start("/home/"); start += getlogin();

    if (boost::filesystem::is_directory(current_path.toStdString())) start = current_path;

    QString new_path = QFileDialog::getOpenFileName(this,
                                                    "Выберите файл с входным тензором",
                                                    start,
                                                    "Бинарные файлы (*.bin)");
    if (!new_path.isEmpty()) ui->InputTensorPathLineEdit->setText(new_path);
}


void MainWindow::on_ShowCmd0Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd0.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowCmd1Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd1.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowCmd2Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd2.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowCmd3Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd3.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowCmd4Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd4.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowCmd5Button_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd5.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void MainWindow::on_ShowTpuDataButton_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/logs/tpu_data";
    redact_file(file_path.toStdString(), FILE_EDITOR);
}


void MainWindow::on_ShowCacheDataButton_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/logs/CashData";
    redact_file(file_path.toStdString(), FILE_EDITOR);
}


void MainWindow::on_ShowCmdJsonButton_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/cmd.json";
    redact_file(file_path.toStdString(), FILE_EDITOR);
}


void MainWindow::on_ShowMetadataButton_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/metadata.json";
    redact_file(file_path.toStdString(), FILE_EDITOR);
}


void MainWindow::on_ShowOutputTensorButton_clicked()
{
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    QString file_path = program_dir + "/output/output.bin";
    redact_file(file_path.toStdString(), BINARY_EDITOR);
}


void run_programm(const RunnerSettings& settings, ProgressBarBuffer* runner_progress, StatusBufferCache* log) {
    RunnerCore core(settings, runner_progress, log);
    core.runProcess();
}


void MainWindow::on_RunButton_clicked()
{
    runner_progress->setCurrent(runner_progress->getMin());
    ui->RunnerProgressBar->setValue(runner_progress->getMin());

    if (ui->WrongFmtProgramDirPathLabel->isVisible()) {
        runner_status_cache->writeMessage("Проверьте путь к директории с программой.", "auto", MessageColor::error);
        return;
    }

    if (ui->isGenerateTensor->isChecked()) {
        if (ui->WrongFmtGeneratedTensorSizeLabel->isVisible()) {
            runner_status_cache->writeMessage("Проверьте размер генерируемого тензора.",  "auto", MessageColor::error);
            return;
        }

        if (ui->WrongFmtGeneratedTensorSavePathLabel->isVisible()) {
            runner_status_cache->writeMessage("Проверьте путь для сохранения генерируемого тензора.",  "auto", MessageColor::error);
            return;
        }

    }

    RemoteConnectionDesc remote_connection_settings;
    RemoteAuthDialog auth_dialog(this, settings, &remote_connection_settings);

    auth_dialog.show();
    int auth_success = auth_dialog.exec();

    if (!auth_success) {
        return;
    }

    bool is_generate_tensor {ui->isGenerateTensor->isChecked()};
    TensorCreatorSettings tensor_creator_settings;

    if (is_generate_tensor) {
        tensor_creator_settings.tensor_size = ui->TensorSizeLineEdit->text();
        tensor_creator_settings.tensor_save_path = ui->GeneratedTensorSavePathLineEdit->text();
    }

    // Local run
    if (ui->RunMode->currentIndex() == 0) {
        ui->IsRemoteTensor->setChecked(false);
        on_IsRemoteTensor_stateChanged(false);
        LocalRunnerSettings local_settings;
        local_settings.program_directory = ui->ProgramDirPathLineEdit->text();
        local_settings.input_tensor_path = ui->InputTensorPathLineEdit->text();

        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        QString program_name = settings->value("ArchiveName").toString();
        settings->endGroup();
        local_settings.program_name = program_name;

        RunnerSettings settings(local_settings);

        if (is_generate_tensor) {

            settings.is_tensor_create = true;
            settings.tensor_create_settings = tensor_creator_settings;
            settings.local_settings.input_tensor_path = tensor_creator_settings.tensor_save_path;
        }

        std::thread t(run_programm, settings, runner_progress, runner_status_cache);
        t.detach();


    // Remote run
    } else if (ui->RunMode->currentIndex() == 1) {
        RemoteRunnerSettings remote_settings;

        // Input tensor name:
        // 1. Случай когда тензор создается
        // 2. Случай когда тензор находится на локалке
        // 3. Случай когда тензор находится на удаленке
        if (ui->isGenerateTensor->isChecked()) {
            QString tensor_path = ui->GeneratedTensorSavePathLineEdit->text();
            remote_settings.input_tensor_name = tensor_path.split("/").last();
            remote_settings.input_tensor_path = tensor_path;
        } else if (!ui->IsRemoteTensor->isChecked()) {
            QString tensor_path = ui->InputTensorPathLineEdit->text();
            remote_settings.input_tensor_name = tensor_path.split("/").last();
            remote_settings.input_tensor_path = tensor_path;
        } else {
            QString tensor_path = ui->InputTensorPathLineEdit->text();
            remote_settings.input_tensor_name = tensor_path.split("/").last();
            remote_settings.input_tensor_path = tensor_path;
        }

        remote_settings.is_generated_tensor = ui->isGenerateTensor->isChecked();
        remote_settings.is_remote_tensor    = ui->IsRemoteTensor->isChecked();


        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        QString program_name = settings->value("ArchiveName").toString();
        settings->endGroup();

        remote_settings.program_directory = ui->ProgramDirPathLineEdit->text();
        remote_settings.program_name = program_name;

        remote_settings.remote_hosting_ip = remote_connection_settings.host_ip;
        remote_settings.remote_hosting_port = "22";
        remote_settings.username = remote_connection_settings.username;
        remote_settings.userpass = remote_connection_settings.password;

        RunnerSettings settings(remote_settings);

        if (is_generate_tensor) {

            settings.is_tensor_create = true;
            settings.tensor_create_settings = tensor_creator_settings;
            settings.local_settings.input_tensor_path = tensor_creator_settings.tensor_save_path;
        }

        std::thread t(run_programm, settings, runner_progress, runner_status_cache);
        t.detach();
    }

}


void MainWindow::on_GeneratedTensorSavePathLineEdit_editingFinished()
{
    QString current_path = ui->GeneratedTensorSavePathLineEdit->text();
    QStringList splitted = current_path.split('/');
    splitted.removeAt(splitted.size() - 1);
    QString directory = splitted.join('/');
    std::cout << "Tensor:" << directory.toStdString() << std::endl;
    if (!boost::filesystem::is_directory(directory.toStdString())) {
        ui->WrongFmtGeneratedTensorSavePathLabel->setText("Директории по указанному пути не существует.");
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(true);
    } else if (!current_path.endsWith(".bin")){
        ui->WrongFmtGeneratedTensorSavePathLabel->setText("Ожидаемый формат файла: *.bin");
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(true);
    } else {
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(false);
    }
}


void MainWindow::on_ChangeGeneratedTensorSavePathButton_clicked()
{
    QString current_text = ui->GeneratedTensorSavePathLineEdit->text();

    QString new_path = QFileDialog::getSaveFileName(this, "Выберите путь для сохранения тензора", current_text);
    if (!new_path.isEmpty()) {
        ui->GeneratedTensorSavePathLineEdit->setText(new_path);
    }
    on_GeneratedTensorSavePathLineEdit_editingFinished();
}

