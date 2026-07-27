/*
 * Keyboard Driver Implementation
 */

#include <stdio.h>
#include "keyboard.h"

static char keyboard_buffer[KEYBOARD_BUFFER_SIZE];
static uint32_t buffer_head = 0;
static uint32_t buffer_tail = 0;

void init_keyboard(void) {
    printf("[OK] Keyboard driver initialized\n");
}

void keyboard_handler(void) {
    uint8_t scancode = 0x00;  // Read from port 0x60
    
    if (scancode == 0x1C) {  // Enter key
        keyboard_buffer[buffer_head++] = '\n';
    } else if (scancode == 0x0E) {  // Backspace
        if (buffer_head > 0) {
            buffer_head--;
        }
    } else {
        // Add character to buffer
    }
}

char keyboard_getchar(void) {
    while (buffer_head == buffer_tail);
    
    char c = keyboard_buffer[buffer_tail++];
    if (buffer_tail >= KEYBOARD_BUFFER_SIZE) {
        buffer_tail = 0;
    }
    
    return c;
}

void register_keyboard_callback(keyboard_callback_t callback) {
    // Implementation
}
