#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @version 1.0
 * @date 2022-04-02
 * 
 * @details Файл mainwindow.h является описанием класса главного окна
 * MainWindow. Данный класс содержит практически всю логику интерфейса
 * пользователя на момент версии 1.0.
 * 
 * @copyright Copyright (c) 2022
 */


/*
* ---------------------------------------------------------------------------
*                               Включения
* ---------------------------------------------------------------------------
*/

// Подключение всех необходимых пользовательских библиотек
#include "lib/controllers/statusbar_controller.h"               // Контроллер Status Bar
#include "lib/buffers/settingsbuffer.h"                         // Буффер настроек
#include "lib/thread_api/statusbuffer_cache.h"                  // Кэш Status Bar
#include "lib/thread_api/interrupt_buffer.h"                    // Буффер для остановки работы потоков
#include "lib/correct_checkers/compile_runner_preprocessor.h"   // Препроцессор для компиляции
#include "lib/thread_api/progressbar_buffer.h"                  // Буффер для хранения состояний Progress Bar

// Библиотеки Qt
#include <QMainWindow>
#include <QSettings>
#include <QTimer>



/*
* ---------------------------------------------------------------------------
*                          Объявляения и макросы
* ---------------------------------------------------------------------------
*/

/**
 * @brief Стандартный редактор файлов имеющих не бинарный формат
 * @details Используется для открытия файлов имеющих формат
 * отличный от *.bin
 */
#define FILE_EDITOR "code -r"

/**
 * @brief Стандартный редактор файлов имеющих бинарный формат
 * @details Используется для открытия файлов имеющих формат *.bin
 */
#define BINARY_EDITOR "ghex"

/**
 * @brief Период обновлений таймера обновлений главного окна
 */
#define UPDATE_WINDOW_LATENCY_MS 100

// Период обновления панели быстрого доступа для Runner Tab вкладки
#define UPDATE_RUNNER_FAST_PANEL_LATENCY_MS 1000



/*
* ---------------------------------------------------------------------------
*                          Пространства имен
* ---------------------------------------------------------------------------
*/

// Пространство имен с UI главного окна
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




/*
* ---------------------------------------------------------------------------
*                                Классы
* ---------------------------------------------------------------------------
*/

/**
 * @brief MainWindow класс описывающий логику работы главного окна интерфейса
 * @details Главное окно является модификацией объекта QMainWindow
 * и описывает всю логику графического интерфейса пользователя.
 * Данный класс связывает работу интерфейса пользователя и ядер
 * ПО отвечающих за выполнение полезной работы.
 * На данный момент главное окно не может выбрасывать исключения и должно работать
 * Стабильно во всех ситуациях.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Construct a new Main Window object
     * @details Основной конструктор MainWindow. 
     * Инициализирует интерфейс пользователя.
     * @param parent - родительское окно.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the Main Window object
     * @details Деструктор главного окна
     * высвобождает все занимаемые ресурсы и сохраняет
     * состояния интерфейса в настройки.
     */
    ~MainWindow();

    /**
     * @brief Проверка первичной инициализации ПО.
     * @details При первом запуске пользователь должен увидеть
     * меню приветствия и заполнить некоторые параметры ПО.
     * Данный метод возвращает соответствующий флаг.
     * @return true  - Если первичная инициализация уже пройдена
     * @return false - Если первичная инициализация еще пройдена
     */
    bool isFirstRunInited();

/**
 * @brief Слоты для UI
 * @details В данной секции описаны слоты для User Interface(UI)
 * которые связываются с триггерами и сигналами виджетов окна MainWindow.
 * Некоторые из них запускаются по таймеру.
 */

