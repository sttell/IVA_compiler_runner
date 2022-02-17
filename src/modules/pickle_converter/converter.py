from lib.arg_parser import ArgParser
from lib.logger import Logger
import pickle
import numpy
import sys

# Переименовыванные потоки вывода
stderr_out = sys.stderr
stdout_out = sys.stdout

# Коды выходов из программы
NORMAL_EXIT = 0
ERROR_EXIT = 1

# Идентификаторы типов констант в формате HPM
HPM_WEIGHTS_STRID   = 'filters'
HPM_POS_SCALE_STRID = 'scale'
HPM_NEG_SCALE_STRID = 'activation_coefficients'
HPM_BIAS_STRID      = 'biases'

# Идентификаторы типов констант в формате Pickle
PICKLE_WEIGHTS_STRID   = 'weights'
PICKLE_POS_SCALE_STRID = 'pos_scale'
PICKLE_NEG_SCALE_STRID = 'neg_scale'
PICKLE_BIAS_STRID      = 'bias'

# Имена аргументов командной строки для входного, выходного и реконструкционного файлов 
INPUT_PATH = "input_path"
OUTPUT_PATH = "output_path"
RECONSTRUCT_PATH = "reconstruct_pickle_path"

# Режимы чтения записи
WRITE_MODE = 'w'
BYTEREAD_MODE = 'rb'

# Аргументы командной строки
arguments = {
    INPUT_PATH: "",                 # Путь к входному файлу .pickle
    OUTPUT_PATH: "",               # Путь к выходному файлу .bin
    RECONSTRUCT_PATH: ""  # Путь к файлу с логом реконструкции pickle формата
}

# Обертка для обработки исключений. Необходимо для исключения аварийных прерываний
# при прямом взаимодействии с GUI программы. Прокидывает на выход вид исключения
def exception_handler_wrap(function):
    exception_log = Logger(stderr_out, stream_mode=True)
    try:
        function()
    except Exception as e:
        exception_log.write(str(e))
        return ERROR_EXIT
    return NORMAL_EXIT

# Функция загрузки данных из .pickle
def load_pickle_data(file_path):
    file = open(file_path, 'rb')
    pickle_data = pickle.load(file)
    return pickle_data

# Запись бинарного файла с весами и лога работы
def write_binary(pickle_data, arguments):
    array = numpy.empty(shape=(0), dtype=numpy.float16)
    
    # Инициализация выходного файла
    out_file = open(arguments[OUTPUT_PATH], 'w')
    # Переменная хранящая счетчик адресов
    address = 0

    # Инициализация std out stream
    pickle_log = Logger(stdout_out, stream_mode=True)

    # Реконструкция pickle файла в удобочитаемом виде
    reconstruct_pickle = Logger(arguments[RECONSTRUCT_PATH])
    reconstruct_pickle.write(str(pickle_data))
    del reconstruct_pickle

    # Прямой ход по слоям из Pickle файла и парсинг данных
    for layer_name in pickle_data:
        # Фиксация названия слоя
        pickle_log.write(layer_name)

        # Контейнеры для хранения весов
        weights   = numpy.empty(shape=(0), dtype=numpy.int8)
        bias      = numpy.empty(shape=(0), dtype=numpy.float16)
        pos_scale = numpy.empty(shape=(0), dtype=numpy.float16)
        neg_scale = numpy.empty(shape=(0), dtype=numpy.float16)
        
        # Данные об адресах и размерах всех типов данных
        addresses = {
            HPM_WEIGHTS_STRID:   [0, 0],
            HPM_BIAS_STRID:      [0, 0],
            HPM_POS_SCALE_STRID: [0, 0],
            HPM_NEG_SCALE_STRID: [0, 0]
        }

        # Список найденных типов данных
        finded_types = []

        # Проход по каждому типу данных на текущем слое и запись нужных данных
        for data_type in pickle_data[layer_name]:
            if (data_type == PICKLE_WEIGHTS_STRID):
                # Добавляем тип данных к найденному
                finded_types.append(HPM_WEIGHTS_STRID)
                # Фиксируем значения в контейнере
                weights = numpy.append(weights, pickle_data[layer_name][data_type])
                # Добавляем нулевой адрес и размер (int8)
                addresses[HPM_WEIGHTS_STRID] = [0, weights.size]
            
            # Далее аналогично. Умножение на 2 для перевода к 8-битному размеру от fp16
            if (data_type == PICKLE_BIAS_STRID):
                finded_types.append(HPM_BIAS_STRID)
                bias = numpy.append(bias, pickle_data[layer_name][data_type])
                addresses[HPM_BIAS_STRID] = [0, bias.size * 2]

            if (data_type == PICKLE_POS_SCALE_STRID):
                finded_types.append(HPM_POS_SCALE_STRID)
                pos_scale = numpy.append(pos_scale, pickle_data[layer_name][data_type])
                addresses[HPM_POS_SCALE_STRID] = [0, pos_scale.size * 2]

            if (data_type == PICKLE_NEG_SCALE_STRID):
                finded_types.append(HPM_NEG_SCALE_STRID)
                neg_scale = numpy.append(neg_scale, pickle_data[layer_name][data_type])
                addresses[HPM_NEG_SCALE_STRID] = [0, neg_scale.size * 2]
        
        # Подсчеты адресов и фиксация для каждого типа данных
        addresses[HPM_WEIGHTS_STRID][0] = address
        address += addresses[HPM_WEIGHTS_STRID][1]

        addresses[HPM_BIAS_STRID][0] = address
        address += addresses[HPM_BIAS_STRID][1]

        addresses[HPM_POS_SCALE_STRID][0] = address
        address += addresses[HPM_POS_SCALE_STRID][1]

        addresses[HPM_NEG_SCALE_STRID][0] = address
        address += addresses[HPM_NEG_SCALE_STRID][1]

        # Для каждого типа данных записываем в лог полученный адрес и размер
        for data_type, data in addresses.items():
            if data_type in finded_types:
                addr = data[0]
                size = data[1]
                pickle_log.write(f"\t{data_type} {addr} {size}")

        # Каждый найденный тип записываем в файл в определенном порядке
        if HPM_WEIGHTS_STRID in finded_types:
            weights.tofile(out_file)

        if HPM_BIAS_STRID in finded_types:
            bias.tofile(out_file)
        
        if HPM_POS_SCALE_STRID in finded_types:
            pos_scale.tofile(out_file)
        
        if HPM_NEG_SCALE_STRID in finded_types:
            neg_scale.tofile(out_file)
    out_file.close()

# Основная функция
def main():
    # парсинг аргументов командной строки
    parser = ArgParser(sys.argv)
    parser.fillArgDict(arguments)
    
    # Чтение данных и обработка
    pickle_data = load_pickle_data(arguments[INPUT_PATH])
    write_binary(pickle_data, arguments)


# От обертки получаем код возврата и завершаем работу с нужным кодом
return_code = exception_handler_wrap(main)
exit(return_code)
