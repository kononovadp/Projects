unit Unit1;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, FileUtil, Forms, Controls, Graphics, Dialogs, StdCtrls,
  Buttons, ExtCtrls, Grids, MaskEdit;

type

  { TForm1 }

  TForm1 = class(TForm)
    b0: TButton;
    b1: TButton;
    b10: TButton;
    b11: TButton;
    b12: TButton;
    b13: TButton;
    b14: TButton;
    b15: TButton;
    b16: TButton;
    b17: TButton;
    b18: TButton;
    b19: TButton;
    b2: TButton;
    b20: TButton;
    b21: TButton;
    b22: TButton;
    b27: TButton;
    b28: TButton;
    b29: TButton;
    b30: TButton;
    b31: TButton;
    b23: TButton;
    b24: TButton;
    b3: TButton;
    b25: TButton;
    b26: TButton;
    b32: TButton;
    b4: TButton;
    b5: TButton;
    b6: TButton;
    b7: TButton;
    b8: TButton;
    b9: TButton;
    abs: TButton;
    b33: TButton;
    B34: TButton;
    B35: TButton;
    bracket1: TButton;
    bracket2: TButton;
    Clearall: TButton;
    Convop1: TButton;
    clear_op: TButton;
    clear_j: TButton;
    ae: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    system2: TComboBox;
    Label1: TLabel;
    system1: TComboBox;
    divprec: TEdit;
    from: TLabel;
    Memo: TMemo;
    ns16: TButton;
    ns10: TButton;
    ns8: TButton;
    ns2: TButton;
    point: TButton;
    b_plus: TButton;
    b_minus: TButton;
    b_mult: TButton;
    b_divide: TButton;
    res: TButton;
    e3: TEdit;
    ns: TComboBox;
    procedure b0Click(Sender: TObject);
    procedure b10Click(Sender: TObject);
    procedure b11Click(Sender: TObject);
    procedure b12Click(Sender: TObject);
    procedure b13Click(Sender: TObject);
    procedure b14Click(Sender: TObject);
    procedure b15Click(Sender: TObject);
    procedure b16Click(Sender: TObject);
    procedure b17Click(Sender: TObject);
    procedure b18Click(Sender: TObject);
    procedure b19Click(Sender: TObject);
    procedure b1Click(Sender: TObject);
    procedure b20Click(Sender: TObject);
    procedure b21Click(Sender: TObject);
    procedure b22Click(Sender: TObject);
    procedure b27Click(Sender: TObject);
    procedure b28Click(Sender: TObject);
    procedure b29Click(Sender: TObject);
    procedure b30Click(Sender: TObject);
    procedure b31Click(Sender: TObject);
    procedure b23Click(Sender: TObject);
    procedure b24Click(Sender: TObject);
    procedure b2Click(Sender: TObject);
    procedure b25Click(Sender: TObject);
    procedure b26Click(Sender: TObject);
    procedure b32Click(Sender: TObject);
    procedure b33Click(Sender: TObject);
    procedure B34Click(Sender: TObject);
    procedure B35Click(Sender: TObject);
    procedure b3Click(Sender: TObject);
    procedure b4Click(Sender: TObject);
    procedure b5Click(Sender: TObject);
    procedure b6Click(Sender: TObject);
    procedure b7Click(Sender: TObject);
    procedure b8Click(Sender: TObject);
    procedure b9Click(Sender: TObject);
    procedure absClick(Sender: TObject);
    procedure bracket1Click(Sender: TObject);
    procedure bracket2Click(Sender: TObject);
    procedure ClearallClick(Sender: TObject);
    procedure clear_jClick(Sender: TObject);
    procedure clear_opClick(Sender: TObject);
    procedure b_divideClick(Sender: TObject);
    procedure Convop1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure b_minusClick(Sender: TObject);
    procedure b_multClick(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
    procedure ns10Click(Sender: TObject);
    procedure ns16Click(Sender: TObject);
    procedure ns2Click(Sender: TObject);
    procedure ns8Click(Sender: TObject);
    procedure nsChange(Sender: TObject);
    procedure b_plusClick(Sender: TObject);
    procedure pointClick(Sender: TObject);
    procedure resClick(Sender: TObject);
    procedure buttonenable(n:byte);
    procedure system1Change(Sender: TObject);
  private
    { private declarations }
  public
    { public declarations }
  end;
var
Form1: TForm1;
var s,t1:string;
c:char; pr,i:byte; set1:set of char; b:boolean;

s1,s2{исходные строки},od{остаток от деления},
se1,se2{выровненные строки}:string;
sys{система счисления},sys1,sys2,
prec{точность деления}:byte;
z1,z2{позиции запятых}:integer;
op_plusb,op_minusb:boolean;
implementation
{$R *.lfm}
//преобразование цифры в символ
function ntoch(i:byte):string;
begin
if i>9 then begin i:=i+55; ntoch:=chr(i); end
else ntoch:=inttostr(i); end;
//преобразование символа в цифру
function chton(ch:char):byte;
var set1:set of char; i:byte;
begin set1:=[];
for i:=48 to 57 do
set1:=set1+[chr(i)];
if ch in set1 then chton:= strtoint(ch)
else chton:=ord(ch)-55; end;
//выравнивание чисел с запятой
function normalize(var s1,s2:string):byte;
var i:byte;
begin
z1:=pos('.',s1); z2:=pos('.',s2);
if z1=0 then z1:=length(s1)+1;
if z2=0 then z2:=length(s2)+1;
if z1>z2 then normalize:=z1 else normalize:=z2;
if z1>z2 then for i:=0 to z1-z2 do s2:='0'+s2
else if z1<z2 then for i:=0 to z2-z1 do s1:='0'+s1;
if pos('.',s1)>0 then z1:=length(s1)-pos('.',s1) else z1:=0;
if pos('.',s2)>0 then z2:=length(s2)-pos('.',s2) else z2:=0;
if z1>z2 then for i:=1 to z1-z2 do s2:=s2+'0'
else if z1<z2 then for i:=1 to z2-z1 do s1:=s1+'0';
if pos('.',s1)>0 then delete(s1,pos('.',s1),1);
if pos('.',s2)>0 then delete(s2,pos('.',s2),1); end;
//выравнивание чисел без запятой
function eqsize(var s1,s2:string):string;
var i:byte;
begin
if length(s1)<length(s2) then
for i:=1 to length(s2)-length(s1) do s1:='0'+s1;
if length(s1)>length(s2) then
for i:=1 to length(s1)-length(s2) do s2:='0'+s2;
se1:=s1; se2:=s2; eqsize:=''; end;
//удаление ноля в начале строки
function zerodelb(s:string):string;
var i:integer;
begin i:=1;
while s[i]='0' do inc(i);
delete(s,1,i-1);
if length(s)=0 then s:='0';
zerodelb:=s; end;
//удаление ноля в конце строки
function zerodele(s:string):string;
var i:integer;
begin i:=length(s){-1};
while s[i]='0' do dec(i);
delete(s,i+1,length(s)-i);
if length(s)=0 then s:='0';
zerodele:=s; end;
//сравнение чисел
function compare(s1,s2:string):char;
var i:byte;
begin
if s1=s2 then compare:='=' else begin
normalize(s1,s2); i:=1;
while s1[i]=s2[i] do inc(i);
if ord(s1[i])<ord(s2[i]) then compare:='<' else compare:='>';
end; end;
//проверка соответствия числа указанной системе счисления
function check(s:string):string;
var i:byte; set1:set of char;
begin
if sys>36 then begin check:='!!!'; exit; end;
set1:=set1+['.']+['-'];
for i:=48 to 48+sys-1 do
set1:=set1+[chr(i)];
if sys>9 then
for i:=65 to 65+sys-10-1 do
set1:=set1+[chr(i)];
for i:=1 to length(s) do
if not(s[i] in set1) then begin check:='!!!'; break; exit; end
else check:=''; end;
//обработка знака при умножении и делении
function sign(var s1,s2:string):boolean;
begin
if (s1[1]='-') and (s2[1]='-') then begin
sign:=false; delete(s1,1,1); delete(s2,1,1); exit; end;
if (s1[1]='-') and (s2[1]<>'-') then begin
sign:=true; delete(s1,1,1); exit; end;
if (s1[1]<>'-') and (s2[1]='-') then begin
sign:=true; delete(s2,1,1); exit; end; end;
//сложение чисел без знака
function op_plus(s1,s2:string):string;
var e:string; c,d,i,r:byte; p,q,cp: byte;
begin r:=0; e:=''; cp:=0;
if op_plusb=false then
if (pos('.',s1)>0) or (pos('.',s2)>0) then
cp:=normalize(s1,s2);
if length(s1)<>length(s2) then eqsize(s1,s2);
p:=length(s1); q:=length(s2); i:=0; r:=0;
while (p>0) and (q>0) do begin
c:=chton(s1[p]); dec(p);
d:=chton(s2[q]); dec(q); r:=c+d+i;
if r>sys-1 then begin r:=r-sys; i:=1 end else i:=0;
e:=ntoch(r)+e; end; if i=1 then e:='1'+e;
{if cp=0 then} e:=zerodelb(e);
if op_plusb=false then
if cp>0 then insert('.',e,cp);
if pos('.',e)=length(e) then delete(e,pos('.',e),1);
if pos('.',e)=0 then op_plus:=zerodelb(e) else begin
e:=zerodele(e); e:=zerodelb(e);
if pos('.',e)=length(e) then delete(e,length(e),1); end;
op_plus:=e; end;
//отнимание чисел без знака
function op_minus(s1,s2:string):string;
var s,t:string; n,k,p,i,r:integer;
cp:byte; ms:boolean;
begin ms:=false; cp:=0;
if op_minusb=false then
if compare(s1,s2)='<' then begin
t:=s1; s1:=s2; s2:=t; ms:=true; end;
if pos('.',s1) or pos('.',s2)>0 then begin
if pos('.',s1)>0 then z1:=length(s1)-pos('.',s1) else z1:=0;
if pos('.',s2)>0 then z2:=length(s2)-pos('.',s2) else z2:=0;
if z1>=z2 then cp:=z1 else cp:=z2; normalize(s1,s2); end;
if length(s1)<>length(s2) then eqsize(s1,s2);
n:=length(s1); r:=0; i:=0;
while (n>0) do begin
k:=chton(s1[n])-i; p:=chton(s2[n]); dec(n);
if k=-1 then k:=sys-1 else
if k<p then begin k:=k+sys; i:=1; end
else  i:=0; r:=k-p;
s:=ntoch(r)+s; end;
if (pos('0',s)=1) and (cp=0) then s:=zerodelb(s);
if op_minusb=false then
if cp>0 then insert('.',s,length(s)-cp+1);
if pos('.',s)=length(s) then delete(s,pos('.',s),1);
if (s[1]='0') and (pos('.',s)>2) then s:=zerodelb(s);
if (ms=true) and (op_minusb=false) then s:='-'+s;
op_minus:=s; end;
//сложение со знаком
function plus(s1,s2:string):string;
begin //writeln(s1,'+++',s2);
if (check(s1)<>'') or (check(s2)<>'') then begin
plus:='Incorrect data!!!'; exit; end; plus:='';
if (s1[1]='-') and (s2[1]='-') then begin
delete(s1,1,1); delete(s2,1,1);
plus:=op_plus(s1,s2); plus:='-'+plus; end else
if (s1[1]='-') and (s2[1]<>'-') then begin
delete(s1,1,1); plus:=op_minus(s2,s1); end else
if (s1[1]<>'-') and (s2[1]='-') then begin
delete(s2,1,1); plus:=op_minus(s1,s2) end
else plus:=op_plus(s1,s2); end;
//вычитание со знаком
function minus(s1,s2:string):string;
begin
if (check(s1)<>'') or (check(s2)<>'') then begin
minus:='Incorrect data!!!'; exit; end; minus:='';
if (s1[1]='-') and (s2[1]='-') then begin
delete(s1,1,1); delete(s2,1,1);
minus:=op_minus(s2,s1); end else
if (s1[1]='-') and (s2[1]<>'-') then begin
delete(s1,1,1); minus:=op_plus(s1,s2);
minus:='-'+minus; end else
if (s1[1]<>'-') and (s2[1]='-') then begin
delete(s2,1,1); minus:=op_plus(s1,s2) end
else minus:=op_minus(s1,s2); end;
//умножение
function mult(s1,s2:string):string;
var e,p,p2:string;
    i,j,l1,i1,j1,a,b,r,c,d,n,n1:byte;
    ms:boolean;
begin  if (check(s1)<>'') or (check(s2)<>'') then
begin mult:='Incorrect data!!!'; exit; end;
op_plusb:=true; n1:=0; z1:=0; z2:=0; ms:=false;
if (s1[1]='-') or (s2[1]='-') then ms:=sign(s1,s2);
if (pos('.',s1)>0) or (pos('.',s2)>0) then begin
if pos('.',s1)>0 then z1:=length(s1)-pos('.',s1);
if pos('.',s2)>0 then z2:=length(s2)-pos('.',s2);
n1:=z1+z2;
if pos('.',s1)>0 then delete(s1,pos('.',s1),1);
if pos('.',s2)>0 then delete(s2,pos('.',s2),1);
if s1[1]='0' then s1:=zerodelb(s1);
if s2[1]='0' then s2:=zerodelb(s2); end;
if length(s1)<>length(s2) then eqsize(s1,s2);
n:=length(s1); r:=0; i:=0;
l1:=length(s2); p2:='0'; i1:=0;
while l1<>0 do begin
b:=chton(s2[l1]); dec(l1);
n:=length(s1); p:='0'; i:=0;
while n>0 do begin
a:=chton(s1[n]); dec(n);
r:=a*b; c:=r div sys; d:=r-(c*sys);
e:=ntoch(c)+ntoch(d); inc(i);
if i>0 then
for j:=1 to i-1 do e:=e+'0'; p:=op_plus(p,e);
end; inc(i1); if i1>0 then for j1:=1 to i1-1 do
p:=p+'0'; p2:=op_plus(p2,p); end;
if (n1>=length(p2)) then for i:=0 to n1-length(p2) do p2:='0'+p2;
if n1>0 then insert('.',p2,length(p2)-n1+1);
if (pos('.',p2)>0) and (p2[length(p2)]='0') then p2:=zerodele(p2);
if pos('.',p2)=length(p2) then delete(p2,length(p2),1);
if ms=true then p2:='-'+p2;
mult:=p2; end;
//преобразование числа из 10-й в любую систему счисления
{function sysconvert(n:int64):string;
var c:integer; sr:string;
begin  sr:='';
while n>0 do begin
  c:=n mod sys;
  n:=n div sys;
  sr:=ntoch(c)+sr;end;
sysconvert:=sr; end;
//деление без остатка
function dividewr(s1,s2:string):string;
var r:int64;
begin r:=0;
while (compare(s1,s2)='>' ) or (compare(s1,s2)='=') do begin
s1:=op_minus(s1,s2); inc(r); end;
od:=s1; dividewr:=sysconvert(r);
if dividewr='' then dividewr:='0'; end; }
//деление без остатка
function dividewr(s1,s2:string):string;
var r:string;
begin r:='0';
while (compare(s1,s2)='>' ) or (compare(s1,s2)='=') do begin
s1:=op_minus(s1,s2);  r:=op_plus(r,'1');
end; od:=s1; od:=s1; dividewr:=r;
if dividewr='' then dividewr:='0'; end;

function edivide(s1,s2:string):string;
var o,r,t:string; i:byte;
begin
if (s1='0') or (s2='0') then begin
edivide:='0'; exit; end; i:=1;
while (compare(o,s2)<>'>') and (compare(o,s2)<>'=')
and (i<length(s1)) do begin
o:=o+s1[i]; inc(i); end;
if length(s1)<>length(s2) then begin
i:=1; o:=s1[1];
while i<length(s1)+1 do begin
t:=dividewr(o,s2);  r:=r+t; t:=mult(r[length(r)],s2);
o:=minus(o,t); if o='0' then o:='';
inc(i); o:=o+s1[i]; end; end else r:=dividewr(s1,s2);
if r[1]='0' then r:=zerodelb(r);
delete(o,length(o),1);
edivide:=(r); end;

//деление с остатком
function divide(s1,s2:string):string;
var x,r,dp:string; ds:boolean; i,pc:integer;
begin
if (check(s1)<>'') or (check(s2)<>'') then
begin divide:='Incorrect data!!!'; exit; end;
z1:=0; z2:=0; op_minusb:=true; ds:=false;
if (s1[1]='-') or (s2[1]='-') then
ds:=sign(s1,s2);
if (pos('.',s1)>0) or (pos('.',s2)>0) then begin
if pos('.',s1)>0 then z1:=length(s1)-pos('.',s1);
if pos('.',s2)>0 then z2:=length(s2)-pos('.',s2);
if z1>z2 then pc:=z1 else pc:=z2; z1:=0; z2:=0;
dp:='1'; for i:=1 to pc do dp:=dp+'0';
s1:=mult(s1,dp); s2:=mult(s2,dp); end;
x:=edivide(s1,s2);  x:=x+'.';  od:=od+'0';
if od<>'0' then
while (prec>0) and (od<>'00') do begin
r:={dividewr}edivide(od,s2); x:=x+r;
od:=od+'0'; dec(prec); end; od:='';
if pos('.',x)=length(x) then delete(x,pos('.',x),1);
if ds=true then x:='-'+x;
if pos('.',x)=0 then divide:=x else divide:=zerodele(x); end;

function power(s,p:string):string;
var i:byte; t:string; b:boolean;
begin b:=false;
if p[1]='-' then begin delete(p,1,1); b:=true; end;
t:='1'; for i:=1 to strtoint(p) do t:=mult(s,t);
if b=true then t:=divide('1',t); power:=t; end;

function convertfromdec(s:string):string;
var c,r,fs,sc,t,r1,fp,ip:string; nst:byte;
b:boolean; t1,pt:integer;
begin sys:=10; pt:=prec; b:=false; od:='0'; r:=''; t:=''; t1:=0; fs:='';
if pos('.',s)=0 then fs:=s else if pos('.',s)>0 then begin
b:=true; fs:=copy(s,1,pos('.',s)-1);
delete(s,1,length(fs)); s:='0'+s; end;
//edivide(fs,inttostr(sys2)); od:=r+od;
while (prec>0) and (fs<>'0') do begin
fs:=edivide(fs,inttostr(sys2));
if od='' then od:='0';
t1:=strtoint(od); r:=ntoch(t1)+r; dec(prec); end;
r1:=r; r:=''; if b=true then begin prec:=pt;
while (prec>0) {and (fp<>'0')} do begin
t:=copy(s,1,pos('.',s)-1);
s:=mult(s,inttostr(sys2));
if pos('.',s)=0 then ip:=s else ip:=copy(s,1,pos('.',s)-1);
pt:=strtoint(ip); ip:=ntoch(pt); r:=r+ip;
if pos('.',s)=0 then fp:='0';
if ip<>t then begin delete(s,1,pos('.',s)-1); s:='0'+s; end;
dec(prec); end; end;
if r<>'' then r1:=r1+'.'+r; convertfromdec:=r1; end;

function numberconvert(s:string):string;
var i,k,n,pr,nst:integer; c:char; r1,ds,t1:string; b:boolean;
begin sys:=sys1;  nst:=sys1;
if (check(s)<>'') then begin
numberconvert:='Incorrect number'; exit; end;
r1:='1'; sys:=10; ds:='';  b:=true;
if pos('.',s)>0 then begin
ds:=copy(s,pos('.',s)+1,length(s)-pos('.',s));
delete(s,pos('.',s),length(s)-pos('.',s)+1); end;
k:= length(s)-1; i:=1; t1:='0';
while k>-1 do begin
r1:=power(inttostr(sys1),inttostr(k));
c:=s[length(s)-k]; n:=chton(c);
r1:=mult(inttostr(n),r1);
t1:=plus(r1,t1);  dec(k); end;
if ds<>'' then begin
k:=-length(ds); i:=0;
for i:=1 to length(ds) do begin pr:=prec;
r1:=power(inttostr(sys1),inttostr(-i));
c:=ds[i]; n:=chton(c); prec:=pr;
r1:=mult(inttostr(n),r1); op_plusb:=false;
t1:=plus(r1,t1); end; end;
if sys2<>10 then begin sys1:=10; t1:=convertfromdec(t1); end;
numberconvert:=t1; sys1:=nst; end;

function strprocwb({var }s:string):string;
//var s1,s2:string; c:char; pr,i:byte;
//set1:set of char; b:boolean;
begin b:=false; pr:=prec;  s1:='';
for i:=1 to length(s) do begin
if s[i]='(' then delete(s,i,1);
if s[i]=')' then delete(s,i,1); end;
set1:=set1+['.'];
for i:=48 to 48+sys-1 do
set1:=set1+[chr(i)];
if sys>9 then
for i:=65 to 65+sys-10-1 do
set1:=set1+[chr(i)]; i:=1;
if s[1]='-' then begin delete(s,1,1); b:=true; end;
while s[i] in set1 do begin s1:=s1+s[i]; inc(i); end;
delete(s,1,length(s1));
if b=true then s1:='-'+s1;
while s<>'' do begin b:=false; i:=1;
prec:=pr; op_plusb:=false; op_minusb:=false; s2:='';
c:=s[1]; delete(s,1,1);
if s[1]='-' then begin delete(s,1,1); b:=true; end;
while s[i] in set1 do begin s2:=s2+s[i]; inc(i); end;
delete(s,1,length(s2));
if b=true then s2:='-'+s2;
case c of
'+': s1:=plus(s1,s2); '-': s1:=minus(s1,s2);
'*': s1:=mult(s1,s2); '/': s1:=divide(s1,s2); end;
end; strprocwb:=s1; end;

function strproc(s:string):string;
var r,t1,t2:string; p,i:byte; b:boolean;
begin
while s<>'' do begin t2:=''; i:=1;
if pos('(',s)>0 then begin
p:=pos('(',s); t1:=copy(s,1,p-1); delete(s,1,p);
p:=pos(')',s); t2:=copy(s,1,p-1); delete(s,1,p);
for i:=1 to length(t2) do begin
if t2[i]='(' then delete(t2,i,1);
if t2[i]=')' then delete(t2,i,1); end;
t2:=strprocwb(t2); end else begin t1:=s; s:=''; end;
r:=r+t1+t2;  end;
strproc:=strprocwb(r); end;

function strprocconv(s:string):string;
var i,pr:byte; c,t1,r:string;
begin pr:=prec;
set1:=set1+['.'];
for i:=48 to 57 do
set1:=set1+[chr(i)];
for i:=65 to 90 do
set1:=set1+[chr(i)];
if not(s[length(s)] in set1) then begin
c:=s[length(s)]; delete(s,length(s),1); end;
while s<>'' do begin i:=1; s2:=''; t1:='';
op_plusb:=false;  op_minusb:=false; prec:=pr;
while not(s[i] in set1) do begin
t1:=t1+s[i]; inc(i); end;
delete(s,1,length(t1)); i:=1; r:=r+t1;
while s[i] in set1 do begin
s2:=s2+s[i]; inc(i); end;
delete(s,1,length(s2));
s2:=numberconvert(s2);  r:=r+s2; end;
r:=r+c; strprocconv:=r; end;
//====================================кнопки====================================
procedure TForm1.b0Click(Sender: TObject);
begin
ae.text:=ae.text+'0'; end;
procedure TForm1.b1Click(Sender: TObject);
begin
ae.text:=ae.text+'1'; end;
procedure TForm1.b2Click(Sender: TObject);
begin
ae.text:=ae.text+'2'; end;
procedure TForm1.b3Click(Sender: TObject);
begin
ae.text:=ae.text+'3'; end;
procedure TForm1.b4Click(Sender: TObject);
begin
ae.text:=ae.text+'4'; end;
procedure TForm1.b5Click(Sender: TObject);
begin
ae.text:=ae.text+'5'; end;
procedure TForm1.b6Click(Sender: TObject);
begin
ae.text:=ae.text+'6'; end;
procedure TForm1.b7Click(Sender: TObject);
begin
ae.text:=ae.text+'7'; end;
procedure TForm1.b8Click(Sender: TObject);
begin
ae.text:=ae.text+'8'; end;
procedure TForm1.b9Click(Sender: TObject);
begin
ae.text:=ae.text+'9'; end;
procedure TForm1.b10Click(Sender: TObject);
begin
ae.text:=ae.text+'A'; end;
procedure TForm1.b11Click(Sender: TObject);
begin
ae.text:=ae.text+'B'; end;
procedure TForm1.b12Click(Sender: TObject);
begin
ae.text:=ae.text+'C'; end;
procedure TForm1.b13Click(Sender: TObject);
begin
ae.text:=ae.text+'D'; end;
procedure TForm1.b14Click(Sender: TObject);
begin
ae.text:=ae.text+'E'; end;
procedure TForm1.b15Click(Sender: TObject);
begin
ae.text:=ae.text+'F'; end;
procedure TForm1.b16Click(Sender: TObject);
begin
ae.text:=ae.text+'G'; end;
procedure TForm1.b17Click(Sender: TObject);
begin
ae.text:=ae.text+'H'; end;
procedure TForm1.b18Click(Sender: TObject);
begin
ae.text:=ae.text+'I'; end;
procedure TForm1.b19Click(Sender: TObject);
begin
ae.text:=ae.text+'J'; end;
procedure TForm1.b20Click(Sender: TObject);
begin
ae.text:=ae.text+'K'; end;
procedure TForm1.b21Click(Sender: TObject);
begin
ae.text:=ae.text+'L'; end;
procedure TForm1.b22Click(Sender: TObject);
begin
ae.text:=ae.text+'M'; end;
procedure TForm1.b23Click(Sender: TObject);
begin
ae.text:=ae.text+'N'; end;
procedure TForm1.b24Click(Sender: TObject);
begin
ae.text:=ae.text+'O'; end;
procedure TForm1.b25Click(Sender: TObject);
begin
ae.text:=ae.text+'P'; end;
procedure TForm1.b26Click(Sender: TObject);
begin
ae.text:=ae.text+'Q'; end;
procedure TForm1.b27Click(Sender: TObject);
begin
ae.text:=ae.text+'R'; end;
procedure TForm1.b28Click(Sender: TObject);
begin
ae.text:=ae.text+'S'; end;
procedure TForm1.b29Click(Sender: TObject);
begin
ae.text:=ae.text+'T'; end;
procedure TForm1.b30Click(Sender: TObject);
begin
ae.text:=ae.text+'U'; end;
procedure TForm1.b31Click(Sender: TObject);
begin
ae.text:=ae.text+'V'; end;
procedure TForm1.b32Click(Sender: TObject);
begin
ae.text:=ae.text+'W'; end;
procedure TForm1.b33Click(Sender: TObject);
begin
ae.text:=ae.text+'X'; end;
procedure TForm1.B34Click(Sender: TObject);
begin
ae.text:=ae.text+'Y'; end;
procedure TForm1.B35Click(Sender: TObject);
begin
ae.text:=ae.text+'Z'; end;
procedure TForm1.pointClick(Sender: TObject);
begin
ae.text:=ae.text+'.'; end;
procedure TForm1.absClick(Sender: TObject);
begin
ae.text:=ae.text+'-'; end;
procedure TForm1.bracket1Click(Sender: TObject);
begin
ae.text:=ae.text+'('; end;
procedure TForm1.bracket2Click(Sender: TObject);
begin
ae.text:=ae.text+')'; end;

procedure TForm1.ClearallClick(Sender: TObject);
begin
ae.text:=''; e3.text:='';
memo.Text:=''; end;
procedure TForm1.clear_jClick(Sender: TObject);
begin memo.Text:=''; end;
procedure TForm1.clear_opClick(Sender: TObject);
begin ae.text:='';
e3.text:=''; end;
procedure TForm1.resClick(Sender: TObject);
var s:string;
begin if ae.text<>'' then begin
op_plusb:=false;  op_minusb:=false; s:=ae.text;
sys:=strtoint(ns.text); prec:=strtoint(divprec.text);
e3.text:=strproc(s);
memo.text:=memo.text+ae.text+'='+e3.text+' ('+ns.text+')'+'; '+#13;
end else showmessage('Enter operands!'); end;
//--------------------------------------------------------------
procedure TForm1.b_plusClick(Sender: TObject);
begin ae.text:=ae.text+'+'; end;
procedure TForm1.b_minusClick(Sender: TObject);
begin ae.text:=ae.text+'-'; end;
procedure TForm1.b_multClick(Sender: TObject);
begin ae.text:=ae.text+'*'; end;
procedure TForm1.b_divideClick(Sender: TObject);
begin ae.text:=ae.text+'/'; end;
procedure TForm1.FormKeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
var s:string;
begin
if (Key=13) then if ae.text<>'' then begin
op_plusb:=false;  op_minusb:=false; s:=ae.text;
sys:=strtoint(ns.text); prec:=strtoint(divprec.text);
e3.text:=strproc(s);
memo.text:=memo.text+ae.text+'='+e3.text+' ('+ns.text+')'+'; ';
end else showmessage('Enter operands!'); end;
procedure TForm1.Convop1Click(Sender: TObject);
var s,p:string;
begin
op_plusb:=false;  op_minusb:=false; prec:=strtoint(divprec.text);
sys1:=strtoint(system1.text); sys2:=strtoint(system2.text);
s:=ae.text; p:=strprocconv(s); e3.text:=p;
if memo.text<>'' then memo.text:=memo.text+'  ';
memo.text:=memo.text+s+' in system '+system1.text+'  =  '+p+' in system '+system2.text;
//memo.text:=memo.text+s+'('+system1.text+') = '+p+'('+system2.text+'); ';
end;
procedure tform1.buttonenable(n:byte);
var i:byte; a:array[0..35] of boolean;
begin
for i:=0 to 35 do a[i]:=false;
for i:=0 to n-1 do a[i]:=true;
if a[0]=true then b0.Enabled:=true else b0.Enabled:=false;
if a[1]=true then b1.Enabled:=true else b1.Enabled:=false;
if a[2]=true then b2.Enabled:=true else b2.Enabled:=false;
if a[3]=true then b3.Enabled:=true else b3.Enabled:=false;
if a[4]=true then b4.Enabled:=true else b4.Enabled:=false;
if a[5]=true then b5.Enabled:=true else b5.Enabled:=false;
if a[6]=true then b6.Enabled:=true else b6.Enabled:=false;
if a[7]=true then b7.Enabled:=true else b7.Enabled:=false;
if a[8]=true then b8.Enabled:=true else b8.Enabled:=false;
if a[9]=true then b9.Enabled:=true else b9.Enabled:=false;
if a[10]=true then b10.Enabled:=true else b10.Enabled:=false;
if a[11]=true then b11.Enabled:=true else b11.Enabled:=false;
if a[12]=true then b12.Enabled:=true else b12.Enabled:=false;
if a[13]=true then b13.Enabled:=true else b13.Enabled:=false;
if a[14]=true then b14.Enabled:=true else b14.Enabled:=false;
if a[15]=true then b15.Enabled:=true else b15.Enabled:=false;
if a[16]=true then b16.Enabled:=true else b16.Enabled:=false;
if a[17]=true then b17.Enabled:=true else b17.Enabled:=false;
if a[18]=true then b18.Enabled:=true else b18.Enabled:=false;
if a[19]=true then b19.Enabled:=true else b19.Enabled:=false;
if a[20]=true then b20.Enabled:=true else b20.Enabled:=false;
if a[21]=true then b21.Enabled:=true else b21.Enabled:=false;
if a[22]=true then b22.Enabled:=true else b22.Enabled:=false;
if a[23]=true then b23.Enabled:=true else b23.Enabled:=false;
if a[24]=true then b24.Enabled:=true else b24.Enabled:=false;
if a[25]=true then b25.Enabled:=true else b25.Enabled:=false;
if a[26]=true then b26.Enabled:=true else b26.Enabled:=false;
if a[27]=true then b27.Enabled:=true else b27.Enabled:=false;
if a[28]=true then b28.Enabled:=true else b28.Enabled:=false;
if a[29]=true then b29.Enabled:=true else b29.Enabled:=false;
if a[30]=true then b30.Enabled:=true else b30.Enabled:=false;
if a[31]=true then b31.Enabled:=true else b31.Enabled:=false;
if a[32]=true then b32.Enabled:=true else b32.Enabled:=false;
if a[33]=true then b33.Enabled:=true else b33.Enabled:=false;
if a[34]=true then b34.Enabled:=true else b34.Enabled:=false;
if a[35]=true then b35.Enabled:=true else b35.Enabled:=false; end;
procedure TForm1.system1Change(Sender: TObject);
var i,n:byte; a:array[0..35] of boolean;
begin n:=strtoint(system1.text);
buttonenable(n); end;
procedure TForm1.nsChange(Sender: TObject);
var i,n:byte; a:array[0..35] of boolean;
begin n:=strtoint(ns.text);
buttonenable(n); end;
procedure TForm1.ns2Click(Sender: TObject);
begin ns.text:='2'; buttonenable(2); end;
procedure TForm1.ns8Click(Sender: TObject);
begin ns.text:='8'; buttonenable(8); end;
procedure TForm1.ns10Click(Sender: TObject);
begin ns.text:='10'; buttonenable(10); end;
procedure TForm1.ns16Click(Sender: TObject);
begin ns.text:='16'; buttonenable(16); end;
procedure TForm1.FormCreate(Sender: TObject);
begin buttonenable(10); end;


end.
