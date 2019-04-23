# usbmouse

## 键盘数据格式解析 (网上查询到的)

```Text

键盘发送给PC的数据每次8个字节
BYTE1 BYTE2 BYTE3 BYTE4 BYTE5 BYTE6 BYTE7 BYTE8
定义分别是：
BYTE1 --
       |--bit0:   Left Control是否按下，按下为1
       |--bit1:   Left Shift  是否按下，按下为1
       |--bit2:   Left Alt    是否按下，按下为1
       |--bit3:   Left GUI    是否按下，按下为1
       |--bit4:   Right Control是否按下，按下为1  
       |--bit5:   Right Shift 是否按下，按下为1
       |--bit6:   Right Alt   是否按下，按下为1
       |--bit7:   Right GUI   是否按下，按下为1
BYTE2 -- 暂不清楚，有的地方说是保留位
BYTE3--BYTE8 -- 这六个为普通按键
```

## 编译

* make

## 参数介绍

```C
xxx@xxx-pc:/fromHere1/USBStudy/4_usbkeyboard$ sudo ./usbkeyboard  -h
usage: libusb-test [-v idVendor] [-p idProduct] [-h] 
   -h      : display usage
   -m      : 显示模式,(0:显示原始数据， 1:显示解析数据)
   -v      : 默认设备的VID
   -p      : 默认设备的PID

```

## 执行结果

## 打印原始数据

```Shell
    xxx@xxx-pc:/fromHere1/USBStudy/4_usbkeyboard$ sudo ./usbkeyboard 
    打印获取鼠标的<原始数据>
    Success to register usb arrived callback
    Success to register usb left callback
    usb_monitor_thread creation Success
    usb monitor thread started.
    : Success
    Device(idVendor=6700, idProduct=3105) (3:86) Opened
    userDevice.bInEndpointAddress=0x0081, userDevice.bInEndpointMaxPacketSize=0x0008
    Kernel Driver Active
    Kernel Driver Detached!
    Claimed Interface
    size:8 : data:00 00 1a 00 00 00 00 00 
    size:8 : data:00 00 1a 15 00 00 00 00 
    size:8 : data:00 00 1a 15 08 00 00 00 
    size:8 : data:00 00 15 00 00 00 00 00 
    size:8 : data:00 00 15 17 00 00 00 00 
    size:8 : data:00 00 17 00 00 00 00 00 
    size:8 : data:00 00 00 00 00 00 00 00 
    ^C收到退出信号，等待main退出
    Released Interface
    收到退出信号，等待thread退出
    thread收到退出信号，完成退出
    main收到退出信号，完成退出
```

## 打印解析数据

```C
xxx@xxx-pc:/fromHere1/USBStudy/4_usbkeyboard$ sudo ./usbkeyboard -m 1
打印获取鼠标的<解析数据> x,y出事坐标为(0,0)
Success to register usb arrived callback
Success to register usb left callback
usb_monitor_thread creation Success
: Success
usb monitor thread started.
Device(idVendor=6700, idProduct=3105) (3:86) Opened
userDevice.bInEndpointAddress=0x0081, userDevice.bInEndpointMaxPacketSize=0x0008
Kernel Driver Active
Kernel Driver Detached!
Claimed Interface
size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- q -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- q e -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- q e r -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- e r -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- r -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- a -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- a s -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- s d -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- d -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- f -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- a -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:按下	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:按下	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:按下	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:按下	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
 size:8 : 	LC:松开	LS:松开	LA:松开	LG:松开	RC:松开	RS:松开	RA:松开	RG:松开 -- -- -- -- -- -- --
^C 收到退出信号，等待main退出
Released Interface
收到退出信号，等待thread退出
thread收到退出信号，完成退出
main收到退出信号，完成退出
```

## usb键盘设备

```C
xxx@xxx-pc:~/WorkSpaces/USBStudy/4_usbkeyboard$ ../1_usblist/usblist -m 1 -v 1a2c -p 0c21
bus:3 addr:103 
Device descriptor:
  bDescriptorType:         1
  bcdUSB:                  0x0110
  bDeviceClass:            0
  bDeviceSubClass:         0
  bDeviceProtocol:         0
  bMaxPacketSize0:         8
  idVendor:                0x1a2c
  idProduct:               0x0c21
  bNumConfigurations:      1
  Configuration descriptor:
    wTotalLength:         59
    bNumInterfaces:       2
    bConfigurationValue:  1
    iConfiguration:       0
    bmAttributes:         a0h
    MaxPower:             50
    Interface descriptor:
      bInterfaceNumber:   0
      bAlternateSetting:  0
      bNumEndpoints:      1
      bInterfaceClass:    3
      bInterfaceSubClass: 1
      bInterfaceProtocol: 1
      iInterface:         0
      Endpoint descriptor:
        bEndpointAddress: 81h
        bmAttributes:     03h
        wMaxPacketSize:   8
        bInterval:        10
        bRefresh:         0
        bSynchAddress:    0
    Interface descriptor:
      bInterfaceNumber:   1
      bAlternateSetting:  0
      bNumEndpoints:      1
      bInterfaceClass:    3
      bInterfaceSubClass: 1
      bInterfaceProtocol: 2
      iInterface:         0
      Endpoint descriptor:
        bEndpointAddress: 82h
        bmAttributes:     03h
        wMaxPacketSize:   5
        bInterval:        10
        bRefresh:         0
        bSynchAddress:    0
```