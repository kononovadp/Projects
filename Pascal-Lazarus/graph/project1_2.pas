uses sysutils;
var s1,s2{исходные строки},od{остаток от деления},
    se1,se2{выровненные строки}:string;
    sys{система счисления},prec{точность деления}:byte;
    z1,z2,ze1,ze2{позиции запятых}:integer; plusb:boolean; c:int64;

function chd(i:byte):string;
var ch:char;
begin
if i>9 then begin i:=i+55; chd:=chr(i); end
else chd:=inttostr(i); end;

function chton(ch:char):byte;
var set1,set2:set of char; i:byte;
begin set1:=[];
for i:=48 to 57 do
set1:=set1+[chr(i)];
if ch in set1 then chton:= strtoint(ch)
else chton:=ord(ch)-55; end;

function eqc(s1,s2:string):string;
var e1,e2:string; i,j:byte;
begin
z1:=pos('.',s1); z2:=pos('.',s2);
if pos('.',s1)>pos('.',s2) then begin
i:=pos('.',s1)-pos('.',s2);
for j:=1 to i-1 do s2:='0'+s2; end;
if pos('.',s1)<pos('.',s2) then begin
i:=pos('.',s2)-pos('.',s1);
for j:=1 to i-1 do s1:='0'+s1; end;
if z1>0 then delete(s1,pos('.',s1),1);
if z2>0 then delete(s2,pos('.',s2),1);
se1:=s1; se2:=s2; eqc:=''; end;

function eqz(s1,s2:string):string;
var i:byte;
begin
if length(s1)<length(s2) then
for i:=1 to length(s2)-length(s1) do s1:='0'+s1;
if length(s1)>length(s2) then
for i:=1 to length(s1)-length(s2) do s2:='0'+s2;
se1:=s1; se2:=s2; eqz:=''; end;

function compare(s1,s2:string):char;
var i,z,x:byte;
begin z:=0; x:=0;
if s1=s2 then compare:='=' else
if length(s1)> length(s2) then compare:='>' else
if length(s1)<length(s2) then compare:='<' else begin i:=1;
while s1[i]=s2[i] do inc(i);
if ord(s1[i])<ord(s2[i]) then compare:='<' else compare:='>';
end; end;

function zerodelb(s:string):string;
var i:integer;
begin i:=1;
while s[i]='0' do inc(i);
delete(s,1,i-1);
if length(s)=0 then s:='0';
zerodelb:=s; end;

function zerodele(s:string):string;
var i:integer;
begin i:=length(s)-1;
while s[i]='0' do dec(i);
delete(s,i+1,length(s)-i);
if length(s)=0 then s:='0';
zerodele:=s; end;

function zeroexc(s1,s2,r:string):string;
var i,k:integer; n:byte;

begin i:=1; k:=1; if (s1<>'') and (s2<>'') then n:=1 else n:=0;
if pos('.',s1)>0 then delete(s1,pos('.',s1),1);
if pos('.',s2)>0 then delete(s2,pos('.',s2),1);
if s1<>'' then while s1[i]='0' do inc(i) else i:=0;
if s2<>'' then while s2[i]='0' do inc(k) else k:=0;
k:=k+i; i:=0;
for i:=1 to k-2-n do r:='0'+r; zeroexc:=r;
end;

function check(s:string):string;
var i:byte; set1:set of char;
begin
if sys>36 then begin check:='!!!'; exit; end;
for i:=48 to 48+sys-1 do
set1:=set1+[chr(i)];
if sys>9 then
for i:=65 to 65+sys-10-1 do
set1:=set1+[chr(i)];
for i:=1 to length(s) do
if not(s[i] in set1) then begin check:='!!!'; break; exit; end
else check:=''; end;

function plus(s1,s2:string):string;
var e:string; a,c,d,i,r:byte; p,q: byte;
    set2:set of char; ch:char;
begin
if plusb=false then
if (pos('.',s1)>0) or (pos('.',s2)>0) then begin
eqc(s1,s2); s1:=se1; s2:=se2; end;
{if length(s1)<>length(s2) then begin
eqz(s1,s2); s1:=se1; s2:=se2; end;}
if (check(s1)<>'') or (check(s2)<>'') then begin
plus:='Incorrect data!!!'; exit; end; set2:=[];
if sys>9 then
for i:=65 to 65+sys-10-1 do
set2:=set2+[chr(i)];
if length(s1)<>length(s2) then
   if length(s1)<length(s2) then
   for i:=1 to length(s2)-length(s1) do s1:='0'+s1 else
   for i:=1 to length(s1)-length(s2) do s2:='0'+s2;
