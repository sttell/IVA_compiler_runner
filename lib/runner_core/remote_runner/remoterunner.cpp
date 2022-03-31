#include "remoterunner.h"

#define SFTP_TRANSFER_CHUNK_SIZE 16384
#define SSH_BUFFER_SIZE 256

void RemoteRunner::runProcess() {
    // Step 1. Check settings
    // Step 2. Connect to host
    // Step 3. Remote host authorization
    // Step 4. SFTP connection
    // Step 5. SFTP program transfer to remote host
    // Step 6. SSH remote run program
    // Step 7. SFTP callback transfer to local host

    try {
        fillRemotePathes();

        log->writeMessage("Начат процесс проверки настроек удаленного запуска.");
        checkSettingsCorrectness();
        (*progress)++;

        ssh_session ssh;
        sftp_session sftp;

        log->writeMessage("Подключение к хостингу.");
        connectToHost(ssh);
        (*progress)++;

        log->writeMessage("Аунтефикация пользователя на хостинге.");
        autheficateUser(ssh);
        (*progress)++;

        log->writeMessage("Инициализация и подключение SFTP протокола передачи.");
        connectToSFTP(ssh, sftp);
        (*progress)++;

        log->writeMessage("Создание директорий на удаленном хостинге.");
        initDirectories(ssh, sftp);

        if (!settings.is_remote_tensor) {
            log->writeMessage("Процесс копирования входного тензора на хостинг.");
            copyTensorToRemoteHost(ssh, sftp);
            (*progress)++;
        }

        log->writeMessage("Копирование программы на удаленный хостинг.");
        copyProgramToRemoteDirectory(ssh, sftp);
        (*progress)++;

        log->writeMessage("Отправляю команду запуска на хостинг.");
        runRemote(ssh, sftp);
        (*progress)++;

        log->writeMessage("Копирую файл с выходом на хостинг.");

        copyOutputToLocal(ssh, sftp);
        (*progress)++;

        log->writeMessage("Файл скопирован.");

        log->writeMessage("Отключаю хостинг и удаляю сессии подключения.");
        freeMemory(ssh, sftp);
        (*progress)++;

    } catch (const std::exception& e) {
        std::string err_desc(REMOTE_RUNNER_THROW_HEADER);
        log->writeMessage(err_desc + e.what(), "auto", MessageColor::error);
    }

};

void RemoteRunner::checkSettingsCorrectness() {
    if (!settings.is_remote_tensor) {
        if (!boost::filesystem::is_regular_file(settings.input_tensor_path.toStdString())) {
            throw std::runtime_error("Файла с входным тензором не существует.");
        }
    }

    QString program_zip = settings.program_directory + "/" + settings.program_name;
    if (!boost::filesystem::is_regular_file(program_zip.toStdString())) {
        std::string err_desc("Файл с программой ");
        err_desc += program_zip.toStdString() + " не найден.";
        throw std::runtime_error(err_desc);
    }
};

void RemoteRunner::fillRemotePathes() {
    remote_pathes.program_dir = REMOTE_TEMPORAL_DIRECTORY;
    remote_pathes.program_dir += "/" + settings.program_directory.split('/').last().toStdString();
    remote_pathes.program_path = remote_pathes.program_dir + "/" + settings.program_name.toStdString();

    if (settings.is_generated_tensor) {
        // Local dir -> remote dir
        remote_pathes.input_dir = REMOTE_TEMPORAL_DIRECTORY;
        remote_pathes.input_dir += "/";
        remote_pathes.input_dir += REMOTE_TENSORS_DIRNAME;

        remote_pathes.input_path = remote_pathes.input_dir + "/" + settings.input_tensor_name.toStdString();
    } else if (settings.is_remote_tensor) {
        // Remote dir
        QStringList splitted_path = settings.input_tensor_path.split("/");
        QStringList splitted_path_to_dir;
        if (splitted_path.size() > 1)
            for (int i = 0; i < splitted_path.size() - 2; i++)
                splitted_path_to_dir.push_back(splitted_path[i]);

        splitted_path = splitted_path_to_dir;
        remote_pathes.input_dir = splitted_path.join("/").toStdString();
        remote_pathes.input_path = settings.input_tensor_path.toStdString();

    } else {
        // Local dir -> remote dir
        remote_pathes.input_dir = REMOTE_TEMPORAL_DIRECTORY;
        remote_pathes.input_dir += "/";
        remote_pathes.input_dir += REMOTE_TENSORS_DIRNAME;

        remote_pathes.input_path = remote_pathes.input_dir + "/" + settings.input_tensor_name.toStdString();
    }

    remote_pathes.output_dir = remote_pathes.program_dir + "/output";
    remote_pathes.output_path = remote_pathes.output_dir + "/output.bin";
}

