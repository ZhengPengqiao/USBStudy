Attribute VB_Name = "USBIOXDLL"
Option Explicit
' 2004.05.28, 2004.10.20, 2005.01.08, 2005.03.25, 2005.04.28
'****************************************
'**  Copyright  (C)  W.ch  1999-2005   **
'**  Web:  http://www.USB-I2C-SPI.com  **
'****************************************
'**  DLL for USB interface chip USB2ISP**
'**  C, VC6.0                          **
'****************************************
'
Public Enum EEPROM_TYPE   ' EEPROM型号定义
  ID_24C01 = 0
  ID_24C02 = 1
  ID_24C04 = 2
  ID_24C08 = 3
  ID_24C16 = 4
  ID_24C32 = 5
  ID_24C64 = 6
  ID_24C128 = 7
  ID_24C256 = 8
  ID_24C512 = 9
  ID_24C1024 = 10
  ID_24C2048 = 11
  ID_24C4096 = 12
End Enum

Type mUspValue
        mUspValueLow As Byte                  ' 02H 值参数低字节
        mUspValueHigh As Byte                 ' 03H 值参数高字节
End Type
Type mUspIndex
        mUspIndexLow As Byte                  ' 04H 索引参数低字节
        mUspIndexHigh  As Byte                ' 05H 索引参数高字节
End Type
Type USB_SETUP_PKT                            ' USB控制传输的建立阶段的数据请求包结构
    mUspReqType As Byte                       ' 00H 请求类型
    mUspRequest As Byte                       ' 01H 请求代码
    mUspValue As mUspValue                    ' 02H-03H 值参数
    mUspIndex As mUspIndex                    ' 04H-05H 索引参数
    mLength As Integer                        ' 06H-07H 数据阶段的数据长度
End Type

Public Const INVALID_HANDLE_VALUE = -1        '错误码
Public Const mUSBIO_PACKET_LENGTH = 32           ' USB2ISP支持的数据包的长度
Public Const mUSBIO_PKT_LEN_SHORT = 8               ' USB2ISP支持的短数据包的长度

Type WIN32_COMMAND                              '定义WIN32命令接口结构
   mFunction As Long                            '输入时指定功能代码或者管道号
                                                '输出时返回操作状态
   mLength As Long                              '存取长度,返回后续数据的长度
   mBuffer(mUSBIO_PACKET_LENGTH - 1) As Byte    '数据缓冲区,长度为0至255B
End Type
Public mWIN32_COMMAND As WIN32_COMMAND

Public Const FILE_DEVICE_UNKNOWN = &H22
Public Const FILE_ANY_ACCESS = 0
Public Const METHOD_BUFFERED = 0
' WIN32应用层接口命令
Public Const IOCTL_USBIO_COMMAND = (FILE_DEVICE_UNKNOWN * (2 ^ 16) + FILE_ANY_ACCESS * 2 ^ 14 + &HF34 * 2 ^ 2 + METHOD_BUFFERED)     ' 专用接口

Const mWIN32_COMMAND_HEAD = 8         ' WIN32命令接口的头长度

Public Const mUSBIO_MAX_NUMBER = 16              ' 最多同时连接的USB2ISP数

Public Const mMAX_BUFFER_LENGTH = &H1000              ' 数据缓冲区最大长度4096

Public Const mMAX_COMMAND_LENGTH = (mWIN32_COMMAND_HEAD + mMAX_BUFFER_LENGTH)             ' 最大数据长度加上命令结构头的长度

Public Const mDEFAULT_BUFFER_LEN = &H400              ' 数据缓冲区默认长度1024

Public Const mDEFAULT_COMMAND_LEN = (mWIN32_COMMAND_HEAD + mDEFAULT_BUFFER_LEN)       ' 默认数据长度加上命令结构头的长度


' USB2ISP端点地址
Public Const mUSBIO_ENDP_INTER_UP = &H81              ' USB2ISP的中断数据上传端点的地址
Public Const mUSBIO_ENDP_INTER_DOWN = &H1             ' USB2ISP的中断数据下传端点的地址
Public Const mUSBIO_ENDP_DATA_UP = &H82              ' USB2ISP的数据块上传端点的地址
Public Const mUSBIO_ENDP_DATA_DOWN = &H2            ' USB2ISP的数据块下传端点的地址

