#ifndef MIXER_TYPES_H
#define MIXER_TYPES_H

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_CHANNELS 16
#define MAX_APPS 64
#define MAX_APPS_PER_CHANNEL 32
#define CHANNEL_NAME_SIZE 64
#define APP_NAME_SIZE 256
#define SAMPLE_RATE 48000
#define BUFFER_SIZE 512

/**
 * Represents an audio application that can be routed to channels
 */
typedef struct AudioApp {
    int id;
    char name[APP_NAME_SIZE];
    int process_id;
    void* audio_buffer;  // Will be ring buffer
    float volume;        // Application-level volume (0.0 to 1.0)
    bool active;         // Is the app currently producing audio
    // Add fields as needed
} AudioApp;

/**
 * Represents a mixing channel
 */
typedef struct Channel {
    int id;
    char name[CHANNEL_NAME_SIZE];
    float volume;                              // Channel volume (0.0 to 1.0)
    bool muted;
    bool solo;
    int app_count;
    AudioApp* apps[MAX_APPS_PER_CHANNEL];
    float* mix_buffer;                         // Intermediate mix buffer
    // Add fields as needed
} Channel;

/**
 * Main mixer state
 */
typedef struct Mixer {
    Channel channels[MAX_CHANNELS];
    int channel_count;
    float* mix_buffer;                         // Final output buffer
    size_t buffer_size;                        // Size in frames
    pthread_t audio_thread;
    bool running;
    void* platform_data;                       // Platform-specific data
    // Add fields as needed
} Mixer;

/**
 * Ring buffer for audio data
 */
typedef struct RingBuffer {
    float* data;
    size_t size;          // Total size in samples
    size_t write_pos;
    size_t read_pos;
    pthread_mutex_t lock;
    // Add fields as needed
} RingBuffer;

// Function declarations - Core Mixer
Mixer* mixer_create(void);
int mixer_init(Mixer* mixer);
void mixer_process(Mixer* mixer, float* output, size_t frames);
void mixer_destroy(Mixer* mixer);
int mixer_start(Mixer* mixer);
void mixer_stop(Mixer* mixer);

// Function declarations - Channel Management
int channel_create(Mixer* mixer, const char* name);
int channel_delete(Mixer* mixer, int channel_id);
int channel_set_volume(Mixer* mixer, int channel_id, float volume);
int channel_set_mute(Mixer* mixer, int channel_id, bool muted);
int channel_set_solo(Mixer* mixer, int channel_id, bool solo);
Channel* channel_get(Mixer* mixer, int channel_id);

// Function declarations - App Routing
int routing_add_app_to_channel(Mixer* mixer, int app_id, int channel_id);
int routing_remove_app_from_channel(Mixer* mixer, int app_id, int channel_id);
int routing_move_app(Mixer* mixer, int app_id, int from_channel, int to_channel);
AudioApp* routing_find_app(Mixer* mixer, int app_id);

// Function declarations - Ring Buffer
RingBuffer* ringbuffer_create(size_t size);
void ringbuffer_destroy(RingBuffer* rb);
int ringbuffer_write(RingBuffer* rb, const float* data, size_t frames);
int ringbuffer_read(RingBuffer* rb, float* data, size_t frames);
size_t ringbuffer_available_read(RingBuffer* rb);
size_t ringbuffer_available_write(RingBuffer* rb);
void ringbuffer_reset(RingBuffer* rb);

#endif // MIXER_TYPES_H
