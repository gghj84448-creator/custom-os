/*
 * Panic - Kernel Panic Implementation
 */

#include <stdio.h>
#include "panic.h"

void panic(const char* message) {
    printf("\n");
    printf("╔═══════════════════════════════════════════════╗\n");
    printf("║  KERNEL PANIC!                                 ║\n");
    printf("║  %s\n", message);
    printf("║                                               ║\n");
    printf("║  System halted.                              ║\n");
    printf("╚═══════════════════════════════════════════════╝\n");
    printf("\n");
    
    // Halt the CPU
    while(1) {
        asm volatile("hlt");
    }
}

void kernel_assert(int condition, const char* message) {
    if (!condition) {
        panic(message);
    }
}

void dump_registers(void) {
    printf("\nRegister Dump:\n");
    printf("EAX: 0x????????  EBX: 0x????????\n");
    printf("ECX: 0x????????  EDX: 0x????????\n");
    printf("ESI: 0x????????  EDI: 0x????????\n");
    printf("EBP: 0x????????  ESP: 0x????????\n");
}

void dump_stack(void) {
    printf("\nStack Dump:\n");
    printf("[Stack contents would be displayed here]\n");
}