p:=length(s1); q:=length(s2); i:=0; r:=0;
while (p>0) and (q>0) do begin
if s1[p] in set2 then begin ch:=s1[p]; c:=ord(ch)-55; end else
c:=strtoint(s1[p]); dec(p);
if s2[q] in set2 then begin ch:=s2[q]; d:=ord(ch)-55; end else
d:=strtoint(s2[q]); dec(q);
r:=c+d+i;
if r>sys-1 then begin r:=r-sys; i:=1 end else i:=0;
if r>9 then begin a:=r+55; ch:=chr(a); e:=ch+e; end
else e:=inttostr(r)+e;
end;
if i=1 then e:='1'+e;
if plusb=false then
if z1>z2 then insert('.',e,z1) else insert('.',e,z2);
plus:=zerodelb(e); end;

function minus(s1,s2:string):string;
var s,q,w:string; n1,n2,n,m,k,p,i,r,a:integer;
set2:set of char; ch:char;
begin
if pos('.',s1) or pos('.',s2)>0 then begin
eqc(s1,s2); s1:=se1; s2:=se2; end;
if length(s1)<>length(s2) then begin
eqz(s1,s2); s1:=se1; s2:=se2; end;
if (check(s1)<>'') or (check(s2)<>'') then begin
minus:='Incorrect data!!!'; exit; end; set2:=[];
if sys>9 then
for i:=65 to 65+sys-10-1 do
set2:=set2+[chr(i)];
n:=length(s1); r:=0; i:=0;
if n>length(s2) then
for r:=1 to n-length(s2) do s2:='0'+s2;
if n<length(s2) then
for r:=1 to length(s2)-n do s1:='0'+s1;
while (n>0) do begin
if s1[n] in set2 then begin ch:=s1[n]; k:=(ord(ch)-55)-i; end else
k:=strtoint(s1[n])-i;
if s2[n] in set2 then begin ch:=s2[n]; p:=(ord(ch)-55); end else
p:=strtoint(s2[n]); dec(n);
if k=-1 then k:=sys-1 else
if k<p then begin k:=k+sys; i:=1; end
else  i:=0; r:=k-p;
if r>9 then begin a:=r+55; ch:=chr(a); s:=ch+s; end
else s:=inttostr(r)+s; end;
if pos('0',s)=1 then s:=zerodelb(s);
if (z1>0) or (z2>0) then
if z1<z2 then insert('.',s,z1) else insert('.',s,z2);
minus:=s; end;

function mult(s1,s2:string):string;
var e,p,p2,zs1,zs2:string; ch:char;
    i,j,l1,i1,j1,a,b,r,c,d,n,ze1,n1:byte; b1:boolean;
begin plusb:=true; ze1:=0; z1:=0; z2:=0;
if s1[1]='0' then zs1:=s1; if s2[1]='0' then zs2:=s2;
if (pos('.',s1)>0) or (pos('.',s2)>0) then begin
if (s1[1]='0') or (s2[1]='0') then n1:=0 else n1:=1;
if pos('.',s1)>0 then z1:=length(s1)-pos('.',s1);
if pos('.',s2)>0 then z2:=length(s2)-pos('.',s2);
ze1:=z1+z2-n1; eqc(s1,s2); s1:=se1; s2:=se2; end;
if length(s1)<>length(s2) then begin
eqz(s1,s2); s1:=se1; s2:=se2; end;
if (check(s1)<>'') or (check(s2)<>'') then begin
mult:='Incorrect data!!!'; exit; end;
n:=length(s1); r:=0; i:=0;
l1:=length(s2); p2:='0'; i1:=0;
while l1<>0 do begin
b:=chton(s2[l1]); dec(l1);
n:=length(s1); p:='0'; i:=0;
while n>0 do begin
a:=chton(s1[n]); dec(n);
r:=a*b; c:=r div sys; d:=r-(c*sys);
e:=chd(c)+chd(d); inc(i);
if i>0 then
for j:=1 to i-1 do e:=e+'0'; p:=plus(p,e);
end; inc(i1); if i1>0 then for j1:=1 to i1-1 do
p:=p+'0'; p2:=plus(p2,p); end;
if (zs1<>'') or (zs2<>'') then p2:=zeroexc(zs1,zs2,p2);
if ((zs1<>'') and (zs2='')) or ((zs2<>'') and (zs1=''))
then n:=1 else n:=0; //случай 32*0,5
if ze1>0 then insert('.',p2,length(p2)-ze1+n);
if pos('.',p2)=1 then p2:='0'+p2;
if (pos('.',p2)>0) and (p2[length(p2)]='0') then p2:=zerodele(p2);
if pos('.',p2)=length(p2) then delete(p2,length(p2),1);
mult:=p2; end;

function sysconvert(n:int64):string;
var i,c:integer; s,sr:string; ch:char;
begin  sr:='';
while n>0 do begin
  c:=n mod sys;
  n:=n div sys;
  sr:=chd(c)+sr;end;
sysconvert:=sr; end;

