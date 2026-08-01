// kernel.h - نواة: رؤوس أولية
#pragma once

#include <stdint.h>

extern "C" void kernel_main();

namespace kernel {

const char* version();
void initialize();

}
