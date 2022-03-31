#ifndef RUNNER_SETTINGS_H
#define RUNNER_SETTINGS_H

#include <QString>

struct LocalRunnerSettings {
    QString program_directory;
    QString program_name;
    QString input_tensor_path;
};

struct RemoteRunnerSettings {
    QString program_directory;
    QString program_name;

    QString input_tensor_path;
    bool is_remote_tensor;

    bool is_generated_tensor;
    QString input_tensor_name;

    QString username;
    QString userpass;
    QString remote_hosting_ip;
    QString remote_hosting_port;
};

struct TensorCreatorSettings {
    QString tensor_size;
    QString tensor_save_path;
};

struct RunnerSettings {

    RunnerSettings(RemoteRunnerSettings& settings) : is_remote(true), is_tensor_create(false), remote_settings(settings) {};
    RunnerSettings(LocalRunnerSettings& settings) : is_remote(false), is_tensor_create(false), local_settings(settings) {};
    RunnerSettings(RemoteRunnerSettings& r_settings, TensorCreatorSettings& tc_settings) :
        is_remote(true), is_tensor_create(true), remote_settings(r_settings), tensor_create_settings(tc_settings) {};
    RunnerSettings(LocalRunnerSettings& r_settings, TensorCreatorSettings& tc_settings) :
        is_remote(false), is_tensor_create(true), local_settings(r_settings), tensor_create_settings(tc_settings) {};

    bool is_remote;
    bool is_tensor_create;

    LocalRunnerSettings local_settings;
    RemoteRunnerSettings remote_settings;
    TensorCreatorSettings tensor_create_settings;
};

#endif // RUNNER_SETTINGS_H
