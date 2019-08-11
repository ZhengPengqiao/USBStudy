/*************************************************
**  Copyright  (C)  WCH  2009-3			**
**  Web:  http://www.winchiphead.com    **
*************************************************
**  CH341 OPERATION SPI FLASH EN25T80	**
**  VC++6.0								**
*************************************************/
/*************************************************	
该程序主要完成对SPI接口的FLASH芯片EN25T80读/快
速读/页写/块擦除/扇区擦除/读写时间测试/下载文件
测试/读写状态寄存器测试等
**************************************************/
/*
Revision History: 
V1.0,2009-3,Created by TECH32:
V1.0,2010-1,Modified by TECH32 : 修改文件下载数据校验部分
Version,Data,Modified by TECHxx:修改内容描述描述


About the status register description

BUSY bit:	The BUSY bit indicates whether the memory is busy with a Write Status Register, Program or Erase cycle.
WEL bit:	The Write Enable Latch (WEL) bit indicates the status of the internal Write Enable Latch.
BP2, BP1, BP0 bits. The Block Protect (BP2, BP1, BP0) bits are non-volatile. 
They define the size of the area to be software protected against Program and Erase instructions.
SRP bit:	The Status Register Protect (SRP) bit is operated in conjunction with the Write Protect (WP#)signal. 
The Status Register Protect (SRP) bit and Write Protect (WP#) signal allow the device to be put in the Hardware Protected mode. 
In this mode, the non-volatile bits of the Status Register (SRP, BP2, BP1,BP0) become read-only bits.

Status Register Bit Locations
=========================================================================
| S7	 | 	S6       |   S5		 |	S4	| S3	| S2	|  S1	|  S0   |
=========================================================================
| SRP    |  reserver |  reserver |  BP2 | BP1   | BP0   |  WEL  |  BUSY |
=========================================================================

Sector SECTOR SIZE (KByte)		Address range
15      64						F0000h – FFFFFh
14      64						E0000h – EFFFFh
13      64						D0000h – DFFFFh
12      64						C0000h – CFFFFh
11      64						B0000h – BFFFFh
10      64						A0000h – AFFFFh
9       64						90000h – 9FFFFh
8       64						80000h – 8FFFFh
7       64						70000h – 7FFFFh
6       64						60000h – 6FFFFh
5       64						50000h – 5FFFFh
4       64						40000h – 4FFFFh
3       64						30000h – 3FFFFh
2       64						20000h – 2FFFFh
1       64						10000h – 1FFFFh
0       64						00000h – 0FFFFh

注意：
1-FLASH编程写入只能有1变0,不能从0到1
2-在对FLASH进行擦除时要加15秒的延时,详细资料请查看官方相关说明书
3- 2009-3-19 该程序不能够支持SST的SPI接口FLASH，因为写命令不支持
4-读整个FLASH要8秒,写整个FLASH要60秒，擦除整个FLASH要15秒
*/

//添加条件编译
//#define EN25T80

#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<conio.h>
#include	<winioctl.h>

#include	"CH341DLL.H"			// CH341的动态链接库

//命令码常量定义,请查阅芯片说明书
#define WREN		0X06			//写使能
#define WRDI		0X04			//写禁止
#define RDSR		0X05			//读状态寄存器
#define WRSR		0X01			//写状态寄存器，WEL为0不允许写
#define READ		0X03			//读字节
#define FAST_READ	0X0B			//快读指令
#define PP			0X02			//页写指令
#define SE			0XD8			//区域擦除
#define BE			0XC7			//批擦除
#define DP			0XB9			//深度掉电模式
#define RES			0XAB			//从深度掉电模式苏醒
#define RDID		0x9F			//读标识	
#define RMDI        0x90            //读厂商/设备ID

//全局变量
ULONG index = 0; //设备号
ULONG chip_select = 0x80; //启动片选
unsigned char buffer_write[4096]; //全局缓冲区

//子函数声明
void Select(); 


//结构体定义
struct var_type
{
	union
	{
		unsigned char	c_var;
		unsigned int	i_var;
		unsigned short	s_var;
		unsigned long	l_var;
	};
};


