uses sysutils;
var dt,cc,cop,b,od,pr,regn,pr2,s,c:string; i:byte;
  function hxd(n:integer):string;
  var i,c:integer; s,sr:string; ch:char;
  begin
  for i:=1 to 4 do begin
    c:=n mod 16;
    n:=n div 16;
    sr:=inttostr(c);
    if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
    if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
    s:=sr+s;
  end;
  hxd:=s; end;
  //перевод числа из двоичнуой системы в десятичную
  function bintodec(s:string):string;
  var n,i,k,b,r,j:integer;
  begin
  k:= length(s); i:=1; b:=1;
  for i:=2 to k do b:=b*2+strtoint(s[i]);
  bintodec:=inttostr(b); end;
  //перевод числа из двоичной в 16-ричную систему
  function bintohex(s:string):string;
  var n,i,k,b,r,j:integer;
  begin
  k:= length(s)-1; i:=1; b:=0;
  while i<>length(s)+1 do begin
  n:=strtoint(s[i]); inc(i);
  r:=1; for j:=1 to k do r:=r*2; k:=k-1;
  b:=b+(r*n);
  end; bintohex:=inttostr(b);
  bintohex:=hxd(b);
  end;
//перевод числа из 16ричной системы в десятичную
function hextodec(s:string):string;
var r,b:int64; i,j,k,n:byte; s6:set of char;
begin
for i:= 65 to 70 do s6:=s6+[chr(i)];
for i:= 97 to 102 do s6:=s6+[chr(i)];
k:=length(s)-1; i:=1; b:=0;
if s[length(s)]='h' then delete(s,length(s),1);
while i<>length(s)+1 do begin
if s[i] in s6 then
case s[i] of
'A':n:=10; 'B':n:=11; 'C':n:=12;
'a':n:=10; 'b':n:=11; 'c':n:=12;
'D':n:=13; 'E':n:=14; 'F':n:=15;
'd':n:=13; 'e':n:=14; 'f':n:=15; end
else n:=strtoint(s[i]);
inc(i);
b:=b*16+n; end;
hextodec:=inttostr(b); end;
{else n:=strtoint(s[i]);
inc(i);
b:=b*16+n; end;
hextodec:=inttostr(b); end;}
function reg(s:string):byte; //определение разрядности регистра
begin
case s of
'al':reg:=8; 'ax':reg:=16; 'eax':reg:=32;
'cl':reg:=8; 'cx':reg:=16; 'ecx':reg:=32;
'dl':reg:=8; 'dx':reg:=16; 'edx':reg:=32;
'bl':reg:=8; 'bx':reg:=16; 'ebx':reg:=32;
'ah':reg:=8; 'sp':reg:=16; 'esp':reg:=32;
'ch':reg:=8; 'bp':reg:=16; 'ebp':reg:=32;
'dh':reg:=8; 'si':reg:=16; 'esi':reg:=32;
'bh':reg:=8; 'di':reg:=16; 'edi':reg:=32;
end; end;
function regcode(s:string):string;
begin
if (s='al') or (s='ax') or (s='eax') then regcode:='000';
if (s='cl') or (s='cx') or (s='ecx') then regcode:='001';
if (s='dl') or (s='dx') or (s='edx') then regcode:='010';
if (s='bl') or (s='bx') or (s='ebx') then regcode:='011';
if (s='ah') or (s='sp') or (s='esp') then regcode:='100';
if (s='ch') or (s='bp') or (s='ebp') then regcode:='101';
if (s='dh') or (s='si') or (s='esi') then regcode:='110';
if (s='bh') or (s='di') or (s='edi') then regcode:='111';
end;
//ф-я определения типа переменной (db,dw,dd)
function typedef(k:string):string;
var f:text; s,a,b:string; i:byte;
begin
assign(f,'idlist.txt'); reset(f);
while not eof(f) do begin
readln(f,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(b,1,1);
if k=a then typedef:=b; a:=''; b:='';
end;
close(f); end;
//ф-я определения смещения переменной
function offsetdef(k:string):string;
var f:text; s,a,b,c:string; i:byte;
begin
assign(f,'idlist.txt'); reset(f);
while not eof(f) do begin
readln(f,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)+1); delete(b,1,1); i:=0;
while s[i]<>' ' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1);
if k=a then offsetdef:=c;
a:=''; b:=''; c:='';
end; close(f); end;
//----------------------------------
function com_cmp(b,c:string):string;
var sc,s1,s2,s3,r1,r2,
pr1,pr2,pr3:string; l1,l2:set of char;
n1,n2,k:integer; ch:char; r:byte;
label m1;
begin sc:=c; n1:=0; n2:=0; k:=0;
for i:= 97 to 122 do l1:=l1+[chr(i)];
for i:= 48 to 57 do l2:=l2+[chr(i)];
if pos('[',sc)=0 then begin
dt:=typedef(sc);
if dt='byte' then cop:='3A ';
if (dt='word') or (dt='dword') then cop:='3B ';
regn:=regcode(b)+'110';
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(sc); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1);
{com_cmp:=cop;} end else begin //---------------------------
i:=0; while sc[i]<>'[' do begin s1:=s1+sc[i]; inc(i); end;
delete(s1,1,1); //const----------------------------
delete(sc,1,length(s1)+1); delete(sc,length(sc),1); //index
if (pos('+',sc)=0) and (pos('-',sc)=0)
then begin s2:=sc; goto m1; end //[bx]
else begin if pos('+',sc)>0 then ch:='+' else ch:='-';
i:=0; while sc[i]<>ch do begin s2:=s2+sc[i]; inc(i); end;
delete(s2,1,1); delete(sc,1,length(s2)+1);//writeln(sc); //bx+si or bx+42
if (pos('+',sc)=0) and (pos('-',sc)=0) then begin
if sc[1] in l1 then begin s2:=s2+'+'+sc; goto m1; end;
if sc[1] in l2 then begin n1:=strtoint(sc); goto m1; end;
end else begin if pos('+',sc)>0 then ch:='+' else ch:='-';
i:=0; while sc[i]<>ch do begin s3:=s3+sc[i]; inc(i); end;
delete(s3,1,1); s2:=s2+'+'+s3; delete(sc,1,length(s3)+1);
n1:=strtoint(sc); {} //[bx+si+56]
end; end; //writeln(s2);
//------
m1:
r:=reg(s2); if r=32 then r2:=regcode(s2) else
case s2 of
'bx+si': r2:='000'; 'bx+di': r2:='001';
'bp+si': r2:='010'; 'bp+di': r2:='011';
'si': r2:='100'; 'di': r2:='101';
'bp': r2:='110'; 'bx': r2:='111'; end;
r1:=regcode(b);
if (s2='bp+si') or (s2='bp+di') or (s2='bp') or (s2='ebp')
then pr3:='3E: ';
regn:='10'+r1+r2; regn:=bintohex(regn); delete(regn,1,2);
dt:=typedef(s1);
if dt='dword' then begin pr2:='66| '; end;
if dt='byte' then dt:='3A ';
if (dt='word') or (dt='dword') then dt:='3B ';
//-------
s2:=offsetdef(s1);
if ch<>'' then begin  s3:=hextodec(s2); n2:=strtoint(s3);
if ch='+' then k:=n1+n2 else k:=n2-n1;
s2:=hxd(k); end;
if r=32 then pr1:='67& ';

if r=32 then insert('0000',s2,1);
cop:=pr1+pr2+pr3+cop+dt+regn+' '+s2+' R';
end;
com_cmp:=cop;
end;
begin
b:='ecx'; c:='const9[ebp+62316]';
writeln(com_cmp(b,c));
readln;
end.
