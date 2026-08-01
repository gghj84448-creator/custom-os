// panic.cpp - kernel panic helper
#include <stdarg.h>
#include <stdio.h>

extern "C" void panic(const char* fmt, ...) {
    // بسيط جدا: في المستقبل اطبع عبر الconsole
    va_list ap; va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);
    for(;;) asm volatile("hlt");
}
