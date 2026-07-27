/*
 * Interrupt Handler Implementation
 */

#include <stdio.h>
#include "interrupt_handler.h"

static idt_entry_t idt[NUM_INTERRUPTS];
static idt_ptr_t idt_ptr;
static interrupt_handler_t handlers[NUM_INTERRUPTS];

void init_interrupts(void) {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;
    
    // Initialize all IDT entries
    for (int i = 0; i < NUM_INTERRUPTS; i++) {
        idt[i].offset_low = 0;
        idt[i].selector = 0x08;  // Kernel code segment
        idt[i].zero = 0;
        idt[i].flags = 0x8E;     // Present, ring 0, interrupt gate
        idt[i].offset_high = 0;
        handlers[i] = NULL;
    }
    
    printf("[OK] Interrupt handler initialized\n");
}

void register_interrupt_handler(uint8_t irq, interrupt_handler_t handler) {
    if (irq < NUM_INTERRUPTS) {
        handlers[irq] = handler;
        printf("[+] Registered handler for IRQ %d\n", irq);
    }
}

void enable_interrupts(void) {
    asm volatile("sti");
}

void disable_interrupts(void) {
    asm volatile("cli");
}
