/**
 * @file mainwindow.cpp
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Реализация класса MainWindow и вспомогательных функций для его работы.
 * @version 1.0
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
* ------------------------------------------------------------------------------------------
*                                    Включения
* ------------------------------------------------------------------------------------------
*/
// Header файл класса
#include "mainwindow.h"

// Пользовательские файлы
#include "include/settings_config.h"
#include "include/wrong_fmt_captures.h"
#include "include/compile_errors.h"
#include "include/runner_errors.h"
#include "lib/controllers/statusbar_controller.h"
#include "lib/correct_checkers/compile_runner_preprocessor.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "lib/buffers/settingsbuffer.h"
#include "lib/runner_core/runnercore.h"

// UI интерфейсы
#include "./ui_mainwindow.h"
#include "ui/remote_auth_dialog.h"
#include "ui/welcome_form.h"
#include "ui/compiler_settings_dialog.h"

// Boost library includes
#include <boost/filesystem/operations.hpp>
#include <boost/process/posix.hpp>
#include <boost/process.hpp>

// Standard Library includes
#include <iostream>
#include <unistd.h>

// Qt library includes
#include <QFileDialog>
#include <QTime>


/*
* ------------------------------------------------------------------------------------------
*                          Функции для многопоточной работы
* ------------------------------------------------------------------------------------------
*/

/**
 * @brief Функция для запуска процесса компиляции в мультипоточном режиме.
 * @details Запускает процесс компиляции с переданными параметрами.
 * Предназначена для запуска в отдельном потоке. И реализует простейшую обертку для запуска
 * работы класса.
 * 
 * @param settings_desc - Дескриптор настроек собранных с окна CompilerTab
 * @param status_bar - Кэш статус бара для вывода лога компиляции.
 * @param settings - Общий буффер настроек
 * @param interrupt_buffer - буффер для прерывания потока. (Не работает в версии 1.0)
 */
void run_compile(
    const CompileVarSettingsDescriptor& settings_desc,             
    StatusBufferCache* status_bar,
    SettingsBuffer* settings,
    InterruptBuffer* interrupt_buffer
    )
{

    CompileRunnerProcessor runner(settings_desc, status_bar, settings, interrupt_buffer);
    runner();

}

/**
 * @brief Запуск программы на удаленном или локальном хостинге.
 * @details Запускает программу с переданными параметрами.
 * Предназначена для запуска в отдельном потоке. И реализует простейшую обертку для запуска
 * работы класса.
 * 
 * @param settings - Общие настройки модуля RunnerCore.
 * @param runner_progress - Буффер Progress bar'a вкладки Runner Tab. 
 * @param log - Кэш Status Buffer'a для логирования процесса выполнения программы.
 */
void run_programm(
    const RunnerSettings& settings, 
    ProgressBarBuffer* runner_progress, 
    StatusBufferCache* log
) 
{

    RunnerCore core(settings, runner_progress, log);
    core.runProcess();

}


/**
 * @brief Открытие файла на редактирование в многопоточном режиме.
 * @details Открывает переданный путь на выполнение путем отправки команды системе.
 * 
 * @param path - Путь к файлу
 * @param redactor - Команда запуска конкретного редактора. (For Ex: code -r)
 */
void open_for_edit(
    const std::string& path, 
    const std::string& redactor
    ) 
{

    // Предварительная подготовка пути при содержании пробелов.
    
    // Подготовленный к запуску формат пути.
    std::string prepared_path(path);

    // Если путь содержит пробелы, то запускаем предподготовку
    if (path.find(' ') != std::string::npos) 
    {
    
        // Разбиение пути на части.
        QStringList path_items = QString::fromStdString(prepared_path).split('/');
        
        // Проход по составляющим пути и оборачивание составляющих содержащих пробел
        // в кавычки: "dir name" 
        for (size_t index = 0; index < path_items.size(); index++) 
        {
        
            if (path_items[index].count(' ')) 
            {
            
                QString new_item("\""); 
                new_item += path_items[index];
                new_item += "\"";
                
                path_items[index] = new_item;
            
            }
        
        }

        // Склейка нового пути.
        prepared_path = path_items.join('/').toStdString();
    
    }

    // Формирование команды запуска
    std::string exec(redactor); exec += " "; exec += prepared_path;

    // pipe для потоков вывода
    boost::process::ipstream stdoutput, stderror;

    // Запуск процесса
    int retcode = boost::process::system(
                exec,
                boost::process::std_out > stdoutput,
                boost::process::std_err > stderror
    );
}



/*
* ------------------------------------------------------------------------------------------
*                          Реализация MainWindow. Public Methods.
* ------------------------------------------------------------------------------------------
*/


/**
 * @brief Construct a new Main Window:: Main Window object
 * @details Инициализирует главное окно и выделяет ресурсы под внутренние данные.
 * @param parent - Радительское окно.
 */
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

/**
 * @brief Destroy the Main Window:: Main Window object
 * @details Дополнительно вызывает метод MainWindow:: saveUiStates()
 * для сохранения состояний виджетов.
 */
MainWindow::~MainWindow()
{
    // Сохраняет состояние виджетов
    this->saveUiStates();

    // Освобождает ресурсы
    delete compiler_status_controller;
    delete compiler_status_cache;
    delete runner_status_controller;
    delete runner_status_cache;
    delete settings;
    delete ui;
}


/**
 * @brief Запуск первичной инициализации ПО
 * @details Данный метод позволяет инициализировать ПО.
 * Вызов этого метода происходит при любом сценарии запуска
 * главного окна. В случае, если первичная инициализация уже проходила, то
 * этот метод обновит поле is_first_run_inited. и вернет работу вызвавшему методу.
 * Если инициализация ранее не проходила и соответсвующее поле не было выставлено в настройках,
 * то метод запустит Welcome Form и проведет первичную инициализацию ПО.
 */
bool MainWindow::isFirstRunInited() {
    // Возвращаем флаг
    return is_first_run_inited;
};


/*
* ------------------------------------------------------------------------------------------
*                          Реализация MainWindow. Private Methods.
* ------------------------------------------------------------------------------------------
*/


/**
 * @brief Запуск первичной инициализации ПО
 * @details Данный метод позволяет инициализировать ПО.
 * Вызов этого метода происходит при любом сценарии запуска
 * главного окна. В случае, если первичная инициализация уже проходила, то
 * этот метод обновит поле is_first_run_inited. и вернет работу вызвавшему методу.
 * Если инициализация ранее не проходила и соответсвующее поле не было выставлено в настройках,
 * то метод запустит Welcome Form и проведет первичную инициализацию ПО.
 */
void MainWindow::firstRunInit() {

    // Открываем глобальные настройки
    settings->beginGroup(GLOBAL_SETTINGS_GROUP);

    // Проверка наличия флага инициализации в глобальных настройках.
    bool is_inited = settings->value(
                        GlobalSettingName::isFirstRunInited, 
                        false
                    ).toBool();

    settings->endGroup();

    // Если ранее приложение не запускалось
    if (!is_inited) 
    {
    
        // Создание welcome формы
        WelcomeWizard welcome_wizard(this, settings);
        
        welcome_wizard.show();
        
        int return_code = welcome_wizard.exec();

        // Если код возврата не нулевой, то была нажата кнопка finish
        bool is_welcome_inited = (return_code != 0);

        // Устанавливаем новое значение в настройках
        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        settings->setValue(GlobalSettingName::isFirstRunInited, is_welcome_inited);
        settings->endGroup();

        // Устанавливаем новое значение флагу
        is_first_run_inited = is_welcome_inited;

    } else {

        // В случае, когда инициализация уже проводилась нужно выставить флаг true
        is_first_run_inited = true;
    
    }

}


