#include "../../../include/modules/programComparatorModule.h"


// Запуск процесса сборки программы
exit_module_status ProgramComparatorModule::runProcess() {
    
    // Очистка кэша ошибок
    clearStdErrCache(settings.stderr_log_path.c_str());
    
    try {
        // Проверка входных настроек
        checkSettingsCorrectness();
        
        // дескрипторы файлов с программой
        std::vector<ProgramFileDesc> program_files_descriptors;

        // Заполнение вектора из дескрипторов файлов с программой
        fillProgramFilesDescriptors(program_files_descriptors);

        // Проверка присутствия и целостности всех файлов программы
        checkProgramFilesExist(program_files_descriptors);
        
        // Предварительная подоготовка файлов с весами. Поблочное копирование со смещением.
        prepareWieghtsFile(
            (settings.compiler_dir + "hpm_weights.bin").c_str(), 
            (settings.compiler_dir + "hpm_coeff").c_str()
        );

        // Создание выходной директории
        makeOutputDirectory();

        // Копирование файлов с программой в выходную директорию
        copyProgramFilesToOutDir(program_files_descriptors);

        // Сжатие в zip архив
        compressToZip(program_files_descriptors);

    } catch (const std::exception& e) {
        dumpStdErrToLog(
            throw_desc + e.what(), 
            settings.stderr_log_path.c_str()
        );
        return ModuleExitStatus::EXCEPTION;
    }
    return ModuleExitStatus::SUCCESS;
}

// Проверка корректности настроек модуля
void ProgramComparatorModule::checkSettingsCorrectness() const {
    
    // Имя архива не должно быть пустым
    if (settings.program_archive_name.empty())
        throwWithDesc(settings.program_archive_name + " <- Bad program archive name.");
    
    // Директория компилятора должна существовать
    checkDirExist(settings.compiler_dir);

}

// Заполнение вектора с дескрипторами файлов программы
void ProgramComparatorModule::fillProgramFilesDescriptors(std::vector<ProgramFileDesc>& descriptors) const {

    // Приводим массив дескрипторов к соответствующему размеру
    descriptors.resize(IPCM::program_filenames.size());

    // Проходимся по всем дескрипторам и заполняем их информацией
    for (size_t idx = 0; ProgramFileDesc& descriptor : descriptors) {
        // Имя файла
        descriptor.filename = IPCM::program_filenames[idx];
        
        // Путь к файлу (по умолчанию файлы лежат в директории компилятора)
        descriptor.path = settings.compiler_dir + IPCM::program_filenames[idx];
        
        // Проверка существования файла
        descriptor.is_exist = boost::filesystem::is_regular_file(descriptor.path.c_str());
        
        // Если файл существует, то получаем его размер. Базовый случай = 0
        if (descriptor.is_exist)
            descriptor.size = boost::filesystem::file_size(descriptor.path.c_str());
        
        // Инкрементируем индекс файла в массиве IMCM::program_filenames
        idx++;
    }

}

// Проверка целостности программы.
void ProgramComparatorModule::checkProgramFilesExist(const std::vector<ProgramFileDesc>& descriptors) const {
    // Подсчет количества не найленных файлов
    size_t count_of_not_exists_files = std::count_if(
        descriptors.begin(), descriptors.end(), 
        [](const ProgramFileDesc& desc) { return !desc.is_exist; }
    );

    // Если хотя бы 1 не найден, то выбрасываем исключение.
    if (count_of_not_exists_files > 0)
        throwWithDesc("One of the program files do not exist.");
}
    
// Создание выходной директории, если ее не существует
void ProgramComparatorModule::makeOutputDirectory() const {
    
    // Флаг существования директории
    bool is_dir_exist = boost::filesystem::is_directory(settings.program_out_dir_path.c_str());
    
    // Если директория существует, то возвращаемся
    if (is_dir_exist) {
    
        return;
    
    } else {
        
        // В ином случае создаем новую
        boost::system::error_code error_code;
        boost::filesystem::create_directory(settings.program_out_dir_path.c_str(), error_code);
        
        if (error_code == boost::system::errc::errc_t::success)
            return;
        else
            throwWithDesc(error_code.message());
        
    }
}

