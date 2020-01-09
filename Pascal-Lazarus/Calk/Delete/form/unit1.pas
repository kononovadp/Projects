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
    Button3: TButton;
    ComboBox1: TComboBox;
    Edit1: TEdit;
    Edit2: TEdit;
    Label1: TLabel;
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Edit1Click(Sender: TObject);
    procedure Edit2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;
  s1,s2,s:string;
  f:byte;
implementation

{$R *.lfm}

{ TForm1 }

procedure TForm1.Button2Click(Sender: TObject);
begin
  if f=1 then edit1.text:=edit1.text+'0';
  if f=2 then edit2.text:=edit2.text+'0';

end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  if f=1 then edit1.text:=edit1.text+'1';
  if f=2 then edit2.text:=edit2.text+'1';
end;

procedure TForm1.Edit1Click(Sender: TObject);
begin
  f:=1;
end;

procedure TForm1.Edit2Click(Sender: TObject);
begin
  f:=2;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  f:=1;
end;

end.

