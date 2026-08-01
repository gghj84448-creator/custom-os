#!/usr/bin/env bash
set -e

# build/scripts/build.sh - simple build script (improved)
# This script attempts to compile a minimal 64-bit kernel and build a bootable ISO using GRUB.
# Customize CC/CXX/LD/AS variables if you use different cross-toolchain names.

ROOT=$(pwd)
OUT=$ROOT/build/output
OBJ=$ROOT/build/obj
mkdir -p "$OUT" "$OBJ"

# Toolchain - customize if needed
CC=${CC:-x86_64-elf-gcc}
CXX=${CXX:-x86_64-elf-g++}
LD=${LD:-x86_64-elf-ld}
AS=${AS:-nasm}

CFLAGS="-ffreestanding -O2 -g -mno-red-zone -Wall -Wextra -fno-exceptions -fno-rtti"
LDFLAGS="-T $ROOT/boot/linker.ld -nostdlib"

echo "Using toolchain: CC=$CC CXX=$CXX LD=$LD AS=$AS"

# compile entry (NASM-style via gcc -c supports GAS syntax for .S files) - we use gcc assembler for .S
$CXX -c kernel/entry.S -o "$OBJ/entry.o" -std=gnu++17 || true
# If the above fails (some toolchains don't accept .S with CXX), try using gcc for assembly
if [ ! -f "$OBJ/entry.o" ]; then
  echo "Falling back to gcc for assembling entry.S"
  $CC -c kernel/entry.S -o "$OBJ/entry.o"
fi

# compile kernel C++ sources
$CXX $CFLAGS -std=gnu++17 -c kernel/kernel.cpp -o "$OBJ/kernel.o"

# link kernel
$LD $LDFLAGS "$OBJ/entry.o" "$OBJ/kernel.o" -o "$OUT/kernel.bin"

# prepare ISO structure
ISO_ROOT="$OUT/iso"
rm -rf "$ISO_ROOT"
mkdir -p "$ISO_ROOT/boot/grub"
cp -v "$OUT/kernel.bin" "$ISO_ROOT/boot/kernel.bin"
cp -v boot/grub.cfg "$ISO_ROOT/boot/grub/grub.cfg"

# build ISO using grub-mkrescue (requires grub-mkrescue and xorriso on the host)
if command -v grub-mkrescue >/dev/null 2>&1; then
  echo "Building ISO with grub-mkrescue..."
  grub-mkrescue -o "$OUT/elyamany.iso" "$ISO_ROOT" || echo "grub-mkrescue failed - ensure grub and xorriso are installed"
else
  echo "grub-mkrescue not found; skipping ISO creation. You can build an ISO manually with grub-mkrescue or xorriso."
fi

echo "Build complete. Output: $OUT"
