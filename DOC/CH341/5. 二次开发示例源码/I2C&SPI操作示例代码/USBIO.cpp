//***************USBIO function definations *******************
#include "USBIO.H"
#define MAXLEN 4096

extern UINT mIndex;

void CheckNum(UCHAR value)
{
	if(value <0 || value >255)
	{
		printf("the entry value is illegal!");
		return;
	}
	
}


//GPIO 控制函数
void GPIO()
{
	ULONG iStatus = 0x00ff;
	UCHAR iData = 0xff;
	UCHAR iDirect = 0xff;

	system("cls");
	printf("\n****************************GPIO Test Modual*******************************");
	printf("\nAPI1:USBIO_GetStatus(mIndex,iStatus) ");
	printf("\nAPI2:USBIO_Set_D5_D0(mIndex,iSetDir,iSetData)");
	printf("\n***************************************************************************");
	
	printf("\n\n<1>PORTS STATUS INPUT");
	printf("\n/**Introductions:Set the input/ouput of the ports D0-D5 in Hex(1:output 0:input)");
	printf("\n/**Example: 05 stands for D0 D2 output ; D1 D3 D4 D5 input ");
	printf("\n\nSET INPUT/OUTPUT STATUS OF D5-D0 : ");
	
	scanf("%X",&iDirect);
	iDirect = iDirect&0x3f;
	//	CheckNum(iDirect);
	printf("\n\n<2>PORS VALUE SET");
	printf("\n/**Introductions:Set the input/ouput of the ports D0-D5 in Hex(1:highlevel 0:lowlevel)");
	printf("\n/**Example:05 stands for D0 D2 highlevel ; D1 D3 D4 D5 lowlevel ");
	printf("\n\nSET INPUT/OUTPUT VALUE OF D5-D0 : ");
	scanf("%X",&iData);
	iData = iData&0x3f;
	//CheckNum(iData);
	
	USBIO_GetStatus(mIndex,&iStatus);
	USBIO_Set_D5_D0(mIndex,iDirect,iData);
	
	printf("\n*********************************** RESULT *********************************");
	printf("\n\nGPIO operation is completed\n");
	printf("\nStatus of the ports : 0X%X",iStatus&0x3f);
	
	printf("\n\nPress any key to the main menu!");
	getch();
	
}

void I2CStream()
{
	UCHAR Data[MAXLEN];
	memset(Data,0,MAXLEN);
	
	UINT iWRLen = 0;
	UINT iRDLen = 0;
	UINT i =0;
	UCHAR SCLK = 0;
	
	system("cls");
	printf("\n*********************I2CStream Test Modual*******************************");
	printf("\nAPI:USBIO_StreamI2C(mIndex,iWriteLength,WriteBuffer,iReadLength,ReadBuffer)");
	printf("\n*************************************************************************");
	
	
	//设置时钟频率
    printf("\n\n\n<1>SELECT FREQUENCY of SCL:  <0> 20Khz <1> 100Khz <2> 400Khz <3> 750Khz\n");
	printf("Select:");
	scanf("%d",&SCLK);
	
	switch(SCLK)
	{
		
	case 1:
		USBIO_SetStream(mIndex,0x81);
		break;
	case 2:
		USBIO_SetStream(mIndex,0x82);
		break;
	case 3:
		USBIO_SetStream(mIndex,0x83);
		break;
	default:
		USBIO_SetStream(mIndex,0x80);
		break;
	}
	
    //写入数据的长度
	printf("\n<2>INPUT THE NUMBER OF WRITE BYTES : ");
	scanf("%d",&iWRLen);
	
    //写入的数据
	printf("\n<3>INPUT THE WRITE BYTES(HEX) : ");
	while(i<iWRLen)
	{
		scanf("%X",&Data[i++]);
	}
	
    //读出数据长度
	printf("\n<4>INPUT THE NUMBER OF READ BYTES : ");
	scanf("%d",&iRDLen);
	
	UCHAR* iRead = new UCHAR[iRDLen];
	memset(iRead,0,iRDLen);
	
	if(!USBIO_StreamI2C(mIndex,iWRLen,Data,iRDLen,iRead))
	{
		printf("Read data fail!");
	}
	
	//数据显示
	printf("\n****************************** RESULT **************************************");
	printf("\n<5>READ OUT DATAS : ");
	for(i=0;i<iRDLen;i++)
	{
		printf("%X ",iRead[i]);
	}
	
	delete[] iRead;
	iRead = NULL;
	
	getch();
	
}

