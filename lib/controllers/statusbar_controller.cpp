#include "statusbar_controller.h"
#include <iostream>
#include <QTime>

// Конструктор инициализирует внутренние ресурсы и захватывает статус бар
StatusBarController::StatusBarController(QTextBrowser* status_bar) :
    bar(status_bar), bar_mutex(), start_tag("<br>"), end_tag("</br>"),
    header_start_tag("<b><font color=\""), header_end_tag("</font></b>")
{

}

// Освобождает запрошенную память
StatusBarController::~StatusBarController()
{
    bar = nullptr;
    delete bar;
}

// Запись сообщения с блокировкой доступа к статус бару
void StatusBarController::writeMessage(const QString& message, QString header, QColor color)
{
    // Определяем хэдер и его текст
    QString curr_time("["); curr_time += QTime::currentTime().toString(Qt::DateFormat::ISODateWithMs); curr_time += "]";
    QString header_text("[Message]: ");

    if (header=="auto") {
        if (color == MessageColor::warning) header_text = "[Warning]: ";
        if (color == MessageColor::error)   header_text = "[Fatal Error]: ";
    } else {
        header_text = header;
    }
    // Формируем сообщение
    QString html_message(start_tag + header_start_tag);
    html_message += (color.name() + "\">" + curr_time + header_text + header_end_tag);
    html_message += message + end_tag;

    bar->insertHtml(html_message);


}

// Выдача текста статус бара с блокировкой
QString StatusBarController::getText() {
    QString text(bar->placeholderText());
    return std::move(text);
}

// Очистка статус бара с блокировкой
void StatusBarController::clear()
{
    bar->clear();
}
