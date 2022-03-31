cmake_minimum_required(VERSION 3.5)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-fpermissive)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Boost 1.71.0 COMPONENTS filesystem thread program_options)
find_package(libssh REQUIRED CONFIG)

set (COMPILER_CORE_HEADERS
    lib/compiler_core/include/aliases.h
    lib/compiler_core/include/compilerCore.h
    lib/compiler_core/include/compileStatus.h
    lib/compiler_core/include/deviceTypes.h
    lib/compiler_core/include/jsonHandler.h
    lib/compiler_core/include/mapSize.h
    lib/compiler_core/include/module.h
    lib/compiler_core/include/moduleExitStatus.h
    lib/compiler_core/include/modules.h
    lib/compiler_core/include/path.h
    lib/compiler_core/include/pipeline.h
    lib/compiler_core/include/programFilesDescriptor.h
    lib/compiler_core/include/timer.h
    lib/compiler_core/include/tpuDescriptor.h
    lib/compiler_core/include/settings/addrCheckerSettings.h
    lib/compiler_core/include/settings/compilerRunnerSettings.h
    lib/compiler_core/include/settings/globalSettings.h
    lib/compiler_core/include/settings/metadataCreatorSettings.h
    lib/compiler_core/include/settings/pickleConverterSettings.h
    lib/compiler_core/include/settings/programComparatorSettings.h
    lib/compiler_core/include/modules/addressCheckerModule.h
    lib/compiler_core/include/modules/compilerRunnerModule.h
    lib/compiler_core/include/modules/metadataCreatorModule.h
    lib/compiler_core/include/modules/pickleConverterModule.h
    lib/compiler_core/include/modules/programComparatorModule.h
    lib/compiler_core/include/modules/optimizationChangerModule.h
    lib/compiler_core/include/settings/optimizationChangerSettings.h
    )

set (COMPILER_CORE_SOURCES
    lib/compiler_core/lib/compilerCore.cpp
    lib/compiler_core/lib/jsonHandler.cpp
    lib/compiler_core/lib/module.cpp
    lib/compiler_core/lib/path.cpp
    lib/compiler_core/lib/pipeline.cpp
    lib/compiler_core/lib/timer.cpp
    lib/compiler_core/src/modules/address_checker/addressCheckerModule.cpp
    lib/compiler_core/src/modules/compiler_runner/compilerRunnerModule.cpp
    lib/compiler_core/src/modules/metadata_creator/metadataCreatorModule.cpp
    lib/compiler_core/src/modules/pickle_converter/pickleConverterModule.cpp
    lib/compiler_core/src/modules/program_comparator/programComparatorModule.cpp
    lib/compiler_core/src/modules/optimization_changer/optimizationChangerModule.cpp
    )

set(RUNNER_CORE_SOURCES
    lib/runner_core/runnercore.cpp
    lib/runner_core/tensor_creator/tensorcreator.cpp
    lib/runner_core/local_runner/localrunner.cpp
    lib/runner_core/remote_runner/remoterunner.cpp
    )

set(RUNNER_CORE_HEADERS
    lib/runner_core/runnercore.h
    lib/runner_core/tensor_creator/tensorcreator.h
    lib/runner_core/local_runner/localrunner.h
    lib/runner_core/remote_runner/remoterunner.h
    lib/runner_core/runner_settings.h
    )


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ui/welcome_form.h
        ui/welcome_form.cpp
        ui/welcome_form_ui.h
        ui/compiler_settings_dialog.cpp
        ui/compiler_settings_dialog.h
        ui/compiler_settings_dialog_ui.h
        ui/warning_settings_dialog.cpp
        ui/warning_settings_dialog.h
        ui/warning_settings_dialog_ui.h
        ui/remote_auth_dialog.h
        ui/remote_auth_dialog.cpp
        ui/remote_auth_dialog_ui.h
        include/log_config.h
        include/settings_config.h
        include/wrong_fmt_captures.h
        lib/correct_checkers/compile_runner_preprocessor.cpp
        lib/correct_checkers/compile_runner_preprocessor.h
        lib/controllers/statusbar_controller.h
        lib/controllers/statusbar_controller.cpp
        lib/thread_api/statusbuffer_cache.h
        lib/thread_api/statusbuffer_cache.cpp
        lib/thread_api/interrupt_buffer.cpp
        lib/thread_api/interrupt_buffer.h
        lib/thread_api/progressbar_buffer.h
        lib/thread_api/progressbar_buffer.cpp
        lib/buffers/settingsbuffer.cpp
        lib/buffers/settingsbuffer.h

        ${COMPILER_CORE_HEADERS}
        ${COMPILER_CORE_SOURCES}

        ${RUNNER_CORE_SOURCES}
        ${RUNNER_CORE_HEADERS}
)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Libssh_INCLUDE_DIRS})
include_directories("include")
include_directories("ui")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gui SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES} ssh)
set_target_properties(gui PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gui)
endif()
