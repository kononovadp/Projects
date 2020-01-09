unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, LResources, Forms, Controls, Graphics, Dialogs, StdCtrls,
  EditBtn, ExtCtrls, maskedit, Buttons, ExtDlgs, Math, CLIPBrd, crt;

type

  { TCalculator }

  TCalculator = class(TForm)
    Percentage: TButton;
    CopyResult: TButton;
    ClearOperationsField: TButton;
    EnterX_static: TStaticText;
    EnterY_static: TStaticText;
    TextOfOperations: TMemo;
    xPlusMinus: TButton;
    PasteResultToX: TButton;
    ctg_x: TButton;
    NumberY: TStaticText;
    PasteResultToY: TButton;
    ClearAllFields: TButton;
    Result: TStaticText;
    Operations: TStaticText;
    squrt_X: TButton;
    NumberX: TStaticText;
    X_stepen_Y: TButton;
    ln_x1: TButton;
    logy_X: TButton;
    tg_x: TButton;
    yPlusMinus: TButton;
    pointY: TButton;
    cos_x: TButton;
    XdivideY: TButton;
    XplusY: TButton;
    x0: TButton;
    pointX: TButton;
    XminusY: TButton;
    XmultiplyY: TButton;
    sin_x: TButton;
    korenX_stepenY: TButton;
    y1: TButton;
    y2: TButton;
    y3: TButton;
    y4: TButton;
    y5: TButton;
    y6: TButton;
    y7: TButton;
    y8: TButton;
    y9: TButton;
    y0: TButton;
    x2: TButton;
    x3: TButton;
    x4: TButton;
    x5: TButton;
    x6: TButton;
    x7: TButton;
    x8: TButton;
    x9: TButton;
    Pi_x: TButton;
    x1: TButton;
    Clear_x: TButton;
    Pi_y: TButton;
    Clear_y: TButton;
    TextOfNumberX: TEdit;
    TextOfNumberY: TEdit;
    TextOfResult: TEdit;
    function CheckUserData(Mode : byte) : boolean;
    procedure factorial_xClick(Sender: TObject);
    procedure YPlusMinusClick(Sender: TObject);
    procedure ClearOperationsFieldClick(Sender: TObject);
    procedure CopyResultClick(Sender: TObject);
    procedure cos_xClick(Sender: TObject);
    procedure ctg_xClick(Sender: TObject);
    procedure korenX_stepenYClick(Sender: TObject);
    procedure ln_x1Click(Sender: TObject);
    procedure logy_XClick(Sender: TObject);
    procedure PasteResultToXClick(Sender: TObject);
    procedure PasteResultToYClick(Sender: TObject);
    procedure PercentageClick(Sender: TObject);
    procedure Pi_xClick(Sender: TObject);
    procedure Pi_yClick(Sender: TObject);
    procedure pointXClick(Sender: TObject);
    procedure pointYClick(Sender: TObject);
    procedure ClearAllFieldsClick(Sender: TObject);
    procedure Clear_xClick(Sender: TObject);
    procedure Clear_yClick(Sender: TObject);
    procedure sin_xClick(Sender: TObject);
    procedure squrt_XClick(Sender: TObject);
    procedure tg_xClick(Sender: TObject);
    procedure x0Click(Sender: TObject);
    procedure x1Click(Sender: TObject);
    procedure x2Click(Sender: TObject);
    procedure x3Click(Sender: TObject);
    procedure x4Click(Sender: TObject);
    procedure x5Click(Sender: TObject);
    procedure x6Click(Sender: TObject);
    procedure x7Click(Sender: TObject);
    procedure x8Click(Sender: TObject);
    procedure x9Click(Sender: TObject);
    procedure XdivideYClick(Sender: TObject);
    procedure XminusYClick(Sender: TObject);
    procedure XmultiplyYClick(Sender: TObject);
    procedure xPlusMinusClick(Sender: TObject);
    procedure XplusYClick(Sender: TObject);
    procedure X_stepen_YClick(Sender: TObject);
    procedure y0Click(Sender: TObject);
    procedure y1Click(Sender: TObject);
    procedure y2Click(Sender: TObject);
    procedure y3Click(Sender: TObject);
    procedure y4Click(Sender: TObject);
    procedure y5Click(Sender: TObject);
    procedure y6Click(Sender: TObject);
    procedure y7Click(Sender: TObject);
    procedure y8Click(Sender: TObject);
    procedure y9Click(Sender: TObject);
  private
    function RadianToGradus(N : real) : real;
  public
    { public declarations }
  end;
   const nmax=1024;
