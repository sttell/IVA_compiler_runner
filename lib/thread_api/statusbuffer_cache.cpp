#include "statusbuffer_cache.h"

// Проверка пустоты очереди сообщений
bool StatusBufferCache::isQueueEmpty() {
    std::lock_guard lg(data_mutex);
    return cache.empty();
};

// Выдача следующего сообщения
StatusMessage StatusBufferCache::getNext() {
    std::lock_guard lg(data_mutex);
    // Если очередь не пуста, то выдаем
    if (!cache.empty()) {

        StatusMessage ret = cache.front();
        cache.pop();
        return ret;

    } else {
        // В ином случае возвращаем затычку
        return {"Обращение к пустому кэшу буффера", "[STATUS BUFFER CACHE MESSAGE]", MessageColor::warning};
    }
};

// Запись сообщения в кэш
void StatusBufferCache::writeMessage(const std::string& message, const std::string& header, QColor color) {
    std::lock_guard lg(data_mutex);

    cache.push({message, header, color});

    // Обновление флага остановки логирующего процесса при цвете error
    if (color == MessageColor::error) {
        end_flag = true;
    }
}

// Проверка на завершение процесса
bool StatusBufferCache::isProcessEnded() {
    std::lock_guard lg(data_mutex);
    return end_flag;
}

// Выставление флага завершения процесса
void StatusBufferCache::endProcess() {
    std::lock_guard lg(data_mutex);
    end_flag = false;
}
