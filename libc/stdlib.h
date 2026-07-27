/*
 * Standard C Library - Core Functions
 */

#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>
#include <stdint.h>

/* Memory management */
void* malloc(size_t size);
void* calloc(size_t nmemb, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

/* Integer functions */
int abs(int j);
long labs(long j);
long long llabs(long long j);

/* Random numbers */
int rand(void);
void srand(unsigned int seed);

/* String conversion */
int atoi(const char* nptr);
long atol(const char* nptr);
long long atoll(const char* nptr);
double atof(const char* nptr);

/* Process control */
void exit(int status);
void abort(void);

/* Searching and sorting */
void* bsearch(const void* key, const void* base, size_t nmemb,
              size_t size, int (*compar)(const void*, const void*));
void qsort(void* base, size_t nmemb, size_t size,
           int (*compar)(const void*, const void*));

#endif