type ts = 0..9; chislo=array[1..nmax] of ts;
var
  Calculator: TCalculator;
  x, y: real; z:shortstring;


implementation
{$R *.lfm}
{TCalculator}

//функция преобразование радианов в градусы
function TCalculator.RadianToGradus(N : real) : real;
begin
  RadianToGradus := (Pi/180) * N;
end;

//проверка данных, введенных пользователем
function TCalculator.CheckUserData(Mode : byte) : boolean;
var i      : byte;
    sX, sY, sZ : string[16];
begin
  sX := Trim(TextOfNumberX.Text);
  for i := 1 to Length(sX) do
    if (sX[i] = '.') or (sX[i] = ',') then sX[i] := DecimalSeparator;
  TextOfNumberX.Text := sX;
  try
    X := StrToFloat(sX); Z := sX;
    case Mode of
    1 : TextOfNumberY.Clear;
    2 : begin
          sY := Trim(TextOfNumberY.Text);
          for i := 1 to Length(sY) do
            if sY[i] = '.' then sY[i] := DecimalSeparator;
          Y := StrToFloat(sY);
          TextOfNumberY.Text := sY;
        end;
    end;
    CheckUserData := TRUE;
  except
    CheckUserData := FALSE;
  end;
end;

procedure nul(var a:chislo);
var i:integer;
begin
for i:=1 to nmax do
a[i]:=0;
end;
procedure perevod(s:string;var a:chislo);
var i,n :1..nmax;
begin
n:=length(s);
nul(a);
for i:=1 to n do
a[n-i+1]:=ord(s[i])-ord('0');
end;
function kol(const a: chislo):integer;
var i:1..nmax;
begin
i:=nmax;
while(a[i]=0)and(i>1) do
i:=i-1;
kol:=i;
end;

procedure umn(var a,b,c:chislo);
var i,g,n,m:1..nmax; p:0..9; v:byte;
begin
nul(c);
m:=kol(a);
n:=kol(b);
for i:=1 to m do
begin
p:=0;
for g:=1 to n do
begin
v:=a[i]*b[g]+p+c[i+g-1];
c[i+g-1]:=v mod 10;
p:=v div 10;
end;
c[i+n]:=p;
end;
end;

procedure sum(a,b:chislo;var c:chislo);
var i,j,r:longint; p:0..9;
begin
p:=0;
for j:=1 to kol(a) do
begin
r:=b[j]+a[j]+p;
p:=r div 10;
c[j]:=r mod 10;
end;
c[j+1]:=p;
end;

procedure TCalculator.factorial_xClick(Sender: TObject);//факториал X
var i,n,f,l: integer; s,k:string; a,b,c,d,q:chislo;
begin
if CheckUserData(1) then begin
    n := trunc(x);//округление дробного числа
     nul(b);
b[1]:=1;
nul(c);
nul(a);
a[1]:=1;
c[1]:=1;
d[1]:=1;
for i:=2 to n do
begin
for f:=1 to nmax do
a[f]:=c[f];
sum(a,d,c);
umn(b,c,q);
for f:=1 to nmax do
b[f]:=q[f];
end;
    for i:=kol(q) downto 1 do
    TextOfResult.Text:=TextOfResult.Text + inttostr(q[i]);
TextOfOperations.text:=TextOfOperations.text+'факториал '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;

// Ввод чисел X
procedure TCalculator.Pi_xClick(Sender: TObject);
begin
TextOfNumberX.text:= '3.14';
end;
procedure TCalculator.pointXClick(Sender: TObject);
begin
    TextOfNumberX.text:= TextOfNumberX.text+'.';
