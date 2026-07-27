/* 
 * Elyamany Linux - Main Kernel
 * Core kernel initialization and management
 */

#ifndef ELYAMANY_KERNEL_H
#define ELYAMANY_KERNEL_H

#include <stdint.h>
#include <stddef.h>

/* Kernel constants */
#define KERNEL_VERSION "1.0.0"
#define KERNEL_NAME "Elyamany Linux"
#define KERNEL_MAGIC 0x1BADB002

/* Memory constants */
#define PAGE_SIZE 4096
#define KERNEL_VIRTUAL_BASE 0xC0000000
#define KERNEL_PHYSICAL_BASE 0x00100000

/* Structures */
typedef struct {
    uint32_t memory_lower;
    uint32_t memory_upper;
    char bootloader_name[64];
    uint32_t flags;
} multiboot_info_t;

typedef struct {
    char name[32];
    uint32_t base;
    uint32_t size;
    uint8_t type;
} kernel_module_t;

/* Core subsystems */
void kernel_main(multiboot_info_t *mbd);
void init_memory_manager(void);
void init_process_manager(void);
void init_scheduler(void);
void init_interrupt_handler(void);
void init_timer(void);
void init_filesystem(void);
void init_device_drivers(void);
void init_user_manager(void);
void init_security(void);

/* Utility */
void panic(const char *message);
void printk(const char *fmt, ...);
void kernel_info(void);

#endif
