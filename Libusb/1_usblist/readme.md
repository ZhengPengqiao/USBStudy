# usblist

## 编译

* make

## 参数介绍

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/1_usblist$ sudo ./usblist -h
    usage: libusb-test [-v vid] [-p pid] [-h] [-m mode] 
    -h      : display usage
    -m      : 显示模式,(0:显示所有usb设备, 1:显示指定设备详细信息)
    -v      : 默认设备的VID
    -p      : 默认设备的PID
```

## 执行结果

* 列出所有usb设备

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/1_usblist$ sudo ./usblist
    bus: 002 device: 002, VID: 8087 PID: 0024
    bus: 002 device: 001, VID: 1d6b PID: 0002, EHCI Host Controller
    bus: 001 device: 002, VID: 8087 PID: 0024
    bus: 001 device: 001, VID: 1d6b PID: 0002, EHCI Host Controller
    bus: 004 device: 001, VID: 1d6b PID: 0003, xHCI Host Controller
    bus: 003 device: 063, VID: 1a2c PID: 0c21, USB Keyboard
    bus: 003 device: 064, VID: 093a PID: 2521, USB OPTICAL MOUSE
    bus: 003 device: 002, VID: 0eef PID: 0001, Touch
    bus: 003 device: 001, VID: 1d6b PID: 0002, xHCI Host Controller
```

* 列出指定设备的详细信息

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/1_usblist$ sudo ./usblist -m 1
    bus:3 addr:64 
    Device descriptor:
    bDescriptorType:         1
    bcdUSB:                  0x0110
    bDeviceClass:            0
    bDeviceSubClass:         0
    bDeviceProtocol:         0
    bMaxPacketSize0:         8
    idVendor:                0x093a
    idProduct:               0x2521
    bNumConfigurations:      1
    Configuration descriptor:
        wTotalLength:         34
        bNumInterfaces:       1
        bConfigurationValue:  1
        iConfiguration:       4
        bmAttributes:         a0h
        MaxPower:             50
        Interface descriptor:
        bInterfaceNumber:   0
        bAlternateSetting:  0
        bNumEndpoints:      1
        bInterfaceClass:    3
        bInterfaceSubClass: 1
        bInterfaceProtocol: 2
        iInterface:         0
        Endpoint descriptor:
            bEndpointAddress: 81h
            bmAttributes:     03h
            wMaxPacketSize:   7
            bInterval:        10
            bRefresh:         0
            bSynchAddress:    0
```