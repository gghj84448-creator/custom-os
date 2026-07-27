/*
 * Timer Implementation - System Clock
 */

#include <stdio.h>
#include "timer.h"

static volatile uint32_t tick_count = 0;
static void (*timer_callback)(void) = NULL;

void init_timer(uint32_t frequency) {
    tick_count = 0;
    
    // Programmable Interval Timer (PIT) setup
    uint32_t divisor = 1193180 / frequency;
    
    // Send command byte
    asm volatile("outb %0, %1" : : "a"((uint8_t)0x34), "Nd"((uint16_t)0x43));
    
    // Send divisor low byte
    asm volatile("outb %0, %1" : : "a"((uint8_t)(divisor & 0xFF)), "Nd"((uint16_t)0x40));
    
    // Send divisor high byte
    asm volatile("outb %0, %1" : : "a"((uint8_t)((divisor >> 8) & 0xFF)), "Nd"((uint16_t)0x40));
    
    printf("[OK] Timer initialized at %d Hz\n", frequency);
}

uint32_t get_tick_count(void) {
    return tick_count;
}

void sleep(uint32_t milliseconds) {
    uint32_t target = tick_count + milliseconds;
    while (tick_count < target);
}

void set_timer_callback(void (*callback)(void)) {
    timer_callback = callback;
}
