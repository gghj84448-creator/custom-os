// kernel.cpp - minimal kernel with basic serial/console output
#include "kernel.h"
#include <stdint.h>

extern "C" void kernel_main();

extern void print_logo();

// very small implementation to demonstrate early kernel behavior
extern "C" void kernel_main() {
    // call a simple logo printer
    print_logo();
    // halt
    for(;;) asm volatile("hlt");
}

namespace kernel {

const char* version() { return "elyamany-0.1"; }

void initialize() {
    // TBI: GDT/IDT, memory, drivers, scheduler
}

}
