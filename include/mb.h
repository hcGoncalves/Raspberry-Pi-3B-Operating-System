#ifndef MB_H
#define MB_H

extern volatile unsigned int mailbox[36];

enum {
    MBOX_REQUEST  = 0
};

enum {
    MBOX_CH_POWER = 0,
    MBOX_CH_FB    = 1,
    MBOX_CH_VUART = 2,
    MBOX_CH_VCHIQ = 3,
    MBOX_CH_LEDS  = 4,
    MBOX_CH_BTNS  = 5,
    MBOX_CH_TOUCH = 6,
    MBOX_CH_COUNT = 7,
    MBOX_CH_PROP  = 8
};

enum {
    MBOX_TAG_GET_FIRMWARE_REV    = 0x00000001, // Get firmware revision      Req: 0 Res: 4 bytes
    MBOX_TAG_GET_BOARD_MODEL     = 0x00010001, // Get board model            Req: 0 Res: 4 bytes
    MBOX_TAG_GET_BOARD_REV       = 0x00010002, // Get board revision         Req: 0 Res: 4 bytes
    MBOX_TAG_GET_MAC_ADDRESS     = 0x00010003, // Get MAC address            Req: 0 Res: 6 bytes
    MBOX_TAG_GET_SERIAL          = 0x00010004, // Get serial number          Req: 0 Res: 8 bytes
    MBOX_TAG_GET_ARM_MEM         = 0x00010005, // Get ARM memory info        Req: 0 Res: 8 bytes     32 bits for base address and 32 bits for size
    MBOX_TAG_GET_VC_MEM          = 0x00010006, // Get VideoCore memory info  Req: 0 Res: 8 bytes     32 bits for base address and 32 bits for size
    MBOX_TAG_GET_CLKS            = 0x00010007, // Get clocks                 Req: 0 Res: variable (multiples of 8 bytes) 32 bits for parent clock id and 32 repeating for other clock ids 

    MBOX_TAG_GET_POWER_STATE     = 0x00020001, // Get power state of device  Req: 4 bytes (32 bits for device id) Res: 4 bytes (32 bits for state)
                                          //Bit 0: 0=off, 1=on, Bit 1: 0=device exists, 1=device does not exist
    MBOX_TAG_GET_TIMING          = 0x00020002, // Get timing of device       Req: 4 bytes (32 bits for device id) Res: 8 bytes (32 bits for device id and 32 bits for wait time (when device is turned on) in microseconds)
    MBOX_TAG_SET_POWER_STATE     = 0x00028001, // Set power state of device  Req: 8 bytes (32 bits for device id and 32 bits for state) Bit 0: 0=off, 1=on, Bit 1: 0=do not wait (to become stable), 1=wait
                                          //Res: 8 bytes (32 bits for device id and 32 bits for state) Bit 0: 0=off, 1=on, Bit 1: 0=device exists, 1=device does not exist

    MBOX_TAG_GET_CLK_STATE       = 0x00030001, // Get clock state of device  Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for state) Bit 0: 0=off, 1=on, Bit 1: 0=clock exists, 1=clock does not exist
    MBOX_TAG_SET_CLK_STATE       = 0x00038001, // Set clock state of device  Req: 8 bytes (32 bits for clock id and 32 bits for state) Bit 0: 0=off, 1=on, Bit 1: 0=clock exists, 1=clock does not exist
                                          //Res: 8 bytes (32 bits for clock id and 32 bits for state) Bit 0: 0=off, 1=on, Bit 1: 0=clock exists, 1=clock does not exist
    MBOX_TAG_GET_CLK_RATE        = 0x00030002, // Get clock rate of device   Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for rate in Hz)
    MBOX_TAG_SET_CLK_RATE        = 0x00038002, // Set clock rate of device   Req: 12 bytes (32 bits for clock id, 32 bits for rate in Hz, 32 bits for skip setting turbo) Res: 8 bytes (32 bits for clock id and 32 bits for rate in Hz)
    
