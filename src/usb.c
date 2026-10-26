#include <usb.h>

unsigned int usb_is_mdio_busy() {
    return *(USB_MDIO_CNTL) & 0x80000000;
}

void usb_mdio_bb_mdo(unsigned int val) {
    if (val) *(USB_MDIO_CNTL) |= (1UL << 23);
    else *(USB_MDIO_CNTL) &= ~(1UL << 23);
}

void usb_mdio_bb_mdc(unsigned int val) {
    if (val) *(USB_MDIO_CNTL) |= (1UL << 22);
    else *(USB_MDIO_CNTL) &= ~(1UL << 22);
}

void usb_mdio_bb_enable(unsigned int val) {
    if (val) *(USB_MDIO_CNTL) |= (1UL << 21);
    else *(USB_MDIO_CNTL) &= ~(1UL << 21);
}

void usb_mdio_freerun_enable(unsigned int val) {
    if (val) *(USB_MDIO_CNTL) |= (1UL << 20);
    else *(USB_MDIO_CNTL) &= ~(1UL << 20);
}

void usb_mdio_set_mdc_ration(unsigned int val) {
    *(USB_MDIO_CNTL) = *(USB_MDIO_CNTL) & 0xFFF0FFFF + ((val & 0x0000000F) << 16);
}

unsigned int usb_mdio_mdi() {
    return *(USB_MDIO_CNTL) & 0x0000FFFF;
}

void usb_mdio_data_write(unsigned char phy_address, unsigned char reg_address, unsigned short data) {
    unsigned int packet =   (0x1 << 30) | //ST always 01
                            (0x1 << 28) | //OP 01 for write
                            ((phy_address & 0x1F) << 23) | //5 bit phy address
                            ((reg_address & 0x1F) << 18) | //5 bit reg address
                            (0x2 << 16) | //TA 10 (2 in hex) while writing
                            (data & 0xFFFF); //16 bit data

    *(USB_MDIO_DATA) = 0xFFFFFFFF;
    *(USB_MDIO_DATA) = packet;
    *(USB_MDIO_DATA) = 0;
}

unsigned short usb_mdio_data_read(unsigned char phy_address, unsigned char reg_address) {
    unsigned int packet =   (0x1 << 30) | //ST always 01
                            (0x2 << 28) | //OP 10 (2 in hex) for write
                            ((phy_address & 0x1F) << 23) | //5 bit phy address
                            ((reg_address & 0x1F) << 18) | //5 bit reg address
                            (0x2 << 16); //TA set to 10 for formatting

    *(USB_MDIO_DATA) = 0xFFFFFFFF;
    *(USB_MDIO_DATA) = packet;
    *(USB_MDIO_DATA) = 0;

    while (usb_is_mdio_busy());

    return (unsigned short)((*USB_MDIO_DATA) & 0xFFFF);
}

void usb_vbus_set_axi_priority(unsigned int val) {
    *(USB_VBUS_DRV) = *(USB_VBUS_DRV) & 0xFFF0FFFF + ((val & 0x0000000F) << 16);
}

unsigned int usb_vbus_irq_bit_changed() {
    return (*(USB_VBUS_DRV) & 0x200);
}

void usb_vbus_irq_enable(unsigned int val) {
    if (val) *(USB_VBUS_DRV) |= (1UL << 8);
    else *(USB_VBUS_DRV) &= ~(1UL << 8);
}
