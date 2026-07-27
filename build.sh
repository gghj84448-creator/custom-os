#!/bin/bash
# Elyamany Linux - Complete Build System

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Configuration
PROJECT_NAME="Elyamany Linux"
VERSION="1.0.0"
ARCH="i686"
CROSS_COMPILER="i686-elf"
BUILD_DIR="build"
ISO_DIR="${BUILD_DIR}/iso"
ISO_FILE="${BUILD_DIR}/elyamany-linux-${VERSION}.iso"

echo -e "${GREEN}================================${NC}"
echo -e "${GREEN}$PROJECT_NAME - Build System${NC}"
echo -e "${GREEN}Version: $VERSION${NC}"
echo -e "${GREEN}================================${NC}"
echo ""

# Check dependencies
check_dependencies() {
    echo -e "${YELLOW}[*] Checking dependencies...${NC}"
    
    local missing=0
    
    for cmd in ${CROSS_COMPILER}-gcc ${CROSS_COMPILER}-ld nasm grub-mkrescue xorriso; do
        if ! command -v $cmd &> /dev/null; then
            echo -e "${RED}    [ERROR] $cmd not found${NC}"
            missing=1
        else
            echo -e "${GREEN}    [OK] $cmd found${NC}"
        fi
    done
    
    if [ $missing -eq 1 ]; then
        echo -e "${RED}[ERROR] Missing required dependencies${NC}"
        exit 1
    fi
    
    echo -e "${GREEN}[OK] All dependencies found${NC}"
    echo ""
}

# Create build directory structure
make_build_structure() {
    echo -e "${YELLOW}[*] Creating build structure...${NC}"
    
    mkdir -p ${BUILD_DIR}/{kernel,bootloader,drivers,fs,services,libc}
    mkdir -p ${ISO_DIR}/{boot/grub,lib,usr/{bin,lib},etc,home}
    
    echo -e "${GREEN}[OK] Build structure created${NC}"
    echo ""
}

# Compile bootloader
compile_bootloader() {
    echo -e "${YELLOW}[*] Compiling bootloader...${NC}"
    
    nasm -f elf32 -o ${BUILD_DIR}/bootloader/boot.o bootloader/boot.asm
    
    echo -e "${GREEN}[OK] Bootloader compiled${NC}"
    echo ""
}

# Compile kernel
compile_kernel() {
    echo -e "${YELLOW}[*] Compiling kernel...${NC}"
    
    # Compile kernel sources
    ${CROSS_COMPILER}-gcc -std=c11 -Wall -Wextra -Werror \
        -ffreestanding -O2 -fno-builtin \
        -Ikernel -Idrivers -Ifs -Iservices -Ilibc \
        -c kernel/elyamany_kernel.h -o ${BUILD_DIR}/kernel/kernel.o
    
    # Compile memory manager
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        kernel/memory_manager.c -o ${BUILD_DIR}/kernel/memory_manager.o
    
    # Compile VFS
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        fs/vfs.c -o ${BUILD_DIR}/fs/vfs.o
    
    # Compile User Manager
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        services/user_manager.c -o ${BUILD_DIR}/services/user_manager.o
    
    # Compile Package Manager
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        services/package_manager.c -o ${BUILD_DIR}/services/package_manager.o
    
    # Compile Drivers
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        drivers/keyboard.c -o ${BUILD_DIR}/drivers/keyboard.o
    
    ${CROSS_COMPILER}-gcc -ffreestanding -O2 -c \
        drivers/display.c -o ${BUILD_DIR}/drivers/display.o
    
    echo -e "${GREEN}[OK] Kernel compiled${NC}"
    echo ""
}

