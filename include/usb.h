#ifndef USB_H
#define USB_H

#include "peripheral.h"

#define USB_MDIO_CNTL   (volatile unsigned int*)(PERIPHERAL_BASE + USB_OFFSET + 0x080)
#define USB_MDIO_DATA   (volatile unsigned int*)(PERIPHERAL_BASE + USB_OFFSET + 0x084)
#define USB_VBUS_DRV    (volatile unsigned int*)(PERIPHERAL_BASE + USB_OFFSET + 0x088)


unsigned int usb_is_mdio_busy();

#endif // USB_H
