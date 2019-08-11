//*****************USBIO.H**************
#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<conio.h>
#include	<winioctl.h>
#include	"USBIOX.H"				// USB2I2CµÄ¶¯Ì¬Á´½Ó¿â


void GPIO();
void I2CStream();
void SPIByte();
void SPIBit();
void Exit();


void CheckNum(UCHAR value);
