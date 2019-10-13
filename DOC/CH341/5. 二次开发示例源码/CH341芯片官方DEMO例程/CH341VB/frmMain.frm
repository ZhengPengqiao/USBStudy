VERSION 5.00
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmMain 
   Caption         =   "CH341EVT"
   ClientHeight    =   7230
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7515
   Icon            =   "frmMain.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7230
   ScaleWidth      =   7515
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton CH341_NOTIFY_ROUTINE 
      Caption         =   "ģ�⴦���豸ͦ���ж��¼�"
      Enabled         =   0   'False
      Height          =   330
      Left            =   2535
      TabIndex        =   115
      Top             =   6660
      Visible         =   0   'False
      Width           =   3255
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   6960
      Left            =   105
      TabIndex        =   0
      Top             =   90
      Width           =   7305
      _ExtentX        =   12885
      _ExtentY        =   12277
      _Version        =   393216
      Tabs            =   5
      Tab             =   1
      TabsPerRow      =   5
      TabHeight       =   520
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "����"
         Size            =   9.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "EPP ����"
      TabPicture(0)   =   "frmMain.frx":0442
      Tab(0).ControlEnabled=   0   'False
      Tab(0).Control(0)=   "Frame2"
      Tab(0).Control(1)=   "Frame1"
      Tab(0).ControlCount=   2
      TabCaption(1)   =   "MEM ����"
      TabPicture(1)   =   "frmMain.frx":045E
      Tab(1).ControlEnabled=   -1  'True
      Tab(1).Control(0)=   "Frame4"
      Tab(1).Control(0).Enabled=   0   'False
      Tab(1).Control(1)=   "Frame3"
      Tab(1).Control(1).Enabled=   0   'False
      Tab(1).ControlCount=   2
      TabCaption(2)   =   "���ߴ���"
      TabPicture(2)   =   "frmMain.frx":047A
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "Frame5"
      Tab(2).Control(0).Enabled=   0   'False
      Tab(2).ControlCount=   1
      TabCaption(3)   =   "EEPROM��д"
      TabPicture(3)   =   "frmMain.frx":0496
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "Frame10"
      Tab(3).Control(1)=   "Frame9"
      Tab(3).Control(2)=   "Frame8"
      Tab(3).ControlCount=   3
      TabCaption(4)   =   "����I/O"
      TabPicture(4)   =   "frmMain.frx":04B2
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "Frame11"
      Tab(4).ControlCount=   1
      Begin VB.Frame Frame5 
         Caption         =   "����ģʽ��д����I2C������ͬ�����ڣ�API=CH341StreamI2C"
         Height          =   6435
         Left            =   -74835
         TabIndex        =   101
         Top             =   450
         Width           =   6975
         Begin VB.Frame Frame7 
            Caption         =   "д������"
            Height          =   2865
            Left            =   450
            TabIndex        =   108
            Top             =   240
            Width           =   6120
            Begin VB.CommandButton StreamICRW 
               Caption         =   "Write\Read"
               Height          =   375
               Left            =   4575
               TabIndex        =   114
               Top             =   330
               Width           =   1185
            End
            Begin VB.TextBox I2CWRBuf 
               Height          =   1770
               Left            =   1125
               MultiLine       =   -1  'True
               ScrollBars      =   2  'Vertical
               TabIndex        =   110
               Top             =   840
               Width           =   4695
            End
            Begin VB.TextBox I2CWRLen 
               BeginProperty DataFormat 
                  Type            =   0
                  Format          =   "0"
                  HaveTrueFalseNull=   0
                  FirstDayOfWeek  =   0
                  FirstWeekOfYear =   0
                  LCID            =   2052
                  SubFormatType   =   0
               EndProperty
               Height          =   375
               Left            =   1140
               TabIndex        =   109
               Top             =   330
               Width           =   2415
            End
            Begin VB.Label Label17 
               Caption         =   "����"
               Height          =   255
               Left            =   300
               TabIndex        =   113
               Top             =   840
               Width           =   615
            End
            Begin VB.Label Label24 
               Caption         =   "����"
               Height          =   255
               Left            =   300
               TabIndex        =   112
               Top             =   390
               Width           =   495
            End
            Begin VB.Label Label25 
               Caption         =   "(<400H)"
               Height          =   180
               Left            =   3630
               TabIndex        =   111
               Top             =   427
               Width           =   855
            End
         End
         Begin VB.Frame Frame6 
            Caption         =   "��ȡ����"
            Height          =   2865
            Left            =   465
            TabIndex        =   102
            Top             =   3210
            Width           =   6120
            Begin VB.TextBox I2CRDLen 
               BeginProperty DataFormat 
                  Type            =   0
                  Format          =   "0"
                  HaveTrueFalseNull=   0
                  FirstDayOfWeek  =   0
                  FirstWeekOfYear =   0
                  LCID            =   2052
                  SubFormatType   =   0
               EndProperty
               Height          =   375
               Left            =   1050
               TabIndex        =   104
               Top             =   315
               Width           =   2415
            End
            Begin VB.TextBox I2CRDBuf 
               Height          =   1770
               Left            =   1050
               MultiLine       =   -1  'True
               ScrollBars      =   2  'Vertical
               TabIndex        =   103
               Top             =   825
               Width           =   4695
            End
            Begin VB.Label Label26 
               Caption         =   "����"
               Height          =   255
               Left            =   330
               TabIndex        =   107
               Top             =   375
               Width           =   495
            End
            Begin VB.Label Label27 
               Caption         =   "����"
               Height          =   255
               Left            =   330
               TabIndex        =   106
               Top             =   825
               Width           =   615
            End
            Begin VB.Label Label30 
               Caption         =   "(<400H)"
               Height          =   180
               Left            =   3555
               TabIndex        =   105
               Top             =   412
               Width           =   855
            End
         End
      End
      Begin VB.Frame Frame11 
         Height          =   6015
         Left            =   -74925
         TabIndex        =   73
         Top             =   600
         Width           =   7140
         Begin VB.Frame Frame14 
            Caption         =   "�����LED��ʾ����"
            Height          =   5475
            Left            =   2835
            TabIndex        =   88
            Top             =   270
            Width           =   1830
            Begin VB.CheckBox Led 
               Caption         =   "LED1"
               Height          =   255
               Index           =   0
               Left            =   615
               TabIndex        =   96
               Top             =   300
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED2"
               Height          =   255
               Index           =   1
               Left            =   615
               TabIndex        =   95
               Top             =   825
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED3"
               Height          =   255
               Index           =   2
               Left            =   615
               TabIndex        =   94
               Top             =   1365
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED4"
               Height          =   255
               Index           =   3
               Left            =   615
               TabIndex        =   93
               Top             =   1890
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED5"
               Height          =   255
               Index           =   4
               Left            =   600
               TabIndex        =   92
               Top             =   2415
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED6"
               Height          =   255
               Index           =   5
               Left            =   615
               TabIndex        =   91
               Top             =   2940
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED7"
               Height          =   255
               Index           =   6
               Left            =   615
               TabIndex        =   90
               Top             =   3480
               Width           =   945
            End
            Begin VB.CheckBox Led 
               Caption         =   "LED8"
               Height          =   255
               Index           =   7
               Left            =   615
               TabIndex        =   89
               Top             =   4005
               Width           =   945
            End
            Begin VB.Label Label40 
               Caption         =   "  ѡ��:����  δѡ��:����"
               Height          =   480
               Left            =   405
               TabIndex        =   97
               Top             =   4500
               Width           =   1110
            End
         End
         Begin VB.Frame Frame12 
            Caption         =   "���룺8λ����״̬"
            Height          =   5430
            Left            =   5055
            TabIndex        =   77
            Top             =   300
            Width           =   1830
            Begin VB.CheckBox swit 
               Caption         =   "ON1"
               Enabled         =   0   'False
               Height          =   225
               Index           =   0
               Left            =   570
               TabIndex        =   86
               Top             =   300
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON2"
               Enabled         =   0   'False
               Height          =   225
               Index           =   1
               Left            =   570
               TabIndex        =   85
               Top             =   825
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON3"
               Enabled         =   0   'False
               Height          =   225
               Index           =   2
               Left            =   570
               TabIndex        =   84
               Top             =   1350
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON4"
               Enabled         =   0   'False
               Height          =   225
               Index           =   3
               Left            =   570
               TabIndex        =   83
               Top             =   1875
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON5"
               Enabled         =   0   'False
               Height          =   225
               Index           =   4
               Left            =   570
               TabIndex        =   82
               Top             =   2415
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON6"
               Enabled         =   0   'False
               Height          =   225
               Index           =   5
               Left            =   570
               TabIndex        =   81
               Top             =   2940
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON7"
               Enabled         =   0   'False
               Height          =   225
               Index           =   6
               Left            =   570
               TabIndex        =   80
               Top             =   3465
               Width           =   720
            End
            Begin VB.CheckBox swit 
               Caption         =   "ON8"
               Enabled         =   0   'False
               Height          =   225
               Index           =   7
               Left            =   570
               TabIndex        =   79
               Top             =   3990
               Width           =   720
            End
            Begin VB.CommandButton evtbtrefresh 
               Caption         =   "���ˢ��״̬"
               Height          =   315
               Left            =   240
               TabIndex        =   78
               Top             =   4905
               Width           =   1305
            End
            Begin VB.Label Label41 
               Caption         =   " ON:ѡ�� OFF:��ѡ��"
               Height          =   435
               Left            =   450
               TabIndex        =   87
               Top             =   4440
               Width           =   1065
            End
         End
         Begin VB.Frame Frame13 
            Caption         =   "ѡ��MEM��д��ַ"
            Height          =   1020
            Left            =   330
            TabIndex        =   74
            Top             =   4575
            Width           =   1935
            Begin VB.OptionButton memadd0 
               Caption         =   "��ַ0"
               Height          =   210
               Index           =   0
               Left            =   270
               TabIndex        =   76
               Top             =   315
               Value           =   -1  'True
               Width           =   840
            End
            Begin VB.OptionButton memadd1 
               Caption         =   "��ַ1"
               Height          =   210
               Index           =   1
               Left            =   270
               TabIndex        =   75
               Top             =   645
               Width           =   840
            End
         End
         Begin VB.Label Label42 
            Caption         =   "�����ʾ��LED��ѡ�������������8��LED״̬"
            Height          =   510
            Left            =   270
            TabIndex        =   100
            Top             =   360
            Width           =   2325
         End
         Begin VB.Label Label43 
            Caption         =   "������ʾ��8λ����״̬�ǵ�""ˢ��""��Ŧ����������в��뿪�صĵ�ǰ״̬"
            Height          =   885
            Left            =   270
            TabIndex        =   99
            Top             =   1230
            Width           =   2325
         End
         Begin VB.Label Label44 
            Caption         =   "����API��MEM������ͬ��ֻ�ǳ�������1�ֽ�"
            Height          =   450
            Left            =   315
            TabIndex        =   98
            Top             =   4005
            Width           =   2310
         End
      End
      Begin VB.Frame Frame8 
         Caption         =   "д�����ݣ�API=CH341WriteEEPROM"
         Height          =   3180
         Left            =   -73215
         TabIndex        =   64
         Top             =   420
         Width           =   5415
         Begin VB.TextBox WrDataLen 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   345
            TabIndex        =   68
            Text            =   "0"
            Top             =   1305
            Width           =   2415
         End
         Begin VB.TextBox WrDataBuf 
            Height          =   1025
            Left            =   345
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   67
            Top             =   1995
            Width           =   4695
         End
         Begin VB.TextBox WrDataAddr 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   330
            TabIndex        =   66
            Text            =   "0"
            Top             =   570
            Width           =   2415
         End
         Begin VB.CommandButton eepromWrDate 
            Caption         =   "Write"
            Height          =   375
            Left            =   4035
            TabIndex        =   65
            Top             =   1230
            Width           =   975
         End
         Begin VB.Label Label38 
            Caption         =   "д�볤��"
            Height          =   255
            Left            =   330
            TabIndex        =   72
            Top             =   1020
            Width           =   810
         End
         Begin VB.Label Label37 
            Caption         =   "(<400H)"
            Height          =   255
            Left            =   1125
            TabIndex        =   71
            Top             =   1020
            Width           =   765
         End
         Begin VB.Label Label36 
            Caption         =   "������ݣ�16���ƣ����ַ�һ�飩"
            Height          =   225
            Left            =   330
            TabIndex        =   70
            Top             =   1725
            Width           =   3075
         End
         Begin VB.Label Label33 
            Caption         =   "���ݵ�Ԫ��ʼ��ַ"
            Height          =   255
            Left            =   315
            TabIndex        =   69
            Top             =   270
            Width           =   1650
         End
      End
      Begin VB.Frame Frame9 
         Caption         =   "�������ݣ�API=CH341ReadEEPROM"
         Height          =   3180
         Left            =   -73230
         TabIndex        =   55
         Top             =   3645
         Width           =   5415
         Begin VB.CommandButton eepromRdDate 
            Caption         =   "Read"
            Height          =   375
            Left            =   4035
            TabIndex        =   59
            Top             =   1245
            Width           =   975
         End
         Begin VB.TextBox RdDataAddr 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   315
            TabIndex        =   58
            Text            =   "0"
            Top             =   540
            Width           =   2415
         End
         Begin VB.TextBox RdDataBuf 
            Height          =   1025
            Left            =   315
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   57
            Top             =   1995
            Width           =   4695
         End
         Begin VB.TextBox RdDataLen 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   315
            TabIndex        =   56
            Text            =   "0"
            Top             =   1305
            Width           =   2415
         End
         Begin VB.Label Label39 
            Caption         =   "���ݵ�Ԫ��ʼ��ַ"
            Height          =   255
            Left            =   315
            TabIndex        =   63
            Top             =   270
            Width           =   1650
         End
         Begin VB.Label Label35 
            Caption         =   "������ݣ�16���ƣ����ַ�һ�飩"
            Height          =   225
            Left            =   330
            TabIndex        =   62
            Top             =   1725
            Width           =   3075
         End
         Begin VB.Label Label34 
            Caption         =   "(<400H)"
            Height          =   255
            Left            =   1125
            TabIndex        =   61
            Top             =   1020
            Width           =   765
         End
         Begin VB.Label Label32 
            Caption         =   "��ȡ����"
            Height          =   255
            Left            =   330
            TabIndex        =   60
            Top             =   1020
            Width           =   795
         End
      End
      Begin VB.Frame Frame10 
         Caption         =   "EEPROM�ͺ�"
         Height          =   6405
         Left            =   -74895
         TabIndex        =   41
         Top             =   420
         Width           =   1620
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C4096"
            Height          =   255
            Index           =   12
            Left            =   180
            TabIndex        =   54
            Top             =   5190
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C2048"
            Height          =   255
            Index           =   11
            Left            =   180
            TabIndex        =   53
            Top             =   4777
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C1024"
            Height          =   255
            Index           =   10
            Left            =   180
            TabIndex        =   52
            Top             =   4370
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C512"
            Height          =   255
            Index           =   9
            Left            =   180
            TabIndex        =   51
            Top             =   3963
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C256"
            Height          =   255
            Index           =   8
            Left            =   180
            TabIndex        =   50
            Top             =   3556
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C128"
            Height          =   255
            Index           =   7
            Left            =   180
            TabIndex        =   49
            Top             =   3149
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C64"
            Height          =   255
            Index           =   6
            Left            =   180
            TabIndex        =   48
            Top             =   2742
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C32"
            Height          =   255
            Index           =   5
            Left            =   180
            TabIndex        =   47
            Top             =   2335
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C16"
            Height          =   255
            Index           =   4
            Left            =   180
            TabIndex        =   46
            Top             =   1928
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C08"
            Height          =   255
            Index           =   3
            Left            =   180
            TabIndex        =   45
            Top             =   1521
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C04"
            Height          =   255
            Index           =   2
            Left            =   180
            TabIndex        =   44
            Top             =   1114
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C02"
            Height          =   255
            Index           =   1
            Left            =   165
            TabIndex        =   43
            Top             =   707
            Width           =   1320
         End
         Begin VB.OptionButton eppromtype 
            Caption         =   "24C01"
            Height          =   255
            Index           =   0
            Left            =   180
            TabIndex        =   42
            Top             =   300
            Value           =   -1  'True
            Width           =   1320
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "��д���ݣ�API=EppReadData��EppWriteData"
         Height          =   2865
         Left            =   -74400
         TabIndex        =   31
         Top             =   585
         Width           =   6120
         Begin VB.TextBox eppData0 
            Height          =   1020
            Left            =   1020
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   35
            Top             =   1275
            Width           =   4695
         End
         Begin VB.TextBox eppLen0 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   1035
            TabIndex        =   34
            Top             =   825
            Width           =   1905
         End
         Begin VB.CommandButton eppRead0 
            Caption         =   "Read"
            Height          =   375
            Left            =   3600
            TabIndex        =   33
            Top             =   2385
            Width           =   975
         End
         Begin VB.CommandButton eppWrite0 
            Caption         =   "Write"
            Height          =   390
            Left            =   4740
            TabIndex        =   32
            Top             =   2370
            Width           =   975
         End
         Begin VB.Label Label1 
            Caption         =   "EPP��ʽ������: WR#=1, DS#=0, AS#=1, D0-D7=input"
            Height          =   180
            Left            =   405
            TabIndex        =   40
            Top             =   255
            Width           =   4455
         End
         Begin VB.Label Label2 
            Caption         =   "EPP��ʽд����: WR#=0, DS#=0, AS#=1, D0-D7=output"
            Height          =   255
            Left            =   405
            TabIndex        =   39
            Top             =   540
            Width           =   4575
         End
         Begin VB.Label Label3 
            Caption         =   "����"
            Height          =   255
            Left            =   390
            TabIndex        =   38
            Top             =   1335
            Width           =   615
         End
         Begin VB.Label Label4 
            Caption         =   "����"
            Height          =   255
            Left            =   405
            TabIndex        =   37
            Top             =   885
            Width           =   495
         End
         Begin VB.Label Label20 
            Caption         =   "(<1000H)"
            Height          =   285
            Left            =   3015
            TabIndex        =   36
            Top             =   885
            Width           =   855
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "��д��ַ��API=EppReadAddr��EppWriteAddr"
         Height          =   2865
         Left            =   -74400
         TabIndex        =   21
         Top             =   3660
         Width           =   6120
         Begin VB.TextBox eppData1 
            Height          =   1025
            Left            =   1035
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   25
            Top             =   1305
            Width           =   4695
         End
         Begin VB.TextBox eppLen1 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   1035
            TabIndex        =   24
            Top             =   855
            Width           =   2415
         End
         Begin VB.CommandButton eppRead1 
            Caption         =   "Read"
            Height          =   375
            Left            =   3660
            TabIndex        =   23
            Top             =   2400
            Width           =   975
         End
         Begin VB.CommandButton eppWrite1 
            Caption         =   "Write"
            Height          =   375
            Left            =   4755
            TabIndex        =   22
            Top             =   2400
            Width           =   975
         End
         Begin VB.Label Label5 
            Caption         =   "EPP��ʽ����ַ: WR#=1, DS#=1, AS#=0, D0-D7=input"
            Height          =   180
            Left            =   345
            TabIndex        =   30
            Top             =   285
            Width           =   4455
         End
         Begin VB.Label Label6 
            Caption         =   "EPP��ʽд��ַ: WR#=0, DS#=1, AS#=0, D0-D7=output"
            Height          =   180
            Left            =   345
            TabIndex        =   29
            Top             =   570
            Width           =   4455
         End
         Begin VB.Label Label7 
            Caption         =   "����"
            Height          =   255
            Left            =   375
            TabIndex        =   28
            Top             =   1320
            Width           =   615
         End
         Begin VB.Label Label8 
            Caption         =   "����"
            Height          =   255
            Left            =   345
            TabIndex        =   27
            Top             =   900
            Width           =   495
         End
         Begin VB.Label Label21 
            Caption         =   "(<1000H)"
            Height          =   285
            Left            =   3510
            TabIndex        =   26
            Top             =   930
            Width           =   855
         End
      End
      Begin VB.Frame Frame3 
         Caption         =   "��д��ַ0��API=MemReadAddr0��MemWriteAddr0"
         Height          =   2865
         Left            =   585
         TabIndex        =   11
         Top             =   540
         Width           =   6120
         Begin VB.TextBox memData0 
            Height          =   1025
            Left            =   1140
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   15
            Top             =   1275
            Width           =   4695
         End
         Begin VB.TextBox memLen0 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   1140
            TabIndex        =   14
            Top             =   825
            Width           =   2415
         End
         Begin VB.CommandButton memRead0 
            Caption         =   "Read"
            Height          =   375
            Left            =   3720
            TabIndex        =   13
            Top             =   2370
            Width           =   975
         End
         Begin VB.CommandButton memWrite0 
            Caption         =   "Write"
            Height          =   375
            Left            =   4875
            TabIndex        =   12
            Top             =   2370
            Width           =   975
         End
         Begin VB.Label Label10 
            Caption         =   "����"
            Height          =   255
            Left            =   300
            TabIndex        =   20
            Top             =   1275
            Width           =   615
         End
         Begin VB.Label Label11 
            Caption         =   "MEM��ʽд��ַ0: WR#=0, DS#/RD#=1,AS#/ADDR=0,D0-D7=output"
            Height          =   255
            Left            =   300
            TabIndex        =   19
            Top             =   540
            Width           =   5295
         End
         Begin VB.Label Label12 
            Caption         =   "MEM��ʽ����ַ0: WR#=1, DS#/RD#=0,AS#/ADDR=0,D0-D7=input"
            Height          =   180
            Left            =   300
            TabIndex        =   18
            Top             =   255
            Width           =   5415
         End
         Begin VB.Label Label9 
            Caption         =   "����"
            Height          =   255
            Left            =   300
            TabIndex        =   17
            Top             =   885
            Width           =   495
         End
         Begin VB.Label Label22 
            Caption         =   "(<1000H)"
            Height          =   285
            Left            =   3585
            TabIndex        =   16
            Top             =   870
            Width           =   855
         End
      End
      Begin VB.Frame Frame4 
         Caption         =   "��д��ַ1��API=MemReadAddr1��MemWriteAddr1"
         Height          =   2865
         Left            =   630
         TabIndex        =   1
         Top             =   3720
         Width           =   6120
         Begin VB.TextBox memLen1 
            BeginProperty DataFormat 
               Type            =   0
               Format          =   "0"
               HaveTrueFalseNull=   0
               FirstDayOfWeek  =   0
               FirstWeekOfYear =   0
               LCID            =   2052
               SubFormatType   =   0
            EndProperty
            Height          =   375
            Left            =   1050
            TabIndex        =   5
            Top             =   840
            Width           =   2415
         End
         Begin VB.TextBox memData1 
            Height          =   1025
            Left            =   1050
            MultiLine       =   -1  'True
            ScrollBars      =   2  'Vertical
            TabIndex        =   4
            Top             =   1290
            Width           =   4695
         End
         Begin VB.CommandButton memRead1 
            Caption         =   "Read"
            Height          =   375
            Left            =   3645
            TabIndex        =   3
            Top             =   2385
            Width           =   975
         End
         Begin VB.CommandButton memWrite1 
            Caption         =   "Write"
            Height          =   375
            Left            =   4710
            TabIndex        =   2
            Top             =   2385
            Width           =   975
         End
         Begin VB.Label Label13 
            Caption         =   "����"
            Height          =   255
            Left            =   330
            TabIndex        =   10
            Top             =   900
            Width           =   495
         End
         Begin VB.Label Label14 
            Caption         =   "����"
            Height          =   255
            Left            =   330
            TabIndex        =   9
            Top             =   1290
            Width           =   615
         End
         Begin VB.Label Label15 
            Caption         =   "MEM��ʽд��ַ1: WR#=0, DS#/RD#=1, AS#/ADDR=1, D0-D7=output"
            Height          =   180
            Left            =   375
            TabIndex        =   8
            Top             =   600
            Width           =   5655
         End
         Begin VB.Label Label16 
            Caption         =   "MEM��ʽ����ַ1: WR#=1, DS#/RD#=0, AS#/ADDR=1, D0-D7=input"
            Height          =   180
            Left            =   375
            TabIndex        =   7
            Top             =   315
            Width           =   5535
         End
         Begin VB.Label Label23 
            Caption         =   "(<1000H)"
            Height          =   285
            Left            =   3555
            TabIndex        =   6
            Top             =   855
            Width           =   855
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

