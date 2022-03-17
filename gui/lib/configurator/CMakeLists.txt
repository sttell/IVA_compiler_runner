cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(configurator)				# Название проекта

add_library(configurator_lib OBJECT configurator.cpp)# Создание статической библиотеки
