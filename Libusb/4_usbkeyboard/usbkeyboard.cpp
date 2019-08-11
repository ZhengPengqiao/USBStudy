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
#define VID 0x1a2c
#define PID 0x0c21

 
struct UserDevice{

    uint8_t bnum;   //获取usb设备总线号
    uint8_t dnum;   //获取usb设备端口号
    libusb_device_handle *dev_handle; //a device handle
	libusb_device *dev;
    struct libusb_device_descriptor desc;
    struct libusb_config_descriptor *config;

	/*Device descriptor*/

    /** USB-IF vendor ID */
	uint16_t idVendor;
	/** USB-IF product ID */
	uint16_t idProduct;
 
	/*Interface descriptor*/
	/** USB-IF class code for this interface. See \ref libusb_class_code. */
	uint8_t  bInterfaceClass;
	/** USB-IF subclass code for this interface, qualified by the bInterfaceClass value */
	uint8_t  bInterfaceSubClass;
 
	/*save parameter*/
	u_int8_t bInEndpointAddress;
	u_int8_t bInEndpointMaxPacketSize;
	uint8_t  bInInterfaceNumber;
	u_int8_t bOutEndpointAddress;
	u_int8_t bOutEndpointMaxPacketSize;
	uint8_t  bOutInterfaceNumber;

    /* ctrl parameter */
    int quitflag;
    int pquitflag;
    int g_no_device_flag;
    libusb_context *ctx; //a libusb session
    libusb_hotplug_callback_handle usb_arrived_handle;
    libusb_hotplug_callback_handle usb_left_handle;
};


struct UserDevice userDevice;

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
    printf("usage: libusb-test [-v idVendor] [-p idProduct] [-h] \n");
    printf("   -h      : display usage\n");
    printf("   -m      : 显示模式,(0:显示原始数据， 1:显示解析数据)\n");
    printf("   -v      : 默认设备的VID\n");
    printf("   -p      : 默认设备的PID\n");

    return;
}

/**
 * @brief 设备移除函数
 * 
 * @param ctx : USB上下文
 * @param dev ： USB设备
 * @param event ： 当前事件
 * @param userdata ： 用户数据
 * @return int ： 0：Ok
 */
static int LIBUSB_CALL usb_arrived_callback(struct libusb_context *ctx,
                                            struct libusb_device *dev, libusb_hotplug_event event, void *userdata)
{
    int ret;
    struct libusb_device_descriptor desc;

    libusb_get_device_descriptor(dev, &desc);