Private Sub eepromRdDate_Click()
 Dim mDataAddr As Long
 Dim mLen As Long
 Dim buffer As arrRBuffer
 Dim bu() As Byte
 mLen = HexToBcd(RdDataLen)
 
 If (RdDataAddr.Text = "") Then
   MsgBox "���������ݵ�Ԫ��ʼ��ַ��", vbExclamation, "CH341"
   Exit Sub
 End If
 If (mLen <= 0) Then
   MsgBox "�������ȡ���ȣ�", vbExclamation, "CH341"
   Exit Sub
 End If
 mDataAddr = HexToBcd(RdDataAddr)
 If (mOpen = True) Then
    If (CH341ReadEEPROM(mIndex, eepromid, mDataAddr, mLen, buffer)) Then
      Dim buff As String
      Dim i As Long
      For i = 0 To mLen - 1
         buff = buff & Hex2bit(buffer.buf(i)) & " "
      Next i
      RdDataBuf.Text = buff
    Else
      MsgBox "��E2PROM����ʧ�ܣ�", vbExclamation, "CH341"
    End If
    RdDataLen.Text = Hex(mLen)
 Else
    MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
 End If
End Sub

Private Sub eepromWrDate_Click()
 Dim mData As Byte
 Dim mDataAddr As Long
 Dim mLen As Long
 Dim buffer As arrRBuffer
 
 mLen = HexToBcd(WrDataLen.Text)
  If (WrDataAddr.Text = "") Then
   MsgBox "���������ݵ�Ԫ��ʼ��ַ��", vbExclamation, "CH341"
   Exit Sub
 End If
 If (mLen <= 0 Or WrDataBuf.Text = "") Then
   MsgBox "������Ҫд�������,���ȣ�", vbExclamation, "CH341"
   Exit Sub
 End If
  
  If (mLen > (Len(WrDataBuf) \ 2)) Then '�����볤�Ⱥ����ݳ�����ȡСֵ
    mLen = Len(WrDataBuf) \ 2
  End If
  
  mDataAddr = HexToBcd(WrDataAddr.Text)
  Call mStrtoVal(WrDataBuf.Text, buffer, mLen)  '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����

  If (mOpen = True) Then
     If (CH341WriteEEPROM(mIndex, eepromid, mDataAddr, mLen, buffer) = False) Then
        MsgBox "��E2PROM����ʧ�ܣ�", vbExclamation, "CH341"
     End If
     WrDataLen.Text = Hex(mLen)
  Else
    MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
  End If