' 设备层接口提供的管道操作命令
Public Const mPipeDeviceCtrl = &H4                  ' USB2ISP的综合控制管道
Public Const mPipeInterUp = &H5                       ' USB2ISP的中断数据上传管道
Public Const mPipeDataUp = &H6                         ' USB2ISP的数据块上传管道
Public Const mPipeDataDown = &H7                     ' USB2ISP的数据块下传管道

' 应用层接口的功能代码
Public Const mFuncNoOperation = &H0                  ' 无操作
Public Const mFuncGetVersion = &H1                    ' 获取驱动程序版本号
Public Const mFuncGetConfig = &H2                   ' 获取USB设备配置描述符
Public Const mFuncSetTimeout = &H9                    ' 设置USB通讯超时
Public Const mFuncSetExclusive = &HB                  ' 设置独占使用
Public Const mFuncResetDevice = &HC                  ' 复位USB设备
Public Const mFuncResetPipe = &HD                     ' 复位USB管道
Public Const mFuncAbortPipe = &HE                      ' 取消USB管道的数据请求

' USB2ISP并口专用的功能代码
Public Const mFuncSetParaMode = &HF                   ' 设置并口模式
Public Const mFuncReadData0 = &H10                   ' 从并口读取数据块0
Public Const mFuncReadData1 = &H11                   ' 从并口读取数据块1
Public Const mFuncWriteData0 = &H12                  ' 向并口写入数据块0
Public Const mFuncWriteData1 = &H13                  ' 向并口写入数据块1
Public Const mFuncWriteRead = &H14                    ' 先输出再输入


' USB设备标准请求代码
Public Const mUSB_CLR_FEATURE = &H1
Public Const mUSB_SET_FEATURE = &H3
Public Const mUSB_GET_STATUS = &H0
Public Const mUSB_SET_ADDRESS = &H5
Public Const mUSB_GET_DESCR = &H6
Public Const mUSB_SET_DESCR = &H7
Public Const mUSB_GET_CONFIG = &H8
Public Const mUSB_SET_CONFIG = &H9
Public Const mUSB_GET_INTERF = &HA
Public Const mUSB_SET_INTERF = &HB
Public Const mUSB_SYNC_FRAME = &HC

' USB2ISP控制传输的厂商专用请求类型
Public Const mUSBIO_VENDOR_READ = &HC0                ' 通过控制传输实现的USB2ISP厂商专用读操作
Public Const mUSBIO_VENDOR_WRITE = &H40             ' 通过控制传输实现的USB2ISP厂商专用写操作

' USB2ISP控制传输的厂商专用请求代码
Public Const mUSBIO_PARA_INIT = &HB1                 ' 初始化并口
Public Const mUSBIO_I2C_STATUS = &H52                ' 获取I2C接口的状态
Public Const mUSBIO_I2C_COMMAND = &H53               ' 发出I2C接口的命令


Public Const mUSBIOA_CMD_I2C_STM_STA = &H74          ' I2C接口的命令流:产生起始位
Public Const mUSBIOA_CMD_I2C_STM_STO = &H75           ' I2C接口的命令流:产生停止位
Public Const mUSBIOA_CMD_I2C_STM_OUT = &H0           'I2C接口的命令流:输出数据,位5-位0为长度,后续字节为数据,0长度则只发送一个字节并返回应答
Public Const mUSBIOA_CMD_I2C_STM_IN = &HC0           ' I2C接口的命令流:输入数据,位5-位0为长度,0长度则只接收一个字节并发送无应答
Public Const mUSBIOA_CMD_I2C_STM_SET = &H60           ' I2C接口的命令流:设置参数,位2=SPI的I/O数(0=单入单出,1=双入双出),位1位0=I2C速度(00=低速,01=标准,10=快速,11=高速)
Public Const mUSBIOA_CMD_I2C_STM_US = &H40           ' I2C接口的命令流:以微秒为单位延时,位3-位0为延时值
Public Const mUSBIOA_CMD_I2C_STM_MS = &H50           ' I2C接口的命令流:以亳秒为单位延时,位3-位0为延时值
Public Const mUSBIOA_CMD_I2C_STM_DLY = &HF           ' I2C接口的命令流单个命令延时的最大值
Public Const mUSBIOA_CMD_I2C_STM_END = &H0            ' I2C接口的命令流:命令包提前结束


