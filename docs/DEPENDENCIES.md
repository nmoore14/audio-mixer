# Dependencies

This document lists all dependencies required to build and run the Audio Mixer application.

## Build Tools

### Required

| Tool | Minimum Version | Purpose |
|------|----------------|---------|
| CMake | 3.15 | Build system generator |
| C Compiler | C11 support | Compile source code |
| Make or Ninja | Latest | Build execution |

### Compilers

**macOS:**
- Clang (Xcode Command Line Tools)
  ```bash
  xcode-select --install
  ```

**Windows:**
- MSVC (Visual Studio 2019+) or
- MinGW-w64 or
- Clang

## Runtime Libraries

### Core Dependencies

| Library | Version | Platform | Purpose |
|---------|---------|----------|---------|
| pthread | System | All | Threading support |
| C Standard Library | C11 | All | Core C functions |

### macOS-Specific

| Framework/Library | Version | Purpose | Installation |
|-------------------|---------|---------|--------------|
| CoreAudio | System | Audio I/O | Included with macOS |
| AudioUnit | System | Audio processing | Included with macOS |
| CoreFoundation | System | System utilities | Included with macOS |
| BlackHole | 2ch or 16ch | Virtual audio device | `brew install blackhole-2ch` |

**BlackHole Installation:**
```bash
# Install via Homebrew
brew install blackhole-2ch

# Or download from:
# https://github.com/ExistentialAudio/BlackHole
```

**Note:** BlackHole provides a virtual audio device that allows routing audio from applications. After installation, configure applications to output to BlackHole in System Preferences → Sound.

### Windows-Specific

| Library | Version | Purpose | Installation |
|---------|---------|---------|--------------|
| Windows SDK | 10+ | WASAPI APIs | Included with Visual Studio |
| ole32.lib | System | COM support | Included with Windows SDK |
| oleaut32.lib | System | COM automation | Included with Windows SDK |
| winmm.lib | System | Multimedia functions | Included with Windows SDK |
| ksuser.lib | System | Kernel streaming | Included with Windows SDK |
| VB-Audio Cable | Latest | Virtual audio device | See below |

**VB-Audio Cable Installation:**
1. Download from: https://vb-audio.com/Cable/
2. Extract and run setup as Administrator
3. Restart computer
4. Configure applications to output to CABLE Input

**Alternative:** VoiceMeeter (more features, but heavier)
- Download from: https://vb-audio.com/Voicemeeter/

## UI Dependencies

### TUI (Terminal User Interface)

| Library | Version | Platform | Purpose | Installation |
|---------|---------|----------|---------|--------------|
| notcurses | 3.0+ | All | Terminal UI | See below |

**macOS:**
```bash
brew install notcurses
```

**Windows:**
```powershell
# Using vcpkg
vcpkg install notcurses

# Or using MSYS2
pacman -S mingw-w64-x86_64-notcurses
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt install libnotcurses-dev
```

**From Source:**
```bash
git clone https://github.com/dankamongmen/notcurses.git
cd notcurses
mkdir build && cd build
cmake ..
make
sudo make install
```

### GUI (Graphical User Interface)

| Library | Version | Platform | Purpose | Installation |
|---------|---------|----------|---------|--------------|
| raylib | 4.0+ | All | Graphics/UI | See below |

**macOS:**
```bash
brew install raylib
```

**Windows:**
```powershell
# Using vcpkg
vcpkg install raylib

# Or download pre-built from:
# https://github.com/raysan5/raylib/releases
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt install libraylib-dev
```

**From Source:**
```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake ..
make
sudo make install
```

## Optional Dependencies

### Development Tools

| Tool | Purpose | Installation |
|------|---------|--------------|
| Git | Version control | System package manager |
| GDB/LLDB | Debugging | `brew install lldb` (macOS) |
| Valgrind | Memory debugging | `brew install valgrind` (macOS) |
| clang-format | Code formatting | `brew install clang-format` |

### Documentation

| Tool | Purpose | Installation |
|------|---------|--------------|
| Doxygen | API documentation | `brew install doxygen` |
| Graphviz | Diagram generation | `brew install graphviz` |

