#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "lib/logger/logger.h"
#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    Logger *log;

    void initWrongFormatIndicators();
    void initUiFromConfig();
    void initUiCompiler();
    void initUiRunner();
    void initUiAnalysis();
};
#endif // MAINWINDOW_H
