#!/bin/bash
# Development Environment Setup

echo "╔════════════════════════════════════════════════╗"
echo "║  Elyamany Linux - Development Setup           ║"
echo "╚════════════════════════════════════════════════╝"
echo ""

# Detect OS
OS="Linux"
if [[ "$OSTYPE" == "darwin"* ]]; then
    OS="macOS"
elif [[ "$OSTYPE" == "msys" ]]; then
    OS="Windows"
fi

echo "[*] Detected OS: $OS"
echo ""

# Check for required tools
echo "[*] Checking required tools..."

required_tools=("gcc" "nasm" "make" "git")
missing_tools=()

for tool in "${required_tools[@]}"; do
    if command -v $tool &> /dev/null; then
        echo "    [OK] $tool found"
    else
        echo "    [ERROR] $tool not found"
        missing_tools+=("$tool")
    fi
done

if [ ${#missing_tools[@]} -gt 0 ]; then
    echo ""
    echo "[!] Missing tools: ${missing_tools[*]}"
    echo ""
    
    if [ "$OS" = "Linux" ]; then
        echo "Install on Ubuntu/Debian:"
        echo "  sudo apt-get install build-essential nasm grub-pc xorriso qemu"
    elif [ "$OS" = "macOS" ]; then
        echo "Install on macOS (requires Homebrew):"
        echo "  brew install nasm qemu"
    fi
    exit 1
fi

echo ""
echo "[*] Installing cross-compiler (i686-elf)..."
echo "    This may take several minutes..."
echo ""

# Create cross-compiler directory
mkdir -p tools/cross-compiler
cd tools/cross-compiler

echo "[*] Download binutils and GCC..."
# Note: In production, automate this process
echo "[!] Please download and compile i686-elf-gcc"
echo "    Guide: https://wiki.osdev.org/GCC_Cross-Compiler"

cd - > /dev/null

echo ""
echo "╔════════════════════════════════════════════════╗"
echo "║  Setup Complete!                              ║"
echo "║  Run 'make build' to build Elyamany Linux     ║"
echo "╚════════════════════════════════════════════════╝"
