#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWrongFormatIndicators();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWrongFormatIndicators()
{
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
