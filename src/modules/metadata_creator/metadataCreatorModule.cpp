#include "../../../include/modules/metadataCreatorModule.h"

    // Запуск процесса работы модуля.
exit_module_status MetadataCreatorModule::runProcess() {
    
    // Очистка кэша ошибок
    clearStdErrCache(settings.stderr_log_path);


    try {
        // Проверяем настройки модуля на корректность значений
        checkSettingsCorrectness();

        // Дескрипы файлов программы
        std::vector<IMCM::ProgramFileDesc> file_descriptors;
        
        // Инициализация дескрипторов файлов программы
        fillProgramFileDescriptors(file_descriptors);

        // Проверка корректности значений дескрипторов(наличия файлов в директории)
        checkProgramFileDescriptorsCorrectness(file_descriptors);

        // Дескриптор устройства (Hardware descriptor)
        TPUDescriptor tpu_desc(settings.device_type);

        // JSON тело с метаданными
        IMCM::json_body_t metadata;

        // Создаем структуру JSON файла и заполняем
        createMetadataBody(metadata, file_descriptors, tpu_desc);
        
        // Обработчик JSON формата с базовым отступом в 4 пробела
        JsonHandler js_handler(4);

        // Сбрасываем JSON по указанному пути
        js_handler.dump(settings.compiler_dir + "metadata.json", metadata);
    
    } catch (const std::exception& e) {

        // В случае возникновения исключения останавливаем процесс обработки и логируем ошибку
        std::string err_desc(throw_desc + e.what());
        dumpStdErrToLog(err_desc, settings.stderr_log_path.c_str());
        return ModuleExitStatus::EXCEPTION;
    
    }

    return ModuleExitStatus::SUCCESS;

};

// Проверка корректности настроек модуля
void MetadataCreatorModule::checkSettingsCorrectness() const {
    // Проверка размеров выходных и входных тензоров
    checkMapSizeCorrect(settings.input_map);
    checkMapSizeCorrect(settings.output_map);
    
    // Проверка существования директории компилятора
    checkDirExist(settings.compiler_dir);
};

// Проверка размеров карты признаков(тензора)
void MetadataCreatorModule::checkMapSizeCorrect(const MapSize& map) const {
    // Если одна из размерностей отрицательна, то выбрасываем исключение
    if (map.B < 0 || map.L < 0 || map.X < 0 || map.Y < 0) {
        throwWithDesc("Map sizes must be only positive integer number, not negative.");
    }
};


// Хаполнение списка дескрипторов файлов в соответствии со списком IMCM::program_filenames
void MetadataCreatorModule::fillProgramFileDescriptors(
    std::vector<IMCM::ProgramFileDesc>& file_descriptors
) const {
    // Приводим массив дескрипторов к соответствующему размеру
    file_descriptors.resize(IMCM::program_filenames.size());

    // Проходимся по всем дескрипторам и заполняем их информацией
    for (size_t idx = 0; IMCM::ProgramFileDesc& descriptor : file_descriptors) {
        // Имя файла
        descriptor.filename = IMCM::program_filenames[idx];
        
        // Путь к файлу (по умолчанию файлы лежат в директории компилятора)
        descriptor.path = settings.compiler_dir + IMCM::program_filenames[idx];
        
        // Проверка существования файла
        descriptor.is_exist = boost::filesystem::is_regular_file(descriptor.path.c_str());
        
        // Если файл существует, то получаем его размер. Базовый случай = 0
        if (descriptor.is_exist)
            descriptor.size = boost::filesystem::file_size(descriptor.path.c_str());
        
        // Инкрементируем индекс файла в массиве IMCM::program_filenames
        idx++;
    }
    
};

// Проверка корректности заполнения дескрипторов файлов программы.
void MetadataCreatorModule::checkProgramFileDescriptorsCorrectness(
    const std::vector<IMCM::ProgramFileDesc>& file_descriptors
) const{
    // Подсчет количества не найленных файлов
    size_t count_of_not_exists_files = std::count_if(
        file_descriptors.begin(), file_descriptors.end(), 
        [](const IMCM::ProgramFileDesc& desc) { return !desc.is_exist; }
    );

    // Если хотя бы 1 не найден, то выбрасываем исключение.
    if (count_of_not_exists_files > 0)
        throwWithDesc("One of the cmdN.bin files do not exist.");
};

