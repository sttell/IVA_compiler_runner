cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

				
project(metadata_creator)				# Название проекта

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCES metadataCreatorModule.cpp)
set(SOURCE_LIB ${SOURCES} ${Boost_INCLUDE_DIRS})		# Установка переменной со списком исходников

add_library(metadata_creator_lib OBJECT ${SOURCE_LIB})# Создание статической библиотеки