End Sub

Private Sub eppRead0_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(eppLen0.Text)
    If (mLen <= 0) Then
        MsgBox "�������ȡ����", vbExclamation, "CH341"
        Exit Sub
    End If
    If (mOpen = True) Then
            If (CH341EppReadData(mIndex, buffer, mLen)) Then
                Dim buff As String
                Dim i As Long
                buff = ""
                For i = 0 To mLen - 1 Step 1
                    buff = buff & Hex2bit(buffer.buf(i)) & " "
                Next
                eppData0.Text = buff
            Else
                MsgBox "EPP��ʽ������ʧ�ܣ� ", vbExclamation, "CH341"
            End If
            eppLen0.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub eppRead1_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(eppLen1.Text)
    If (mLen <= 0) Then
        MsgBox "�������ȡ���ݵĳ���", vbExclamation, "CH341"
        Exit Sub
    End If
     If (mOpen = True) Then
        If (CH341EppReadAddr(mIndex, buffer, mLen)) Then
            Dim buff As String
            Dim i, j As Long
            j = 0
            For i = 0 To mLen - 1
                buff = buff & Hex2bit(buffer.buf(i)) + " "
            Next
            eppData1.Text = buff
        Else
            MsgBox "EPP�����ݿ�1ʧ�ܣ� ", vbExclamation, "CH341"
        End If
        eppLen1.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub eppromtype_Click(Index As Integer)
