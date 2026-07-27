/*
 * Storage Driver - Hard Disk, SSD, USB Storage
 */

#ifndef STORAGE_DRIVER_H
#define STORAGE_DRIVER_H

#include <stdint.h>

void init_storage(void);
int read_sector(uint32_t sector, uint8_t* buffer);
int write_sector(uint32_t sector, const uint8_t* buffer);
int read_sectors(uint32_t start_sector, uint32_t count, uint8_t* buffer);
int write_sectors(uint32_t start_sector, uint32_t count, const uint8_t* buffer);

#endif
