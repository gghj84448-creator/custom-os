/*
 * Scheduler - Process Scheduling and Context Switching
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "process_manager.h"

typedef enum {
    SCHED_FIFO,
    SCHED_RR,
    SCHED_CFS
} scheduler_policy_t;

void init_scheduler(scheduler_policy_t policy);
void schedule(void);
void context_switch(void);
void yield_cpu(void);
process_t* get_current_process(void);
void set_process_priority(uint32_t pid, uint32_t priority);

#endif
