cmake_minimum_required(VERSION 3.0) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.



find_package(Boost COMPONENTS program_options filesystem system thread)

include_directories(${Boost_INCLUDE_DIRS})

include_directories("lib")
include_directories("include")
include_directories("include/settings")
include_directories("src")

add_subdirectory(lib)
add_subdirectory(src)
add_executable(main main.cpp)		# Создает исполняемый файл с именем main
									# из исходника main.cpp

target_link_libraries(main compiler_lib pickle_converter_lib ${Boost_LIBRARIES})