' 直接输入的状态信号的位定义
Public Const mStateBitERR = &H100                     ' 只读,ERR#引脚输入状态,1:高电平,0:低电平
Public Const mStateBitPEMP = &H200                   ' 只读,PEMP引脚输入状态,1:高电平,0:低电平
Public Const mStateBitINT = &H400                     ' 只读,INT#引脚输入状态,1:高电平,0:低电平
Public Const mStateBitSLCT = &H800                  ' 只读,SLCT引脚输入状态,1:高电平,0:低电平
Public Const mStateBitSDA = &H800000              ' 只读,SDA引脚输入状态,1:高电平,0:低电平




Declare Function USBIO_OpenDevice Lib "USBIOX.DLL" (ByVal iIndex As Long) As Long
' 打开USB2ISP设备,返回句柄,出错则无效
' iIndex  指定USB2ISP设备序号,0对应第一个设备

Declare Sub USBIO_CloseDevice Lib "USBIOX.DLL" (ByVal iIndex As Long)
' 关闭USB2ISP设备
' iIndex    指定USB2ISP设备序号

Declare Function USBIO_GetVersion Lib "USBIOX.DLL" () As Long

' 获得DLL版本号,返回版本号

Declare Function USBIO_DriverCommand Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef ioCommand As WIN32_COMMAND) As Long
' 直接传递命令给驱动程序,出错则返回0,否则返回数据长度
' iIndex,  ' 指定USB2ISP设备序号,V1.6以上DLL也可以是设备打开后的句柄
' ioCommand   命令结构的地址
' 该程序在调用后返回数据长度,并且仍然返回命令结构,如果是读操作,则数据返回在命令结构中,
' 返回的数据长度在操作失败时为0,操作成功时为整个命令结构的长度,例如读一个字节,则返回mWIN32_COMMAND_HEAD+1,
' 命令结构在调用前,分别提供:管道号或者命令功能代码,存取数据的长度(可选),数据(可选)
' 命令结构在调用后,分别返回:操作状态代码,后续数据的长度(可选),
'   操作状态代码是由WINDOWS定义的代码,可以参考NTSTATUS.H,
'   后续数据的长度是指读操作返回的数据长度,数据存放在随后的缓冲区中,对于写操作一般为0

Declare Function USBIO_GetDrvVersion Lib "USBIOX.DLL" () As Long

' 获得驱动程序版本号,返回版本号,出错则返回0

Declare Function USBIO_ResetDevice Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean

'复位USB设备
' iIndex  指定USB2ISP设备序号

Declare Function USBIO_GetDeviceDescr Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' 读取设备描述符
' iIndex,   指定USB2ISP设备序号
' oBuffer   指向一个足够大的缓冲区,用于保存描述符
' ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_GetConfigDescr Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' 读取配置描述符
'  iIndex,    指定USB2ISP设备序号
'  oBuffer,   指向一个足够大的缓冲区,用于保存描述符
'  ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_SetIntRoutine Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iIntRoutine As Long) As Boolean
'设定中断服务程序
' 指定USB2ISP设备序号
'指定中断服务程序,为NULL则取消中断服务,否则在中断时调用该程序


Declare Function USBIO_ReadInter Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iStatus As Long) As Boolean
' 读取中断数据
' iIndex,  指定USB2ISP设备序号
' iStatus   指向一个双字单元,用于保存读取的中断状态数据,见下行
' 位7-位0对应USB2ISP的D7-D0引脚
'  位8对应USB2ISP的ERR#引脚, 位9对应USB2ISP的PEMP引脚, 位10对应USB2ISP的INT#引脚, 位11对应USB2ISP的SLCT引脚

Declare Function USBIO_AbortInter Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
' 放弃中断数据读操作
' iIndex   指定USB2ISP设备序号

Declare Function USBIO_ReadData0 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' 从0#端口读取数据块
 ' iIndex     指定USB2ISP设备序号
 ' oBuffer   指向一个足够大的缓冲区,用于保存读取的数据
 ' ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_ReadData1 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' 从1#端口读取数据块
' iIndex,  指定USB2ISP设备序号
' oBuffer 指向一个足够大的缓冲区,用于保存读取的数据
' ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_AbortRead Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
' 放弃数据块读操作
' iIndex    指定USB2ISP设备序号

Declare Function USBIO_WriteData0 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
' 向0#端口写出数据块
' iIndex,    指定USB2ISP设备序号
' iBuffer     指向一个缓冲区,放置准备写出的数据
' ioLength  指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_WriteData1 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
' 向1#端口写出数据块
' iIndex,    指定USB2ISP设备序号
' iBuffer,    指向一个缓冲区,放置准备写出的数据
' ioLength   指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_AbortWrite Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
' 放弃数据块写操作
' iIndex   指定USB2ISP设备序号

