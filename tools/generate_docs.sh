#!/bin/bash
# Documentation Generator

echo "Generating Elyamany Linux Documentation..."

mkdir -p docs/{api,guides,design}

# Create API documentation
cat > docs/api/kernel.md << 'EOF'
# Elyamany Linux Kernel API

## Core Functions

### Memory Management
- `void* malloc(size_t size)` - Allocate memory
- `void free(void* ptr)` - Free memory
- `void* realloc(void* ptr, size_t size)` - Reallocate memory

### Process Management
- `process_t* create_process(const char* name, uint32_t priority)` - Create new process
- `void destroy_process(uint32_t pid)` - Destroy process
- `void schedule()` - Schedule next process

### File System
- `int vfs_open(const char* path, uint32_t flags)` - Open file
- `int vfs_read(int fd, void* buffer, uint32_t size)` - Read file
- `int vfs_write(int fd, const void* data, uint32_t size)` - Write file

EOF

echo "[OK] Documentation generated"
