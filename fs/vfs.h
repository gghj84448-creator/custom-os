/*
 * Virtual File System - Generic FS Interface
 */

#ifndef VFS_H
#define VFS_H

#include <stdint.h>
#include <stddef.h>

#define MAX_FILENAME 256
#define MAX_OPEN_FILES 1024

typedef enum {
    FILE_TYPE_REGULAR,
    FILE_TYPE_DIRECTORY,
    FILE_TYPE_SYMLINK,
    FILE_TYPE_DEVICE
} file_type_t;

typedef struct {
    char filename[MAX_FILENAME];
    file_type_t type;
    uint32_t size;
    uint32_t permissions;
    uint32_t uid, gid;
    uint32_t created_time;
    uint32_t modified_time;
    uint32_t accessed_time;
} file_stat_t;

typedef struct {
    uint32_t inode;
    uint32_t position;
    uint32_t flags;
} file_descriptor_t;

void init_vfs(void);
int vfs_open(const char* path, uint32_t flags);
int vfs_close(int fd);
int vfs_read(int fd, void* buffer, uint32_t size);
int vfs_write(int fd, const void* data, uint32_t size);
int vfs_stat(const char* path, file_stat_t* stat);
int vfs_mkdir(const char* path, uint32_t permissions);
int vfs_rmdir(const char* path);
int vfs_unlink(const char* path);

#endif
