cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(src)				# Название проекта

include_directories("modules")
add_subdirectory(modules)