/* Linker Script for x86 Kernel */

OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    . = 0x00100000;
    
    .text ALIGN(0x1000) : AT(ADDR(.text) - 0xC0000000)
    {
        *(.multiboot)
        *(.text*)
    }
    
    .rodata ALIGN(0x1000) : AT(ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata*)
    }
    
    .data ALIGN(0x1000) : AT(ADDR(.data) - 0xC0000000)
    {
        *(.data*)
    }
    
    .bss ALIGN(0x1000) : AT(ADDR(.bss) - 0xC0000000)
    {
        *(COMMON)
        *(.bss*)
    }
}
