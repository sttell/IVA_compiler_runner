#ifndef _INCLUDE_TPUDESCRIPTOR_H_
#define _INCLUDE_TPUDESCRIPTOR_H_

#include <cinttypes>
#include "deviceTypes.h"
#include <vector>
#include <string>


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
        switch (device_type) 
        { 
        case Device::MOBILE:
            initMobile();
            break;

        case Device::KCU:
            initKCU();
            break;
        
        case Device::SERVER:
            initServer();
            break;
        
        default:
            break;
        
        }
    };

    // Инициализация IVA TPU MOBILE (M)
    void initMobile() {
        ddr_word_len               = 16;
        ddr_bank_capacity          = 268435456;
        ddr_num_banks              = 1;
        cache_single_port          = true;
        cache_word_len             = 64;
        cache_bank_capacity        = 4096;
        cache_num_banks            = 32;
        data_int_size              = 1;
        me_sa_type                 = "g_sa";
        me_sa_size                 = {64, 64};
        me_sa_mem_capacity         = 1;
        me_ps_buf_capacity         = 1024;
        me_ps_bias_buf_capacity    = 32;
        lut_act_input_bw           = 12;
        lut_act_lut_bw             = 16;
        lut_act_lut_depth          = 8;
        lut_act_output_bw          = 16;
        me_sa_wmm_use              = false;
        ve_pdp_channel_number      = 64;
        ve_pdp_mult_number         = 3;
        ve_ewp_channel_number      = 32;
        ve_ewp_cache_bank_capacity = 512;
        ve_ewp_cache_num_banks     = 8;
        cu_argv_number             = 8;
        me_frequency               = 1000000000.0;
        ddr_frequency              = 800000000.0;
        profiler_time_resolution   = "1e-06_![hardwrite]";
        dtu_timing_initial         = 62.;
        dtu_timing_latency         = 18.;
        me_timing_initial_ff       = 50.;
        me_timing_initial_sdp      = 50.;
        me_timing_initial          = 265.;
        me_timing_latency          = 234.;
        ve_timing_initial_pdp      = 64.;
        ve_timing_initial_ewp      = 144.;
        ve_timing_latency          = 92.;
        ddr_page_size              = 4096;
        ddr_bandwith_ideal         = false;
        cu_start_delay             = 150.;
    };

    // Инициализация для IVA TPU KCU BASED PLATFORM
    void initKCU() {
        ddr_word_len               = 32;
        ddr_bank_capacity          = 67108864;
        ddr_num_banks              = 2;
        cache_single_port          = true;
        cache_word_len             = 32;
        cache_bank_capacity        = 4096;
        cache_num_banks            = 16;
        data_int_size              = 1;
        me_sa_type                 = "g_sa";
        me_sa_size                 = {32, 32};
        me_sa_mem_capacity         = 1;
        me_ps_buf_capacity         = 1024;
        me_ps_bias_buf_capacity    = 32;
        lut_act_input_bw           = 12;
        lut_act_lut_bw             = 16;
        lut_act_lut_depth          = 8;
        lut_act_output_bw          = 16;
        me_sa_wmm_use              = false;
        ve_pdp_channel_number      = 32;
        ve_pdp_mult_number         = 3;
        ve_ewp_channel_number      = 16;
        ve_ewp_cache_bank_capacity = 256;
        ve_ewp_cache_num_banks     = 8;
        cu_argv_number             = 8;
        me_frequency               = 200000000.0;
        ddr_frequency              = 200000000.0;
        profiler_time_resolution   = "1e-06_![hardwrite]";
        dtu_timing_initial         = 62.;
        dtu_timing_latency         = 18.;
        me_timing_initial_ff       = 50.;
        me_timing_initial_sdp      = 50.;
        me_timing_initial          = 265.;
        me_timing_latency          = 234.;
        ve_timing_initial_pdp      = 64.;
        ve_timing_initial_ewp      = 144.;
        ve_timing_latency          = 92.;
        ddr_page_size              = 4096;
        ddr_bandwith_ideal         = false;
        cu_start_delay             = 150.;
    };

    // Инициализация для IVA TPU SERVER (H)
    void initServer() {
        // TODO Характеристики для серверного не известны. Нужно будет откорректировать.
        ddr_word_len               = 16;
        ddr_bank_capacity          = 268435456;
        ddr_num_banks              = 1;
        cache_single_port          = true;
        cache_word_len             = 64;
        cache_bank_capacity        = 4096;
        cache_num_banks            = 32;
        data_int_size              = 1;
        me_sa_type                 = "g_sa";
        me_sa_size                 = {64, 64};
        me_sa_mem_capacity         = 1;
        me_ps_buf_capacity         = 1024;
        me_ps_bias_buf_capacity    = 32;
        lut_act_input_bw           = 12;
        lut_act_lut_bw             = 16;
        lut_act_lut_depth          = 8;
        lut_act_output_bw          = 16;
        me_sa_wmm_use              = false;
        ve_pdp_channel_number      = 64;
        ve_pdp_mult_number         = 3;
        ve_ewp_channel_number      = 32;
        ve_ewp_cache_bank_capacity = 512;
        ve_ewp_cache_num_banks     = 8;
        cu_argv_number             = 8;
        me_frequency               = 1000000000.0;
        ddr_frequency              = 800000000.0;
        profiler_time_resolution   = "1e-06_![hardwrite]";
        dtu_timing_initial         = 62.;
        dtu_timing_latency         = 18.;
        me_timing_initial_ff       = 50.;
        me_timing_initial_sdp      = 50.;
        me_timing_initial          = 265.;
        me_timing_latency          = 234.;
        ve_timing_initial_pdp      = 64.;
        ve_timing_initial_ewp      = 144.;
        ve_timing_latency          = 92.;
        ddr_page_size              = 4096;
        ddr_bandwith_ideal         = false;
        cu_start_delay             = 150.;
    };
};

#endif // _INCLUDE_TPUDESCRIPTOR_H_