#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Bash скрипт для запуска процесса установки ПО
#    Устанавливает необходимые модули и делает CMake сборку проекта
#    Необходимые библиотеки для работы:
#    1. Boost version > 1.71.0
#    2. libssh
#    3. qt5, qt6
#    4. OpenGL
#    5. Python3 -> Pickle, Numpy
#
# Текущий скрипт требует аргумента-пути к директории для сборки.
#    sudo ./install.sh /path/to/build/dir
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


# Установка модулей
# sudo apt-get install -y libboost-all-dev  # Boost
# sudo apt-get install -y libssh-dev        # LibSSH
# sudo apt-get install -y qt5-default       # Qt5
# sudo apt-get install -y build-essential   # Build Essential for Qt
# sudo apt-get install -y libgl1-mesa-dev   # OpenGL for Qt

# pip install numpy                         # Numpy module
# #pip install pickle                        # Pickle module

# Определение переменных
build_directory=$1
img_directory=img

# Создание директории под собранный проект
echo "Creating build directory"
mkdir $build_directory

# Копирование директории с изображениями в проект сборки
echo "Copy images to build directory"
cp -r $img_directory $build_directory/$img_directory


# Создание второстепенных директорий внутри сборки
echo "Creating child directories in build"
mkdir $build_directory/cfg
mkdir $build_directory/src
mkdir $build_directory/src/pickle_converter_scripts
mkdir $build_directory/src/compiler_runner_scripts

# Копирование вспомогательных скриптов в директорию сборки
echo "Copy pickle converter and compiler runner bash sources to build directory"
cp ./lib/compiler_core/src/modules/compiler_runner/runner.sh $build_directory/src/compiler_runner_scripts/runner.sh
cp -r ./lib/compiler_core/src/modules/pickle_converter/lib $build_directory/src/pickle_converter_scripts/lib
cp -r ./lib/compiler_core/src/modules/pickle_converter/converter.py $build_directory/src/pickle_converter_scripts/converter.py

# Запуск сборки CMake
cmake -S . -B $build_directory

# Установка прав на всех пользователей. (Т.к. текущий скрипт запускается от суперпользователя и создает директории)
echo "Set premission for directory"
chmod 777 -R $build_directory