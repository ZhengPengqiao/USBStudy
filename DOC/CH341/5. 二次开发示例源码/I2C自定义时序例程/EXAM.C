// V1.1

#include	<windows.h>
#include	"CH341DLL.H"

/* 本程序涉及到
 1、2线接口的一些自定义时序,处理IIC总线的应答位,以及了解2线接口的内部时序分析
 2、提供例子程序,操作2线接口IIC器件X76F640、PCF8574、PCA9554
 3、用EPP或者MEM并口进行多位输出或者多位输入,模拟只读或者只写的SPI时序
 4、用UIO通用I/O位流命令实现自定义的同步串行接口
 5、提供例子程序,操作类似SPI的非标准串行时序的器件TLC1549
 6、提供例子程序,通过CH341StreamSPI4操作4线接口SPI器件25C512、25C020
 7、提供例子程序,通过CH341BitStreamSPI操作类似SPI的非标准串行时序的器件ADC0831
 另外可以用CH341SetOutput设置CH341的I/O方向,并通过CH341的任何一个引脚直接输出数据,未提供例子,建议用CH341Set_D5_D0代替
*/

/* CH341并口驱动及DLL的API层次,按从低向高分为
 1、CH341DriverCommand直接传给WDM驱动程序层
 2、CH341WriteData只写数据, CH341ReadData只读数据, CH341WriteRead先写数据再读数据
 3、CH341StreamI2C先写IIC,可选地再读IIC (内部调用CH341WriteData和CH341WriteRead)
    CH341StreamSPI进行SPI传输,读写都是可选的 (内部调用CH341WriteRead)
 4、CH341ReadEEPROM读EEPROM数据, CH341WriteEEPROM写EEPROM数据 (内部调用CH341StreamI2C)
 本例子中的子程序将调用CH341WriteData、CH341WriteRead、CH341StreamI2C等DLL中的API */

/* 实测速度
   CH341StreamI2C     约56K字节
   CH341ReadEEPROM    约56K字节
   CH341WriteEEPROM   约5K字节(如果是RAM而非闪存那么与CH341ReadEEPROM速度相同)
   CH341StreamSPI4    约68K字节
   CH341StreamSPI5    每路约30K字节  * 2路输入和2路输出
   CH341BitStreamSPI  每路约8K位     * 至少2路输入和2路输出(最多7路输入4路输出)
*/

/* ********************************************************************************************** */
/* 例子:兼容IIC总线的通用操作时序 */

BOOL	WINAPI	IIC_IssueStart(
	ULONG			iIndex )  // 指定CH341设备序号
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_STA;  // 产生起始位
	mBuffer[ 2 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 3;
	return( CH341WriteData( iIndex, mBuffer, &mLength ) );  // 写出数据块
}

BOOL	WINAPI	IIC_IssueStop(
	ULONG			iIndex )  // 指定CH341设备序号
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_STO;  // 产生停止位
	mBuffer[ 2 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 3;
	return( CH341WriteData( iIndex, mBuffer, &mLength ) );  // 写出数据块
}

BOOL	WINAPI	IIC_OutBlockSkipAck(  // 输出数据块,不检查应答
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iOutLength,  // 准备写出的数据字节数,单次必须小于29字节
	PVOID			iOutBuffer )  // 指向一个缓冲区,放置准备写出的数据
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength;
	if ( iOutLength == 0 || iOutLength > ( mCH341_PACKET_LENGTH - 1 - 1 - 1 ) ) return( FALSE );
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | iOutLength );  // 输出数据,位5-位0为长度
	memcpy( &mBuffer[2], iOutBuffer, iOutLength );  // 数据
	mBuffer[ 1 + 1 + iOutLength ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 1 + 1 + iOutLength + 1;
	return( CH341WriteData( iIndex, mBuffer, &mLength ) );  // 写出数据块
}

