#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "lib/configurator/configurator.h"
#include "lib/logger/logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , log(new Logger("ui_mainwindow.log", "[UI Main Window]: "))
{
    log->send("Main window constructor.");

    ui->setupUi(this);

    log->send("UI inited setup success.");

    initWrongFormatIndicators();

    log->send("Form inited.");
}

MainWindow::~MainWindow()
{
    log->send("Main window desctructor.");

    Configurator::dumpConfigs();

    log->send("Configurations saved.");

    delete log;
    delete ui;
}

void MainWindow::initWrongFormatIndicators()
{
    log->send("initialization of wrong format forms.");
    ui->WrongFmtCatalogNameLabel->setVisible(false);
    ui->WrongFmtInputPadDownLabel->setVisible(false);
    ui->WrongFmtInputPadUpLabel->setVisible(false);
    ui->WrongFmtInputSizeLabel->setVisible(false);
    ui->WrongFmtJsonPathLabel->setVisible(false);
    ui->WrongFmtOutputPadDownLabel->setVisible(false);
    ui->WrongFmtOutputPadUpLabel->setVisible(false);
    ui->WrongFmtOutputSizeLabel->setVisible(false);
    ui->WrongFmtWeightsPathLabel->setVisible(false);
}

void MainWindow::initUiFromConfig() {
    log->send("initialization of compiler runner tab UI.");
    this->initUiCompiler();

    log->send("initialization of programm runner tab UI.");
    this->initUiRunner();

    log->send("initialization of analysis tab UI.");
    this->initUiAnalysis();
}



void MainWindow::initUiCompiler() {
    ConfigurationDesc * cfg_desc = &configs[CONFIGURE_TYPE::CompilerSettings];

    //TODO Заполнить

    cfg_desc = nullptr;
    delete cfg_desc;
}

void MainWindow::initUiRunner() {
    // TODO To do task
}

void MainWindow::initUiAnalysis() {
    // TODO To do Task
}
