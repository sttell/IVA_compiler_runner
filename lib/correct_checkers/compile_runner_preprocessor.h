#ifndef COMPILERUNNERPREPROCESSOR_H
#define COMPILERUNNERPREPROCESSOR_H

#include "lib/controllers/statusbar_controller.h"
#include "lib/buffers/settingsbuffer.h"
#include "include/settings_config.h"
#include "lib/compiler_core/include/settings/globalSettings.h"
#include "lib/compiler_core/include/pipeline.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "lib/buffers/settingsbuffer.h"
#include "lib/thread_api/interrupt_buffer.h"

#include <QString>
#include <QTextBrowser>
#include <QPushButton>
#include <QSettings>

struct CompileVarSettingsDescriptor
{
    QString json_path;
    QString weights_path;
    QString output_directory_path;
    QString output_directory_name;
    QString input_size;
    QString output_size;
    QString input_pad_up;
    QString output_pad_up;
    QString input_pad_down;
    QString output_pad_down;
    unsigned int device_index;
    bool is_add_logs;
    bool is_input_optimization;
    bool is_preload_filters;
    bool is_preload_bias_scales;
    bool is_reorder_data;
    bool is_tpu_debug;
    bool pipe_json_convert;
    bool pipe_pickle_convert;
    bool pipe_weights_convert;
    bool pipe_address_check;
    bool pipe_compile;
    bool pipe_create_metadata;
    bool pipe_make_output;

};

class CompileRunnerProcessor
{
public:
    explicit CompileRunnerProcessor(
            CompileVarSettingsDescriptor compile_settings, StatusBufferCache* status_bar, SettingsBuffer* _parent_settings, InterruptBuffer* _interrupt_buffer);
    ~CompileRunnerProcessor();
    void operator()();

private:
    CompileVarSettingsDescriptor var_settings;
    StatusBufferCache* status_cache;
    SettingsBuffer* parent_settings;
    InterruptBuffer* interrupt_buffer;

    bool runProcessing();
    void checkRegularSettings();

    void formGlobalSettingsDesc(GlobalSettings*);
    void createPipeline(Pipeline*);
    void runCompileProcess(GlobalSettings*, Pipeline*);

    void operator=(CompileRunnerProcessor&)=delete;

};




#endif // COMPILERUNNERPREPROCESSOR_H