BOOL	WINAPI	IIC_OutByteCheckAck(  // 输出一字节数据并检查应答是否有效
	ULONG			iIndex,  // 指定CH341设备序号
	UCHAR			iOutByte )  // 准备写出的数据
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength, mInLen;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_OUT;  // 输出数据,位5-位0为长度,0长度则只发送一个字节并返回应答
	mBuffer[ 2 ] = iOutByte;  // 数据
	mBuffer[ 3 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 4;
	mInLen = 0;
	if ( CH341WriteRead( iIndex, mLength, mBuffer, mCH341A_CMD_I2C_STM_MAX, 1, &mInLen, mBuffer ) ) {  // 执行数据流命令,先输出再输入
		if ( mInLen && ( mBuffer[ mInLen - 1 ] & 0x80 ) == 0 ) return( TRUE );  // 返回的数据的位7代表ACK应答位,ACK=0有效
	}
	return( FALSE );
}

BOOL	WINAPI	IIC_InBlockByAck(  // 输入数据块,每输入一个字节都产生有效应答
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iInLength,  // 准备读取的数据字节数,单次必须小于32字节
	PVOID			oInBuffer )  // 指向一个缓冲区,返回后是读入的数据
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength, mInLen;
	if ( iInLength == 0 || iInLength > mCH341A_CMD_I2C_STM_MAX ) return( FALSE );
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = (UCHAR)( mCH341A_CMD_I2C_STM_IN | iInLength );  // 输入数据,位5-位0为长度
	mBuffer[ 2 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 3;
	mInLen = 0;
	if ( CH341WriteRead( iIndex, mLength, mBuffer, mCH341A_CMD_I2C_STM_MAX, 1, &mInLen, mBuffer ) ) {  // 执行数据流命令,先输出再输入
		if ( mInLen == iInLength ) {
			memcpy( oInBuffer, &mBuffer[0], iInLength );  // 数据
			return( TRUE );
		}
	}
	return( FALSE );
}

BOOL	WINAPI	IIC_InByteNoAck(  // 输入一字节数据,但是不产生应答
	ULONG			iIndex,  // 指定CH341设备序号
	PUCHAR			oInByte )  // 指向一个字节的缓冲区,返回后是读入的数据
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength, mInLen;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_IN;  // 输入数据,位5-位0为长度,0长度则只接收一个字节并发送无应答
	mBuffer[ 2 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 3;
	mInLen = 0;
	if ( CH341WriteRead( iIndex, mLength, mBuffer, mCH341A_CMD_I2C_STM_MAX, 1, &mInLen, mBuffer ) ) {  // 执行数据流命令,先输出再输入
		if ( mInLen ) {
			*oInByte = mBuffer[ mInLen - 1 ];  // 数据
			return( TRUE );
		}
	}
	return( FALSE );
}

/* ********************************************************************************************** */
/* 操作加密存储器X76F640 */

BOOL	WINAPI	X76F640_AckPolling(  // 查询X76F640应答 (包括:输出起始位,输出一字节命令数据,检查应答是否有效)
	ULONG			iIndex )  // 指定CH341设备序号
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength, mInLen;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_STA;  // 产生起始位
	mBuffer[ 2 ] = mCH341A_CMD_I2C_STM_OUT;  // 输出数据,位5-位0为长度,0长度则只发送一个字节并返回应答
	mBuffer[ 3 ] = 0xF0;  // 应答查询操作的命令码
	mBuffer[ 4 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 5;
	mInLen = 0;
	if ( CH341WriteRead( iIndex, mLength, mBuffer, mCH341A_CMD_I2C_STM_MAX, 1, &mInLen, mBuffer ) ) {  // 执行数据流命令,先输出再输入
		if ( mInLen && ( mBuffer[ mInLen - 1 ] & 0x80 ) == 0 ) return( TRUE );  // 返回的数据的位7代表ACK应答位,ACK=0有效
	}
	return( FALSE );
}

