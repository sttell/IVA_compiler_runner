#ifndef _INCLUDE_TPUDESCRIPTOR_H_
#define _INCLUDE_TPUDESCRIPTOR_H_

#include <cinttypes>
#include "deviceTypes.h"
#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <boost/filesystem/operations.hpp>
namespace opt = boost::program_options;

// Дескриптор устройства. Необходим для формирования файла с метаданными.
// Описывает hardware parameters устройств.
class TPUDescriptor {
public:
    explicit TPUDescriptor(Device device_type) { init(device_type); };

    // Hardware parameters
    uint16_t ddr_word_len;
    uint64_t ddr_bank_capacity;
    uint16_t ddr_num_banks;
    bool cache_single_port;
    uint16_t cache_word_len;
    uint64_t cache_bank_capacity;
    uint64_t cache_num_banks;
    uint8_t data_int_size;
    std::string me_sa_type;
    std::pair<size_t, size_t> me_sa_size;
    size_t me_sa_mem_capacity;
    size_t me_ps_buf_capacity;
    size_t me_ps_bias_buf_capacity;
    size_t lut_act_input_bw;
    size_t lut_act_lut_bw;
    size_t lut_act_lut_depth;
    size_t lut_act_output_bw;
    bool me_sa_wmm_use;
    size_t ve_pdp_channel_number;
    size_t ve_pdp_mult_number;
    size_t ve_ewp_channel_number;
    size_t ve_ewp_cache_bank_capacity;
    size_t ve_ewp_cache_num_banks;
    size_t cu_argv_number;
    double me_frequency;
    double ddr_frequency;
    std::string profiler_time_resolution;
    double dtu_timing_initial;
    double dtu_timing_latency;
    double me_timing_initial_ff;
    double me_timing_initial_sdp;
    double me_timing_initial;
    double me_timing_latency;
    double ve_timing_initial_pdp;
    double ve_timing_initial_ewp;
    double ve_timing_latency;
    size_t ddr_page_size;
    bool ddr_bandwith_ideal;
    double cu_start_delay;

private:
    // Запуск инициализации определенного устройства
    void init(Device device_type) { 
        std::string current_path = boost::filesystem::current_path().generic_string();

        switch (device_type)
        { 
        case Device::MOBILE:
            init(current_path + "/cfg/mobile_hardware.cfg");
            break;

        case Device::KCU:
            init(current_path + "/cfg/kcu_hardware.cfg");
            break;
        
        case Device::SERVER:
            init(current_path + "/cfg/server_hardware.cfg");
            break;
        
        default:
            break;
        
        }
    };

