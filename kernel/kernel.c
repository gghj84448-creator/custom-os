/* Main kernel file */

#include "kernel.h"

/* Video memory for text mode */
uint16_t* video_memory = (uint16_t*) 0xB8000;
uint32_t cursor_x = 0;
uint32_t cursor_y = 0;

/* Print character to screen */
void putchar(char c)
{
    uint16_t attribute = 0x0F; /* White text on black background */
    uint16_t* location = video_memory + (cursor_y * 80 + cursor_x);
    
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        *location = (attribute << 8) | c;
        cursor_x++;
        if (cursor_x >= 80) {
            cursor_x = 0;
            cursor_y++;
        }
    }
    
    if (cursor_y >= 25) {
        cursor_y = 0;
    }
}

/* Print string to screen */
void puts(const char* str)
{
    while (*str) {
        putchar(*str++);
    }
}

/* Clear screen */
void clear_screen(void)
{
    uint16_t attribute = 0x0F;
    uint16_t blank = (attribute << 8) | ' ';
    
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = blank;
    }
    
    cursor_x = 0;
    cursor_y = 0;
}

/* Main kernel entry point */
void kernel_main(void)
{
    clear_screen();
    
    puts("==================================\n");
    puts("    Custom OS - Kernel Started     \n");
    puts("==================================\n\n");
    
    puts("[OK] Screen cleared\n");
    puts("[OK] Video memory initialized\n");
    puts("[OK] Kernel loaded at 0x100000\n");
    puts("[OK] Stack initialized\n");
    
    puts("\nSystem Information:\n");
    puts("- Architecture: x86 (32-bit)\n");
    puts("- Memory: 512 MB\n");
    puts("- Boot method: GRUB Multiboot\n");
    
    puts("\n[INFO] Kernel initialization complete!\n");
    puts("[INFO] Waiting for interrupts...\n");
    
    /* Hang forever */
    while(1);
}
