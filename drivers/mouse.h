/*
 * Mouse Driver - PS/2 Mouse Input
 */

#ifndef MOUSE_DRIVER_H
#define MOUSE_DRIVER_H

#include <stdint.h>

typedef struct {
    int32_t x;
    int32_t y;
    uint8_t buttons;
} mouse_state_t;

void init_mouse(void);
void mouse_handler(void);
mouse_state_t get_mouse_state(void);

#endif