void RemoteRunner::freeMemory(ssh_session& ssh, sftp_session& sftp) {
    sftp_free(sftp);
    ssh_disconnect(ssh);
    ssh_free(ssh);
}

void RemoteRunner::copyOutputToLocal(ssh_session& ssh, sftp_session& sftp) {
    QString local_out_path = settings.program_directory + "/output/output.bin";
    QString local_out_dir  = settings.program_directory + "/output";

    if (!boost::filesystem::is_directory(local_out_dir.toStdString()))
        boost::filesystem::create_directory(local_out_dir.toStdString());

    copyFileFromRemoteHost(ssh, sftp, local_out_path.toStdString(), remote_pathes.output_path, "выходной файл");

}

void RemoteRunner::runRemote(ssh_session& ssh, sftp_session& sftp) {
    ssh_channel channel = ssh_channel_new(ssh);

    if (channel == NULL) {

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);
        std::string err_desc("Ошибка аллокации SSH канала.");
        throw std::runtime_error(err_desc);
    }

    ssh_channel_open_session(channel);

    if (ssh_channel_is_open(channel)) {
        log->writeMessage("SSH канал успешно открыт.");
    } else {
        sftp_free(sftp);
        ssh_channel_free(channel);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error("Ошибка откртия SSH канала передачи.");
    }

    std::string exec("run_tpu -t -r -p ");
    exec += remote_pathes.program_path + " -i ";
    exec += remote_pathes.input_path + " -o ";
    exec += remote_pathes.output_path;

    int exec_result = ssh_channel_request_exec(channel, exec.c_str());
    if (DEBUG_REMOTE) log->writeMessage("Ответ получен.");
    if (exec_result != SSH_OK) {
        sftp_free(sftp);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error("Ошибка выполнения команды на удаленном хостинге.");
    }

    std::string stdout_answer;
    char buffer[SSH_BUFFER_SIZE];
    int nbytes_out;

    while(!ssh_channel_is_eof(channel))
    {
        nbytes_out = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        stdout_answer += buffer;

    }

    QStringList out_strings;

    bool is_error = parseStdOut(stdout_answer, out_strings);

    log->writeMessage("Ответ хостинга:");

    QColor message_color = (is_error) ? MessageColor::error : MessageColor::normal;

    for (const auto& string : out_strings) {
        log->writeMessage(string.toStdString(), "auto", message_color);
    }

    if (is_error) {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error("Произошла ошибка выполнения на стороне сервера.");
    }

    ssh_channel_send_eof(channel);
    ssh_channel_free(channel);
}

bool RemoteRunner::parseStdOut(const std::string& out, QStringList& result) {
    QString output = out.c_str();
    QRegularExpression memcol_rx("memory collision error");
    QRegularExpression watchdog_rx("watchdog error");
    QRegularExpression exec_took_time_rx("execution took (\\d+) us");
    QRegularExpression exec_time_rx("execution time: (\\d+) us");
    QRegularExpression digits_rx("\\d+");

    if (memcol_rx.match(output).hasMatch()) {
        result.push_back("Memory Collision Error.");
        return true;
    } else if (watchdog_rx.match(output).hasMatch()) {
        result.push_back("Watchdog Error.");
        return true;
    } else if (exec_took_time_rx.match(output).hasMatch()) {
        QString line1("Execution took: ");
        QString line2("Execution time: ");

        QString cap;
        cap = exec_took_time_rx.match(output).captured(0);
        QString exec_took_time = digits_rx.match(cap).captured(0);

        cap = exec_time_rx.match(output).captured(0);
        QString exec_time = digits_rx.match(cap).captured(0);

        line1 += (exec_took_time + " us");
        line2 += (exec_time + " us");

        result.push_back(line1);
        result.push_back(line2);
        return false;
    } else {
        result.push_back(output);
        return true;
    }

}

