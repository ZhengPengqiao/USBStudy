VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "tabctl32.ocx"
Begin VB.Form frmMain 
   Caption         =   "USB2ISP DEMO    WWW.USB-I2C-SPI.COM"
   ClientHeight    =   7230
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7515
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7230
   ScaleWidth      =   7515
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton USBIO_NOTIFY_ROUTINE 
      Caption         =   "模拟处理设备挺拔中断事件"
      Enabled         =   0   'False
      Height          =   330
      Left            =   2535
      TabIndex        =   1
      Top             =   6660
      Visible         =   0   'False
      Width           =   3255
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   6915
      Left            =   105
      TabIndex        =   0
      Top             =   90
      Width           =   7305
      _ExtentX        =   12885
      _ExtentY        =   12197
      _Version        =   393216
      Tabs            =   6
      Tab             =   5
      TabsPerRow      =   6
      TabHeight       =   520
      MouseIcon       =   "frmMain.frx":030A
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "宋体"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "EPP并口"
      TabPicture(0)   =   "frmMain.frx":0624
      Tab(0).ControlEnabled=   0   'False
      Tab(0).ControlCount=   0
      TabCaption(1)   =   "MEM并口"
      TabPicture(1)   =   "frmMain.frx":0640
      Tab(1).ControlEnabled=   0   'False
      Tab(1).ControlCount=   0
      TabCaption(2)   =   "I2C接口"
      TabPicture(2)   =   "frmMain.frx":065C
      Tab(2).ControlEnabled=   0   'False
      Tab(2).ControlCount=   0
      TabCaption(3)   =   "EEPROM读写"
      TabPicture(3)   =   "frmMain.frx":0678
      Tab(3).ControlEnabled=   0   'False
      Tab(3).ControlCount=   0
      TabCaption(4)   =   "数字I/O"
      TabPicture(4)   =   "frmMain.frx":0694
      Tab(4).ControlEnabled=   0   'False
      Tab(4).ControlCount=   0
      TabCaption(5)   =   "SPI接口"
      TabPicture(5)   =   "frmMain.frx":06B0
      Tab(5).ControlEnabled=   -1  'True
      Tab(5).Control(0)=   "Frame15"
      Tab(5).Control(0).Enabled=   0   'False
      Tab(5).ControlCount=   1
      Begin VB.Frame Frame15 
         Caption         =   "以流模式读写兼容SPI的4线制同步串口，API=USBIO_StreamSPI4"
         Height          =   6255
         Left            =   120
         TabIndex        =   2
         Top             =   480
         Width           =   6975
         Begin VB.Frame Frame16 
            Caption         =   "SPI字节中的位顺序"
            Height          =   615
            Left            =   960
            TabIndex        =   11
            Top             =   4920
            Width           =   5535
            Begin VB.OptionButton SPIMSB 
               Caption         =   "高位在前"
               Height          =   255
               Index           =   0
               Left            =   2040
               TabIndex        =   13
               Top             =   240
               Value           =   -1  'True
               Width           =   1095
            End
            Begin VB.OptionButton SPILSB 
               Caption         =   "低位在前"
               Height          =   255
               Index           =   1
               Left            =   3840
               TabIndex        =   12
               Top             =   240
               Width           =   1095
            End
         End
         Begin VB.CommandButton StreamSPIRW 
            Caption         =   "Read\Write"
            Height          =   495
            Left            =   2640
            TabIndex        =   9
            Top             =   4320
            Width           =   1695
         End
         Begin VB.TextBox SPIWRBuf 
            Height          =   3255
            Left            =   840
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   8
            Top             =   1080
            Width           =   5535
         End
         Begin VB.TextBox SPIWRLen 
            Height          =   405
            Left            =   2760
            TabIndex        =   7
            Top             =   360
            Width           =   1575
         End
         Begin VB.Label Label31 
            Caption         =   "(<40H)"
            Height          =   255
            Left            =   4560
            TabIndex        =   10
            Top             =   480
            Width           =   735
         End
         Begin VB.Label Label28 
            Caption         =   "放置准备从DO/MOSI/D5写出的数据,返回后是从DI/MISO/D7读入的数据"
            Height          =   255
            Left            =   840
            TabIndex        =   6
            Top             =   840
            Width           =   5655
         End
         Begin VB.Label Label29 
            Caption         =   "SPI时序: SCK/D3引脚为时钟输出, 默认为低电平, DO/MOSI/D5引脚在时钟上升沿之前输出, DI/MISO/D7引脚在时钟下降沿之后输入."
            Height          =   495
            Left            =   840
            TabIndex        =   5
            Top             =   5640
            Width           =   5655
         End
         Begin VB.Label Label19 
            Caption         =   "数据缓冲区ioBuffer"
            Height          =   255
            Left            =   960
            TabIndex        =   4
            Top             =   4440
            Width           =   1575
         End
         Begin VB.Label Label18 
            Caption         =   "准备传输的数据字节数"
            Height          =   255
            Left            =   840
            TabIndex        =   3
            Top             =   480
            Width           =   1935
         End
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim hopen As Long