private slots:
    /* 
     * -----------------------------------------------------------------
     *                 Слоты вызываемые по таймеру
     * -----------------------------------------------------------------
     */

    /**
     * @brief Обновление статус буффера в текущей вкладке
     * @details Данный слот обновляет статус бар текущей вкладки
     * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
     */
    void statusBufferUpdate();

    /**
     * @brief Обновление текущего времени на главной панели.
     * @details Данный слот обновляет текущее время
     * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
     */
    void updateCurrentTime();
    
    /**
     * @brief Обновление прогресс бара во вкладке Runner Tab
     * @details Данный слот обновляет progress bar вкладки Runner Tab
     * по таймеру. Частота обновлений указана в #define UPDATE_WINDOW_LATENCY_MS
     */
    void runnerProgressUpdate();
    
    /**
     * @brief Обновление панели быстрого доступа во вкладке Runner Tab
     * @details Данный слот обновляет панель быстрого доступа вкладки Runner Tab
     * по таймеру. Частота обновлений указана в #define UPDATE_RUNNER_FAST_PANEL_LATENCY_MS
     */
    void initUiRunnerPanelStates();



    /* 
     * -----------------------------------------------------------------
     *                Слоты виджетов генерируемые Qt
     *  on_[WidgetName]_[Action](atgs). 
     *  WidgetName - имя виджета в котором происходит событие
     *  Action     - название события, которое произошло.
     * -----------------------------------------------------------------
     */

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

    void on_RunProcessPushButton_clicked();

    void on_PickleConvertationCheckBox_stateChanged(int arg1);

    void on_OutputDirPathLineEdit_editingFinished();

    void on_OutputDirPathPushButton_clicked();

    void on_RedactJsonPushButton_clicked();

    void on_CompilerTabButton_clicked();

    void on_RunnerTabButton_clicked();

    void on_SettingsButton_stateChanged(int arg1);

    void on_CompilerSettingsButton_clicked();

    void on_IsRemoteTensor_stateChanged(int arg1);

    void on_isGenerateTensor_stateChanged(int arg1);

    void on_TensorSizeLineEdit_editingFinished();

    void on_ProgramDirPathLineEdit_editingFinished();

    void on_ChangeProgramDirPathButton_clicked();

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

    /* 
     * -----------------------------------------------------------------
     *               Слоты вызова настроек.
     * -----------------------------------------------------------------
     */

    /**
     * @brief Слот вызываемый при нажатии на кнопку Compiler Settings.
     * @details Данный слот вызывает окно Compiler Settings Dialog
     * и отвечает за обновление статичных настроек компиляции.
     */
    void compilerSettingsAction();


