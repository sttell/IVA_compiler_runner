cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(compiler_lib)				# Название проекта

find_package(Boost COMPONENTS program_options filesystem )
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES pipeline.cpp compilerCore.cpp path.cpp jsonHandler.cpp module.cpp timer.cpp)
set(SOURCE_LIB ${SOURCES} ${Boost_INCLUDE_DIRS})		# Установка переменной со списком исходников

add_library(compiler_lib OBJECT ${SOURCE_LIB})# Создание статической библиотеки