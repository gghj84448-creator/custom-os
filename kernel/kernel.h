/* Kernel header file */

#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>
#include <stddef.h>

/* Kernel version */
#define KERNEL_VERSION "0.1.0"
#define KERNEL_NAME "Custom OS"

/* Basic types */
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;

/* Function prototypes */
void kernel_main(void);
void putchar(char c);
void puts(const char* str);
void clear_screen(void);

#endif /* KERNEL_H */
