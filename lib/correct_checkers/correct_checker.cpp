#include "correct_checker.h"

#include <vector>

bool is_digit(const std::string& string) {
    return false;
}

void strip_spaces(std::string& text) {
    if (text.empty()) return;
    if (text == " ") {
        text = "";
        return;
    }

    size_t first_sym = 0;
    size_t last_sym = std::string::npos;

    for(size_t i = 1; i < text.size(); i++) {
        if (text[i] != ' ' && text[i - 1] == ' ') {
            first_sym = i;
            break;
        }
        if (text[i] != ' ') break;
    }
    text.erase(0, first_sym);
    text.shrink_to_fit();

    if (text.size() <= 1) return;

    for(size_t i=text.size() - 2; i > 0; i--) {
        if (text[i] != ' ' && text[i + 1] == ' ') {
            last_sym = i + 1;
            break;
        }
        if (text[i] != ' ') break;
    }

    text.erase(last_sym);
    text.shrink_to_fit();

}

// Разбиение строки по разделителю
std::vector<std::string> split(const std::string& text, char separator) {
    // Вектор хранящий результаты.
    std::vector<std::string> splitted;

    // Копия текста для обработки.
    std::string text_copy(text);

    // Стартовая позиция разделителя
    size_t pos = 0;
    // Пока разделитель найден и не равен концу, то делим текст
    while ((pos = text_copy.find(separator)) != std::string::npos)
    {
        // Добавляем подстроку в результат
        splitted.push_back(text_copy.substr(0, pos));
        // Вырезаем добавленный учаток
        text_copy.erase(0, pos + 1);
    }
    // Базовый случай / последний элемент
    splitted.push_back(text_copy.substr(0, pos));

    return splitted;
}

bool is_good_size_format(const std::string& text)
{
    // Size format: 0, 0, 0, 0

    return false;



}
bool is_good_padding_format(const std::string& text) {
    return false;
}
bool is_good_directory_format(const std::string& text) {
    return false;
}
bool is_good_file_format(const std::string& text, const std::string& file_fmt) {
    return false;
}
bool is_good_directory_name_format(const std::string& text) {
    return false;
}
