#ifndef OPTIMIZATIONCHANGERSETTINGS_H
#define OPTIMIZATIONCHANGERSETTINGS_H

#include "lib/compiler_core/include/path.h"

struct OptimizationChangerSettings
{
    OptimizationChangerSettings() :
        optimization_settings_header(PathType::File), is_input_optimization(false),
        is_preload_filters(false), is_preload_biases(false),
        is_preload_scales(false), is_reorder_data(false),
        is_tpu_debug_mode(false) {};

    Path optimization_settings_header;
    bool is_input_optimization;
    bool is_preload_filters;
    bool is_preload_biases;
    bool is_preload_scales;
    bool is_reorder_data;
    bool is_tpu_debug_mode;
};

#endif // OPTIMIZATIONCHANGERSETTINGS_H
