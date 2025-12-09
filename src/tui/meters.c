#include "shared_state.h"
#include <stdio.h>
#include <math.h>

#ifdef HAVE_NOTCURSES
#include <notcurses/notcurses.h>
#endif

/**
 * Convert linear amplitude to dB
 */
float meters_linear_to_db(float linear) {
    // TODO: Implement linear to dB conversion
    // - Handle zero/negative values
    // - Return dB value
    (void)linear;
    return -96.0f;
}

/**
 * Render peak meter
 */
void meters_render_peak(float level, int x, int y, int height) {
    // TODO: Render vertical peak meter with notcurses
    // - Convert level to dB
    // - Calculate bar height
    // - Color code (green/yellow/red zones)
    // - Show numeric dB value
    (void)level;
    (void)x;
    (void)y;
    (void)height;
}

/**
 * Render all channel meters
 */
void meters_render_all(SharedState* state) {
    // TODO: Render meters for all channels
    // - Get meter values from shared state
    // - Render each channel meter
    // - Show master meter
    (void)state;
}

/**
 * Update meters from shared state
 */
void meters_update(SharedState* state) {
    // TODO: Update meter displays
    // - Get latest meter values
    // - Apply smoothing/decay
    // - Trigger redraw if needed
    (void)state;
}
