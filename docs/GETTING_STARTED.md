# Getting Started with Custom OS

## Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential nasm grub-pc xorriso qemu-system-x86 gcc-i686-linux-gnu

# Alternative: Cross-compiler for i686-elf
sudo apt-get install i386-elf-binutils i386-elf-gcc
```

### macOS
```bash
brew install nasm qemu binutils i686-elf-gcc
```

### Windows (WSL2)
```bash
# Inside WSL2 Ubuntu terminal
sudo apt-get update
sudo apt-get install build-essential nasm grub-pc xorriso qemu-system-x86
```

## Building

```bash
# Clone the repository
git clone https://github.com/gghj84448-creator/custom-os.git
cd custom-os

# Build the kernel
make

# Run in QEMU
make run
```

## Project Structure

```
custom-os/
├── bootloader/       # Bootloader files (Assembly)
├── kernel/           # Kernel core (C)
├── arch/             # Architecture-specific (x86_64)
├── drivers/          # Device drivers
├── fs/               # File system
├── mm/               # Memory management
├── libc/             # C library
├── shell/            # Command shell
├── gui/              # GUI framework
├── tools/            # Build tools
├── docs/             # Documentation
└── Makefile          # Build configuration
```

## Current Status

✅ Phase 1 - Basic Bootloader
- [x] Multiboot header
- [x] Basic kernel initialization
- [x] Text mode output
- [ ] Interrupt handling setup

## Next Steps

1. **Interrupt Descriptor Table (IDT)**
2. **Global Descriptor Table (GDT)**
3. **Interrupt handlers**
4. **Memory paging**
5. **Process scheduling**

## Testing

### Run in QEMU
```bash
make run
```

### Debug with GDB
```bash
make debug
```

## Contributing

Fork, create a branch, and submit a pull request.

## License

MIT License