BOOL	WINAPI	X76F640_CheckPasswd(  // 发出操作命令并检查指定的密码 (包括:输出起始位,输出9字节数据(1命令+8密码),查询应答,输出2字节地址)
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iCommand,  // 操作命令码
	PVOID			iPasswdBuf,  // 指向一个缓冲区,提供8字节的密码数据
	ULONG			iAddress )  // 指定操作地址或者密码后的2字节数据
{
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	i, mLength;
	i = 0;
	mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_STA;  // 产生起始位
	mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | 9 );  // 输出数据,位5-位0为长度,9字节
	mBuffer[ i++ ] = (UCHAR)iCommand;  // 操作命令码
	memcpy( &mBuffer[ i ], iPasswdBuf, 8 );  // 8字节密码数据
	i += 8;
	mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_MS | 10 );  // 以亳秒为单位延时,位3-位0为延时值,延时10毫秒
	mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = i;
	if ( CH341WriteData( iIndex, mBuffer, &mLength ) ) {  // 写出数据块
		if ( X76F640_AckPolling( iIndex ) ) {  // 查询应答有效
			i = 0;
			mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 命令码
			mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | 2 );  // 输出数据,位5-位0为长度
			mBuffer[ i++ ] = (UCHAR)( iAddress & 0x00FF );  // 地址低8位
			mBuffer[ i++ ] = (UCHAR)( ( iAddress >> 8 ) & 0x00FF );  // 地址高8位
			mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
			mLength = i;
			return( CH341WriteData( iIndex, mBuffer, &mLength ) );  // 写出数据块
		}
		else IIC_IssueStop( iIndex );  // 应答无效
	}
	return( FALSE );
}

BOOL	WINAPI	X76F640_WriteWithPasswd(  // 写X76F640的块,使用指定的密码
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iWriteCommand,  // 块写命令码
	PVOID			iPasswdBuf,  // 指向一个缓冲区,放置8字节的密码数据
	ULONG			iAddress,  // 指定操作地址
	ULONG			iOutLength,  // 准备写出的数据字节数,单次必须小于32字节(1个扇区)
	PVOID			iOutBuffer )  // 指向一个缓冲区,放置准备写出的数据
{
	UCHAR	mBuffer[ mDEFAULT_BUFFER_LEN ];
	ULONG	i, mLength;
	if ( iOutLength == 0 || iOutLength > 32 ) return( FALSE );
	if ( X76F640_CheckPasswd( iIndex, iWriteCommand, iPasswdBuf, iAddress ) ) {  // 发出命令及密码检查通过
		if ( iOutLength > ( mCH341_PACKET_LENGTH - 1 - 1 - 1 - 1 - 1 ) ) {  // 去掉前2字节后3字节,一个包不够用
			mLength = iOutLength - ( mCH341_PACKET_LENGTH - 1 - 1 - 1 - 1 - 1);  // 多出的长度
			iOutLength -= mLength;  // 第1个包的数据长度
		}
		else mLength = 0;  // 1个包就够用了
		i = 0;
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 命令码
		mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | iOutLength );  // 输出数据,位5-位0为长度
		memcpy( &mBuffer[ i ], iOutBuffer, iOutLength );  // 数据
		i += iOutLength;
		if ( mLength ) {  // 第2包
			mBuffer[ i ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
			i += mCH341_PACKET_LENGTH - i % mCH341_PACKET_LENGTH;  // 跳过当前包剩余部分
			mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 第2个包的首字节仍然是命令码
			mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | mLength );  // 输出数据,位5-位0为长度
			memcpy( &mBuffer[ i ], (PUCHAR)iOutBuffer + iOutLength, mLength );  // 剩余数据
			i += mLength;
		}
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_STO;  // 产生停止位
		mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_MS | 10 );  // 以亳秒为单位延时,位3-位0为延时值,延时10毫秒
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
		return( CH341WriteData( iIndex, mBuffer, &i ) );  // 写出数据块
	}
	return( FALSE );
}