Select Case Index
      Case 0
         eepromid = ID_24C01
      Case 1
         eepromid = ID_24C02
      Case 2
         eepromid = ID_24C04
      Case 3
         eepromid = ID_24C08
      Case 4
         eepromid = ID_24C16
      Case 5
         eepromid = ID_24C32
      Case 6
         eepromid = ID_24C64
      Case 7
         eepromid = ID_24C128
      Case 8
         eepromid = ID_24C256
      Case 9
         eepromid = ID_24C512
      Case 10
         eepromid = ID_24C1024
      Case 11
         eepromid = ID_24C2048
      Case 12
         eepromid = ID_24C4096
  End Select
End Sub

Private Sub eppWrite0_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(eppLen0.Text)
    If (mLen <= 0 Or Len(eppData0.Text) = 0) Then
        MsgBox "������Ҫд������,���ȣ�", vbExclamation, "CH341"
        Exit Sub
    End If
    If (mLen > Len(eppData0.Text) \ 2) Then
        mLen = Len(eppData0.Text) \ 2
    End If
    Call mStrtoVal(eppData0.Text, buffer, mLen)  '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����
    
    If (mOpen = True) Then
        If (CH341EppWriteData(mIndex, buffer, mLen) = False) Then
            MsgBox "EPPд���ݿ�0ʧ�ܣ�", vbExclamation, "CH341"
        End If
        eppLen0.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub eppWrite1_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(eppLen1.Text)
    
    If (mLen <= 0 Or Len(eppData1.Text) = 0) Then
        MsgBox "������д���ݺͳ��ȣ�", vbExclamation, "CH341"
        Exit Sub
    End If
    
    If (mLen > Len(eppData1.Text) \ 2) Then
        mLen = Len(eppData1.Text) \ 2
    End If
    
    Call mStrtoVal(eppData1.Text, buffer, mLen)  '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����
   If (mOpen = True) Then
        If (CH341EppWriteAddr(mIndex, buffer, mLen) = False) Then
            MsgBox "EPPд���ݿ�1ʧ�ܣ�", vbExclamation, "CH341"
        End If
       eppLen1.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub evtbtrefresh_Click()