// Создания JSON блока с параметрами устройства по дескриптору устройства.
void MetadataCreatorModule::createHardwareParamsBlock(
    const TPUDescriptor& tpu_descriptor, 
    ptree& hardware_parameters_block
) const {
    
    ptree lut_activation_params_list; // Подблок с параметрами LUT активаций
    ptree me_sa_size_list;            // Подблок с параметрами размеров ME ядра

    // Заполнение подблоков
    IMCM::fill_ptree_list<size_t>(me_sa_size_list, {tpu_descriptor.me_sa_size.first, tpu_descriptor.me_sa_size.second});
    IMCM::fill_ptree_map<size_t>(lut_activation_params_list, 
        {
            {"input_bw", tpu_descriptor.lut_act_input_bw},
            {"lut_bw", tpu_descriptor.lut_act_lut_bw},
            {"lut_depth", tpu_descriptor.lut_act_lut_depth},
            {"output_bw", tpu_descriptor.lut_act_output_bw}
        }
    );
    
    // Заполнение блока с параметрами устройства
    hardware_parameters_block.put("ddr_word_len", tpu_descriptor.ddr_word_len);
    hardware_parameters_block.put("ddr_bank_capacity", tpu_descriptor.ddr_bank_capacity);
    hardware_parameters_block.put("ddr_num_banks", tpu_descriptor.ddr_num_banks);
    hardware_parameters_block.put("cache_single_port_mem", tpu_descriptor.cache_single_port);
    hardware_parameters_block.put("cache_word_len", tpu_descriptor.cache_word_len);
    hardware_parameters_block.put("cache_bank_capacity", tpu_descriptor.cache_bank_capacity);
    hardware_parameters_block.put("cache_num_banks", tpu_descriptor.cache_num_banks);
    hardware_parameters_block.put("data_int_size", tpu_descriptor.data_int_size);
    hardware_parameters_block.put("me_sa_type", tpu_descriptor.me_sa_type);
    hardware_parameters_block.add_child("me_sa_size", me_sa_size_list);
    hardware_parameters_block.put("me_sa_mem_capacity", tpu_descriptor.me_sa_mem_capacity);
    hardware_parameters_block.put("me_ps_buf_capacity", tpu_descriptor.me_ps_buf_capacity);
    hardware_parameters_block.put("me_ps_bias_buf_capacity", tpu_descriptor.me_ps_bias_buf_capacity);
    hardware_parameters_block.add_child("lut_activation_params", lut_activation_params_list);
    hardware_parameters_block.put("me_sa_wmm_use", tpu_descriptor.me_sa_wmm_use);
    hardware_parameters_block.put("ve_pdp_channel_number", tpu_descriptor.ve_pdp_channel_number);
    hardware_parameters_block.put("ve_pdp_mult_number", tpu_descriptor.ve_pdp_mult_number);
    hardware_parameters_block.put("ve_ewp_channel_number", tpu_descriptor.ve_ewp_channel_number);
    hardware_parameters_block.put("ve_ewp_cache_bank_capacity", tpu_descriptor.ve_ewp_cache_bank_capacity);
    hardware_parameters_block.put("ve_ewp_cache_num_banks", tpu_descriptor.ve_ewp_cache_num_banks);
    hardware_parameters_block.put("cu_argv_number", tpu_descriptor.cu_argv_number);
    hardware_parameters_block.put("me_frequency", tpu_descriptor.me_frequency);
    hardware_parameters_block.put("ddr_frequency", tpu_descriptor.ddr_frequency);
    hardware_parameters_block.put("profiler_time_resolution", tpu_descriptor.profiler_time_resolution);
    hardware_parameters_block.put("dtu_timing_initial", tpu_descriptor.dtu_timing_initial);
    hardware_parameters_block.put("dtu_timing_latency", tpu_descriptor.dtu_timing_latency);
    hardware_parameters_block.put("me_timing_initial_ff", tpu_descriptor.me_timing_initial_ff);
    hardware_parameters_block.put("me_timing_initial_sdp", tpu_descriptor.me_timing_initial_sdp);
    hardware_parameters_block.put("me_timing_initial", tpu_descriptor.me_timing_initial);
    hardware_parameters_block.put("me_timing_latency", tpu_descriptor.me_timing_latency);
    hardware_parameters_block.put("ve_timing_initial_pdp", tpu_descriptor.ve_timing_initial_pdp);
    hardware_parameters_block.put("ve_timing_initial_ewp", tpu_descriptor.ve_timing_initial_ewp);
    hardware_parameters_block.put("ve_timing_latency", tpu_descriptor.ve_timing_latency);
    hardware_parameters_block.put("ddr_page_size", tpu_descriptor.ddr_page_size);
    hardware_parameters_block.put("ddr_bandwidth_ideal", tpu_descriptor.ddr_bandwith_ideal);
    hardware_parameters_block.put("cu_start_delay", tpu_descriptor.cu_start_delay);
};

