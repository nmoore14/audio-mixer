#include "shared_state.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef HAVE_RAYLIB
#include <raylib.h>
#endif

typedef struct DragState {
    bool is_dragging;
    int dragged_app_id;
    int source_channel_id;
    int mouse_x;
    int mouse_y;
} DragState;

static DragState g_drag_state = {0};

/**
 * Start dragging an app
 */
void drag_drop_start(int app_id, int channel_id, int mouse_x, int mouse_y) {
    // TODO: Start drag operation
    // - Set drag state
    // - Store app and channel info
    // - Start visual feedback
    (void)app_id;
    (void)channel_id;
    (void)mouse_x;
    (void)mouse_y;
}

/**
 * Update drag position
 */
void drag_drop_update(int mouse_x, int mouse_y) {
    // TODO: Update drag position
    // - Update visual feedback
    // - Highlight drop targets
    (void)mouse_x;
    (void)mouse_y;
}

/**
 * End drag operation (drop)
 */
int drag_drop_end(int target_channel_id) {
    // TODO: Complete drag-and-drop
    // - Send CMD_MOVE_APP command
    // - Clear drag state
    // - Update UI
    (void)target_channel_id;
    return -1;
}

/**
 * Cancel drag operation
 */
void drag_drop_cancel(void) {
    // TODO: Cancel drag
    // - Clear drag state
    // - Reset visual feedback
}

/**
 * Check if currently dragging
 */
bool drag_drop_is_active(void) {
    // TODO: Return drag state
    return g_drag_state.is_dragging;
}

/**
 * Render drag visual feedback
 */
void drag_drop_render(void) {
    // TODO: Render drag feedback
    // - Draw dragged app preview
    // - Show drop target highlights
    // - Draw connection line
}

/**
 * Get drop target at position
 */
int drag_drop_get_target_at(int x, int y) {
    // TODO: Determine drop target
    // - Hit test against channel areas
    // - Return channel ID or -1
    (void)x;
    (void)y;
    return -1;
}
