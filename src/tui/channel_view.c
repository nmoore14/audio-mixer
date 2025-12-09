#include "shared_state.h"
#include <stdio.h>

#ifdef HAVE_NOTCURSES
#include <notcurses/notcurses.h>
#endif

/**
 * Render channel list view
 */
void channel_view_render(SharedState* state) {
    // TODO: Render channel list with notcurses
    // - Display each channel with name, volume, mute/solo status
    // - Show which apps are routed to each channel
    // - Highlight selected channel
    // - Show volume faders
    (void)state;
}

/**
 * Handle channel view input
 */
int channel_view_handle_input(int key) {
    // TODO: Handle keyboard input for channel view
    // - Arrow keys to select channel
    // - +/- to adjust volume
    // - M to toggle mute
    // - S to toggle solo
    // - Enter to edit
    (void)key;
    return 0;
}

/**
 * Update channel view from shared state
 */
void channel_view_update(SharedState* state) {
    // TODO: Update view when state changes
    // - Redraw channels if changed
    // - Update volume displays
    // - Update meters
    (void)state;
}
