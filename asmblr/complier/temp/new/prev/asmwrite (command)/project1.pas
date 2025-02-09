uses sysutils;
var g,temp:text;
    s,a,b,c,{исходные строки} a1,b1,c1,cop1,{предыдущие строки}
    com,{комментарий}dt,{тип переменной (db,dw,dd)}
    cop{код операции},regn{номер регистра},dtb{код регистра},
    cc{код команды},pr{префикс},od{смещение переменной}:string;
    i,m:integer; numbers:set of char; t:longint;
    bol{комментарий},bth{2-10 или 2-16},ordb{bin или dec}:boolean;
    r:byte;{результат определения типа}
label l1,l2;
function hxd(n:integer):string; //перевод числа из десятичной в 16-ричную систему
var i,c:integer; s,sr:string; ch:char;
begin
for i:=1 to 4 do begin
  c:=n mod 16;
  n:=n div 16;
  sr:=inttostr(c);
  if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
  if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
  s:=s+sr;
end;
n:= length(s) div 2;
for i:= 1 to n do begin
ch:= s[i];
s[i]:= s[length(s)-i+1];
s[length(s)-i+1] := ch;
end;
hxd:=s;
end;
function bintohex(s:string):string;
var n,i,k,b,r,j:integer;
begin
k:= length(s)-1; i:=1; b:=0;
while i<>length(s)+1 do begin
n:=strtoint(s[i]); inc(i);
r:=1; for j:=1 to k do r:=r*2; k:=k-1;
b:=b+(r*n);
end;
bintohex:=inttostr(b);
if bth=true then bintohex:=hxd(b);
end;
function hextodec(s:string):string;
var r,b:int64; i,j,k,n:byte; s6:set of char;
label l1;
begin
for i:= 65 to 70 do s6:=s6+[chr(i)];  i:=0;
k:=length(s)-1; i:=1; b:=0;
while i<>length(s)+1 do begin
if s[i] in s6 then begin
case s[i] of
'A':n:=10; 'B':n:=11; 'C':n:=12;
'D':n:=13; 'E':n:=14; 'F':n:=15; end; goto l1;
end; n:=strtoint(s[i]);
l1:inc(i); r:=1;
for j:=1 to k do r:=r*16; k:=k-1;
b:=b+(r*n); end;
hextodec:=inttostr(b); end;
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
//функции определения кода регистра
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
close(f);
end;
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
//ф-я определения типа числа (2,10 или 16)
function numdef(s:string):byte;
var s5:set of char;
begin
for i:= 48 to 57 do s5:=s5+[chr(i)];
if s[length(s)]='b' then numdef:=2;
if s[length(s)] in s5 then numdef:=10;
if s[length(s)]='d' then numdef:=11;
if s[length(s)]='h' then numdef:=16; end;
//ф-я определения количества байтов
function dollardef(s:string):integer;
var c:string; i,j,n,k:integer;
begin
writeln(temp,s);
//if (s[1]='6') and (s[3]='|') then delete(s,1,4);
s:=s+' '; n:=0;
for j:=1 to length(s) do if s[j]=' ' then inc(n);
j:=0; k:=0;
for i:=1 to n do begin
while s[j]<>' ' do begin c:=c+s[j]; inc(j); end; j:=0;
delete(c,1,1); delete (s,1,length(c)); delete(s,1,1);
case length(c) of
1: j:=1; 2: j:=1; 3: j:=1; end;