/**
 * @brief Общий метод инициализации главного окна
 * @details Вызывает группу методов, отвечающих за инициализацию интерфейса
 */
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


/**
 * @brief Инициализация таймеров главного окна
 * @details Инициализирует работу таймеров главного окна
 * запускает таймеры, устанавливает период обновлений и 
 * связывает слоты с таймерами.
 */
void MainWindow::initTimer() 
{
    
    // Установка интервала для таймеров обновлений
    update_timer->setInterval(UPDATE_WINDOW_LATENCY_MS);
    update_runner_fast_panel_timer->setInterval(UPDATE_RUNNER_FAST_PANEL_LATENCY_MS);


    // ----------------------------------------
    // Подключение таймеров к слотам
    // ----------------------------------------

    // Таймер для обновление статус баров
    connect(update_timer, 
            SIGNAL(timeout()), 
            this, 
            SLOT(statusBufferUpdate())
        );
    
    // Таймер для обновления текущего времени
    connect(update_timer, 
            SIGNAL(timeout()), 
            this, 
            SLOT(updateCurrentTime())
        );
    
    // таймер для обновления прогресс бара вкладки Runner Tab
    connect(update_timer, 
            SIGNAL(timeout()), 
            this, 
            SLOT(runnerProgressUpdate())
        );
    
    // Таймер для обновления панели быстрого доступа
    connect(update_runner_fast_panel_timer, 
            SIGNAL(timeout()), 
            this, 
            SLOT(initUiRunnerPanelStates())
        );



    // Запуск работы таймера
    update_timer->start();
    update_runner_fast_panel_timer->start();

}


/**
 * @brief Инициализация Status Bar'ов главного окна
 * @details Выделяет ресурсы под контроллеры и cache
 * статус баров всех вкладок
 */
void MainWindow::initStatusBars() 
{

    // Кэш статус бара для компиляции
    compiler_status_cache = new StatusBufferCache();

    // Инициализация контроллера статус бара компилятора
    compiler_status_controller = new StatusBarController(ui->CompilerStatusBar);

    // Кэш статус бара для окна запуска программ
    runner_status_cache = new StatusBufferCache();

    // Статус бар контроллер для окна запуска программ
    runner_status_controller = new StatusBarController(ui->RunnerStatusBar);

}


/**
 * @brief Инициализация индикаторов неверного формата ввода
 * @details Запускает методы инициализирующие индикаторы неверного
 * формата ввода для всех вкладок UI
 */
void MainWindow::initWrongFormatIndicators()
{
    // Инициализация индикаторов вкладки Compiler Tab
    this->initCompilerTabWrongFormatIndicators();

    // Инициализация индикаторов вкладки Runner Tab
    this->initRunnerTabWrongFormatIndicators();
    
}

/**
 * @brief Инициализация индикаторов неверного формата ввода для вкладки Compiler Tab
 * @details Вызывает все методы, которые проверяют корректность введенных данных
 */
void MainWindow::initCompilerTabWrongFormatIndicators()
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

/**
 * @brief Инициализация индикаторов неверного формата ввода для вкладки Runner Tab
 * @details Вызывает все методы, которые проверяют корректность введенных данных
 */
void MainWindow::initRunnerTabWrongFormatIndicators()
{

    on_ProgramDirPathLineEdit_editingFinished();
    on_GeneratedTensorSavePathLineEdit_editingFinished();

}


/**
 * @brief Инициализация состояний UI интерфеса
 * @details Запускает методы инициализации состояний интерфейса пользователя
 * для всех вкладок и главного окна.
 * 
 * Вызываемые методы:
 * MainWindow:: initUiCompilerTabStates() 
 * MainWindow:: initUiRunnerTabStates()
 * MainWindow:: initUiAnalysisTabStates()
 */
void MainWindow::initUiStates() 
{

    // Инициализация состояний CompilerTab
    this->initUiCompilerTabStates();

    // Инициализация состояний Runner Tab
    this->initUiRunnerTabStates();

    // Инициализация состояний Analysis Tab
    this->initUiAnalysisTabStates();

    // Инициализация начального состояния виджетов
    ui->CompilerTabWidget->setVisible(true);
    ui->CompilerTabButton->setChecked(true);
    ui->RunnerTabWidget->setVisible(false);

    // Инициализация начального состояния Settings Menu
    ui->SettingsButton->setChecked(false);
    ui->CompilerSettingsButton->setVisible(false);
    ui->RunnerSettingsButton->setVisible(false);
    ui->AnalysisSettingsButton->setVisible(false);

}

/**
 * @brief Инициализация состояний UI интерфейса вкладки CompilerTab
 * @details Инициализирует состояния интерфейса вкладки CompilerTab
 * из настроек. И определяет видимость виджетов в зависимости от 
 * корректности данных и состояний иных виджетов.
 * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
 */
void MainWindow::initUiCompilerTabStates() 
{

    // Переход в группу настроек
    settings->beginGroup(COMPILER_SETTINGS_GROUP);

    // Line Edits
    QString json_path = settings->value(
                            ui->JsonPathLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::user_folder)
                        ).toString();

    QString weights_path = settings->value(
                            ui->WeightsPathLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::user_folder)
                        ).toString();
    
    QString output_path = settings->value(
                            ui->OutputDirPathLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::user_folder)
                        ).toString();
    
    QString program_directory_name = settings->value(
                            ui->CatalogNameLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::program_dir)
                        ).toString();
    
    QString input_size = settings->value(
                            ui->InputSizeEditLine->objectName(), 
                            QString(CompilerSettingsDefault::tensor_size)
                        ).toString();
    
    QString output_size = settings->value(
                            ui->OutputSizeLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::tensor_size)
                        ).toString();
    
    QString input_pad_up = settings->value(
                            ui->InputPadUpLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::paddings)
                        ).toString();
    
    QString input_pad_down = settings->value(
                            ui->InputPadDownLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::paddings)
                        ).toString();
    
    QString output_pad_up = settings->value(
                            ui->OutputPadUpLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::paddings)
                        ).toString();
    
    QString output_pad_down = settings->value(
                            ui->OutputPadDownLineEdit->objectName(), 
                            QString(CompilerSettingsDefault::paddings)
                        ).toString();



    // Check Boxes
    bool is_add_compilation_logs     = settings->value(ui->AddCompilationLogCheckBox->objectName(), true).toBool();
    bool is_add_bias_preload         = settings->value(ui->AddBiasPreloadCheckBox->objectName(), true).toBool();
    bool is_add_input_optimization   = settings->value(ui->AddInputOptimizationCheckBox->objectName(), true).toBool();
    bool is_add_reorder_optimization = settings->value(ui->AddReorderOptimizationCheckBox->objectName(), true).toBool();
    bool is_add_debug_mode           = settings->value(ui->AddDebugModeCheckBox->objectName(), true).toBool();
    bool is_convert_json             = settings->value(ui->JsonConvertationCheckBox->objectName(), false).toBool();
    bool is_convert_pickle           = settings->value(ui->PickleConvertationCheckBox->objectName(), true).toBool();
    bool is_check_addresses          = settings->value(ui->AddressCheckCheckBox->objectName(), true).toBool();
    bool is_compile_program          = settings->value(ui->CompileProgrammCheckBox->objectName(), true).toBool();
    bool is_make_archive             = settings->value(ui->MakeArchiveCheckBox->objectName(), true).toBool();
    bool is_make_metadata            = settings->value(ui->MakeMetadataCheckBox->objectName(), true).toBool();
    bool is_preload_filters          = settings->value(ui->AddFilterPreloadCheckBox->objectName(), true).toBool();


    // Combo Boxes
    unsigned int device_index = settings->value(ui->DeviceComboBox->objectName(), 0).toUInt();

    settings->endGroup();



    // Обновление состояний
    // Line Edits
    ui->JsonPathLineEdit     ->setText(json_path);
    ui->WeightsPathLineEdit  ->setText(weights_path);
    ui->OutputDirPathLineEdit->setText(output_path);
    ui->CatalogNameLineEdit  ->setText(program_directory_name);
    ui->InputSizeEditLine    ->setText(input_size);
    ui->OutputSizeLineEdit   ->setText(output_size);
    ui->InputPadDownLineEdit ->setText(input_pad_down);
    ui->InputPadUpLineEdit   ->setText(input_pad_up);
    ui->OutputPadDownLineEdit->setText(output_pad_down);
    ui->OutputPadUpLineEdit  ->setText(output_pad_up);

    // Check Boxes
    ui->AddCompilationLogCheckBox     ->setChecked(is_add_compilation_logs);
    ui->AddBiasPreloadCheckBox        ->setChecked(is_add_bias_preload);
    ui->AddInputOptimizationCheckBox  ->setChecked(is_add_input_optimization);
    ui->AddReorderOptimizationCheckBox->setChecked(is_add_reorder_optimization);
    ui->AddDebugModeCheckBox          ->setChecked(is_add_debug_mode);
    ui->JsonConvertationCheckBox      ->setChecked(is_convert_json);
    ui->PickleConvertationCheckBox    ->setChecked(is_convert_pickle);
    ui->AddressCheckCheckBox          ->setChecked(is_check_addresses);
    ui->CompileProgrammCheckBox       ->setChecked(is_compile_program);
    ui->MakeArchiveCheckBox           ->setChecked(is_make_archive);
    ui->MakeMetadataCheckBox          ->setChecked(is_make_metadata);
    ui->AddFilterPreloadCheckBox      ->setChecked(is_preload_filters);

    // Combo Boxes
    ui->DeviceComboBox->setCurrentIndex(device_index);

    // Other States
    ui->JsonConvertationCheckBox->setEnabled(false);

}

