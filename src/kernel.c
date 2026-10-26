#include <stdint.h>
#include <fb.h>
#include <delay.h>
#include <utils.h>
#include <mb.h>
#include <shell.h>

int main(void) {
    char temp_str[64];

    delayUSecs(100);

    framebufferInit();
    shell_init(0,32);
    append_to_shell_buffer_str("Shell Initialized\n");

    mailbox[0] = 30*4; // Length of message in bytes
    mailbox[1] = MBOX_REQUEST;

    mailbox[2] = MBOX_TAG_GET_FIRMWARE_REV; // Tag identifier
    mailbox[3] = 4;
    mailbox[4] = 0;
    mailbox[5] = 0;

    mailbox[6] = MBOX_TAG_GET_BOARD_MODEL;
    mailbox[7] = 4;
    mailbox[8] = 0;
    mailbox[9] = 0;

    mailbox[10] = MBOX_TAG_GET_BOARD_REV;
    mailbox[11] = 4;
    mailbox[12] = 0;
    mailbox[13] = 0;

    mailbox[14] = MBOX_TAG_GET_MAC_ADDRESS;
    mailbox[15] = 6;
    mailbox[16] = 0;
    mailbox[17] = 0;
    mailbox[18] = 0;

    mailbox[19] = MBOX_TAG_GET_SERIAL;
    mailbox[20] = 8;
    mailbox[21] = 0;
    mailbox[22] = 0;
    mailbox[23] = 0;

    mailbox[24] = MBOX_TAG_GET_ARM_MEM;
    mailbox[25] = 8;
    mailbox[26] = 0;
    mailbox[27] = 0;
    mailbox[28] = 0;

    mailbox[29] = MBOX_TAG_LAST;

    while (mailboxCall(MBOX_CH_PROP) == 0) {
        append_to_shell_buffer_str("Mailbox Call Failed\n");
    }

    append_to_shell_buffer_str("Mailbox Call Success\n");

    int firmware_rev = mailbox[5];
    int board_model = mailbox[9];
    int board_rev = mailbox[13];
    long mac_address = (long)mailbox[18] << 32 | mailbox[17];
    long serial = (long)mailbox[23] << 32 | mailbox[22];
    int mem_address = mailbox[27];
    int mem_size = mailbox[28];

    append_to_shell_buffer_str("Firmware Revision: "); append_to_shell_buffer_int(firmware_rev); append_to_shell_buffer_ch('\n');
    append_to_shell_buffer_str("Board Model: "); append_to_shell_buffer_int(board_model); append_to_shell_buffer_ch('\n');
    append_to_shell_buffer_str("Board Revision: "); append_to_shell_buffer_int(board_rev); append_to_shell_buffer_ch('\n');

    append_to_shell_buffer_str("MAC Address: "); append_to_shell_buffer_hex(mac_address); append_to_shell_buffer_ch('\n');
    append_to_shell_buffer_str("Serial: "); append_to_shell_buffer_hex(serial); append_to_shell_buffer_ch('\n');

    append_to_shell_buffer_str("Base Memory Address: ");append_to_shell_buffer_hex(mem_address); append_to_shell_buffer_ch('\n');
    append_to_shell_buffer_str("Memory Size: "); append_to_shell_buffer_hex(mem_size); append_to_shell_buffer_ch('\n');


    uint32_t el;
    __asm__ volatile("mrs %0, CurrentEL" : "=r"(el));
    append_to_shell_buffer_str("Current Exception Level: "); append_to_shell_buffer_int((el >> 2) & 3); append_to_shell_buffer_ch('\n');

    while (1) {
        intToString(temp_str, 64, getSystemTimer());
        drawString(0,0, temp_str, 0xFFFFFF);

        mailbox[0] = 8*4; // Length of message in bytes
        mailbox[1] = MBOX_REQUEST;

        mailbox[2] = MBOX_TAG_GET_TEMP; // Tag identifier
        mailbox[3] = 8;
        mailbox[4] = 0;
        mailbox[5] = 0;
        mailbox[6] = 0;

        mailbox[7] = MBOX_TAG_LAST;

        mailboxCall(MBOX_CH_PROP);

        intToString(temp_str, 64, mailbox[6]);
        drawString(128,0, temp_str, 0xFFFFFF);
    }

    return 0;
}
