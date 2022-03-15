cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(modules)				# Название проекта

include_directories("pickle_converter")
include_directories("address_checker")
include_directories("compiler_runner")
include_directories("metadata_creator")
add_subdirectory(pickle_converter)
add_subdirectory(address_checker)
add_subdirectory(compiler_runner)
add_subdirectory(metadata_creator)