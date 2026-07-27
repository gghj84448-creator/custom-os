/* Linker script */

ENTRY(_start)

SECTIONS
{
    /* Kernel starts at 1MB */
    . = 0x100000;
    
    .text :
    {
        *(.text)
    }
    
    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
    }
    
    .data :
    {
        *(.data)
        *(.data.*)
    }
    
    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }
}
