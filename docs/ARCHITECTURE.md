# Audio Mixer Architecture

## Overview

The Audio Mixer is designed as a modular, cross-platform application with a daemon-frontend architecture. This design allows multiple user interfaces to control a single audio processing backend.

## System Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                        Frontends                             │
├─────────────────────┬───────────────────────────────────────┤
│                     │                                        │
│  ┌───────────┐      │      ┌───────────┐                    │
│  │    TUI    │      │      │    GUI    │                    │
│  │(notcurses)│      │      │ (raylib)  │                    │
│  └─────┬─────┘      │      └─────┬─────┘                    │
│        │            │            │                          │
└────────┼────────────┴────────────┼──────────────────────────┘
         │                         │
         │        IPC Layer        │
         │    (Unix Sockets /      │
         │     Named Pipes)        │
         │                         │
┌────────┴─────────────────────────┴──────────────────────────┐
│                      Daemon Process                          │
├──────────────────────────────────────────────────────────────┤
│  ┌────────────────────────────────────────────────────┐     │
│  │              IPC Server                             │     │
│  │  - Command Processing                               │     │
│  │  - State Synchronization                            │     │
│  └────────────────────────────────────────────────────┘     │
│                           │                                  │
│  ┌────────────────────────┴──────────────────────────┐     │
│  │              Core Mixer Engine                      │     │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐         │     │
│  │  │ Channel  │  │ Channel  │  │ Channel  │         │     │
│  │  │    1     │  │    2     │  │   ...    │         │     │
│  │  └────┬─────┘  └────┬─────┘  └────┬─────┘         │     │
│  │       │             │             │                │     │
│  │  ┌────┴──────────────┴──────────────┘              │     │
│  │  │        Audio Processing Thread                  │     │
│  │  │  - Mix channels                                 │     │
│  │  │  - Apply volume/mute/solo                       │     │
│  │  │  - Update meters                                │     │
│  │  └─────────────────────┬──────────────────────────┘     │
│  └────────────────────────┼──────────────────────────────┐ │
│                           │                               │ │
│  ┌────────────────────────┴───────────────────────────┐  │ │
│  │         Platform Audio Interface                    │  │ │
│  │  ┌──────────────┐         ┌──────────────┐         │  │ │
│  │  │   CoreAudio  │   or    │   WASAPI     │         │  │ │
│  │  │   (macOS)    │         │  (Windows)   │         │  │ │
│  │  └──────┬───────┘         └──────┬───────┘         │  │ │
│  └─────────┼────────────────────────┼─────────────────┘  │ │
└────────────┼────────────────────────┼─────────────────────┘
             │                        │