Dim mBuf(0) As Byte
Dim mLen As Long

If mOpen = True Then
mLen = 1
If (memadd0(0).Value = True) Then
    If (CH341MemReadAddr0(mIndex, mBuf(0), mLen) = False) Then
       MsgBox "MEM��ַ��ʽ�����뿪��״̬ʧ�ܣ� ", vbExclamation, "CH341"
       Exit Sub
    End If
ElseIf (memadd1(1).Value = True) Then
    If (CH341MemReadAddr1(mIndex, mBuf(0), mLen) = False) Then
       MsgBox "MEM��ַ��ʽ1�����뿪��״̬ʧ�ܣ� ", vbExclamation, "CH341"
       Exit Sub
    End If
End If
'��ť״̬��ʾ
    If ((mBuf(0) And 1) = 0) Then
      swit(0).Value = 1
    Else
      swit(0).Value = 0
    End If
    If ((mBuf(0) And 2) = 0) Then
      swit(1).Value = 1
    Else
      swit(1).Value = 0
    End If
    If ((mBuf(0) And 4) = 0) Then
      swit(2).Value = 1
    Else
      swit(2).Value = 0
    End If
    If ((mBuf(0) And 8) = 0) Then
      swit(3).Value = 1
    Else
      swit(3).Value = 0
    End If
    If ((mBuf(0) And 16) = 0) Then
      swit(4).Value = 1
    Else
     swit(4).Value = 0
    End If
    If ((mBuf(0) And 32) = 0) Then
      swit(5).Value = 1
    Else
      swit(5).Value = 0
    End If
    If ((mBuf(0) And 64) = 0) Then
      swit(6).Value = 1
    Else
      swit(6).Value = 0
    End If
    If ((mBuf(0) And 128) = 0) Then
      swit(7).Value = 1
    Else
      swit(7).Value = 0
    End If