private:
    /*
    * ------------------------------------------------------------------
    *                   Приватные поля и данные
    * ------------------------------------------------------------------
    */

    /**
     * @brief UI интерфейс окна
     * @details Инициализируется в конструкторе MainWindow()
     */
    Ui::MainWindow* ui;

    /**
     * @brief Буффер с общими настройками ПО
     * @details Инициализируется в конструкторе MainWindow()
     */
    SettingsBuffer* settings;

    /**
     * @brief Контроллер Status Buffer'a вкладки Compiler Tab
     * @details Инициализируется в initStatusBars()
     */
    StatusBarController* compiler_status_controller;
    
    /**
     * @brief Кэш Status Buffer'a вкладки Compiler Tab
     * @details Инициализируется в initStatusBars()
     */
    StatusBufferCache*   compiler_status_cache;
    
    /**
     * @brief Контроллер Status Buffer'a вкладки Runner Tab
     * @details Инициализируется в initStatusBars()
     */
    StatusBarController* runner_status_controller;

    /**
     * @brief Кэш Status Buffer'a вкладки Runner Tab
     * @details Инициализируется в initStatusBars()
     */
    StatusBufferCache*   runner_status_cache;

    /**
     * @brief Общий таймер обновления окон.
     * @details Инициализируется в конструкторе MainWindow().
     * Период обновлений и связь со слотами определяется в initTimer().
     */
    QTimer* update_timer;

    /**
     * @brief Таймер обновления панели быстрого доступа вкладки Runner Tab.
     * @details Инициализируется в конструкторе MainWindow().
     * Период обновлений и связь со слотами определяется в initTimer().
     */
    QTimer* update_runner_fast_panel_timer;
 
    /**
     * @brief Буффер прерывания работы потока компиляции
     * @details На данный момент не работает (версия 1.0)
     */
    InterruptBuffer* compile_interrupt_buffer;

    /**
     * @brief Буффер для Progress Bar'a Runner Tab
     * @details Инициализируется в конструкторе MainWindow()
     */
    ProgressBarBuffer* runner_progress;

    // 
    /**
     * @brief Состояние первичной инициализации
     * @details Значение в firstRunInit() при вызове из конструктора MainWindow().
     */
    bool is_first_run_inited;



    /*
    * ------------------------------------------------------------------
    *                      Приватные методы
    * ------------------------------------------------------------------
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
    void firstRunInit();

    /**
     * @brief Общий метод инициализации главного окна
     * @details Вызывает группу методов, отвечающих за инициализацию интерфейса
     */
    void initMainWindow();

    /**
     * @brief Инициализация таймеров главного окна
     * @details Инициализирует работу таймеров главного окна
     * запускает таймеры, устанавливает период обновлений и 
     * связывает слоты с таймерами.
     */
    void initTimer();

    /**
     * @brief Инициализация Status Bar'ов главного окна
     * @details Выделяет ресурсы под контроллеры и cache
     * статус баров всех вкладок
     */
    void initStatusBars();


    /**
     * @brief Инициализация индикаторов неверного формата ввода
     * @details Запускает методы инициализирующие индикаторы неверного
     * формата ввода для всех вкладок UI
     */
    void initWrongFormatIndicators();

    /**
     * @brief Инициализация индикаторов неверного формата ввода для вкладки Compiler Tab
     */
    void initCompilerTabWrongFormatIndicators();

    /**
     * @brief Инициализация индикаторов неверного формата ввода для вкладки Runner Tab
     */
    void initRunnerTabWrongFormatIndicators();


    /**
     * @brief Инициализация состояний UI интерфеса
     * @details Запускает методы инициализации состояний интерфейса пользователя
     * для всех вкладок и главного окна
     */
    void initUiStates();

    /**
     * @brief Инициализация состояний UI интерфейса вкладки CompilerTab
     * @details Инициализирует состояния интерфейса вкладки CompilerTab
     * из настроек. И определяет видимость виджетов в зависимости от 
     * корректности данных и состояний иных виджетов.
     * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
     */
    void initUiCompilerTabStates();

    /**
     * @brief Инициализация состояний UI интерфейса вкладки Runner Tab
     * @details Инициализирует состояния интерфейса вкладки Runner Tab
     * из настроек. И определяет видимость виджетов в зависимости от 
     * корректности данных и состояний иных виджетов.
     * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
     */
    void initUiRunnerTabStates();

    /**
     * @brief Инициализация состояний UI интерфейса вкладки Analysis Tab
     * @details Инициализирует состояния интерфейса вкладки Analysis Tab
     * из настроек. И определяет видимость виджетов в зависимости от 
     * корректности данных и состояний иных виджетов.
     * Здесь происходит подгрузка всех сохраненных состояний с прошлого запуска ПО.
     */
    void initUiAnalysisTabStates();

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
    std::pair<bool, bool> checkSizesFormat(const QString& text, QString items_regex="");

    /**
     * @brief Проверка правильности введенных настроек при запуске процесса компиляции
     * @details Метод проверяет видимость индикаторов неверного формата ввода.
     * В случае, когда один из индикаторов виден, то в лог(Status Cache) выводится соответствующее
     * сообщение об ошибке.
     * 
     * @return true  - Все индикаторы неверного формата ввода скрыты и можно продолжать процесс компиляции.
     * @return false - Один из индикаторов неверного формата ввода виден, значит процесс нужно остановить.
     */
    bool checkCompilationInputStates();

    /**
     * @brief Формирование дескриптора вариативных настроек компиляции.
     * @details Формирует дескриптор настроек компиляции, которые указываются во вкладке 
     * Compiler Tab. 
     * 
     * @param settings_desc - Дескриптор настроек. Ссылка на дескриптор настроек, который будет заполнен.
     */
    void formCompilationVariableSettingsDescriptor(CompileVarSettingsDescriptor& settings_desc);


    /**
     * @brief Сохранение состояний виджетов UI.
     * @details Вызывает методы сохранения состояний для всех вкладок
     * и обновляет буффер настроек.
     * Вызываемые методы: saveUiCompilerTabStates(), saveUiRunnerTabStates()
     */
    void saveUiStates();

    /**
     * @brief Метод сохранения состояний вкладки Compiler Tab
     * @details Сохраняет состояния виджетов в настройки. Вызывается из saveUiStates()
     */
    void saveUiCompilerTabStates();

    /**
     * @brief Метод сохранения состояний вкладки Runner Tab
     * @details Сохраняет состояния виджетов в настройки. Вызывается из saveUiStates()
     */
    void saveUiRunnerTabStates();


};
#endif // MAINWINDOW_H
