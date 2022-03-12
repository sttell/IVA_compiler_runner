#include "../../../include/modules/addressCheckerModule.h"

exit_module_status AddressCheckerModule::runProcess() {
    
    clearStdErrCache(settings.stderr_log_path);

    // В любом из методов может возникнуть исключительная ситуация
    // которая записывается в лог с ошибками.
    // Все выбрасываемые исключения внутри методов необходимо
    // выбрасывать в виде std::runtime_error(description).
    try{
        // Проверка правильности настроек
        checkSettingsCorrectness();
        // Чтение буффера PickleConverter
        readPickleBuffer();
        // Чтение Json файла с описанием сети в формате hpm_scheduler
        readJSON();
        // Корректировка адресов и размеров
        correctData();
        // Выгрузка json файла с исправлениями
        dumpJSON();
    
    } catch (const std::runtime_error& e) {
        
		// Выгружаем исключение в лог ошибок.
        dumpStdErrToLog(e.what(), settings.stderr_log_path.c_str());
        
		return ModuleExitStatus::EXCEPTION;
    }
    return ModuleExitStatus::SUCCESS;
};

// Проверка корректности настроек
void AddressCheckerModule::checkSettingsCorrectness() const {
    // Проверка наличия входных файлов
    checkFileExist(settings.json_path);
    checkFileExist(settings.pickle_buffer_path);
    
    // Проверка существования директории
    checkDirExist(settings.out_log_path);
    checkDirExist(settings.out_json_path);
}

// Чтение Pickle Log
void AddressCheckerModule::readPickleBuffer() {
	try
	{
		// opening input file stream
		std::ifstream fin;
		fin.open(settings.pickle_buffer_path.c_str());

		std::string b_key;
		pickle_ld_t layer_data;
		std::string ld_key;
		std::pair<int, int> p;
		int address, size;

		std::string line;

		// reading first line as layer name
		std::getline(fin, line);
		b_key = line;

		// loop through all lines of input log file
		while (std::getline(fin, line))
		{
			std::istringstream iss(line);
			// if line is the name of new layer
			if (!(iss >> ld_key >> address >> size))
			{
				// adding layer to buffer
				pickle_buffer.insert({ b_key, layer_data });
				// clearing layer_data
				layer_data = {};
				// updating layer name
				b_key = line;
				continue;
			}
			// else adding new data into layer data
			p = { address, size };
			layer_data.insert({ ld_key, p });
		}

		fin.close();
	}
	catch (std::exception const& e)
	{
		std::string err_desc = THROW_DESC;
		err_desc += e.what();
		throw std::runtime_error(err_desc.c_str());
	}
}

// Чтение JSON описания сети в формате HPM
void AddressCheckerModule::readJSON() {
	try {
		json_handler.read(settings.json_path, json_buffer);
	}
	catch (std::exception const& e)
	{
		std::string err_desc = THROW_DESC;
		err_desc += e.what();
		throw std::runtime_error(err_desc.c_str());
	}
}

// Запись корректированного JSON файла сети
void AddressCheckerModule::dumpJSON() const {
	try {
		json_handler.dump(settings.out_json_path, json_buffer);
	}
	catch (std::exception const& e)
	{
		std::string err_desc = THROW_DESC;
		err_desc += e.what();
		throw std::runtime_error(err_desc.c_str());
	}
}

void AddressCheckerModule::correctData() {
	return;
	// TODO Коррекция данных
}
