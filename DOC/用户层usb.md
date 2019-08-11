# 用户层usb

## 常用指令

* 显示当前系统的设备
  * lsusb

    ```Shell
    zpq@zpq-pc:~$ lsusb 
    Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
    Bus 001 Device 003: ID 0bda:0129 Realtek Semiconductor Corp. RTS5129 Card Reader Controller
    Bus 001 Device 002: ID 04f2:b581 Chicony Electronics Co., Ltd 
    Bus 001 Device 045: ID 18f8:0f97  
    Bus 001 Device 058: ID 1fc9:0129 NXP Semiconductors 
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    zpq@zpq-pc:~$
    ```

* 显示idVendor=1fc9设备的详细信息，包括Configuration Descriptor/iInterface/Endpoint Descriptor
  * sudo lsusb  -d 1fc9: -v

    ```Shell
    zpq@zpq-pc:~$ sudo lsusb  -d 1fc9: -v

    Bus 001 Device 058: ID 1fc9:0129 NXP Semiconductors 
    Device Descriptor:
    bLength                18
    bDescriptorType         1
    bcdUSB               2.00
    bDeviceClass            0 (Defined at Interface level)
    bDeviceSubClass         0 
    bDeviceProtocol         0 
    bMaxPacketSize0        64
    idVendor           0x1fc9 NXP Semiconductors
    idProduct          0x0129 
    bcdDevice            0.02
    iManufacturer           1 NXP       SemiConductor Inc 
    iProduct                2 SE Blank 8QM 
    iSerial                 0 
    bNumConfigurations      1
    Configuration Descriptor:
        bLength                 9
        bDescriptorType         2
        wTotalLength           34
        bNumInterfaces          1
        bConfigurationValue     1
        iConfiguration          4 0A151998538FCADE
        bmAttributes         0xc0
        Self Powered
        MaxPower               10mA
        Interface Descriptor:
        bLength                 9
        bDescriptorType         4
        bInterfaceNumber        0
        bAlternateSetting       0
        bNumEndpoints           1
        bInterfaceClass         3 Human Interface Device
        bInterfaceSubClass      0 No Subclass
        bInterfaceProtocol      0 None
        iInterface              5 (error)
            HID Device Descriptor:
            bLength                 9
            bDescriptorType        33
            bcdHID               1.10
            bCountryCode            0 Not supported
            bNumDescriptors         1
            bDescriptorType        34 Report
            wDescriptorLength      76
            Report Descriptor: (length is 76)
                Item(Global): Usage Page, data= [ 0x00 0xff ] 65280
                                (null)
                Item(Local ): Usage, data= [ 0x01 ] 1
                                (null)
                Item(Main  ): Collection, data= [ 0x01 ] 1
                                Application
                Item(Global): Report ID, data= [ 0x01 ] 1
                Item(Local ): Usage Minimum, data= [ 0x01 ] 1
                                (null)
                Item(Local ): Usage Maximum, data= [ 0x01 ] 1
                                (null)
                Item(Global): Logical Minimum, data= [ 0x00 ] 0
                Item(Global): Logical Maximum, data= [ 0xff 0x00 ] 255
                Item(Global): Report Size, data= [ 0x08 ] 8
                Item(Global): Report Count, data= [ 0x10 ] 16
                Item(Main  ): Output, data= [ 0x02 ] 2
                                Data Variable Absolute No_Wrap Linear
                                Preferred_State No_Null_Position Non_Volatile Bitfield
                Item(Global): Report ID, data= [ 0x02 ] 2
                Item(Local ): Usage Minimum, data= [ 0x01 ] 1
                                (null)
                Item(Local ): Usage Maximum, data= [ 0x01 ] 1
                                (null)
                Item(Global): Logical Minimum, data= [ 0x00 ] 0
                Item(Global): Logical Maximum, data= [ 0xff 0x00 ] 255
                Item(Global): Report Size, data= [ 0x80 ] 128
                Item(Global): Report Count, data= [ 0x40 ] 64
                Item(Main  ): Output, data= [ 0x02 ] 2
                                Data Variable Absolute No_Wrap Linear
                                Preferred_State No_Null_Position Non_Volatile Bitfield
                Item(Global): Report ID, data= [ 0x03 ] 3
                Item(Local ): Usage Minimum, data= [ 0x01 ] 1
                                (null)
                Item(Local ): Usage Maximum, data= [ 0x01 ] 1
                                (null)
                Item(Global): Logical Minimum, data= [ 0x00 ] 0
                Item(Global): Logical Maximum, data= [ 0xff 0x00 ] 255
                Item(Global): Report Size, data= [ 0x08 ] 8
                Item(Global): Report Count, data= [ 0x04 ] 4
                Item(Main  ): Input, data= [ 0x02 ] 2
                                Data Variable Absolute No_Wrap Linear
                                Preferred_State No_Null_Position Non_Volatile Bitfield
                Item(Global): Report ID, data= [ 0x04 ] 4
                Item(Local ): Usage Minimum, data= [ 0x01 ] 1
                                (null)
                Item(Local ): Usage Maximum, data= [ 0x01 ] 1
                                (null)
                Item(Global): Logical Minimum, data= [ 0x00 ] 0
                Item(Global): Logical Maximum, data= [ 0xff 0x00 ] 255
                Item(Global): Report Size, data= [ 0x08 ] 8
                Item(Global): Report Count, data= [ 0x40 ] 64
                Item(Main  ): Input, data= [ 0x02 ] 2
                                Data Variable Absolute No_Wrap Linear
                                Preferred_State No_Null_Position Non_Volatile Bitfield
                Item(Main  ): End Collection, data=none
        Endpoint Descriptor:
            bLength                 7
            bDescriptorType         5
            bEndpointAddress     0x81  EP 1 IN
            bmAttributes            3
            Transfer Type            Interrupt
            Synch Type               None
            Usage Type               Data
            wMaxPacketSize     0x0040  1x 64 bytes
            bInterval               1
    Device Qualifier (for other device speed):
    bLength                10
    bDescriptorType         6
    bcdUSB               2.00
    bDeviceClass            0 (Defined at Interface level)
    bDeviceSubClass         0 
    bDeviceProtocol         0 
    bMaxPacketSize0        64
    bNumConfigurations      1
    Device Status:     0x0000
    (Bus Powered)
    zpq@zpq-pc:~$ 

    ```