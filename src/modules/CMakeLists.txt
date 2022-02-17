cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(modules)				# Название проекта

include_directories("pickle_converter")
add_subdirectory(pickle_converter)