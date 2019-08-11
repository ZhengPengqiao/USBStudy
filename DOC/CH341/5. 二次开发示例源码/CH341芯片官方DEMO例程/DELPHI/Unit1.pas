unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,CH341DLL, ComCtrls;

type
  TForm1 = class(TForm)
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    GroupBox1: TGroupBox;
    c1: TRadioButton;
    c2: TRadioButton;
    c3: TRadioButton;
    c4: TRadioButton;
    c9: TRadioButton;
    c10: TRadioButton;
    c11: TRadioButton;
    c12: TRadioButton;
    c13: TRadioButton;
    c5: TRadioButton;
    c6: TRadioButton;
    c7: TRadioButton;
    c8: TRadioButton;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label7: TLabel;
    wrdataaddr: TMemo;
    wrdatalen: TMemo;
    wrdatabuf: TMemo;
    WriteEeprom: TButton;
    GroupBox3: TGroupBox;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label8: TLabel;
    rddataaddr: TMemo;
    rddatalen: TMemo;
    rddatabuf: TMemo;
    ReadEeprom: TButton;
    GroupBox5: TGroupBox;
    Label11: TLabel;
    Label12: TLabel;
    ON1: TCheckBox;
    ON2: TCheckBox;
    ON3: TCheckBox;
    ON4: TCheckBox;
    ON5: TCheckBox;
    ON6: TCheckBox;
    ON7: TCheckBox;
    ON8: TCheckBox;
    GroupBox4: TGroupBox;
    Label10: TLabel;
    Label9: TLabel;
    LED1: TCheckBox;
    LED2: TCheckBox;
    LED3: TCheckBox;
    LED4: TCheckBox;
    LED5: TCheckBox;
    LED6: TCheckBox;
    LED7: TCheckBox;
    LED8: TCheckBox;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label19: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    GroupBox6: TGroupBox;
    memadd0: TRadioButton;
    memadd1: TRadioButton;
    Button1: TButton;
    CH341_NOTIFY_ROUTINE: TButton;
    procedure WriteEepromClick(Sender: TObject);
    procedure ReadEepromClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure PageControl1Change(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure LED1Click(Sender: TObject);
    procedure LED2Click(Sender: TObject);
    procedure LED3Click(Sender: TObject);
    procedure LED4Click(Sender: TObject);
    procedure LED5Click(Sender: TObject);
    procedure LED6Click(Sender: TObject);
    procedure LED7Click(Sender: TObject);
    procedure LED8Click(Sender: TObject);
    procedure CH341_NOTIFY_ROUTINEKeyUp(Sender: TObject; var Key: Word;
    Shift: TShiftState);


  private
    { Private declarations }
  public

    { Public declarations }
  end;

          procedure CH341_INT_Func(iStatus:cardinal);stdcall;
var
  Form1: TForm1;
  mIndex:cardinal;
  mOpen:Boolean;
  hopen:cardinal;
implementation

{$R *.dfm}
procedure enablebtn(bEnable:Boolean);  //bEnable=true :各窗体按钮可用 ;
                                                      //=false:enable:各窗体按钮禁用
begin
    Form1.WriteEeprom.Enabled :=bEnable;
    Form1.ReadEeprom.Enabled :=bEnable;
    Form1.Button1.Enabled := bEnable;
    Form1.LED1.Enabled := bEnable;
    Form1.LED2.Enabled := bEnable;
    Form1.LED3.Enabled := bEnable;
    Form1.LED4.Enabled := bEnable;
    Form1.LED5.Enabled := bEnable;
    Form1.LED6.Enabled := bEnable;
    Form1.LED7.Enabled := bEnable;
    Form1.LED8.Enabled := bEnable;
    If (bEnable = True) Then //窗体标题显示
    begin
        Form1.Caption := 'CH341EVT **设备已插上';
    end
    Else
    begin
        Form1.Caption := 'CH341EVT **设备已拔出';
    End;
    If (bEnable = True) Then //数字I/O窗口已初始化,刷新LED,按拔码开关状态
    begin
        Form1.LED1Click(Form1.LED1);
        Form1.LED2Click(Form1.LED2);
        Form1.LED3Click(Form1.LED3);
        Form1.LED4Click(Form1.LED4);
        Form1.LED5Click(Form1.LED5);
        Form1.LED6Click(Form1.LED6);
        Form1.LED7Click(Form1.LED7);
        Form1.LED8Click(Form1.LED8);
        Form1.Button1Click(Form1.Button1 ) ;
    End;
end;

procedure CH341_INT_Func(iStatus:cardinal);stdcall;
begin
    PostMessage(Form1.CH341_NOTIFY_ROUTINE.Handle,WM_KEYUP,iStatus,0);
end;

//数据格式转换格式
function BytetoHex(date:byte):string;
var de:integer;
begin
  de:=0;
  case date of
       0..9:   BytetoHex:='0'+inttostr(date);
       10..15: bytetohex:='0'+chr(ord('A')+(date-10));
       16..255:bytetohex:=IntToHex(date,de);
  else
               bytetohex:='00';
  end;
end;

//两位十六进制字符转换为数值
function HexToBcd(Str:string):cardinal;
var
 strLen:byte;
  x:char;
  i:byte;
  FunResult:cardinal;
begin
  str:=trim(str);
  strlen :=Length(str);
  funresult:=0;
  For i := 1 To (StrLen ) do
  begin
    x := upcase(str[i]);
    Case x  of
        'A':FunResult := FunResult + 10 * Trunc(Exp((strlen-i)*ln(16)));
        'B':FunResult := FunResult + 11 * Trunc(Exp((strlen-i)*ln(16)));
        'C':FunResult := FunResult + 12 * Trunc(Exp((strlen-i)*ln(16)));
        'D':FunResult := FunResult + 13 * Trunc(Exp((strlen-i)*ln(16)));
        'E':FunResult := FunResult + 14 * Trunc(Exp((strlen-i)*ln(16)));
        'F':FunResult := FunResult + 15 * Trunc(Exp((strlen-i)*ln(16)));
        '0'..'9':FunResult := FunResult + strtoint(x) * Trunc(Exp((strlen-i)*ln(16)));
    Else   FunResult := 0;
    End;
  end;
  hextobcd:=FunResult;
end;

function BoolToByte(bool:boolean):byte;
begin
if bool=true then
  BoolToByte:=1
else
  BoolToByte:=0;
end;

function EepromID():EEPROM_TYPE;  //根据单选按纽,选择E2P器件型号
var
  iEepromID:EEPROM_TYPE;
begin
    iEepromID:=ID_24C01;
    if(form1.c1.Checked=true) then
       iEepromID:=ID_24C01;
    if(form1.c2.Checked=true) then
       iEepromID:=ID_24C02;
    if(form1.c3.Checked=true) then
       iEepromID:=ID_24C04;
    if(form1.c4.Checked=true) then
       iEepromID:=ID_24C08;
    if(form1.c5.Checked=true) then
      iEepromID:=ID_24C16;
    if(form1.c6.Checked=true) then
      iEepromID:=ID_24C32;
    if(form1.c7.Checked=true) then
       iEepromID:=ID_24C64;
    if(form1.c8.Checked=true) then
       iEepromID:=ID_24C128;
    if(form1.c9.Checked=true) then
       iEepromID:=ID_24C256;
    if(form1.c10.Checked=true) then
      iEepromID:=ID_24C512;
    if(form1.c11.Checked=true) then
       iEepromID:=ID_24C1024;
    if(form1.c12.Checked=true) then
       iEepromID:=ID_24C2048;
    if(form1.c13.Checked=true) then
       iEepromID:=ID_24C4096;
    EepromID:=iEepromID;
end ;

procedure SendLedVal();

var
  mBuf:array[0..(mMAX_BUFFER_LENGTH - 1)]of Byte;
  mLen:cardinal;
begin
  If (mOpen = true) Then
  begin
    mLen := 1;
    mBuf[0] :=((BoolToByte(form1.LED1.checked) shl 7) + (BoolToByte(form1.LED2.checked) shl 6) + (BoolToByte(form1.LED3.checked) shl 5) + (BoolToByte(form1.LED4.checked) shl 4) + (BoolToByte(form1.LED5.checked) shl 3) + (BoolToByte(form1.LED6.checked) shl 2) + (BoolToByte(form1.LED7.checked) shl 1) + (BoolToByte(form1.LED8.checked) shl 0));         //组合按钮键值
    If (form1.memadd0.checked = True) Then //地址0
    begin
      If (CH341MemWriteAddr0(mIndex, @mBuf[0], @mLen) = False) Then
        application.MessageBox ( '发送LED状态值失败！','CH341',MB_ICONEXCLAMATION);
    end
    Else
    begin
      If (form1.memadd1.checked= True) Then
      begin
       If (CH341MemWriteAddr1(mIndex, @mBuf[0], @mLen) = False) Then
         application.MessageBox ( '发送LED状态值失败！', 'CH341',MB_ICONEXCLAMATION);
      End;
    end;
  end
  Else
    application.MessageBox ( '设备未打开！','CH341',MB_ICONEXCLAMATION);
end;
procedure TForm1.WriteEepromClick(Sender: TObject);
var
 mDataAddr:cardinal;
 mLen:cardinal;
 i:cardinal;
 Tems:String;
 Temh:byte;
 hexval:integer;
 buffer:array[0..(mMAX_BUFFER_LENGTH - 1)]of byte;
begin
  hexval:=0;
  mLen := HexToBcd(WrDataLen.Text) ;
 If (WrDataAddr.Text = '') Then
 begin
   application.MessageBox('请输入数据单元起始地址！','CH341',MB_ICONEXCLAMATION);
   Exit;
 End;
 If ((mLen <= 0) Or (WrDataBuf.Text = '')) Then
 begin
   application.MessageBox( '请输入要写入的数据,长度！', 'CH341',MB_ICONEXCLAMATION);
   Exit;
 End;
  If (mLen > (Length(WrDataBuf.Text ) / 2)) Then //在输入长度和数据长度中取小值
    mLen := Length(WrDataBuf.text) div 2;
  mDataAddr := HexToBcd(WrDataAddr.Text);

  for i:=0 to (mlen-1) do
  begin
      Tems := Trim(copy(wrdatabuf.Text , (i * 2 + 1), 2));
      Temh := hextobcd(Tems);
      buffer[i]:=Temh;
  end ;

  If (mOpen = True) Then
  begin
     If (CH341WriteEEPROM(mIndex, EepromID(), mDataAddr, mLen, @buffer[0]) = False) Then
        application.MessageBox('读E2PROM数据失败！','CH341',MB_ICONEXCLAMATION);
     WrDataLen.Text := inttohex(mLen,hexval);
  end
  Else
    application.MessageBox('设备未打开！', 'CH341',MB_ICONEXCLAMATION);
end;

procedure TForm1.ReadEepromClick(Sender: TObject);
var
  hexval:integer;
  mDataAddr:cardinal;
  mlen:cardinal;
  buffer:array[0..(mMAX_BUFFER_LENGTH - 1)]of byte;
  buff : String;
  i : cardinal;
begin
 hexval:=0;
 mlen :=hextobcd(rddatalen.Text);

 If (RdDataAddr.Text = '') Then
 begin
   application.MessageBox('请输入数据单元起始地址！','CH341',MB_ICONEXCLAMATION);
   Exit ;
 End;
 If (mlen <= 0) Then
 begin
   application.MessageBox('请输入读取长度！','CH341',MB_ICONEXCLAMATION);
   Exit;
 End;
 mDataAddr := HexToBcd(RdDataAddr.Text );
 If (mOpen = True) Then
 begin
    If (CH341ReadEEPROM(mIndex, eepromid, mDataAddr, mlen, @buffer[0])=true) Then
    begin
      buff:='';
      For i := 0 To mlen-1 do
         buff :=buff + bytetohex(buffer[i])+' ';
      RdDataBuf.Text := buff;
    end                                           
    Else
      application.MessageBox('读E2PROM数据失败！','CH341',MB_ICONEXCLAMATION);
    RdDataLen.Text := inttohex(mlen,hexval);
 end
 Else
    application.MessageBox ('设备未打开！', 'CH341',MB_ICONEXCLAMATION);

end;

procedure TForm1.FormCreate(Sender: TObject);

begin
mIndex := 0;
hopen := CH341OpenDevice(mIndex);
If (hopen = INVALID_HANDLE_VALUE) Then
begin
    //application.MessageBox( '打开设备失败','CH341PAR',MB_ICONEXCLAMATION);
    mOpen := False;
end
Else
begin
    mOpen := True;
    rddatalen.Text :='0';
    rddataaddr.Text :='0';
    wrdatalen.Text :='0';
    wrdataaddr.Text :='0';
end;
enablebtn(mOpen); //设备打开输入按钮可用,没打开按钮禁用
CH341SetDeviceNotify(mIndex,'',CH341_INT_Func);        //设备插拔通知
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
CH341SetDeviceNotify(mIndex,'',mPCH341_NOTIFY_ROUTINE(0));
If (mOpen = True) Then
   CH341CloseDevice (mIndex);
end;

procedure TForm1.PageControl1Change(Sender: TObject);
begin
If (mOpen = True) Then
   SendLedVal();
   form1.Button1Click(Sender);
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  mBuf:array[0..(mMAX_BUFFER_LENGTH - 1)]of Byte;
  mLen:cardinal;
begin
If (mOpen = true) Then
begin
  mBuf[0]:=0;
  mLen := 1;
  If (memadd0.Checked = True) Then
  begin
    If (CH341MemReadAddr0(mIndex, @mBuf[0], @mLen) = False) Then
    begin
       application.MessageBox ('MEM地址方式读拔码开关状态失败！', 'CH341',MB_ICONEXCLAMATION);
       Exit;
    End;
  end
  Else
  begin
    if (memadd1.Checked  = True) then
    begin
       If (CH341MemReadAddr1(mIndex, @mBuf, @mLen) = False) Then
       begin
         application.MessageBox ( 'MEM地址方式1读拔码开关状态失败！ ','CH341',MB_ICONEXCLAMATION);
         Exit;
       end;
    End;
  end;
//按钮状态显示
    If ((mBuf[0] And 1) = 0) Then
      ON1.checked := true
    Else
      ON1.checked := false;

    If ((mBuf[0] And 2) = 0) Then
      ON2.checked := true
    Else
      ON2.checked := false;

    If ((mBuf[0] And 4) = 0) Then
      ON3.checked := true
    Else
      ON3.checked := false;

    If ((mBuf[0] And 8) = 0) Then
      ON4.checked := true
    Else
      ON4.checked := false;

    If ((mBuf[0] And 16) = 0) Then
      ON5.checked := true
    Else
     ON5.checked := false;

    If ((mBuf[0] And 32) = 0) Then
      ON6.checked := true
    Else
      ON6.checked := false;

    If ((mBuf[0] And 64) = 0) Then
      ON7.checked := true
    Else
      ON7.checked := false;

    If ((mBuf[0] And 128) = 0) Then
      ON8.checked := true
    Else
      ON8.checked := false;
end
//Else
//    application.messagebox( '设备未打开！','CH341',MB_ICONEXCLAMATION);

end;

procedure TForm1.LED1Click(Sender: TObject);
begin
SendLedVal();  //发送LED状态值
end;

procedure TForm1.LED2Click(Sender: TObject);
begin
SendLedVal();     //发送LED状态值
end;

procedure TForm1.LED3Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;

procedure TForm1.LED4Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;

procedure TForm1.LED5Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;

procedure TForm1.LED6Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;

procedure TForm1.LED7Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;

procedure TForm1.LED8Click(Sender: TObject);
begin
SendLedVal();    //发送LED状态值
end;


procedure TForm1.CH341_NOTIFY_ROUTINEKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
var
   iEventStatus:word;
begin
  iEventStatus := Key; //插拔事件
    If (iEventStatus = CH341_DEVICE_ARRIVAL) Then // 设备插入事件,已经插入
    begin
        If (CH341OpenDevice(mIndex) = -1) Then
        begin
            MessageBox(Form1.Handle, '打开设备失败!', 'CH341PAR',0);
            mOpen := FALSE;
        end
        Else
            mOpen := True;  //打开成功
    end
    Else
    begin
         If (iEventStatus = CH341_DEVICE_REMOVE) Then // 设备拔出事件,已经拔出
         begin
             CH341CloseDevice (mIndex);
             mOpen := False;
         End;
    end ;
    enablebtn (mOpen);  //设备打开,按钮可用,设备没打开,按钮禁用
end;



end.




