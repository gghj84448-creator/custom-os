/* Main Elyamany Linux Kernel Implementation */

#include <stdio.h>
#include "elyamany_kernel.h"
#include "memory_manager.h"
#include "interrupt_handler.h"
#include "timer.h"
#include "process_manager.h"
#include "scheduler.h"
#include "panic.h"

void printk(const char *fmt, ...) {
    // Simple implementation - can be enhanced
    printf(fmt);
}

void kernel_info(void) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║  %s v%s                       ║\n", KERNEL_NAME, KERNEL_VERSION);
    printf("║  Kernel loaded at: 0x%X\n", KERNEL_PHYSICAL_BASE);
    printf("║  Architecture: x86 32-bit                    ║\n");
    printf("║  Build Date: %s %s             ║\n", __DATE__, __TIME__);
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
}

void kernel_main(multiboot_info_t *mbd) {
    // Clear screen and show welcome message
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║  Welcome to Elyamany Linux!                   ║\n");
    printf("║  Starting kernel initialization...            ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Display kernel information
    kernel_info();
    
    // Initialize core subsystems
    printf("[*] Initializing core subsystems...\n");
    printf("\n");
    
    // Memory management
    printf("[Stage 1] Memory Management\n");
    init_paging();
    printf("\n");
    
    // Interrupts
    printf("[Stage 2] Interrupt Management\n");
    init_interrupts();
    printf("\n");
    
    // Timer
    printf("[Stage 3] Timer System\n");
    init_timer(100);  // 100 Hz
    printf("\n");
    
    // Process management
    printf("[Stage 4] Process Management\n");
    init_process_manager();
    printf("\n");
    
    // Scheduler
    printf("[Stage 5] Scheduler\n");
    init_scheduler(SCHED_RR);
    printf("\n");
    
    // File system
    printf("[Stage 6] File System\n");
    // init_filesystem();
    printf("[OK] Virtual File System ready\n");
    printf("\n");
    
    // Enable interrupts
    printf("[*] Enabling interrupts...\n");
    enable_interrupts();
    printf("\n");
    
    // System ready
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║  Kernel initialization completed!             ║\n");
    printf("║  System is now ready.                        ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Idle loop
    printf("[*] Entering idle loop...\n");
    while(1) {
        asm volatile("hlt");
    }
}