    if (LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED == event)
    {
        printf("ADD: usb device attached: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }
    else
    {
        printf("ADD: unsupport event: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }

    if (userDevice.dev_handle)
    {
        libusb_close(userDevice.dev_handle);
        userDevice.dev_handle = NULL;
    }

    ret = libusb_open(dev, &userDevice.dev_handle);
    if (LIBUSB_SUCCESS != ret)
    {
        printf("error opening device.\n");
    }
    else
    {
        if (libusb_kernel_driver_active(userDevice.dev_handle, userDevice.bInInterfaceNumber) == 1)
        { //find out if kernel driver is attached
            printf("kernel driver active\n");
            if (libusb_detach_kernel_driver(userDevice.dev_handle, userDevice.bInInterfaceNumber) == 0) //detach it
                printf("kernel driver detach\n");
        }
        // 为指定的设备申请接口
        ret = libusb_claim_interface(userDevice.dev_handle, userDevice.bInInterfaceNumber);
        if (ret < 0)
        {
            printf("Cannot Claim Interface userDevice.bInInterfaceNumber=0x%02x\n", userDevice.bInInterfaceNumber);
        }
        else
        {
            printf("Claimed Interfaceuser Device.bInInterfaceNumber=0x%02x\n", userDevice.bInInterfaceNumber);
        }


        if (libusb_kernel_driver_active(userDevice.dev_handle, userDevice.bOutInterfaceNumber) == 1)
        { //find out if kernel driver is attached
            printf("kernel driver active\n");
            if (libusb_detach_kernel_driver(userDevice.dev_handle, userDevice.bOutInterfaceNumber) == 0) //detach it
                printf("kernel driver detach\n");
        }
        // 为指定的设备申请接口
        ret = libusb_claim_interface(userDevice.dev_handle, userDevice.bOutInterfaceNumber);
        if (ret < 0)
        {
            printf("Cannot Claim Interface userDevice.bInInterfaceNumber=0x%02x\n", userDevice.bOutInterfaceNumber);
        }
        else
        {
            printf("Claimed Interfaceuser Device.bInInterfaceNumber=0x%02x\n", userDevice.bOutInterfaceNumber);
        }
    }
    userDevice.g_no_device_flag = 0;

    return 0;
}

/**
 * @brief 设备移除函数
 * 
 * @param ctx : USB上下文
 * @param dev ： USB设备
 * @param event ： 当前事件
 * @param userdata ： 用户数据
 * @return int ： 0：Ok
 */
static int LIBUSB_CALL usb_left_callback(struct libusb_context *ctx,
                                         struct libusb_device *dev, libusb_hotplug_event event, void *userdata)
{
    struct libusb_device_descriptor desc;

    libusb_get_device_descriptor(dev, &desc);

    if (LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT == event)
    {
        printf("LEFT: usb device removed: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }
    else
    {
        printf("LEFT: unsupport event: %04x:%04x\n", desc.idVendor, desc.idProduct);
    }

    if ( userDevice.dev_handle != NULL )
    {
        userDevice.g_no_device_flag = 1;
        //TODO: Device handle closed while transfer was still being processed, but the device is still connected as far as we know
        libusb_close(userDevice.dev_handle);
        userDevice.dev_handle = NULL;
    }

    return 0;
}

/**
 * @brief 线程信号监听函数
 * 
 * @param sign : 传到这个函数的信号值
 */
void thread_fun(int sign)
{
    userDevice.pquitflag = 1;
    printf("收到退出信号，等待thread退出\n");
}

/**
 * @brief 
 * 
 * @param arg 
 * @return void* 
 */
void *usb_monitor_thread(void *arg)
{
    int ret = 0;
    struct timeval tv;
    libusb_context *ctx = (libusb_context *)arg;

    signal(SIGQUIT, thread_fun);
    printf("usb monitor thread started.\n");
    
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    while (!userDevice.pquitflag)
    {
        //定义1s中超时
        ret = libusb_handle_events_timeout_completed(ctx, &tv, NULL);
        if (ret < 0 && !userDevice.pquitflag)
        {
            printf("libusb_handle_events() failed: %s\n", libusb_error_name(ret));
        }
    }

    printf("thread收到退出信号，完成退出\n");
    return 0;
}


/**
 * @brief 向键盘发送状态信息
 * @param status : 发送状态
 * 
 * @return int 0:Ok, -1:Err
 */
int sendData(unsigned char status)
{
    unsigned char datain[6];
    int ret;
    int size = 5;

    switch(status)
    {
        case 1:
            datain[0] = 0x21;
            datain[1] = 0x09;
            datain[2] = 0x02;
            datain[3] = 0x00;
            datain[4] = 0x01;
            datain[5] = '\0';            
        break;
        case 2:
            datain[0] = 0x21;
            datain[1] = 0x09;
            datain[2] = 0x02;
            datain[3] = 0x00;
            datain[4] = 0x03;
            datain[5] = '\0';            
        break;
        default:
            printf("sendData() don't know send this msg\n");
            return 0;
            break;
    }


    printf("userDevice.bOutEndpointAddress=0x%02x, userDevice.bOutEndpointMaxPacketSize=0x%02x\n", userDevice.bOutEndpointAddress, userDevice.bOutEndpointMaxPacketSize);
    ret = libusb_interrupt_transfer(userDevice.dev_handle, userDevice.bOutEndpointAddress, datain, 
        userDevice.bOutEndpointMaxPacketSize, &size, 1000);
    if (ret == LIBUSB_SUCCESS)
    {
        printf("interrupt ep sed success\n");
    }
    else if(ret == LIBUSB_ERROR_IO)
    {
        printf("interrupt ep sed faild, err: %s\n", libusb_error_name(ret));
    }
    else if( ret == LIBUSB_ERROR_NO_DEVICE )
    {
        //监测LIBUSB_ERROR_NO_DEVICE防止libusb_close时出错
        printf("interrupt ep sed faild, err: %s\n", libusb_error_name(ret));
        userDevice.g_no_device_flag = 1; //防止一直输出err
    }
    else
    {
        printf("interrupt ep sed faild, err: %s\n", libusb_error_name(ret));
    }
    return 0;
}
/**
 * @brief 主程序信号监听函数
 * 
 * @param sign : 传到这个函数的信号值
 */
void exit_fun(int sign)
{
    userDevice.quitflag = 1;
    printf("收到退出信号，等待main退出\n");
}

/**
 * @brief Get the Key Name object
 * 
 * @param code  : 按键值
 * @param str  ： 返回的按键名
 * @return int : 0:Ok, -1:Err
 */
int getKeyName(char code, char *str)
{
    if( code >= 3 && code <= 29 )
    {
        str[0] = code-4+'a';
        str[1] = '\0';
        return 0;
    }
    else if( code >= 0x1e && code <= 0x26 )
    {
        str[0] = code-0x1e + '1';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x27 )
    {
        str[0] = '0';
        str[1] = '\0';
        return 0;
    }
    else if( code >= 0x59 && code <= 0x61 )
    {
        str[0] = code-0x59 + '1';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x62 )
    {
        str[0] = '0';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x53 )
    {
        str[0] = 'N';
        str[1] = 'L';
        str[2] = '\0';
        sendData(1);
        return 0;
    }
    else if( code == 0x54 )
    {
        str[0] = '/';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x55 )
    {
        str[0] = '*';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x56 )
    {
        str[0] = '-';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x57 )
    {
        str[0] = '+';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x58 )
    {
        str[0] = 'E';
        str[1] = 'T';
        str[2] = '\0';
        return 0;
    }
    else if( code >= 0x3a && code <= 0x42 )
    {
        str[0] = 'F';
        str[1] = code-0x3a + '1';
        str[2] = '\0';
        return 0;
    }
    else if( code >= 0x42 && code <= 0x45 )
    {
        str[0] = 'F';
        str[1] = code-0x43 + 'A';
        str[2] = '\0';
        return 0;
    }
    else if( code == 0x39 )
    {
        str[0] = 'C';
        str[1] = 'L';
        str[2] = '\0';
        sendData(2);
        return 0;
    }
    else if( code == 0x2C )
    {
        str[0] = 'S';
        str[1] = 'P';
        str[2] = '\0';
        return 0;
    }
    else if( code == 0x29 )
    {
        str[0] = 'E';
        str[1] = 'S';
        str[2] = '\0';
        return 0;
    }
    else if( code == 0x2b )
    {
        str[0] = 'T';
        str[1] = 'B';
        str[2] = '\0';
        return 0;
    }
    else if( code == 0x35 )
    {
        str[0] = '`';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x2a )
    {
        str[0] = 'B';
        str[1] = 'K';
        str[2] = '\0';
        return 0;
    }
    else if( code == 0x2d )
    {
        str[0] = '-';
        str[1] = '\0';
        return 0;
    }
    else if( code == 0x2e )
    {
        str[0] = '+';
        str[1] = '\0';
        return 0;
    }

    str[0] = '-';
    str[1] = '-';
    str[2] = '\0';
    return 0;
}


/**
 * @brief 打印解析数据
 * 
 * 键盘发送给PC的数据每次8个字节
 * BYTE1 BYTE2 BYTE3 BYTE4 BYTE5 BYTE6 BYTE7 BYTE8
 * 定义分别是：
 * BYTE1 --
 *        |--bit0:   Left Control是否按下，按下为1 
 *        |--bit1:   Left Shift  是否按下，按下为1 
 *        |--bit2:   Left Alt    是否按下，按下为1 
 *        |--bit3:   Left GUI    是否按下，按下为1 
 *        |--bit4:   Right Control是否按下，按下为1  
 *        |--bit5:   Right Shift 是否按下，按下为1 
 *        |--bit6:   Right Alt   是否按下，按下为1 
 *        |--bit7:   Right GUI   是否按下，按下为1 
 * BYTE2 -- 暂不清楚，有的地方说是保留位
 * BYTE3--BYTE8 -- 这六个为普通按键
 * 
 * @param data : 从设备接收的数据
 * @param size : 从设备接收数据的长度
 * @return int ： 0：Ok, -1：Err
 */
int print_keyboardInfo(unsigned char *data, int size)
{
    char str[1024];
    char name[5];
    int len = 0;

    if( ( data[0] & (1<<0) ) != 0 )
    {
        len += sprintf(str, "\tLC:按下");
    }
    else
    {
        len += sprintf(str, "\tLC:松开");
    }
    
    if( ( data[0] & (1<<1) ) != 0 )
    {
        len += sprintf(str+len, "\tLS:按下");
    }
    else
    {
        len += sprintf(str+len, "\tLS:松开");
    }

    if( ( data[0] & (1<<2) ) != 0 )
    {
        len += sprintf(str+len, "\tLA:按下");
    }
    else
    {
        len += sprintf(str+len, "\tLA:松开");
    }
    
    if( ( data[0] & (1<<3) ) != 0 )
    {
        len += sprintf(str+len, "\tLG:按下");
    }
    else
    {
        len += sprintf(str+len, "\tLG:松开");
    }

    if( ( data[0] & (1<<4) ) != 0 )
    {
        len += sprintf(str+len, "\tRC:按下");
    }
    else
    {
        len += sprintf(str+len, "\tRC:松开");
    }

    if( ( data[0] & (1<<5) ) != 0 )
    {
        len += sprintf(str+len, "\tRS:按下");
    }
    else
    {
        len += sprintf(str+len, "\tRS:松开");
    }

    if( ( data[0] & (1<<6) ) != 0 )
    {
        len += sprintf(str+len, "\tRA:按下");
    }
    else
    {
        len += sprintf(str+len, "\tRA:松开");
    }

    if( ( data[0] & (1<<7) ) != 0 )
    {
        len += sprintf(str+len, "\tRG:按下");
    }
    else
    {
        len += sprintf(str+len, "\tRG:松开");
    }

    getKeyName(data[1], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[2], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[3], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[4], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[5], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[6], name);
    len += sprintf(str+len, " %s", name );
    getKeyName(data[7], name);
    len += sprintf(str+len, " %s", name );

    printf("size:%d : %s\n ", size, str);
    return 0;
}

/**
 * @brief 打印解析数据
 * 
 * @param data : 从设备接收的数据
 * @param size : 从设备接收数据的长度
 * @return int ： 0：Ok, -1：Err
 */
int print_keyboardData(unsigned char *data, int size)
{
    printf("size:%d : data:", size);
    for (int j = 0; j < size; j++)
    {
        printf("%02x ", (unsigned char)(data[j]));
    }
    printf("\n");

    return 0;
}

int main(int argc, char **argv)
{

    int opt;
    int ret;
    int mode = 0;
    int hotplug_enable = 1; //默认打开
    void *status;
    pthread_t usb_monitor_thread_id;

    memset(&userDevice, 0, sizeof(userDevice));

    userDevice.idVendor = VID;
    userDevice.idProduct = PID;

    //命令行参数解析
    while ((opt = getopt(argc, argv, "hv:p:m:")) != -1)
    {
        switch (opt)
        {
        case 'v':
            userDevice.idVendor = str2hex(optarg);
            break;
        case 'p':
            userDevice.idProduct = str2hex(optarg);
            break;
        case 'm':
            mode = str2hex(optarg);
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

    signal(SIGKILL, exit_fun);
    signal(SIGINT, exit_fun);
    signal(SIGQUIT, exit_fun);

    if( mode == 0 )
    {
        printf("打印获取鼠标的<原始数据>\n");
    }
    else
    {
        printf("打印获取鼠标的<解析数据> x,y出事坐标为(0,0)\n");
    }

    //initialize a library session
    ret = libusb_init(&userDevice.ctx);
    if (ret < 0)
    {
        printf("Init Error ret=%d\n", ret); //there was an error
        return EXIT_FAILURE;
    }

    //set verbosity level to LIBUSB_LOG_LEVEL_INFO, as suggested in the documentation
    libusb_set_option(userDevice.ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);

    //判断是否支持热拔插
    if (!libusb_has_capability(LIBUSB_CAP_HAS_HOTPLUG))
    {
        hotplug_enable = 0; //不支持热拔插功能
        printf("hotplug capabilites are not supported on this platform.\n");
    }
    else
    {
        ret = libusb_hotplug_register_callback(userDevice.ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED,
                            LIBUSB_HOTPLUG_NO_FLAGS, userDevice.idVendor, userDevice.idProduct,
                            LIBUSB_HOTPLUG_MATCH_ANY, usb_arrived_callback, 
                            NULL, &userDevice.usb_arrived_handle);
        if (LIBUSB_SUCCESS != ret)
        {
            printf("Error to register usb arrived callback\n");
            goto exit_1;
        }
        else
        {
            printf("Success to register usb arrived callback\n");
        }

        ret = libusb_hotplug_register_callback(userDevice.ctx, LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                            LIBUSB_HOTPLUG_NO_FLAGS, userDevice.idVendor, userDevice.idProduct,
                            LIBUSB_HOTPLUG_MATCH_ANY, usb_left_callback, 
                            NULL, &userDevice.usb_left_handle);
        if (LIBUSB_SUCCESS != ret)
        {
            printf("Error to register usb left callback\n");
            goto exit_2;
        }
        else
        {
            printf("Success to register usb left callback\n");
        }

        //热插拔监听
        ret = pthread_create(&usb_monitor_thread_id, 0, usb_monitor_thread, userDevice.ctx);
        if (ret != 0)
        {
            perror("usb_monitor_thread creation faild\n");
            goto exit_3;
        }
        else
        {
            perror("usb_monitor_thread creation Success\n");
        }
    }

    userDevice.dev_handle = libusb_open_device_with_vid_pid(userDevice.ctx, 
            userDevice.idVendor, userDevice.idProduct); //open mouse
    if (userDevice.dev_handle == NULL)
    {
        printf("Cannot open device \n");
        goto exit_4;
    }

    userDevice.dev = libusb_get_device(userDevice.dev_handle);
    userDevice.bnum = libusb_get_bus_number(userDevice.dev);      //获取usb设备总线号
    userDevice.dnum = libusb_get_device_address(userDevice.dev);  //获取usb设备端口号

    printf("Device(idVendor=%d, idProduct=%d) (%d:%d) Opened\n",  
            userDevice.idVendor, userDevice.idProduct, userDevice.bnum, userDevice.dnum);

    //得到设备的描述描述
    ret = libusb_get_device_descriptor(userDevice.dev, &userDevice.desc);
    if (ret < 0)
    {
        printf("failed to get device descriptor\n");
        goto exit_4;
    }

    //得到设备的第0个配置描述
    ret = libusb_get_config_descriptor(userDevice.dev, 0, &userDevice.config);
    if (LIBUSB_SUCCESS != ret)
    {
        printf("Couldn't retrieve descriptors\n");
        goto exit_4;
    }

    printf("userDevice.config->bNumInterfaces=%d\n", userDevice.config->bNumInterfaces);
    if( userDevice.config->bNumInterfaces >= 1 )
    {
        userDevice.bInEndpointAddress = userDevice.config->interface[0].altsetting[0].endpoint[0].bEndpointAddress;
        userDevice.bInEndpointMaxPacketSize = userDevice.config->interface[0].altsetting[0].endpoint[0].wMaxPacketSize;
        userDevice.bInInterfaceNumber = userDevice.config->interface[0].altsetting[0].bInterfaceNumber;
        printf("bInInterfaceNumber=0x%02x, bInEndpointAddress=0x%04x, bInEndpointMaxPacketSize=0x%04x\n",  
            userDevice.bInInterfaceNumber, userDevice.bInEndpointAddress, userDevice.bInEndpointMaxPacketSize);   

        // 确定指定接口的内核驱动程序是否已经激活。如果一个内核驱动程序是激活的，
        // libusb_claim_interface调用的会失败
        if (libusb_kernel_driver_active(userDevice.dev_handle, userDevice.bInInterfaceNumber) == 1)
        {
            printf("Kernel Driver Active\n");
            // 卸载指定接口的内核驱动程序。如果一个内核驱动程序是激活的，必须先调用这个函数，
            // 再调用libusb_claim_interface
            if (libusb_detach_kernel_driver(userDevice.dev_handle, userDevice.bInInterfaceNumber) == 0) //detach it
                printf("Kernel Driver Detached!\n");
        }
    }
    if( userDevice.config->bNumInterfaces >= 2 )
    {
        userDevice.bOutEndpointAddress = userDevice.config->interface[1].altsetting[0].endpoint[0].bEndpointAddress;
        userDevice.bOutEndpointMaxPacketSize = userDevice.config->interface[1].altsetting[0].endpoint[0].wMaxPacketSize;
        userDevice.bOutInterfaceNumber = userDevice.config->interface[1].altsetting[0].bInterfaceNumber;
        printf("bOutInterfaceNumber=0x%02x, bOutEndpointAddress=0x%04x, bOutEndpointMaxPacketSize=0x%04x\n",  
            userDevice.bOutInterfaceNumber, userDevice.bOutEndpointAddress, userDevice.bOutEndpointMaxPacketSize);

        // 确定指定接口的内核驱动程序是否已经激活。如果一个内核驱动程序是激活的，
        // libusb_claim_interface调用的会失败
        if (libusb_kernel_driver_active(userDevice.dev_handle, userDevice.bOutInterfaceNumber) == 1)
        {
            printf("Kernel Driver Active\n");
            // 卸载指定接口的内核驱动程序。如果一个内核驱动程序是激活的，必须先调用这个函数，
            // 再调用libusb_claim_interface
            if (libusb_detach_kernel_driver(userDevice.dev_handle, userDevice.bOutInterfaceNumber) == 0) //detach it
                printf("Kernel Driver Detached!\n");
        }
    }

    if( userDevice.config->bNumInterfaces >= 1 )
    {
        // 为指定的设备申请接口
        ret = libusb_claim_interface(userDevice.dev_handle, userDevice.bInInterfaceNumber);
        if (ret < 0)
        {
            printf("Cannot Claim Interface userDevice.bInInterfaceNumber=0x%02x\n", userDevice.bInInterfaceNumber);
            goto exit_5;
        }
        printf("Claimed Interface userDevice.bInInterfaceNumber=0x%02x\n", userDevice.bInInterfaceNumber);

    }
    if( userDevice.config->bNumInterfaces >= 2 )
    {
        // 为指定的设备申请接口
        ret = libusb_claim_interface(userDevice.dev_handle, userDevice.bOutInterfaceNumber);
        if (ret < 0)
        {
            printf("Cannot Claim Interface userDevice.bOutInterfaceNumber=0x%02x\n", userDevice.bOutInterfaceNumber);
            goto exit_5;
        }
        printf("Claimed Interface userDevice.bOutInterfaceNumber=0x%02x\n", userDevice.bOutInterfaceNumber);
    }

    while (!userDevice.quitflag)
    {
        int size;
        unsigned char datain[1024] = "\0";
        if( userDevice.dev_handle == NULL || userDevice.g_no_device_flag == 1)
        {
            usleep(500 * 1000);
            continue;
        }
        
        ret = libusb_interrupt_transfer(userDevice.dev_handle, userDevice.bInEndpointAddress, datain, 
            userDevice.bInEndpointMaxPacketSize, &size, 1000);
        if (ret == LIBUSB_SUCCESS)
        {
            if( mode == 0 )
            {
                print_keyboardData(datain, size);
            }
            else
            {
                print_keyboardInfo(datain, size);
            }
        }
        else if(ret == LIBUSB_ERROR_IO)
        {
            printf("interrupt ep rev faild, err: %s\n", libusb_error_name(ret));
        }
        else if( ret == LIBUSB_ERROR_NO_DEVICE )
        {
            //监测LIBUSB_ERROR_NO_DEVICE防止libusb_close时出错
            printf("interrupt ep rev faild, err: %s\n", libusb_error_name(ret));
            userDevice.g_no_device_flag = 1; //防止一直输出err
        }
    }

    //释放config
    libusb_free_config_descriptor(userDevice.config);

    if( userDevice.config->bNumInterfaces >= 1 )
    {
        //释放之前为指定的设备申请接口，注意这个函数只是释放接口，不会重新加载内核驱动
        ret = libusb_release_interface(userDevice.dev_handle, userDevice.bInInterfaceNumber);
        if (ret != 0)
        {
            printf("Cannot Release Interface\n");
        }
        printf("Released Interface\n");

        //加载指定接口的内核驱动
        libusb_attach_kernel_driver(userDevice.dev_handle, userDevice.bInInterfaceNumber);
    }
    if( userDevice.config->bNumInterfaces >= 2 )
    {
        //释放之前为指定的设备申请接口，注意这个函数只是释放接口，不会重新加载内核驱动
        ret = libusb_release_interface(userDevice.dev_handle, userDevice.bOutInterfaceNumber);
        if (ret != 0)
        {
            printf("Cannot Release Interface\n");
        }
        printf("Released Interface\n");
        //加载指定接口的内核驱动
        libusb_attach_kernel_driver(userDevice.dev_handle, userDevice.bOutInterfaceNumber);
    }

    libusb_close(userDevice.dev_handle);

    if (hotplug_enable == 1) //判断是否处理热拔插事件
    {
        //发出SIGQUIT信号，让线程退出
        pthread_kill(usb_monitor_thread_id, SIGQUIT);
        //等待线程tid执行完毕，这里阻塞。
        pthread_join(usb_monitor_thread_id, &status);

        libusb_hotplug_deregister_callback(userDevice.ctx, userDevice.usb_arrived_handle);
        libusb_hotplug_deregister_callback(userDevice.ctx, userDevice.usb_left_handle);
    }
    libusb_exit(userDevice.ctx);
    printf("main收到退出信号，完成退出\n");
    return 0;

exit_5:
    libusb_free_config_descriptor(userDevice.config);
    //加载指定接口的内核驱动
    libusb_attach_kernel_driver(userDevice.dev_handle, userDevice.bInInterfaceNumber);
    libusb_close(userDevice.dev_handle);
exit_4:
    //发出SIGQUIT信号，让线程退出
    pthread_kill(usb_monitor_thread_id, SIGQUIT);
    //等待线程tid执行完毕，这里阻塞。
    pthread_join(usb_monitor_thread_id, &status);
exit_3:
    libusb_hotplug_deregister_callback(userDevice.ctx, userDevice.usb_left_handle);
exit_2:
    libusb_hotplug_deregister_callback(userDevice.ctx, userDevice.usb_arrived_handle);
exit_1:
    libusb_exit(userDevice.ctx);
    return EXIT_FAILURE;
}