// Очистка директории, если она существовала ранее
void ProgramComparatorModule::clearDirectory(std::string path) const {

    // Итераторы директории
    boost::filesystem::directory_iterator current_it{path};
    boost::filesystem::directory_iterator end{};

    // Соответствие путей и типов путей, которые найдены
    std::unordered_map<std::string, PathType> pathes;
    
    // Проходимся по директории, определяем пути в директории и их типы(файл, директория)
    while(current_it != end) {

        std::string path((*current_it).path().string());
        
        PathType path_type;
        if (boost::filesystem::is_regular_file(path)) path_type = PathType::File;
        else if (boost::filesystem::is_directory(path)) path_type = PathType::Directory;
        else path_type = PathType::Directory;

        pathes[path] = path_type;

        *current_it++;
    }

    // Удаляем файлы и директории с их содержимым
    for (const auto& [path, path_type] : pathes) {
        if (path_type == PathType::File) {
            boost::filesystem::remove(path);
        } else {
            boost::filesystem::remove_all(path);
        }
    }

}

// Подготовка весов для программы
void ProgramComparatorModule::prepareWieghtsFile(std::string in, std::string out) const {
    
    // Формируем команду блочного копирования
    std::string command("dd");
    command += " if="; command += in;
    command += " of="; command += out;
    command += " bs=1 skip=8";
    
    // Запускаем и получаем ответ
    int return_code = boost::process::system(
        command,
        boost::process::std_out > settings.out_log_path.c_str(),
        boost::process::std_err > settings.stderr_log_path.c_str() 
    );

    if (return_code != 0) throwWithDesc("Prepare weitghts error.");

}

// Копирование файлов с программой в выходную директорию
void ProgramComparatorModule::copyProgramFilesToOutDir(std::vector<ProgramFileDesc>& descriptors) const {
    
    // Предварительная очистка содержимого
    clearDirectory(settings.program_out_dir_path.c_str());

    // Создание папки constants для сохранения весов
    boost::filesystem::create_directory((settings.program_out_dir_path + "constants").c_str());

    // Вроходимся по всем дескрипторам файлов программы и копируем их в нужное место
    for (const auto& descriptor : descriptors) {

        // Выходной путь определяется в зависимости от типа файла. Файлы с весами сохраняются в constants
        std::string filename = descriptor.filename;
        std::string from((settings.compiler_dir + descriptor.filename).c_str());
        std::string to;

        if (IPCM::is_cmd_file(filename) || IPCM::is_metadata_file(filename)) {
            to = (settings.program_out_dir_path + descriptor.filename).c_str();
        } else {
            to = (settings.program_out_dir_path + "constants" + descriptor.filename).c_str();
        }

        // Запуск копирования
        boost::system::error_code error_code;
        boost::filesystem::copy_file(from, to, error_code);

        if (error_code != boost::system::errc::errc_t::success)
            throwWithDesc(error_code.message());
        
    }
}

// Сжатие в zip архив, формирование окончательной программы для запуска
void ProgramComparatorModule::compressToZip(const std::vector<ProgramFileDesc>& descriptors) const {
    // Сохраняем текущую директорию и перемещаемся в директорию с программой
    boost::filesystem::path current_dir = boost::filesystem::current_path();
    boost::filesystem::current_path(settings.program_out_dir_path.c_str());

    // Формирование команды сжатия
    std::string command("zip ");
    command += (settings.program_archive_name).c_str();
    command += " ";
    
    for (const auto& descriptor : descriptors) {
        std::string filename(descriptor.filename);

        if (IPCM::is_cmd_file(filename) || IPCM::is_metadata_file(filename)) {
            command += filename + " ";
        } else {
            command += "constants/";
            command += filename + " ";
        }
    }

    // Исполнение команды
    int return_code = boost::process::system(
        command,
        boost::process::std_out > settings.out_log_path.c_str(),
        boost::process::std_err > settings.stderr_log_path.c_str()
    );

    // Возврат в исходную директорию
    boost::filesystem::current_path(current_dir);

    if (return_code != 0) throwWithDesc("Create archive error.");
}