Else
    MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
End If
End Sub

Private Sub Form_Load()
mIndex = 0
hopen = CH341OpenDevice(mIndex)
If (hopen = INVALID_HANDLE_VALUE) Then
    'MsgBox "���豸ʧ��", vbExclamation, "CH341PAR"
    mOpen = False
Else
    mOpen = True
End If
'�����豸���֪ͨ
If CH341SetDeviceNotify(mIndex, vbNullString, AddressOf mPCH341_NOTIFY_ROUTINE) = False Then
    MsgBox "�����豸���֪ͨʧ��", vbExclamation, "CH341PAR"
End If
enablebtn (mOpen)
End Sub

Private Sub Form_Unload(Cancel As Integer)
CH341SetDeviceNotify mIndex, vbNullString, 0&
If (mOpen = True) Then
    CH341CloseDevice (mIndex)
End If
End Sub

Private Sub Led_Click(Index As Integer)
Dim mBuf(0) As Byte
Dim mLen As Long
If (mOpen = True) Then
  mLen = 1
  mBuf(0) = CByte((Led(0).Value * (2 ^ 7)) + (Led(1).Value * (2 ^ 6)) + (Led(2).Value * (2 ^ 5)) + (Led(3).Value * (2 ^ 4)) + (Led(4).Value * (2 ^ 3)) + (Led(5).Value * (2 ^ 2)) + (Led(6).Value * (2 ^ 1)) + (Led(7).Value * (2 ^ 0)))         '��ϰ�ť��ֵ
  If (memadd0(0).Value = True) Then '��ַ0
     If (CH341MemWriteAddr0(mIndex, mBuf(0), mLen) = False) Then
        MsgBox "����LED״ֵ̬ʧ�ܣ�", vbExclamation, "CH341"
     End If
  ElseIf (memadd1(1).Value = True) Then
     If (CH341MemWriteAddr1(mIndex, mBuf(0), mLen) = False) Then
        MsgBox "����LED״ֵ̬ʧ�ܣ�", vbExclamation, "CH341"
     End If
  End If