//if length(c)=1 then c:=c+'*';
//k:=k+(length(c) div 2);
c:='';
end;
dollardef:=n; end;
begin
assign(g,'res.asm'); reset(g); b1:='segment'; bth:=true;
assign(temp,'temp10.asm'); rewrite(temp);
for i:= 48 to 57 do numbers:=numbers+[chr(i)]; i:=0;
pr:='66| '; //префикс замены разрядности (для 32-разрядных данных)
while not eof(g) do begin
l2:readln(g,s); i:=0; bol:=false;
for i:= 1 to length(s) do if pos('*',s)<>0 then bol:=true;
if bol=true then begin i:=0; while s[i]<>'*' do begin com:=com+s[i]; inc(i); end;
delete(s,1,length(com)); delete(com,1,1); i:=0; end;
i:=0; while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(a,1,1); if a='assume' then begin writeln(s); a:=''; goto l2; end;
delete(s,1,length(a)+1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
//-----------------------------------------------------------------------
//if a1='cli' then m:=m+1; {счетчик IP}
if a='cli' then cop:='FA'; {код команды}
//----------inc----------
{счетчик IP}
{if a1='inc' then begin r:=reg(b1);
case r of
8: m:=m+2; 16: m:=m+1; 32: m:= m+2; end; end;}
{код команды}
if a='inc' then begin
r:=reg(b); if r=8 then regn:='11000' else regn:='1000';
dtb:=regcode(b); regn:=regn+dtb;
cop:=bintohex(regn); delete(cop,1,2);
if r=8 then begin cc:='FE '; insert(cc,cop,1); end;
if r=32 then insert(pr,cop,1);
end;
//----------dec----------
{счетчик IP}
{if a1='dec' then begin
dt:=typedef(b1);
if (dt='byte') or (dt='word') then m:=m+4;
if (dt='dword') then m:=m+5; end;}
{код команды}
if a='dec' then begin
dt:=typedef(b);
if dt='byte' then cc:='FE 0E ';
if (dt='word') or (dt='dword') then cc:='FF 0E ';
cop:=cc; od:=offsetdef(b); cop:=cop+od;
cop:= cop+' R'; if dt='dword' then insert(pr,cop,1);
end;
//----------adc----------
{счетчик IP}
{if a1='adc' then begin r:=reg(b1);
case r of
8: m:=m+2; 16: m:=m+2; 32: m:= m+3; end; end;}
{код команды}
if a='adc' then begin
regn:='11'; dtb:=regcode(b); insert(dtb,regn,3);
dtb:=regcode(c); insert(dtb,regn,6);
cop:=bintohex(regn); delete(cop,1,2);
r:=reg(b); if r=8 then cc:='12 ' else cc:='13 ';
insert(cc,cop,1);
if r=32 then insert(pr,cop,1); end;
//----------cmp----------
{счетчик IP}
{if a1='cmp' then begin r:=reg(b1);
case r of
8: m:=m+4; 16: m:=m+4; 32: m:= m+5; end; end;}
{код команды}
if a='cmp' then begin
dt:=typedef(c);
if dt='byte' then cop:='3A ';
if (dt='word') or (dt='dword') then cop:='3B ';
regn:='110'; dtb:=regcode(b); insert(dtb,regn,1);
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(c); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1); end;
//----------xor----------
{счетчик IP}
{if a1='xor' then begin
dt:=typedef(c1);
if (dt='byte') or (dt='word') then m:=m+4;
if (dt='dword') then m:=m+5; end;}
{код команды}
if a='xor' then begin
dt:=typedef(c);
if dt='byte' then cop:='32 ';
if (dt='word') or (dt='dword') then cop:='33 ';
regn:='110'; dtb:=regcode(b); insert(dtb,regn,1);
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(c); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1); end;
//----------sal----------
{счетчик IP}
{if a1='sal' then begin r:=reg(b1);
case r of
8: m:=m+3; 16: m:=m+3; 32: m:= m+4; end; end;}
{код команды}
if a='sal' then begin
r:=reg(b); if r=8 then cop:='C0 ' else cop:='C1 ';
dtb:=regcode(b); insert('11100',dtb,1);
cc:=bintohex(dtb); delete(cc,1,2);
cop:=cop+cc+' '; if r=32 then insert(pr,cop,1);
r:=numdef(c);
if r=2 then begin dtb:=c;
delete(dtb,length(dtb),1); cc:=bintohex(dtb); delete(cc,1,2); end;
if r=10 then begin t:=strtoint(c); cc:=hxd(t); delete(cc,1,2); end;
if r=11 then begin dtb:=c; delete(dtb,length(dtb),1);
t:=strtoint(dtb); cc:=hxd(t); delete(cc,1,2); end;
if r=16 then begin dtb:=c;
delete(dtb,length(dtb),1); cc:=dtb; end;
cop:=cop+cc; end;
//----------or----------
{счетчик IP}
{if a1='or' then begin
dt:=typedef(b1);
if (dt='byte') or (dt='word') then m:=m+5;
if (dt='dword') then m:=m+6; end;}
{код команды}
if a='or' then begin
dtb:=c; r:=numdef(dtb); dt:=typedef(b); ordb:=false;
if r=2 then begin delete(dtb,length(dtb),1);
bth:=false; cc:=bintohex(dtb); t:=strtoint(cc); bth:=true;
cc:=bintohex(dtb); ordb:=true; end;
if r=10 then begin t:=strtoint(dtb); cc:=hxd(t); ordb:=true; end;
if r=11 then begin delete(dtb,length(dtb),1);
cc:=hxd(t); t:=strtoint(dtb); ordb:=true; end;
if r=16 then begin delete(dtb,length(dtb),1);
cc:=hextodec(dtb); t:=strtoint(cc); cc:=dtb; end;
regn:=offsetdef(b);
if dt='byte' then begin cop:='80'; delete(cc,1,2); end;
if (t>127) and(dt<>'byte') then cop:='81';
if (dt='word') and (t<=127) then cop:='83';
if (dt='dword') and (t<=127) then cop:='83';
if (dt='dword') and (length(cc)>3) then
for i:=1 to 8-length(cc) do insert ('0',cc,i);
if (t<=127) and (ordb=true) then delete(cc,1,2);
cop:=cop+' 0E '+regn+' R '+cc; bol:=false;
if dt='dword' then begin insert(pr,cop,1); bol:=true; end;
if bol=true then t:=4; if bol=false then t:=5;
t:=t+(length(cc) div 2);
end;
if (cop1<>'') and (a1<>'or') then m:=m+dollardef(cop1);
if a1='jb' then m:=m+2; if a1='or' then m:=m+t;
if (b1='segment') or (b1='ends') or (b='ends') then m:=0;
//-----------------------------------------------------------------------

l1:writeln(m,' ',hxd(m),' ',cop,' ',com,' ',a,' ',b,' ',c);
//writeln(temp,cop,' ',com,' ',a,' ',b,' ',c);
if a='end' then break;
a1:=a; b1:=b; c1:=c; cop1:=cop;
a:=''; b:=''; c:=''; com:=''; cop:=''; regn:='';
end;
close(g);  close(temp);
readln;
end.
