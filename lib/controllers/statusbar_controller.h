#ifndef STATUSBARCONTROLLER_H
#define STATUSBARCONTROLLER_H

#include <memory>
#include <thread>
#include <mutex>

#include <QTextBrowser>
#include <QColor>
#include <QString>

// Пространство имен, в котором определены основные цвета сообщений в StatusBar
namespace MessageColor
{
inline QColor normal = QColor::fromRgb(238, 238, 236);
inline QColor warning = QColor::fromRgb(237, 212, 0);
inline QColor error = QColor::fromRgb(205, 0, 0);
}

// Контроллер для параллельной работы со статус баром
class StatusBarController
{
public:
    // Принимает на вход объект представляющий статус бар
    explicit StatusBarController(QTextBrowser *status_bar);
    ~StatusBarController();

    // Запись сообщения с header и определенным цветом
    void writeMessage(const QString& message, QString header="auto", QColor color=MessageColor::normal);
    // Очистка статус бара
    void clear();
    // Выдача текста статус бара
    QString getText();

private:
    // Статус бар
    QTextBrowser* bar;
    // Мьютекс для обращения к статус бару
    std::mutex bar_mutex;
    // Тэг сообщения(общий, начало)
    QString start_tag;
    // Тэг сообщения(общей, конец)
    QString end_tag;
    // Теги для хэдера
    QString header_start_tag;
    QString header_end_tag;
};


#endif // STATUSBARCONTROLLER_H