Private Sub Form_Load()
mIndex = 0
    SSTab1.TabVisible(0) = False
    SSTab1.TabVisible(1) = False
    SSTab1.TabVisible(2) = False
    SSTab1.TabVisible(3) = False
    SSTab1.TabVisible(4) = False
    'SSTab1.TabVisible(5) = False
hopen = USBIO_OpenDevice(mIndex)
If (hopen = INVALID_HANDLE_VALUE) Then
    mOpen = False
Else
    mOpen = True
End If
'设置设备插拔通知
If USBIO_SetDeviceNotify(mIndex, vbNullString, AddressOf mUSBIO_NOTIFY_ROUTINE) = False Then
    MsgBox "设置设备插拔通知失败", vbExclamation, "USB2SPI DEMO"
End If
enablebtn (mOpen)
End Sub

Private Sub Form_Unload(Cancel As Integer)
USBIO_SetDeviceNotify mIndex, vbNullString, 0&
If (mOpen = True) Then
    USBIO_CloseDevice (mIndex)

End If
End Sub

Private Sub StreamSPIRW_Click()
Dim mWRLen As Long
'Dim mRdLen As Long
Dim ioBuff As arrRBuffer
'Dim iBuff As arrRBuffer
'Dim buffer As arrRBuffer

mWRLen = HexToBcd(SPIWRLen.Text)
'mRdLen = HexToBcd(I2CRDLen.Text)
Dim mTheFirst As Boolean
mTheFirst = True

'----------------------------------------
If (SPIMSB(0).Value = True) Then
    If (USBIO_SetStream(mIndex, &H81) = False) Then
       MsgBox "设置SPI高位在前模式失败！ ", vbExclamation, "USB2SPI DEMO"
       Exit Sub
    End If
ElseIf (SPILSB(1).Value = True) Then
    If (USBIO_SetStream(mIndex, &H1) = False) Then
       MsgBox "设置SPI低位在前模式失败！ ", vbExclamation, "USB2SPI DEMO"
       Exit Sub
    End If
End If
'----------------------------------------

If (mWRLen > 0 And SPIWRBuf.Text = "") Then
  MsgBox "请输入要准备传输的数据字节数！", vbExclamation, "USB2SPI DEMO"
  Exit Sub
End If
'If ((mWRLen = 0) And (mRdLen = 0)) Then
'  MsgBox "请输入读数据所需的长度！", vbExclamation, "USB2SPI DEMO"
'  Exit Sub
'End If


If (mWRLen > Len(Trim(SPIWRBuf.Text)) \ 2) Then
   mWRLen = Len(Trim(SPIWRBuf.Text)) \ 2
End If

Call mStrtoVal(SPIWRBuf.Text, ioBuff, mWRLen)       '将输入的十六进制格式字符数据转成数值数据

If (mOpen = True) Then
  If (USBIO_StreamSPI4(mIndex, &H80, mWRLen, ioBuff) = False) Then
     MsgBox "SPI流模式读写数据失败！", vbExclamation, "USB2SPI DEMO"
  Else
    If (mWRLen > 0) Then   '有数据返回
       Dim buff As String
       Dim i As Long
       For i = 0 To mWRLen - 1
         buff = buff & Hex2bit(ioBuff.buf(i)) + " "
       Next
       SPIWRBuf.Text = buff
    End If
  End If
  SPIWRLen.Text = Hex(mWRLen)
  'I2CRDLen.Text = Hex(mRdLen)
Else
  MsgBox "设备未打开！", vbExclamation, "USB2SPI DEMO"
End If
End Sub

Private Sub USBIO_NOTIFY_ROUTINE_KeyUp(KeyCode As Integer, Shift As Integer)  '设备插拔通知处理程序
    Dim iEventStatus As Long
    iEventStatus = KeyCode '插拔事件
    If (iEventStatus = USBIO_DEVICE_ARRIVAL) Then ' 设备插入事件,已经插入
        If (USBIO_OpenDevice(mIndex) = INVALID_HANDLE_VALUE) Then
            MsgBox "打开设备失败!", vbOK, "USB2SPI DEMO"
            mOpen = False
        Else
            mOpen = True  '打开成功
        End If
    ElseIf (iEventStatus = USBIO_DEVICE_REMOVE) Then ' 设备拔出事件,已经拔出
        USBIO_CloseDevice (mIndex)
        mOpen = False
    End If
    enablebtn (mOpen) '设备打开,按钮可用,设备没打开,按钮禁用
End Sub

Public Sub enablebtn(ByVal bEnable As Boolean)  'bEnable=true :各窗体按钮可用 ;=false:enable:各窗体按钮禁用
  With frmMain
  
       
    '.StreamICRW.Enabled = bEnable
    
    .StreamSPIRW.Enabled = bEnable
    
    If (bEnable = True) Then '窗体标题显示
        frmMain.Caption = "USB2SPI **设备已插上"

    Else
        frmMain.Caption = "USB2SPI **设备已拔出"

    End If
  End With
    
    
End Sub