end;
procedure TCalculator.x0Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'0';end; end;
procedure TCalculator.x1Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'1';end; end;
procedure TCalculator.x2Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'2';end; end;
procedure TCalculator.x3Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'3';end; end;
procedure TCalculator.x4Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'4';end; end;
procedure TCalculator.x5Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'5';end; end;
procedure TCalculator.x6Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'6';end; end;
procedure TCalculator.x7Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'7';end; end;
procedure TCalculator.x8Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'8';end; end;
procedure TCalculator.x9Click(Sender: TObject);
begin
  if TextOfResult.text<>'' then begin TextOfNumberX.text:='';end;
  begin TextOfResult.text:='';TextOfNumberX.text:=TextOfNumberX.text+'9';end; end;
procedure TCalculator.xPlusMinusClick(Sender: TObject);//изменение знака числа X
var i: real;
begin
if CheckUserData(1) then begin
i:=-x;
TextOfNumberX.text:= floattostr(i);
end
else showmessage('Введите корректные данные');
end;
// Ввод чисел Y
procedure TCalculator.Pi_yClick(Sender: TObject);
begin
TextOfNumberY.text:= '3.14';
end;
procedure TCalculator.pointYClick(Sender: TObject);
begin
TextOfNumberY.text:= TextOfNumberY.text+'.';
end;
procedure TCalculator.y0Click(Sender: TObject);
begin   Clear_y.enableD:=true;
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'0';end; end;
procedure TCalculator.y1Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'1';end; end;
procedure TCalculator.y2Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'2';end; end;
procedure TCalculator.y3Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'3';end; end;
procedure TCalculator.y4Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'4';end; end;
procedure TCalculator.y5Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'5';end; end;
procedure TCalculator.y6Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'6';end; end;
procedure TCalculator.y7Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'7';end; end;
procedure TCalculator.y8Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'8';end; end;
procedure TCalculator.y9Click(Sender: TObject);
begin
if TextOfResult.text='' then begin TextOfNumberY.text:='';end;
begin TextOfResult.text:=' ';TextOfNumberY.text:=TextOfNumberY.text+'9';end; end;
procedure TCalculator.YPlusMinusClick(Sender: TObject);//изменение знака числа Y
var i: real;
begin
if CheckUserData(2) then begin
i:=-y;
TextOfNumberY.text:= floattostr(i);
end
else showmessage('Введите корректные данные');
end;
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
procedure TCalculator.ClearOperationsFieldClick(Sender: TObject);//очистка списка операций
begin
TextOfOperations.text:='';
end;
procedure TCalculator.ClearAllFieldsClick(Sender: TObject);//очистка всех полей
begin
TextOfNumberX.text:='';
TextOfNumberY.text:='';
TextOfResult.text:='';
TextOfOperations.text:='';
end;
procedure TCalculator.CopyResultClick(Sender: TObject);//копировать результат
begin
Clipboard.AsText:=TextOfResult.text;
end;
procedure TCalculator.Clear_xClick(Sender: TObject);//очистка значения X
begin
TextOfNumberX.text:='';
end;
procedure TCalculator.Clear_yClick(Sender: TObject);//очистка значения Y
begin
TextOfNumberY.text:='';
 Clear_y.enableD:=false;
end;
procedure TCalculator.PasteResultToXClick(Sender: TObject);//результат в поле X
begin
TextOfNumberX.text:='';
TextOfNumberX.text:= TextOfResult.text;TextOfResult.text:='';
end;
procedure TCalculator.PasteResultToYClick(Sender: TObject);//результат в поле Y
begin
TextOfNumberY.text:='';
TextOfNumberY.text:= TextOfResult.text;
end;
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
procedure TCalculator.XplusYClick(Sender: TObject); // операция сложения
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= floattostr(x+y);
    TextOfOperations.text:=TextOfOperations.text+(FloatToStr(x))+'+'+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
    end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.XminusYClick(Sender: TObject);//операция вычитания
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= FloatToStr(X - Y);
    TextOfOperations.text:=TextOfOperations.text+(FloatToStr(x))+'-'+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.XmultiplyYClick(Sender: TObject);//операция умножения
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= FloatToStr(X * Y);
    TextOfOperations.text:=TextOfOperations.text+(FloatToStr(x))+'*'+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.XdivideYClick(Sender: TObject);//операция деления
