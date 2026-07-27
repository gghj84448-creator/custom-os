/*
 * Display Driver Implementation - Graphics and Framebuffer
 */

#include <stdio.h>
#include "display.h"

static framebuffer_t fb;

void init_display(graphics_mode_t mode) {
    fb.width = 1024;
    fb.height = 768;
    fb.bpp = 32;
    fb.pitch = fb.width * (fb.bpp / 8);
    fb.framebuffer = (uint8_t*)0xE0000000;  // Frame buffer address
    
    printf("[OK] Display driver initialized: %dx%d@%d-bit\n", 
           fb.width, fb.height, fb.bpp);
}

void set_pixel(uint32_t x, uint32_t y, uint32_t color) {
    if (x >= fb.width || y >= fb.height) return;
    
    uint32_t offset = (y * fb.pitch) + (x * (fb.bpp / 8));
    *(uint32_t*)(fb.framebuffer + offset) = color;
}

void draw_rectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color) {
    for (uint32_t i = 0; i < h; i++) {
        for (uint32_t j = 0; j < w; j++) {
            set_pixel(x + j, y + i, color);
        }
    }
}

framebuffer_t* get_framebuffer(void) {
    return &fb;
}

void swap_buffers(void) {
    // Implementation for double buffering
}
