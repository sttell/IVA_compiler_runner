#ifndef STATUSBUFFERCACHE_H
#define STATUSBUFFERCACHE_H

#include "lib/controllers/statusbar_controller.h"
#include "include/compile_errors.h"
#include "include/runner_errors.h"
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <QColor>

struct StatusMessage
{
    StatusMessage(const std::string& _message) : message(_message), header("auto"), message_color(MessageColor::normal) {};
    StatusMessage(const std::string& _message, QColor color) : message(_message), header("auto"), message_color(color) {};
    StatusMessage(const std::string& _message, const std::string& _header, QColor color) : message(_message), header(_header), message_color(color) {};

    std::string message;
    std::string header;
    QColor message_color;
};

class StatusBufferCache
{

public:
    StatusBufferCache() : end_flag(false) {};
    ~StatusBufferCache() {};

    bool isQueueEmpty();
    bool isProcessEnded();
    StatusMessage getNext();
    void writeMessage(const std::string& message, const std::string& header="auto", QColor color=MessageColor::normal);
    // Запись сообщения с header и определенным цветом
    void writeMessage(CompileError error_type, const std::string& header="auto");
    void writeMessage(RunnerError error_type, const std::string& header="auto");
    void endProcess();

private:
    std::queue<StatusMessage> cache;
    volatile bool end_flag;
    std::mutex data_mutex;

};

#endif // STATUSBUFFERCACHE_H
