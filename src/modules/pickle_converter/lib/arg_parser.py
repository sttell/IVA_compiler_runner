# Класс для извлечения аргументов командной строки
# Извлекает аргументы вида arg_name=arg_value
class ArgParser:
    def __init__(self, argv):
        # Список аргументов
        self.argv = argv

    def _extractValue(self, arg):
        # Метод извлекающий значение аргумента
        return arg.split('=')[-1]

    def _findArgument(self, name):
        # Итерация по списку аргументов и поиск совпадения имени
        # Выдает флаг успешности поиска и аргумент
        for arg in self.argv:
            if name in arg:
                return True, arg
        return False, None

    def getArgument(self, name, arg_type=str):
        # Метод позволяющий получить значение аргумента по имени
        # В случае, если аргумент не найден, то выпадает исключение.
        is_finded, arg = self._findArgument(name)
        if is_finded:
            return arg_type(self._extractValue(arg))
        raise ValueError(f"Argument {name} not found")
    
    def fillArgDict(self, arg_dict):
        for key, item in arg_dict.items():
            value = self.getArgument(key, type(item))
            arg_dict[key] = value
        return