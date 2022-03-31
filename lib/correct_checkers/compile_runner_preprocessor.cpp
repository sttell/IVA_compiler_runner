#include "compile_runner_preprocessor.h"

#include "lib/compiler_core/include/compilerCore.h"
#include "lib/thread_api/statusbuffer_cache.h"

#include <boost/filesystem.hpp>
#include <QRegularExpression>
#include <iostream>
#include <memory>
#include <QThread>

// Конструктор инициализирует указатели и состояния внутренних полей
// CompileVarSettingsDescriptor compile_settings  - Вариативные настройки компиляции
// StatusBufferCache*           status_bar        - Кэш статус бара
// SettingsBuffer*              _parent_settings  - Буффер с настройками главного окна
// InterruptBuffer*             _interrupt_buffer - Буффер для завершения работы потока
CompileRunnerProcessor::CompileRunnerProcessor(
        CompileVarSettingsDescriptor compile_settings,
        StatusBufferCache* status_bar,
        SettingsBuffer* _parent_settings,
        InterruptBuffer* _interrupt_buffer) :
    var_settings(compile_settings),
    status_cache(status_bar),
    parent_settings(_parent_settings),
    interrupt_buffer(_interrupt_buffer)
{

}

// Оператор для запуска работы в потоке
void CompileRunnerProcessor::operator()()
{
    bool retcode = runProcessing();
}


// Запуск процесса компиляции
bool CompileRunnerProcessor::runProcessing()
{
    // Указатель на пайплайн компиляции
    std::shared_ptr pipe_ptr = std::make_shared<Pipeline>();

    // Указатель на глобальные настройки компиляции
    std::shared_ptr global_settings_ptr = std::make_shared<GlobalSettings>();

    try {
        // Проверка регулярных настроек
        checkRegularSettings();
        // Формирования дескриптора глобальных настроек
        formGlobalSettingsDesc(global_settings_ptr.get());
        // Создание пайплайна компиляции
        createPipeline(pipe_ptr.get());
        // Запуск ядра компиляции
        runCompileProcess(global_settings_ptr.get(), pipe_ptr.get());

    }  catch (const std::exception& e) {
        // обработка исключений вызываемых ядром компилятора при неверных конфигурациях
        status_cache->writeMessage(e.what(), "auto", MessageColor::error);
        return false;
    }
    return true;
}


// Проверка статических настроек компиляции (Окна с настройками)
void CompileRunnerProcessor::checkRegularSettings() {

    // Входим в группу с настройками
    parent_settings->beginGroup(GLOBAL_SETTINGS_GROUP);

    // Проверка корректности конвертации
    bool is_num_runs, is_num_cores(true), is_input_scale, is_output_scale;

    // Получение данных
    QString compiler_dir = parent_settings->value("CompilerDirectory", "").toString();
    int num_runs = parent_settings->value("CMakeNumberRuns").toInt(&is_num_runs);
    int num_cores = parent_settings->value("CMakeNumberCores").toInt(&is_num_cores);
    QString archive_name = parent_settings->value("ArchiveName", "").toString();
    float input_scale = parent_settings->value("InputScale").toFloat(&is_input_scale);
    float output_scale = parent_settings->value("OutputScale").toFloat(&is_output_scale);
    QString kcu_api = parent_settings->value("KcuAPIVersion").toString();
    QString kcu_ip = parent_settings->value("KcuIPVersion").toString();
    QString mobile_api = parent_settings->value("MobileAPIVersion").toString();
    QString mobile_ip = parent_settings->value("MobileIPVersion").toString();
    QString server_api = parent_settings->value("ServerAPIVersion").toString();
    QString server_ip = parent_settings->value("ServerIPVersion").toString();
    bool make_parallel = parent_settings->value("CMakeParallelMode").toBool();

    parent_settings->endGroup();

    // Обработка неверных событий

    if (!boost::filesystem::is_directory(compiler_dir.toStdString())) {
        throw std::runtime_error("Директория с компилятором не найдена. Проверьте общие настройки компиляции");
    }

    if (!is_num_runs || num_runs < 0) {
        throw std::runtime_error("Число запусков сборки программы указано неверно. Проверьте настройки компиляции.");
    }

    if (make_parallel) {
        if (!is_num_cores || num_cores < 1) {
            throw std::runtime_error("Число ядер при параллельной сборке указано неверно. Проверьте настройки компиляции.");
        }
    }

    if (!is_input_scale) {
        throw std::runtime_error("Scale входного тензора указан в неверном формате. Проверьте настройки компиляции.");
    }

    if (!is_output_scale) {
        throw std::runtime_error("Scale выходного тензора указан в неверном формате. Проверьте настройки компиляции.");
    }

    QRegularExpression device_ip_api_rx("^(\\d+).(\\d+).(\\d+)$");

    bool is_api_match(false), is_ip_match(false);

    if (var_settings.device_index == 0) {
        // MOBILE
        is_ip_match = device_ip_api_rx.match(mobile_ip).hasMatch();
        is_api_match = device_ip_api_rx.match(mobile_api).hasMatch();

    } else if (var_settings.device_index == 1) {
        // KCU
        is_ip_match = device_ip_api_rx.match(kcu_ip).hasMatch();
        is_api_match = device_ip_api_rx.match(kcu_api).hasMatch();
    } else if (var_settings.device_index == 2) {
        // SERVER
        is_ip_match = device_ip_api_rx.match(server_ip).hasMatch();
        is_api_match = device_ip_api_rx.match(server_api).hasMatch();
    }

    if (!is_ip_match) {
        throw std::runtime_error("IP версия устройства не указана, либо имеет неверный формат. Проверьте настойки компиляции.");
    }
    if (!is_api_match) {
        throw std::runtime_error("API версия устройства не указана, либо имеет неверный формат. Проверьте настойки компиляции.");
    }

    // В случае прохождения всех этапов выдаем сообщение в лог
    status_cache->writeMessage("Постоянные настройки компиляции проверены. Все верно определено.");
}

