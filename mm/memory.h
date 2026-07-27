/* Memory Management System */

#ifndef MM_MEMORY_H
#define MM_MEMORY_H

#include <stdint.h>
#include <stddef.h>

/* Memory layout constants */
#define KERNEL_VIRTUAL_BASE 0xC0000000
#define PAGE_SIZE 4096
#define PAGE_MASK (PAGE_SIZE - 1)

/* Memory structure */
typedef struct {
    uint32_t start;
    uint32_t size;
    uint8_t type;  /* 1 = usable, 2 = reserved */
} memory_region_t;

/* Page frame info */
typedef struct {
    uint32_t physical_address;
    uint32_t virtual_address;
    uint8_t present;
    uint8_t writable;
    uint8_t user;
} page_t;

/* Function prototypes */
void init_memory_manager(void);
void* malloc(size_t size);
void free(void* ptr);
void* realloc(void* ptr, size_t size);
void enable_paging(void);
void map_page(uint32_t virtual, uint32_t physical);
void unmap_page(uint32_t virtual);
uint32_t get_physical_address(uint32_t virtual);

#endif /* MM_MEMORY_H */