BOOL	WINAPI	X76F640_ReadWithPasswd(  // 读X76F640的块,使用指定的密码 (包括:输出起始位,输出9字节数据(1命令+8密码),查询应答,输出2字节地址,读入数据块)
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iReadCommand,  // 块读命令码
	PVOID			iPasswdBuf,  // 指向一个缓冲区,放置8字节的密码数据
	ULONG			iAddress,  // 指定操作地址
	ULONG			iInLength,  // 准备读取的数据字节数,单次必须小于512字节 ( 每包32 * 16个包 = 512字节 )
	PVOID			oInBuffer )  // 指向一个缓冲区,返回后是读入的数据
{
	UCHAR	mBuffer[ mDEFAULT_BUFFER_LEN ];
	ULONG	i, mLength, mInLen;
	if ( iInLength == 0 || iInLength > ( 16 * mCH341_PACKET_LENGTH ) ) return( FALSE );
	if ( X76F640_CheckPasswd( iIndex, iReadCommand, iPasswdBuf, iAddress ) ) {  // 发出命令及密码检查通过
		i = 0;
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 命令码
		for ( mInLen = 1; mInLen < iInLength; ) {
			mLength = iInLength - mInLen >= mCH341A_CMD_I2C_STM_MAX ? mCH341A_CMD_I2C_STM_MAX : iInLength - mInLen;  // 本次输入有效数据长度
			mBuffer[ i++ ] = (UCHAR)( mCH341A_CMD_I2C_STM_IN | mLength );  // 输入数据,位5-位0为长度
			mInLen += mLength;
			if ( mLength >= mCH341A_CMD_I2C_STM_MAX ) {  // 当前包将满
				mBuffer[ i ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
				i += mCH341_PACKET_LENGTH - i % mCH341_PACKET_LENGTH;  // 跳过当前包剩余部分
				mBuffer[ i++ ] = mCH341A_CMD_I2C_STREAM;  // 新包的命令码
			}
		}
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_IN;  // 输入最后一个字节数据,只接收一个字节并发送无应答
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_STO;  // 产生停止位
		mBuffer[ i++ ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
		mLength = 0;
		if ( CH341WriteRead( iIndex, i, mBuffer, mCH341A_CMD_I2C_STM_MAX, ( iInLength + mCH341A_CMD_I2C_STM_MAX - 1 ) / mCH341A_CMD_I2C_STM_MAX, &mLength, oInBuffer ) ) {  // 执行数据流命令,先输出再输入
			if ( mLength == iInLength ) return( TRUE );
		}
	}
	return( FALSE );
}

/* ********************************************************************************************** */
/* 例子:操作准双向I/O扩展PCF8574 */

BOOL	WINAPI	PCF8574_WriteIO(  // 输出PCF8574的I/O
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iDeviceAddr,  // 设备地址,最低位为命令方向位
	ULONG			iOutByte )  // 准备写出的I/O数据
{  // 可以直接用CH341StreamI2C( iIndex, 2, mBuffer, 0, NULL )实现
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_STA;  // 产生起始位
	mBuffer[ 2 ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | 2 );  // 输出数据,位5-位0为长度,2字节
	mBuffer[ 3 ] = (UCHAR)( iDeviceAddr & 0xFE );  // 设备地址,写操作
	mBuffer[ 4 ] = (UCHAR)iOutByte;  // I/O数据
	mBuffer[ 5 ] = mCH341A_CMD_I2C_STM_STO;  // 产生停止位
	mBuffer[ 6 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 7;
	return( CH341WriteData( iIndex, mBuffer, &mLength ) );  // 写出数据块
}

BOOL	WINAPI	PCF8574_ReadIO(  // 输入PCF8574的I/O
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iDeviceAddr,  // 设备地址,最低位为命令方向位
	PUCHAR			oInByte )  // 指向一个字节的缓冲区,返回后是读入的I/O数据
{  // 可以直接用CH341StreamI2C( iIndex, 1, mBuffer, 1, oInByte )实现
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	ULONG	mLength, mInLen;
	mBuffer[ 0 ] = mCH341A_CMD_I2C_STREAM;  // 命令码
	mBuffer[ 1 ] = mCH341A_CMD_I2C_STM_STA;  // 产生起始位
	mBuffer[ 2 ] = (UCHAR)( mCH341A_CMD_I2C_STM_OUT | 1 );  // 输出数据,位5-位0为长度,1字节
	mBuffer[ 3 ] = (UCHAR)( iDeviceAddr | 0x01 );  // 设备地址,读操作
	mBuffer[ 4 ] = (UCHAR)( mCH341A_CMD_I2C_STM_IN | 1 );  // 输入数据,位5-位0为长度,1字节
	mBuffer[ 5 ] = mCH341A_CMD_I2C_STM_STO;  // 产生停止位
	mBuffer[ 6 ] = mCH341A_CMD_I2C_STM_END;  // 当前包提前结束
	mLength = 7;
	mInLen = 0;
	if ( CH341WriteRead( iIndex, mLength, mBuffer, mCH341A_CMD_I2C_STM_MAX, 1, &mInLen, mBuffer ) ) {  // 执行数据流命令,先输出再输入
		if ( mInLen ) {
			*oInByte = mBuffer[ mInLen - 1 ];  // 返回的数据
			return( TRUE );
		}
	}
	return( FALSE );
}

/* ********************************************************************************************** */
/* 例子:操作双向I/O扩展PCA9554 */

BOOL	WINAPI	PCA9554_SetIO(  // 设置PCA9554的I/O方向
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iDeviceAddr,  // 设备地址,最低位为命令方向位
	ULONG			iSetByte )  // 方向数据
{  // 也可以用CH341WriteI2C实现
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	mBuffer[ 0 ] = (UCHAR)( iDeviceAddr & 0xFE );  // 设备地址,写操作
	mBuffer[ 1 ] = 0x03;
	mBuffer[ 2 ] = (UCHAR)iSetByte;  // I/O方向数据
	return( CH341StreamI2C( iIndex, 3, mBuffer, 0, NULL ) );  // 处理I2C数据流
}

BOOL	WINAPI	PCA9554_WriteIO(  // 输出PCA9554的I/O
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iDeviceAddr,  // 设备地址,最低位为命令方向位
	ULONG			iOutByte )  // 准备写出的I/O数据
{  // 也可以用CH341WriteI2C实现
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	mBuffer[ 0 ] = (UCHAR)( iDeviceAddr & 0xFE );  // 设备地址,写操作
	mBuffer[ 1 ] = 0x01;
	mBuffer[ 2 ] = (UCHAR)iOutByte;  // I/O数据
	return( CH341StreamI2C( iIndex, 3, mBuffer, 0, NULL ) );  // 处理I2C数据流
}

BOOL	WINAPI	PCA9554_ReadIO(  // 输入PCA9554的I/O
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iDeviceAddr,  // 设备地址,最低位为命令方向位
	PUCHAR			oInByte )  // 指向一个字节的缓冲区,返回后是读入的I/O数据
{  // 也可以用CH341ReadI2C实现
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH ];
	mBuffer[ 0 ] = (UCHAR)( iDeviceAddr & 0xFE );  // 设备地址,CH341StreamI2C自动处理读操作
	mBuffer[ 1 ] = 0x00;
	return( CH341StreamI2C( iIndex, 2, mBuffer, 1, oInByte ) );  // 处理I2C数据流
}

/* ********************************************************************************************** */
/* 用EPP或者MEM并口进行多位输出或者多位输入,模拟只读或者只写的SPI时序 */

/* 下面是用EPP并口CH341EppWriteData模拟只是进行输出的SPI时序,参考下图波形(选择等宽的中文字体时才能看出)
       ___                                                           ___
  WR#     |_________________________________________________________|       SPI_CS
       ______    ___    ___    ___    ___    ___    ___    ___    ______
  DS#        |__|   |__|   |__|   |__|   |__|   |__|   |__|   |__|          SPI_CLK
       ____        ______ ______        ______                      ____
  D0       |______|      |      |______|      |______|______|______|        SPI_DOUT0
       ____ ______        ______ ______ ______        ______        ____
  D1       |      |______|      |      |      |______|      |______|        SPI_DOUT1
       ____                      ______                      ______ ____
  D5       |______|______|______|      |______|______|______|      |        SPI_DOUT5

  如果用CH341MemWriteAddr0代替CH341EppWriteData,那么波形如下
       ___                                                           ___
  ADDR    |_________________________________________________________|       SPI_CS
       ______    ___    ___    ___    ___    ___    ___    ___    ______
  WR#        |__|   |__|   |__|   |__|   |__|   |__|   |__|   |__|          SPI_CLK

   相应的源程序如下 */

BOOL	WINAPI	Exam_EppSerialOut(
	ULONG			iIndex )  // 指定CH341设备序号
{
	UCHAR	mBuffer[256];
	ULONG	mLength;
	mBuffer[0]=0x02;
	mBuffer[1]=0x01;
	mBuffer[2]=0x03;
	mBuffer[3]=0x22;
	mBuffer[4]=0x03;
	mBuffer[5]=0x00;
	mBuffer[6]=0x02;
	mBuffer[7]=0x20;
	mLength = 8;  /* 如果多于31个那么在WR#引脚的低电平中间将出现高电平脉冲 */
	return( CH341EppWriteData( iIndex, mBuffer, &mLength ) );
}

/* 下面是用MEM并口CH341MemReadAddr0模拟只是进行输入的SPI时序,参考下图波形(选择等宽的中文字体时才能看出)
       ___                                                                  ___
  ADDR    |________________________________________________________________|       SPI_CS
       _____      __      __      __      __      __      __      __      _____
  RD#       |____|  |____|  |____|  |____|  |____|  |____|  |____|  |____|         SPI_CLK
       ______    ____    ____    ____    ____    ____    ____    ____    ______
  D0/in      |IN|    |IN|    |IN|    |IN|    |IN|    |IN|    |IN|    |IN|          SPI_DIN0
       ______    ____    ____    ____    ____    ____    ____    ____    ______
  D7/in      |IN|    |IN|    |IN|    |IN|    |IN|    |IN|    |IN|    |IN|          SPI_DIN7

  如果用CH341EppReadData代替CH341MemReadAddr0,那么波形如下
       _______________________________________________________________________
  WR#
       _____      __      __      __      __      __      __      __      _____
  DS#       |____|  |____|  |____|  |____|  |____|  |____|  |____|  |____|         SPI_CLK

   相应的源程序如下 */

BOOL	WINAPI	Exam_MemSerialIn(
	ULONG			iIndex )  // 指定CH341设备序号
{
	UCHAR	mBuffer[256];
	ULONG	mLength, i;
	mLength = 8;  /* 如果多于31个那么在ADDR引脚的低电平中间将出现高电平脉冲 */
	if ( CH341MemReadAddr0( iIndex, mBuffer, &mLength ) == FALSE ) return( FALSE );
	for ( i = 0; i < mLength; i ++ ) {
/*		printf( "D0 is %d, D1 is %d, D7 is %d\n", mBuffer[i]&1, mBuffer[i]>>1&1, mBuffer[i]>>7&1 );*/
	}
	return( TRUE );
}

/* ********************************************************************************************** */
/* 用UIO通用I/O位流命令实现自定义的同步串行接口 */

/* UIO方式共可以使用8个I/O引脚D7-D0,最多可以8个输入或者6个输出
   上位机以字节流控制CH341对最终位流进行输入和输出,有4种基本操作和1个结束操作:
#define		mCH341A_CMD_UIO_STM_IN	0x00		// UIO接口的命令流:输入数据D7-D0
#define		mCH341A_CMD_UIO_STM_DIR	0x40		// UIO接口的命令流:设定I/O方向D5-D0,位5-位0为方向数据
#define		mCH341A_CMD_UIO_STM_OUT	0x80		// UIO接口的命令流:输出数据D5-D0,位5-位0为数据
#define		mCH341A_CMD_UIO_STM_US	0xC0		// UIO接口的命令流:以微秒为单位延时,位5-位0为延时值
#define		mCH341A_CMD_UIO_STM_END	0x20		// UIO接口的命令流:命令包提前结束

   例子:操作10位ADC芯片TLC1549,其时序为非标准
   连线: CH341_D0 <-> TLC1549_CS, CH341_D1 <-> TLC1549_IO_CLK, CH341_D7 <-> TLC1549_DOUT
   下面是用UIO通用I/O位流命令实现的任意波形,参考下图波形(选择等宽的中文字体时才能看出)
         ______                                                                        ____________
  D0/out       |______________________________________________________________________|            |_________   TLC1549_CS#
         ____     ___    ___    ___    ___    ___    ___    ___    ___    ___    ___    Delay 24uS    ___
  D1/out     |___| 1 |__| 2 |__| 3 |__| 4 |__| 5 |__| 6 |__| 7 |__| 8 |__| 9 |__| 10|________________| 1 |__|   TLC1549_I/O_CLOCK

  D7/in  ------| A9  |  A8  |  A7  |  A6  |  A5  |  A4  |  A3  |  A2  |  A1  |  A0  |__/-----------| B9  | B8   TLC1549_DATA_OUT

   相应的源程序如下 */

BOOL	WINAPI	TLC1549_ReadADC(  // 读取TLC1549的ADC结果
	ULONG			iIndex,  // 指定CH341设备序号
	PULONG			oLastADC )  // 指向一个双字单元,返回读出的上次ADC的结果
{
#define		TLC1549_MAX_BIT		10	// 10位ADC
	UCHAR	mBuffer[ mCH341_PACKET_LENGTH * 2 ];
	ULONG	i, j, mLength;
	i = 0;
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STREAM;  // 命令码
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x01;  // default status: D0=1, D1=0, CS#=HIGH, I/O_CLOCK=LOW
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_DIR | 0x03;  // D0 output, D1 output, other input
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x00;  // D0=0, CS#=LOW
	for ( j = 0; j < 8; j ++ ) {  // input 8 bit
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x02;  // D1=1, I/O_CLOCK=HIGH
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_IN;  // input 1 byte from D7-D0, input A9,A8,A7,A6,A5,A4,A3,A2
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x00;  // D1=0, I/O_CLOCK=LOW
	}
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_END;  // 当前命令包提前结束,因为一个包放不下,所以分成两个包
	i = mCH341_PACKET_LENGTH;
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STREAM;  // 命令码
	for ( j = 0; j < TLC1549_MAX_BIT - 2; j ++ ) {  // input 2 bit
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x02;  // D1=1, I/O_CLOCK=HIGH
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_IN;  // input 1 byte from D7-D0, input A1,A0
		mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x00;  // D1=0, I/O_CLOCK=LOW
	}
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_OUT | 0x01;  // D0=1, CS#=HIGH
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_US | 24;  // delay 24uS,实际上这个延时完全不需要,因为USB传输每1mS一次,下次传输是在1mS之后
	mBuffer[ i++ ] = mCH341A_CMD_UIO_STM_END;  // 当前命令包提前结束
	mLength = 0;
	j = CH341WriteRead( iIndex, i, mBuffer, 8, 2, &mLength, mBuffer );  // 执行数据流命令,先输出再输入,执行两次输入,每次最多8字节
	*oLastADC = 0;
	if ( j ) {
		if ( mLength == TLC1549_MAX_BIT ) {  // 输入长度正确
			for ( i = 0; i < TLC1549_MAX_BIT; i ++ ) {  // 将每字节的位7合并为10位ADC结果数据
				*oLastADC = ( *oLastADC << 1 ) | ( mBuffer[ i ] >> 7 );  // 位7移到位0
			}
			return( TRUE );
		}
	}
	return( FALSE );
}

/* ********************************************************************************************** */
/* 例子:操作4线接口SPI存储器25F512、25F020 */
/* 连线: CH341_DCK/D3 <-> 25FXX_SCK, CH341_DOUT/D5 <-> 25FXX_SI, CH341_DIN/D7 <-> 25FXX_SO, CH341_D0 <-> 25FXX_CS# */

BOOL	WINAPI	AT25F512_ReadBlock(  // 读AT25F512的块 (包括:输出器件读命令码,输出3字节共24位地址,读入数据块)
	ULONG			iIndex,  // 指定CH341设备序号
	ULONG			iAddress,  // 指定操作地址
	ULONG			iInLength,  // 准备读取的数据字节数,单次建议小于1024字节
	PVOID			oInBuffer )  // 指向一个缓冲区,返回后是读入的数据
{
	static	BOOL	mTheFirst = TRUE;
	if ( mTheFirst ) {  // 首次进入时需要设置I/O方向
		if ( CH341SetStream( iIndex, 0x81 ) == FALSE ) return( FALSE );  // 设置串口流模式:SPI为单入单出,SPI字节中的位顺序是高位在前
		mTheFirst = FALSE;
	}
	if ( iInLength == 0 || iInLength > mDEFAULT_BUFFER_LEN ) return( FALSE );
	*( (PUCHAR)oInBuffer + 0 ) = 0x03;  // 读存储器命令码,注意各器件不一定命令码相同
	*( (PUCHAR)oInBuffer + 1 ) = (UCHAR)( iAddress >> 16 & 0xFF );  // 指定读操作的地址A23-A16
	*( (PUCHAR)oInBuffer + 2 ) = (UCHAR)( iAddress >> 8 & 0xFF );  // 指定读操作的地址A15-A8
	*( (PUCHAR)oInBuffer + 3 ) = (UCHAR)( iAddress & 0xFF );  // 指定读操作的地址A7-A0
//	memset( (PUCHAR)oInBuffer + 4, 0xFF, iInLength );  // 对于有些SPI器件,可能要求在读出数据时SI输入保持为1或者0,那么就要在此设置
	if ( CH341StreamSPI4( iIndex, 0x80, iInLength + 4, oInBuffer ) == FALSE ) return( FALSE );  // 处理4线接口SPI数据流,自动片选为D0
/* 对于25F512的读操作,要先输出4个字节命令及地址,再输入若干个字节数据,调用API和API返回时都是指总长度,所以返回数据的前4个字节是在输出命令及地址时输入的,应该丢弃 */
	memmove( oInBuffer, (PUCHAR)oInBuffer + 4, iInLength );  // 因为CH341的SPI是数据流,所以实际返回数据应该去掉自己发出的4个字节(命令和地址)
	return( TRUE );
}

/* ********************************************************************************************** */
/* 例子:操作类似SPI的非标准串行时序的8位ADC芯片ADC0831、TLC0831 */
/* 连线: CH341_DCK/D3 <-> ADC0831_CLK, CH341_DIN/D7 <-> ADC0831_DO, CH341_D2 <-> ADC0831_CS# */

BOOL	WINAPI	ADC0831_ReadADC(  // 读取ADC结果
	ULONG			iIndex,  // 指定CH341设备序号
	PUCHAR			oADC )  // 指向一个字节单元,返回读出的ADC结果
{
	static	BOOL	mTheFirst = TRUE;
	UCHAR	mBuffer[ 256 ];
	ULONG	i;
	if ( mTheFirst ) {  // 首次进入时需要设置I/O方向
		if ( CH341Set_D5_D0( iIndex, 0x0C, 0x04 ) == FALSE ) return( FALSE );  // 设置CH341的D5-D0引脚的I/O方向,DCK/D3输出默认为0,D2输出默认为1
		mTheFirst = FALSE;
	}
	for ( i = 0; i < 12; i ++ ) {
		mBuffer[ i ] = 0x00;  // CS=0 for 1st bit to 12th bit
	}
	mBuffer[ i++ ] = 0x04;  // CS=1 for 13th bit
	if ( CH341BitStreamSPI( iIndex, i, mBuffer ) == FALSE ) return( FALSE );  // 处理SPI位数据流,输入输出共13位,实际未全部用到
	*oADC = 0;
	for ( i = 0; i < 8; i ++ ) {  // 将每字节的位7合并为8位ADC结果数据
		*oADC = ( *oADC << 1 ) | ( mBuffer[ i + 1 ] >> 7 );  // 位7移到位0,跳过首字节无效数据,第2个时钟的输入数据才是MSB位
	}
	return( TRUE );
}

/* ********************************************************************************************** */

main( ) {
	return(1);
}