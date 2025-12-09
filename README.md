# Audio Mixer

A cross-platform audio routing and mixing application for macOS and Windows. Route audio from different applications to separate channels and mix them with individual volume control.

## Features

- Per-application audio capture and routing
- Multiple mixing channels with individual controls
- Volume, mute, and solo controls per channel
- Real-time peak meters
- Terminal UI (TUI) using notcurses
- Graphical UI (GUI) using raylib
- Daemon architecture with IPC for multiple frontends
- Low-latency audio processing

## System Architecture

The application consists of three main components:

1. **Daemon** (`audio-mixer-daemon`): Background service that handles audio capture, mixing, and routing
2. **TUI** (`audio-mixer-tui`): Terminal-based interface for controlling the mixer
3. **GUI** (`audio-mixer-gui`): Graphical interface for controlling the mixer

The daemon runs independently and communicates with frontends via IPC (Inter-Process Communication).

## Prerequisites

### macOS

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake
brew install notcurses
brew install raylib

# Install BlackHole virtual audio device for app capture
brew install blackhole-2ch
```

### Windows

```powershell
# Install dependencies (using vcpkg)
vcpkg install notcurses
vcpkg install raylib

# Install VB-Audio Virtual Cable for app capture
# Download from: https://vb-audio.com/Cable/
```

### Build Tools

- CMake 3.15 or higher
- C11 compatible compiler (GCC, Clang, MSVC)
- Git (for version control)

## Building

### macOS

```bash
# Clone the repository
git clone <repository-url>
cd audio-mixer

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build
make -j$(sysctl -n hw.ncpu)

# Install (optional)
sudo make install
```

### Windows

```powershell
# Create build directory
mkdir build
cd build

# Configure with CMake (using Visual Studio)
cmake .. -G "Visual Studio 17 2022"

# Build
cmake --build . --config Release

# Install (optional)
cmake --install . --config Release
```

## Usage

### Starting the Daemon

```bash
# Start daemon in background
audio-mixer --daemon
```

### Using the TUI

```bash
# Launch terminal interface
audio-mixer --tui
```

**TUI Controls:**
- Arrow keys: Navigate channels/apps
- `+`/`-`: Adjust volume
- `M`: Toggle mute
- `S`: Toggle solo
- `Tab`: Switch between views
- `Q`: Quit

### Using the GUI

```bash
# Launch graphical interface
audio-mixer --gui
```

**GUI Controls:**
- Drag and drop apps between channels
- Click faders to adjust volume
- Click M/S buttons to mute/solo channels
- Right-click for context menu

### Other Commands

```bash
# Check daemon status
audio-mixer --status

# Stop daemon
audio-mixer --stop

# Show help
audio-mixer --help

# Show version
audio-mixer --version
```

## Configuration

Configuration files are stored in:
- macOS: `~/Library/Application Support/AudioMixer/`
- Windows: `%APPDATA%\AudioMixer\`

## Development

See [ARCHITECTURE.md](docs/ARCHITECTURE.md) for detailed architecture documentation.

See [DEPENDENCIES.md](docs/DEPENDENCIES.md) for complete dependency information.

## Known Limitations

- Per-app audio capture requires virtual audio devices on both platforms
- Some applications may not be capturable depending on their audio implementation
- Latency depends on buffer size and system audio configuration

## Troubleshooting

### macOS

**Problem:** Daemon won't start
- Check if BlackHole is installed: `ls /Library/Audio/Plug-Ins/HAL/`
- Check Console.app for error messages

**Problem:** No apps detected
- Verify apps are playing audio
- Check Audio MIDI Setup for BlackHole device

### Windows

**Problem:** Daemon won't start
- Check if VB-Audio Cable is installed
- Run as Administrator if needed

**Problem:** No apps detected
- Verify apps are playing audio
- Check Windows Sound Settings

## License

[Your license here]

## Contributing

[Contributing guidelines here]
