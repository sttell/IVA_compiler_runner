#include "../../../include/modules/addressCheckerModule.h"

exit_module_status AddressCheckerModule::runProcess() {
    // В любом из методов может возникнуть исключительная ситуация
    // которая записывается в лог с ошибками.
    // Все выбрасываемые исключения внутри методов необходимо
    // выбрасывать в виде std::runtime_error(description).
    try{
        
        // Проверка правильности настроек
        checkSettingsCorrectness();
        // Чтение буффера PickleConverter
        readPickleBuffer();
        // Чтение Json файла с описанием сети в формате hpm_scheduler
        readJSON();
        // Корректировка адресов и размеров
        correctData();
        // Выгрузка json файла с исправлениями
        dumpJSON();
    
    } catch (const std::runtime_error& e) {
        // Пытаемся открыть лог из настроек.
        std::string err_log_path = settings.stderr_log_path.c_str();
        std::ofstream err_log;

        try {
        
            err_log.open(err_log_path);
            if (!err_log.is_open()) throw std::runtime_error("Err log don't opened.");
        
        } catch (const std::exception& log_ex){
        
            err_log_path = DEFAUL_STDERR_PATH;
            err_log.open(err_log_path);
            err_log << log_ex.what() << std::endl;

        }
        // Записываем описание исключения
        err_log << e.what() << std::endl;
        err_log.close();
        return ModuleExitStatus::EXCEPTION;
    }
    return ModuleExitStatus::SUCCESS;
};

// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void AddressCheckerModule::checkFileExist(const Path& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!path.isExists()) {
        std::string err_desc = THROW_DESC;
        err_desc += "File ";
        err_desc += path.c_str();
        err_desc += " not found.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}

// Проверка настройки для выходного файла
void AddressCheckerModule::checkDirExist(const Path& path) const {
    // Директория ведущая к файлу должна существовать
    if (!path.isExistsPathDirectory()) {
        std::string err_desc = THROW_DESC;
        err_desc += "Directory ";
        err_desc += path.c_str();
        err_desc += " with file not found.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    if (path.back() == SLASH) {
        std::string err_desc = THROW_DESC;
        err_desc += "Path ";
        err_desc += path.c_str();
        err_desc += " maybe only file path, not directory!\n";
        throw std::runtime_error(err_desc.c_str());
    }
}

// Проверка корректности настроек
void AddressCheckerModule::checkSettingsCorrectness() const {
    // Проверка наличия входных файлов
    checkFileExist(settings.json_path);
    checkFileExist(settings.pickle_buffer_path);
    
    // Проверка существования директории
    checkDirExist(settings.out_log_path);
    checkDirExist(settings.out_json_path);
}
