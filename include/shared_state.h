#ifndef SHARED_STATE_H
#define SHARED_STATE_H

#include "mixer_types.h"
#include <pthread.h>

/**
 * Shared state structure for IPC between daemon and frontends
 * This will be stored in shared memory
 */
typedef struct SharedState {
    Channel channels[MAX_CHANNELS];
    int channel_count;

    AudioApp apps[MAX_APPS];
    int app_count;

    float meters[MAX_CHANNELS];          // Peak meters for each channel
    float master_meter_left;
    float master_meter_right;

    pthread_mutex_t lock;
    bool daemon_running;

    // Add fields as needed
} SharedState;

// Function declarations
SharedState* shared_state_create(void);
void shared_state_destroy(SharedState* state);
int shared_state_lock(SharedState* state);
int shared_state_unlock(SharedState* state);
void shared_state_update_from_mixer(SharedState* state, Mixer* mixer);

#endif // SHARED_STATE_H
