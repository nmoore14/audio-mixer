#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * IPC Protocol definition for communication between daemon and frontends
 */

#define PROTOCOL_VERSION 1
#define MAX_COMMAND_SIZE 1024

/**
 * Command types
 */
typedef enum {
    CMD_GET_STATE,           // Request full state
    CMD_SET_VOLUME,          // Set channel volume
    CMD_MOVE_APP,            // Move app between channels
    CMD_MUTE_CHANNEL,        // Mute/unmute channel
    CMD_SOLO_CHANNEL,        // Solo/unsolo channel
    CMD_CREATE_CHANNEL,      // Create new channel
    CMD_DELETE_CHANNEL,      // Delete channel
    CMD_SET_APP_VOLUME,      // Set app-specific volume
    CMD_SHUTDOWN,            // Shutdown daemon
    CMD_PING,                // Keep-alive ping
    // Add more commands as needed
} CommandType;

/**
 * Response status codes
 */
typedef enum {
    STATUS_OK = 0,
    STATUS_ERROR = 1,
    STATUS_INVALID_COMMAND = 2,
    STATUS_INVALID_CHANNEL = 3,
    STATUS_INVALID_APP = 4,
    STATUS_PERMISSION_DENIED = 5,
    // Add more status codes as needed
} StatusCode;

/**
 * Command structure
 */
typedef struct Command {
    CommandType type;
    uint32_t sequence;       // For matching responses

    // Command parameters (union to save space)
    union {
        struct {
            int channel_id;
            float volume;
        } set_volume;

        struct {
            int app_id;
            int from_channel;
            int to_channel;
        } move_app;

        struct {
            int channel_id;
            bool muted;
        } mute_channel;

        struct {
            int channel_id;
            bool solo;
        } solo_channel;

        struct {
            char name[64];
        } create_channel;

        struct {
            int channel_id;
        } delete_channel;

        struct {
            int app_id;
            float volume;
        } set_app_volume;

        // Add more command parameters as needed
    } params;
} Command;

/**
 * Response structure
 */
typedef struct Response {
    StatusCode status;
    uint32_t sequence;       // Matches command sequence
    char message[256];       // Error message or additional info

    // Response data (if needed)
    union {
        int int_value;
        float float_value;
        bool bool_value;
        // Add more response data types as needed
    } data;
} Response;

// Function declarations - IPC Server
int ipc_server_init(void);
void ipc_server_shutdown(void);
int ipc_server_process_commands(void);
int ipc_server_send_response(Response* response);

// Function declarations - IPC Client
int ipc_client_connect(void);
void ipc_client_disconnect(void);
int ipc_client_send_command(Command* cmd);
int ipc_client_receive_response(Response* response, int timeout_ms);

#endif // PROTOCOL_H
