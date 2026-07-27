/*
 * Package Manager Implementation - Install/Remove/Update Packages
 */

#include <stdio.h>
#include <string.h>
#include "package_manager.h"

static package_t packages[MAX_PACKAGES];
static uint32_t package_count = 0;

void init_package_manager(void) {
    package_count = 0;
    printf("[OK] Package Manager initialized\n");
}

int install_package(const char* package_name) {
    if (!package_name || package_count >= MAX_PACKAGES) {
        printf("[ERROR] Cannot install package: %s\n", package_name);
        return -1;
    }
    
    package_t* pkg = &packages[package_count++];
    strcpy(pkg->name, package_name);
    pkg->installed = 1;
    
    printf("[+] Package '%s' installed successfully\n", package_name);
    return 0;
}

int uninstall_package(const char* package_name) {
    for (uint32_t i = 0; i < package_count; i++) {
        if (strcmp(packages[i].name, package_name) == 0) {
            packages[i].installed = 0;
            printf("[+] Package '%s' uninstalled successfully\n", package_name);
            return 0;
        }
    }
    
    printf("[ERROR] Package '%s' not found\n", package_name);
    return -1;
}

int update_package(const char* package_name) {
    for (uint32_t i = 0; i < package_count; i++) {
        if (strcmp(packages[i].name, package_name) == 0) {
            printf("[+] Updating package '%s'...\n", package_name);
            return 0;
        }
    }
    
    return -1;
}

int list_installed_packages(void) {
    printf("\nInstalled Packages:\n");
    printf("──────────────────────────────────────────\n");
    
    for (uint32_t i = 0; i < package_count; i++) {
        if (packages[i].installed) {
            printf("  %s (v%s)\n", packages[i].name, packages[i].version);
        }
    }
    
    printf("──────────────────────────────────────────\n");
    printf("Total: %d packages\n\n", package_count);
    
    return 0;
}

package_t* search_package(const char* name) {
    for (uint32_t i = 0; i < package_count; i++) {
        if (strcmp(packages[i].name, name) == 0) {
            return &packages[i];
        }
    }
    
    return NULL;
}