    MBOX_TAG_GET_CLK_RATE_MEASURED = 0x00030047, //Get the true clock rate which respects clamping, throttling and clock divider limitations. Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for rate in Hz)
    MBOX_TAG_GET_CLK_MAX_RATE      = 0x00030004, // Get max clock rate of device. Clocks should not be set higher than this. Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for rate in Hz)
    MBOX_TAG_GET_CLK_MIN_RATE      = 0x00030007, // Get min clock rate of device Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for rate in Hz)

    MBOX_TAG_GET_TURBO           = 0x00030009, // Get turbo state of device   Req: 4 bytes (32 bits for clock id) Res: 8 bytes (32 bits for clock id and 32 bits for level) id should be 0. level will be 0 for non-turbo and one for turbo
    MBOX_TAG_SET_TURBO           = 0x00038009, // Set turbo state of device   Req: 8 bytes (32 bits for clock id and 32 bits for level) id should be 0. level will be 0 for non-turbo and one for turbo Res: 8 bytes (32 bits for clock id and 32 bits for level) id should be 0. level will be 0 for non-turbo and one for turbo
                                          //GPU clocks will be set to max on turbo and to min on non-turbo.

    //LED Pins: Pin 42 is status pin, Pin 130 is power pin
    MBOX_TAG_GET_LED_STATUS      = 0x00030041, // Get onboard LED status (on or off) Req: 0 Res: 8 bytes (32 bits for pin number and 32 bits for status)
    MBOX_TAG_TEST_LED_STATUS     = 0x00034041, // Test onboard LED status (on or off) Req: 0 Res: 8 bytes (32 bits for pin number and 32 bits for status)
    MBOX_TAG_SET_LED_STATUS      = 0x00038041, // Set onboard LED status (on or off) Req: 8 bytes (32 bits for pin number and 32 bits for status) Res: 8 bytes (32 bits for pin number and 32 bits for status)


    MBOX_TAG_GET_VOLTAGE          = 0x00030003, // Get voltage of device       Req: 4 bytes (32 bits for voltage id) Res: 8 bytes (32 bits for voltage id and 32 bits for voltage in microvolts). A value of 0x8000000 indicates that the id is not valid.
    MBOX_TAG_SET_VOLTAGE          = 0x00038003, // Set voltage of device       Req: 8 bytes (32 bits for voltage id and 32 bits for voltage in microvolts) Res: 8 bytes (32 bits for voltage id and 32 bits for voltage in microvolts)
                                       //Voltage request value <= 16: relative to platform-specific typical voltage. 16 < value < 500000: absolute voltage in microvolts. value >= 500000: absolute voltage in microvolts
    MBOX_TAG_GET_VOLTAGE_MAX      = 0x00030005, // Get max voltage of device   Req: 4 bytes (32 bits for voltage id) Res: 8 bytes (32 bits for voltage id and 32 bits for voltage in microvolts). Voltages should not be higher than this.
    MBOX_TAG_GET_VOLTAGE_MIN      = 0x00030008, // Get min voltage of device   Req: 4 bytes (32 bits for voltage id) Res: 8 bytes (32 bits for voltage id and 32 bits for voltage in microvolts). This may be used while idle.

    MBOX_TAG_GET_TEMP            = 0x00030006, // Get temperature of the SoC   Req: 4 bytes (32 bits for temperature id) Res: 8 bytes (32 bits for temperature id and 32 bits for temperature in millidegrees Celsius). id should be 0.
    MBOX_TAG_GET_MAX_TEMP        = 0x0003000a, // Get max safe temperature of the SoC Req: 4 bytes (32 bits for temperature id) Res: 8 bytes (32 bits for temperature id and 32 bits for temperature in millidegrees Celsius). id should be 0. Overclock may be disabled above this.


