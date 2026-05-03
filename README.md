# TUI File Explorer for Linux

**Terminal file manager with live text & ZIP previews**

[![Linux](https://img.shields.io/badge/Linux-amd64-brightgreen?logo=linux&logoColor=white)](https://github.com/jesusalbertodeveloper/tuifileexplorerapp)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Stars](https://img.shields.io/github/stars/jesusalbertodeveloper/tuifileexplorerapp?style=social)](https://github.com/jesusalbertodeveloper/tuifileexplorerapp)

A lightweight **TUI file explorer for Linux** built in C++. Navigate, manage files, and **preview text/ZIP contents instantly** in the bottom panel – just highlight to see!

## ✨ Key Features
- **Live previews**: Text files & ZIP contents display without opening
- **Dual-pane UI**: Left pane for storage devices/partitions, right for files/folders
- **Full file operations**: Copy, move, delete, rename, create folders
- **Nano editor integration**: Press Enter to edit → Ctrl+X returns (save prompt)
- **Arrow key navigation**: Smooth terminal controls
- **Prebuilt binary**: AMD64 Linux (Intel/AMD) – tested on Linux Mint 21.3 Cinnamon

Perfect **Linux terminal file manager** alternative to ranger/nnn with unique ZIP preview.

## 🚀 Quick Install & Run
```bash
# Download prebuilt binary
wget https://github.com/jesusalbertodeveloper/tuifileexplorer/releases/latest/download/tuifileexplorer_amd64
chmod +x tuifileexplorer_amd64
./tuifileexplorer_amd64
```

**Build from source** (C++):
```bash
cd sourcecode
make  # Or your build command
```

## 📱 Controls & Usage
- **← → Arrow keys**: Switch panes (left: devices, right: files)
- **↑ ↓**: Navigate files/folders
- **Enter**: Open/edit text in nano
- **Highlight**: Auto-preview text/ZIP in bottom box
- **File ops**: Use menu/hotkeys (copy/move/delete/rename/mkdir)
## 🤝 Contributing
1. Fork & clone
2. Create feature branch
3. Submit a pull request to `main`

Issues welcome!

## 📝 License
[MIT License](LICENSE)

## 🐧 Built On
**Developed and tested on Linux Mint 21.3 Cinnamon**  
Works on Ubuntu, Debian derivatives, and most AMD64 Linux distributions.

**Made with ❤️ on Linux Mint 21.3 | Stars/forks boost visibility!**
