/*
 * Security Manager - Permissions, Encryption, Authentication
 */

#ifndef SECURITY_H
#define SECURITY_H

#include <stdint.h>

#define PERM_READ 4
#define PERM_WRITE 2
#define PERM_EXECUTE 1

typedef struct {
    uint32_t owner_uid;
    uint32_t group_gid;
    uint8_t owner_perms;
    uint8_t group_perms;
    uint8_t other_perms;
} permissions_t;

void init_security(void);
int check_permission(uint32_t uid, uint32_t gid, permissions_t* perms, uint8_t required);
char* hash_password(const char* password);
int verify_password(const char* password, const char* hash);
char* encrypt_file(const char* filename, const char* key);
char* decrypt_file(const char* filename, const char* key);

#endif