// Формирование глобальных настроек компилятора
void CompileRunnerProcessor::formGlobalSettingsDesc(GlobalSettings* global_settings)
{

    // Собр настроек с буффера
    parent_settings->beginGroup(GLOBAL_SETTINGS_GROUP);

    QString compiler_dir = parent_settings->value("CompilerDirectory", "").toString();
    int num_runs = parent_settings->value("CMakeNumberRuns").toInt();
    int num_cores = parent_settings->value("CMakeNumberCores").toInt();
    QString archive_name = parent_settings->value("ArchiveName", "").toString();
    float input_scale = parent_settings->value("InputScale").toFloat();
    float output_scale = parent_settings->value("OutputScale").toFloat();
    QString kcu_api = parent_settings->value("KcuAPIVersion").toString();
    QString kcu_ip = parent_settings->value("KcuIPVersion").toString();
    QString mobile_api = parent_settings->value("MobileAPIVersion").toString();
    QString mobile_ip = parent_settings->value("MobileIPVersion").toString();
    QString server_api = parent_settings->value("ServerAPIVersion").toString();
    QString server_ip = parent_settings->value("ServerIPVersion").toString();
    bool make_parallel = parent_settings->value("CMakeParallelMode").toBool();

    parent_settings->endGroup();

    // Формирование глоабльных настроек

    // Настройки изменения оптимизаций
    global_settings->optimization_change.optimization_settings_header = (compiler_dir + "/Libs/tpu/hpm_options.h").toStdString();
    global_settings->optimization_change.is_input_optimization = var_settings.is_input_optimization;
    global_settings->optimization_change.is_preload_biases = var_settings.is_preload_bias_scales;
    global_settings->optimization_change.is_preload_filters = var_settings.is_preload_filters;
    global_settings->optimization_change.is_reorder_data = var_settings.is_reorder_data;
    global_settings->optimization_change.is_tpu_debug_mode = var_settings.is_tpu_debug;

    // Настройки Pickle converter
    global_settings->pickle_converter.pickle_file_path = var_settings.weights_path.toStdString();
    global_settings->pickle_converter.out_log_path = compiler_dir.toStdString() + "/pickle.log";
    global_settings->pickle_converter.reconstruct_log_path = compiler_dir.toStdString() + "/pickle_reconstruct.log";
    global_settings->pickle_converter.weights_out_path = compiler_dir.toStdString() + "/weights.bin";

    // Настройки проверщика адресов
    global_settings->addr_checker.json_path = var_settings.json_path.toStdString();
    global_settings->addr_checker.out_json_path = var_settings.json_path.toStdString();
    global_settings->addr_checker.pickle_buffer_path = compiler_dir.toStdString() + "/pickle.log";

    // Настройки модуля запуска компиляции

    Device current_device;
    switch (var_settings.device_index)
    {
        case 0:
            current_device = Device::MOBILE;
            break;
        case 1:
            current_device = Device::KCU;
            break;
        case 2:
            current_device = Device::SERVER;
            break;
    }

    QStringList input_sizes = var_settings.input_size.remove(" ").split(",");
    MapSize input_map;
    input_map.B = input_sizes[0].toInt(); input_map.Y = input_sizes[2].toInt();
    input_map.X = input_sizes[1].toInt(); input_map.L = input_sizes[3].toInt();

    QStringList output_sizes = var_settings.output_size.remove(" ").split(",");
    MapSize output_map;
    output_map.B = output_sizes[0].toInt(); output_map.Y = output_sizes[2].toInt();
    output_map.X = output_sizes[1].toInt(); output_map.L = output_sizes[3].toInt();

    // TODO При добавлении модуля конвертации JSON поменять логику
    QString hpm_json_path = var_settings.json_path;

    QString weights_bin_path(var_settings.weights_path);
    if (var_settings.pipe_pickle_convert)
        weights_bin_path = global_settings->pickle_converter.weights_out_path.c_str();

    global_settings->compiler_runner.input = input_map;
    int make_n_jobs = 1;
    if (make_parallel)
        make_n_jobs = num_cores;

    global_settings->compiler_runner.compiler_dir = compiler_dir.toStdString();
    global_settings->compiler_runner.current_device = current_device;
    global_settings->compiler_runner.make_n_jobs = make_n_jobs;
    global_settings->compiler_runner.num_starts = num_runs;
    global_settings->compiler_runner.output = output_map;
    global_settings->compiler_runner.path_to_json = hpm_json_path.toStdString();
    global_settings->compiler_runner.path_to_weights = weights_bin_path.toStdString();


    // Настройки модуля формирования метаданных
    QString device_api, device_ip;

    switch(current_device) {
    case Device::MOBILE:
        device_api = mobile_api;
        device_ip  = mobile_ip;
        break;
    case Device::KCU:
        device_api = kcu_api;
        device_ip  = kcu_ip;
        break;
    case Device::SERVER:
        device_api = server_api;
        device_ip  = server_ip;
        break;
    }

    Paddings input_paddings;
    QStringList input_pad_up = var_settings.input_pad_up.remove(" ").split(",");
    QStringList input_pad_down = var_settings.input_pad_down.remove(" ").split(",");
    input_paddings.B.left = input_pad_up[0].toInt(); input_paddings.X.left = input_pad_up[1].toInt();
    input_paddings.Y.left = input_pad_up[2].toInt(); input_paddings.L.left = input_pad_up[3].toInt();
    input_paddings.B.right = input_pad_down[0].toInt(); input_paddings.X.right = input_pad_down[1].toInt();
    input_paddings.Y.right = input_pad_down[2].toInt(); input_paddings.L.right = input_pad_down[3].toInt();

    Paddings output_paddings;
    QStringList output_pad_up = var_settings.output_pad_up.remove(" ").split(",");
    QStringList output_pad_down = var_settings.output_pad_down.remove(" ").split(",");
    output_paddings.B.left = output_pad_up[0].toInt(); output_paddings.X.left = output_pad_up[1].toInt();
    output_paddings.Y.left = output_pad_up[2].toInt(); output_paddings.L.left = output_pad_up[3].toInt();
    output_paddings.B.right = output_pad_down[0].toInt(); output_paddings.X.right = output_pad_down[1].toInt();
    output_paddings.Y.right = output_pad_down[2].toInt(); output_paddings.L.right = output_pad_down[3].toInt();

    global_settings->metadata_creator.api_version = device_api.toStdString();
    global_settings->metadata_creator.ip_version  = device_ip.toStdString();
    global_settings->metadata_creator.compiler_dir = compiler_dir.toStdString();
    global_settings->metadata_creator.device_type = current_device;
    global_settings->metadata_creator.input_map = input_map;
    global_settings->metadata_creator.output_map = output_map;
    global_settings->metadata_creator.input_map_scale = input_scale;
    global_settings->metadata_creator.output_map_scales = output_scale;
    global_settings->metadata_creator.paddings_in = input_paddings;
    global_settings->metadata_creator.paddings_out = output_paddings;

    // Настройки модуля сборки программы
    global_settings->program_comparator.compiler_dir = compiler_dir.toStdString();
    global_settings->program_comparator.is_dump_test_data = var_settings.is_add_logs;
    global_settings->program_comparator.program_archive_name = archive_name.toStdString();
    global_settings->program_comparator.program_out_dir_path = var_settings.output_directory_path.toStdString();
    global_settings->program_comparator.program_out_dir_path = global_settings->program_comparator.program_out_dir_path + var_settings.output_directory_name.toStdString();
}

