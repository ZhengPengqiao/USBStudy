object Form1: TForm1
  Left = 127
  Top = 152
  Width = 534
  Height = 532
  Caption = 'CH341EVT'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000111111111111111111111111111111110000
    0000000000000000000000000000000CC0000CC000000CCCC000CC0000CC000C
    C0000CC00000CC00CC00CC0000CC000CC0000CC0000CC0000C00CC0000CC00CC
    CC00CCCC000CC0000000CC0000CC00CC0C00C0CC000CC0000000CC0000CC0CC0
    0CCCC00CC00CC0000000CCCCCCCC0CC00CCCC00CC00CC0000000CC0000CCCC00
    00CC0000CC0CC0000C00CC0000CCCC0000CC0000CC00CC00CC00CC0000CCCC00
    00CC0000CC000CCCC000CC0000CCF01E7E7FF3FE7E7FF3FC3E7FF3FC3E7FF3FD
    BE7FF0399E7FF3F99E7FF3F99E7FF3F3CE7FF013C00FFFFFFFFFC3330F999932
    6799993264199F33E4999F038E199933E61999326711C3330F99FFFFFFFF0000
    0000FFFFFFFFE79F873CE79F333CE79E7B3CC30E7F3CCB4E7F3C98667F009866
    7F3C3CF27B3C3CF3333C3CF3873C280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    00000000000000000000000000000000000000000000FFFF0000FFFF0000FFFF
    0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF
    0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000}
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 12
    Top = 8
    Width = 497
    Height = 473
    ActivePage = TabSheet2
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabIndex = 1
    TabOrder = 0
    OnChange = PageControl1Change
    object TabSheet1: TTabSheet
      Caption = 'EEPROM'#35835#20889
      object GroupBox1: TGroupBox
        Left = 20
        Top = 8
        Width = 101
        Height = 409
        Caption = 'EEPROM'#22411#21495
        TabOrder = 0
        object c1: TRadioButton
          Left = 10
          Top = 18
          Width = 69
          Height = 25
          Caption = '24C01'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object c2: TRadioButton
          Left = 10
          Top = 41
          Width = 69
          Height = 25
          Caption = '24C02'
          TabOrder = 1
        end
        object c3: TRadioButton
          Left = 10
          Top = 64
          Width = 69
          Height = 25
          Caption = '24C04'
          TabOrder = 2
        end
        object c4: TRadioButton
          Left = 10
          Top = 88
          Width = 69
          Height = 25
          Caption = '24C08'
          TabOrder = 3
        end
        object c9: TRadioButton
          Left = 10
          Top = 204
          Width = 69
          Height = 25
          Caption = '24C256'
          TabOrder = 4
        end
        object c10: TRadioButton
          Left = 10
          Top = 228
          Width = 69
          Height = 25
          Caption = '24C512'
          TabOrder = 5
        end
        object c11: TRadioButton
          Left = 10
          Top = 251
          Width = 69
          Height = 25
          Caption = '24C1024'
          TabOrder = 6
        end
        object c12: TRadioButton
          Left = 10
          Top = 274
          Width = 69
          Height = 25
          Caption = '24C2048'
          TabOrder = 7
        end
        object c13: TRadioButton
          Left = 10
          Top = 298
          Width = 69
          Height = 25
          Caption = '24C4096'
          TabOrder = 8
        end
        object c5: TRadioButton
          Left = 10
          Top = 111
          Width = 69
          Height = 25
          Caption = '24C16'
          TabOrder = 9
        end
        object c6: TRadioButton
          Left = 10
          Top = 134
          Width = 69
          Height = 25
          Caption = '24C32'
          TabOrder = 10
        end
        object c7: TRadioButton
          Left = 10
          Top = 158
          Width = 69
          Height = 25
          Caption = '24C64'
          TabOrder = 11
        end
        object c8: TRadioButton
          Left = 10
          Top = 181
          Width = 69
          Height = 25
          Caption = '24C128'
          TabOrder = 12
        end
      end
      object GroupBox2: TGroupBox
        Left = 136
        Top = 10
        Width = 341
        Height = 201
        Caption = #20889#20837#25968#25454#65292'API=CH341WriteEEPROM'
        TabOrder = 1
        object Label1: TLabel
          Left = 16
          Top = 20
          Width = 96
          Height = 13
          Caption = #25968#25454#21333#20803#36215#22987#22320#22336
        end
        object Label2: TLabel
          Left = 16
          Top = 64
          Width = 73
          Height = 13
          AutoSize = False
          Caption = #20889#20837#38271#24230
        end
        object Label3: TLabel
          Left = 15
          Top = 108
          Width = 242
          Height = 13
          AutoSize = False
          Caption = #22810#20010#25968#25454#65288'16'#36827#21046#65292#20004#23383#31526#19968#32452#65289
        end
        object Label7: TLabel
          Left = 88
          Top = 64
          Width = 38
          Height = 13
          Caption = '(<400H)'
        end
        object wrdataaddr: TMemo
          Left = 16
          Top = 36
          Width = 121
          Height = 25
          TabOrder = 0
        end
        object wrdatalen: TMemo
          Left = 16
          Top = 80
          Width = 121
          Height = 25
          TabOrder = 1
        end
        object wrdatabuf: TMemo
          Left = 15
          Top = 124
          Width = 218
          Height = 69
          Lines.Strings = (
            '')
          ScrollBars = ssVertical
          TabOrder = 2
        end
        object WriteEeprom: TButton
          Left = 212
          Top = 80
          Width = 75
          Height = 25
          Caption = 'Write'
          TabOrder = 3
          OnClick = WriteEepromClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 136
        Top = 216
        Width = 341
        Height = 201
        Caption = #35835#20986#25968#25454#65292'API=CH341ReadEEPROM'
        TabOrder = 2
        object Label4: TLabel
          Left = 16
          Top = 20
          Width = 96
          Height = 13
          Caption = #25968#25454#21333#20803#36215#22987#22320#22336
        end
        object Label5: TLabel
          Left = 16
          Top = 64
          Width = 85
          Height = 13
          AutoSize = False
          Caption = #35835#21462#38271#24230
        end
        object Label6: TLabel
          Left = 17
          Top = 108
          Width = 286
          Height = 13
          AutoSize = False
          Caption = #22810#20010#25968#25454#65288'16'#36827#21046#65292#20004#23383#31526#19968#32452#65289
        end
        object Label8: TLabel
          Left = 100
          Top = 64
          Width = 38
          Height = 13
          Caption = '(<400H)'
        end
        object rddataaddr: TMemo
          Left = 16
          Top = 36
          Width = 121
          Height = 25
          TabOrder = 0
        end
        object rddatalen: TMemo
          Left = 16
          Top = 80
          Width = 121
          Height = 25
          TabOrder = 1
        end
        object rddatabuf: TMemo
          Left = 15
          Top = 124
          Width = 263
          Height = 69
          ScrollBars = ssVertical
          TabOrder = 2
        end
        object ReadEeprom: TButton
          Left = 220
          Top = 72
          Width = 75
          Height = 25
          Caption = 'Read'
          TabOrder = 3
          OnClick = ReadEepromClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = #25968#23383'I/O'
      ImageIndex = 1
      object Label13: TLabel
        Left = 13
        Top = 29
        Width = 185
        Height = 13
        AutoSize = False
        Caption = #36755#20986#28436#31034#65306'LED'#22797#36873#26694#25511#21046#35780
      end
      object Label14: TLabel
        Left = 13
        Top = 45
        Width = 145
        Height = 13
        AutoSize = False
        Caption = #20272#26495#20013'8'#20010'LED'#29366#24577
      end
      object Label15: TLabel
        Left = 13
        Top = 81
        Width = 177
        Height = 13
        AutoSize = False
        Caption = #36755#20837#28436#31034#65306'8'#20301#24320#20851#29366#24577#26159#28857
      end
      object Label16: TLabel
        Left = 13
        Top = 97
        Width = 185
        Height = 13
        AutoSize = False
        Caption = '"'#21047#26032'"'#25353#32445#33719#24471#35780#20272#26495#20013#25320#30721
      end
      object Label19: TLabel
        Left = 13
        Top = 113
        Width = 133
        Height = 13
        AutoSize = False
        Caption = #25320#30721#24320#20851#30340#24403#21069#29366#24577
      end
      object Label17: TLabel
        Left = 13
        Top = 249
        Width = 173
        Height = 13
        AutoSize = False
        Caption = #25152#29992'API'#19982'MEM'#24182#21475#30456#21516#65292#21482
      end
      object Label18: TLabel
        Left = 13
        Top = 265
        Width = 129
        Height = 13
        AutoSize = False
        Caption = #26159#38271#24230#24635#26159'1'#23383#33410
      end
      object GroupBox5: TGroupBox
        Left = 347
        Top = 20
        Width = 125
        Height = 361
        Caption = #36755#20837#65306'8'#20301#24320#20851#29366#24577
        TabOrder = 0
        object Label11: TLabel
          Left = 25
          Top = 308
          Width = 70
          Height = 21
          AutoSize = False
          Caption = 'OFF:'#19981#36873#20013
        end
        object Label12: TLabel
          Left = 28
          Top = 291
          Width = 61
          Height = 17
          AutoSize = False
          Caption = 'ON:'#36873#20013
        end
        object ON1: TCheckBox
          Left = 35
          Top = 24
          Width = 53
          Height = 21
          Caption = 'ON1'
          Enabled = False
          TabOrder = 0
        end
        object ON2: TCheckBox
          Left = 35
          Top = 58
          Width = 53
          Height = 21
          Caption = 'ON2'
          Enabled = False
          TabOrder = 1
        end
        object ON3: TCheckBox
          Left = 35
          Top = 92
          Width = 53
          Height = 21
          Caption = 'ON3'
          Enabled = False
          TabOrder = 2
        end
        object ON4: TCheckBox
          Left = 35
          Top = 126
          Width = 53
          Height = 21
          Caption = 'ON4'
          Enabled = False
          TabOrder = 3
        end
        object ON5: TCheckBox
          Left = 35
          Top = 161
          Width = 53
          Height = 21
          Caption = 'ON5'
          Enabled = False
          TabOrder = 4
        end
        object ON6: TCheckBox
          Left = 35
          Top = 195
          Width = 53
          Height = 21
          Caption = 'ON6'
          Enabled = False
          TabOrder = 5
        end
        object ON7: TCheckBox
          Left = 35
          Top = 229
          Width = 53
          Height = 21
          Caption = 'ON7'
          Enabled = False
          TabOrder = 6
        end
        object ON8: TCheckBox
          Left = 35
          Top = 264
          Width = 53
          Height = 21
          Caption = 'ON8'
          Enabled = False
          TabOrder = 7
        end
        object Button1: TButton
          Left = 12
          Top = 328
          Width = 97
          Height = 25
          Caption = #28857#27492#21047#26032#29366#24577
          TabOrder = 8
          OnClick = Button1Click
        end
      end
      object GroupBox4: TGroupBox
        Left = 208
        Top = 24
        Width = 125
        Height = 361
        Caption = #36755#20986#65306'LED'#26174#31034#25511#21046
        TabOrder = 1
        object Label10: TLabel
          Left = 16
          Top = 319
          Width = 85
          Height = 13
          AutoSize = False
          Caption = #26410#36873#20013':'#28783#20142
        end
        object Label9: TLabel
          Left = 29
          Top = 303
          Width = 61
          Height = 17
          AutoSize = False
          Caption = #36873#20013':'#28783#28781
        end
        object LED1: TCheckBox
          Left = 32
          Top = 24
          Width = 53
          Height = 21
          Caption = 'LED1'
          TabOrder = 0
          OnClick = LED1Click
        end
        object LED2: TCheckBox
          Left = 32
          Top = 58
          Width = 53
          Height = 21
          Caption = 'LED2'
          TabOrder = 1
          OnClick = LED2Click
        end
        object LED3: TCheckBox
          Left = 32
          Top = 92
          Width = 53
          Height = 21
          Caption = 'LED3'
          TabOrder = 2
          OnClick = LED3Click
        end
        object LED4: TCheckBox
          Left = 32
          Top = 126
          Width = 53
          Height = 21
          Caption = 'LED4'
          TabOrder = 3
          OnClick = LED4Click
        end
        object LED5: TCheckBox
          Left = 32
          Top = 161
          Width = 53
          Height = 21
          Caption = 'LED5'
          TabOrder = 4
          OnClick = LED5Click
        end
        object LED6: TCheckBox
          Left = 32
          Top = 195
          Width = 53
          Height = 21
          Caption = 'LED6'
          TabOrder = 5
          OnClick = LED6Click
        end
        object LED7: TCheckBox
          Left = 32
          Top = 229
          Width = 53
          Height = 21
          Caption = 'LED7'
          TabOrder = 6
          OnClick = LED7Click
        end
        object LED8: TCheckBox
          Left = 32
          Top = 264
          Width = 53
          Height = 21
          Caption = 'LED8'
          TabOrder = 7
          OnClick = LED8Click
        end
      end
      object GroupBox6: TGroupBox
        Left = 13
        Top = 309
        Width = 137
        Height = 77
        Caption = #36873#25321'MEM'#35835#20889#22320#22336
        TabOrder = 2
        object memadd0: TRadioButton
          Left = 16
          Top = 20
          Width = 85
          Height = 21
          Caption = #22320#22336'0'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object memadd1: TRadioButton
          Left = 16
          Top = 40
          Width = 77
          Height = 21
          Caption = #22320#22336'0'
          TabOrder = 1
        end
      end
      object CH341_NOTIFY_ROUTINE: TButton
        Left = 148
        Top = 404
        Width = 213
        Height = 25
        Caption = #27169#25311#22788#29702#35774#22791#25402#25300#20013#26029#20107#20214
        Enabled = False
        TabOrder = 3
        OnKeyUp = CH341_NOTIFY_ROUTINEKeyUp
      end
    end
  end
end
