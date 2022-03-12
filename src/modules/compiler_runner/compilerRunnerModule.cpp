
#include "../../../include/modules/compilerRunnerModule.h"

// Конструктор класса
CompilerRunnerModule::CompilerRunnerModule(const CompileRunnerSettings& settings) :
    settings(settings) {};

// Запуск процесса обработки модулем
exit_module_status CompilerRunnerModule::runProcess() {
    
    // Очистка кэша ошибок
    clearStdErrCache(settings.stderr_log_path);

    // Формирование необходимых для обработки путей
    formInternalPathes();

    // Ловим исключения, которые могут возникнуть в процессе обработки
    try {
        
        // Проверка корректности настроек
        checkSettingsCorrectness();
        // Формирование файла содержащего MetaDataInOutSize.dat
        formInOutSizeFile();
        // Формирование команд запуска
        formCommands();
        // Запуск процесса компиляции
        runCompile();
        // Проверка лога компилятора на наличие ошибок и исключений
        checkCompileErrors();
        // Проверка наличия выходных файлов в директории компилятора
        checkOutputFiles();
        // В случае отсутствия отключений происходит возврат с кодом "успешно"
        return ModuleExitStatus::SUCCESS;

    } catch (const std::exception& e) {

        // При возникновении исключения сбрасываем его в stderr cache
        std::string err_desc(throw_desc);
        err_desc += e.what();

        dumpStdErrToLog(err_desc, settings.stderr_log_path.c_str());

        return ModuleExitStatus::EXCEPTION;
    }
}

// Проверка корректности настроек модуля
void CompilerRunnerModule::checkSettingsCorrectness() const {
    // Проверка числовых параметров
    if (settings.make_n_jobs < 1)
        throwWithDesc("Number of jobs for a CMake build, it cannot be less than 1.");
    
    if (settings.num_starts < 1)
        throwWithDesc("Number of compile runs, it cannot be less than 1.");
    
    if (settings.input.B < 1) 
        throwWithDesc("Size of axes B for input tensor, it must be only positive integer number.");
    
    if (settings.input.X < 1) 
        throwWithDesc("Size of axes X for input tensor, it must be only positive integer number.");
    
    if (settings.input.Y < 1) 
        throwWithDesc("Size of axes Y for input tensor, it must be only positive integer number.");
    
    if (settings.input.L < 1) 
        throwWithDesc("Size of axes L for input tensor, it must be only positive integer number.");
    
    if (settings.output.B < 1) 
        throwWithDesc("Size of axes B for output tensor, it must be only positive integer number.");
    
    if (settings.output.X < 1) 
        throwWithDesc("Size of axes X for output tensor, it must be only positive integer number.");
    
    if (settings.output.Y < 1) 
        throwWithDesc("Size of axes Y for output tensor, it must be only positive integer number.");
    
    if (settings.output.L < 1) 
        throwWithDesc("Size of axes L for output tensor, it must be only positive integer number.");
    
    // Проверка допустимости девайса
    if (settings.current_device != Device::KCU && 
        settings.current_device != Device::MOBILE &&
        settings.current_device != Device::SERVER) {
            throwWithDesc("Unknown device type.");
        }
    
    // Проверка существования входных файлов
    checkFileExist(settings.path_to_json);
    checkFileExist(settings.path_to_weights);

    // Проверка существования директорий для путей выходных файлов и директории компилятора
    checkDirExist(settings.compiler_dir);
    checkDirExist(settings.out_log_path);
}

// Формирование внутренних путей для процесса работы модуля
void CompilerRunnerModule::formInternalPathes() {
    // MetaDataInOutSize.dat file
    MetadataInOutSize_path = settings.compiler_dir + _SpecificFileNames::MetaDataInOutSize;
    
    // hpm_scheduler file
    hpm_scheduler_path = settings.compiler_dir + _SpecificFileNames::hpm_scheduler;
}

// Формирование файла MetaDataInOutSize.dat
void CompilerRunnerModule::formInOutSizeFile() const {
    std::ofstream fout(MetadataInOutSize_path.c_str());

    // Файл содержит в себе размеры тензоров входа и выхода через пробел
    // Bin Xin Yin Lin Bout Xout Yout Lout
    if (fout.is_open()) {
        fout << std::to_string(settings.input.B) << " ";
        fout << std::to_string(settings.input.X) << " ";
        fout << std::to_string(settings.input.Y) << " ";
        fout << std::to_string(settings.input.L) << " ";

        fout << std::to_string(settings.output.B) << " ";
        fout << std::to_string(settings.output.X) << " ";
        fout << std::to_string(settings.output.Y) << " ";
        fout << std::to_string(settings.output.L);
    } else {
        throwWithDesc("MetaDataInOutSize.dat cannot be opened.");
    }

    fout.close();
}