Else
  MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
End If
End Sub

Private Sub memRead0_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(memLen0.Text)
    
    If (mLen <= 0) Then
        MsgBox "�������ȡ����", vbExclamation, "CH341"
        Exit Sub
    End If
    
    If (mOpen = True) Then
        On Error Resume Next
            If (CH341MemReadAddr0(mIndex, buffer, mLen)) Then
                Dim buff As String
                Dim i As Long
                buff = ""
                For i = 0 To mLen - 1 Step 1
                    DoEvents
                    buff = buff & Hex2bit(buffer.buf(i)) + " "
                Next i
                memData0.Text = buff
            Else
                MsgBox "MEM�����ݿ�0ʧ�ܣ� ", vbExclamation, "CH341"
            End If
            memLen0.Text = Hex(mLen)
    Else
         MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub memRead1_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(memLen1.Text)
    If (mLen <= 0) Then
        MsgBox "����������ݳ���", vbExclamation, "CH341"
        Exit Sub
    End If
    
     If (mOpen = True) Then
        If (CH341MemReadAddr1(mIndex, buffer, mLen)) Then
            Dim buff As String
            Dim i As Long
            For i = 0 To mLen - 1
                buff = buff & Hex2bit(buffer.buf(i)) + " "
            Next i
            memData1.Text = buff
        Else
            MsgBox "MEM�����ݿ�1ʧ�ܣ� ", vbExclamation, "CH341"
        End If
        memLen1.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub memWrite0_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(memLen0.Text)
    
    If (mLen <= 0 Or Len(memData0.Text) = 0) Then
        MsgBox "������Ҫд������,���ȣ�", vbExclamation, "CH341"
        Exit Sub
    End If
    
    If (mLen > Len(memData0.Text) / 2) Then
        mLen = Len(memData0.Text) / 2
    End If
    
    Call mStrtoVal(memData0.Text, buffer, mLen)    '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����
    If (mOpen = True) Then
        If (CH341MemWriteAddr0(mIndex, buffer, mLen) = False) Then
            MsgBox "MEMд���ݿ�0ʧ�ܣ�", vbExclamation, "CH341"
       End If
       memLen0.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341"
    End If
End Sub

