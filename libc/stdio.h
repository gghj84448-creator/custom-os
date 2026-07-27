/*
 * Standard I/O Functions
 */

#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>
#include <stdarg.h>

/* File operations */
int putchar(int c);
int getchar(void);
int puts(const char* s);
char* gets(char* s);

/* Formatted output */
int printf(const char* format, ...);
int sprintf(char* str, const char* format, ...);
int snprintf(char* str, size_t size, const char* format, ...);
int vprintf(const char* format, va_list ap);
int vsprintf(char* str, const char* format, va_list ap);
int vsnprintf(char* str, size_t size, const char* format, va_list ap);

/* Formatted input */
int scanf(const char* format, ...);
int sscanf(const char* str, const char* format, ...);

#endif