// Добавление аргумента к команде запуска в формате --argname value
void CompilerRunnerModule::addArgument(const std::string& argname, const std::string& value) {
    exec_command += "--";
    exec_command += argname;
    exec_command += " ";
    exec_command += value;
    exec_command += " ";
}

// Формирование команды запуска скрипта
void CompilerRunnerModule::formCommands() {
    // Вторичные пути для запуска компиляции и логов компилятора
    Path weights_verification_log_path = _SpecificPathes::weights_verification_log;
    Path bias_verification_log_path = _SpecificPathes::bias_verification_log;
    Path scale_verification_log_path = _SpecificPathes::scale_verification_log;
    Path warning_data_log_path = _SpecificPathes::warning_data_log;
    Path runtime_data_log_path = _SpecificPathes::runtime_data_log;
    Path tpu_data_path = _SpecificPathes::tpu_data_log;
    
    // Формирование команды запуска
    exec_command = "./src/modules/compiler_runner/runner.sh ";
    addArgument("n_starts", std::to_string(settings.num_starts));
    addArgument("n_jobs", std::to_string(settings.make_n_jobs));
    addArgument("input_x", std::to_string(settings.input.X));
    addArgument("input_y", std::to_string(settings.input.Y));
    addArgument("current_dir", boost::filesystem::current_path().generic_string());
    addArgument("compiler_dir", settings.compiler_dir.c_str());
    addArgument("wver", weights_verification_log_path.c_str());
    addArgument("bver", bias_verification_log_path.c_str());
    addArgument("sver", scale_verification_log_path.c_str());
    addArgument("warning", warning_data_log_path.c_str());
    addArgument("runtime", runtime_data_log_path.c_str());
    addArgument("json", settings.path_to_json.c_str());
    addArgument("weights", settings.path_to_weights.c_str());
    addArgument("hpm_weights", "./hpm_weights.bin");
    addArgument("tpu_data", tpu_data_path.c_str());
}

// Запуск этапа компиляции с помощью скрипта
void CompilerRunnerModule::runCompile() const {
    
    try {
        // Запуск скрипта
        int return_code = boost::process::system(
            exec_command.c_str(),
            boost::process::std_out > settings.out_log_path.c_str(),
            boost::process::std_err > settings.stderr_log_path.c_str()
        );

        // Если лог ошибок пуст, то удаляем его
        if (boost::filesystem::is_empty(settings.stderr_log_path.c_str())) {
            clearStdErrCache(settings.stderr_log_path);
        }

    } catch (const std::exception& e) {
        std::string desc("In command ");
        desc += exec_command;
        desc += " exception: ";
        desc += e.what();
        throw std::runtime_error(desc);
    }
}

// Проверка наличия ошибок при компиляции
void CompilerRunnerModule::checkCompileErrors() const {
    
    Path warning_log = settings.compiler_dir.c_str();
    warning_log = warning_log + _SpecificPathes::warning_data_log; 
    
    // Если лог ошибок не пуст и существует, то произошла ошибка компиляции
    if (boost::filesystem::is_regular_file(settings.stderr_log_path.c_str())) {
        throwWithDesc("hpm_sheduler run error.");
    }
    // Если строка "exit with return code 1" существует в warning log, то сборка прошла неудачно
    if (isStringInFile(warning_log, "exit with return code 1")) {
        throwWithDesc("hpm_scheduler compile error. See warnind_data file.");
    }
}

// Проверка существования выходных файлов после компиляции
void CompilerRunnerModule::checkOutputFiles() const {
    int num_files = 8;
    std::vector<std::string> files(num_files);
    for (std::string& file_path : files) file_path = settings.compiler_dir.c_str();
    files[0] += "/cmd0.bin";
    files[1] += "/cmd1.bin";
    files[2] += "/cmd2.bin";
    files[3] += "/cmd3.bin";
    files[4] += "/cmd4.bin";
    files[5] += "/cmd5.bin";
    files[6] += "/cmd.json";
    files[7] += "/hpm_coeff";
    
    for (const std::string& file : files) {
        if (!boost::filesystem::is_regular_file(file)) {
            std::string err_desc = "File ";
            err_desc += file.c_str();
            err_desc += " not found after compile process.";
            throwWithDesc(err_desc);
        }
    }
}

// Проверка наличия строки в файле
bool CompilerRunnerModule::isStringInFile(const Path& file_path, const std::string& search_string) const {
    
    std::ifstream fin(file_path.c_str());
    
    if (fin.is_open()) {
        while(!fin.eof()) {
            
            std::string line;
            std::getline(fin, line);
            
            if (!line.find(search_string))
                return true;
            
        }
    } else {
        std::string err_desc = "Connot open file ";
        err_desc += file_path.c_str();
        throwWithDesc(err_desc);
    }
    fin.close();
    return false;
}
