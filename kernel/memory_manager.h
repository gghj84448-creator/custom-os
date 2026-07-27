/*
 * Memory Manager - Virtual Memory, Paging, Heap
 */

#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stdint.h>
#include <stddef.h>

#define PAGE_SIZE 4096
#define PAGE_MASK (PAGE_SIZE - 1)
#define HEAP_START 0xD0000000
#define HEAP_SIZE (512 * 1024 * 1024)  // 512 MB

typedef struct {
    uint32_t present : 1;
    uint32_t writable : 1;
    uint32_t user : 1;
    uint32_t write_through : 1;
    uint32_t cache_disable : 1;
    uint32_t accessed : 1;
    uint32_t dirty : 1;
    uint32_t reserved : 1;
    uint32_t global : 1;
    uint32_t available : 3;
    uint32_t frame : 20;
} page_entry_t;

void init_paging(void);
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void map_page(uint32_t virtual, uint32_t physical);
void unmap_page(uint32_t virtual);
uint32_t get_physical_address(uint32_t virtual);

#endif
