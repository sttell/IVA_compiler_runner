#include "../../../include/modules/addressCheckerModule.h"

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !(std::isdigit(c) || c == '.'); }) == s.end();
}

void put_value(std::ofstream& fout, const std::string& value)
{
	if (value == "true" || value == "false" || is_number(value))
		fout << value;
	else
		fout << "\"" << value << "\"";
	fout << ",";
}

void put_tree(std::ofstream& fout, const boost::property_tree::ptree& ptree)
{
	//fout << "{";
	for (auto& item : ptree.get_child(""))
	{
		fout << "\n";
		fout << "\"" << item.first << "\": ";
		if (item.second.get_value<std::string>() == "")
		{
			put_tree(fout, item.second);
		}
		else
			put_value(fout, item.second.get_value<std::string>());
	}
	//fout << "}";
}

exit_module_status AddressCheckerModule::runProcess() {
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
        // Пытаемся открыть лог из настроек.
        std::string err_log_path = settings.stderr_log_path.c_str();
        std::ofstream err_log;

        try {
        
            err_log.open(err_log_path);
            if (!err_log.is_open()) throw std::runtime_error("Err log don't opened.");
        
        } catch (const std::exception& log_ex){
        
            err_log_path = DEFAUL_STDERR_PATH;
            err_log.open(err_log_path);
            err_log << log_ex.what() << std::endl;

        }
        // Записываем описание исключения
        err_log << e.what() << std::endl;
        err_log.close();
        return ModuleExitStatus::EXCEPTION;
    }
    return ModuleExitStatus::SUCCESS;
};

// Проверка наличия файла. 
// В случае отсутствия выбрасывает исключение std::runtime_error
// с описанием ошибки.
void AddressCheckerModule::checkFileExist(const Path& path) const {
    // В случае отсутствия файла формируется исключение с описанием пути
    if (!path.isExists()) {
        std::string err_desc = THROW_DESC;
        err_desc += "File ";
        err_desc += path.c_str();
        err_desc += " not found.\n";
        throw std::runtime_error(err_desc.c_str());   
    }
}

// Проверка настройки для выходного файла
void AddressCheckerModule::checkDirExist(const Path& path) const {
    // Директория ведущая к файлу должна существовать
    if (!path.isExistsPathDirectory()) {
        std::string err_desc = THROW_DESC;
        err_desc += "Directory ";
        err_desc += path.c_str();
        err_desc += " with file not found.\n";
        throw std::runtime_error(err_desc.c_str());
    }

    if (path.back() == SLASH) {
        std::string err_desc = THROW_DESC;
        err_desc += "Path ";
        err_desc += path.c_str();
        err_desc += " maybe only file path, not directory!\n";
        throw std::runtime_error(err_desc.c_str());
    }
}

// Проверка корректности настроек
void AddressCheckerModule::checkSettingsCorrectness() const {
    // Проверка наличия входных файлов
    checkFileExist(settings.json_path);
    checkFileExist(settings.pickle_buffer_path);
    
    // Проверка существования директории
    checkDirExist(settings.out_log_path);
    checkDirExist(settings.out_json_path);
}

void AddressCheckerModule::readPickleBuffer() {
	// TODO Чтение буффера Pickle
}

void AddressCheckerModule::readJSON() {
	try
	{
		// reading json into a tree
		boost::property_tree::ptree root;
		boost::property_tree::read_json(settings.json_path, root);

		// loop through array of layers
		for (auto& item : root.get_child(""))
		{
			// item has type pair<string,ptree<string,string>>
			json_buffer.push_back(item.second);
		}
	}
	catch (std::exception const& e)
	{
		std::string err_desc = THROW_DESC;
		err_desc += e.what();
		throw std::runtime_error(err_desc.c_str());
	}
}

void AddressCheckerModule::dumpJSON() const {
	try
	{
		// opening output file stream
		std::ofstream fout;
		fout.open(settings.json_path);
		fout << "[";
		// loop through array of layers
		for (int i = 0; i < json_buffer.size(); i++)
		{
			fout << "\n{";
			// loop through all fields of layer
			for (auto& item : json_buffer[i].get_child(""))
			{
				fout << "\n";
				fout << "\"" << item.first << "\": ";
				// if value of field is an array
				if (item.second.get_value<std::string>() == "")
				{
					fout << "[";
					boost::property_tree::ptree leaf = item.second;
					// loop through all elements of array
					for (auto& leaf_item : leaf.get_child(""))
					{
						fout << "\n";
						put_value(fout, leaf_item.second.get_value<std::string>());
					}
					fout.seekp(-1, std::ios_base::cur);
					fout << "\n],";
				}
				else
					put_value(fout, item.second.get_value<std::string>());
			}
			fout.seekp(-1, std::ios_base::cur);
			fout << "\n},";
		}
		fout.seekp(-1, std::ios_base::cur);
		fout << "\n]";
		fout.close();
	}
	catch (std::exception const& e)
	{
		std::string err_desc = THROW_DESC;
		err_desc += e.what();
		throw std::runtime_error(err_desc.c_str());
	}
}

void correctData() {
	// TODO Коррекция данных
}