    // Инициализация IVA TPU MOBILE (M)
    void init(const std::string& cfg_file) {

        opt::options_description desc("Mobile hardware");
        desc.add_options()
                ("ddr_word_len", opt::value<size_t>()->required())
                ("ddr_bank_capacity", opt::value<size_t>()->required())
                ("ddr_num_banks", opt::value<size_t>()->required())
                ("cache_single_port", opt::value<bool>()->required())
                ("cache_word_len", opt::value<size_t>()->required())
                ("cache_bank_capacity", opt::value<size_t>()->required())
                ("cache_num_banks", opt::value<size_t>()->required())
                ("data_int_size", opt::value<size_t>()->required())
                ("me_sa_type", opt::value<std::string>()->required())
                ("me_sa_size_x", opt::value<size_t>()->required())
                ("me_sa_size_y", opt::value<size_t>()->required())
                ("me_sa_mem_capacity", opt::value<size_t>()->required())
                ("me_ps_buf_capacity", opt::value<size_t>()->required())
                ("me_ps_bias_buf_capacity", opt::value<size_t>()->required())
                ("lut_act_input_bw", opt::value<size_t>()->required())
                ("lut_act_lut_bw", opt::value<size_t>()->required())
                ("lut_act_lut_depth", opt::value<size_t>()->required())
                ("lut_act_output_bw", opt::value<size_t>()->required())
                ("me_sa_wmm_use", opt::value<bool>()->required())
                ("ve_pdp_channel_number", opt::value<size_t>()->required())
                ("ve_pdp_mult_number", opt::value<size_t>()->required())
                ("ve_ewp_channel_number", opt::value<size_t>()->required())
                ("ve_ewp_cache_bank_capacity", opt::value<size_t>()->required())
                ("ve_ewp_cache_num_banks", opt::value<size_t>()->required())
                ("cu_argv_number", opt::value<size_t>()->required())
                ("me_frequency", opt::value<float>()->required())
                ("ddr_frequency", opt::value<float>()->required())
                ("profiler_time_resolution", opt::value<std::string>()->required())
                ("dtu_timing_initial", opt::value<float>()->required())
                ("dtu_timing_latency", opt::value<float>()->required())
                ("me_timing_initial_ff", opt::value<float>()->required())
                ("me_timing_initial_sdp", opt::value<float>()->required())
                ("me_timing_initial", opt::value<float>()->required())
                ("me_timing_latency", opt::value<float>()->required())
                ("ve_timing_initial_pdp", opt::value<float>()->required())
                ("ve_timing_initial_ewp", opt::value<float>()->required())
                ("ve_timing_latency", opt::value<float>()->required())
                ("ddr_page_size", opt::value<size_t>()->required())
                ("ddr_bandwith_ideal", opt::value<bool>()->required())
                ("cu_start_delay", opt::value<float>()->required())

        ;

        // Переменная для хранения аргументов нашей командной строки
        opt::variables_map vm;
        // Парсинг и сохранение аргументов
        try {
            opt::store(
            opt::parse_config_file<char>(cfg_file.c_str(), desc),
            vm
            );
        } catch (const opt::reading_file& e) {
            throw std::runtime_error("Ошибка чтения конфигурации hardware параметров для устройства.");
        }
        // Эта функция должна вызываться после парсинга и сохранения.
        opt::notify(vm);

        ddr_word_len               = vm["ddr_word_len"].as<size_t>();
        ddr_bank_capacity          = vm["ddr_bank_capacity"].as<size_t>();
        ddr_num_banks              = vm["ddr_num_banks"].as<size_t>();
        cache_single_port          = vm["cache_single_port"].as<bool>();
        cache_word_len             = vm["cache_word_len"].as<size_t>();
        cache_bank_capacity        = vm["cache_bank_capacity"].as<size_t>();
        cache_num_banks            = vm["cache_num_banks"].as<size_t>();
        data_int_size              = vm["data_int_size"].as<size_t>();
        me_sa_type                 = vm["me_sa_type"].as<std::string>();
        me_sa_size                 = {vm["me_sa_size_x"].as<size_t>(), vm["me_sa_size_y"].as<size_t>()};
        me_sa_mem_capacity         = vm["me_sa_mem_capacity"].as<size_t>();
        me_ps_buf_capacity         = vm["me_ps_buf_capacity"].as<size_t>();
        me_ps_bias_buf_capacity    = vm["me_ps_bias_buf_capacity"].as<size_t>();
        lut_act_input_bw           = vm["lut_act_input_bw"].as<size_t>();
        lut_act_lut_bw             = vm["lut_act_lut_bw"].as<size_t>();
        lut_act_lut_depth          = vm["lut_act_lut_depth"].as<size_t>();
        lut_act_output_bw          = vm["lut_act_output_bw"].as<size_t>();
        me_sa_wmm_use              = vm["me_sa_wmm_use"].as<bool>();
        ve_pdp_channel_number      = vm["ve_pdp_channel_number"].as<size_t>();
        ve_pdp_mult_number         = vm["ve_pdp_mult_number"].as<size_t>();
        ve_ewp_channel_number      = vm["ve_ewp_channel_number"].as<size_t>();
        ve_ewp_cache_bank_capacity = vm["ve_ewp_cache_bank_capacity"].as<size_t>();
        ve_ewp_cache_num_banks     = vm["ve_ewp_cache_num_banks"].as<size_t>();
        cu_argv_number             = vm["cu_argv_number"].as<size_t>();
        me_frequency               = vm["me_frequency"].as<float>();
        ddr_frequency              = vm["ddr_frequency"].as<float>();
        profiler_time_resolution   = vm["profiler_time_resolution"].as<std::string>();
        dtu_timing_initial         = vm["dtu_timing_initial"].as<float>();
        dtu_timing_latency         = vm["dtu_timing_latency"].as<float>();
        me_timing_initial_ff       = vm["me_timing_initial_ff"].as<float>();
        me_timing_initial_sdp      = vm["me_timing_initial_sdp"].as<float>();
        me_timing_initial          = vm["me_timing_initial"].as<float>();
        me_timing_latency          = vm["me_timing_latency"].as<float>();
        ve_timing_initial_pdp      = vm["ve_timing_initial_pdp"].as<float>();
        ve_timing_initial_ewp      = vm["ve_timing_initial_ewp"].as<float>();
        ve_timing_latency          = vm["ve_timing_latency"].as<float>();
        ddr_page_size              = vm["ddr_page_size"].as<size_t>();
        ddr_bandwith_ideal         = vm["ddr_bandwith_ideal"].as<bool>();
        cu_start_delay             = vm["cu_start_delay"].as<float>();
    };

};

#endif // _INCLUDE_TPUDESCRIPTOR_H_
