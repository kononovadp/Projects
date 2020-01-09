uses sysutils;
var jbl{адрес метки (для jb)},m{//$}:integer;
    g,labels,temp:text;
    s,a,b,c,{исходные строки} a1,b1,c1,cop1,{предыдущие строки}
    com,{комментарий}dt,{тип переменной (db,dw,dd)}
    cop{код операции},regn{номер регистра},dtb{код регистра},
    cc{код команды},pr{префикс},od{смещение переменной}:string;
    i:integer; numbers:set of char; t:longint;
    bol{комментарий},ordb{bin или dec},
    jbprov:boolean;
    r:integer;{результат определения типа}
//перевод числа из десятичной в 16-ричную систему
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
//ф-я определения типа числа (2,10 или 16)
function numdef(s:string):byte;
var s5:set of char; i:byte;
begin
for i:= 48 to 57 do s5:=s5+[chr(i)];
if s[length(s)]='b' then numdef:=2;
if s[length(s)] in s5 then numdef:=10;
if s[length(s)]='d' then numdef:=11;
if s[length(s)]='h' then numdef:=16; end;
//ф-я определения количества байт
function dollar(s:string):integer;
var c:string; i,j,n,k:integer;
begin
n:=0; s:=s+' ';
for j:=1 to length(s) do if s[j]=' ' then inc(n);
dollar:=n; end;
//===============================коды команд====================================
//----------inc----------
function com_inc(b:string):string;
begin
r:=reg(b); if r=8 then regn:='11000' else regn:='1000';
dtb:=regcode(b); regn:=regn+dtb;
cop:=bintohex(regn); delete(cop,1,2);
if r=8 then begin cc:='FE '; insert(cc,cop,1); end;
if r=32 then insert(pr,cop,1);
com_inc:=cop; end;
//----------dec----------
function com_dec(b:string):string;
begin
dt:=typedef(b);
if dt='byte' then cc:='FE 0E ';
if (dt='word') or (dt='dword') then cc:='FF 0E ';
cop:=cc; od:=offsetdef(b); cop:=cop+od;
cop:= cop+' R'; if dt='dword' then insert(pr,cop,1);
com_dec:=cop; end;
//----------adc----------
function com_adc(b,c:string):string;
begin
regn:='11'; dtb:=regcode(b); insert(dtb,regn,3);
dtb:=regcode(c); insert(dtb,regn,6);
cop:=bintohex(regn); delete(cop,1,2);
r:=reg(b); if r=8 then cc:='12 ' else cc:='13 ';
insert(cc,cop,1);
if r=32 then insert(pr,cop,1);
com_adc:=cop; end;
//----------cmp----------
function com_cmp(b,c:string):string;
begin
dt:=typedef(c);
if dt='byte' then cop:='3A ';
if (dt='word') or (dt='dword') then cop:='3B ';
regn:=regcode(b)+'110';
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(c); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1);
com_cmp:=cop; end;
//----------xor----------
function com_xor(b,c:string):string;
begin
dt:=typedef(c);
if dt='byte' then cop:='32 ';
if (dt='word') or (dt='dword') then cop:='33 ';
regn:='110'; dtb:=regcode(b); insert(dtb,regn,1);
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(c); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1);
com_xor:=cop; end;
//----------sal----------
function com_sal(b,c:string):string;
begin
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
cop:=cop+cc; com_sal:=cop; end;
//----------or----------
function com_or(b,c:string):string;
begin r:=0; dtb:=''; dt:=''; cc:=''; regn:=''; t:=0; regn:=''; cop:='';
dtb:=c;
r:=numdef(dtb);
dt:=offsetdef(b);
regn:=typedef(b);
if r=2 then begin
delete(dtb,length(dtb),1);
cc:=bintodec(dtb);
t:=strtoint(cc);
cc:=hxd(t); end;//bintohex(dtb); end;
if r=10 then begin t:=strtoint(dtb); cc:=hxd(t); end;
if r=11 then begin delete(dtb,length(dtb),1);
t:=strtoint(dtb); cc:=hxd(t); end;
if r=16 then begin delete(dtb,length(dtb),1);
cc:=hextodec(dtb); t:=strtoint(cc); cc:=dtb; end;
if (regn='byte') and (t<256) then begin cop:='80 0E '; delete(cc,1,2); end;
if (regn<>'byte') and (t>127) then cop:='81 0E ';
if (regn<>'byte') and (t<128) then cop:='83 0E ';
if (regn<>'byte') and (t<128)
and (length(cc)=4) then delete(cc,1,2);
if (regn='dword') and (t>128) then
for i:=1 to 8-length(cc) do insert('0',cc,1);
cop:=cop+dt+' R '+cc;
if regn='dword' then insert(pr,cop,1);
r:=(length(cc) div 2-1); //case length(cc) of 2: r:=0; 4: r:=1; 8: r:=3; end;
t:=dollar(cop)+r; //writeln(t);
com_or:=cop; end;
//----------jb----------
function com_jb(k:string):string;
var x,y:string; k1,k2:integer;
begin k:=k+':';
assign(labels,'labels.asm'); reset(labels);
while not eof(labels) do begin
readln(labels,x); i:=0;
while x[i]<>' ' do begin y:=y+x[i]; inc(i); end;
delete(y,1,1); delete(x,1,length(y)+1);
if x=k then cc:=y;
y:=''; end; close(labels);
k1:=strtoint(cc);

