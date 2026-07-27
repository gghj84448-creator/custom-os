/*
 * FAT32 File System Support
 */

#ifndef FAT32_H
#define FAT32_H

#include <stdint.h>

void init_fat32(void);
int fat32_mount(const char* device, const char* mount_point);
int fat32_unmount(const char* mount_point);

#endif