Private Sub memWrite1_Click()
    Dim mLen As Long
    Dim buffer As arrRBuffer
    
    mLen = HexToBcd(memLen1.Text)
    
    If (mLen <= 0 Or Len(memData1.Text) = 0) Then
        MsgBox "������Ҫд�������,���ȣ�", vbExclamation, "CH341"
        Exit Sub
    End If
    
    If (mLen > Len(memData1.Text) / 2) Then
        mLen = Len(memData1.Text) / 2
    End If
    
    Call mStrtoVal(memData1.Text, buffer, mLen)       '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����
    If (mOpen = True) Then
        If (CH341MemWriteAddr1(mIndex, buffer, mLen) = False) Then
            MsgBox "MEMд���ݿ�0ʧ�ܣ�", vbExclamation, "CH341"
       End If
       memLen1.Text = Hex(mLen)
    Else
        MsgBox "�豸δ�򿪣�", vbExclamation, "CH341PAR"
    End If
End Sub

Private Sub SSTab1_Click(PreviousTab As Integer)

If (mOpen = True) And (SSTab1.Tab = 4) Then
   Call evtbtrefresh_Click
   Call Led_Click(0)
End If

End Sub

Private Sub StreamICRW_Click()
Dim mWrLen As Long
Dim mRdLen As Long
Dim iBuff As arrRBuffer
Dim buffer As arrRBuffer

mWrLen = HexToBcd(I2CWRLen.Text)
mRdLen = HexToBcd(I2CRDLen.Text)

If (mWrLen > 0 And I2CWRBuf.Text = "") Then
  MsgBox "������Ҫд������,���ȣ�", vbExclamation, "CH341"
  Exit Sub
End If
If ((mWrLen = 0) And (mRdLen = 0)) Then
  MsgBox "���������������ĳ��ȣ�", vbExclamation, "CH341"
  Exit Sub
End If
If (mWrLen > Len(Trim(I2CWRBuf.Text)) \ 2) Then
   mWrLen = Len(Trim(I2CWRBuf.Text)) \ 2
End If

Call mStrtoVal(I2CWRBuf.Text, buffer, mWrLen)       '�������ʮ�����Ƹ�ʽ�ַ�����ת����ֵ����

If (mOpen = True) Then
  If (CH341StreamI2C(mIndex, mWrLen, buffer, mRdLen, iBuff) = False) Then
     MsgBox "��ģʽ��д����ʧ�ܣ�", vbExclamation, "CH341"
  Else
    If (mRdLen > 0) Then   '�����ݷ���
       Dim buff As String
       Dim i As Long
       For i = 0 To mRdLen - 1
         buff = buff & Hex2bit(iBuff.buf(i)) + " "
       Next
       I2CRDBuf.Text = buff
    End If
  End If
  I2CWRLen.Text = Hex(mWrLen)
  I2CRDLen.Text = Hex(mRdLen)
Else
  MsgBox "�豸δ�򿪣�", vbExclamation, "CH341PAR"
End If
End Sub

Private Sub CH341_NOTIFY_ROUTINE_KeyUp(KeyCode As Integer, Shift As Integer)  '�豸���֪ͨ�������
    Dim iEventStatus As Long
    iEventStatus = KeyCode '����¼�
    If (iEventStatus = CH341_DEVICE_ARRIVAL) Then ' �豸�����¼�,�Ѿ�����
        If (CH341OpenDevice(mIndex) = INVALID_HANDLE_VALUE) Then
            MsgBox "���豸ʧ��!", vbOK, "CH341PAR"
            mOpen = False
        Else
            mOpen = True  '�򿪳ɹ�
        End If
    ElseIf (iEventStatus = CH341_DEVICE_REMOVE) Then ' �豸�γ��¼�,�Ѿ��γ�
        CH341CloseDevice (mIndex)
        mOpen = False
    End If
    enablebtn (mOpen) '�豸��,��ť����,�豸û��,��ť����
End Sub

Public Sub enablebtn(ByVal bEnable As Boolean)  'bEnable=true :�����尴ť���� ;=false:enable:�����尴ť����
  With frmMain
  
    .eppRead0.Enabled = bEnable
    .eppWrite0.Enabled = bEnable
    .eppRead1.Enabled = bEnable
    .eppWrite1.Enabled = bEnable
    
    .memRead0.Enabled = bEnable
    .memWrite0.Enabled = bEnable
    .memRead1.Enabled = bEnable
    .memWrite1.Enabled = bEnable
    
    .StreamICRW.Enabled = bEnable
    
    .eepromRdDate.Enabled = bEnable
    .eepromWrDate.Enabled = bEnable
    
    .evtbtrefresh.Enabled = bEnable
    .Led(0).Enabled = bEnable
    .Led(1).Enabled = bEnable
    .Led(2).Enabled = bEnable
    .Led(3).Enabled = bEnable
    .Led(4).Enabled = bEnable
    .Led(5).Enabled = bEnable
    .Led(6).Enabled = bEnable
    .Led(7).Enabled = bEnable
    
    If (bEnable = True) Then '���������ʾ
        frmMain.Caption = "CH341EVT **�豸�Ѳ���"
    Else
        frmMain.Caption = "CH341EVT **�豸�Ѱγ�"
    End If
  End With
    
    If (bEnable = True) Then '����I/O�����ѳ�ʼ��,ˢ��LED,�����뿪��״̬
        Call Led_Click(0)
        Call Led_Click(1)
        Call Led_Click(2)
        Call Led_Click(3)
        Call Led_Click(4)
        Call Led_Click(5)
        Call Led_Click(6)
        Call Led_Click(7)
        Call evtbtrefresh_Click
    End If
End Sub
