#ifndef _INCLUDE_MODULES_METADATACREATORMODULE_H_
#define _INCLUDE_MODULES_METADATACREATORMODULE_H_

#include "../module.h"
#include "../settings/globalSettings.h"
#include "../path.h"
#include "../tpuDescriptor.h"
#include "../jsonHandler.h"
#include "../programFilesDescriptor.h"
#include <map>
#include <fstream>
#include <iostream>
#include <boost/filesystem/operations.hpp>
#include <boost/property_tree/ptree.hpp>

// Хэдер дескриптора исключений модуля
#define METADATA_CREATOR_THROW_DESC "Metadata creator error. "

using boost::property_tree::ptree;



// Implementation Metadata Creator Module - пространство имен для хранения вторичных функций используемых
// внутри модуля
namespace IMCM {

using json_body_t = ptree;

static std::vector<std::string> program_filenames {
    "cmd0.bin", "cmd1.bin", "cmd2.bin", "cmd3.bin", "cmd4.bin", "cmd5.bin", "hpm_coeff"
};

// Проверка на принадлежность файла к файлам с инструкциями(cmd.bin file)
inline bool is_cmd_file(const std::string& filename) {
    return filename.find("cmd") != std::string::npos && filename.find(".bin") != std::string::npos;
}

// Заполнение JSON списка. Принимает на вход:
// ptree - узел в котором хранится список
// vector<T> values - Значения типа T, которые сохраняются в узел
template<typename T>
void fill_ptree_list(ptree& ptree, std::vector<T> values) {
    for (const auto& value : values) {
        boost::property_tree::ptree node; node.put("", value);
        ptree.push_back(std::make_pair("", node));
    }
}

// Заполнение JSON map. Принимает на вход:
// ptree - узел в котором хранится список
// map<string, T> items - Имена узлов и соответствующие значения типа T, которые сохраняются в узел
template<typename T>
void fill_ptree_map(ptree& ptree, std::map<std::string, T> items) {
    for(const auto&[node_name, node] : items) ptree.put(node_name, node);
}

} // namespace IMCM




// Модуль, который отвечает за формирование метаданных
// программы для драйвера TPU в формате json.
class MetadataCreatorModule : public Module {
public:
    
    // Конструктор инициализирует настройки модуля и дескриптор исключений
    explicit MetadataCreatorModule(const GlobalSettings& _settings) : 
        settings(_settings.metadata_creator) { throw_desc = METADATA_CREATOR_THROW_DESC; }; 
    
    // Запуск процесса работы модуля.
    exit_module_status runProcess() override;
private:

    // Проверка корректности настроек модуля
    void checkSettingsCorrectness() const override;

    // Проверка размеров карты признаков(тензора)
    void checkMapSizeCorrect(const MapSize& map) const;

    // Хаполнение списка дескрипторов файлов в соответствии со списком IMCM::program_filenames
    void fillProgramFileDescriptors(std::vector<ProgramFileDesc>& file_descriptors) const;

    // Проверка корректности заполнения дескрипторов файлов программы.
    void checkProgramFileDescriptorsCorrectness(const std::vector<ProgramFileDesc>& file_descriptors) const;

    // Создания JSON блока с параметрами устройства по дескриптору устройства.
    void createHardwareParamsBlock(const TPUDescriptor& tpu_descriptor, 
        ptree& hardware_parameters_block) const;

    // Создание блока с описанием файла с инструкциями для одного файла по дескриптору.
    void createOneInstructionBlock(const ProgramFileDesc& file_descriptor, 
        ptree& block) const;

    // Создание блока с описанием файлов с инструкциями по списку дескрипторов файлов.
    void createInstructionsBlock(const std::vector<ProgramFileDesc>& file_descriptors, 
        ptree& instructions_block) const;
    
    // Создание блока с описанием файлов с константами по списку дескрипторов файлов.
    void createConstantsBlock(const std::vector<ProgramFileDesc>& file_descriptors, 
        ptree& constants_block) const;

    // Создание блока с описанием параметров входного тензора
    void createInputBlock(ptree& inputs_block) const;

    // Создание блока с описание выходного тензора
    void createOutputsBlock(ptree& outputs_block) const;

    // Заполнение блока со схемой DDR. 
    void createRamSchemeBlock(const std::vector<ProgramFileDesc>& file_descriptors, 
        ptree& ram_scheme_block) const;

    // Заполнение тела JSON описания метаданных.
    void createMetadataBody(IMCM::json_body_t& metadata, 
                            const std::vector<ProgramFileDesc>& file_descriptors, 
                            const TPUDescriptor& tpu_descriptor) const;

    // Настройки модуля
    MetadataCreatorSettings settings;

};


#endif // _INCLUDE_MODULES_METADATACREATORMODULE_H_