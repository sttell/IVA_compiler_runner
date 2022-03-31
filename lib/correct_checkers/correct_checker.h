#ifndef CORRECT_CHECKER_H
#define CORRECT_CHECKER_H

#include <string>

bool is_good_size_format(const std::string& text);
bool is_good_padding_format(const std::string& text);
bool is_good_directory_format(const std::string& text);
bool is_good_file_format(const std::string& text, const std::string& file_fmt);
bool is_good_directory_name_format(const std::string& text);

#endif // CORRECT_CHECKER_H
