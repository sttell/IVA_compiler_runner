#ifndef _INCLUDE_COMPILERCORE_H_
#define _INCLUDE_COMPILERCORE_H_

#include <exception>
#include "lib/compiler_core/include/pipeline.h"
#include "lib/compiler_core/include/modules.h"
#include "lib/compiler_core/include/moduleExitStatus.h"
#include "lib/compiler_core/include/settings/globalSettings.h"
#include "lib/compiler_core/include/modules/pickleConverterModule.h"
#include "lib/compiler_core/include/modules/addressCheckerModule.h"
#include "lib/compiler_core/include/modules/compilerRunnerModule.h"
#include "lib/compiler_core/include/modules/programComparatorModule.h"
#include "lib/compiler_core/include/modules/metadataCreatorModule.h"
#include "lib/compiler_core/include/modules/optimizationChangerModule.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include "lib/compiler_core/include/compileStatus.h"
#include "lib/thread_api/interrupt_buffer.h"

#include <vector>
#include <memory>

#define CORE_EXCEPTION_HEADER "[Compilation Exception]:"

/* Ядро для запуска пайплайна компиляции.
*   
*  Ядро является Singletone классом.
*  Перед запуском необходимо инициализировать пайплайн компиляции.
*  После инициализации можно запускать процесс компиляции.
*  Настройки должны содержать корректные данные собранные из GUI.
*/
class CompilerCore
{
public:

    explicit CompilerCore(StatusBufferCache* status_bar, Pipeline _pipe, const GlobalSettings& _settings, InterruptBuffer* _interrupt_buffer) :
        log(status_bar), pipeline(_pipe), settings(_settings), interrupt_buffer(_interrupt_buffer){};
    ~CompilerCore() {interrupt_buffer=nullptr; log = nullptr;
                     delete interrupt_buffer; delete log;} ;

    void runProcess();
    void runModule(Modules module);
    void exceptionHandlerWrap(Module* module);

private:
    StatusBufferCache* log;
    Pipeline pipeline;
    GlobalSettings settings;
    InterruptBuffer* interrupt_buffer;

};

#endif // _INCLUDE_COMPILERCORE_H_