## Dependency Summary by Component

### Daemon (`audio-mixer-daemon`)
- pthread (threading)
- Platform audio frameworks (CoreAudio/WASAPI)
- Virtual audio device (BlackHole/VB-Cable)

### TUI (`audio-mixer-tui`)
- pthread (threading)
- notcurses (UI)
- IPC libraries (sockets/pipes)

### GUI (`audio-mixer-gui`)
- pthread (threading)
- raylib (graphics)
- IPC libraries (sockets/pipes)
- Platform frameworks (Cocoa on macOS, Win32 on Windows)

### Launcher (`audio-mixer`)
- C standard library only

## Version Compatibility

### Minimum Tested Versions

- **macOS**: 10.15 Catalina
- **Windows**: Windows 10 version 1903
- **CMake**: 3.15
- **notcurses**: 3.0.0
- **raylib**: 4.0.0

### Recommended Versions

- **macOS**: 11.0 Big Sur or later
- **Windows**: Windows 10 version 21H2 or Windows 11
- **CMake**: 3.20+
- **notcurses**: 3.0.9+
- **raylib**: 4.5.0+

## Known Issues

### macOS

1. **BlackHole Permission Issues**
   - Some apps may require enabling in System Preferences → Security & Privacy
   - Restart app after installing BlackHole

2. **CoreAudio Entitlements**
   - Per-app capture may require specific entitlements
   - May need to disable SIP for development

### Windows

1. **WASAPI Exclusive Mode**
   - Some audio devices don't support exclusive mode
   - Fall back to shared mode if needed

2. **VB-Cable Latency**
   - Default buffer size may be too large
   - Configure in VB-Audio Control Panel

### Cross-Platform

1. **notcurses Terminal Compatibility**
   - Works best with modern terminals (iTerm2, Windows Terminal)
   - May have issues with older terminals

2. **raylib OpenGL Requirements**
   - Requires OpenGL 3.3+ or OpenGL ES 2.0+
   - May need graphics driver updates

## Troubleshooting

### Missing Dependencies

**macOS:**
```bash
# Check installed packages
brew list

# Update packages
brew update
brew upgrade
```

**Windows:**
```powershell
# Check vcpkg packages
vcpkg list

# Update vcpkg
cd <vcpkg-root>
git pull
.\bootstrap-vcpkg.bat
```

### Link Errors

If you encounter link errors:

1. Check that all frameworks are found:
   ```bash
   cmake .. -DCMAKE_VERBOSE_MAKEFILE=ON
   ```

2. Verify library paths:
   ```bash
   # macOS
   otool -L build/audio-mixer-daemon

   # Windows
   dumpbin /dependents build/Release/audio-mixer-daemon.exe
   ```

### Runtime Issues

1. **"Library not found" errors**
   - macOS: Check `DYLD_LIBRARY_PATH`
   - Windows: Check PATH includes library directories

2. **Audio device not found**
   - Verify virtual audio device is installed
   - Check system audio settings
   - Restart audio service

## Building Without Optional Dependencies

The build system will detect missing optional dependencies and build without them:

- **Without notcurses**: TUI will be built but show a warning
- **Without raylib**: GUI will be built but show a warning

To force building without optional dependencies:
```bash
cmake .. -DSKIP_TUI=ON -DSKIP_GUI=ON
```

## Updating Dependencies

### Recommended Update Schedule

- **Security updates**: Immediately
- **Minor versions**: Monthly
- **Major versions**: Test thoroughly before upgrading

### Update Commands

**macOS:**
```bash
brew update
brew upgrade
```

**Windows (vcpkg):**
```powershell
cd <vcpkg-root>
git pull
.\vcpkg.exe upgrade --no-dry-run
```

## License Information

- **CoreAudio**: Apple frameworks (system)
- **WASAPI**: Microsoft SDK (system)
- **notcurses**: Apache 2.0
- **raylib**: zlib/libpng
- **BlackHole**: GPL 3.0
- **VB-Audio Cable**: Freeware (check EULA for redistribution)

Always verify license compatibility with your project before distribution.
