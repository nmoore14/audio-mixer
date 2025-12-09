#include "shared_state.h"
#include <stdio.h>

#ifdef HAVE_NOTCURSES
#include <notcurses/notcurses.h>
#endif

/**
 * Render routing matrix view
 */
void routing_view_render(SharedState* state) {
    // TODO: Render routing matrix with notcurses
    // - Show apps in rows
    // - Show channels in columns
    // - Display routing connections
    // - Allow drag-and-drop style routing
    (void)state;
}

/**
 * Handle routing view input
 */
int routing_view_handle_input(int key) {
    // TODO: Handle keyboard input for routing view
    // - Arrow keys to navigate
    // - Space to toggle routing
    // - Enter to confirm
    // - Tab to switch between apps and channels
    (void)key;
    return 0;
}

/**
 * Move app to different channel
 */
int routing_view_move_app(int app_id, int from_channel, int to_channel) {
    // TODO: Send move command to daemon
    // - Create CMD_MOVE_APP command
    // - Send via IPC
    // - Wait for response
    (void)app_id;
    (void)from_channel;
    (void)to_channel;
    return -1;
}
