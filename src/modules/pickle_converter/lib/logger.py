# Класс для удобной записи в файл
class Logger:
    # Инициализирует файл с одноразовым логом или поток вывода.
    # log_path    - путь к файлу с логом, либо поток вывода
    # mode        - режим работы с файлом
    # stream_mode - режим работы с потоком вывода
    def __init__(self, log_path, mode='w', stream_mode=False):
        self.log = log_path
        if not stream_mode:
            self.log = open(log_path, mode)
    
    # Запись строки
    def write(self, string, end='\n'):
        self.log.write(string + end)
    
    # Освобождение файла
    def __del__(self):
        self.log.close()