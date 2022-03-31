#include "tensorcreator.h"

TensorCreator::~TensorCreator() {
    progress = nullptr;
    log = nullptr;
    delete progress;
    delete log;
}

void TensorCreator::runProcess() {

    try {
        std::vector<size_t> sizes;
        parseSizes(sizes);

        log->writeMessage("Начат процесс генерации входного тензора...");
        generateTensor(sizes);
        (*progress)++;

    }  catch (const std::exception& e) {
        std::string err_desc(TENSOR_CREATOR_THROW_HEADER);
        log->writeMessage(err_desc + e.what(), "auto", MessageColor::error);
    }


}

void TensorCreator::parseSizes(std::vector<size_t>& sizes) {
    QStringList sizes_str = settings.tensor_size.replace(" ", "").split(",");
    for (const auto& size : sizes_str) {
        sizes.push_back(size.toInt());
    }
}

void TensorCreator::generateTensor(const std::vector<size_t>& sizes) {
    size_t num_bytes = 1;
    for (const auto& size : sizes) num_bytes *= size;

    std::ofstream fout(settings.tensor_save_path.toStdString(), std::ios::binary | std::ios::out);

    if (fout.is_open()) {
        for (size_t i=0; i < num_bytes; i++) {
            char num = rand();
            fout.write(&num, sizeof(num));
        }

    } else {
        throw std::runtime_error("Не удалось открыть файл для записи.");
    }
    fout.close();
    log->writeMessage("Тензор успешно сгенерирован.");
}
