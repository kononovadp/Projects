unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ExtCtrls;

type

  { TForm1 }

  TForm1 = class(TForm)
    CheckBox1: TCheckBox;
    Label1: TLabel;
    RadioGroup1: TRadioGroup;
    ToggleBox1: TToggleBox;
    procedure CheckBox1Change(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
    procedure ToggleBox1Change(Sender: TObject);
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

procedure TForm1.ToggleBox1Change(Sender: TObject);
begin
  label1.Visible:=not(label1.Visible) ;
end;

procedure TForm1.CheckBox1Change(Sender: TObject);
begin
  if checkbox1.Checked=true then label1.Caption:='HALLO'
  else label1.Caption:='hallo';
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
  case radiogroup1.ItemIndex of
  0: label1.Font.Color:=clred;
  1:  label1.Font.Color:=clgreen;
  2: label1.Font.Color:=clyellow;

  end;
end;

end.

