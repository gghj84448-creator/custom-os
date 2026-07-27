/*
 * EXT4 File System Support
 */

#ifndef EXT4_H
#define EXT4_H

#include <stdint.h>

#define EXT4_MAGIC 0xEF53

void init_ext4(void);
int ext4_mount(const char* device, const char* mount_point);
int ext4_unmount(const char* mount_point);

#endif
