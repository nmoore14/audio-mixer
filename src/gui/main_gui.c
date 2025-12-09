#include "protocol.h"
#include "shared_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef HAVE_RAYLIB
#include <raylib.h>
#endif

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

/**
 * Initialize GUI
 */
int gui_init(void) {
    // TODO: Initialize raylib
    // - Create window
    // - Set target FPS
    // - Load fonts and resources
#ifdef HAVE_RAYLIB
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Audio Mixer");
    SetTargetFPS(60);
    return 0;
#else
    fprintf(stderr, "Error: GUI built without raylib support\n");
    return -1;
#endif
}

/**
 * Shutdown GUI
 */
void gui_shutdown(void) {
    // TODO: Cleanup raylib
    // - Unload resources
    // - Close window
#ifdef HAVE_RAYLIB
    CloseWindow();
#endif
}

/**
 * Main GUI render loop
 */
int gui_run(void) {
    // TODO: Implement GUI main loop
    // - Handle window events
    // - Process mouse/keyboard input
    // - Update from shared state
    // - Render UI elements
    // - Send commands to daemon via IPC
#ifdef HAVE_RAYLIB
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Audio Mixer GUI", 10, 10, 20, DARKGRAY);
        DrawText("TODO: Implement UI", 10, 40, 16, GRAY);
        EndDrawing();
    }
#endif
    return 0;
}

/**
 * GUI entry point
 */
int main(void) {
    printf("Audio Mixer GUI\n");

    // TODO: Implement GUI
    // - Connect to daemon via IPC
    // - Initialize GUI
    // - Run main loop
    // - Cleanup on exit

    printf("Connecting to daemon...\n");

    if (ipc_client_connect() < 0) {
        fprintf(stderr, "Error: Could not connect to daemon. Is it running?\n");
        return 1;
    }

    printf("Connected successfully\n");

    if (gui_init() < 0) {
        ipc_client_disconnect();
        return 1;
    }

    gui_run();
    gui_shutdown();

    ipc_client_disconnect();
    return 0;
}