// Создание блока с описанием файла с инструкциями для одного файла по дескриптору.
void MetadataCreatorModule::createOneInstructionBlock(
    const IMCM::ProgramFileDesc& file_descriptor,
    ptree& block
) const {
    block.put("size", file_descriptor.size);
    block.put("file", file_descriptor.filename);
};

// Создание блока с описанием файлов с инструкциями по списку дескрипторов файлов.
void MetadataCreatorModule::createInstructionsBlock(
    const std::vector<IMCM::ProgramFileDesc>& file_descriptors, 
    ptree& instructions_block
) const {
    
    // Компаратор для проверки на принадлежность к CMD файлам
    auto is_cmd_comparator = [](const IMCM::ProgramFileDesc& file_desc) { return IMCM::is_cmd_file(file_desc.filename); };
    
    // Подсчет количества файлов CMD с помощью компаратора
    size_t num_instruction_files = std::count_if(file_descriptors.begin(), file_descriptors.end(), is_cmd_comparator);
    
    // Инициализируем вектор с подблоками размером с количество файлов с инструкциями
    std::vector<ptree> cmd_blocks(num_instruction_files);

    // Заполняем подблоки с инструкциями для CMD файлов
    for(size_t idx=0; ptree& cmd_block : cmd_blocks) {
        if (is_cmd_comparator(file_descriptors.at(idx))) {
            createOneInstructionBlock(file_descriptors.at(idx), cmd_block);
            instructions_block.push_back(std::make_pair("", cmd_block));
        }
        idx++;
    }

};
    
// Создание блока с описанием файлов с константами по списку дескрипторов файлов.
void MetadataCreatorModule::createConstantsBlock(
    const std::vector<IMCM::ProgramFileDesc>& file_descriptors, 
    ptree& constants_block
) const {
    // Тело блока
    ptree block_body;
    // Дескрипторы файлов с константами
    std::vector<IMCM::ProgramFileDesc> constants_descriptors;

    // Заполняем дескрипторы файлов с константами. Файлы с константами - все, что не являются CMD файлами.
    for (const IMCM::ProgramFileDesc& descriptor : file_descriptors) {
        if (!IMCM::is_cmd_file(descriptor.filename)) {
            constants_descriptors.push_back(descriptor);
        }
    }

    // Если файлов с константами не найдено, то это является исключительной ситуацией
    if (constants_descriptors.empty())
        throwWithDesc("Constants files not found. Check module implementation.");
        

    // Проходимся по дейскрипторам файлов с константами и заполняем нужную информацию в подблоки
    for (size_t idx=0; IMCM::ProgramFileDesc& file_descriptor : constants_descriptors) {
        ptree constant_files_block;
        ptree constant_space;
        constant_space.put("address", 0);
        constant_space.put("size", file_descriptor.size);
        constant_space.put("file", "constants/" + file_descriptor.filename);
        
        constant_files_block.push_back(std::make_pair("", constant_space));
        constants_block.add_child(std::to_string(idx), constant_files_block);

        idx++;
    }

};

