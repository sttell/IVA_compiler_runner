#ifndef _INCLUDE_MODULES_PROGRAMCOMPARATORMODULE_H_
#define _INCLUDE_MODULES_PROGRAMCOMPARATORMODULE_H_

#include "../module.h"
#include "../settings/globalSettings.h"
#include "../programFilesDescriptor.h"
#include <boost/filesystem/operations.hpp>
#include <boost/process.hpp>

// Кэдер исключения для модуля Program Comparator
#define PROGRAM_COMAPRATOR_THROW_DESC "Program comparator module. "

// Пространство имен содержащее функции необходимые для имплементации 
// модуля Program Comparator
namespace IPCM 
{

// Проверка на принадлежность файла к cmd инструкциям
inline bool is_cmd_file(std::string filename) {
    return filename.find(".bin") != std::string::npos;
}

// Проверка на принадлежность файла к метаданным
inline bool is_metadata_file(std::string filename) {
    return filename == "metadata.json";
}

// Список имен файлов программы
static std::vector<std::string> program_filenames = {
    "cmd0.bin", "cmd1.bin", "cmd2.bin", "cmd3.bin", "cmd4.bin", "cmd5.bin",
    "hpm_coeff", "metadata.json", "cmd.json"
};

} // namespace IPCM


// Модуль, который отвечает за сборку программы из файлов в единую директорию и архив готовый для запуска
class ProgramComparatorModule : public Module {
public:
    // Инициализирует настройки и хэдер дескриптора ошибки
    explicit ProgramComparatorModule(const GlobalSettings& _settings, StatusBufferCache* status_bar) :
        Module(status_bar, PROGRAM_COMAPRATOR_THROW_DESC), settings(_settings.program_comparator) {};
    ~ProgramComparatorModule() {log=nullptr; delete log;};
    // Запуск процесса сборки программы
    exit_module_status runProcess() override;

private:
    // Проверка корректности настроек модуля
    void checkSettingsCorrectness() const override;

    // Заполнение вектора с дескрипторами файлов программы
    void fillProgramFilesDescriptors(std::vector<ProgramFileDesc>& descriptors) const;

    // Проверка целостности программы.
    void checkProgramFilesExist(const std::vector<ProgramFileDesc>& descriptors) const;

    // Создание выходной директории, если ее не существует
    void makeOutputDirectory() const;
    
    // Очистка директории, если она существовала ранее
    void clearDirectory(std::string path) const;
    
    // Копирование файлов с программой в выходную директорию
    void copyProgramFilesToOutDir(std::vector<ProgramFileDesc>& descriptors) const;

    // Сжатие в zip архив, формирование окончательной программы для запуска
    void compressToZip(const std::vector<ProgramFileDesc>& descriptors) const;

    // Сохранение файлов tpu_data и cache_data в директорию с программой
    void saveTestLogs();

    // Настройки модуля
    ProgramComparatorSettings settings;
};

#endif // _INCLUDE_MODULES_PROGRAMCOMPARATORMODULE_H_
