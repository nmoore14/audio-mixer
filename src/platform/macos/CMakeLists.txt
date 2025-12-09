# macOS-specific platform audio implementation

add_library(platform_audio STATIC
    coreaudio.c
    app_capture.c
)

# Link macOS frameworks
target_link_libraries(platform_audio PUBLIC
    ${COREAUDIO_FRAMEWORK}
    ${AUDIOUNIT_FRAMEWORK}
    ${COREFOUNDATION_FRAMEWORK}
)

target_include_directories(platform_audio PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
