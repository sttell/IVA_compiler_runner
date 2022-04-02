#ifndef SETTINGS_CONFIG_H
#define SETTINGS_CONFIG_H

#define COMPILER_SETTINGS_GROUP "Compiler Settings"
#define RUNNER_SETTINGS_GROUP "Runner Settings"
#define ANALYSIS_SETTINGS_GROUP "Analysis Settings"
#define GLOBAL_SETTINGS_GROUP "Global Settings"
#define REMOTE_AUTH_GROUP "Remote_Auth_Settings"

#define SETTINGS_DIRECTORY_PATH "cfg/"
#define SETTINGS_CONFIGURATION_PATH "cfg/settings.ini"
#define STATIC_COMPILER_SETTINGS_CONFIGURATION_PATH "cfg/static_compiler_settings.ini"
#define SETTINGS_CONFIGURATION_FORMAT QSettings::IniFormat

#include <string>
#include <unistd.h>

namespace GlobalSettingName {
    inline const char* isFirstRunInited   = "is_application_inited";
    inline const char* programArchiveName = "ArchiveName";
}

namespace DefaultSettingsImpl
{

inline const char* get_user_folder() 
{

    std::string user_folder { "/home/" };
    return (user_folder + getlogin()).c_str();    

}

inline const char* get_tensor_path()
{

    std::string user_folder { get_user_folder() };
    return (user_folder + "/tensor.bin").c_str();

}

} // namespace DefaultSettingsImpl



namespace CompilerSettingsDefault {
    inline const char* user_folder = DefaultSettingsImpl::get_user_folder();
    inline const char* paddings    = "0,0,0,0";
    inline const char* tensor_size = "1,1,1,1";
    inline const char* program_dir = "TestProgram";

}

namespace RunnerSettingsDefault {
    inline const char* user_folder = DefaultSettingsImpl::get_user_folder();
    inline const char* tensor_size = "1,1,1,1";
    inline const char* tensor_path = DefaultSettingsImpl::get_tensor_path();
}



#endif // SETTINGS_CONFIG_H
