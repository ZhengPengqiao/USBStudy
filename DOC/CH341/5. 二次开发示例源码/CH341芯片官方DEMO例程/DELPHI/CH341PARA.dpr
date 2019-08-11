program CH341PARA;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  CH341DLL in 'CH341DLL.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
