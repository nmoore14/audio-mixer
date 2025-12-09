cmake_minimum_required(VERSION 3.15)
project(AudioMixer VERSION 0.1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Platform detection
if(APPLE)
    set(PLATFORM_MACOS TRUE)
    message(STATUS "Building for macOS")
elseif(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Building for Windows")
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

# Configuration file
configure_file(
    ${CMAKE_SOURCE_DIR}/include/config.h.in
    ${CMAKE_BINARY_DIR}/include/config.h
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)

# Compiler flags
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Platform-specific dependencies
if(PLATFORM_MACOS)
    find_library(COREAUDIO_FRAMEWORK CoreAudio REQUIRED)
    find_library(AUDIOUNIT_FRAMEWORK AudioUnit REQUIRED)
    find_library(COREFOUNDATION_FRAMEWORK CoreFoundation REQUIRED)

    set(PLATFORM_LIBS
        ${COREAUDIO_FRAMEWORK}
        ${AUDIOUNIT_FRAMEWORK}
        ${COREFOUNDATION_FRAMEWORK}
    )

    # Add macOS platform source directory
    add_subdirectory(src/platform/macos)

elseif(PLATFORM_WINDOWS)
    # Windows-specific libraries will be linked in subdirectory
    add_subdirectory(src/platform/windows)
endif()

# Find threading library
find_package(Threads REQUIRED)

# Core library - shared between all targets
add_library(mixer_core STATIC
    src/core/mixer.c
    src/core/channels.c
    src/core/routing.c
    src/core/ringbuffer.c
)
target_link_libraries(mixer_core PRIVATE Threads::Threads)

# IPC library - shared between daemon and frontends
add_library(mixer_ipc STATIC
    src/ipc/server.c
    src/ipc/client.c
)
target_link_libraries(mixer_ipc PRIVATE Threads::Threads)

# Daemon executable
add_executable(audio-mixer-daemon
    src/core/daemon.c
)
target_link_libraries(audio-mixer-daemon PRIVATE
    mixer_core
    mixer_ipc
    platform_audio
    Threads::Threads
    ${PLATFORM_LIBS}
)

# TUI subdirectory
add_subdirectory(src/tui)

# GUI subdirectory
add_subdirectory(src/gui)

# Main launcher executable
add_subdirectory(src/cli)

# Installation rules
install(TARGETS audio-mixer-daemon audio-mixer-tui audio-mixer-gui audio-mixer
    RUNTIME DESTINATION bin
)
