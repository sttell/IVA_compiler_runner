#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void initWrongFormatIndicators();
};
#endif // MAINWINDOW_H
