/*
 * Display Driver - GPU and Framebuffer
 */

#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

#include <stdint.h>

typedef enum {
    GRAPHICS_MODE_VGA,
    GRAPHICS_MODE_VESA,
    GRAPHICS_MODE_UEFI
} graphics_mode_t;

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t bpp;  // bits per pixel
    uint32_t pitch;
    uint8_t* framebuffer;
} framebuffer_t;

void init_display(graphics_mode_t mode);
void set_pixel(uint32_t x, uint32_t y, uint32_t color);
void draw_rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
framebuffer_t* get_framebuffer(void);
void swap_buffers(void);

#endif
