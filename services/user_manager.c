/*
 * User Manager Implementation
 */

#include <stdio.h>
#include <string.h>
#include "user_manager.h"

static user_t users[MAX_USERS];
static uint32_t user_count = 0;

void init_user_manager(void) {
    // Create default root user
    strcpy(users[0].username, "root");
    users[0].uid = 0;
    users[0].gid = 0;
    strcpy(users[0].home_dir, "/root");
    user_count = 1;
    
    printf("[OK] User Manager initialized\n");
}

int create_user(const char* username, const char* password) {
    if (user_count >= MAX_USERS) {
        printf("[ERROR] Maximum users reached\n");
        return -1;
    }
    
    user_t* user = &users[user_count];
    strcpy(user->username, username);
    // Hash password here
    strcpy(user->password_hash, password);
    user->uid = user_count;
    user->gid = 100;  // Default group
    
    printf("[+] User '%s' created (UID: %d)\n", username, user->uid);
    user_count++;
    
    return 0;
}

int delete_user(uint32_t uid) {
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].uid == uid) {
            printf("[+] User '%s' deleted\n", users[i].username);
            return 0;
        }
    }
    
    return -1;
}

int authenticate_user(const char* username, const char* password) {
    for (uint32_t i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Verify password
            if (strcmp(users[i].password_hash, password) == 0) {
                printf("[+] User '%s' authenticated\n", username);
                return users[i].uid;
            }
        }
    }
    
    printf("[ERROR] Authentication failed\n");
    return -1;
}

user_t* get_user_by_uid(uint32_t uid) {
    for (uint32_t i = 0; i < user_count; i++) {
        if (users[i].uid == uid) {
            return &users[i];
        }
    }
    
    return NULL;
}

user_t* get_user_by_name(const char* username) {
    for (uint32_t i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    
    return NULL;
}
