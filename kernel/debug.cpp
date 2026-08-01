// debug.cpp - debug helpers
#include <stdio.h>

void kdebug(const char* msg) {
    // TODO: route to serial / framebuffer
    printf("[KDBG] %s\n", msg);
}
