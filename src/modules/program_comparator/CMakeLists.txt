cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(program_comparator)				# Название проекта

find_package(Boost COMPONENTS filesystem thread system)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES programComparatorModule.cpp)
set(SOURCE_LIB ${SOURCES} ${Boost_INCLUDE_DIRS})		# Установка переменной со списком исходников

add_library(program_comparator_lib OBJECT ${SOURCE_LIB})# Создание статической библиотеки