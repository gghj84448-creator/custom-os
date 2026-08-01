#!/usr/bin/env bash
set -e

# build/scripts/build.sh - simple build script (placeholder)
# This script is a stub. Customize toolchain paths and build commands.

OUT=build/output
mkdir -p "$OUT"

echo "Building Elyamany OS (stub)..."
# TODO: run cross-compiler, assemble bootloader, create kernel.bin, build ISO

echo "(stub) Creating placeholder ISO structure"
mkdir -p "$OUT/iso/boot"
cp -r boot "$OUT/iso/boot/" || true
cp -r kernel "$OUT/iso/boot/" || true

echo "Done. Output in $OUT"
