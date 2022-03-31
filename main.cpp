#include "mainwindow.h"
#include <QApplication>
#include "ui/welcome_form.h"
#include <iostream>

int main(int argc, char *argv[])
{
    // Основное приложение
    QApplication a(argc, argv);

    // Главное окно
    MainWindow w;

    // retcode приложения
    int application_return_code = -1;

    // Проверка: происходила ли первичная инициализация ПО.
    // Если не происходила, то mainwindow запустит welcome menu
    // и вернет его код возврата. Иначе - true
    bool is_not_first_run = w.isFirstRunInited();

    // Если инициализация прошла успешно
    if (is_not_first_run) {
        // Запускаем главное окно
        w.show();
        application_return_code = a.exec();
    } else {
        // В ином случае закрываем ПО с кодом 0
        w.close();
        application_return_code = 0;
        a.exit(application_return_code);
    }

    return application_return_code;
}
