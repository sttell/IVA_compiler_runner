#ifndef OPTIMIZATIONCHANGERMODULE_H
#define OPTIMIZATIONCHANGERMODULE_H

#include "lib/compiler_core/include/module.h"
#include "lib/compiler_core/include/settings/globalSettings.h"
#include "lib/thread_api/statusbuffer_cache.h"
#include <QString>

#define OPT_CHANGER_THROW_DESC "Optimization changer module error. "

class OptimizationChangerModule : public Module {
public:
    // Конструктор инициализирует настройки
    explicit OptimizationChangerModule(const GlobalSettings& _settings, StatusBufferCache* status_bar) :
        Module(status_bar, OPT_CHANGER_THROW_DESC), settings(_settings.optimization_change){};
    ~OptimizationChangerModule() {log=nullptr; delete log;};

    // Метод запуска конвертации
    exit_module_status runProcess();

protected:
    // Проверка корректности настроек
    void checkSettingsCorrectness() const;

private:
    void changeOptimizations();
    void replaceBoolOptinon(QString& text, const std::string& opt_define_pattern, bool new_value);
    OptimizationChangerSettings settings;
};

#endif // OPTIMIZATIONCHANGERMODULE_H
