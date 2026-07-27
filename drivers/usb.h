/*
 * USB Driver - Universal Serial Bus
 */

#ifndef USB_DRIVER_H
#define USB_DRIVER_H

#include <stdint.h>

void init_usb(void);
void usb_enumerate_devices(void);
int usb_read_device(uint8_t device_id, uint8_t* buffer, uint32_t size);
int usb_write_device(uint8_t device_id, const uint8_t* data, uint32_t size);

#endif
