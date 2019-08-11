/**
 * @file showlist.cpp
 * @author ZhengPengqiao (157510312@qq.com)
 * @brief 显示usb列表
 * @version 0.1
 * @date 2019-04-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>  
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <libusb.h>
#include "usbshow.h"

using namespace std;

/**
 * @brief 默认设备的VID,PID
 * 
 */
#define VID 0x093a
#define PID 0x2521


/**
 * @brief 帮助函数
 * 
 */
void help(void)
{
    printf("usage: libusb-test [-v vid] [-p pid] [-h] [-m mode] \n");
    printf("   -h      : display usage\n");
    printf("   -m      : 显示模式,(0:显示所有usb设备, 1:显示指定设备详细信息)\n");
    printf("   -v      : 默认设备的VID\n");
    printf("   -p      : 默认设备的PID\n"); 

    return;  
 
}

int main(int argc, char **argv)
{

    int opt;
    int mode = 0;
    int vid = VID;
    int pid = PID;

    //命令行参数解析
    while((opt = getopt(argc, argv, "hv:p:m:")) != -1)
    {
        switch(opt)
        {
            case 'v' :
                vid = str2hex(optarg);
                break;
            case 'p' :
                pid = str2hex(optarg);
                break;
            case 'm' :
                mode = atoi(optarg);
            break;
            case 'h' :
                help();
                return 0;
            default  :
                printf("unkonw option.\n");
                help();
                return 0;
        }
    }
    
    switch( mode )
    {
        case 0:
            list_devices();
        break;
        case 1:
            list_device_info(vid, pid);
        break;
        default:
            list_devices();
        break;
    }

    return 0;
}
    