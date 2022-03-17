#include "mainwindow.h"
#include "lib/configurator/configurator.h"
#include <QApplication>

void initApp()
{
    Configurator::loadConfigs();
}

int main(int argc, char *argv[])
{

    initApp();

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
