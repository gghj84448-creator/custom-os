/*
 * Keyboard Driver - PS/2 Keyboard Input
 */

#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#include <stdint.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_BUFFER_SIZE 256

typedef void (*keyboard_callback_t)(char key);

void init_keyboard(void);
void keyboard_handler(void);
char keyboard_getchar(void);
void register_keyboard_callback(keyboard_callback_t callback);

#endif
