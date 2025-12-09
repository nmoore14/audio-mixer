# GUI (Graphical User Interface) executable

# Try to find raylib
find_package(raylib QUIET)

# Create GUI executable
add_executable(audio-mixer-gui
    main_gui.c
    ui_renderer.c
    drag_drop.c
)

target_link_libraries(audio-mixer-gui PRIVATE
    mixer_ipc
    Threads::Threads
)

# Link raylib if found
if(raylib_FOUND)
    target_link_libraries(audio-mixer-gui PRIVATE raylib)
    target_compile_definitions(audio-mixer-gui PRIVATE HAVE_RAYLIB)
else()
    message(WARNING "raylib not found - GUI will not be built with graphics support. Install with: brew install raylib (macOS) or your package manager")
endif()

# Platform-specific GUI dependencies
if(APPLE)
    target_link_libraries(audio-mixer-gui PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
