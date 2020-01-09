unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    mytext: TMemo;
    Tfile: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Sfile: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button1Click(Sender: TObject);
var f,r:file; i:longint; b:byte; s,f1,f2:string;
begin s:=mytext.text;  f1:=Sfile.text; f2:=Tfile.text;
assignfile(f,f1); reset(f,1);
assignfile(r,f2); rewrite(r,1); i:=0;
for i:=0 to filesize(f) do begin
  seek (f,i); blockread(f,b,1); blockwrite(r,b,1); end;
seek(r,5); b:=length(s); blockwrite(r,b,1);
seek (r,filesize(f));
for i:=0 to length(s) do begin
b:=ord(s[i]); blockwrite(r,b,1); end;
closefile(f); closefile(r);
end;

procedure TForm1.Button2Click(Sender: TObject);
var f,r:file; i:longint; b:byte; f1,f2,s:string; ch:char;
begin
f1:=Sfile.text; f2:=Tfile.text;
assignfile(r,f2); reset(r,1);
seek(r,5); blockread(r,b,1);
i:=filesize(r)-b;
for i:= filesize(r)-b to filesize(r) do begin
  seek(r,i); blockread(r,b,1);
  mytext.text:=mytext.text+chr(b); end;
closefile(r);
end;

end.