    MBOX_TAG_MEM_ALLOC           = 0x0003000c, // Allocate memory to GPU       Req: 12 bytes (32 bits for size, 32 bits for alignment, 32 bits for flags) Res: 4 bytes (32 bits for handle). Handle != 0 for success.
    /* Flags Example

    MEM_FLAG_DISCARDABLE = 1 << 0,  can be resized to 0 at any time. Use for cached data 
    MEM_FLAG_NORMAL = 0 << 2,  normal allocating alias. Don't use from ARM 
    MEM_FLAG_DIRECT = 1 << 2,  0xC alias uncached 
    MEM_FLAG_COHERENT = 2 << 2,  0x8 alias. Non-allocating in L2 but coherent 
    MEM_FLAG_L1_NONALLOCATING = (MEM_FLAG_DIRECT | MEM_FLAG_COHERENT),  Allocating in L2 
    MEM_FLAG_ZERO = 1 << 4,   initialise buffer to all zeros 
    MEM_FLAG_NO_INIT = 1 << 5,  don't initialise (default is initialise to all ones 
    MEM_FLAG_HINT_PERMALOCK = 1 << 6,  Likely to be locked for long periods of time. 
    */

    MBOX_TAG_MEM_LOCK            = 0x0003000d, // Lock buffer in place          Req: 4 bytes (32 bits for handle) Res: 4 bytes (32 bits for bus address) address != 0 is success
    MBOX_TAG_MEM_UNLOCK          = 0x0003000e, // Unlock buffer                 Req: 4 bytes (32 bits for handle) Res: 4 bytes (32 bits for status). status = 0 is success.
    MBOX_TAG_MEM_RELEASE         = 0x0003000f, // Release memory block          Req: 4 bytes (32 bits for handle) Res: 4 bytes (32 bits for status). status = 0 is success.
    MBOX_TAG_EXECUTE_CODE        = 0x00030010, // Execute code on GPU           Req: 28 bytes (32 bits for function pointer, 32 for r0, 32 for r1, 32 for r2, 32 for r3, 32 for r4, 32 for r5) Res: 4 bytes (32 bits for r0).

    MBOX_TAG_GET_DISPMANX_RESOURCE_MEM   = 0x00030014, // Get a resource handle for a memory block. Req: 4 bytes (32 bits for resource handle) Res: 8 bytes (32 bits for success (0 is success) and 32 bits for mem handle for resource)
    MBOX_TAG_GET_EDID_BLOCK              = 0x00030020, // Get EDID block for display    Req: 4 bytes (32 bits for block number) Res: 136 bytes (32 bits for block number and 32 bits for status and 128 bytes for EDID block). You should keep requesting blocks until the status is non zero.



    MBOX_TAG_FB_ALLOCATE_BUFFER              = 0x00040001, // Allocate frame buffer        Req: 4 bytes (32 bits for alignment in bytes) Res: 8 bytes (32 bits for frame buffer address in bytes and 32 bits for buffer size in bytes)
    MBOX_TAG_FB_RELEASE_BUFFER               = 0x00048001, // Release and disable frame buffer  Req: 0 bytes Res: 0 bytes
    MBOX_TAG_FB_BLANK_SCREEN                 = 0x00040002, // Blank/unblank screen         Req: 4 bytes (bit 0: 0=off, 1=on) Res: 4 bytes (32 bits for status). status bit 0: 0=off, 1=on
    
    MBOX_TAG_FB_GET_PHYSICAL_WIDTH_HEIGHT    = 0x00040003, // Get physical width and height of frame buffer Req: 0 Res: 8 bytes (32 bits for width and 32 bits for height)
    MBOX_TAG_FB_TEST_PHYSICAL_WIDTH_HEIGHT   = 0x00044003, // Test physical width and height of frame buffer. Response is the same as the request if the configuration is supported Req: 8 bytes (32 bits for width and 32 bits for height) Res: 8 bytes (32 bits for width and 32 bits for height)
    MBOX_TAG_FB_SET_PHYSICAL_WIDTH_HEIGHT    = 0x00048003, // Set physical width and height of frame buffer Req: 8 bytes (32 bits for width and 32 bits for height) Res: 8 bytes (32 bits for width and 32 bits for height)
    
    MBOX_TAG_FB_GET_VIRTUAL_WIDTH_HEIGHT     = 0x00040004, // Get virtual width and height of frame buffer Req: 0 Res: 8 bytes (32 bits for width and 32 bits for height)
    MBOX_TAG_FB_TEST_VIRTUAL_WIDTH_HEIGHT    = 0x00044004, // Test virtual width and height of frame buffer. Response is the same as the request if the configuration is supported Req: 8 bytes (32 bits for width and 32 bits for height) Res: 8 bytes (32 bits for width and 32 bits for height)
    MBOX_TAG_FB_SET_VIRTUAL_WIDTH_HEIGHT     = 0x00048004, // Set virtual width and height of frame buffer Req: 8 bytes (32 bits for width and 32 bits for height) Res: 8 bytes (32 bits for width and 32 bits for height)

