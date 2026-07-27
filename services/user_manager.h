/*
 * User Manager - User and Group Management
 */

#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <stdint.h>

#define MAX_USERNAME 32
#define MAX_PASSWORD 64
#define MAX_USERS 256

typedef struct {
    uint32_t uid;
    uint32_t gid;
    char username[MAX_USERNAME];
    char password_hash[MAX_PASSWORD];
    char home_dir[256];
    uint32_t created_time;
} user_t;

void init_user_manager(void);
int create_user(const char* username, const char* password);
int delete_user(uint32_t uid);
int authenticate_user(const char* username, const char* password);
user_t* get_user_by_uid(uint32_t uid);
user_t* get_user_by_name(const char* username);

#endif
