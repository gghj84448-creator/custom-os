#!/bin/bash
# Elyamany Linux - Complete System Structure Builder

echo "================================"
echo "Elyamany Linux - System Setup"
echo "================================"

# Core directories structure
mkdir -p elyamany-os/{bootloader,kernel,drivers,mm,process,fs,services,gui,libc,tools,iso}

# 1. BOOTLOADER
mkdir -p elyamany-os/bootloader/{grub,efi,legacy}

# 2. KERNEL CORE
mkdir -p elyamany-os/kernel/{arch,interrupts,syscall,panic}

# 3. MEMORY MANAGEMENT
mkdir -p elyamany-os/mm/{heap,paging,virtual_memory,swap}

# 4. PROCESS & SCHEDULING
mkdir -p elyamany-os/process/{scheduler,thread,context_switch}

# 5. DRIVERS
mkdir -p elyamany-os/drivers/{keyboard,mouse,gpu,audio,network,usb,storage,wifi,bluetooth,display}

# 6. FILE SYSTEM
mkdir -p elyamany-os/fs/{vfs,ext4,fat32,ntfs}

# 7. INTERRUPT & TIMER
mkdir -p elyamany-os/kernel/{interrupt,timer,ipc}

# 8. SYSCALLS
mkdir -p elyamany-os/kernel/syscall

# 9. LIBC - Standard C Library
mkdir -p elyamany-os/libc/{stdlib,string,stdio,math,sys}

# 10. SERVICES
mkdir -p elyamany-os/services/{power,network,audio,bluetooth,security,user_manager}

# 11. USERLAND TOOLS
mkdir -p elyamany-os/userland/{shell,init,package_manager,installer}

# 12. GUI
mkdir -p elyamany-os/gui/{display_server,window_manager,theme}

# 13. BUILD TOOLS
mkdir -p elyamany-os/tools/{iso_builder,cross_compiler}

echo "✅ Directory structure created successfully!"
echo "📁 Location: elyamany-os/"