┌────────────┴────────────────────────┴─────────────────────┐
│                  System Audio Layer                        │
│  ┌────────────┐  ┌────────────┐  ┌────────────┐          │
│  │   App 1    │  │   App 2    │  │   App N    │          │
│  │  (Spotify) │  │  (Discord) │  │   (...)    │          │
│  └────────────┘  └────────────┘  └────────────┘          │
└────────────────────────────────────────────────────────────┘
```

## Component Responsibilities

### 1. Core Mixer (`src/core/`)

#### Mixer (`mixer.c`)
- Main mixer state and lifecycle management
- Audio processing coordination
- Thread management

#### Channels (`channels.c`)
- Channel creation and deletion
- Volume/mute/solo control
- Channel state management

#### Routing (`routing.c`)
- Application to channel routing
- Dynamic routing changes
- Application discovery and tracking

#### Ring Buffer (`ringbuffer.c`)
- Lock-free audio buffer implementation
- Used for app audio capture buffering
- Handles wraparound and overrun conditions

### 2. Platform Layer (`src/platform/`)

Provides an abstract interface for platform-specific audio operations.

#### macOS Implementation (`macos/`)
- **CoreAudio** (`coreaudio.c`): Audio device management and output
- **App Capture** (`app_capture.c`): Per-app audio capture using Audio Server API

#### Windows Implementation (`windows/`)
- **WASAPI** (`wasapi.c`): Audio device management and output
- **App Capture** (`app_capture.c`): Per-app audio capture using Audio Session API

### 3. IPC Layer (`src/ipc/`)

#### Server (`server.c`)
- Listens for client connections
- Processes commands from frontends
- Updates shared state
- Sends responses

#### Client (`client.c`)
- Connects to daemon
- Sends commands
- Receives responses and state updates

#### Protocol (`protocol.h`)
- Defines command/response format
- Version negotiation
- Error codes

### 4. Frontends

#### TUI (`src/tui/`)
- Terminal-based interface using notcurses
- Views: channel list, routing matrix, meters
- Keyboard-driven navigation

#### GUI (`src/gui/`)
- Graphical interface using raylib
- Drag-and-drop routing
- Visual faders and meters
- Mouse and keyboard input

#### CLI Launcher (`src/cli/`)
- Command-line entry point
- Process management
- Argument parsing

## Data Flow

### Audio Data Flow

1. **Capture**: Apps produce audio → Platform captures per-app audio
2. **Buffer**: Audio written to per-app ring buffers
3. **Route**: Ring buffers associated with channels via routing
4. **Mix**: Audio thread reads from ring buffers, mixes per channel
5. **Process**: Apply volume/mute/solo, update meters
6. **Output**: Mixed audio sent to output device

### Control Flow

1. **User Input**: User interacts with TUI/GUI
2. **Command**: Frontend sends command via IPC
3. **Process**: Daemon receives and validates command
4. **Execute**: Daemon modifies mixer state
5. **Update**: Shared state updated
6. **Refresh**: Frontend reads new state and updates display

## Threading Model

### Daemon Threads

1. **Main Thread**
   - IPC server processing
   - Command handling
   - State updates

2. **Audio Thread** (real-time priority)
   - Audio processing callback
   - Mixing operations
   - Meter updates
   - **Constraints**: No locks, no allocations, no syscalls

3. **Capture Threads** (per platform, optional)
   - Per-app audio capture
   - Write to ring buffers

### Synchronization

- **Audio Thread**: Lock-free ring buffers for audio data
- **State Updates**: Atomic operations where possible, short-lived locks for complex updates
- **Shared State**: Mutex-protected for IPC reads/writes

## Memory Management

### Allocation Strategy

- **Initialization**: Allocate all buffers upfront
- **Runtime**: No allocations in audio thread
- **Ring Buffers**: Pre-allocated, fixed size
- **Channels**: Pre-allocated array (MAX_CHANNELS)
- **Apps**: Pre-allocated array (MAX_APPS)

### Buffer Sizes

- Audio buffer: 512 frames default (adjustable)
- Ring buffers: 4096 frames per app
- IPC buffers: 1024 bytes per message

## Platform-Specific Details

### macOS (CoreAudio)

- Uses Audio Units for output
- Audio Server API for per-app capture (requires entitlements)
- BlackHole virtual device for routing apps
- IOProc callback for audio processing

### Windows (WASAPI)

- Uses IAudioClient for output
- Audio Session API for per-app enumeration
- Loopback capture for per-app audio
- Shared-mode or exclusive-mode output
- Event-driven or polling for audio callback

## Error Handling

- All public APIs return error codes
- Audio thread: fail-safe, zero output on error
- IPC: graceful degradation on connection loss
- Platform layer: fallback to default device on error

## Performance Considerations

### Latency

- Target latency: 10-20ms total (system + processing)
- Buffer size configurable: 128-1024 frames
- Processing overhead: < 1ms per mix cycle

### CPU Usage

- Audio thread: < 5% on modern CPU
- IPC overhead: < 1% when idle
- Frontend: depends on UI complexity

### Scalability

- Max 16 channels (configurable)
- Max 64 apps (configurable)
- Max 32 apps per channel

## Future Enhancements

1. **Plugin System**: VST/AU effects per channel
2. **Recording**: Record individual channels or master output
3. **Network Sync**: Control mixer from remote devices
4. **Presets**: Save/load routing configurations
5. **Automation**: Scheduled volume changes
6. **JACK Support**: Linux support via JACK audio server

## Building and Testing

See main README.md for build instructions.

### Testing Strategy

- Unit tests for core mixer logic
- Integration tests for IPC
- Platform-specific tests for audio backends
- UI tests for frontends (manual for now)

## References

- [Core Audio Programming Guide](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview/)
- [WASAPI Documentation](https://docs.microsoft.com/en-us/windows/win32/coreaudio/wasapi)
- [notcurses Documentation](https://notcurses.com/)
- [raylib Documentation](https://www.raylib.com/)