// 将ASCII字符转换为一位BCD码,有效字符是0-9,A-F,a-f,无效字符返回0FFH
unsigned char char_to_bcd( unsigned char i_char )  // 输入的ASCII字符
{
	unsigned char bcd;
	if ( i_char >= '0' && i_char <= '9' ) bcd = i_char -'0';
	else if ( i_char >= 'A' && i_char <= 'Z' ) bcd = i_char - 'A' + 0x0a;
	else if ( i_char >= 'a' && i_char <= 'z' ) bcd = i_char - 'a' + 0x0a;
	else bcd = 0xff;
	return( bcd );
}

// 将字符串转换成数值返回
struct var_type char_to_var(unsigned char * s_char,unsigned int s_len,unsigned int s_flag)
{
	unsigned int i;
	struct var_type type;
	if(s_len != 0)
	{
		if(s_len > 1)	//字符串长度大于1
		{
			if(s_flag == 1)		//sFlag为1 表示返回ULONG型
			{
				unsigned long l_ret = 0;
				for(i=0;i<s_len;i++)	
				{
					l_ret <<= 4;
					l_ret |= char_to_bcd(s_char[i]); 
				}
				type.l_var = l_ret;
			}
			else if(s_flag == 0)		//sFlag为0 表示返回USHORT型
			{
				unsigned short s_ret = 0;
				for(i=0;i<s_len;i++)
				{
					s_ret <<= 4;
					s_ret |= char_to_bcd(s_char[i]);
				}
				type.s_var = s_ret;
			}
			else if(s_flag == 2)		//sFlag为2 表示返回UINT型
			{
				unsigned int i_ret = 0;
				for(i=0;i<s_len;i++)
				{
					i_ret <<= 4;
					i_ret |= char_to_bcd(s_char[i]);
				}
				type.i_var = i_ret;
			}
			else if(s_flag == 3)
			{
				unsigned char c_ret = 0;
				c_ret = (char_to_bcd(s_char[0])<<4) | char_to_bcd(s_char[1]);
				type.c_var = c_ret;
			}
		}
		else	//字符串长度等于1
		{
			type.l_var = char_to_bcd(s_char[0]);
			type.s_var = char_to_bcd(s_char[0]);
			type.i_var = char_to_bcd(s_char[0]);
			type.c_var = char_to_bcd(s_char[0]);
		}
	}
	else
	{
		type.i_var = 0;
		type.l_var = 0;
		type.s_var = 0;
		type.c_var = 0;
	}
	return type;
}

/*********************************************************************  
*
* 函 数 名: file_operation
* 功能描述: 文件操作，用于保存读出的FLASH数据，便于调试
* 函数说明: 
* 调用函数:
* 全局变量:
* 输    入: 无
* 返    回: 成功返回TRUE，失败返回FLASE
* 设 计 者：tech32                         日期：2009-3-11
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/

FILE *stream;
void file_operation( char *path, char *flag)
{
	if( (stream = fopen( path, flag )) == NULL )
		printf( "The file %s was not opened\n", path );
	else
		printf( "The file %s was opened\n", path );
}

/*********************************************************************  
*
* 函 数 名:write_enable
* 功能描述: 写使能
* 函数说明: PP,SE,BE,WRSR之前必须进行写使能
* 调用函数:CH341StreamSPI4
* 全局变量:iIndex,iChipSelect
* 输    入: 无
* 返    回: 成功返回TRUE，失败返回FLASE
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char write_enable(unsigned char *buffer)
{
	*( (unsigned char *)buffer + 0 ) = WREN;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
	
}

/*********************************************************************  
*
* 函 数 名: write_disable
* 功能描述: 写禁止
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: iIndex,iChipSelect
* 输    入: 无
* 返    回: 成功返回TRUE，失败返回FLASE
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char write_disable(unsigned char *buffer)
{
	*( (unsigned char *)buffer + 0 ) = WRDI;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: read_status_register
* 功能描述: 读状态寄存器
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE，失败返回FALSE
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char read_status_register(unsigned char *buffer)
{
	*( (unsigned char *)buffer + 0 ) = RDSR;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1+2, buffer ) == FALSE ) return( FALSE );
	memmove( buffer, (unsigned char *)buffer + 1, 2 );  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的1个字节(命令和地址)
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: write_status_register
* 功能描述: 写功能寄存器
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char status,unsigned char *buffer
* 返    回: 成功返回TRUE，失败返回FALSE
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char write_status_register(unsigned char status,unsigned char *buffer)
{
	*( (unsigned char *)buffer + 0 ) = WRSR;  //命令码
	*( (unsigned char *)buffer + 1 ) = status;  
	if ( CH341StreamSPI4( index, chip_select, 2, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名:check
* 功能描述: WIP位检查
* 函数说明: 1，表示写操作未完成，0表示写操作完成
* 调用函数: read_status_register
* 全局变量:
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE，失败返回FALSE
* 设 计 者：tech32							日期：2009-3-10
* 修 改 者：								日期：
* 版    本：VER 1.0
***********************************************************************/
void check( unsigned char *buffer )
{
	do{
		read_status_register(buffer_write);
	}while(buffer_write[0] & 0x01);
}