/**
 * @brief Инициализация состояний UI интерфейса вкладки Runner Tab
 * @details Инициализирует состояния интерфейса вкладки Runner Tab
 * из настроек. И определяет видимость виджетов в зависимости от 
 * корректности данных и состояний иных виджетов.
 * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
 */
void MainWindow::initUiRunnerTabStates() 
{
    // Входим в группу настроек
    settings->beginGroup(RUNNER_SETTINGS_GROUP);

    // Считывание сохраненных состояний
    QString program_dir       = settings->value(
                                    ui->ProgramDirPathLineEdit->objectName(), 
                                    RunnerSettingsDefault::user_folder
                                ).toString();

    QString input_tensor_path = settings->value(
                                    ui->InputTensorPathLineEdit->objectName(), 
                                    RunnerSettingsDefault::user_folder
                                ).toString();

    QString input_tensor_size = settings->value(
                                    ui->TensorSizeLineEdit->objectName(), 
                                    RunnerSettingsDefault::tensor_size
                                ).toString();

    QString input_tensor_save = settings->value(
                                    ui->GeneratedTensorSavePathLineEdit->objectName(), 
                                    RunnerSettingsDefault::tensor_path).toString();

    bool is_remote_tensor     = settings->value(ui->IsRemoteTensor->objectName(),   true).toBool();
    bool is_generate_tensor   = settings->value(ui->isGenerateTensor->objectName(), false).toBool();

    settings->endGroup();


    // Обновление состояний виджетов
    ui->ProgramDirPathLineEdit         ->setText(program_dir);
    ui->InputTensorPathLineEdit        ->setText(input_tensor_path);
    ui->TensorSizeLineEdit             ->setText(input_tensor_size);
    ui->GeneratedTensorSavePathLineEdit->setText(input_tensor_save);
    
    // Check Boxes States
    ui->IsRemoteTensor                 ->setChecked(is_remote_tensor);
    ui->isGenerateTensor               ->setChecked(is_generate_tensor);

    // Обновление состояний зависимых виджетов
    on_IsRemoteTensor_stateChanged(ui->IsRemoteTensor->isChecked());
    on_isGenerateTensor_stateChanged(ui->isGenerateTensor->isChecked());
    
    // Сброс и установка настроек бара прогресса
    ui->RunnerProgressBar->setValue(runner_progress->getCurrent());
    ui->RunnerProgressBar->setMaximum(runner_progress->getMax());
    ui->RunnerProgressBar->setMinimum(runner_progress->getMin());

}

/**
 * @brief Инициализация состояний UI интерфейса вкладки Analysis Tab
 * @details Инициализирует состояния интерфейса вкладки Analysis Tab
 * из настроек. И определяет видимость виджетов в зависимости от 
 * корректности данных и состояний иных виджетов.
 * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
 * @warning В версии 1.0 не реализовано в связи с отсутствием вкладки Analysis Tab
 */
void MainWindow::initUiAnalysisTabStates() {
    // TODO To do Task
}

/**
 * @brief Проверка формата введенных размеров.
 * @details Проверяет форматы по регулярному выражению "^(-?\\d+),(-?\\d+),(-?\\d+),(-?\\d+)$"
 * Опционально возможно применение регулярного выражения ко всем элементам списка.
 * При проверке не учитывает присутствие пробелов.
 * 
 * @param text Строка с введенным текстом.
 * @param items_regex Регулярное выражение для отдельных элеменов списка. По умолчанию - пустое.
 * @return std::pair<bool, bool> Возвращает пару значений. Первый элемент - соответствие главному регулярному выражению.
 * Второй элемент - соответствие дочернему регулярному выражению, если оно не пустое. В случае когда дочернее регулярное
 * выражение пустое метод возвращает во втором поле true
 */
std::pair<bool, bool> MainWindow::checkSizesFormat(
                                    const QString& text, 
                                    QString items_regex
                                ) 
{

    // Основное регулярное выражение
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
    if (is_matched && !items_regex.isEmpty()) 
    {
    
        // Регулярное выражение для айтемов
        QRegularExpression digit_rx(items_regex);
    
        // Разделение по запятой
        QStringList digits = text_copy.split(',');
    
        // Проверка соответствия каждого элемента выражению
        for (const auto& digit : digits) 
        {
        
            if (!(digit_rx.match(digit).hasMatch())) 
            {
            
                is_matched_child = false;
                break;
            
            }
        
        }
    
    }

    // Возврат пары
    return {is_matched, is_matched_child};

}


/**
 * @brief Проверка правильности введенных настроек при запуске процесса компиляции
 * @details Метод проверяет видимость индикаторов неверного формата ввода.
 * В случае, когда один из индикаторов виден, то в лог(Status Cache) выводится соответствующее
 * сообщение об ошибке.
 * 
 * @return true  - Все индикаторы неверного формата ввода скрыты и можно продолжать процесс компиляции.
 * @return false - Один из индикаторов неверного формата ввода виден, значит процесс нужно остановить.
 */