if k1>m then k2:=k1-m;
if k2<127 then begin k2:=k2-2; t:=2; cc:='72 ';
x:=hxd(k2); delete(x,1,2); end
else begin k2:=k2-2; t:=4; cc:='0F 82 '; x:=hxd(k2); end;
if k1<m then //begin
if m<127 then begin k2:=256-m+k1-2; t:=2; cc:='72 ';
x:=hxd(k2); delete(x,1,2); end
else begin k2:=65536-m+k1-4; t:=4; cc:='0F 82 '; x:=hxd(k2); end;
com_jb:=cc+x//hxd(k2);
end;


procedure commandcode;
label l1,l2;
begin
assign(g,'res.asm'); reset(g); b1:='segment';
if jbprov=false then begin
assign(labels,'labels.asm'); rewrite(labels); end;
assign(temp,'temp.asm'); rewrite(temp);
for i:= 48 to 57 do numbers:=numbers+[chr(i)]; i:=0;
a:=''; b:=''; c:='';
pr:='66| '; //префикс замены разрядности (для 32-разрядных данных)
while not eof(g) do begin
l2:readln(g,s); i:=0; bol:=false;


if pos('*',s)<>0 then
begin i:=0; while s[i]<>'*' do begin com:=com+s[i]; inc(i); end;
delete(s,1,length(com)); delete(com,1,1); i:=0; end;

i:=0; while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(a,1,1);
if (a='assume') and (jbprov=false) then begin a:=''; goto l2; end;
if (a='assume') and (jbprov=true) then begin writeln(s); a:=''; goto l2; end;
delete(s,1,length(a)+1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
//-----------------------------------------------------------------------------
//if (a1='jb') and(jbprov=true) then writeln(m);
if (cop1<>'') and (a1<>'or') and(a1<>'jb') {and (jbprov=false)} then m:=m+dollar(cop1);
if (a1='jb') and(jbprov=false) then m:=m+2;//найти почему нужно там +2 а там +1
if (a1='jb') and(jbprov=true) then m:=m+t;//m:=m+1;
 if a1='or' then m:=m+t;
if (b1='segment') or (b1='ends') or (b='ends') then m:=0;
case a of'cli': cop:='FA'; 'inc': cop:=com_inc(b);
'dec': cop:=com_dec(b); 'adc': cop:=com_adc(b,c);
'cmp': cop:=com_cmp(b,c); 'xor': cop:=com_xor(b,c);
'sal': cop:=com_sal(b,c); 'or': cop:=com_or(b,c); end;
if (a='jb') and (jbprov=true) then cop:=com_jb(b);
if (jbprov=false) and(com<>'') then writeln(labels,m,' ',com);
//=============================================================================
l1: if jbprov=true then
writeln(m,' ',hxd(m),' ',cop,' ',com,' ',a,' ',b,' ',c);
if a='end' then break;
a1:=a; b1:=b; c1:=c; cop1:=cop;
a:=''; b:=''; c:=''; com:=''; cop:=''; regn:='';
end;
close(g); close(temp);
if jbprov=false then close(labels);
end;



begin
jbprov:=false;
commandcode;
jbprov:=true;
commandcode;
readln;
end.
