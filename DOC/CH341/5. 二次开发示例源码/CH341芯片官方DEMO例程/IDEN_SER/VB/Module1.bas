Attribute VB_Name = "Module1"
Option Explicit

Public ch341sername   As String    '存储监测到的已插入的串口名

Public Const WM_KEYUP = &H101
Public Const FILE_FLAG_OVERLAPPED = &H40000000
Public Const GENERIC_READ = &H80000000
Public Const GENERIC_WRITE = &H40000000
Public Const FILE_SHARE_READ = &H1
Public Const FILE_SHARE_WRITE = &H2
Public Const OPEN_EXISTING = 3
Public Const INVALID_HANDLE_VALUE = -1

Public Declare Function CreateFile Lib "kernel32" Alias "CreateFileA" (ByVal lpFileName As String, ByVal dwDesiredAccess As Long, ByVal dwShareMode As Long, lpSecurityAttributes As String, ByVal dwCreationDisposition As Long, ByVal dwFlagsAndAttributes As Long, ByVal hTemplateFile As Long) As Long
Public Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Public Declare Function PostMessage Lib "user32" Alias "PostMessageA" (ByVal hwnd As Long, ByVal wMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long


Public Sub CH341PT_NOTIFY_ROUTINE(ByVal iDevIndexAndEvent As Long)
'在中断回调函数中,不能对系统资源操作过多.通过窗体WM_KEYUP事件来模拟插拔事件
    PostMessage Form1.notify.hwnd, WM_KEYUP, iDevIndexAndEvent, 0
End Sub

Public Sub CH341SerNotifyFunc(ByVal iDevIndexAndEvent As Long)
Dim fullportname As String
Dim tem As String
Dim portname As String

If (iDevIndexAndEvent > 0) Then 'USB串口已插上
    portname = "COM" + Trim(Str(iDevIndexAndEvent))   '设备名
    fullportname = "\\.\" & portname '完整的设备名
    If (CH341PtNameIsCH341(fullportname) <> False) Then
        ch341sername = portname  '作为设备拔出时CH341串口判别的依据
        Form1.点击右边按钮获取USB串口信息.AddItem "CH341串口 " & ch341sername & "已插入"
    Else
        Form1.点击右边按钮获取USB串口信息.AddItem "串口 " & portname & "已插入"
    End If
ElseIf (iDevIndexAndEvent < 0) Then 'USB串口已拔出
        portname = "COM" + Trim(Str(-iDevIndexAndEvent)) '中断传来的端口号为负值
    If (ch341sername = portname) Then '与是先前监测到的插入的341串口名比较
        Form1.点击右边按钮获取USB串口信息.AddItem "CH341串口 " & portname & "已拔出"
        ch341sername = ""
    Else
        Form1.点击右边按钮获取USB串口信息.AddItem "串口 " & portname & "已拔出"
    End If
End If

End Sub

