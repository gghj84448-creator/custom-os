/*
 * Power Manager - Power States, Shutdown, Reboot
 */

#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <stdint.h>

typedef enum {
    POWER_STATE_RUNNING,
    POWER_STATE_IDLE,
    POWER_STATE_SLEEP,
    POWER_STATE_HIBERNATE,
    POWER_STATE_SHUTDOWN
} power_state_t;

void init_power_manager(void);
void set_power_state(power_state_t state);
void shutdown_system(void);
void reboot_system(void);
void sleep_system(void);
power_state_t get_power_state(void);

#endif