Declare Function USBIO_GetStatus Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iStatus As Long) As Boolean
'  通过USB2ISP直接输入数据和状态
'  iIndex,   指定USB2ISP设备序号
'  iStatus  指向一个双字单元,用于保存状态数据,见下行
'  位7-位0对应USB2ISP的D7-D0引脚
'  位8对应USB2ISP的ERR#引脚, 位9对应USB2ISP的PEMP引脚, 位10对应USB2ISP的INT#引脚, 位11对应USB2ISP的SLCT引脚, 位23对应USB2ISP的SDA引脚
'  位13对应USB2ISP的BUSY/WAIT#引脚, 位14对应USB2ISP的AUTOFD#/DATAS#引脚,位15对应USB2ISP的SLCTIN#/ADDRS#引脚

Declare Function USBIO_ReadI2C Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iDevice As Byte, ByVal iAddr As Byte, ByRef oByte As Byte) As Boolean

'  从I2C接口读取一个字节数据
'  iIndex,   指定USB2ISP设备序号
'  iDevice,    低7位指定I2C设备地址
'  iAddr,    指定数据单元的地址
'  oByte    指向一个字节单元,用于保存读取的字节数据

Declare Function USBIO_WriteI2C Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iDevice As Byte, ByVal iAddr As Byte, ByVal iByte As Byte) As Boolean

'    向I2C接口写入一个字节数据
'    iIndex,   指定USB2ISP设备序号
'    iDevice,   低7位指定I2C设备地址
'    iAddr,  指定数据单元的地址
'    iByte  待写入的字节数据

Declare Function USBIO_EppReadData Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
'  EPP方式读数据: WR#=1, DS#=0, AS#=1, D0-D7=input
'  iIndex,    指定USB2ISP设备序号
'  oBuffer,    指向一个足够大的缓冲区,用于保存读取的数据
'  ioLength    指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_EppReadAddr Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
'  EPP方式读地址: WR#=1, DS#=1, AS#=0, D0-D7=input
'  iIndex,    指定USB2ISP设备序号
'  oBuffer,    指向一个足够大的缓冲区,用于保存读取的地址数据
'  ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_EppWriteData Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
'   EPP方式写数据: WR#=0, DS#=0, AS#=1, D0-D7=output
'   iIndex,     指定USB2ISP设备序号
'   iBuffer,    指向一个缓冲区,放置准备写出的数据
'   ioLength     指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_EppWriteAddr Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
'   EPP方式写地址: WR#=0, DS#=1, AS#=0, D0-D7=output
'   iIndex,    指定USB2ISP设备序号
'   iBuffer,    指向一个缓冲区,放置准备写出的地址数据
'   ioLength   指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_MemReadAddr0 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' MEM方式读地址0: WR#=1, DS#/RD#=0, AS#/ADDR=0, D0-D7=input
' iIndex,    指定USB2ISP设备序号
' oBuffer,     指向一个足够大的缓冲区,用于保存从地址0读取的数据
' ioLength   指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_MemReadAddr1 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' MEM方式读地址1: WR#=1, DS#/RD#=0, AS#/ADDR=1, D0-D7=input
' iIndex,    指定USB2ISP设备序号
' oBuffer,    指向一个足够大的缓冲区,用于保存从地址1读取的数据
' ioLength    指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_MemWriteAddr0 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
' MEM方式写地址0: WR#=0, DS#/RD#=1, AS#/ADDR=0, D0-D7=output
' iIndex,    指定USB2ISP设备序号
' iBuffer,    指向一个缓冲区,放置准备向地址0写出的数据
' ioLength    指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_MemWriteAddr1 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
'  MEM方式写地址1: WR#=0, DS#/RD#=1, AS#/ADDR=1, D0-D7=output
'  iIndex,   指定USB2ISP设备序号
'  iBuffer,    指向一个缓冲区,放置准备向地址1写出的数据
'  ioLength      指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_SetExclusive Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iExclusive As Long) As Boolean
' 设置独占使用当前USB2ISP设备
' iIndex,    指定USB2ISP设备序号
' iExclusive  为0则设备可以共享使用,非0则独占使用