/*********************************************************************  
*
* 函 数 名: page_program
* 功能描述: 存储多字节子程序
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量:	index,chip_select
* 输    入: unsigned long address,unsigned long length,unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char page_program( unsigned long address,unsigned long length,unsigned char *buffer )
{
	unsigned char *buffer_write;
	buffer_write = (unsigned char *)malloc(length+4);
	memcpy(buffer_write+4,buffer,length);
	*( (unsigned char *)buffer_write + 0 ) = PP;  //命令码
	*( (unsigned char *)buffer_write + 1 ) = (unsigned char)( address >> 16 & 0xFF );  // 指定读操作的地址A23-A16
	*( (unsigned char *)buffer_write + 2 ) = (unsigned char)( address >> 8 & 0xFF );  // 指定读操作的地址A15-A8
	*( (unsigned char *)buffer_write + 3 ) = (unsigned char)( address & 0xFF );  // 指定读操作的地址A7-A0
	if ( CH341StreamSPI4( index, chip_select, length+4, buffer_write ) == FALSE ) 
	{	
		free(buffer_write);
		return( FALSE );
	}
	free(buffer_write);
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: sector_erase
* 功能描述: 扇区擦除
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned long address,unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char sector_erase(unsigned long address,unsigned char *buffer)
{
	*( (unsigned char *)buffer + 0 ) = SE;  //命令码
	*( (unsigned char *)buffer + 1 ) = (unsigned char)( address >> 16 & 0xFF );  // 指定读操作的地址A23-A16
	*( (unsigned char *)buffer + 2 ) = (unsigned char)( address >> 8 & 0xFF );  // 指定读操作的地址A15-A8
	*( (unsigned char *)buffer + 3 ) = (unsigned char)( address & 0xFF );  // 指定读操作的地址A7-A0
	if ( CH341StreamSPI4( index, chip_select, 4, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: bulk_erase
* 功能描述: 块擦除
* 函数说明: 
* 调用函数: 
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char bulk_erase( unsigned char *buffer )
{
	*( (unsigned char *)buffer + 0 ) = BE;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: read_block
* 功能描述: 读FLASH
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned long address,unsigned long length, unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char  read_block( unsigned long address,unsigned long length, unsigned char *buffer ) 
{
	*( (unsigned char *)buffer + 0 ) = READ;  //命令码
	*( (unsigned char *)buffer + 1 ) = (unsigned char)( address >> 16 & 0xFF );  // 指定读操作的地址A23-A16
	*( (unsigned char *)buffer + 2 ) = (unsigned char)( address >> 8 & 0xFF );  // 指定读操作的地址A15-A8
	*( (unsigned char *)buffer + 3 ) = (unsigned char)( address & 0xFF );  // 指定读操作的地址A7-A0
	memset( (unsigned char *)buffer + 4, 0xFF, length );  // 对于有些SPI器件,可能要求在读出数据时SI输入保持为1或者0,那么就要在此设置
	if ( CH341StreamSPI4( index, chip_select, length+4, buffer ) == FALSE ) return( FALSE );  // 处理4线接口SPI数据流,自动片选为D0
	/* 对于EN25T80的读操作,要先输出4个字节命令及地址,再输入若干个字节数据,调用API和API返回时都是指总长度,所以返回数据的前4个字节是在输出命令及地址时输入的,应该丢弃 */
	memmove( buffer, (unsigned char *)buffer + 4, length );  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的4个字节(命令和地址)
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: read_block_fast
* 功能描述: 快速读FLASH
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned long address,unsigned long length, unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-12
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char  read_block_fast( unsigned long address,unsigned long length, unsigned char *buffer ) 
{
	*( (unsigned char *)buffer + 0 ) = FAST_READ;  //命令码
	*( (unsigned char *)buffer + 1 ) = (unsigned char)( address >> 16 & 0xFF );  // 指定读操作的地址A23-A16
	*( (unsigned char *)buffer + 2 ) = (unsigned char)( address >> 8 & 0xFF );  // 指定读操作的地址A15-A8
	*( (unsigned char *)buffer + 3 ) = (unsigned char)( address & 0xFF );  // 指定读操作的地址A7-A0
	*( (unsigned char *)buffer + 4 ) = 0;  //
	memset( (unsigned char *)buffer + 5, 0xFF, length );  // 对于有些SPI器件,可能要求在读出数据时SI输入保持为1或者0,那么就要在此设置
	if ( CH341StreamSPI4( index, chip_select, length+5, buffer ) == FALSE ) return( FALSE );  // 处理4线接口SPI数据流,自动片选为D0
	/* 对于EN25T80的读操作,要先输出4个字节命令及地址,再输入若干个字节数据,调用API和API返回时都是指总长度,所以返回数据的前4个字节是在输出命令及地址时输入的,应该丢弃 */
	memmove( buffer, (unsigned char *)buffer + 5, length );  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的4个字节(命令和地址)
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名:read_identification
* 功能描述: 读芯片标识
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char read_identification( unsigned char *buffer )
{
	*( (unsigned char *)buffer + 0 ) = RDID;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 4, buffer ) == FALSE ) return( FALSE );
	memmove( buffer, (unsigned char *)buffer + 1, 3 );  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的4个字节(命令和地址)
	return( TRUE );
}