// Создание блока с описанием параметров входного тензора
void MetadataCreatorModule::createInputBlock(ptree& inputs_block) const {
    // Первое пространство DDR
    ptree first_input_space;
    // Первый входной узел
    ptree first_node;
    // Список размерностей со стороны пользователя
    ptree user_shape_list;

    // Заполнение размерностей
    IMCM::fill_ptree_list<axis_size_t>(user_shape_list, 
        {settings.input_map.B, settings.input_map.X, settings.input_map.Y, settings.input_map.L});

    // Порядок расположение осей со стороны пользователя и его заполнение
    ptree user_order_list;
    IMCM::fill_ptree_list<const char*>(user_order_list, {"N", "H", "W", "C"});
    
    // Список размерностей со стороны TPU и его заполнение.
    ptree tpu_shape_list;
    IMCM::fill_ptree_list<axis_size_t>(tpu_shape_list, 
        {settings.input_map.B, settings.input_map.X, settings.input_map.Y, settings.input_map.L});
    
    // Порядок расположение осей со стороны TPU и его заполнение
    ptree tpu_order_list;
    IMCM::fill_ptree_list<const char*>(tpu_order_list, {"C", "H", "W", "N"});

    // Список скейлов для входной карты и его заполнение
    ptree scales_list;
    IMCM::fill_ptree_list<double>(scales_list, {settings.input_map_scale});

    // Заполнение паддингов входного тензора
    ptree paddings_list;   // Общий список паддингов
    ptree batch_padding;   // Дочерний список паддингов: Batch axis
    ptree width_padding;   // Дочерний список паддингов: Width axis
    ptree height_padding;  // Дочерний список паддингов: Height axis
    ptree channel_padding; // Дочерний список паддингов: Channel axis

    // Распакованные значения паддингов
    auto [b_pad, x_pad, y_pad, l_pad] = settings.paddings_in;

    // Заполнение дочерних списков
    IMCM::fill_ptree_list<axes_padding_t>(batch_padding, {b_pad.left, b_pad.right});
    IMCM::fill_ptree_list<axes_padding_t>(width_padding, {x_pad.left, x_pad.right});
    IMCM::fill_ptree_list<axes_padding_t>(height_padding, {y_pad.left, y_pad.right});
    IMCM::fill_ptree_list<axes_padding_t>(channel_padding, {l_pad.left, l_pad.right});

    // Заполнение главного списка
    paddings_list.push_back(std::make_pair("", batch_padding));
    paddings_list.push_back(std::make_pair("", width_padding));
    paddings_list.push_back(std::make_pair("", height_padding));
    paddings_list.push_back(std::make_pair("", channel_padding));

    // Оаспаковка размерностей осей входного тензора
    auto [B, X, Y, L] = settings.input_map;

    // Заполнение общей информации о первом узле
    first_node.put("address", 0);
    first_node.put("size", B * X * Y * L);
    first_node.add_child("user_shape", user_shape_list);
    first_node.add_child("user_order", user_order_list);
    first_node.put("user_dtype", "float32");
    first_node.add_child("tpu_shape", tpu_shape_list);
    first_node.add_child("tpu_order", tpu_order_list);
    first_node.put("tpu_dtype", "int8");
    first_node.add_child("scales", scales_list);
    first_node.put("anchor", "Placeholder: 0");
    first_node.add_child("padding", paddings_list);

    // Заполнение главного блока
    first_input_space.add_child("input_node_1", first_node);
    inputs_block.add_child("1", first_input_space);
};

// Создание блока с описание выходного тензора
void MetadataCreatorModule::createOutputsBlock(ptree& outputs_block) const {
    // Первое пространство DDR
    ptree first_output_space;
    // Первый выходной узел
    ptree first_node;
    
    // Размеры выходного тензора
    auto [B, X, Y, L] = settings.output_map;
    
    // Пользовательские и внутренние размеры тензоров и порядки осей
    ptree user_shape_list, user_order_list, tpu_shape_list, tpu_order_list;

    // Заполнение размеров и порядка осей тензоров
    IMCM::fill_ptree_list<axis_size_t>(user_shape_list, {B, (X * Y * L)});
    IMCM::fill_ptree_list<const char*>(user_order_list, {"N", "C"});
    IMCM::fill_ptree_list<axis_size_t>(tpu_shape_list, {B, (X * Y * L)});
    IMCM::fill_ptree_list<const char*>(tpu_order_list, {"N", "C"});

    // Список скейлов для выходной карты
    ptree scales_list;
    IMCM::fill_ptree_list<double>(scales_list, {settings.output_map_scales});

    // Список паддингов для выходной карты
    ptree paddings_list, batch_paddings, channel_paddings;
    
    // Заполенение списка паддингов
    IMCM::fill_ptree_list<axes_padding_t>(batch_paddings, 
        {settings.paddings_out.B.left, settings.paddings_out.B.right}
    );
    IMCM::fill_ptree_list<axes_padding_t>(channel_paddings, 
        {settings.paddings_out.L.left, settings.paddings_out.L.right}
    );

    paddings_list.push_back(std::make_pair("", batch_paddings));
    paddings_list.push_back(std::make_pair("", channel_paddings));


    // Заполнение информации о выходном тензоре
    first_node.put("address", 0);
    first_node.put("size", B * X * Y * L);
    first_node.add_child("user_shape", user_shape_list);
    first_node.add_child("user_order", user_shape_list);
    first_node.put("user_dtype", "float16");
    first_node.add_child("tpu_shape", tpu_shape_list);
    first_node.add_child("tpu_order", tpu_order_list);
    first_node.put("tpu_dtype", "int8");
    first_node.add_child("scales", scales_list);
    first_node.put("anchor", "logits: 0");
    first_node.add_child("padding", paddings_list);

    first_output_space.add_child("spatial_squeeze_layer_1", first_node);
    outputs_block.add_child("2", first_output_space);
};

