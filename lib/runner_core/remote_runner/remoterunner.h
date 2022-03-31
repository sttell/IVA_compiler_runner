#ifndef REMOTERUNNER_H
#define REMOTERUNNER_H

#define DEBUG_REMOTE true

#include <libssh/libssh.h>
#include <libssh/sftp.h>

#include <boost/filesystem.hpp>
#include <string>
#include <boost/process.hpp>
#include <iostream>
#include <QRegularExpression>

#include "lib/runner_core/runner_settings.h"
#include "lib/thread_api/progressbar_buffer.h"
#include "lib/thread_api/statusbuffer_cache.h"

#define REMOTE_RUNNER_THROW_HEADER "Remote Runner: "
#define REMOTE_TEMPORAL_DIRECTORY "IvaRunnerRemote"
#define REMOTE_TENSORS_DIRNAME "Tensors"

struct RemotePathes {
    std::string program_dir;
    std::string program_path;
    std::string input_dir;
    std::string input_path;
    std::string output_dir;
    std::string output_path;
};

class RemoteRunner
{
public:
    RemoteRunner(RemoteRunnerSettings& _settings, ProgressBarBuffer* _progress, StatusBufferCache* _log)
        : settings(_settings), progress(_progress), log(_log) {};
    ~RemoteRunner() {};

    void runProcess();

private:
    RemoteRunnerSettings settings;
    ProgressBarBuffer* progress;
    StatusBufferCache* log;
    RemotePathes remote_pathes;

    void checkSettingsCorrectness();
    void fillRemotePathes();
    void freeMemory(ssh_session& ssh, sftp_session& sftp);
    void copyOutputToLocal(ssh_session& ssh, sftp_session& sftp);
    void runRemote(ssh_session& ssh, sftp_session& sftp);
    bool parseStdOut(const std::string& out, QStringList& result) ;
    void copyFileToRemoteHost(ssh_session& ssh, sftp_session& sftp, std::string local_path, std::string remote_path, std::string file_desc) ;
    void copyFileFromRemoteHost(ssh_session& ssh, sftp_session& sftp, std::string local_path, std::string remote_path, std::string file_desc);
    void copyTensorToRemoteHost(ssh_session& ssh, sftp_session& sftp);
    void copyProgramToRemoteDirectory(ssh_session& ssh, sftp_session& sftp);
    void createRemoteDirectory(ssh_session& ssh, sftp_session& sftp, std::string path);
    void createLocalDirectory(std::string path);
    void initDirectories(ssh_session& ssh, sftp_session& sftp) ;
    void connectToSFTP(ssh_session& ssh, sftp_session& sftp) ;
    void autheficateUser(ssh_session& session);
    void connectToHost(ssh_session& session);

};


#endif // REMOTERUNNER_H
