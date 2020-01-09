unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  ActnList;

type

  { TForm1 }

  TForm1 = class(TForm)
    convert: TButton;
    result: TMemo;
    number: TMemo;
    procedure convertClick(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.lfm}
function ntotext(n:int64):string;
var u:array[0..19] of string; //единицы
d:array[2..9] of string; s:string;
h:array[1..9] of string;
ui,di,hi:integer;
begin
u[0]:='ноль'; u[1]:='один'; u[2]:='два';
u[3]:='три'; u[4]:='четыре'; u[5]:='пять';
u[6]:='шесть'; u[7]:='семь'; u[8]:='восемь';
u[9]:='девять'; u[10]:='десять'; u[11]:='одиннадцать';
u[12]:='двенадцать'; u[13]:='тринадцать'; u[14]:='четырнадцать';
u[15]:='пятьнадцать'; u[16]:='шестьнадцать'; u[17]:='семьнадцать';
u[18]:='восемьнадцать'; u[19]:='девятьнадцать';
d[2]:='двадцать'; d[3]:='тридцать'; d[4]:='сорок'; d[5]:='пятьдесят';
d[6]:='шестьдесят'; d[7]:='семьдесят'; d[8]:='восемьдесят'; d[9]:='девяносто';
h[1]:='сто'; h[2]:='двести'; h[3]:='триста'; h[4]:='четыреста'; h[5]:='пятьсот';
h[6]:='шестьсот'; h[7]:='семьсот'; h[8]:='восемьсот'; h[9]:='девятьсот';
if n<20 then s:=u[n] else
if n<100 then begin
ui:=n mod 10; di:=n div 10;
s:=d[di]; if ui>0 then s:=s+' '+u[ui]; end else
if n<1000 then begin
ui:= n mod 10; if ui>0 then s:=u[ui];
n:= n div 10; ui:=n mod 10; if ui>0 then s:=d[ui]+' '+s;
ui:=n div 10; s:=h[ui]+' '+s; end;
ntotext:=s;
end;

{ TForm1 }

procedure TForm1.convertClick(Sender: TObject);
var n:int64;
begin

n:=strtoint(number.text); result.text:=ntotext(n);
end;

end.

