.PHONY: all clean run debug iso

# Toolchain
CC = i686-elf-gcc
LD = i686-elf-ld
AS = nasm
OBJCOPY = i686-elf-objcopy

# Directories
BUILD_DIR = build
SRC_DIR = src
BOOT_DIR = bootloader
KERNEL_DIR = kernel

# Flags
CFLAGS = -std=c11 -Wall -Wextra -Werror -ffreestanding -O2 -fno-builtin
LDFLAGS = -static -nostdlib
ASFLAGS = -f elf

# Output files
KERNEL_ELF = $(BUILD_DIR)/kernel.elf
BOOT_OBJ = $(BUILD_DIR)/boot.o
ISO = $(BUILD_DIR)/os.iso
FLOPPY = $(BUILD_DIR)/os.flp

# Main targets
all: $(ISO)

$(BUILD_DIR):
	@mkdir -p $@

$(BOOT_OBJ): bootloader/boot.asm | $(BUILD_DIR)
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_ELF): $(BOOT_OBJ) kernel/kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -T kernel/linker.ld $(BOOT_OBJ) kernel/kernel.c -o $@ $(LDFLAGS)

$(ISO): $(KERNEL_ELF)
	mkdir -p $(BUILD_DIR)/isodir/boot/grub
	cp $(KERNEL_ELF) $(BUILD_DIR)/isodir/boot/
	cp kernel/grub.cfg $(BUILD_DIR)/isodir/boot/grub/
	grub-mkrescue -o $@ $(BUILD_DIR)/isodir/

run: $(ISO)
	qemu-system-i386 -cdrom $< -m 512M

debug: $(ISO)
	qemu-system-i386 -cdrom $< -m 512M -s -S &
	i386-elf-gdb $(KERNEL_ELF) -ex "target remote localhost:1234" -ex "continue"

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Available targets:"
	@echo "  all    - Build the OS ISO"
	@echo "  run    - Run in QEMU"
	@echo "  debug  - Run with GDB debugging"
	@echo "  clean  - Remove build artifacts"
	@echo "  help   - Show this help message"
