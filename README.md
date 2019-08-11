# USBStudy

USBStudy

* YSUSB : 优胜电子 YSUMA01-341A ----> ALL IN ONE多功能,USB转I2C/SPI/UART 适配器
  * ![allinone](YSUSB/allinone.jpg)

* Libusb:   从应用层使用libusb来操作设备
  * 1_usblist : 列出usb的设备,及查看指定设备的信息
  * 2_hotplug : 处理usb设备的热拔插事件
  * 3_usbmouse : 使用libusb在应用层处理mouse设备
  * 4_usbkeyboard : 使用libusb在应用层处理keyboard设备
  * libusb的安装:    Libusb/DOC/libusb_安装.md
  * libusb的api介绍: Libusb/DOC/libusb_api.md

* DOC:      USB的常用知识
  * 用户层查看信息: DOC/用户层usb.md
  * 抓取USB包:     DOC/Linux 抓USB包.md
