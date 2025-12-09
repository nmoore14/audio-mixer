#ifndef AUDIO_INTERFACE_H
#define AUDIO_INTERFACE_H

#include "mixer_types.h"
#include <stddef.h>
#include <stdbool.h>

/**
 * Abstract audio interface for platform-specific implementations
 * This provides a common API for CoreAudio (macOS) and WASAPI (Windows)
 */

/**
 * Platform-specific audio context (opaque pointer)
 */
typedef struct AudioContext AudioContext;

/**
 * Audio device information
 */
typedef struct AudioDevice {
    int id;
    char name[256];
    int channel_count;
    int sample_rate;
    bool is_input;
    bool is_output;
    bool is_default;
} AudioDevice;

/**
 * Audio callback function type
 * Called by the platform audio system when audio data is needed
 *
 * @param userdata User-provided data pointer (typically Mixer*)
 * @param output Output buffer to fill with audio
 * @param frames Number of frames to process
 */
typedef void (*AudioCallback)(void* userdata, float* output, size_t frames);

// Function declarations - Audio Interface
AudioContext* audio_init(void);
void audio_shutdown(AudioContext* ctx);
int audio_start(AudioContext* ctx, AudioCallback callback, void* userdata);
void audio_stop(AudioContext* ctx);

// Device enumeration
int audio_enumerate_devices(AudioDevice** devices, int* count);
void audio_free_device_list(AudioDevice* devices);
int audio_set_output_device(AudioContext* ctx, int device_id);

// Application capture (platform-specific)
int audio_enumerate_apps(AudioApp** apps, int* count);
void audio_free_app_list(AudioApp* apps);
int audio_start_app_capture(AudioContext* ctx, int app_id);
void audio_stop_app_capture(AudioContext* ctx, int app_id);

// Configuration
int audio_set_sample_rate(AudioContext* ctx, int sample_rate);
int audio_set_buffer_size(AudioContext* ctx, size_t buffer_size);
int audio_get_sample_rate(AudioContext* ctx);
size_t audio_get_buffer_size(AudioContext* ctx);

#endif // AUDIO_INTERFACE_H