bool MainWindow::checkCompilationInputStates() 
{

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
    if (ui->WrongFmtJsonPathLabel->isVisible()) 
    {
    
        compiler_status_cache->writeMessage(CompileError::JSON_NOT_FOUND);
        return false;
    
    }
    
    
    // Если показан индикатор для Weights пути
    if (ui->WrongFmtWeightsPathLabel->isVisible()) 
    {
    
        compiler_status_cache->writeMessage(CompileError::WEIGHTS_NOT_FOUND);
        return false;
    
    }

    // Проверка соответствия формата весов пайплайну компиляции
    QString weights_path(ui->WeightsPathLineEdit->text());
    QString expected_weights_format = (ui->PickleConvertationCheckBox->isChecked()) ? (".pickle") : (".bin");

    // Если путь к файлу с весами заканчивается с неверным форматом.
    if (!(weights_path.endsWith(expected_weights_format))) 
    {
    
        compiler_status_cache->writeMessage(CompileError::WRONG_WEIGHTS_FORMAT);
        return false;
    
    }

    // Если неверно указано имя каталога
    if (ui->WrongFmtCatalogNameLabel->isVisible()) 
    {
    
        compiler_status_cache->writeMessage(CompileError::WRONG_CATALOG_NAME);
        return false;
    
    }

    // Если неверно указан размер входного тензора
    if (ui->WrongFmtInputSizeLabel->isVisible()) 
    {
    
        compiler_status_cache->writeMessage(CompileError::WRONG_INPUT_SIZE);
        return false;
    
    }

    // Если неверно указан размер выходного тензора
    if(ui->WrongFmtOutputSizeLabel->isVisible())
    {
        compiler_status_cache->writeMessage(CompileError::WRONG_OUTPUT_SIZE);
        return false;
    }

    // Если неверно указано одно из полей паддингов
    if (ui->WrongFmtInputPadDownLabel->isVisible()  ||
        ui->WrongFmtInputPadUpLabel->isVisible()    ||
        ui->WrongFmtOutputPadDownLabel->isVisible() ||
        ui->WrongFmtOutputPadUpLabel->isVisible()
        ) 
    {
    
        compiler_status_cache->writeMessage(CompileError::WRONG_PADDINGS_FORMAT);
        return false;
    
    }

    // В случае когда все проверки пройдены возвращается True
    return true;
}

/**
 * @brief Формирование дескриптора вариативных настроек компиляции.
 * @details Формирует дескриптор настроек компиляции, которые указываются во вкладке 
 * Compiler Tab. 
 * 
 * @param settings_desc - Дескриптор настроек. Ссылка на дескриптор настроек, который будет заполнен.
 */
void MainWindow::formCompilationVariableSettingsDescriptor(CompileVarSettingsDescriptor& settings_desc) 
{

    settings_desc.json_path    = ui->JsonPathLineEdit->text();
    settings_desc.weights_path = ui->WeightsPathLineEdit->text();
    settings_desc.output_directory_path = ui->OutputDirPathLineEdit->text();
    settings_desc.output_directory_name = ui->CatalogNameLineEdit->text();
    settings_desc.input_size      = ui->InputSizeEditLine->text().remove(" ");
    settings_desc.output_size     = ui->OutputSizeLineEdit->text().remove(" ");
    settings_desc.input_pad_up    = ui->InputPadUpLineEdit->text().remove(" ");
    settings_desc.output_pad_up   = ui->OutputPadUpLineEdit->text().remove(" ");
    settings_desc.input_pad_down  = ui->InputPadDownLineEdit->text().remove(" ");
    settings_desc.output_pad_down = ui->OutputPadDownLineEdit->text().remove(" ");
    settings_desc.is_input_optimization  = ui->AddInputOptimizationCheckBox->isChecked();
    settings_desc.is_add_logs            = ui->AddCompilationLogCheckBox->isChecked();
    settings_desc.is_preload_bias_scales = ui->AddBiasPreloadCheckBox->isChecked();
    settings_desc.is_preload_filters   = ui->AddFilterPreloadCheckBox->isChecked();
    settings_desc.is_reorder_data      = ui->AddReorderOptimizationCheckBox->isChecked();
    settings_desc.device_index         = ui->DeviceComboBox->currentIndex();
    settings_desc.pipe_json_convert    = ui->JsonConvertationCheckBox->isChecked();
    settings_desc.pipe_weights_convert = ui->PickleConvertationCheckBox->isChecked();
    settings_desc.pipe_address_check   = ui->AddressCheckCheckBox->isChecked();
    settings_desc.pipe_compile         = ui->CompileProgrammCheckBox->isChecked();
    settings_desc.pipe_create_metadata = ui->MakeMetadataCheckBox->isChecked();
    settings_desc.pipe_make_output     = ui->MakeArchiveCheckBox->isChecked();

}

/**
 * @brief Сохранение состояний виджетов UI.
 * @details Вызывает методы сохранения состояний для всех вкладок
 * и обновляет буффер настроек.
 * Вызываемые методы: saveUiCompilerTabStates(), saveUiRunnerTabStates()
 */
void MainWindow::saveUiStates() 
{

    // Сохранение вкладки Compiler Tab
    saveUiCompilerTabStates();

    // Сохранение вкладки Runner Tab
    saveUiRunnerTabStates();

}


/**
 * @brief Метод сохранения состояний вкладки Compiler Tab
 * @details Сохраняет состояния виджетов в настройки. Вызывается из saveUiStates()
 */