    MBOX_TAG_FB_GET_DEPTH                    = 0x00040005, // Get depth of frame buffer    Req: 0 Res: 4 bytes (32 bits for depth in bits per pixel)
    MBOX_TAG_FB_TEST_DEPTH                   = 0x00044005, // Test depth of frame buffer   Req: 4 bytes (32 bits for depth in bits per pixel) Res: 4 bytes (32 bits for depth in bits per pixel)
    MBOX_TAG_FB_SET_DEPTH                    = 0x00048005, // Set depth of frame buffer    Req: 4 bytes (32 bits for depth in bits per pixel) Res: 4 bytes (32 bits for depth in bits per pixel)

    MBOX_TAG_FB_GET_PIXEL_ORDER              = 0x00040006, // Get pixel order of frame buffer Req: 0 Res: 4 bytes (32 bits for pixel order)
    MBOX_TAG_FB_TEST_PIXEL_ORDER             = 0x00044006, // Test pixel order of frame buffer Req: 4 bytes (32 bits for pixel order) Res: 4 bytes (32 bits for pixel order)
    MBOX_TAG_FB_SET_PIXEL_ORDER              = 0x00048006, // Set pixel order of frame buffer Req: 4 bytes (32 bits for pixel order) Res: 4 bytes (32 bits for pixel order)

    MBOX_TAG_FB_GET_ALPHA_MODE               = 0x00040007, // Get alpha mode of frame buffer Req: 0 Res: 4 bytes (32 bits for alpha mode)
    MBOX_TAG_FB_TEST_ALPHA_MODE              = 0x00044007, // Test alpha mode of frame buffer Req: 4 bytes (32 bits for alpha mode) Res: 4 bytes (32 bits for alpha mode)
    MBOX_TAG_FB_SET_ALPHA_MODE               = 0x00048007, // Set alpha mode of frame buffer Req: 4 bytes (32 bits for alpha mode) Res: 4 bytes (32 bits for alpha mode)

    MBOX_TAG_FB_GET_PITCH                    = 0x00040008, // Get pitch of frame buffer    Req: 0 Res: 4 bytes (32 bits for pitch in bytes)
    
    MBOX_TAG_FB_GET_VIRTUAL_OFFSET           = 0x00040009, // Get virtual offset of frame buffer Req: 0 Res: 8 bytes (32 bits for x offset and 32 bits for y offset)
    MBOX_TAG_FB_TEST_VIRTUAL_OFFSET          = 0x00044009, // Test virtual offset of frame buffer Req: 8 bytes (32 bits for x offset and 32 bits for y offset) Res: 8 bytes (32 bits for x offset and 32 bits for y offset)
    MBOX_TAG_FB_SET_VIRTUAL_OFFSET           = 0x00048009, // Set virtual offset of frame buffer Req: 8 bytes (32 bits for x offset and 32 bits for y offset) Res: 8 bytes (32 bits for x offset and

    MBOX_TAG_FB_GET_OVERSCAN                 = 0x0004000a, // Get overscan of frame buffer  Req: 0 Res: 16 bytes (32 bits for top, bottom, left and right overscan)
    MBOX_TAG_FB_TEST_OVERSCAN                = 0x0004400a, // Test overscan of frame buffer Req: 16 bytes (32 bits for top, bottom, left and right overscan) Res: 16 bytes (32 bits for top, bottom, left and right overscan)
    MBOX_TAG_FB_SET_OVERSCAN                 = 0x0004800a, // Set overscan of frame buffer  Req: 16 bytes (32 bits for top, bottom, left and right overscan) Res: 16 bytes (32 bits for top, bottom, left and

