/*
 * Package Manager - Software Installation and Management
 */

#ifndef PACKAGE_MANAGER_H
#define PACKAGE_MANAGER_H

#include <stdint.h>

#define MAX_PACKAGE_NAME 128
#define MAX_PACKAGES 10000

typedef struct {
    char name[MAX_PACKAGE_NAME];
    char version[16];
    char description[256];
    uint32_t size;
    char* dependencies;
    uint32_t installed;
} package_t;

void init_package_manager(void);
int install_package(const char* package_name);
int uninstall_package(const char* package_name);
int update_package(const char* package_name);
int list_installed_packages(void);
package_t* search_package(const char* name);

#endif
