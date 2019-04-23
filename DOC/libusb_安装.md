# libusb

## 参考网址

* website：http://libusb.info/
* API：http://libusb.sourceforge.net/api-1.0/
* download：https://github.com/libusb/libusb
* mailing list：http://mailing-list.libusb.info
* libusb test demo：https://github.com/crazybaoli/libusb-test

## 编译安装

* 解压
  * tar xvf libusb-1.0.22.tar.bz2 
* 编译
  * ./configure && make && sudo make install

## 错误

* 运行时错误：undefined symbol: libusb_set_option
  * sudo ln -sf /usr/local/lib/libusb-1.0.so /lib/x86_64-linux-gnu/libusb-1.0.so.0
