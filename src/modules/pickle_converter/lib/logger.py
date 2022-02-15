# Класс для удобной записи в файл
class Logger:
    # Инициализирует файл с одноразовым логом
    def __init__(self, log_path, mode='w'):
        self.log = open(log_path, mode)
    
    # Запись строки
    def write(self, string, end='\n'):
        self.log.write(string + end)
    
    # Освобождение файла
    def __del__(self):
        self.log.close()