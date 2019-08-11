#ifndef __USBSHOW__
#define __USBSHOW__
/**
 * @file usbshow.h
 * @author ZhengPengqiao (157510312@qq.com)
 * @brief 供显示usb设备信息的一些函数
 * @version 0.1
 * @date 2019-04-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief 打印设备列表
 * 
 * @param devs 
 */
void print_devs(libusb_device **devs);


/**
 * @brief : 将字符串(16进制数字)，变为数字（int）
 * 
 * @param hex : 等待解析的16进数值的制字符串
 * @return int ： 返回解析后的数值
 */
int str2hex(char *hex);

/**
 * @brief 列出所有设备
 * 显示设备的信息包括：bus number. device number, vid, pid, product info
 * @return int 0:OK, 其他:Err
 */
int list_devices(void);

/**
 * @brief 显示指定设备的详细信息
 * 
 * @param vid : 指定设备的vid
 * @param pid : 指定设备的pid
 * @return int : 0：OK, 1:Err
 */
int list_device_info(int vid, int pid);


/**
 * @brief 打印指定设备的信息
 * 
 * @param dev ： 需要打印信息的设备
 * @return int ： 0：Ok, -1:Err
 */
int print_descriptor(libusb_device *dev);

#endif //__USBSHOW__