// Запуск ядра компиляции
void CompileRunnerProcessor::runCompileProcess(GlobalSettings* glob, Pipeline* pipe)
{
    CompilerCore core(status_cache, *pipe, *glob, interrupt_buffer);
    core.runProcess();
}

// Формирование пайплайна компиляции
void CompileRunnerProcessor::createPipeline(Pipeline* pipe)
{

    pipe->setModule(Modules::ChangeOptimizatons);
    if (var_settings.pipe_json_convert)
        pipe->setModule(Modules::JsonConverter);
    if (var_settings.pipe_pickle_convert)
        pipe->setModule(Modules::PickleConverter);
    if (var_settings.pipe_address_check)
        pipe->setModule(Modules::AddrChecker);
    if (var_settings.pipe_compile)
        pipe->setModule(Modules::CompileRunner);
    if (var_settings.pipe_create_metadata)
        pipe->setModule(Modules::MetadataCreator);
    if (var_settings.pipe_make_output)
        pipe->setModule(Modules::ProgramComparator);
}

// Высвобождение занимаемых ресурсов
CompileRunnerProcessor::~CompileRunnerProcessor()
{
    status_cache = nullptr;
    parent_settings = nullptr;
    interrupt_buffer = nullptr;

    delete status_cache;
    delete parent_settings;
    delete interrupt_buffer;
}
