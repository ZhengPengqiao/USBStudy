VERSION 5.00
Begin VB.Form Form1 
   Appearance      =   0  'Flat
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "USB������Ϣ��ȡ��(http://usendz.taobao.com)"
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
   StartUpPosition =   3  '����ȱʡ
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
      Caption         =   "�����ʾ"
      Height          =   345
      Left            =   4080
      TabIndex        =   8
      Top             =   3480
      Width           =   2175
   End
   Begin VB.Frame Frame2 
      Caption         =   "��μ���"
      Height          =   1290
      Left            =   4080
      TabIndex        =   5
      Top             =   1680
      Width           =   2130
      Begin VB.CommandButton stopmonitor 
         Caption         =   "ֹͣ����USB����"
         Height          =   360
         Left            =   165
         TabIndex        =   7
         Top             =   750
         Width           =   1800
      End
      Begin VB.CommandButton beginmonitor 
         Caption         =   "��ʼ����USB����"
         Height          =   360
         Left            =   180
         TabIndex        =   6
         Top             =   300
         Width           =   1800
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "����USB����"
      Height          =   1290
      Left            =   4080
      TabIndex        =   2
      Top             =   240
      Width           =   2130
      Begin VB.CommandButton PtNameIsCH341 
         Caption         =   "�������Ʋ���"
         Height          =   360
         Left            =   180
         TabIndex        =   4
         Top             =   765
         Width           =   1800
      End
      Begin VB.CommandButton PtHandleIsCH341 
         Caption         =   "���ھ������"
         Height          =   360
         Left            =   180
         TabIndex        =   3
         Top             =   315
         Width           =   1800
      End
   End
   Begin VB.ListBox ����ұ߰�ť��ȡUSB������Ϣ 
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "΢���ź�"
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
      Caption         =   "�����ʤUSB�����豸����"
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
����ұ߰�ť��ȡUSB������Ϣ.Clear
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

����ұ߰�ť��ȡUSB������Ϣ.AddItem "ͨ�������ҵ�USB����Ϊ:"
For j = 1 To 21
    portname = "COM" + Trim(Str(j)) + Trim(Chr(0)) '�豸��
    fullportname = "\\.\" & portname '�������豸��
    If (CH341PtNameIsCH341(fullportname) <> False) Then
        ����ұ߰�ť��ȡUSB������Ϣ.AddItem portname
    End If
Next j
End Sub

Private Sub PtHandleIsCH341_Click()
 '�������Ĵ�����Ϊ"////.//COMxx"
 'ͨ����������������ʶ��CH341����
 Dim porthandle As Long
 Dim i As Byte
 Dim j As Byte
 Dim portname As String
 Dim fullportname As String
 ����ұ߰�ť��ȡUSB������Ϣ.AddItem "ͨ������ҵ�USB����Ϊ:"
 For j = 1 To 21
    portname = "COM" + Trim(Str(j)) + Trim(Chr(0)) '�豸��
    fullportname = "\\.\" & portname '�������豸��
    porthandle = CreateFile(fullportname, GENERIC_READ Or GENERIC_WRITE, FILE_SHARE_READ Or FILE_SHARE_WRITE, vbNullString, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0&)
    If (porthandle <> INVALID_HANDLE_VALUE) Then
        If (CH341PtHandleIsCH341(porthandle) <> False) Then
            ����ұ߰�ť��ȡUSB������Ϣ.AddItem portname
       End If
        CloseHandle (porthandle)
    End If
 Next j
End Sub

Private Sub beginmonitor_Click()
If (CH341PtSetDevNotify(vbNullString, AddressOf CH341PT_NOTIFY_ROUTINE) <> False) Then
    ����ұ߰�ť��ȡUSB������Ϣ.AddItem "��ʼ����USB���ڲ��"
Else
    ����ұ߰�ť��ȡUSB������Ϣ.AddItem "����USB���ڼ���ʧ��"
End If
End Sub

Private Sub stopmonitor_Click()
If (CH341PtSetDevNotify(vbNullString, 0&) <> False) Then
    ����ұ߰�ť��ȡUSB������Ϣ.AddItem "ֹͣ����USB���ڲ��"
    ch341sername = ""
Else
    ����ұ߰�ť��ȡUSB������Ϣ.AddItem "ֹͣ����USB���ڲ��ʧ��"
End If
End Sub


    