void MainWindow::saveUiCompilerTabStates() 
{

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

/**
 * @brief Метод сохранения состояний вкладки Runner Tab
 * @details Сохраняет состояния виджетов в настройки. Вызывается из saveUiStates()
 */
void MainWindow::saveUiRunnerTabStates() 
{
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




/*
* ------------------------------------------------------------------------------------------
*                 Реализация MainWindow. Private Methods [SLOTS].
*                    Пользовательские слоты не генерируемые Qt
* ------------------------------------------------------------------------------------------
*/

/**
 * @brief Обновление статус буффера в текущей вкладке
 * @details Данный слот обновляет статус бар текущей вкладки
 * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
 */
void MainWindow::statusBufferUpdate() {

    // Пока очередь сообщений не пуста выводим сообщения через контроллер соответствующего окна
    
    // Compiler Tab
    while(!compiler_status_cache->isQueueEmpty()) 
    {
    
        auto [message, header, color] = compiler_status_cache->getNext();
        compiler_status_controller->writeMessage(message.c_str(), header.c_str(), color);
    
    }

    // Runner Tab
    while(!runner_status_cache->isQueueEmpty()) 
    {
    
        auto [message, header, color] = runner_status_cache->getNext();
        runner_status_controller->writeMessage(message.c_str(), header.c_str(), color);
    
    }

}

/**
 * @brief Обновление текущего времени на главной панели.
 * @details Данный слот обновляет текущее время
 * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
 */
void MainWindow::updateCurrentTime()
{

    // обновление часов на главной панели
    ui->CurrentTime->setText(
        QTime::currentTime().toString("hh:mm:ss")
    );

}

/**
 * @brief Обновление прогресс бара во вкладке Runner Tab
 * @details Данный слот обновляет progress bar вкладки Runner Tab
 * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
 */
void MainWindow::runnerProgressUpdate() {

    ui->RunnerProgressBar->setValue(runner_progress->getCurrent());

}

/**
 * @brief Обновление панели быстрого доступа во вкладке Runner Tab
 * @details Данный слот обновляет панель быстрого доступа вкладки Runner Tab
 * по таймеру. Частота обновлений указана в #define UPDATE_RUNNER_FAST_PANEL_LATENCY_MS
 */
void MainWindow::initUiRunnerPanelStates()
{

    // Если текущая вкладка - Runner Tab, то проверяем доступ
    if (ui->RunnerTabButton->isChecked()) 
    {

        // Если путь к директории указанной в настройках существует, то проверяем
        if (!ui->WrongFmtProgramDirPathLabel->isVisible()) 
        {
        
            // Флаги которые отмечают найденные файлы
            bool is_cmd0bin_found(false), is_cmdjson_found(false),
                 is_cmd1bin_found(false), is_metadata_found(false),
                 is_cmd2bin_found(false), is_cache_data_found(false),
                 is_cmd3bin_found(false), is_tpu_data_found(false),
                 is_cmd4bin_found(false), is_output_found(false),
                 is_cmd5bin_found(false);

            // Директории в которых происходит поиск
            QString program_dir(ui->ProgramDirPathLineEdit->text());
            QString logs_dir = program_dir + "/logs";
            QString output_dir = program_dir + "/output";

            // Выставление файлов
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

            // Обновление состояний кнопок в зависимости от результатов поиска
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


/**
 * @brief Слот вызываемый при нажатии на кнопку Compiler Settings.
 * @details Данный слот вызывает окно Compiler Settings Dialog
 * и отвечает за обновление статичных настроек компиляции.
 */
void MainWindow::compilerSettingsAction()
{

    // Открываем диалговое окно
    CompilerSettingsDialog dialog(this, settings);

    // Показываем его и ждем возврата
    dialog.show();

    // Код возврата диалогового окна
    int ret_code = dialog.exec();

}




/*
* ------------------------------------------------------------------------------------------
*                 Реализация MainWindow. Private Methods [SLOTS].
*                            Слоты генерируемые Qt
* ------------------------------------------------------------------------------------------
*/



/**
 * @brief Проверка корректности введенного пути к описанию сети
 */
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
    if (is_exist && is_json) 
    {
    
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

/**
 * @brief Проверка корректности введенного пути к файлу с весами сети
 * и проверка на соответствие формата пайплайну
 */
void MainWindow::on_WeightsPathLineEdit_editingFinished()
{
    // Проверка существования файла

    // Путь указанный в LineEdit
    QString path = ui->WeightsPathLineEdit->text();

    // Ожидаемый формат файла
    QString current_format;

    if (ui->PickleConvertationCheckBox->isChecked()) current_format = ".pickle";
    else                                             current_format = ".bin";

    // Если файл существует
    bool is_exist = boost::filesystem::is_regular_file(path.toStdString());
    
    // Если файл нужного формата
    bool is_weights = path.toLower().endsWith(current_format);

    // Если файл нормальный, то выставляем видимость в false и выходим
    if (is_exist && is_weights) 
    {
    
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

/**
 * @brief Проверка каталога на содержание недопустимых для ОС символов
 */
void MainWindow::on_CatalogNameLineEdit_editingFinished()
{
    // Проверка имени директории на допустимый формат ОС

    // Недопустимые символы
    QString wrong_symbols("*|:\"<>?/\\");
    
    // Флаг соответствия имени директории формату
    bool is_wrong = false;

    // Проходимся по символам. Если имеются плохие значения, то выставляем флаг
    for(const QChar& sym : ui->CatalogNameLineEdit->text()) 
    {
        
        if (wrong_symbols.contains(sym)) 
        {
    
            is_wrong = true;
            break;
    
        }
    
    }

    // Если формат не допустимый, то устанавливаем индикатор
    if (is_wrong) 
    {
    
        ui->WrongFmtCatalogNameLabel->setText(WRONG_FMT_TEXT::bad_dir_format);
        ui->WrongFmtCatalogNameLabel->setVisible(true);
    
    } else
        ui->WrongFmtCatalogNameLabel->setVisible(false);
}

/**
 * @brief Проверка корректности введенных размеров
 * @details Введенные размеры должны быть: Больше или равны 1, перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_InputSizeEditLine_editingFinished()
{

    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->InputSizeEditLine->text(), "^[1-9]");
    
    // Если не прошло основное регулярное выражение.
    if (!is_general) 
    {
    
        ui->WrongFmtInputSizeLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtInputSizeLabel->setVisible(true);
        return;
    
    // Если содерджит отрицательные значения или нули
    } else if (!is_child) 
    {
    
        ui->WrongFmtInputSizeLabel->setText(WRONG_FMT_TEXT::zero_value);
        ui->WrongFmtInputSizeLabel->setVisible(true);
        return;
    
    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtInputSizeLabel->setVisible(false);
    
    }

}

/**
 * @brief Проверка корректности введенных паддингов
 * @details Введенные размеры должны быть: перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_InputPadUpLineEdit_editingFinished()
{

    // Проверка на соответсвие формату ввода
    auto [is_general, ignored] = checkSizesFormat(ui->InputPadUpLineEdit->text());
    
    // Если проверка не пройдена
    if (!is_general) 
    {
    
        ui->WrongFmtInputPadUpLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtInputPadUpLabel->setVisible(true);
        return;
    
    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtInputPadUpLabel->setVisible(false);
    
    }
}

/**
 * @brief Проверка корректности введенных паддингов
 * @details Введенные размеры должны быть: перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_InputPadDownLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->InputPadDownLineEdit->text());

    // Если проверка не пройдена
    if (!is_general) 
    {
    
        ui->WrongFmtInputPadDownLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtInputPadDownLabel->setVisible(true);
        return;

    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtInputPadDownLabel->setVisible(false);
    
    }
}

/**
 * @brief Проверка корректности введенных размеров
 * @details Введенные размеры должны быть: Больше или равны 1, перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_OutputSizeLineEdit_editingFinished()
{
    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputSizeLineEdit->text(), "^[1-9]");

    // Если не прошло основное регулярное выражение.
    if (!is_general) 
    {
    
        ui->WrongFmtOutputSizeLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtOutputSizeLabel->setVisible(true);
        return;
    
    // Если содерджит отрицательные значения или нули
    } else if (!is_child) 
    {
    
        ui->WrongFmtOutputSizeLabel->setText(WRONG_FMT_TEXT::zero_value);
        ui->WrongFmtOutputSizeLabel->setVisible(true);
        return;
    
    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtOutputSizeLabel->setVisible(false);
    
    }
}

/**
 * @brief Проверка корректности введенных паддингов
 * @details Введенные размеры должны быть: перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_OutputPadUpLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputPadUpLineEdit->text());

    // Если проверка не пройдена
    if (!is_general) 
    {

        ui->WrongFmtOutputPadUpLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtOutputPadUpLabel->setVisible(true);
        return;
    
    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtOutputPadUpLabel->setVisible(false);
    
    }
}

/**
 * @brief Проверка корректности введенных паддингов
 * @details Введенные размеры должны быть: перечислены
 * через запятую, содержать количество 4 штук (по 1 для каждой оси тензора).
 */
void MainWindow::on_OutputPadDownLineEdit_editingFinished()
{
    // Проверка на соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->OutputPadDownLineEdit->text());
    
    // Если проверка не пройдена
    if (!is_general) 
    {

        ui->WrongFmtOutputPadDownLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtOutputPadDownLabel->setVisible(true);
        return;
    
    // Если проверка пройдена
    } else 
    {
    
        ui->WrongFmtOutputPadDownLabel->setVisible(false);
    
    }
}


/**
 * @brief Открывает диалоговое окно с проводником для поиска JSON файла с описанием сети
 */
void MainWindow::on_ChangeJsonPathPushButton_clicked()
{
    
    // Изменение пути к JSON файлу.
    QString current_path = ui->JsonPathLineEdit->text();

    // Проверка существования текущего пути или пути к директории
    bool is_path_exist = (boost::filesystem::is_regular_file(current_path.toStdString()) ||
                          boost::filesystem::is_directory(current_path.toStdString()));

    // Базовый стартовый путь
    // Если текущий путь существует, то оставляем его. Иначе - стандартный путь
    QString start_path = (is_path_exist) ? (current_path) : (CompilerSettingsDefault::user_folder);

    // Запускаем проводник и ожидаем выбора файла
    QString file = QFileDialog::getOpenFileName(
                    this,
                    "Выбор файла с весами сети",
                    start_path,
                    "Все файлы (*.json)"
                );

    // Если полученный путь не пуст, то устанавливаем новый
    if (!file.isEmpty()) 
        ui->JsonPathLineEdit->setText(file);

}

/**
 * @brief Открывает диалоговое окно с проводником для поиска файла с весами сети
 */
void MainWindow::on_ChangeWeightsPathPushButton_clicked()
{
    // Текущее состояние введенного пути и проверка его существования
    QString current_path = ui->WeightsPathLineEdit->text();
    
    // Проверка существования текущего пути
    bool is_path_exist = (boost::filesystem::is_regular_file(current_path.toStdString()) ||
                          boost::filesystem::is_directory(current_path.toStdString()));
    
    // Базовый путь
    QString start_path = (is_path_exist) ? (current_path) : (CompilerSettingsDefault::user_folder);

    // Запускаем проводник для поиска файлов
    QString file = QFileDialog::getOpenFileName(
                    this,
                    "Выбор файла с весами сети",
                    start_path,
                    "Все файлы (*.bin *.pickle);; Бинарные файлы (*.bin);; Pickle файлы (*.pickle)"
                );

    // Если путь не пуст, то устанавливаем новое состояние и проверяем корректность
    if (!file.isEmpty())
        ui->WeightsPathLineEdit->setText(file);

}


/**
 * @brief Запуск этапа компиляции.
 * @details Метод запускает проверку настроек компиляции.
 * checkCompilationInputStates() проверяет корректность настроек на уровне вкладки
 * 
 * Статичные настройки вводимые в отдельном меню настроек компиляции проверяются
 * на этапе препроцессинга и не относятся к данному методу.
 * 
 * Данный метод инициализирует отдельный поток для запуска процесса компиляции и отсоединяет его
 * от мастер-потока. Таким образом связь с ним поддерживается только в режиме приема
 * в версии 1.0. В дальнейшем планируется добавить возможность прерывания работы.
 */
void MainWindow::on_RunProcessPushButton_clicked()
{

   // Проверка состояний всех введенных пользователем параметров
   bool is_normal_states = this->checkCompilationInputStates();

   // Если параметры в норме, то запускаем процесс
   if (is_normal_states) 
   {
   
        // Дескриптор вариативных настроек компиляции
        CompileVarSettingsDescriptor settings_desc;
   
        // Формирование дескриптора
        this->formCompilationVariableSettingsDescriptor(settings_desc);

        // Запуск процесса компиляции в отдельный поток
        std::thread compiler_thread(run_compile, 
            settings_desc, compiler_status_cache, settings, compile_interrupt_buffer
        );

        // Отсоединение потока(Он должен завершить работу сам)
        compiler_thread.detach();
   
   }

   // Восстановление фокуса на кнопке запуска
   ui->RunProcessPushButton->setFocus();

}

/**
 * @brief Запускает проверку соответствия формата весов при изменении пайплайна компиляции
 * 
 * @param arg1 - Новое состояние. Не используется в реализации, значение не важно.
 */
void MainWindow::on_PickleConvertationCheckBox_stateChanged(int arg1)
{
    // Когда устанавливается новое состояние нужно проверять формат весов.
    on_WeightsPathLineEdit_editingFinished();
}

/**
 * @brief Проверка существования указанного пути
 */
void MainWindow::on_OutputDirPathLineEdit_editingFinished()
{
    
    std::string current_path { ui->OutputDirPathLineEdit->text().toStdString() };

    // Проверка существования указанной директории.
    if (!boost::filesystem::is_directory(current_path)) 
    {
    
        ui->WrongFmtOutputDirPathLabel->setText(WRONG_FMT_TEXT::directory_not_exist);
        ui->WrongFmtOutputDirPathLabel->setVisible(true);
    
    } else 
    {
    
        ui->WrongFmtOutputDirPathLabel->setVisible(false);
    
    }
}

/**
 * @brief Выбор директории для сохранения программы
 */
void MainWindow::on_OutputDirPathPushButton_clicked()
{

    // Установка нового пути
    QString current_path(ui->OutputDirPathLineEdit->text());
    
    // Проверка существования текущего пути
    bool is_path_exist { boost::filesystem::is_directory(current_path.toStdString()) };

    // Базовый путь. Если текущий существует, то он. Иначе - стандартный путь
    QString start_path = (is_path_exist) ? (current_path) : (CompilerSettingsDefault::user_folder);

    // Получаем новый путь.
    QString path = QFileDialog::getExistingDirectory(
                                    this, 
                                    "Выберите директорию для программ", 
                                    start_path
                                );

    // Устанавливаем его, если он существует
    if (!path.isEmpty())
        ui->OutputDirPathLineEdit->setText(path);

}

/**
 * @brief Открытие JSON файла на редактирование
 * @details Редактирование открывается в отдельном потоке, который будет отсоединен от мастер-ветки
 * без возможности передачи сообщений.
 */
void MainWindow::on_RedactJsonPushButton_clicked()
{

    // Обновляем индикатор неверного формата.
    on_JsonPathLineEdit_editingFinished();

    // Если формат соответствует и файл существует, то запускаем редактирование файла отдельным потоком
    if (!ui->WrongFmtJsonPathLabel->isVisible()) 
    {
    
        std::thread edit_thread(open_for_edit, ui->JsonPathLineEdit->text().toStdString(), FILE_EDITOR);
        edit_thread.detach();
    
    }

}

/**
 * @brief Смена вкладки на Compiler Tab
 */
void MainWindow::on_CompilerTabButton_clicked()
{

    // Установка состояний виджетов при нажатии
    ui->CompilerTabWidget->setVisible(true);
    ui->RunnerTabWidget  ->setVisible(false);

}

/**
 * @brief Смена вкладки на Runner Tab
 */
void MainWindow::on_RunnerTabButton_clicked()
{

    // Установка состояний виджетов при нажатии
    ui->CompilerTabWidget->setVisible(false);
    ui->RunnerTabWidget  ->setVisible(true);

}


/**
 * @brief Если произошло нажатие на кнопку SettingsButton, нужно открыть или закрыть вкладки
 * с настройками.
 * @param new_state - новое состояние. 1 - открытие, 0 - закрытие. 
 */
void MainWindow::on_SettingsButton_stateChanged(int new_state)
{

    // Изменение меню бара при нажатии на кнопку настроек.
    // Если новое состояние 1, то
    if (new_state) 
    {
    
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
    
    } else 
    {
    
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

/**
 * @brief Нажатие на кнопку Compiler Settings. Запускает диалоговое окно.
 */
void MainWindow::on_CompilerSettingsButton_clicked()
{

    // При нажатии на кнопку изменения настроек вызываем соответствующий слот
    compilerSettingsAction();

}

/**
 * @brief При нажатии на чек-бокс локализации тензора необходимо обновить состояния
 * некоторых виджетов.
 * 
 * @param is_checked - новое состояние (1 - нажат, 0 - не нажат)
 */
void MainWindow::on_IsRemoteTensor_stateChanged(int is_checked)
{
    // Если тензор лежит на удаленном хостинге
    if (is_checked) 
    {
        // Меняем описание поля для ввода пути и запрещаем нажатие кнопки изменения.
        // предпологается ручной ввод пути на удаленном хосте.
        ui->InputTensorPathLabel->setText("Путь к входному тензору на удаленном хосте:");
        ui->ChangeInputTensorPathButton->setEnabled(false);
    
    // Если тензор лежит на локальном хостинге
    } else 
    {
        // Разблокируем кнопку и меняем описание поля ввода пути.
        ui->InputTensorPathLabel->setText("Путь к входному тензору на локальном хосте:");
        ui->ChangeInputTensorPathButton->setEnabled(true);
    
    }

}

/**
 * @brief Меняет состояния при выборе опции генерации нового тензора.
 * @details При генерации тензора необходимо указать дополнительные поля,
 * поэтому нужно из показать в режиме генерации и скрыть от глаз в обычном режиме
 * @param is_checked - флаг режима. (1 - генерация нужна, 0 - генерация не нужна)
 */
void MainWindow::on_isGenerateTensor_stateChanged(int is_checked)
{
    // Если генерация нужна, то нужно показать определенные виджеты
    if(is_checked) 
    {
    
        ui->GeneratedTensorSizeLabel->setVisible(true);
        ui->TensorSizeLineEdit      ->setVisible(true);
        ui->GeneratedTensorSavePathLineEdit->setVisible(true);
        ui->GeneratedTensorSavePathLabel   ->setVisible(true);
        ui->ChangeGeneratedTensorSavePathButton->setVisible(true);
        
        // Проверка корректности текущих данных
        on_TensorSizeLineEdit_editingFinished();
        on_GeneratedTensorSavePathLineEdit_editingFinished();
    
    // Если панель генерации скрывается, то нужно убрать лишние виджеты
    } else 
    {

        ui->GeneratedTensorSizeLabel->setVisible(false);
        ui->TensorSizeLineEdit      ->setVisible(false);
        ui->GeneratedTensorSavePathLineEdit->setVisible(false);
        ui->GeneratedTensorSavePathLabel   ->setVisible(false);
        ui->ChangeGeneratedTensorSavePathButton ->setVisible(false);
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(false);
        ui->WrongFmtGeneratedTensorSizeLabel    ->setVisible(false);
    
    }

}

/**
 * @brief Проверка размеров генерируемого тензора
 * @details Введенные значения должны соответствовать формату:
 * быть не нулевыми, не отрицательными, кол-во 4 штуки, перечислены через запятую.
 */
void MainWindow::on_TensorSizeLineEdit_editingFinished()
{

    // Проверка на отрицательные и нулевые значения + соответсвие формату ввода
    auto [is_general, is_child] = checkSizesFormat(ui->TensorSizeLineEdit->text(), "^[1-9]");
    
    // Если неверный формат
    if (!is_general) 
    {
    
        ui->WrongFmtGeneratedTensorSizeLabel->setText(WRONG_FMT_TEXT::bad_format);
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(true);
        return;
    
    // Если содержит нули
    } else if (!is_child) 
    {
        
        ui->WrongFmtGeneratedTensorSizeLabel->setText(WRONG_FMT_TEXT::zero_value);
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(true);
        return;
    
    // Если все в норме
    } else 
    {
    
        ui->WrongFmtGeneratedTensorSizeLabel->setVisible(false);
    
    }
}


/**
 * @brief Проверка существования введнного пути
 */
void MainWindow::on_ProgramDirPathLineEdit_editingFinished()
{
    // Текущий путь
    QString current_text(ui->ProgramDirPathLineEdit->text());

    // Если не существует - показываем индикатор. Иначе - скрываем.
    if (!boost::filesystem::is_directory(current_text.toStdString())) 
    {
    
        ui->WrongFmtProgramDirPathLabel->setVisible(true);
    
    } else 
    {
        
        ui->WrongFmtProgramDirPathLabel->setVisible(false);
    
    }

}


/**
 * @brief Выбор директории через проводник при нажатии на кнопку
 */
void MainWindow::on_ChangeProgramDirPathButton_clicked()
{

    // Текущий указанный путь
    QString current_path(ui->ProgramDirPathLineEdit->text());
    
    // Проверка существования текущего пути
    bool is_path_exist { boost::filesystem::is_directory(current_path.toStdString()) };

    // Стартовый путь. Если текущий существует, то устанавливаем его. Иначе - стандартный путь.
    QString start = (is_path_exist) ? (current_path) : (RunnerSettingsDefault::user_folder);

    // Получение нового пути из проводника
    QString new_path = QFileDialog::getExistingDirectory(
                                        this,
                                        "Выберите директорию с программой",
                                        start
                                    );

    // Если путь не пуст, то добавляем его.
    if (!new_path.isEmpty()) 
        ui->ProgramDirPathLineEdit->setText(new_path);

}

/**
 * @brief Выбор файла со входным тензором на локальном хостинге
 */
void MainWindow::on_ChangeInputTensorPathButton_clicked()
{

    // Текущий указанный путь
    QString current_path(ui->InputTensorPathLineEdit->text());

    // Проверка существования текущего пути
    bool is_path_exist { boost::filesystem::is_directory(current_path.toStdString()) };

    // Стартовый путь. Если текущий существует, то устанавливаем его. Иначе - стандартный путь.
    QString start = (is_path_exist) ? (current_path) : (RunnerSettingsDefault::user_folder);

    // Получение нового пути из проводника
    QString new_path = QFileDialog::getOpenFileName(
                                        this,
                                        "Выберите файл с входным тензором",
                                        start,
                                        "Бинарные файлы (*.bin)"
                                    );

    // Если путь не пуст, то добавляем его.                               
    if (!new_path.isEmpty()) 
        ui->InputTensorPathLineEdit->setText(new_path);

}

/**
 * @brief Открытие на редактирование файла cmd0.bin из директории с программой.
 */
void MainWindow::on_ShowCmd0Button_clicked()
{

    QString program_dir(ui->ProgramDirPathLineEdit->text());

    QString file_path = program_dir + "/cmd0.bin";

    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Открытие на редактирование файла cmd1.bin из директории с программой.
 */
void MainWindow::on_ShowCmd1Button_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd1.bin";
    
    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Открытие на редактирование файла cmd2.bin из директории с программой.
 */
void MainWindow::on_ShowCmd2Button_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd2.bin";
    
    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Открытие на редактирование файла cmd3.bin из директории с программой.
 */
void MainWindow::on_ShowCmd3Button_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd3.bin";
    
    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Открытие на редактирование файла cmd4.bin из директории с программой.
 */
void MainWindow::on_ShowCmd4Button_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd4.bin";
    
    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Открытие на редактирование файла cmd5.bin из директории с программой.
 */
void MainWindow::on_ShowCmd5Button_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd5.bin";
    
    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}


/**
 * @brief Открытие на редактирование файла с логом tpu_data из директории с программой.
 */
void MainWindow::on_ShowTpuDataButton_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/logs/tpu_data";
    
    open_for_edit(file_path.toStdString(), FILE_EDITOR);

}

/**
 * @brief Открытие на редактирование файла с логом CashData из директории с программой.
 */
void MainWindow::on_ShowCacheDataButton_clicked()
{

    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/logs/CashData";
    
    open_for_edit(file_path.toStdString(), FILE_EDITOR);

}

/**
 * @brief Открытие на редактирование файла с логом cmd.json из директории с программой.
 */
void MainWindow::on_ShowCmdJsonButton_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/cmd.json";
    
    open_for_edit(file_path.toStdString(), FILE_EDITOR);
}

/**
 * @brief Открытие на редактирование файла с метаданными из директории с программой.
 */
void MainWindow::on_ShowMetadataButton_clicked()
{
    
    QString program_dir(ui->ProgramDirPathLineEdit->text());
    
    QString file_path = program_dir + "/metadata.json";
    
    open_for_edit(file_path.toStdString(), FILE_EDITOR);

}

/**
 * @brief Открытие на редактирование выходного файла из директории с программой.
 */
void MainWindow::on_ShowOutputTensorButton_clicked()
{

    QString program_dir(ui->ProgramDirPathLineEdit->text());

    QString file_path = program_dir + "/output/output.bin";

    open_for_edit(file_path.toStdString(), BINARY_EDITOR);

}

/**
 * @brief Запуск программы при нажатии на кнопку.
 * @details В данном месте заполняются настройки запуска программы и проверяется их корректность.
 * При корректно введенных настройках будет запущен отдельный поток для выполнения программы
 * на локальном или удаленном хосте и опциональное создание нового тензора.
 */
void MainWindow::on_RunButton_clicked()
{

    // Сброс состояния прогресс бара к минимальному значению
    runner_progress->setCurrent(runner_progress->getMin());
    ui->RunnerProgressBar->setValue(runner_progress->getMin());

    // Проверка видимости индикаторов неверного формата ввода
    if (ui->WrongFmtProgramDirPathLabel->isVisible()) 
    {
        
        runner_status_cache->writeMessage(RunnerError::PROGRAM_DIR_NOT_EXIT);
        return;
    
    }

    // Проверка полей связанных с генерацией нового тензора
    if (ui->isGenerateTensor->isChecked()) 
    {
        
        // Если неверно введен размер тензора
        if (ui->WrongFmtGeneratedTensorSizeLabel->isVisible()) 
        {
        
            runner_status_cache->writeMessage(RunnerError::WRONG_GENERATED_TENSOR_FORMAT);
            return;
        
        }

        // Если неверно указан путь для сохранения генерируемого тензора
        if (ui->WrongFmtGeneratedTensorSavePathLabel->isVisible()) 
        {
            
            runner_status_cache->writeMessage(RunnerError::WRONG_GENERATED_TENSOR_SAVE_PATH);
            return;
        
        }

    }

    // Проверка на необходимость генерирования нового тензора
    bool is_generate_tensor { ui->isGenerateTensor->isChecked() };

    // Настройки генерации тензора
    TensorCreatorSettings tensor_creator_settings;

    // Если тензор генерируется, то настройки заполняются
    if (is_generate_tensor) 
    {
    
        tensor_creator_settings.tensor_size      = ui->TensorSizeLineEdit->text();
        tensor_creator_settings.tensor_save_path = ui->GeneratedTensorSavePathLineEdit->text();
    
    }


    // Локальный запуск программы
    if (ui->RunMode->currentIndex() == LOCAL_RUN_ID) 
    {

        // Если запуск локальный, то нужно обновить состояние вкладки
        // и скрыть ненужные виджеты для удаленного запуска
        ui->IsRemoteTensor->setChecked(false);
        on_IsRemoteTensor_stateChanged(false);

        // Настройки локального запуска
        LocalRunnerSettings local_settings;

        // Директория с программой
        local_settings.program_directory = ui->ProgramDirPathLineEdit->text();
        
        // Путь к входному тензору по умолчанию
        local_settings.input_tensor_path = ui->InputTensorPathLineEdit->text();

        // Название архива с программой
        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        QString program_name = settings->value(GlobalSettingName::programArchiveName).toString();
        settings->endGroup();
        local_settings.program_name = program_name;

        // Общие настройки запуска
        RunnerSettings settings(local_settings);
        
        // Если тензор генерируется, то устанавливаем в общие настройки соответсвующие флаги
        // и поля
        if (is_generate_tensor) 
        {

            settings.is_tensor_create = true;
            settings.tensor_create_settings = tensor_creator_settings;
            settings.local_settings.input_tensor_path = tensor_creator_settings.tensor_save_path;
        
        }

        // Запуск отдельного потока для выполнения программы
        std::thread t(run_programm, settings, runner_progress, runner_status_cache);
        t.detach();


    // Удаленный запуск программы
    } else if (ui->RunMode->currentIndex() == REMOTE_RUN_ID) 
    {

        // Дескриптор настроек удаленного запуска.
        RemoteConnectionDesc remote_connection_settings;

        // Заполнение полей аунтефикации и вызов диалогового окна с заполнением параметров аунтефикации.
        RemoteAuthDialog auth_dialog(this, settings, &remote_connection_settings);
        auth_dialog.show();
        int auth_success = auth_dialog.exec();

        // Если авторизация отклонена, то необходимо завершить процесс запуска
        if (!auth_success)
            return;
        
        // Общие настройки удаленного запуска программы
        RemoteRunnerSettings remote_settings;

        // Заполнение имен и путей к входным тензорам для разных случаев локализации
        // Случай когда тензор создается с нуля
        if (ui->isGenerateTensor->isChecked()) 
        {
        
            QString tensor_path = ui->GeneratedTensorSavePathLineEdit->text();
            remote_settings.input_tensor_name = tensor_path.split("/").last();
            remote_settings.input_tensor_path = tensor_path;
        
        // Остальные случаи
        } else 
        {
        
            QString tensor_path = ui->InputTensorPathLineEdit->text();
            remote_settings.input_tensor_name = tensor_path.split("/").last();
            remote_settings.input_tensor_path = tensor_path;
        
        }

        // Заполнение информации о входном тензоре
        remote_settings.is_generated_tensor = ui->isGenerateTensor->isChecked();
        remote_settings.is_remote_tensor    = ui->IsRemoteTensor->isChecked();


        // Получение названия архива с программой
        settings->beginGroup(GLOBAL_SETTINGS_GROUP);
        QString program_name = settings->value(GlobalSettingName::programArchiveName).toString();
        settings->endGroup();

        // Директория с программой
        remote_settings.program_directory = ui->ProgramDirPathLineEdit->text();
        
        // Название архива с программой
        remote_settings.program_name = program_name;

        // Hosting IP address
        remote_settings.remote_hosting_ip = remote_connection_settings.host_ip;

        // Hosting port
        remote_settings.remote_hosting_port = "22";
        
        // Authefication username
        remote_settings.username = remote_connection_settings.username;
        
        // Authefication password
        remote_settings.userpass = remote_connection_settings.password;

        // Настройки ядра
        RunnerSettings settings(remote_settings);

        // Заполнение информации о необходимости генерации тензора
        if (is_generate_tensor) 
        {

            settings.is_tensor_create = true;
            settings.tensor_create_settings = tensor_creator_settings;
            settings.local_settings.input_tensor_path = tensor_creator_settings.tensor_save_path;
        
        }

        // Выделение потока для работы
        std::thread t(run_programm, settings, runner_progress, runner_status_cache);
        t.detach();
    
    }

}


/**
 * @brief Проверка корректности введенного пути для сохранения генерируемого тензора
 */
void MainWindow::on_GeneratedTensorSavePathLineEdit_editingFinished()
{

    // Текущий путь
    QString current_path = ui->GeneratedTensorSavePathLineEdit->text();
    
    // Разбиваем путь на составляющие и удаляем последнюю. Получаем тем самым путь к директории
    QStringList splitted = current_path.split('/');
    splitted.removeAt(splitted.size() - 1);
    QString directory = splitted.join('/');

    // Если директория не существует
    if (!boost::filesystem::is_directory(directory.toStdString())) 
    {
    
        ui->WrongFmtGeneratedTensorSavePathLabel->setText(WRONG_FMT_TEXT::directory_not_exist);
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(true);
    
    // Если указанный формат не является бинарным файлом
    } else if (!current_path.endsWith(".bin")){
    
        ui->WrongFmtGeneratedTensorSavePathLabel->setText(WRONG_FMT_TEXT::not_bin_fmt);
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(true);
    
    // Если все введено верно
    } else {
    
        ui->WrongFmtGeneratedTensorSavePathLabel->setVisible(false);
    
    }

}

/**
 * @brief Действие при нажатии на кнопку выбора пути сохранения генерируемого тензора.
 */
void MainWindow::on_ChangeGeneratedTensorSavePathButton_clicked()
{

    // Текущий путь
    QString current_path = ui->GeneratedTensorSavePathLineEdit->text();

    // Получаем новый путь
    QString new_path = QFileDialog::getSaveFileName(
                                        this, 
                                        "Выберите путь для сохранения тензора", 
                                        current_path
                                    );
    
    // Если новый путь не пуст, то обновляем состояние
    if (!new_path.isEmpty())
        ui->GeneratedTensorSavePathLineEdit->setText(new_path);
    

}

