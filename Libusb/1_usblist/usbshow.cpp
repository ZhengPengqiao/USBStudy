/**
 * @file usbshow.cpp
 * @author ZhengPengqiao (157510312@qq.com)
 * @brief 供显示usb设备信息的一些函数
 * @version 0.1
 * @date 2019-04-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "usbshow.h"

/**
 * @brief 打印设备列表
 * 
 * @param devs 
 */
void print_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0;
    libusb_device_handle *handle = NULL;
    unsigned char string[256];

    while ((dev = devs[i++]) != NULL)
    {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0)
        {
            printf("failed to get device descriptor\n");
            return;
        }

        printf("bus: %03d device: %03d, VID: %04x PID: %04x",
               libusb_get_bus_number(dev), libusb_get_device_address(dev), desc.idVendor, desc.idProduct);

        int ret = libusb_open(dev, &handle);
        if (LIBUSB_SUCCESS == ret)
        {
            if (desc.iProduct)
            {
                ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string)); //显示产品信息
                if (ret > 0)
                    printf(", %s", string);
            }
        }
        printf("\n");

        if (handle)
            libusb_close(handle);
    }
}

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
 * @brief 列出所有设备
 * 显示设备的信息包括：bus number. device number, vid, pid, product info
 * @return int LIBUSB_SUCCESS:OK, 其他:Err
 */
int list_devices(void)
{
    int ret;
    ssize_t num_devs;
    libusb_context *ctx = NULL; //a libusb session
    libusb_device **devs;       //usb设备

    //initialize a library session
    ret = libusb_init(&ctx);
    if (ret < 0)
    {
        printf("Init Error ret=%d\n", ret); //there was an error
        return -1;
    }

    //set verbosity level to LIBUSB_LOG_LEVEL_INFO, as suggested in the documentation
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);

    num_devs = libusb_get_device_list(ctx, &devs);
    if (num_devs < 0)
    {
        return (int)num_devs;
    }

    print_devs(devs);

    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);
    return LIBUSB_SUCCESS;
}

/**
 * @brief 显示指定设备的详细信息
 * 
 * @param vid : 指定设备的vid
 * @param pid : 指定设备的pid
 * @return int : LIBUSB_SUCCESS：OK, 1:Err
 */
int list_device_info(int vid, int pid)
{
    libusb_device **devs;
    libusb_device *found = NULL;
    libusb_device *dev;
    libusb_context *ctx = NULL; //a libusb session
    ssize_t num_devs;
    int ret, i;

    //initialize a library session
    ret = libusb_init(&ctx);
    if (ret < 0)
    {
        printf("Init Error ret=%d\n", ret); //there was an error
        return -1;
    }

    //set verbosity level to LIBUSB_LOG_LEVEL_INFO, as suggested in the documentation
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_INFO);

    num_devs = libusb_get_device_list(NULL, &devs);
    if (num_devs < 0)
        return -1;

    while ((dev = devs[i++]) != NULL)
    {
        struct libusb_device_descriptor desc;
        ret = libusb_get_device_descriptor(dev, &desc);
        if (ret < 0)
        {
            perror("libusb_get_device_descriptor err:\n");
            return -1;
        }

        if (desc.idVendor == vid && desc.idProduct == pid)
        {
            found = dev;
            break;
        }
    }

    if(found)
    {
        print_descriptor(found);
    }
    else
    {
        printf("not find vid=0x%04x pid=0x%04x\n", vid, pid);
        ret = LIBUSB_ERROR_NOT_FOUND;
    }


    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);
    return LIBUSB_SUCCESS;
}


/**
 * @brief 打印USB终端节点的信息
 * 
 * @param endpoint : 需要打印的终端节点
 */
void print_endpoint(const struct libusb_endpoint_descriptor *endpoint)
{
    printf("      Endpoint descriptor:\n");
    printf("        bLength: %02xh\n", endpoint->bLength);
    printf("        bDescriptorType: %02xh\n", endpoint->bDescriptorType);
    printf("        bEndpointAddress: %02xh (b[0:3]->ep num. b[4:6]->resd. b[7]->direction)\n", 
                    endpoint->bEndpointAddress);
    printf("        bmAttributes:     %02xh\n", endpoint->bmAttributes);
    printf("        wMaxPacketSize:   %d\n", endpoint->wMaxPacketSize);
    printf("        bInterval:        %d\n", endpoint->bInterval);
    printf("        bRefresh:         %d\n", endpoint->bRefresh);
    printf("        bSynchAddress:    %d\n", endpoint->bSynchAddress);
}

