# Build Instructions for Elyamany Linux

## Quick Start

### 1. Install Dependencies

**Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install -y build-essential nasm grub-pc xorriso qemu-system-x86 git
```

**macOS:**
```bash
brew install nasm qemu
# For grub-mkrescue, use Linux in VM or WSL
```

**Windows (WSL2):**
```bash
# Inside WSL2 Ubuntu terminal
sudo apt-get install build-essential nasm grub-pc xorriso qemu-system-x86
```

### 2. Setup Cross-Compiler

```bash
# Make sure you have i686-elf-gcc
# If not available, install it:

bash tools/setup_dev_env.sh
```

### 3. Build

```bash
# Simple build
make build

# Or with build script
bash build.sh

# Output: build/elyamany-linux-1.0.0.iso
```

### 4. Run

```bash
# Run in QEMU
make run

# Or manually
qemu-system-i386 -cdrom build/elyamany-linux-1.0.0.iso -m 512M -boot d
```

### 5. Debug

```bash
# Launch with GDB
make debug

# In another terminal:
i686-elf-gdb build/kernel/kernel.elf -ex "target remote localhost:1234"
```

## Detailed Steps

### Step 1: Verify Cross-Compiler

```bash
i686-elf-gcc --version
i686-elf-ld --version
nasm -version
```

If commands not found, install or add to PATH.

### Step 2: Create Build Directory

```bash
mkdir -p build/{bootloader,kernel,drivers,fs,services}
```

### Step 3: Compile Each Component

```bash
# Bootloader
nasm -f elf32 -o build/bootloader/boot.o bootloader/boot.asm

# Kernel core
i686-elf-gcc -ffreestanding -O2 -c kernel/memory_manager.c -o build/kernel/memory_manager.o
i686-elf-gcc -ffreestanding -O2 -c kernel/interrupt_handler.c -o build/kernel/interrupt_handler.o
i686-elf-gcc -ffreestanding -O2 -c kernel/timer.c -o build/kernel/timer.o
i686-elf-gcc -ffreestanding -O2 -c kernel/panic.c -o build/kernel/panic.o
i686-elf-gcc -ffreestanding -O2 -c kernel/kernel_main.c -o build/kernel/kernel_main.o

# Drivers
i686-elf-gcc -ffreestanding -O2 -c drivers/keyboard.c -o build/drivers/keyboard.o
i686-elf-gcc -ffreestanding -O2 -c drivers/display.c -o build/drivers/display.o

# File system
i686-elf-gcc -ffreestanding -O2 -c fs/vfs.c -o build/fs/vfs.o

# Services
i686-elf-gcc -ffreestanding -O2 -c services/user_manager.c -o build/services/user_manager.o
i686-elf-gcc -ffreestanding -O2 -c services/package_manager.c -o build/services/package_manager.o
```

### Step 4: Link Kernel

```bash
i686-elf-ld -T kernel/linker.ld -o build/kernel/kernel.elf \
    build/bootloader/boot.o \
    build/kernel/memory_manager.o \
    build/kernel/interrupt_handler.o \
    build/kernel/timer.o \
    build/kernel/panic.o \
    build/kernel/kernel_main.o \
    build/drivers/keyboard.o \
    build/drivers/display.o \
    build/fs/vfs.o \
    build/services/user_manager.o \
    build/services/package_manager.o
```

### Step 5: Create ISO

```bash
mkdir -p build/iso/boot/grub
cp build/kernel/kernel.elf build/iso/boot/
cp kernel/grub.cfg build/iso/boot/grub/
grub-mkrescue -o build/elyamany-linux-1.0.0.iso build/iso/
```

### Step 6: Test

```bash
qemu-system-i386 -cdrom build/elyamany-linux-1.0.0.iso -m 512M
```

## Troubleshooting

### Issue: i686-elf-gcc not found

**Solution:**
```bash
# Install from binary
wget https://github.com/osdev/osdev-tools/releases/download/v1.0/i686-elf-gcc.tar.gz
tar -xzf i686-elf-gcc.tar.gz
export PATH=$PATH:$(pwd)/i686-elf/bin
```

### Issue: grub-mkrescue not found

**Solution:**
```bash
# Use xorriso instead
xorriso -as mkisofs -R -J -o build/elyamany-linux-1.0.0.iso build/iso/
```

### Issue: QEMU not found

**Solution:**
```bash
# Ubuntu/Debian
sudo apt-get install qemu-system-x86

# macOS
brew install qemu
```

### Issue: Permission denied on scripts

**Solution:**
```bash
chmod +x build.sh setup_dev_env.sh iso_builder.sh
```

## Advanced Build Options

### Build with Debugging Symbols

```bash
CFLAGS="-g -O0" make build
```

### Build with Optimization

```bash
CFLAGS="-O3" make build
```

### Build Specific Component

```bash
make build/kernel/kernel.elf
```

## Verification

After building, verify:

```bash
# Check ISO exists
ls -lh build/elyamany-linux-1.0.0.iso

# Check ISO contents
grub-mount -v build/elyamany-linux-1.0.0.iso mnt/
ls -la mnt/
```

## Additional Resources

- [OSDev Build Scripts](https://wiki.osdev.org/Bare_Bones)
- [GNU Toolchain](https://www.gnu.org/software/gnu-linux-gnu/)
- [GRUB Manual](https://www.gnu.org/software/grub/manual/)
- [NASM Manual](https://www.nasm.us/)

---

**Questions?** Check GitHub Issues or Documentation
