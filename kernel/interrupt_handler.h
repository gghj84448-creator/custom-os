/*
 * Interrupt Handler - IDT, ISR, IRQ
 */

#ifndef INTERRUPT_HANDLER_H
#define INTERRUPT_HANDLER_H

#include <stdint.h>

#define NUM_INTERRUPTS 256
#define NUM_IRQ 16

typedef void (*interrupt_handler_t)(void);

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr_t;

void init_interrupts(void);
void register_interrupt_handler(uint8_t irq, interrupt_handler_t handler);
void enable_interrupts(void);
void disable_interrupts(void);

#endif