void RemoteRunner::copyFileToRemoteHost(ssh_session& ssh, sftp_session& sftp, std::string local_path, std::string remote_path, std::string file_desc) {
    int access_type = O_WRONLY | O_CREAT | O_TRUNC;
    sftp_file file;
    char buffer[SFTP_TRANSFER_CHUNK_SIZE];
    int length {sizeof (buffer)};

    file = sftp_open(sftp, remote_path.c_str(), access_type, S_IRWXU);

    if (file == NULL) {
        std::string err_desc("Ошибка отрытия файла на удаленном хостинге ["); err_desc += file_desc + "] :";
        err_desc += ssh_get_error(ssh);

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);
    }

    int local_file_size   = boost::filesystem::file_size(local_path);
    int num_full_chunks   = local_file_size / (SFTP_TRANSFER_CHUNK_SIZE);

    std::ifstream fin(local_path, std::ios::binary | std::ios::in);

    if (fin.is_open()) {
        for (int current_chunk_id = 0; current_chunk_id < num_full_chunks; current_chunk_id++) {
            // Getting chunk from local file
            fin.read(buffer, length);

            int nwritten = sftp_write(file, buffer, length);

            if (nwritten != length) {
                std::string err_desc("Не удалось записать данные (Chunk ID - ");
                err_desc += std::to_string(current_chunk_id) + "/" + std::to_string(num_full_chunks + 1) + ") в файл: ";
                err_desc += file_desc;
                err_desc += " Error: "; err_desc += ssh_get_error(ssh);

                fin.close();
                sftp_close(file);
                sftp_free(sftp);
                ssh_disconnect(ssh);
                ssh_free(ssh);

                throw std::runtime_error(err_desc);
            }
        }

        int last_chapter_size = local_file_size % (SFTP_TRANSFER_CHUNK_SIZE);

        if (last_chapter_size != 0) {
            char* last_chapter_buffer = new char[last_chapter_size];
            fin.read(last_chapter_buffer, last_chapter_size);

            int nwritten = sftp_write(file, last_chapter_buffer, last_chapter_size);

            if (nwritten != last_chapter_size) {
                std::string err_desc("Не удалось записать данные (Chunk ID - last) в файл: "); err_desc += file_desc;
                err_desc += " Error: "; err_desc += ssh_get_error(ssh);

                fin.close();
                sftp_close(file);
                sftp_free(sftp);
                ssh_disconnect(ssh);
                ssh_free(ssh);

                throw std::runtime_error(err_desc);
            }
        }

    } else {

        std::string err_desc("Не удалось открыть файл на чтение: "); err_desc += file_desc;

        sftp_close(file);
        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);
    }

    fin.close();

    int close_result = sftp_close(file);
    if (close_result != SSH_OK) {
        std::string err_desc("Не удалось закрыть файл на удаленном хостинге: "); err_desc += file_desc + " Error:";
        err_desc += ssh_get_error(ssh);

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);

    }

}

void RemoteRunner::copyFileFromRemoteHost(ssh_session& ssh, sftp_session& sftp, std::string local_path, std::string remote_path, std::string file_desc) {
    int access_type = O_RDONLY;
    sftp_file file;
    char buffer[SFTP_TRANSFER_CHUNK_SIZE];
    int nbytes, nwritten, retcode;
    int local_file_descriptor;

    file = sftp_open(sftp, remote_path.c_str(), access_type, 0);

    if (file == NULL) {
        std::string err_desc("Ошибка отрытия файла на удаленном хостинге ["); err_desc += file_desc + "] :";
        err_desc += ssh_get_error(ssh);

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);
    }

    local_file_descriptor = open(local_path.c_str(), O_CREAT | O_RDWR, S_IRWXU);

    if (local_file_descriptor < 0) {
        std::string err_desc("Не удалось файл на запись на локальном хостинге: "); err_desc += file_desc;

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);
    }

    for ( ; ; ) {
        nbytes = sftp_read(file, buffer, sizeof(buffer));
        if (nbytes == 0) {
            break;
        } else if (nbytes < 0) {
            std::string err_desc("Ошибка чтения файла ");
            err_desc += remote_path + " на удаленном хостинге: ";
            err_desc += " Error: "; err_desc += ssh_get_error(ssh);

            sftp_close(file);
            sftp_free(sftp);
            ssh_disconnect(ssh);
            ssh_free(ssh);

            throw std::runtime_error(err_desc);
        }

        nwritten = write(local_file_descriptor, buffer, nbytes);
        if (nwritten != nbytes) {

            std::string err_desc("Ошбка записи файла на локальный хостинг.");

            sftp_close(file);
            sftp_free(sftp);
            ssh_disconnect(ssh);
            ssh_free(ssh);

            throw std::runtime_error(err_desc);

        }

    }


    int close_result = sftp_close(file);
    if (close_result != SSH_OK) {
        std::string err_desc("Не удалось закрыть файл на удаленном хостинге: "); err_desc += file_desc + " Error:";
        err_desc += ssh_get_error(ssh);

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);

    }
}

