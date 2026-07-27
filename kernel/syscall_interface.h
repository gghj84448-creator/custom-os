/*
 * Syscall Interface - System Call Definitions
 */

#ifndef SYSCALL_INTERFACE_H
#define SYSCALL_INTERFACE_H

#include <stdint.h>

/* Syscall numbers */
#define SYSCALL_EXIT 1
#define SYSCALL_FORK 2
#define SYSCALL_EXEC 3
#define SYSCALL_READ 4
#define SYSCALL_WRITE 5
#define SYSCALL_OPEN 6
#define SYSCALL_CLOSE 7
#define SYSCALL_MALLOC 8
#define SYSCALL_FREE 9
#define SYSCALL_GETPID 10
#define SYSCALL_KILL 11
#define SYSCALL_YIELD 12
#define SYSCALL_SLEEP 13
#define SYSCALL_STAT 14
#define SYSCALL_CHDIR 15
#define SYSCALL_MKDIR 16
#define SYSCALL_RMDIR 17
#define SYSCALL_UNLINK 18

void init_syscalls(void);
uint32_t syscall(uint32_t number, ...);

#endif