begin
if CheckUserData(2) then begin
    if y=0 then begin showmessage('Нельзя делить на ноль!'); exit; end else
    TextOfResult.Text:= FloatToStr(X / Y);
    TextOfOperations.text:=TextOfOperations.text+(FloatToStr(x))+'/'+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
procedure TCalculator.X_stepen_YClick(Sender: TObject);//X в степени Y
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= floattostr(Power(X, Y));
    TextOfOperations.text:=TextOfOperations.text+(FloatToStr(x))+' '+'в степени '+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end;
end;
procedure TCalculator.squrt_XClick(Sender: TObject);//квадратный корень  из x
begin
if CheckUserData(1) then begin
    TextOfResult.Text:= FloatToStr(sqrt(X));
    TextOfOperations.text:=TextOfOperations.text+'квадратный корень из '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.korenX_stepenYClick(Sender: TObject);//корень из X степени Y
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= FloatToStr(exp(1/y * ln(X)));
    TextOfOperations.text:=TextOfOperations.text+'корень из '+(FloatToStr(x))+' '+'степени '+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;



{------------------------------------------------------------------------------}
{------------------------------------------------------------------------------}
procedure TCalculator.sin_xClick(Sender: TObject);//sin (x)
begin
if CheckUserData(1) then begin
    TextOfResult.Text:= FloatToStr(sin(RadianToGradus(X)));
    TextOfOperations.text:=TextOfOperations.text+'sin '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;

procedure TCalculator.tg_xClick(Sender: TObject);//tg (x)
begin
if CheckUserData(1) then begin
    TextOfResult.Text:= FloatToStr(tan(RadianToGradus(X)));
    TextOfOperations.text:=TextOfOperations.text+'tg '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.cos_xClick(Sender: TObject);//cos(x)
begin
if CheckUserData(1) then begin
if (frac(strtofloat(TextOfNumberX.Text))=0 )then begin
    if (trunc(strtofloat(TextOfNumberX.Text))=0)  then begin TextOfResult.Text:='1'; exit; end;
    if (trunc(strtofloat(TextOfNumberX.Text))=90) then begin TextOfResult.Text:='0';exit end;
    if (trunc(strtofloat(TextOfNumberX.Text))=180) then begin TextOfResult.Text:='-1';exit end;
    TextOfResult.Text:= FloatToStr(cos(RadianToGradus(X)));
    TextOfOperations.text:=TextOfOperations.text+'cos '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.ctg_xClick(Sender: TObject);//ctg(x)
begin
if CheckUserData(1) then begin
    TextOfResult.Text:= FloatToStr(cos(RadianToGradus(X))/sin(RadianToGradus(X)));
    TextOfOperations.text:=TextOfOperations.text+'ctg '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;
procedure TCalculator.ln_x1Click(Sender: TObject);//ln(x)
begin
if CheckUserData(1) then begin
    TextOfResult.Text:= FloatToStr(ln(x));
    TextOfOperations.text:=TextOfOperations.text+'ln '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;

procedure TCalculator.logY_XClick(Sender: TObject);//log(x) по основанию Y
begin
if CheckUserData(2) then begin
    TextOfResult.Text:= FloatToStr(logN(y, x));
    TextOfOperations.text:=TextOfOperations.text+'log '+(FloatToStr(x))+' '+'по основанию '+(FloatToStr(y))+'='+(TextOfResult.Text)+'; ';
end
else showmessage('Введите корректные данные');
end;

procedure TCalculator.PercentageClick(Sender: TObject);//процент Y от числа X
var a:real;
begin
if CheckUserData(2) then begin
a:= x*y/100;
TextOfresult.Text:= FloatToStr(a);
TextOfNumberY.text:='';
TextOfNumberY.text:= TextOfResult.text;
TextOfOperations.text:=TextOfOperations.text+(FloatToStr(y))+'% '+'числа '+(FloatToStr(x))+'='+(TextOfResult.Text)+'; ';
end;
end;

end.

