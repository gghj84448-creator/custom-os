#!/bin/bash
# ISO Builder - Create bootable Elyamany Linux ISO

set -e

echo "╔═══════════════════════════════════════════════╗"
echo "║  Elyamany Linux - ISO Builder                 ║"
echo "║  Version 1.0.0                               ║"
echo "╚═══════════════════════════════════════════════╝"
echo ""

# Configuration
PROJECT_NAME="Elyamany Linux"
VERSION="1.0.0"
ISO_LABEL="ELYAMANY"
BUILD_DIR="build"
ISO_DIR="${BUILD_DIR}/iso-build"
KERNEL_FILE="${BUILD_DIR}/kernel/kernel.elf"
OUT_ISO="${BUILD_DIR}/elyamany-linux-${VERSION}.iso"

# Check if kernel exists
if [ ! -f "$KERNEL_FILE" ]; then
    echo "[ERROR] Kernel not found: $KERNEL_FILE"
    echo "Please run 'make build' first"
    exit 1
fi

echo "[+] Building ISO..."
echo "    Kernel: $KERNEL_FILE"
echo "    Output: $OUT_ISO"
echo ""

# Create ISO directory structure
echo "[*] Creating ISO structure..."
mkdir -p ${ISO_DIR}/{boot/grub,usr/bin,usr/lib,etc,home,tmp,var}

# Copy kernel
echo "[*] Copying kernel..."
cp "$KERNEL_FILE" "${ISO_DIR}/boot/"

# Create GRUB configuration
echo "[*] Creating GRUB configuration..."
cat > "${ISO_DIR}/boot/grub/grub.cfg" << 'EOF'
menuentry 'Elyamany Linux' {
    multiboot /boot/kernel.elf
    boot
}
EOF

# Copy system files
echo "[*] Copying system files..."
cp userland/init.sh "${ISO_DIR}/sbin/init" 2>/dev/null || true
cp userland/shell.sh "${ISO_DIR}/usr/bin/esh" 2>/dev/null || true

# Create necessary directories
echo "[*] Creating system directories..."
mkdir -p ${ISO_DIR}/{sbin,dev,proc,sys,run,opt,srv,mnt}

# Create /etc files
echo "[*] Creating system configuration files..."
cat > "${ISO_DIR}/etc/os-release" << EOF
NAME="${PROJECT_NAME}"
VERSION="${VERSION}"
ID="elyamany-linux"
BUILD_ID="1"
PRETTY_NAME="${PROJECT_NAME} ${VERSION}"
HOME_URL="https://github.com/gghj84448-creator/custom-os"
EOF

cat > "${ISO_DIR}/etc/hostname" << EOF
elyamany
EOF

# Create ISO image
echo "[*] Creating ISO image..."
if command -v grub-mkrescue &> /dev/null; then
    grub-mkrescue -o "$OUT_ISO" "$ISO_DIR" 2>/dev/null && \
    echo "[OK] ISO created with grub-mkrescue" || {
        echo "[*] grub-mkrescue failed, trying xorriso..."
        xorriso -as mkisofs -R -J -o "$OUT_ISO" "$ISO_DIR"
    }
else
    echo "[*] Using xorriso..."
    xorriso -as mkisofs -R -J -o "$OUT_ISO" "$ISO_DIR"
fi

# Verify ISO
echo "[*] Verifying ISO..."
if [ -f "$OUT_ISO" ]; then
    ISO_SIZE=$(du -h "$OUT_ISO" | cut -f1)
    echo ""
    echo "╔═══════════════════════════════════════════════╗"
    echo "║  ISO Creation Successful!                     ║"
    echo "║  File: $OUT_ISO"
    echo "║  Size: $ISO_SIZE"
    echo "║  Label: $ISO_LABEL"
    echo "╚═══════════════════════════════════════════════╝"
    echo ""
    echo "To run the ISO:"
    echo "  qemu-system-i386 -cdrom $OUT_ISO -m 512M"
else
    echo "[ERROR] ISO creation failed"
    exit 1
fi

# Cleanup
echo "[*] Cleaning up..."
rm -rf "$ISO_DIR"
echo "[OK] Done"
