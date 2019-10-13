Attribute VB_Name = "Module1"
Option Explicit

Public ch341sername   As String    '�洢��⵽���Ѳ���Ĵ�����

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
'���жϻص�������,���ܶ�ϵͳ��Դ��������.ͨ������WM_KEYUP�¼���ģ�����¼�
    PostMessage Form1.notify.hwnd, WM_KEYUP, iDevIndexAndEvent, 0
End Sub

Public Sub CH341SerNotifyFunc(ByVal iDevIndexAndEvent As Long)
Dim fullportname As String
Dim tem As String
Dim portname As String

If (iDevIndexAndEvent > 0) Then 'USB�����Ѳ���
    portname = "COM" + Trim(Str(iDevIndexAndEvent))   '�豸��
    fullportname = "\\.\" & portname '�������豸��
    If (CH341PtNameIsCH341(fullportname) <> False) Then
        ch341sername = portname  '��Ϊ�豸�γ�ʱCH341�����б������
        Form1.����ұ߰�ť��ȡUSB������Ϣ.AddItem "CH341���� " & ch341sername & "�Ѳ���"
    Else
        Form1.����ұ߰�ť��ȡUSB������Ϣ.AddItem "���� " & portname & "�Ѳ���"
    End If
ElseIf (iDevIndexAndEvent < 0) Then 'USB�����Ѱγ�
        portname = "COM" + Trim(Str(-iDevIndexAndEvent)) '�жϴ����Ķ˿ں�Ϊ��ֵ
    If (ch341sername = portname) Then '������ǰ��⵽�Ĳ����341�������Ƚ�
        Form1.����ұ߰�ť��ȡUSB������Ϣ.AddItem "CH341���� " & portname & "�Ѱγ�"
        ch341sername = ""
    Else
        Form1.����ұ߰�ť��ȡUSB������Ϣ.AddItem "���� " & portname & "�Ѱγ�"
    End If
End If

End Sub

