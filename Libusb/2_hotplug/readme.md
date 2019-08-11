# hotplug

## 编译

* make

## 参数介绍

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/1_usblist$ sudo ./hotplug -h
    usage: libusb-test [-v vid] [-p pid] [-h] 
    -h      : display usage
    -m      : 显示模式,(0:监听所以设备, 1:监听指定设备)
    -v      : 默认设备的VID
    -p      : 默认设备的PID
```

## 执行结果

* 检测一个设备的热拔插

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/2_hotplug$ sudo ./hotplug -m 1
    usb monitor thread started.
    LEFT: usb device removed: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    LEFT: usb device removed: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
```

* 检测所以设备的热拔插

```C
    xxx@xxx-pc:~/WorkSpaces/USBStudy/2_hotplug$ sudo ./hotplug
    usb monitor thread started.
    LEFT: usb device removed: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    LEFT: usb device removed: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    LEFT: usb device removed: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    LEFT: usb device removed: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 1a2c:0c21
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    LEFT: usb device removed: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
    ADD: usb device attached: 093a:2521
        CLASS(0x0) SUBCLASS(0x0) PROTOCOL(0x0)
```