cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(logger)				# Название проекта

set(HEADERS logger.h)

add_library(logger_lib OBJECT logger.cpp logger.h)# Создание статической библиотеки
