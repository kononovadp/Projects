uses sysutils;
var g:text;
    s,a,b,c,{исходные строки} a1,b1,c1,{предыдущие строки}
    com,{комментарий}dt,{тип переменной (db,dw,dd)}
    cop{код операции}:string;
    i,m:integer; numbers:set of char;
    bol:boolean;{комментарий} r:byte;{результат определения регистра}
    {var g,temp:text; s,a,b,c,b1,c1,a1,l,p,p1,com,dt:string; i,m,k,pt:integer;
    t,t1:real; numbers:set of char; bol:boolean; r:byte; }
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
bintohex:=inttostr(b); bintohex:=hxd(b);
end;
function reg(s:string):byte;
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
begin
assign(g,'res.asm'); reset(g); b1:='segment';
for i:= 48 to 57 do numbers:=numbers+[chr(i)]; i:=0;
while not eof(g) do begin
l2:readln(g,s); i:=0; bol:=false;
for i:= 1 to length(s) do if pos('*',s)<>0 then bol:=true;
if bol=true then begin i:=0; while s[i]<>'*' do begin com:=com+s[i]; inc(i); end;
delete(s,1,length(com)); delete(com,1,1); com:=com+'|'; i:=0; end;
i:=0; while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(a,1,1); if a='assume' then begin writeln(s); a:=''; goto l2; end;
delete(s,1,length(a)+1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
//-----------------------------------------------------------------------
if a1='cli' then m:=m+1;
if a1='inc' then begin r:=reg(b1);
case r of
8: m:=m+2; 16: m:=m+1; 32: m:= m+2; end; end;
if a1='dec' then begin
dt:=typedef(b1);
if (dt='byte') or (dt='word') then m:=m+4;
if (dt='dword') then m:=m+5; end;
if a1='adc' then begin r:=reg(b1);
case r of
8: m:=m+2; 16: m:=m+2; 32: m:= m+3; end; end;
if a1='cmp' then begin r:=reg(b1);
case r of
8: m:=m+4; 16: m:=m+4; 32: m:= m+5; end; end;
if a1='xor' then begin
dt:=typedef(c1);
if (dt='byte') or (dt='word') then m:=m+4;
if (dt='dword') then m:=m+5; end;
if a1='sal' then begin r:=reg(b1);
case r of
8: m:=m+3; 16: m:=m+3; 32: m:= m+4; end; end;
if a1='or' then begin
dt:=typedef(b1);
if (dt='byte') or (dt='word') then m:=m+5;
if (dt='dword') then m:=m+6; end;
{if a1='or' then begin
case b1 of
'db': m:=m+5;
'dw': m:=m+5;
'dd': m:=m+6; end; end;}
if a1='jb' then m:=m+2;
if (b1='segment') or (b1='ends') or (b='ends') then m:=0;
//-----------------------------------------------------------------------

l1:writeln(hxd(m),com,'|',a,'|',b,'|',c,'|');
if a='end' then break;
a1:=a; b1:=b; c1:=c;
a:=''; b:=''; c:=''; com:='';
end;
close(g);
readln;
end.
