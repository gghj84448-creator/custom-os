/*
 * Panic - Kernel Panic and Error Handling
 */

#ifndef PANIC_H
#define PANIC_H

#include <stdint.h>

void panic(const char* message);
void kernel_assert(int condition, const char* message);
void dump_registers(void);
void dump_stack(void);

#endif
