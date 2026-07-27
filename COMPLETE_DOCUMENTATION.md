# Elyamany Linux - Complete Project Documentation

## 📋 Table of Contents
1. [Overview](#overview)
2. [Architecture](#architecture)
3. [Building](#building)
4. [Running](#running)
5. [Project Structure](#project-structure)
6. [Modules](#modules)
7. [Contributing](#contributing)

---

## 🎯 Overview

**Elyamany Linux** is a complete, bootable operating system built from scratch. It includes:

- ✅ Custom Bootloader (GRUB-compatible)
- ✅ Complete Kernel (32-bit x86)
- ✅ Memory Management (Paging, Heap)
- ✅ Process & Thread Management
- ✅ CPU Scheduling (Round Robin)
- ✅ Interrupt & Exception Handling
- ✅ Device Drivers (Keyboard, Mouse, Display, Network)
- ✅ Virtual File System (VFS)
- ✅ File System Support (EXT4, FAT32, NTFS)
- ✅ Standard C Library
- ✅ System Services
- ✅ User Management & Security
- ✅ Package Manager
- ✅ ISO Builder
- ✅ QEMU Support

**Version:** 1.0.0  
**Target Architecture:** x86 (32-bit)  
**Minimum RAM:** 512 MB

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│     User Applications                   │
├─────────────────────────────────────────┤
│     System Services & Libraries         │
├─────────────────────────────────────────┤
│     File System (VFS)                   │
├─────────────────────────────────────────┤
│     Device Drivers                      │
├─────────────────────────────────────────┤
│     Process & Memory Management         │
├─────────────────────────────────────────┤
│     Kernel Core                         │
├─────────────────────────────────────────┤
│     Bootloader & Hardware               │
└─────────────────────────────────────────┘
```

---

## 🔨 Building

### Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install build-essential nasm grub-pc xorriso qemu

# macOS (Homebrew)
brew install nasm qemu
```

### Cross-Compiler Setup

You need `i686-elf-gcc` and `i686-elf-ld`:

```bash
# Run setup script
bash tools/setup_dev_env.sh
```

### Build the OS

```bash
# Simple build
make build

# Or using build script
bash build.sh
```

**Output:** `build/elyamany-linux-1.0.0.iso` (~50 MB)

---

## 🚀 Running

### QEMU Emulation

```bash
# Run in QEMU
make run

# Or directly
qemu-system-i386 -cdrom build/elyamany-linux-1.0.0.iso -m 512M
```

### Debugging

```bash
# Run with GDB
make debug

# Manually
qemu-system-i386 -cdrom build/elyamany-linux-1.0.0.iso -m 512M -s -S
i686-elf-gdb build/kernel/kernel.elf -ex "target remote localhost:1234"
```

### Real Hardware

```bash
# Write ISO to USB
sudo dd if=build/elyamany-linux-1.0.0.iso of=/dev/sdX bs=4M
sync

# Boot from USB
```

---

## 📁 Project Structure

```
custom-os/
├── bootloader/
│   ├── boot.asm              # x86 bootloader
│   ├── grub/                 # GRUB configuration
│   └── efi/                  # EFI support (future)
│
├── kernel/
│   ├── elyamany_kernel.h     # Main kernel header
│   ├── kernel_main.c         # Kernel entry point
│   ├── memory_manager.c      # Paging & heap
│   ├── interrupt_handler.c   # IDT & IRQ handling
│   ├── timer.c               # System timer
│   ├── panic.c               # Panic handling
│   ├── linker.ld             # Linker script
│   └── grub.cfg              # GRUB config
│
├── drivers/
│   ├── keyboard.c/.h         # Keyboard input
│   ├── mouse.c/.h            # Mouse input
│   ├── display.c/.h          # Graphics/Framebuffer
│   ├── audio.h               # Audio (stub)
│   ├── network.h             # Network
│   ├── usb.h                 # USB (stub)
│   └── storage.h             # Storage
│
├── fs/
│   ├── vfs.c/.h              # Virtual File System
│   ├── ext4.h                # EXT4 support
│   ├── fat32.h               # FAT32 support
│   └── ntfs.h                # NTFS support
│
├── mm/
│   ├── memory.h              # Memory management
│   ├── heap/                 # Heap allocator
│   ├── paging/               # Paging system
│   └── virtual_memory/       # Virtual memory
│
├── process/
│   ├── process_manager.h     # Process management
│   ├── scheduler.h           # CPU scheduler
│   └── thread/               # Threading
│
├── services/
│   ├── user_manager.c/.h     # User management
│   ├── package_manager.c/.h  # Package management
│   ├── security.h            # Security/permissions
│   ├── power_manager.h       # Power states
│   └── network_manager.h     # Network management
│
├── libc/
│   ├── stdlib.h              # Standard library
│   ├── string.h              # String functions
│   ├── stdio.h               # I/O functions
│   └── math.h                # Math functions
│
├── userland/
│   ├── shell.sh              # Command shell
│   ├── init.sh               # System init
│   └── (applications)
│
├── gui/
│   ├── display_server/       # Display server
│   ├── window_manager/       # Window manager
│   └── theme/                # Theme engine
│
├── tools/
│   ├── build.sh              # Build script
│   ├── iso_builder.sh        # ISO creation
│   ├── setup_dev_env.sh      # Development setup
│   ├── generate_docs.sh      # Doc generator
│   └── cross_compiler/       # Cross-compiler
│
├── docs/
│   ├── api/                  # API documentation
│   ├── guides/               # User guides
│   └── design/               # Design docs
│
├── Makefile                  # Main build system
├── build.sh                  # Build script
├── README.md                 # This file
├── PHASE_1.md                # Phase 1 documentation
└── .gitignore
```

---

## 📦 Core Modules

### 1. Memory Management
- Virtual memory with paging
- Heap allocator
- Page fault handling
- Swap support

### 2. Process Management
- Process creation/destruction
- Thread support
- Context switching
- Process states

### 3. Scheduling
- Round-robin scheduling
- Priority-based scheduling
- CPU affinity
- Load balancing

### 4. File System
- VFS abstraction layer
- EXT4 support
- FAT32 support
- NTFS support

### 5. Device Drivers
- Keyboard input
- Mouse input
- Graphics/Framebuffer
- Network interface
- USB support
- Storage devices

### 6. Security
- User authentication
- File permissions
- Password hashing
- Encryption support

### 7. System Services
- User manager
- Package manager
- Power management
- Network management

---

## 🛠️ Development

### Adding a New Driver

1. Create `drivers/mydriver.h` and `drivers/mydriver.c`
2. Implement `init_mydriver()` function
3. Add to `kernel/kernel_main.c` initialization
4. Update `Makefile`

### Adding a System Call

1. Add definition to `kernel/syscall_interface.h`
2. Implement handler in `kernel/syscall.c`
3. Register in syscall dispatcher

### Building Documentation

```bash
bash tools/generate_docs.sh
```

---

## 🤝 Contributing

Contributions welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Submit a pull request
4. Follow the code style

---

## 📝 License

MIT License - See LICENSE file

---

## 👥 Authors

**gghj84448-creator** - Project Lead

---

## 🔗 Resources

- [OSDev Wiki](https://wiki.osdev.org)
- [Intel x86 Architecture](https://www.intel.com/)
- [Linux Kernel Documentation](https://www.kernel.org/doc/)
- [POSIX Standard](https://pubs.opengroup.org/onlinepubs/9699919799/)

---

## 📞 Support

For issues and questions:
- Open a GitHub issue
- Check existing documentation
- Review OSDev resources

---

**Last Updated:** July 27, 2026  
**Status:** Active Development