Declare Function USBIO_SetTimeout Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iWriteTimeout As Long, ByVal iReadTimeout As Long) As Boolean
'  设置USB数据读写的超时
'  iIndex,  // 指定USB2ISP设备序号
'  iWriteTimeout  指定USB写出数据块的超时时间,以毫秒mS为单位,0xFFFFFFFF指定不超时(默认值)
'  iReadTimeout  指定USB读取数据块的超时时间,以毫秒mS为单位,0xFFFFFFFF指定不超时(默认值)

Declare Function USBIO_ReadData Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef oBuffer As Any, ByRef ioLength As Long) As Boolean
' 读取数据块
' iIndex,    指定USB2ISP设备序号
' oBuffer,    指向一个足够大的缓冲区,用于保存读取的数据
' ioLength      指向长度单元,输入时为准备读取的长度,返回后为实际读取的长度

Declare Function USBIO_WriteData Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iBuffer As Any, ByRef ioLength As Long) As Boolean
'  写出数据块
'  iIndex,    指定USB2ISP设备序号
'  iBuffer,    指向一个缓冲区,放置准备写出的数据
'  ioLength   指向长度单元,输入时为准备写出的长度,返回后为实际写出的长度

Declare Function USBIO_GetDeviceName Lib "USBIOX.DLL" (ByVal iIndex As Long) As Long           ''''
' 返回指向USB2ISP设备名称的缓冲区,出错则返回NULL
' iIndex   指定USB2ISP设备序号,0对应第一个设备

Declare Function USBIO_FlushBuffer Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
' 清空USB2ISP的缓冲区
' iIndex   指定USB2ISP设备序号

Declare Function USBIO_WriteRead Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iWriteLength As Long, ByRef iWriteBuffer As Any, ByVal iReadStep As Long, ByVal iReadTimes As Long, ByRef oReadLength As Long, ByRef oReadBuffer As Any) As Boolean
' USBIO_WriteRead   执行数据流命令,先输出再输入
' iIndex,    指定USB2ISP设备序号
' iWriteLength,   写长度,准备写出的长度
' iWriteBuffer,    指向一个缓冲区,放置准备写出的数据
' iReadStep,    准备读取的单个块的长度, 准备读取的总长度为(iReadStep*iReadTimes)
' iReadTimes,    准备读取的次数
' oReadLength,    指向长度单元,返回后为实际读取的长度
' oReadBuffer      指向一个足够大的缓冲区,用于保存读取的数据

Declare Function USBIO_SetStream Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iMode As Long) As Boolean
' USBIO_SetStream   设置串口流模式
' iIndex,    指定USB2ISP设备序号
' iMode      指定模式,见下行
' 位1-位0: I2C接口速度/SCL频率, 00=低速/20KHz,01=标准/100KHz,10=快速/400KHz,11=高速/750KHz
' 位2:     SPI的I/O数/IO引脚, 0=单入单出(D5出/D7入),1=双入双出(D5出D4出/D7入D6入)
' 位7:     SPI字节中的位顺序, 0=低位在前, 1=高位在前
' 其它保留,必须为0

Declare Function USBIO_SetDelaymS Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iDelay As Long) As Boolean
'  USBIO_SetDelaymS     设置硬件异步延时,调用后很快返回,而在下一个流操作之前延时指定毫秒数
 ' iIndex,    指定USB2ISP设备序号
 ' iDelay      指定延时的毫秒数

Declare Function USBIO_StreamI2C Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iWriteLength As Long, ByRef iWriteBuffer As Any, ByVal iReadLength As Long, ByRef oReadBuffer As Any) As Boolean
' USBIO_StreamI2C     处理I2C数据流,2线接口,时钟线为SCL引脚,数据线为SDA引脚(准双向I/O),速度约56K字节
' iIndex,    指定USB2ISP设备序号
' iWriteLength,    准备写出的数据字节数
' iWriteBuffer,    指向一个缓冲区,放置准备写出的数据,首字节通常是I2C设备地址及读写方向位
' iReadLength,     准备读取的数据字节数
' oReadBuffer     指向一个缓冲区,返回后是读入的数据
Declare Function USBIO_ReadEEPROM Lib "USBIOX.DLL" (ByVal iIndexas As Long, ByVal iEepromID As EEPROM_TYPE, ByVal iAddr As Long, ByVal iLength As Long, ByRef oBuffer As Any) As Boolean
' i    Index  指定USB2ISP设备序号
' iEepromID   指定EEPROM型号
' iAddr       指定数据单元的地址
' iLength     准备读取的数据字节数
' oBuffer     指向一个缓冲区,返回后是读入的数据

Declare Function USBIO_WriteEEPROM Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iEepromID As EEPROM_TYPE, ByVal iAddr As Long, ByVal iLength As Long, ByRef iBuffer As Any) As Boolean
' iIndex,    指定USB2ISP设备序号
' iEepromID, 指定EEPROM型号
' iAddr,     指定数据单元的地址
' iLength,   准备写出的数据字节数
' iBuffer    指向一个缓冲区,放置准备写出的数据
'----------------------------------------------------------------------------------------
Declare Function USBIO_GetInput Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iStatus As Long) As Boolean
' USBIO_GetInput 通过USB2ISP直接输入数据和状态,效率比USBIO_GetStatus更高
' iIndex,  指定USB2ISP设备序号
' iStatus  指向一个双字单元,用于保存状态数据,参考下面的位说明
' 位7-位0对应USB2ISP的D7-D0引脚
' 位8对应USB2ISP的ERR#引脚, 位9对应USB2ISP的PEMP引脚, 位10对应USB2ISP的INT#引脚, 位11对应USB2ISP的SLCT引脚, 位23对应USB2ISP的SDA引脚
' 位13对应USB2ISP的BUSY/WAIT#引脚, 位14对应USB2ISP的AUTOFD#/DATAS#引脚,位15对应USB2ISP的SLCTIN#/ADDRS#引脚

Declare Function USBIO_SetOutput Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iEnable As Long, ByVal iSetDirOut As Long, ByVal iSetDataOut As Long) As Boolean
' USBIO_SetOutput 设置USB2ISP的I/O方向,并通过USBIO_直接输出数据
' ***** 谨慎使用该API, 防止修改I/O方向使输入引脚变为输出引脚导致与其它输出引脚之间短路而损坏芯片 *****
' iIndex,  指定USB2ISP设备序号
' iEnable, 数据有效标志,参考下面的位说明
'// 位0为1说明iSetDataOut的位15-位8有效,否则忽略
'// 位1为1说明iSetDirOut的位15-位8有效,否则忽略
'// 位2为1说明iSetDataOut的7-位0有效,否则忽略
'// 位3为1说明iSetDirOut的位7-位0有效,否则忽略
'// 位4为1说明iSetDataOut的位23-位16有效,否则忽略
' iSetDirOut, 设置I/O方向,某位清0则对应引脚为输入,某位置1则对应引脚为输出,并口方式下默认值为0x000FC000,参考下面的位说明
' iSetDataOut 输出数据,如果I/O方向为输出,那么某位清0时对应引脚输出低电平,某位置1时对应引脚输出高电平,参考下面的位说明
'// 位7-位0对应USB2ISP的D7-D0引脚
'// 位8对应USB2ISP的ERR#引脚, 位9对应USB2ISP的PEMP引脚, 位10对应USB2ISP的INT#引脚, 位11对应USB2ISP的SLCT引脚
'// 位13对应USB2ISP的WAIT#引脚, 位14对应USB2ISP的DATAS#/READ#引脚,位15对应USB2ISP的ADDRS#/ADDR/ALE引脚
'// 以下引脚只能输出,不考虑I/O方向: 位16对应USB2ISP的RESET#引脚, 位17对应USB2ISP的WRITE#引脚, 位18对应USB2ISP的SCL引脚, 位29对应USB2ISP的SDA引脚

Declare Function USBIO_Set_D5_D0 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iSetDirOut As Long, ByVal iSetDataOut As Long) As Boolean
' USBIO_Set_D5_D0 设置USB2ISP的D5-D0引脚的I/O方向,并通过USB2ISP的D5-D0引脚直接输出数据,效率比USBIO_SetOutput更高
' ***** 谨慎使用该API, 防止修改I/O方向使输入引脚变为输出引脚导致与其它输出引脚之间短路而损坏芯片 *****
' iIndex,      指定USB2ISP设备序号
' iSetDirOut,  设置D5-D0各引脚的I/O方向,某位清0则对应引脚为输入,某位置1则对应引脚为输出,并口方式下默认值为0x00全部输入
' iSetDataOut  设置D5-D0各引脚的输出数据,如果I/O方向为输出,那么某位清0时对应引脚输出低电平,某位置1时对应引脚输出高电平
'// 以上数据的位5-位0分别对应USB2ISP的D5-D0引脚

Declare Function USBIO_StreamSPI3 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iChipSelect As Long, ByVal iLength As Long, ByRef ioBuffer As Any) As Boolean
' USBIO_StreamSPI3 处理SPI数据流,3线接口,时钟线为SCK/SCL引脚,数据线为DIO/SDA引脚(准双向I/O),片选线为D0/D1/D2,速度约51K字节
' SPI时序: SCK2/SCL引脚为时钟输出, 默认为低电平, DIO/SDA引脚在时钟上升沿之前输出, DIO/SDA引脚在时钟下降沿之后输入
' iIndex,   指定USB2ISP设备序号
' iChipSelect,片选控制, 位7为0则忽略片选控制, 位7为1则参数有效: 位1位0为00/01/10分别选择D0/D1/D2引脚作为低电平有效片选
' iLength,    准备传输的数据字节数
' ioBuffer    指向一个缓冲区,放置准备从DIO写出的数据,返回后是从DIO读入的数据

Declare Function USBIO_StreamSPI4 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iChipSelect As Long, ByVal iLength As Long, ByRef ioBuffer As Any) As Boolean
' USBIO_StreamSPI4 处理SPI数据流,4线接口,时钟线为SCK/D3引脚,输出数据线为DOUT/D5/MOSI引脚,输入数据线为DIN/D7/MISO引脚,片选线为D0/D1/D2,速度约68K字节
' SPI时序: SCK/D3引脚为时钟输出, 默认为低电平, DOUT/D5/MOSI引脚在时钟上升沿之前输出, DIN/D7/MISO引脚在时钟下降沿之后输入
' iIndex,   指定USB2ISP设备序号
' iChipSelect,片选控制, 位7为0则忽略片选控制, 位7为1则参数有效: 位1位0为00/01/10分别选择D0/D1/D2引脚作为低电平有效片选
' iLength,    准备传输的数据字节数
' ioBuffer    指向一个缓冲区,放置准备从DOUT/MOSI写出的数据,返回后是从DIN/MISO读入的数据

Declare Function USBIO_StreamSPI5 Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iChipSelect As Long, ByVal iLength As Long, ByRef ioBuffer As Any, ByRef ioBuffer2 As Any) As Boolean
' USBIO_StreamSPI5 处理SPI数据流,5线接口,时钟线为SCK/D3引脚,输出数据线为DOUT/D5/MOSI和DOUT2/D4引脚,输入数据线为DIN/D7/MISO和DIN2/D6引脚,片选线为D0/D1/D2,速度约30K字节*2
' SPI时序: SCK/D3引脚为时钟输出, 默认为低电平, DOUT/D5/MOSI和DOUT2/D4引脚在时钟上升沿之前输出, DIN/D7/MISO和DIN2/D6引脚在时钟下降沿之后输入
' iIndex,   指定USB2ISP设备序号
' iChipSelect,片选控制, 位7为0则忽略片选控制, 位7为1则参数有效: 位1位0为00/01/10分别选择D0/D1/D2引脚作为低电平有效片选
' iLength,    准备传输的数据字节数
' ioBuffer,   指向一个缓冲区,放置准备从DOUT/MOSI写出的数据,返回后是从DIN/MISO读入的数据
' ioBuffer2   指向第二个缓冲区,放置准备从DOUT/MOSI2写出的数据,返回后是从DIN/MISO2读入的数据

Declare Function USBIO_BitStreamSPI Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iLength As Long, ByRef ioBuffer As Any) As Boolean
' USBIO_BitStreamSPI 处理SPI位数据流,4线/5线接口,时钟线为SCK/D3引脚,输出数据线为DOUT/DOUT2引脚,输入数据线为DIN/DIN2引脚,片选线为D0/D1/D2,速度约8K位*2
' iIndex,  指定USB2ISP设备序号
' iLength, 准备传输的数据位数,一次最多896,建议不超过256
' ioBuffer 指向一个缓冲区,放置准备从DOUT/MOSI/DOUT2/D2-D0写出的数据,返回后是从DIN/MISO/DIN2读入的数据
'/* SPI时序: SCK/D3引脚为时钟输出, 默认为低电平, DOUT/D5/MOSI和DOUT2/D4引脚在时钟上升沿之前输出, DIN/D7/MISO和DIN2/D6引脚在时钟下降沿之后输入 */
'/* ioBuffer中的一个字节共8位分别对应D7-D0引脚, 位5输出到DOUT, 位4输出到DOUT2, 位2-位0输出到D2-D0, 位7从DIN/MISO输入, 位6从DIN/MISO2输入, 位3数据忽略 */
'/* 在调用该API之前,应该先调用USBIO_Set_D5_D0设置USB2ISP的D5-D0引脚的I/O方向,并设置引脚的默认电平 */

'-------------------------------------------------------------------------

Declare Function USBIO_SetBufUpload Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iEnableOrClear As Long) As Boolean  ' 为0则禁止内部缓冲上传模式,使用直接上传,非0则启用内部缓冲上传模式并清除缓冲区中的已有数据
' USBIO_SetBufUpload  ' 设定内部缓冲上传模式
' iIndex,          0指定USB2ISP设备序号,0对应第一个设备
' iEnableOrClear  为0则禁止内部缓冲上传模式,使用直接上传,非0则启用内部缓冲上传模式并清除缓冲区中的已有数据
' 如果启用内部缓冲上传模式,那么USB2ISP驱动程序创建线程自动接收USB上传数据到内部缓冲区,同时清除缓冲区中的已有数据,当应用程序调用USBIO_ReadData后将立即返回缓冲区中的已有数据

Declare Function USBIO_QueryBufUpload Lib "USBIOX.DLL" (ByVal iIndex As Long) As Long
' USBIO_QueryBufUpload   查询内部上传缓冲区中的已有数据包个数,成功返回数据包个数,出错返回-1
' iIndex                指定USB2ISP设备序号,0对应第一个设备

Declare Function USBIO_SetBufDownload Lib "USBIOX.DLL" (ByVal iIndex As Long, ByVal iEnableOrClear As Long) As Boolean
'  USBIO_SetBufDownload  设定内部缓冲下传模式
'  iIndex,              指定USB2ISP设备序号,0对应第一个设备
'  iEnableOrClear       为0则禁止内部缓冲下传模式,使用直接下传,非0则启用内部缓冲下传模式并清除缓冲区中的已有数据
'  如果启用内部缓冲下传模式,那么当应用程序调用USBIO_WriteData后将仅仅是将USB下传数据放到内部缓冲区并立即返回,而由USB2ISP驱动程序创建的线程自动发送直到完毕

Declare Function USBIO_QueryBufDownload Lib "USBIOX.DLL" (ByVal iIndex As Long) As Long    ' 指定USB2ISP设备序号,0对应第一个设备
'  USBIO_QueryBufDownload  查询内部下传缓冲区中的剩余数据包个数(尚未发送),成功返回数据包个数,出错返回-1
'  iIndex                 指定USB2ISP设备序号,0对应第一个设备


Declare Function USBIO_ResetInter Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
'  USBIO_ResetInter   复位中断数据读操作
'  iIndex            指定USB2ISP设备序号

Declare Function USBIO_ResetRead Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
'  USBIO_ResetRead  复位数据块读操作
'  iIndex          指定USB2ISP设备序号

Declare Function USBIO_ResetWrite Lib "USBIOX.DLL" (ByVal iIndex As Long) As Boolean
'    USBIO_ResetRead    复位数据块读操作
'    iIndex            指定USB2ISP设备序号

'typedef     VOID    ( CALLBACK  * mUSBIO_NOTIFY_ROUTINE ) (  ' 设备事件通知回调程序
'    ULONG           iEventStatus );  ' 设备事件和当前状态(在下行定义): 0=设备拔出事件, 3=设备插入事件

Public Const USBIO_DEVICE_ARRIVAL = 3               ' 设备插入事件,已经插入
Public Const USBIO_DEVICE_REMOVE_PEND = 1         ' 设备将要拔出
Public Const USBIO_DEVICE_REMOVE = 0              ' 设备拔出事件,已经拔出

Declare Function USBIO_SetDeviceNotify Lib "USBIOX.DLL" (ByVal iIndex As Long, ByRef iDeviceID As String, ByVal iNotifyRoutine As Long) As Boolean
'  USBIO_SetDeviceNotify     设定设备事件通知程序
'  iIndex,                  指定USB2ISP设备序号,0对应第一个设备
'  iDeviceID,               可选参数,指向字符串,指定被监控的设备的ID,字符串以\0终止
'  iNotifyRoutine           (函数地址)指定设备事件回调程序, 为NULL则取消事件通知, 否则在检测到事件时调用该程序

