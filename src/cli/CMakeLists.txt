# Main launcher executable

add_executable(audio-mixer
    launcher.c
)

target_link_libraries(audio-mixer PRIVATE
    Threads::Threads
)

target_include_directories(audio-mixer PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_BINARY_DIR}/include
)