    MBOX_TAG_FB_GET_PALETTE                  = 0x0004000b, // Get palette of frame buffer   Req: 0 Res: 1024 bytes (32 bits repeating for RGBA palette values)
    MBOX_TAG_FB_TEST_PALETTE                 = 0x0004400b, // Test palette of frame buffer  Req: 24-1032 (32 bits for offset (first palette to set), 32 bits for number of palette entries (1-256) and 32 bits repeating for RGBA palette values) Res: 4 (32 bits for status (0=valid, 1=invalid))
    MBOX_TAG_FB_SET_PALETTE                  = 0x0004800b, // Set palette of frame buffer   Req: 24-1032 (32 bits for offset (first palette to set), 32 bits for number of palette entries (1-256) and 32 bits repeating for RGBA palette values) Res: 4 (32 bits for status (0=valid, 1=invalid))

    MBOX_TAG_FB_SET_CURSOR_INFO              = 0x00008010, // Set cursor info Req: 24 bytes (32 bits for width, 32 bits for height, 32 bits unused, 32 bits for pointer to pixels, 32 pixels for hotspotX and 32 pixels for hotspotY) Res: 4 bytes (32 bits for value (0=valid, 1=invalid)) Format is 32bpp (ARGB) Width and height should be >= 16 and (width*height) <= 64
    MBOX_TAG_FB_SET_CURSOR_STATE             = 0x00008011, // Set cursor state Req: 16 bytes (32 bits for enabled (0=invisible, 1=visible), 32 bits for x, 32 bits for y and 32 bits for flags) Res: 4 bytes (32 bits for value (0=valid, 1=invalid))

    MBOX_TAG_LAST = 0x00000000
};

enum {
    MBOX_POWER_DEVICE_ID_SDCARD = 0x00000000,
    MBOX_POWER_DEVICE_ID_UART0   = 0x00000001,
    MBOX_POWER_DEVICE_ID_UART1   = 0x00000002,
    MBOX_POWER_DEVICE_ID_USBHCD = 0x00000003,
    MBOX_POWER_DEVICE_ID_I2C0    = 0x00000004,
    MBOX_POWER_DEVICE_ID_I2C1    = 0x00000005,
    MBOX_POWER_DEVICE_ID_I2C2    = 0x00000006,
    MBOX_POWER_DEVICE_ID_SPI     = 0x00000007,
    MBOX_POWER_DEVICE_ID_CCP2TX  = 0x00000008,
};

enum {
    MBOX_CLK_ID_EMMC     = 0x00000001,
    MBOX_CLK_ID_UART     = 0x00000002,
    MBOX_CLK_ID_ARM      = 0x00000003,
    MBOX_CLK_ID_CORE     = 0x00000004,
    MBOX_CLK_ID_V3D      = 0x00000005,
    MBOX_CLK_ID_H264     = 0x00000006,
    MBOX_CLK_ID_ISP      = 0x00000007,
    MBOX_CLK_ID_SDRAM    = 0x00000008,
    MBOX_CLK_ID_PIXEL    = 0x00000009,
    MBOX_CLK_ID_PWM      = 0x0000000a,
    MBOX_CLK_ID_HEVC     = 0x0000000b,
    MBOX_CLK_ID_EMMC2    = 0x0000000c,
    MBOX_CLK_ID_M2MC     = 0x0000000d,
    MBOX_CLK_ID_PIXELBVB = 0x0000000e,
};

enum {
    MBOX_VOLTAGE_ID_CORE    = 0x00000001,
    MBOX_VOLTAGE_ID_SDRAMC = 0x00000002,
    MBOX_VOLTAGE_ID_SDRAMP = 0x00000003,
    MBOX_VOLTAGE_ID_SDRAMI = 0x00000004,

    MBOX_VOLTAGE_RESPONSE_INVALID = 0x8000000,
};

enum {
    MBOX_FB_VALUES_PX_ORDER_BGR = 0x0,
    MBOX_FB_VALUES_PX_ORDER_RGB = 0x1,
    MBOX_FB_VALUES_ALPHA_ENABLED = 0x0, //0 = fully opaque
    MBOX_FB_VALUES_ALPHA_REVERSED =0x1, //0 = fully transparent
    MBOX_FB_VALUES_ALPHA_DISABLED = 0x2, //alpha channel is ignored
};

unsigned int mailboxCall(unsigned char ch);

#endif
