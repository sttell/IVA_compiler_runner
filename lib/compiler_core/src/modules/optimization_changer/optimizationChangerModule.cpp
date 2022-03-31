#include "lib/compiler_core/include/modules/optimizationChangerModule.h"

#include <fstream>
#include <QRegularExpression>

// define в файле с оптимизациями для регулярных выражений
#define INPUT_OPT_DEFINE "#define INPUT_LAYER_OPTIMIZATION "
#define BIAS_SCALE_PRELOAD_OPT_DEFINE "#define PRELOAD_BIASES "
#define FILTERS_PRELOAD_OPT_DEFINE "#define PRELOAD_FILTERS "
#define REORDER_DATA_DEFINE "#define REORDER_DATA "
#define TPU_DEBUG_DEFINE "#define debug_files "


// Проверка корректности настроек
void OptimizationChangerModule::checkSettingsCorrectness() const {
    checkFileExist(settings.optimization_settings_header);
}

// Запуск модуля
exit_module_status OptimizationChangerModule::runProcess() {


    try {

        // Проверяем корректность настроек
        checkSettingsCorrectness();

        // Меняем оптимизации
        changeOptimizations();

    } catch (const std::exception& e) {
        throw std::runtime_error(throw_desc + e.what());
    }

    return ModuleExitStatus::SUCCESS;
}

// Замена булевого значения по переданному ключевому выражению + [0-1]
// text               - текст файла
// opt_define_pattern - ключевое слово, после которого должно стоять значение [0-1]
// new_value          - новое значение для замены
void OptimizationChangerModule::replaceBoolOptinon(QString& text, const std::string& opt_define_pattern, bool new_value) {
    // Формируем регулярное выражение
    QString rx_pattern(opt_define_pattern.c_str()); rx_pattern += "[0-1]";
    // Формируем замену
    QString replace_to(opt_define_pattern.c_str()); replace_to += std::to_string(new_value).c_str();
    QRegularExpression rx(rx_pattern);
    // Меняем текст
    text = text.replace(rx, replace_to);
};

// Изменение оптимизаций
void OptimizationChangerModule::changeOptimizations() {
    // Читаем файл
    std::ifstream fin(settings.optimization_settings_header.c_str());
    QString text;
    std::string line;
    if (fin.is_open()) {
        while(getline(fin, line)) {
            text += QString::fromStdString(line + "\n");
        }
        fin.close();
    } else {
        throw std::runtime_error("Не удалось открыть файл с оптимизациями.");
    }

    // Меняем все оптимизации
    replaceBoolOptinon(text, INPUT_OPT_DEFINE, settings.is_input_optimization);
    replaceBoolOptinon(text, BIAS_SCALE_PRELOAD_OPT_DEFINE, settings.is_preload_biases);
    replaceBoolOptinon(text, FILTERS_PRELOAD_OPT_DEFINE, settings.is_preload_filters);
    replaceBoolOptinon(text, REORDER_DATA_DEFINE, settings.is_reorder_data);
    replaceBoolOptinon(text, TPU_DEBUG_DEFINE, settings.is_tpu_debug_mode);

    // Записываем обновленный текст
    std::ofstream fout(settings.optimization_settings_header.c_str());
    fout << text.toStdString();
    fout.close();
}