void RemoteRunner::copyTensorToRemoteHost(ssh_session& ssh, sftp_session& sftp) {
    QString local_path = settings.input_tensor_path;
    std::cout << remote_pathes.input_path << std::endl;
    copyFileToRemoteHost(ssh, sftp, local_path.toStdString(), remote_pathes.input_path, "входной тензор");
}

void RemoteRunner::copyProgramToRemoteDirectory(ssh_session& ssh, sftp_session& sftp) {
    QString local_path = settings.program_directory + "/" + settings.program_name;
    copyFileToRemoteHost(ssh, sftp, local_path.toStdString(), remote_pathes.program_path, "архив с программой");
};

void RemoteRunner::createRemoteDirectory(ssh_session& ssh, sftp_session& sftp, std::string path) {

    int result = sftp_mkdir(sftp, path.c_str(), S_IRWXU);

    if (result != SSH_OK) {
        if (sftp_get_error(sftp) != SSH_FX_FILE_ALREADY_EXISTS) {
            std::string err_desc("Не удалось создать директорию на удаленном хостинге: ");
            err_desc += sftp_get_error(sftp);

            sftp_free(sftp);
            ssh_disconnect(ssh);
            ssh_free(ssh);
        }
    }

}
void RemoteRunner::createLocalDirectory(std::string path) {
    if (!boost::filesystem::is_directory(path))
       boost::filesystem::create_directory(path);
}
void RemoteRunner::initDirectories(ssh_session& ssh, sftp_session& sftp) {
    std::string tensors_dir(REMOTE_TEMPORAL_DIRECTORY);
    tensors_dir += "/"; tensors_dir += REMOTE_TENSORS_DIRNAME;

    createRemoteDirectory(ssh, sftp, REMOTE_TEMPORAL_DIRECTORY);
    createRemoteDirectory(ssh, sftp, tensors_dir);
    createRemoteDirectory(ssh, sftp, remote_pathes.program_dir);
    createRemoteDirectory(ssh, sftp, remote_pathes.output_dir);
    createLocalDirectory((settings.program_directory + "/output").toStdString());
}

void RemoteRunner::connectToSFTP(ssh_session& ssh, sftp_session& sftp) {
    sftp = sftp_new(ssh);

    if (sftp == NULL) {
        ssh_disconnect(ssh);
        ssh_free(ssh);
        throw std::runtime_error("Не удалось аллоцировать SFTP сессию.");
    }

    int init_result = sftp_init(sftp);

    if (init_result != SSH_OK) {

        std::string err_desc("Не удалось инициализировать SFTP сессию. Error: ");
        err_desc += sftp_get_error(sftp);

        sftp_free(sftp);
        ssh_disconnect(ssh);
        ssh_free(ssh);

        throw std::runtime_error(err_desc);
    }

}

void RemoteRunner::autheficateUser(ssh_session& session) {

    std::string auth_username = settings.username.toStdString();

    int auth_result = ssh_userauth_password(session, auth_username.c_str(), settings.userpass.toStdString().c_str());

    if (auth_result != SSH_OK) {

        std::string err_desc("Ошибка авторизации на сервере: ");
        err_desc += ssh_get_error(session);

        ssh_disconnect(session);
        ssh_free(session);

        throw std::runtime_error(err_desc);
    }
}

void RemoteRunner::connectToHost(ssh_session& session) {
    session = ssh_new();

    if (session == NULL) {
        throw std::runtime_error("не удалось аллоцировать SSH сессию.");
    }

    int port = settings.remote_hosting_port.toInt();
    int log_verbosity = SSH_LOG_NOLOG;
    std::string host_ip = settings.remote_hosting_ip.toStdString();
    std::string host_username = settings.username.toStdString() + "@" + host_ip;

    ssh_options_set(session, SSH_OPTIONS_HOST, host_ip.c_str());
    ssh_options_set(session, SSH_OPTIONS_PORT, &port);
    ssh_options_set(session, SSH_OPTIONS_USER, host_username.c_str());
    ssh_options_set(session, SSH_OPTIONS_LOG_VERBOSITY, &log_verbosity);

    int connection_result = ssh_connect(session);

    if (connection_result != SSH_OK) {

        std::string err_desc("Не удалось подключиться к серверу ");
        err_desc += host_ip + ":" + std::to_string(port) + " Error: ";
        err_desc += ssh_get_error(session);

        ssh_free(session);

        throw std::runtime_error(err_desc);
    }

}
