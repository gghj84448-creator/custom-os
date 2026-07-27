/*
 * Network Manager - Network Configuration and Management
 */

#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <stdint.h>

void init_network_manager(void);
int connect_wifi(const char* ssid, const char* password);
int disconnect_wifi(void);
int set_static_ip(uint32_t ip, uint32_t gateway, uint32_t netmask);
int enable_dhcp(void);
int get_ip_address(char* buffer);

#endif
