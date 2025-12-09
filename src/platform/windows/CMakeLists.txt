# Windows-specific platform audio implementation

add_library(platform_audio STATIC
    wasapi.c
    app_capture.c
)

# Link Windows libraries
target_link_libraries(platform_audio PUBLIC
    ole32
    oleaut32
    winmm
    ksuser
)

target_include_directories(platform_audio PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