function dividewr(s1,s2:string):string;
var r:int64; b1:boolean; set1:set of char; ch:char;
begin r:=0;
while (compare(s1,s2)='>' ) or (compare(s1,s2)='=') do begin
s1:=minus(s1,s2); inc(r); end; od:=s1;
dividewr:=sysconvert(r); if dividewr='' then dividewr:='0';

end;

function divide(s1,s2:string):string;
var x,r,es:string; b1:boolean; i,z,p:integer;
begin z:=0;
if (pos('.',s1)>0) or (pos('.',s2)>0) then begin
{if pos('.',s1)>0 then z:=(length(s1)-pos('.',s1))-(length(s2)-pos('.',s2)) //z:=pos('.',s1)-pos('.',s2)
else z:=(length(s2)-pos('.',s2))-(length(s1)-pos('.',s1));//z:=pos('.',s2)-pos('.',s1);
if z=0 then z:=1; if z<0 then z:=abs(z);}
z1:=length(s1)-pos('.',s1); z2:=length(s2)-pos('.',s2);
p:=z1-z2;
if pos('.',s1)>0 then delete(s1,pos('.',s1),1);
if pos('.',s2)>0 then delete(s2,pos('.',s2),1);
end;
writeln(s1,'|',s2);


x:=dividewr(s1,s2); if (x='0') and (z>0) then x:='';
if z=0 then x:=x+'.'; od:=od+'0';
while (prec>0) and (od<>'00') do begin
r:=dividewr(od,s2); x:=x+r; od:=od+'0';
dec(prec); end;

if z>0 then insert('.',x,p{z+1});
if pos('.',x)=length(x) then delete(x,pos('.',x),1);
divide:=x; end;


begin plusb:=false;
//проверка сложения
{sys:=16;
s1:='377A75'; s2:='375E76';
writeln(plus(s1,s2));}
//проверка отнимания
{sys:=16;
s1:='3BB7E775'; s2:='3BA75A76';
writeln(minus(s1,s2));
sys:=12;
s1:='753'; s2:='674';
writeln(minus(s1,s2));
sys:=14;
s1:='311714775'; s2:='311751076';
writeln(minus(s2,s1));}
//проверка умножения
{sys:=16;
s1:='3117A14775'; s2:='31175107B6';
writeln(mult(s1,s2));
sys:=2;
s1:='11110011'; s2:='10101011';
writeln(mult(s1,s2));
//проверка деления
sys:=10; prec:=10;
s1:='37768977'; s2:='12752345';
writeln(octdiv(s1,s2));}
{sys:=16;
s1:='58.312'; s2:='377.78';
writeln(plus(s1,s2));
sys:=16;
s1:='377.78'; s2:='58.312';
writeln(minus(s1,s2));}
{sys:=16;
s1:='378747.78ABC45'; s2:='58.01231';//s1:='377.78ABC45'; s2:='58.01';
writeln(mult(s1,s2));}
//s1:='1234ABC56789'; s2:='1234567CBA89'; writeln(compare(s1,s2));
//sys:=16; c:=9223372036854775807; writeln(sysconvert(c));
{sys:=10;
s1:='300'; s2:='150';writeln(octdivfunc(s1,s2));  }
//------------------------//
{sys:=10; //умножение случай 1
s1:='1.2345167'; s2:='5678';
writeln(s1,' * ',s2,' = ',mult(s1,s2));
sys:=10; //умножение случай 2
s1:='0.0002'; s2:='3.2';
writeln(s1,' * ',s2,' = ',mult(s1,s2));
sys:=10; //умножение случай 3
s1:='0.032'; s2:='0.5';
writeln(s1,' * ',s2,' = ',mult(s1,s2));
sys:=10; //умножение случай 4
s1:='32'; s2:='0.5';
writeln(s1,' * ',s2,' = ',mult(s1,s2));}
//------------------------//
{sys:=10; //деление случай 1
s1:='12345167'; s2:='5678'; prec:=10;
writeln(s1,' / ',s2,' = ',divide(s1,s2));}
{sys:=10; //деление случай 2
s1:='99'; s2:='5355'; prec:=10;
writeln(s1,' / ',s2,' = ',divide(s1,s2));}
{sys:=10; //деление случай 3
s1:='35.1'; s2:='1.8'; prec:=10; //s1:='4.1234'; s2:='2.1'; prec:=10;
writeln(s1,' / ',s2,' = ',divide(s1,s2));}
{sys:=10; //деление случай 4
s1:='32'; s2:='15.5'; prec:=10;
writeln(s1,' / ',s2,' = ',divide(s1,s2));}
sys:=10; //деление случай 3
s1:='35.1'; s2:='1'; prec:=10; //s1:='4.1234'; s2:='2.1'; prec:=10;
writeln(s1,' / ',s2,' = ',mult(s1,s2));
readln;
end.
