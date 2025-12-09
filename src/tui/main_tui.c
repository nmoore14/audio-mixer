#include "protocol.h"
#include "shared_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef HAVE_NOTCURSES
#include <notcurses/notcurses.h>
#endif

/**
 * Initialize TUI
 */
int tui_init(void) {
    // TODO: Initialize notcurses
    // - Create notcurses context
    // - Set up color pairs
    // - Create initial windows/planes
#ifdef HAVE_NOTCURSES
    return -1;
#else
    fprintf(stderr, "Error: TUI built without notcurses support\n");
    return -1;
#endif
}

/**
 * Shutdown TUI
 */
void tui_shutdown(void) {
    // TODO: Cleanup notcurses
    // - Destroy windows/planes
    // - Stop notcurses
#ifdef HAVE_NOTCURSES
#endif
}

/**
 * Main TUI event loop
 */
int tui_run(void) {
    // TODO: Implement TUI main loop
    // - Poll for keyboard input
    // - Update display from shared state
    // - Handle user input (volume changes, routing, etc.)
    // - Send commands to daemon via IPC
    return -1;
}

/**
 * TUI entry point
 */
int main(void) {
    printf("Audio Mixer TUI\n");

    // TODO: Implement TUI
    // - Connect to daemon via IPC
    // - Initialize TUI
    // - Run main loop
    // - Cleanup on exit

    printf("Connecting to daemon...\n");

    if (ipc_client_connect() < 0) {
        fprintf(stderr, "Error: Could not connect to daemon. Is it running?\n");
        return 1;
    }

    printf("Connected successfully\n");
    printf("Press Ctrl+C to exit\n");

    // tui_init();
    // tui_run();
    // tui_shutdown();

    ipc_client_disconnect();
    return 0;
}
