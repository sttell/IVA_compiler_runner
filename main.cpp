/**
 * @file main.cpp
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Основной файл. Точка входа в программу.
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */


// Включения для интерфейса
#include "mainwindow.h"

// Включения Qt
#include <QApplication>


/**
 * @brief Стандартный код возврата из приложения
 */
#define DEFAULT_APP_RETCODE -1

/**
 * @brief Код возврата из приложения: неудачное завершение
 */
#define FAIL_APP_RETCODE     0

/**
 * @brief Код возврата из приложения: удачное завершение
 */
#define SUCCES_APP_RETCODE   1


/**
 * @brief Точка входа в приложение
 * 
 * @param argc - Количество аргументов командной строки
 * @param argv - Аргументы командной строки
 * @return int - Код возврата приложения
 */
int main(int argc, char *argv[])
{

    // Основное приложение
    QApplication a(argc, argv);

    // Главное окно
    MainWindow w;

    // retcode приложения
    int application_return_code { DEFAULT_APP_RETCODE };

    // Проверка: происходила ли первичная инициализация ПО.
    // Если не происходила, то mainwindow запустит welcome menu
    // и вернет его код возврата. Иначе - true
    bool is_not_first_run = w.isFirstRunInited();

    // Если инициализация прошла успешно
    if (is_not_first_run) 
    {
    
        // Запускаем главное окно
        w.show();
        application_return_code = a.exec();

    // В ином случае закрываем ПО с кодом 0
    } else {
    
        w.close();
        application_return_code = FAIL_APP_RETCODE;
        a.exit(application_return_code);
    
    }

    return application_return_code;

}
