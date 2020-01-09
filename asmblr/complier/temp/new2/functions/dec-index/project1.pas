uses sysutils;
var dt,cc,cop,b,od,pr,reg,pr2:string; i:byte;
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
//----------
function com_dec(b:string):string;
var s1,s2,s3,r:string; j:byte; ch:char;
l1:set of char; t1,t2:integer;
begin r:=b;
for i:= 97 to 122 do l1:=l1+[chr(i)]; i:=0;
if pos('[',r)=0 then begin; s1:=r; reg:=''; end;//begin reg:='0E '; s1:=r; end;
if pos('[',r)<>0 then begin
while r[i]<>'[' do begin s1:=s1+r[i]; inc(i); end; delete(s1,1,1);//идентификатор
j:=pos('[',r)+1;
while r[j]<>']' do begin s2:=s2+r[j]; inc(j); end; reg:=s2;//полное выражение в скобках
if (pos('-',r)<>0) or (pos('+',r)<>0) then begin
i:=pos('-',r); j:=pos('+',r); if i>0 then ch:='-' else ch:='+'; i:=0;
while s2[i]<>ch do begin s3:=s3+s2[i]; inc(i); end;
delete(s3,1,1); reg:=s3; {writeln(reg);} delete(s2,1,length(s3)); ch:=s2[1];//действие
delete(s2,1,1);t1:=strtoint(s2);//операнд
end; end; //========================================
dt:=typedef(s1);
if dt='byte' then r:='FE ';
if (dt='word') or (dt='dword') then r:='FF ';
if dt='dword' then insert(pr,r,1);
od:=offsetdef(s1); if ch<>'' then begin //вычисление выражения
od:=hextodec(od); t2:=strtoint(od);
case ch of '-': t2:=t2-t1; '+': t2:=t2+t1; end;
od:=hxd(t2); end;
case reg of 'di': s1:='8D '; 'si': s1:='8C '; 'bx': s1:='8F ';
'ebx': s1:='8B '; 'esi': s1:='8E '; 'edi': s1:='8F '; '': s1:='0E 'end;
//writeln(reg,'|');
//if dt='dword' then insert(pr,r,5);
if (reg='ebx') or (reg='esi') or (reg='edi') then begin
insert(pr2,r,1); for i:=1 to 4 do insert('0',od,1); end;
//writeln(r); readln; writeln(s1); readln; writeln(od);
com_dec:=r+s1+od+' R';
end;
begin
pr:='66| '; pr2:='67& ';
b:='const'; writeln(com_dec(b));
readln;
end.