/**
 * @brief 打印USB接口描述的信息
 * 
 * @param interface : 需要打印的USB接口描述
 */
void print_altsetting(const struct libusb_interface_descriptor *interface)
{
    int i;

    printf("    Interface descriptor:\n");
    printf("      bInterfaceNumber:   %d\n", interface->bInterfaceNumber);
    printf("      bAlternateSetting:  %d\n", interface->bAlternateSetting);
    printf("      bNumEndpoints:      %d\n", interface->bNumEndpoints);
    printf("      bInterfaceClass:    %d\n", interface->bInterfaceClass);
    printf("      bInterfaceSubClass: %d\n", interface->bInterfaceSubClass);
    printf("      bInterfaceProtocol: %d\n", interface->bInterfaceProtocol);
    printf("      iInterface:         %d\n", interface->iInterface);

    for (i = 0; i < interface->bNumEndpoints; i++)
        print_endpoint(&interface->endpoint[i]);
}

/**
 * @brief 打印USB接口的信息
 * 
 * @param interface : 需要打印的USB接口 
 */
void print_interface(const struct libusb_interface *interface)
{
    int i;

    for (i = 0; i < interface->num_altsetting; i++)
        print_altsetting(&interface->altsetting[i]);
}


/**
 * @brief 打印USB配置信息
 * 
 * @param config : 需要打印的打印的USB配置
 */
void print_configuration(struct libusb_config_descriptor *config)
{
    int i;

    printf("  Configuration descriptor:\n");
    printf("    wTotalLength:         %d\n", config->wTotalLength);
    printf("    bNumInterfaces:       %d\n", config->bNumInterfaces);
    printf("    bConfigurationValue:  %d\n", config->bConfigurationValue);
    printf("    iConfiguration:       %d\n", config->iConfiguration);
    printf("    bmAttributes:         %02xh\n", config->bmAttributes);
    printf("    MaxPower:             %d\n", config->MaxPower);

    for (i = 0; i < config->bNumInterfaces; i++)
        print_interface(&config->interface[i]);
}

/**
 * @brief 打印设备的详细信息
 * 
 * @param dev : 需要打印详情的设备
 * @param desc : 需要的打印设备的设备描述
 */
void print_device(libusb_device *dev, struct libusb_device_descriptor *desc)
{
    int i;

    printf("Device descriptor:\n");
    printf("  bDescriptorType:         %d\n", desc->bDescriptorType);
    printf("  bcdUSB:                  %#06x\n", desc->bcdUSB);
    printf("  bDeviceClass:            %d\n", desc->bDeviceClass);
    printf("  bDeviceSubClass:         %d\n", desc->bDeviceSubClass);
    printf("  bDeviceProtocol:         %d\n", desc->bDeviceProtocol);
    printf("  bMaxPacketSize0:         %d\n", desc->bMaxPacketSize0);
    printf("  idVendor:                %#06x\n", desc->idVendor);
    printf("  idProduct:               %#06x\n", desc->idProduct);
    printf("  bNumConfigurations:      %d\n", desc->bNumConfigurations);

    for (i = 0; i < desc->bNumConfigurations; i++)
    {
        //得到设备的第i个配置描述
        struct libusb_config_descriptor *config;
        int ret = libusb_get_config_descriptor(dev, i, &config);
        if (LIBUSB_SUCCESS != ret)
        {
            printf("Couldn't retrieve descriptors\n");
            continue;
        }

        //打印配置描述
        print_configuration(config);
        libusb_free_config_descriptor(config);
    }
}


/**
 * @brief 打印USB设备的详细描述信息
 * 
 * @param dev : 需要打印的设备
 * @return int : LIBUSB_SUCCESS:Ok, 其他:错误
 */
int print_descriptor(libusb_device *dev)
{
    struct libusb_device_descriptor desc;
    int ret;
    uint8_t bnum, dnum;
    bnum = libusb_get_bus_number(dev);      //获取usb设备总线号
    dnum = libusb_get_device_address(dev);  //获取usb设备端口号

    printf("bus:%d addr:%d \n", bnum, dnum);
    //得到设备的描述描述
    ret = libusb_get_device_descriptor(dev, &desc);
    if (ret < 0)
    {
        printf("failed to get device descriptor\n");
        return ret;
    }

    print_device(dev, &desc);
    return LIBUSB_SUCCESS;
}