/*********************************************************************  
*
* 函 数 名: read_manufacturer_device_id
* 功能描述: 读厂商设备ID号
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char read_manufacturer_device_id( unsigned char *buffer )
{
	*( (unsigned char *)buffer + 0 ) = RMDI;  //命令码
	*( (unsigned char *)buffer + 1 ) = 0x00;
	*( (unsigned char *)buffer + 2 ) = 0x00;
	*( (unsigned char *)buffer + 3 ) = 0x00;
	if ( CH341StreamSPI4( index, chip_select, 6, buffer ) == FALSE ) return( FALSE );
	memmove( buffer, (unsigned char *)buffer + 4, 2);  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的4个字节(命令和地址)
	return( TRUE );
	
}

/*********************************************************************  
*
* 函 数 名: deep_power_down
* 功能描述: 电源处理
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char deep_power_down( unsigned char *buffer )
{
	*( (unsigned char *)buffer + 0 ) = 0xB9;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}


/*********************************************************************  
*
* 函 数 名: release_deep_power_down
* 功能描述: 电源处理
* 函数说明: 
* 调用函数: CH341StreamSPI4
* 全局变量: index,chip_select
* 输    入: unsigned char *buffer
* 返    回: 成功返回TRUE,失败返回FALSE
* 设 计 者：tech32									日期：2009-3-10
* 修 改 者：										日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char release_deep_power_down( unsigned char *buffer )
{
	*( (unsigned char *)buffer + 0 ) = 0xAB;  //命令码
	if ( CH341StreamSPI4( index, chip_select, 1, buffer ) == FALSE ) return( FALSE );
	return( TRUE );
}

//功能测试子函数

/*********************************************************************  
*
* 函 数 名: deep_power_down_test
* 功能描述: 
* 函数说明: 
* 调用函数: deep_power_down
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-12
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void deep_power_down_test()
{
	deep_power_down(buffer_write);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: release_deep_power_down
* 功能描述: 
* 函数说明: 
* 调用函数: deep_power_down
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-12
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void release_deep_power_down_test()
{
	release_deep_power_down(buffer_write);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: read_status_register_test
* 功能描述: 测试读状态寄存器
* 函数说明: 
* 调用函数: read_status_register
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_status_register_test()
{
	unsigned char i;
	read_status_register(buffer_write);
	for(i=0;i<2;i++) //根据时序可知返回2个字节
	{
		printf("buffer_write[%d]=%x\n",i,buffer_write[i]);
	}
	printf("****** OK ******\n");
	
	Select();
}

/*********************************************************************  
*
* 函 数 名: write_status_register_test
* 功能描述: 测试写状态寄存器，在写前务必写使能
* 函数说明: 
* 调用函数: write_enable,write_status_register,write_disable
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void write_status_register_test()
{
	write_enable(buffer_write);
	write_status_register(0,buffer_write); //写0
	write_disable(buffer_write);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: write_enable_test
* 功能描述: 测试写使能
* 函数说明: 
* 调用函数: write_enable,read_status_register
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void write_enable_test()
{
	unsigned char i;
	write_enable(buffer_write); //写使能
	read_status_register(buffer_write); //读状态register，检查位1
	for(i=0;i<2;i++) 
	{
		printf("buffer_write[%d]=%x\n",i,buffer_write[i]); //打印信息
	}
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: write_disable_test
* 功能描述: 测试写使能
* 函数说明: 
* 调用函数: write_disable,read_status_register
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void write_disable_test()
{
	unsigned char i;
	write_disable(buffer_write); //写禁止
	read_status_register(buffer_write); //读状态register，检查位1
	for(i=0;i<2;i++)
	{
		printf("buffer_write[%d]=%x\n",i,buffer_write[i]); //打印信息
	}
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: read_identification_test
* 功能描述: 测试读芯片标识
* 函数说明: 
* 调用函数: read_identification
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_identification_test()
{
	unsigned char i;
	read_identification(buffer_write);
	for(i=0;i<3;i++)
	{
		printf("buffer_write[%d]=%x\n",i,buffer_write[i]);	
	}
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: read_manufacturer_device_id_test
* 功能描述: 测试读厂商/设备ID
* 函数说明: 
* 调用函数: read_manufacturer_device_id
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_manufacturer_device_id_test()
{
	unsigned char i;
	read_manufacturer_device_id(buffer_write);
	for(i=0;i<2;i++)
	{
		printf("buffer_write[%d]=%x\n",i,buffer_write[i]);	
	}
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: sector_erase_test
* 功能描述: 擦除FLASH的某个扇区
* 函数说明: 地址只能是0x1000的整数倍
* 调用函数: write_enable,bulk_erase,check,write_disable
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void sector_erase_test()
{
	write_enable(buffer_write);
	sector_erase(0,buffer_write); //
	printf("正在扇区擦除FLASH...\n");
	write_disable(buffer_write);
	check(buffer_write);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: bulk_erase_test
* 功能描述: 擦除整个FLASH
* 函数说明: 
* 调用函数: write_enable,bulk_erase,check,write_disable
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void bulk_erase_test()
{	
	write_enable(buffer_write);
	bulk_erase(buffer_write);
	printf("正在块擦除FLASH...\n");
	//Sleep(15000);
	write_disable(buffer_write);
	check(buffer_write);
	printf("****** OK ******\n");
	Select();
}

#define BUFFER_LENGTH 0x100
/*********************************************************************  
*
* 函 数 名: read_block_test
* 功能描述: 测试读FLASH
* 函数说明: 
* 调用函数: read_block
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_block_test()
{
	//int i;
	unsigned long address,mTotal;
	mTotal=0;
	file_operation("read_data","w+"); //创建文件来保存读出的数据
	for(address=0;address<0xFFFFF;address+=BUFFER_LENGTH)
	{
		read_block(address,BUFFER_LENGTH,buffer_write); //读FLASH	每次读2K字节，CH341动态库只支持最大4K
		fwrite( buffer_write,sizeof( char ), BUFFER_LENGTH,stream );
		//for(i=0;i<BUFFER_LENGTH;i++) //打印数据,方便调试	
		//{
		//	printf("buffer_write[%d]=%x\n",i,buffer_write[i]);	
		//}
		mTotal = mTotal+BUFFER_LENGTH;
		fseek(stream,mTotal,SEEK_SET);	
		printf(".");
	}
	fclose( stream );
	printf("\n");
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: read_block_fast_test
* 功能描述: 测试读FLASH
* 函数说明: 
* 调用函数: read_block_fast
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-12
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_block_fast_test()
{
	unsigned long address,mTotal;
	mTotal=0;
	file_operation("read_data","w+"); //创建文件来保存读出的数据
	for(address=0;address<0xFFFFF;address+=BUFFER_LENGTH)
	{
		read_block_fast(address,BUFFER_LENGTH,buffer_write); //读FLASH	每次读2K字节，CH341动态库只支持最大4K
		fwrite( buffer_write,sizeof( char ), BUFFER_LENGTH,stream );
		//for(i=0;i<BUFFER_LENGTH;i++) //打印数据,方便调试	
		//{
		//	printf("buffer_write[%d]=%x\n",i,buffer_write[i]);	
		//}
		mTotal = mTotal+BUFFER_LENGTH;
		fseek(stream,mTotal,SEEK_SET);	
		if(address%0x8000==0) printf("."); //进度,写完32k输出"."
	}
	fclose( stream );
	printf("\n");
	printf("****** OK ******\n");
	Select();
}


/*********************************************************************  
*
* 函 数 名: page_program_test
* 功能描述: 测试写FLASH,写一页，从地址0开始写
* 函数说明: 
* 调用函数: write_enable,page_program,check,write_disable
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void page_program_test_pre(unsigned long address)
{
	unsigned char buffer[BUFFER_LENGTH+1];
	int i;
	for(i=0;i<BUFFER_LENGTH;i++) //初始化发送缓冲区
		buffer[i]=0x55;
	write_enable(buffer_write); //写使能
	page_program(address,BUFFER_LENGTH,buffer); //写FLASH
	write_disable(buffer_write); //写禁止
	check(buffer_write); //检查WIP位		
}

void page_program_test()
{
	unsigned long address;
	for(address=0;address<0xFFFFF;address+=0x100)
	{
		page_program_test_pre(address); //每次都要分配缓冲区，否则数据在page_program子函数中被改掉
		if(address%0x8000==0) printf("."); //进度,写完32k输出"."
	}
	printf("\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: read_time_test
* 功能描述: 测试读FLASH速度
* 函数说明: 
* 调用函数: read_block
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void read_time_test()
{
	unsigned long mLength, mStep, mTotal,address;
	double  speed;
	mTotal = 0;
	file_operation("read_data","w+"); //创建文件来保存读出的数据
	mStep=GetTickCount();
	for(address=0;address<0x100000;address+=0x800)
	{
		read_block(address,0x800,buffer_write);//读FLASH	每次读2K字节，CH341动态库只支持最大4K
		fwrite( buffer_write,sizeof( char ), 0x800,stream );
		mTotal = mTotal+0x800;
		fseek(stream,mTotal,SEEK_SET);
		if(address%0x8000==0) printf("."); //进度,写完32k输出"."
	}
	fclose( stream );
	printf("\n");
	mLength=GetTickCount();
	mLength=mLength-mStep;
	speed=1000;
	if ( mLength !=0 ) speed=speed*mTotal/mLength;
	else speed=9999999;
	printf( "*** speed = %7.1f Bytes/Sec, total=%ld bytes, time=%ld mS\n", speed, mTotal, mLength);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: write_time_test
* 功能描述: 测试写FLASH速度
* 函数说明: 
* 调用函数: write_enable,page_program,check,write_disable
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void write_time_test()
{
	unsigned long mLength, mStep, mTotal,address;
	double  speed;
	unsigned char buffer[BUFFER_LENGTH+1];
	int i;
	for(i=0;i<BUFFER_LENGTH;i++) //初始化发送缓冲区
		buffer[i]=0x55;
	mTotal = 0x100000;
	printf("正在测试写FLASH速度...\n");
	
	mStep=GetTickCount();
	for(address=0;address<mTotal;address+=0x100)
	{
		write_enable(buffer_write); //写使能
		page_program(address,BUFFER_LENGTH,buffer); //写FLASH
		write_disable(buffer_write); //写禁止
		check(buffer_write); //检查WIP位	
		if(address%0x8000==0) printf("."); //进度,写完32k输出"."
	}
	
	mLength=GetTickCount();
	mLength=mLength-mStep;
	speed=1000;
	if ( mLength !=0 ) speed=speed*mTotal/mLength;
	else speed=9999999;
	printf( "*** speed = %7.1f Bytes/Sec, total=%ld bytes, time=%ld mS\n", speed, mTotal, mLength);
	printf("****** OK ******\n");
	Select();
}

/*********************************************************************  
*
* 函 数 名: auto_test
* 功能描述: 自动测试，其中包括所有的测试项目
* 函数说明: 
* 调用函数: 
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void auto_test()
{
	printf("****** OK ******\n");
	Select();
}


/*********************************************************************  
*
* 函 数 名: file_down
* 功能描述: 下载文件
* 函数说明: 
* 调用函数: 
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-12
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
unsigned char path[256]; //保存文件路径
HANDLE hFile;
void file_down()
{
	//打开保存要下载文件路径的文件
	unsigned long file_size,file_length,address,length,write_count,i;
	unsigned char *buffer;
	unsigned char *buffer_read,*p,*q;
	file_operation("path","r"); //以只读方式打开
	file_length = fread(path,sizeof(char),256,stream);
	printf("file_length=%d\n",file_length);
	fclose(stream);
	
	//打开要下载的文件
	if ( ( hFile = CreateFile ( path,GENERIC_READ,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,
								OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,( HANDLE ) NULL ) ) == ( HANDLE ) -1 )
	{ 
		printf("open %s failed\n",path);	
	}
	else 
	{
		printf("open file: %s ok \n",path);
		file_size = GetFileSize (hFile, NULL) ; 
		printf("This file length is %d Bytes\n",file_size);
	}
	//获得文件数据
	buffer = ( unsigned char * ) malloc ( file_size );  // 分配放文件的缓冲区
	
	if ( buffer == NULL )// 分配缓冲区错误
	{  
		CloseHandle ( hFile );
		free ( buffer );
		printf("动态分配缓冲区出错\n");
	}
	memset ( buffer,0,file_size );  // 清空缓冲区
	p = buffer;
	if ( ! ( ReadFile ( hFile, buffer, file_size, &file_size, NULL ) ) ) // 读取文件数据到分配的缓冲区中，发生错误时，关闭文件句柄，释放缓冲区
	{  
		CloseHandle ( hFile );
		//free ( buffer );
		printf("读文件出错\n");
	}
	//关闭文件
	CloseHandle ( hFile );
	//在写之前务必擦除整个FALSH
	write_enable(buffer_write);
	bulk_erase(buffer_write);
	printf("正在块擦除FLASH...\n");
	check(buffer_write);
	write_disable(buffer_write);
	printf("****** OK ******\n");
	printf("正在写FLASH...\n");
	//循环写，每次写256个字节数据到FLASH
	write_count = file_size / BUFFER_LENGTH;
	address = 0;
	for(i=0;i<write_count;i++)
	{
		write_enable(buffer_write);
		page_program( address, BUFFER_LENGTH , buffer );
		check(buffer_write);
		write_disable(buffer_write);
		address+=BUFFER_LENGTH;
		buffer+=BUFFER_LENGTH;
		if(address%0x400==0) printf("."); //进度,写完1k输出"."
	}
	printf("\n");
	//写剩下的
	if(file_size % BUFFER_LENGTH != 0)
	{
		length = file_size % 256;
		page_program( address, length, buffer );
	}
	printf("写FLASH完成...\n");
	//数据校验
	printf("开始进行数据校验...\n");
	address= 0;
	buffer_read = ( unsigned char * ) malloc ( file_size );  // 分配放文件的缓冲区
	if ( buffer_read == NULL )// 分配缓冲区错误
	{  
		free ( buffer_read );
		printf("动态分配缓冲区出错\n");
	}
	memset ( buffer_read,0,file_size );  // 清空缓冲区
	q = buffer_read;
	for(i=0;i<write_count;i++) // 读出FLASH数据
	{
		read_block(address,BUFFER_LENGTH,buffer_read);
		address+=BUFFER_LENGTH;
		buffer_read+=BUFFER_LENGTH;
		if(address%0x400==0) printf("."); //进度,写完1k输出"."
	}
	printf("\n");
	// 读剩下的
	if(file_size % BUFFER_LENGTH != 0)
	{
		length = file_size % 256;
		read_block( address, length, buffer_read );
	}
	if( memcmp( p, q, file_size ) == 0 ) // 比较内存 2010-1-20修改
	{
		printf("数据校验正确\n");
	}
	else printf("数据校验出错\n");
	free(buffer);
	free(buffer_read);
	Select();
}

/*********************************************************************  
*
* 函 数 名: Select
* 功能描述: 用户接口
* 函数说明: 
* 调用函数: 1-read_status_register_test
			2-write_status_register_test
			3-write_enable_test
			4-write_disable_test
			5-read_identification_test
			6-read_manufacturer_device_id_test
			7-sector_erase_test
			8-bulk_erase_test
			9-read_block_test
			a-page_program_test
			b-read_time_test
			c-write_time_test
* 全局变量: buffer_write
* 输    入: 无
* 返    回: 
* 设 计 者：tech32                         日期：2009-3-10
* 修 改 者：                               日期：
* 版    本：VER 1.0
***********************************************************************/
void Select()
{
	char     inputr;   // 输入一个选择号
	unsigned char    a;
	unsigned char * temp1=&a;
	printf("\n");
	printf("          *******请输入测试的选项*******\n");
	printf("0.退出程序\n");												
	printf("1.Read Identification测试\n");
	printf("2.Read Manufacturer / Device ID测试\n");
	printf("3.Release from Deep Power-down and Read Device ID测试\n");
	printf("4.Deep Power-down测试\n");
	printf("5.Bulk Erase测试\n");
	printf("6.Sector Erase测试\n");
	printf("7.Page Program测试\n");
	printf("8.Read Data Bytes at Higher Speed测试\n");
	printf("9.Read Data Bytes测试\n");
	printf("a.Write Status Register测试\n");
	printf("b.Read Status Register测试\n");
	printf("c.Write Disable测试\n");
	printf("d.Write Enable测试\n");
	printf("e.read flash time测试\n");
	printf("f.write flash time测试\n");
	printf("A.auto测试\n");
	printf("B.file down测试\n");
	printf("请输入测试的选项:");
	do{
		inputr=getchar();
		switch(inputr)
        {
		case '0':
			printf( "*** CH341CloseDevice \n" );
	           CH341CloseDevice(0);
			   printf( "\nExit.\n" );
			   exit(0);    //退出
		case '1':
			printf("*** read_identification_test \n");
			read_identification_test();
			break;
		case '2':
			printf("*** read_manufacturer_device_id_test \n");
			read_manufacturer_device_id_test();
			break;
		case '3':
			printf("*** deep_power_down_test \n");
			deep_power_down_test();
			break;
		case '4':
			printf("*** release_deep_power_down_test \n");
			release_deep_power_down_test();
			break;
		case '5':
			printf("*** bulk_erase_test \n");
			bulk_erase_test();
			break;
		case '6':
			printf("*** sector_erase_test \n");
			sector_erase_test();
			break;
		case '7':
			printf("*** page_program_test \n");
			page_program_test();
			break;
		case '8':
			printf("*** read_block_fast_test \n");
			read_block_fast_test();
			break;
		case '9':
			printf("*** read_block_test \n");
			read_block_test();
			break;
		case 'a':
			printf("*** write_status_register_test \n");
			write_status_register_test();
			break;
		case 'b':
			printf("*** read_status_register_test \n");
			read_status_register_test();
			break;
		case 'c':
			printf("*** write_disable_test \n");
			write_disable_test();
			break;
		case 'd':
			printf("*** write_enable_test \n");
			write_enable_test();
			break;
		case 'e':
			printf("*** read_time_test \n");
			read_time_test();
			break;
		case 'f':
			printf("*** write_time_test \n");
			write_time_test();
			break;
		case 'A':
			printf("*** auto test \n");
			auto_test();
			break;
		case 'B':
			printf("*** file down test \n");
			file_down();
			break;
		default :
			break;
		}
	}
	while(1);
}  

//程序入口
void main ( )
{
	HANDLE hOut;
	WORD attText = FOREGROUND_GREEN  | FOREGROUND_INTENSITY; // 文本属性
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 获取标准输出设备句柄
	SetConsoleOutputCP(936); // 设置代码页
	SetConsoleTextAttribute(hOut,attText);
	printf( "\nCH341 OPERATION SPI FLASH EN25T80 TEST PROGRAM V1.0\n");
	printf("Copyright (C) TECH32 2009.3\n" );
	printf( "*** Load DLL: CH341DLL.DLL \n" );
	if ( LoadLibrary( "CH341DLL.DLL" ) == NULL ) return;  // 加载DLL失败,可能未安装到系统中
	printf( "*** CH341OpenDevice: 0# \n" );
	if ( CH341OpenDevice( 0 ) == INVALID_HANDLE_VALUE ) return;  // 使用之前必须打开设备
	if( CH341SetStream(0, 0x81) == 0) return ; //高位先发
	Select(); //测试选择
	CloseHandle(hOut); // 关闭标准输出设备句柄
}