void SPIByte()
{
	UCHAR CS = 0;
	UCHAR ORDER = 0;
	UCHAR iChipSelect =0x80;
	
	UINT DataLen = 0;
	UINT i=0;
	
	system("cls");
	printf("\n**************************SPI Test Modual*******************************");
	printf("\n API: USBIO_StreamSPI4(mIndex,iChipSelect,Length,Buffer)");
    printf("\n*************************************************************************");
	
	UCHAR CSEN = 0;//ENABLE 
	//设置时钟频率和首字节位置
	printf("\n\n<1>CHIP SELECT ENABLE: <0> ENABLE <1> UNENABLE");
	printf("\nSelect:");
	scanf("%d",&CSEN);


	if(CSEN == 0)
	{

		printf("\n\n<2>CHIP SELECT:  <0> CS0 <1> CS1 <2> CS2");
		printf("\nSelect:");
		scanf("%d",&CS);
	}

	printf("\n<3>BYTE ORDER SELECT:  <0> MSB first    <1> LSB first ");
	printf("\nSelect:");
	scanf("%d",&ORDER);
	
	
	switch((CSEN+1)*10+CS)
	{
		
	case 10:
		iChipSelect = 0x80;
		break;
	case 11:		
		iChipSelect = 0x81;
		break;
	case 12:
		iChipSelect = 0x82;
		break;
	case 13:
		iChipSelect = 0x83;
		break;
	case 20:
		iChipSelect = 0x00;
		break;
	case 21:
		iChipSelect = 0x01;
		break;
	case 22:
		iChipSelect = 0x02;
		break;
	case 23:
		iChipSelect = 0x03;
		break;
	default:
		iChipSelect = 0x00;
		break;
	}
	
	//数据传输长度
	printf("\n<3>INPUT TRANSFORM LENGTH : ");
	scanf("%d",&DataLen);
	
	
	//输入传输的数据
	UCHAR* pData = new UCHAR[DataLen];
	memset(pData,0,DataLen);
	
	
	printf("\n<4>INPUT BYTE STREAM(End with -1):");
	
	do{
		scanf("%X",&pData[i++]);
		
	}while(pData[i-1] != 0xFF);
	pData[i-1] = 0;
	


	/*set stream
	BOOL	WINAPI	USBIO_SetStream(  // 设置串口流模式
	ULONG			iIndex,  // 指定mUSBIO_PACKET_LENGTH设备序号
	ULONG			iMode );  // 指定模式,见下行
// 位1-位0: I2C接口速度/SCL频率, 00=低速/20KHz,01=标准/100KHz(默认值),10=快速/400KHz,11=高速/750KHz
// 位2:     SPI的I/O数/IO引脚, 0=单入单出(D3时钟/D5出/D7入)(默认值),1=双入双出(D3时钟/D5出D4出/D7入D6入)
// 位7:     SPI字节中的位顺序, 0=低位在前, 1=高位在前
// 其它保留,必须为0
	*/
	if(ORDER == 0)
	{
	USBIO_SetStream(mIndex,0x00);//Set SPI model;
	}
	else
	{
		USBIO_SetStream(mIndex,0x80);//Set SPI model;

	}
	printf("%X,%X,%X,%X,%X",iChipSelect,DataLen,pData[0],pData[1],pData[2]);
	printf("\n****************************** RESULT **********************************");
	//获取返回的数据和显示数据
	USBIO_Set_D5_D0(mIndex,0xff,0x00);  //CS拉低

	if(!USBIO_StreamSPI4(mIndex,iChipSelect,DataLen,pData))
	{
		printf("\nFail to SPI operation!");
		return;
	}
	
	printf("\nDATAS FROM MISO :  ");
	i =0;
	while(i<DataLen)
	{
		printf("%X ",pData[i++]);
	}
	
	getch();
}


//*********************SPI 位传输模式**********************
void SPIBit()
{
	UINT iNumber = 0;
	system("cls");
	printf("\n***************************** SPIBit Test Modual *****************************");
	printf("\n API:USBIO_BitStreamSPI(mIndex,Length,Buffer)                              ***");
	printf("\n******************************************************************************");
	
	printf("\nThe order of the Bytes: ");
	printf("\n          Bit4 for MOSI, Bit7 for MISO;");
	printf("\n          Bit0,1,2 for CS0,CS1,CS2\n");
	printf("****************************************************************************");
	
	printf("\n\n<1>INPUT THE DATA NUMBER: ");
	scanf("%d",&iNumber);
	
	UCHAR* wBuf = new UCHAR[iNumber];//放置发送的数据，只有bit4发送，bit0，1，2分别是D0,D1,D2的片选
	UCHAR* rBuf = new UCHAR[iNumber];//放置接收的数据，从bit7接收，bit0，1，2分别是D0,D1,D2的片选
	
	memset(wBuf,0,iNumber);
	
	if(iNumber>256)
	{
		printf("The number is too big to transmit!");
		return;
	}
	
	USBIO_Set_D5_D0(mIndex,0xff,0xff);//设置端口数据
	
	printf("\n<2>INPUT BYTE STREAM(BIT4 FOR MOSI)<End with -1> : ");
	UINT i = 0;
	do
	{
		scanf("%X",&wBuf[i++]);
		
	}while(wBuf[i-1]!=0XFF);
	
	//Bit Stream send 
	if (!USBIO_BitStreamSPI(mIndex,iNumber,wBuf)) 
	{
		return;     
	}
	
	//显示读取的数据
	printf("\n***************************** RESULT *************************************");
	printf("\n<3>MISO BIT STREAM : ");
	i = 0;
	while(i<iNumber)
	{
		rBuf[i] = (wBuf[i]>>7)&0x01;
		printf("%d ",rBuf[i]);
		i++;
	}
	
	getch();	
}
