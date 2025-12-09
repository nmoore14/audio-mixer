# TUI (Terminal User Interface) executable

# Try to find notcurses
find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(NOTCURSES notcurses)
endif()

# Create TUI executable
add_executable(audio-mixer-tui
    main_tui.c
    channel_view.c
    routing_view.c
    meters.c
)

target_link_libraries(audio-mixer-tui PRIVATE
    mixer_ipc
    Threads::Threads
)

# Link notcurses if found
if(NOTCURSES_FOUND)
    target_include_directories(audio-mixer-tui PRIVATE ${NOTCURSES_INCLUDE_DIRS})
    target_link_libraries(audio-mixer-tui PRIVATE ${NOTCURSES_LIBRARIES})
    target_compile_definitions(audio-mixer-tui PRIVATE HAVE_NOTCURSES)
else()
    message(WARNING "notcurses not found - TUI will have limited functionality. Install with: brew install notcurses (macOS) or your package manager")
endif()
