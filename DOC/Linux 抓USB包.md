# Linux 抓USB包

## 配置内核

```C
Device Driver   ---->
  [*] USB support  ---> 
  <M>     USB Monitor  
```

## 加载模块

```C
modprobe usbmon  后者  sudo insmod 路径/usbmon.ko
mount -t debugfs none_debugs /sys/kernel/debug
```

* 检查是否存在目录 /sys/kernel/debug/usb/usbmon
* ls /sys/kernel/debug/usb/usbmon
  * 0s  0u  1s  1t  1u  2s  2t  2u  3s  3t  3u
  * 如果总线号是1，则是1u，如果总线号是2，则是2u，依次类推。特殊情况是0u表示监听所有的

## lsusb 确认需要监听的usb设备的pid 和vid

* cat /sys/kernel/debug/usb/devices

```C
   # cat /sys/kernel/debug/usb/devices 确定你要监视的usb设备所在总线号和设备号
    T:  Bus=03 Lev=01 Prnt=01 Port=03 Cnt=02 Dev#= 82 Spd=1.5  MxCh= 0
    D:  Ver= 1.10 Cls=00(>ifc ) Sub=00 Prot=00 MxPS= 8 #Cfgs=  1
    P:  Vendor=1a2c ProdID=0c21 Rev= 1.10
    S:  Manufacturer=USB
    S:  Product=USB Keyboard
    C:* #Ifs= 2 Cfg#= 1 Atr=a0 MxPwr=100mA
    I:* If#= 0 Alt= 0 #EPs= 1 Cls=03(HID  ) Sub=01 Prot=01 Driver=(none)
    E:  Ad=81(I) Atr=03(Int.) MxPS=   8 Ivl=10ms
    I:* If#= 1 Alt= 0 #EPs= 1 Cls=03(HID  ) Sub=01 Prot=02 Driver=(none)
    E:  Ad=82(I) Atr=03(Int.) MxPS=   5 Ivl=10ms
```

## 抓包：

* cat /sys/kernel/debug/usb/usbmon/2u > ./log.txt
* 这里需要注意，由于我们的这个抓包命令，只能指定是抓哪个总线上，但同一个总线通常会有很多usb设备的，
如果我们只是关注特定的某个usb设备的话，我自己就需要留意设备地址字段，通过这个字段，我们就可以区分这个传输是不是我们要监听的设备发送出来的。

## 还有一个tcpdump 工具抓出来的包可以结合wireshark 工具来查看

* 下载tcpdump工具
* wireshark ,如果嵌入式设备不方面弄这个程序，可以在宿主机上装wireshark

```C
tcpdump -D
1.usbmon1 (USB bus number 1)
2.usbmon2 (USB bus number 2)
3.eth4
4.any (Pseudo-device that captures on all interfaces)
5.lo
```

## 我们这里抓取usb2

* tcpdump -i usbmon2 -w /data/usblog.pcap &
* killall tcpdump
* wireshark usblog.pcap
