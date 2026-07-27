/*
 * Network Driver - Ethernet, WiFi, TCP/IP Stack
 */

#ifndef NETWORK_DRIVER_H
#define NETWORK_DRIVER_H

#include <stdint.h>

typedef struct {
    uint8_t mac_address[6];
    uint32_t ip_address;
    uint32_t gateway;
    uint32_t netmask;
} network_config_t;

void init_network(void);
void init_wifi(const char* ssid, const char* password);
void init_ethernet(void);
int send_packet(const uint8_t* data, uint32_t size);
int receive_packet(uint8_t* buffer, uint32_t buffer_size);
network_config_t* get_network_config(void);

#endif
