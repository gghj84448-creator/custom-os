/*
 * Process Manager - Process/Thread Management
 */

#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <stdint.h>
#include <stddef.h>

#define MAX_PROCESSES 256
#define MAX_THREADS_PER_PROCESS 32

typedef enum {
    PROCESS_RUNNING,
    PROCESS_SLEEPING,
    PROCESS_BLOCKED,
    PROCESS_ZOMBIE,
    PROCESS_TERMINATED
} process_state_t;

typedef struct {
    uint32_t eax, ebx, ecx, edx;
    uint32_t esi, edi, ebp, esp;
    uint32_t eip, eflags, cr3;
} registers_t;

typedef struct process {
    uint32_t pid;
    uint32_t ppid;
    process_state_t state;
    uint32_t priority;
    registers_t registers;
    void* page_directory;
    struct process* next;
    struct process* prev;
} process_t;

void init_process_manager(void);
process_t* create_process(const char* name, uint32_t priority);
void destroy_process(uint32_t pid);
void switch_process(void);
void list_processes(void);

#endif
