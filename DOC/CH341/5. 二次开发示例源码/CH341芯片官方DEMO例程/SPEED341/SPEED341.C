//****************************************
//**  Copyright  (C)  W.ch  1999-2004   **
//**  Web:  http://www.winchiphead.com  **
//****************************************
//**  C, VC5.0                          **
//****************************************
//
// CH341 测试并口传输速度
//


#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<conio.h>
#include	<winioctl.h>

#include	"CH341DLL.H"				// CH341的动态链接库

//程序入口
void main ( )
{
	unsigned char	mBuffer[4100];
	unsigned long	i, mLength, mTestCount, mErrCnt, mStep, mTotal;
	double          speed;

	printf( "\nCH341 Bulk Data Test Program V1.0 ,   Copyright (C) W.ch 2003.12\n" );

// 需要使用DLL则需要先加载
	printf( "*** Load DLL: CH341DLL.DLL \n" );
	if ( LoadLibrary( "CH341DLL.DLL" ) == NULL ) return;  // 加载DLL失败,可能未安装到系统中

	printf( "*** CH341OpenDevice: 0# \n" );
	if ( CH341OpenDevice( 0 ) == INVALID_HANDLE_VALUE ) return;  /* 使用之前必须打开设备 */
	mErrCnt = 0;
	
	printf( "*** Step-2: test speed of download data: 2048KB data \n" );
	for ( i=0; i<4096; i+=4 ) *(unsigned long *)(&mBuffer[i])=rand();  // 产生随机数以发送
	mTotal=0;
	mStep=GetTickCount();
	for ( mTestCount=0; mTestCount<500; ++mTestCount )  // 循环测试
	{
		*(unsigned long *)(&mBuffer[4])=mTestCount;
		mLength = 4096;
		if ( CH341EppWriteData( 0, &mBuffer, &mLength ) )  // 发送成功
		{
			if ( mLength != 4096 ) printf( "S2-C%ld CH341WriteData actual length short %ld (4096)\n", mLength );
			mTotal +=mLength;  // 累计长度
		}
		else {  // 写操作失败
			mErrCnt++;
			printf( "S2-C%ld CH341WriteData return error\n", mTestCount );
		}
	}
	mLength=GetTickCount();
	mLength=mLength-mStep;
	speed=1000;
	if ( mLength !=0 ) speed=speed*mTotal/mLength;
	else speed=9999999;
	printf( "*** download speed = %7.1f Bytes/Sec, total=%ld bytes, time=%ld mS\n", speed, mTotal, mLength);
	Sleep(100);

	printf( "*** Step-3: test speed of upload data: 2048KB data\n" );
	mTotal=0;
	mStep=GetTickCount();
	for ( mTestCount=0; mTestCount<500; ++mTestCount )  // 循环测试
	{
		mLength = 4096;
		if ( CH341EppReadData( 0, &mBuffer, &mLength ) )  // 接收成功
		{
			if ( mLength != 4096 ) printf( "S3-C%ld CH341ReadData actual length short %ld (4096)\n", mLength );
			mTotal +=mLength;  // 累计长度
		}
		else {  // 读操作失败
			mErrCnt++;
			printf( "S3-C%ld CH341ReadData return error\n", mTestCount );
		}
	}
	mLength=GetTickCount();
	mLength=mLength-mStep;
	speed=1000;
	if ( mLength !=0 ) speed=speed*mTotal/mLength;
	else speed=9999999;
	printf( "*** upload speed = %7.1f Bytes/Sec, total=%ld bytes, time=%ld mS\n", speed, mTotal, mLength);
	Sleep(100);

// 关闭CH341设备,如果不继续使用则必须关闭设备,就象读写完硬盘中的数据文件后要关闭一样
	printf( "*** Total error = %ld \n", mErrCnt );
	printf( "*** CH341CloseDevice: 0 \n" );
	CH341CloseDevice( 0 );

	printf( "\nExit.\n" );
	getch();
}

