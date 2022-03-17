cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(lib)				# Название проекта

include_directories("configurator")
add_subdirectory(configurator)