// Заполнение блока со схемой DDR. 
void MetadataCreatorModule::createRamSchemeBlock(
    const std::vector<IMCM::ProgramFileDesc>& file_descriptors, 
    ptree& ram_scheme_block
) const {
    // Подблоки с различными типами пространств DDR
    ptree constants_block, input_block, output_block, swap_block;

    // Определение размера файла с константами
    int constant_file_size = 0;
    for (const IMCM::ProgramFileDesc& descriptor : file_descriptors) {
        if (!IMCM::is_cmd_file(descriptor.filename)) {
            constant_file_size = descriptor.size;
            break;
        }
    }

    // Распаковка размеров выходного и входного тензоров
    auto [Bin, Xin, Yin, Lin] = settings.input_map;
    auto [Bout, Xout, Yout, Lout] = settings.output_map;

    // Заполнение информации в подблоки 
    constants_block.put("type", "constant");
    constants_block.put("ddr_id", 0);
    constants_block.put("size", constant_file_size);

    input_block.put("type", "input");
    input_block.put("ddr_id", 0);
    input_block.put("size", Bin * Xin * Yin * Lin);
    
    output_block.put("type", "output");
    output_block.put("ddr_id", 0);
    output_block.put("size", Bout * Xout * Yout * Lout);

    swap_block.put("type", "swap");
    swap_block.put("ddr_id", 0);
    swap_block.put("size", 6623232);

    // Добавление информации в основной блок
    ram_scheme_block.add_child("0", constants_block);
    ram_scheme_block.add_child("1", input_block);
    ram_scheme_block.add_child("2", output_block);
    ram_scheme_block.add_child("3", swap_block);
};

// Заполнение тела JSON описания метаданных.
void MetadataCreatorModule::createMetadataBody(
    IMCM::json_body_t& metadata, 
    const std::vector<IMCM::ProgramFileDesc>& file_descriptors, 
    const TPUDescriptor& tpu_descriptor
) const {
    ptree hardware_parameters_block; // Блок с описанием параметров устройоства
    ptree instructions_block;        // Блок с описанием инструкций
    ptree constants_block;           // Блок с описанием файлов с константами
    ptree inputs_block;              // Блок с описанием входного тензора
    ptree outputs_block;             // Блок с описанием выходного тензора
    ptree ram_scheme_block;          // Блок со схемой памяти
    
    // Заполнение соответствующих блоков
    createHardwareParamsBlock(tpu_descriptor, hardware_parameters_block);
    createInstructionsBlock(file_descriptors, instructions_block);
    createConstantsBlock(file_descriptors, constants_block);
    createInputBlock(inputs_block);
    createOutputsBlock(outputs_block);
    createRamSchemeBlock(file_descriptors, ram_scheme_block);

    // Добавление блоков в тело
    metadata.add_child("hardware_parameters", hardware_parameters_block);
    metadata.add_child("instructions", instructions_block);
    metadata.add_child("constants", constants_block);
    metadata.add_child("inputs", inputs_block);
    metadata.add_child("outputs", outputs_block);
    metadata.add_child("ram_scheme", ram_scheme_block);
    
    // Параметры версии драйверов
    metadata.put("iva_tpu_ip_version", settings.ip_version);
    metadata.put("iva_tpu_api_version", settings.api_version);
};
