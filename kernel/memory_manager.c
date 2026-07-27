/*
 * Memory Manager Implementation - Paging and Heap
 */

#include <stdio.h>
#include "memory_manager.h"

static page_entry_t* page_directory = (page_entry_t*)0xFFFFF000;
static uint32_t heap_pointer = HEAP_START;

void init_paging(void) {
    // Initialize page tables
    for (int i = 0; i < 1024; i++) {
        page_directory[i].present = 0;
    }
    
    printf("[OK] Paging initialized\n");
}

void* malloc(size_t size) {
    if (heap_pointer + size > HEAP_START + HEAP_SIZE) {
        printf("[ERROR] Heap overflow\n");
        return NULL;
    }
    
    void* ptr = (void*)heap_pointer;
    heap_pointer += size;
    
    return ptr;
}

void free(void* ptr) {
    // Simple implementation - no actual freeing in this basic version
    (void)ptr;
}

void* realloc(void* ptr, size_t size) {
    void* new_ptr = malloc(size);
    if (!new_ptr) return NULL;
    
    // Copy old data if exists
    if (ptr) {
        // memcpy(new_ptr, ptr, old_size);
    }
    
    return new_ptr;
}

void map_page(uint32_t virtual, uint32_t physical) {
    uint32_t page_dir_index = virtual >> 22;
    uint32_t page_table_index = (virtual >> 12) & 0x3FF;
    
    page_entry_t* page_table = (page_entry_t*)(page_directory[page_dir_index].frame << 12);
    page_table[page_table_index].frame = physical >> 12;
    page_table[page_table_index].present = 1;
    page_table[page_table_index].writable = 1;
}

void unmap_page(uint32_t virtual) {
    uint32_t page_dir_index = virtual >> 22;
    uint32_t page_table_index = (virtual >> 12) & 0x3FF;
    
    page_entry_t* page_table = (page_entry_t*)(page_directory[page_dir_index].frame << 12);
    page_table[page_table_index].present = 0;
}

uint32_t get_physical_address(uint32_t virtual) {
    uint32_t page_dir_index = virtual >> 22;
    uint32_t page_table_index = (virtual >> 12) & 0x3FF;
    
    page_entry_t* page_table = (page_entry_t*)(page_directory[page_dir_index].frame << 12);
    return (page_table[page_table_index].frame << 12) | (virtual & 0xFFF);
}
