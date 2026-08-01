// kernel.cpp - stub
#include "kernel.h"
#include <stdio.h>

extern "C" void kernel_main() {
    // نقطة انطلاق النواة
    kernel::initialize();
    while (1) {
        asm volatile ("hlt");
    }
}

namespace kernel {

const char* version() { return "elyamany-0.1"; }

void initialize() {
    // تهيئة أساسية
    // TODO: init GDT/IDT, memory, drivers, scheduler
}

}
