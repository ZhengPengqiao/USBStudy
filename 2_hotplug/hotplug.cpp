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
#include <pthread.h>

using namespace std;

/**
 * @brief 默认设备的VID,PID
 * 
 */
#define VID 0x093a
#define PID 0x2521


/**
 * @brief : 将字符串(16进制数字)，变为数字（int）
 * 
 * @param hex : 等待解析的16进数值的制字符串
 * @return int ： 返回解析后的数值
 */
int str2hex(char *hex)
{
    int sum = 0;
    int tmp = 0;
    char hex_str[5];

    if (strlen(hex) == 6)
        memcpy(hex_str, &hex[2], 4);
    else
        memcpy(hex_str, hex, 4);

    for (int i = 0; i < 4; i++)
    {
        tmp = hex_str[i] - (((hex_str[i] >= '0') && (hex_str[i] <= '9')) ? '0' : ((hex_str[i] >= 'A') && (hex_str[i] <= 'Z')) ? 'A' - 10 : 'a' - 10);
        sum += tmp * pow(16, 3 - i);
    }

    return sum;
}

/**
 * @brief 帮助函数
 * 
 */
void help(void)
{
    printf("usage: libusb-test [-v vid] [-p pid] [-h] \n");
    printf("   -h      : display usage\n");
    printf("   -m      : 显示模式,(0:监听所以设备, 1:监听指定设备)\n");
    printf("   -v      : 默认设备的VID\n");
    printf("   -p      : 默认设备的PID\n");

    return;
}



static int LIBUSB_CALL usb_arrived_callback(struct libusb_context *ctx, 
    struct libusb_device *dev, libusb_hotplug_event event, void *userdata)
{
    struct libusb_device_descriptor desc;

    libusb_get_device_descriptor(dev, &desc);

    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event)
    {
        printf("ADD: usb device attached: %04x:%04x\n", desc.idVendor, desc.idProduct);
        printf("    CLASS(0x%x) SUBCLASS(0x%x) PROTOCOL(0x%x)\n",
            desc.bDeviceClass, desc.bDeviceSubClass, desc.bDeviceProtocol);
    }
    else
    {
        printf("ADD: unsupport event: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }


    return 0;
}

static int LIBUSB_CALL usb_left_callback(struct libusb_context *ctx, 
    struct libusb_device *dev, libusb_hotplug_event event, void *userdata)
{
    struct libusb_device_descriptor desc;

    libusb_get_device_descriptor(dev, &desc);

    if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event)
    {
        printf("LEFT: usb device removed: %04x:%04x\n", desc.idVendor, desc.idProduct);
        printf("    CLASS(0x%x) SUBCLASS(0x%x) PROTOCOL(0x%x)\n",
            desc.bDeviceClass, desc.bDeviceSubClass, desc.bDeviceProtocol);
    }
    else
    {
        printf("LEFT: unsupport event: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }


    return 0;
}


//usb hotplugin monitor thread
void * usb_monitor_thread(void *arg) 
{ 
    libusb_context *ctx = (libusb_context *)arg;

    printf("usb monitor thread started.\n");

    int r = 0;
    while (1) {
        r = libusb_handle_events(ctx);
        if (r < 0)
        {
            printf("libusb_handle_events() failed: %s\n", libusb_error_name(r));
        }
    }  

}


int main(int argc, char **argv)
{

    int opt;
    int vid = VID;
    int pid = PID;
    int ret;
    int mode = 0;
    libusb_context *ctx = NULL; //a libusb session
    libusb_hotplug_callback_handle usb_arrived_handle;
    libusb_hotplug_callback_handle usb_left_handle;
    pthread_t usb_monitor_thread_id;

    //命令行参数解析
    while ((opt = getopt(argc, argv, "hv:p:m:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            vid = str2hex(optarg);
            break;
        case 'p':
            pid = str2hex(optarg);
            break;
        case 'm' :
                mode = atoi(optarg);
            break;
        case 'h':
            help();
            return 0;
        default:
            printf("unkonw option.\n");
            help();
            return 0;
        }
    }

    //initialize a library session
    ret = libusb_init(&ctx);
    if (ret < 0)
    {
        printf("Init Error ret=%d\n", ret); //there was an error
        return -1;
    }

    //set verbosity level to LIBUSB_LOG_LEVEL_INFO, as suggested in the documentation
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);

    if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
    {
        printf("hotplug capabilites are not supported on this platform.\n");
        libusb_exit(NULL);
        return -1;
    }

    switch( mode )
    {
        case 0:
            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_arrived_callback, NULL, &usb_arrived_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb arrived callback\n");
                goto failure;
            }

            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_left_callback, NULL, &usb_left_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb left callback\n");
                goto failure;
            }
        break;
        case 1:
            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                LIBUSB_HOTPLUG_NO_FLAGS, vid, pid,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_arrived_callback, NULL, &usb_arrived_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb arrived callback\n");
                goto failure;
            }

            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                LIBUSB_HOTPLUG_NO_FLAGS, vid, pid,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_left_callback, NULL, &usb_left_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb left callback\n");
                goto failure;
            }
        break;
        default:
            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_arrived_callback, NULL, &usb_arrived_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb arrived callback\n");
                goto failure;
            }

            ret = libusb_hotplug_register_callback(ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                LIBUSB_HOTPLUG_NO_FLAGS, LIBUSB_HOTPLUG_MATCH_ANY, LIBUSB_HOTPLUG_MATCH_ANY,
                LIBUSB_HOTPLUG_MATCH_ANY, usb_left_callback, NULL, &usb_left_handle);
            if (LIBUSB_SUCCESS != ret) {
                printf("Error to register usb left callback\n");
                goto failure;
            }
        break;
    }

    //热插拔监听
    ret = pthread_create(&usb_monitor_thread_id, 0, usb_monitor_thread, ctx); 
    if(ret != 0 )
    {
        perror("usb_monitor_thread creation faild\n");
    } 

    while (1) {
        usleep(1000);
    }

    libusb_hotplug_deregister_callback(ctx, usb_arrived_handle);
    libusb_hotplug_deregister_callback(ctx, usb_left_handle);
    libusb_exit(ctx);
    return 0;

failure:
    libusb_exit(ctx);
    return EXIT_FAILURE;
}