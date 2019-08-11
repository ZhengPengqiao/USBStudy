VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "USB串口信息获取器(http://usendz.taobao.com)"
   ClientHeight    =   4485
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   6420
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4485
   ScaleWidth      =   6420
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton notify 
      Caption         =   "devnotify"
      Height          =   240
      Left            =   4080
      TabIndex        =   9
      Top             =   3000
      Visible         =   0   'False
      Width           =   1410
   End
   Begin VB.CommandButton clearshow 
      Caption         =   "清除显示"
      Height          =   345
      Left            =   4080
      TabIndex        =   8
      Top             =   3480
      Width           =   2175
   End
   Begin VB.Frame Frame2 
      Caption         =   "插拔监视"
      Height          =   1290
      Left            =   4080
      TabIndex        =   5
      Top             =   1680
      Width           =   2130
      Begin VB.CommandButton stopmonitor 
         Caption         =   "停止监视USB串口"
         Height          =   360
         Left            =   165
         TabIndex        =   7
         Top             =   750
         Width           =   1800
      End
      Begin VB.CommandButton beginmonitor 
         Caption         =   "开始监视USB串口"
         Height          =   360
         Left            =   180
         TabIndex        =   6
         Top             =   300
         Width           =   1800
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "查找USB串口"
      Height          =   1290
      Left            =   4080
      TabIndex        =   2
      Top             =   240
      Width           =   2130
      Begin VB.CommandButton PtNameIsCH341 
         Caption         =   "串口名称查找"
         Height          =   360
         Left            =   180
         TabIndex        =   4
         Top             =   765
         Width           =   1800
      End
      Begin VB.CommandButton PtHandleIsCH341 
         Caption         =   "串口句柄查找"
         Height          =   360
         Left            =   180
         TabIndex        =   3
         Top             =   315
         Width           =   1800
      End
   End
   Begin VB.ListBox 点击右边按钮获取USB串口信息 
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "微软雅黑"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3600
      ItemData        =   "Form1.frx":0000
      Left            =   120
      List            =   "Form1.frx":0007
      TabIndex        =   1
      Top             =   360
      Width           =   3840
   End
   Begin VB.Label usenlabel 
      Caption         =   "多款优胜USB串口设备适用"
      Height          =   255
      Left            =   4080
      TabIndex        =   10
      Top             =   4200
      Width           =   2175
   End
   Begin VB.Label CH341PTver 
      Caption         =   "CH341PT.DLL Ver:??"
      Height          =   180
      Left            =   180
      TabIndex        =   0
      Top             =   4200
      Width           =   1620
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub clearshow_Click()
点击右边按钮获取USB串口信息.Clear
End Sub

Private Sub Form_Load()
CH341PTver.Caption = "CH341PT.DLL Ver:" & Hex(CH341PtGetVersion())
End Sub

Private Sub notify_KeyUp(KeyCode As Integer, Shift As Integer)
   Call CH341SerNotifyFunc(KeyCode)
End Sub

Private Sub PtNameIsCH341_Click()
 Dim porthandle As Long
 Dim i As Byte
 Dim j As Byte
 Dim portname As String
 Dim fullportname As String

点击右边按钮获取USB串口信息.AddItem "通过名称找到USB串口为:"
For j = 1 To 21
    portname = "COM" + Trim(Str(j)) + Trim(Chr(0)) '设备名
    fullportname = "\\.\" & portname '完整的设备名
    If (CH341PtNameIsCH341(fullportname) <> False) Then
        点击右边按钮获取USB串口信息.AddItem portname
    End If
Next j
End Sub

Private Sub PtHandleIsCH341_Click()
 '在完整的串口名为"////.//COMxx"
 '通过串口特征数据来识别CH341串口
 Dim porthandle As Long
 Dim i As Byte
 Dim j As Byte
 Dim portname As String
 Dim fullportname As String
 点击右边按钮获取USB串口信息.AddItem "通过句柄找到USB串口为:"
 For j = 1 To 21
    portname = "COM" + Trim(Str(j)) + Trim(Chr(0)) '设备名
    fullportname = "\\.\" & portname '完整的设备名
    porthandle = CreateFile(fullportname, GENERIC_READ Or GENERIC_WRITE, FILE_SHARE_READ Or FILE_SHARE_WRITE, vbNullString, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0&)
    If (porthandle <> INVALID_HANDLE_VALUE) Then
        If (CH341PtHandleIsCH341(porthandle) <> False) Then
            点击右边按钮获取USB串口信息.AddItem portname
       End If
        CloseHandle (porthandle)
    End If
 Next j
End Sub

Private Sub beginmonitor_Click()
If (CH341PtSetDevNotify(vbNullString, AddressOf CH341PT_NOTIFY_ROUTINE) <> False) Then
    点击右边按钮获取USB串口信息.AddItem "开始监视USB串口插拔"
Else
    点击右边按钮获取USB串口信息.AddItem "设置USB串口监视失败"
End If
End Sub

Private Sub stopmonitor_Click()
If (CH341PtSetDevNotify(vbNullString, 0&) <> False) Then
    点击右边按钮获取USB串口信息.AddItem "停止监视USB串口插拔"
    ch341sername = ""
Else
    点击右边按钮获取USB串口信息.AddItem "停止监视USB串口插拔失败"
End If
End Sub


    