# Link kernel
link_kernel() {
    echo -e "${YELLOW}[*] Linking kernel...${NC}"
    
    ${CROSS_COMPILER}-ld -T kernel/linker.ld -o ${BUILD_DIR}/kernel/kernel.elf \
        ${BUILD_DIR}/bootloader/boot.o \
        ${BUILD_DIR}/kernel/memory_manager.o \
        ${BUILD_DIR}/fs/vfs.o \
        ${BUILD_DIR}/services/user_manager.o \
        ${BUILD_DIR}/services/package_manager.o \
        ${BUILD_DIR}/drivers/keyboard.o \
        ${BUILD_DIR}/drivers/display.o
    
    echo -e "${GREEN}[OK] Kernel linked${NC}"
    echo ""
}

# Create ISO image
create_iso() {
    echo -e "${YELLOW}[*] Creating ISO image...${NC}"
    
    # Copy kernel to ISO
    cp ${BUILD_DIR}/kernel/kernel.elf ${ISO_DIR}/boot/
    
    # Copy GRUB configuration
    cp kernel/grub.cfg ${ISO_DIR}/boot/grub/
    
    # Copy system files
    cp userland/init.sh ${ISO_DIR}/
    cp userland/shell.sh ${ISO_DIR}/usr/bin/
    
    # Create ISO
    grub-mkrescue -o ${ISO_FILE} ${ISO_DIR} 2>/dev/null || \
    xorriso -as mkisofs -R -J -b boot/grub/i386-pc/eltorito.img \
        -no-emul-boot -boot-load-size 4 -boot-info-table \
        -o ${ISO_FILE} ${ISO_DIR}
    
    echo -e "${GREEN}[OK] ISO image created: ${ISO_FILE}${NC}"
    echo ""
}

# Build everything
build_all() {
    echo -e "${YELLOW}[*] Starting build process...${NC}"
    echo ""
    
    check_dependencies
    make_build_structure
    compile_bootloader
    compile_kernel
    link_kernel
    create_iso
    
    echo -e "${GREEN}================================${NC}"
    echo -e "${GREEN}Build completed successfully!${NC}"
    echo -e "${GREEN}ISO: ${ISO_FILE}${NC}"
    echo -e "${GREEN}Size: $(du -h ${ISO_FILE} | cut -f1)${NC}"
    echo -e "${GREEN}================================${NC}"
}

# Run in QEMU
run_qemu() {
    echo -e "${YELLOW}[*] Launching QEMU...${NC}"
    
    if [ ! -f ${ISO_FILE} ]; then
        echo -e "${RED}[ERROR] ISO file not found. Build first with: ./build.sh${NC}"
        exit 1
    fi
    
    qemu-system-i386 -cdrom ${ISO_FILE} -m 512M -boot d
}

# Debug mode
debug_mode() {
    echo -e "${YELLOW}[*] Launching QEMU with GDB...${NC}"
    
    qemu-system-i386 -cdrom ${ISO_FILE} -m 512M -boot d -s -S &
    sleep 1
    ${CROSS_COMPILER}-gdb ${BUILD_DIR}/kernel/kernel.elf \
        -ex "target remote localhost:1234" \
        -ex "break kernel_main" \
        -ex "continue"
}

# Clean build artifacts
clean() {
    echo -e "${YELLOW}[*] Cleaning build artifacts...${NC}"
    
    rm -rf ${BUILD_DIR}
    
    echo -e "${GREEN}[OK] Clean complete${NC}"
}

# Display help
show_help() {
    echo "Usage: ./build.sh [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  build       Build the OS (default)"
    echo "  run         Run in QEMU"
    echo "  debug       Run with GDB debugging"
    echo "  clean       Remove build artifacts"
    echo "  help        Show this help message"
    echo ""
}

# Main
case "${1:-build}" in
    build)
        build_all
        ;;
    run)
        if [ ! -f ${ISO_FILE} ]; then
            build_all
        fi
        run_qemu
        ;;
    debug)
        if [ ! -f ${ISO_FILE} ]; then
            build_all
        fi
        debug_mode
        ;;
    clean)
        clean
        ;;
    help)
        show_help
        ;;
    *)
        echo -e "${RED}Unknown command: $1${NC}"
        show_help
        exit 1
        ;;
esac
