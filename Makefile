# Elyamany Linux - Complete Makefile

.PHONY: all build run debug clean help install

# Toolchain
CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm
OBJCOPY = i686-elf-objcopy
QEMU = qemu-system-i386
GDB = i686-elf-gdb

# Directories
BUILD_DIR = build
ISO_DIR = $(BUILD_DIR)/iso
KERNEL_BUILD = $(BUILD_DIR)/kernel
BOOT_BUILD = $(BUILD_DIR)/bootloader
DRIVER_BUILD = $(BUILD_DIR)/drivers
FS_BUILD = $(BUILD_DIR)/fs
SERV_BUILD = $(BUILD_DIR)/services
LIBC_BUILD = $(BUILD_DIR)/libc

# Output files
KERNEL_ELF = $(KERNEL_BUILD)/kernel.elf
ISO_FILE = $(BUILD_DIR)/elyamany-linux-1.0.0.iso
BOOT_OBJ = $(BOOT_BUILD)/boot.o

# Flags
CFLAGS = -std=c11 -Wall -Wextra -Werror -ffreestanding -O2 -fno-builtin
LDFLAGS = -static -nostdlib
ASFLAGS = -f elf32

# Default target
all: build

# Create directories
$(BUILD_DIR) $(KERNEL_BUILD) $(BOOT_BUILD) $(DRIVER_BUILD) $(FS_BUILD) $(SERV_BUILD) $(LIBC_BUILD) $(ISO_DIR):
	@mkdir -p $@

# Compile bootloader
$(BOOT_OBJ): bootloader/boot.asm | $(BOOT_BUILD)
	@echo "[+] Compiling bootloader..."
	$(AS) $(ASFLAGS) $< -o $@

# Compile kernel modules
$(KERNEL_BUILD)/memory_manager.o: kernel/memory_manager.c | $(KERNEL_BUILD)
	@echo "[+] Compiling memory manager..."
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BUILD)/%.o: kernel/%.c | $(KERNEL_BUILD)
	@echo "[+] Compiling kernel/$*..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile drivers
$(DRIVER_BUILD)/keyboard.o: drivers/keyboard.c | $(DRIVER_BUILD)
	@echo "[+] Compiling keyboard driver..."
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVER_BUILD)/display.o: drivers/display.c | $(DRIVER_BUILD)
	@echo "[+] Compiling display driver..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile filesystem
$(FS_BUILD)/vfs.o: fs/vfs.c | $(FS_BUILD)
	@echo "[+] Compiling VFS..."
	$(CC) $(CFLAGS) -c $< -o $@

# Compile services
$(SERV_BUILD)/user_manager.o: services/user_manager.c | $(SERV_BUILD)
	@echo "[+] Compiling user manager..."
	$(CC) $(CFLAGS) -c $< -o $@

$(SERV_BUILD)/package_manager.o: services/package_manager.c | $(SERV_BUILD)
	@echo "[+] Compiling package manager..."
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel
$(KERNEL_ELF): $(BOOT_OBJ) $(KERNEL_BUILD)/memory_manager.o $(DRIVER_BUILD)/keyboard.o $(DRIVER_BUILD)/display.o $(FS_BUILD)/vfs.o $(SERV_BUILD)/user_manager.o $(SERV_BUILD)/package_manager.o | $(KERNEL_BUILD)
	@echo "[+] Linking kernel..."
	$(LD) -T kernel/linker.ld -o $@ $^ $(LDFLAGS)
	@echo "[OK] Kernel linked successfully"

# Create ISO
$(ISO_FILE): $(KERNEL_ELF) | $(ISO_DIR)
	@echo "[+] Creating ISO image..."
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(KERNEL_ELF) $(ISO_DIR)/boot/kernel.elf
	@cp kernel/grub.cfg $(ISO_DIR)/boot/grub/
	@cp userland/init.sh $(ISO_DIR)/
	@grub-mkrescue -o $@ $(ISO_DIR) 2>/dev/null || \
	  xorriso -as mkisofs -R -J -o $@ $(ISO_DIR)
	@echo "[OK] ISO created: $@"

# Build target
build: $(ISO_FILE)
	@echo ""
	@echo "╔════════════════════════════════════════════╗"
	@echo "║   Elyamany Linux - Build Successful        ║"
	@echo "║   Version: 1.0.0                          ║"
	@echo "║   ISO: $(ISO_FILE)               ║"
	@echo "║   Size: $$(du -h $(ISO_FILE) | cut -f1)                             ║"
	@echo "╚════════════════════════════════════════════╝"
	@echo ""

# Run in QEMU
run: build
	@echo "[*] Launching QEMU..."
	@$(QEMU) -cdrom $(ISO_FILE) -m 512M -boot d

# Debug mode
debug: build
	@echo "[*] Launching QEMU with GDB..."
	@$(QEMU) -cdrom $(ISO_FILE) -m 512M -boot d -s -S &
	@sleep 1
	@$(GDB) $(KERNEL_ELF) -ex "target remote localhost:1234" \
		-ex "break kernel_main" -ex "continue"

# Clean build artifacts
clean:
	@echo "[*] Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "[OK] Clean complete"

# Help
help:
	@echo "Elyamany Linux - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  all     - Build the OS (default)"
	@echo "  build   - Build ISO image"
	@echo "  run     - Build and run in QEMU"
	@echo "  debug   - Build and run with GDB"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
	@echo ""
