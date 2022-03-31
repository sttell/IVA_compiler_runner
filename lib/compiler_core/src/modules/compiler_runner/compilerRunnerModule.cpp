

#include "../../../include/modules/compilerRunnerModule.h"

// Запуск процесса обработки модулем
exit_module_status CompilerRunnerModule::runProcess() {

    // Формирование необходимых для обработки путей
    formInternalPathes();

    // Ловим исключения, которые могут возникнуть в процессе обработки
    try {
        log->writeMessage("Проверка настроек модуля компиляции.");
        // Проверка корректности настроек
        checkSettingsCorrectness();
        log->writeMessage("Настройки введены корректно.");

        // Формирование файла содержащего MetaDataInOutSize.dat
        log->writeMessage("Формирование файла MetaDataInOutSize.dat");
        formInOutSizeFile();
        log->writeMessage("Формирование файла закончено успешно.");

        // Формирование команд запуска
        log->writeMessage("Формирование команд запуска.");
        formCommands();

        // Запуск процесса компиляции
        log->writeMessage("Запуск процесса компиляции.");
        Timer compile_time;
        compile_time.start();
        runCompile();
        compile_time.end();
        std::string compile_time_format = compile_time.getStringFormat("MM min SS sec");
        std::string compilation_ended("Процесс компиляции программы завершен. Время компиляции:");
        compilation_ended += compile_time_format;
        log->writeMessage(compilation_ended.c_str());

        // Проверка лога компилятора на наличие ошибок и исключений
        log->writeMessage("Проверка наличия ошибок со стороны компилятора.");
        checkCompileErrors();
        log->writeMessage("Ошибок не обнаружено.");

        // Проверка наличия выходных файлов в директории компилятора
        log->writeMessage("Проверка целостности полученной программы.");
        checkOutputFiles();
        log->writeMessage("Ошибок не обнаружено.");

        // В случае отсутствия отключений происходит возврат с кодом "успешно"

    } catch (const std::exception& e) {
        throw std::runtime_error(throw_desc + e.what());
    }
    return ModuleExitStatus::SUCCESS;
}

// Проверка корректности настроек модуля
void CompilerRunnerModule::checkSettingsCorrectness() const {
    // Проверка числовых параметров
    if (settings.make_n_jobs < 1)
        throw std::runtime_error("Количество ядер для параллельной сборки не может быть меньше 1.");

    if (settings.num_starts < 1)
        throw std::runtime_error("Количество запусков сборки не может быть меньше 1.");

    if (settings.input.B < 1)
        throw std::runtime_error("Ось B входного тензора имеет размер меньше 1.");

    if (settings.input.X < 1)
        throw std::runtime_error("Ось X входного тензора имеет размер меньше 1.");

    if (settings.input.Y < 1)
        throw std::runtime_error("Ось Y входного тензора имеет размер меньше 1.");

    if (settings.input.L < 1)
        throw std::runtime_error("Ось L входного тензора имеет размер меньше 1.");

    if (settings.output.B < 1)
        throw std::runtime_error("Ось B выходного тензора имеет размер меньше 1.");

    if (settings.output.X < 1)
        throw std::runtime_error("Ось X выходного тензора имеет размер меньше 1.");

    if (settings.output.Y < 1)
        throw std::runtime_error("Ось Y выходного тензора имеет размер меньше 1.");

    if (settings.output.L < 1)
        throw std::runtime_error("Ось L выходного тензора имеет размер меньше 1.");

    // Проверка допустимости девайса
    if (settings.current_device != Device::KCU &&
        settings.current_device != Device::MOBILE &&
        settings.current_device != Device::SERVER) {
            throw std::runtime_error("Указан неизвестный тип устройства.");
        }

    // Проверка существования входных файлов
    checkFileExist(settings.path_to_json);
    checkFileExist(settings.path_to_weights);

    // Проверка существования директорий для путей выходных файлов и директории компилятора
    checkDirExist(settings.compiler_dir);
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

    unsigned int B = settings.input.B;
    unsigned int X = settings.input.X;
    unsigned int Y = settings.input.Y;
    unsigned int L = settings.input.L;

    unsigned int align = 1;
    switch (settings.current_device)
    {
    case Device::MOBILE:
        align = 64;
        break;
    case Device::KCU:
        align = 32;
        break;
    case Device::SERVER:
        align = 128;
        break;
    }

    unsigned int extended_x = X;

    if (L == 3) L++;

    while((extended_x * Y * L) % align != 0) {
        extended_x++;
    }

    // Файл содержит в себе размеры тензоров входа и выхода через пробел
    // Bin Xin Yin Lin Bout Xout Yout Lout
    if (fout.is_open()) {
        fout << std::to_string(B) << " ";
        fout << std::to_string(extended_x) << " ";
        fout << std::to_string(Y) << " ";
        fout << std::to_string(L) << " ";

        fout << std::to_string(settings.output.B) << " ";
        fout << std::to_string(settings.output.X) << " ";
        fout << std::to_string(settings.output.Y) << " ";
        fout << std::to_string(settings.output.L);
    } else {
        throw std::runtime_error("Файл MetaDataInOutSize.dat не может быть открыт для записи.");
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
    exec_command = boost::filesystem::current_path().generic_string() + RUN_COMPILE_SCRIPT_PATH;
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
        boost::process::ipstream std_stream;
        boost::process::ipstream err_stream;

        // Запуск скрипта
        int return_code = boost::process::system(
            exec_command.c_str(),
            boost::process::std_out > std_stream,
            boost::process::std_err > err_stream
        );

        std::string stderr_output;
        std::string line;

        while (err_stream && std::getline(err_stream, line) && !line.empty())
            stderr_output += line;

        if (return_code != 1 && !stderr_output.empty()) {
            if (stderr_output.find("make: *** No rule to make target 'clean'.") != std::string::npos) {
                throw std::runtime_error("Указанная директория с компилятором не содержит Makefile для сборки.");
            }
            if (stderr_output.find("./hpm_scheduler: No such file or directory.")) {
                throw std::runtime_error("Ошибка сборки программы со стороны компилятора. Для подробностей смотреть warning_data.");
            }
            throw std::runtime_error(stderr_output);
        }

    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

// Проверка наличия ошибок при компиляции
void CompilerRunnerModule::checkCompileErrors() const {

    Path warning_log = settings.compiler_dir.c_str();
    warning_log = warning_log + _SpecificPathes::warning_data_log;

    // Если строка "exit with return code 1" существует в warning log, то сборка прошла неудачно
    if (isStringInFile(warning_log, "exit with return code 1")) {
        throw std::runtime_error("Ошибка сборки hpm_scheduler. Дополнительная информация в файле warnind_data.");
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
    files[7] += "/hpm_weights.bin";

    for (const std::string& file : files) {
        if (!boost::filesystem::is_regular_file(file) && file.find("hpm_coeff") == std::string::npos) {
            std::string err_desc = "Выходной файл ";
            err_desc += file.c_str();
            err_desc += " не найден после процесса компиляции программы.";
            throw std::runtime_error(err_desc);
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
        std::string err_desc = "Не удалось открыть файл ";
        err_desc += file_path.c_str();
        throw std::runtime_error(err_desc);
    }
    fin.close();
    return false;
}
