/*
 * Timer - System Timer and Clock Management
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void init_timer(uint32_t frequency);
uint32_t get_tick_count(void);
void sleep(uint32_t milliseconds);
void set_timer_callback(void (*callback)(void));

#endif
