uses sysutils;
var prov:boolean; g,temp,il,main,dataseg:text;
function hxd(n:integer):string; //перевод числа из десятичной в 16-ричную систему
var i,c:integer; k:byte; s,sr:string; ch:char;
begin
if prov=false then k:=4 else k:=8;
for i:=1 to k do begin
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
procedure datasegment;
var
    s,a,b,c,b1,c1,l,p,p1,seg,dt,ms:string;
    i,m,k,pt:integer;
    t,t1:real; numbers:set of char;
label l1;
begin
assign(g,'res.asm'); reset(g); b1:='segment'; prov:=false;
assign(main,'1.asm'); reset(main);
assign(il,'idlist.txt'); rewrite(il);
assign(dataseg,'dataseg.asm'); rewrite(dataseg);
for i:= 48 to 57 do numbers:=numbers+[chr(i)]; i:=0;
while not eof(g) do begin
readln(g,s); readln(main,ms); i:=0;
while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
if b='segment' then seg:=a;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
if b1='db' then m:=m+1;
if b1='dw' then m:=m+2;
if b1='dd' then m:=m+4;
if (b1='db') and (c1[1]=chr(39)) and (c1[length(c1)]=chr(39)) then m:=m+length(c1)-3;
//if (b1='segment') or (b1='ends') or (b='ends') then m:=0;
if c='' then goto l1;
if (c[1]=chr(39)) and (c[length(c)]=chr(39)) then begin //текстовая константа для db
p1:=c; delete(p1,1,1); delete(p1,length(p1),1);
for i:=1 to length(p1) do begin
k:=ord(p1[i]); l:=hxd(k); delete(l,1,2); p:=p+l+' '; end; delete(p,length(p),1); end;
if (c[length(c)]='h') and (b='db') then begin //шестнадцатиричная система для db
p:=c; delete(p,length(p),1); end;
if (c[length(c)]='h') and (b='dw') then begin //шестнадцатиричная система для dw
p1:=c; delete(p1,length(p1),1); for i:=1 to 4-length(p1) do p:=p+'0'; p:=p+p1; end;
if (c[length(c)]='h') and (b='dd') then begin //шестнадцатиричная система для dd
p1:=c; delete(p1,length(p1),1); for i:=1 to 8-length(p1) do p:=p+'0'; p:=p+p1; end;
if (c[length(c)]='d') and (b='db') then begin //десятичная система для db
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); p:=hxd(pt); delete(p,1,2);
if (c[length(c)] in numbers) and (b='db') then begin
p1:=c; pt:=strtoint(p1); p:=hxd(pt); delete(p,1,2); end; end;
if (c[length(c)]='d') and (b='dw') then begin //десятичная система для dw
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); p:=hxd(pt); end;
if (c[length(c)] in numbers) and (b='dw') then begin
p1:=c; pt:=strtoint(p1); p:=hxd(pt) end;
if (c[length(c)]='d') and (b='dd') then begin //десятичная система для dd
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); prov:=true; p:=hxd(pt);
prov:=false; end;
if (c[length(c)] in numbers) and (b='dd') then begin
p1:=c; pt:=strtoint(p1); prov:=true; p:=hxd(pt);
prov:=false; end;
if (c[length(c)]='b') and (b='db') then begin //двоичная система для db
p1:=c; delete(p1,length(p1),1); p:=bintohex(p1); delete(p,1,2); end;
if (c[length(c)]='b') and (b='dw') then begin //двоичная система для dw
p1:=c; delete(p1,length(p1),1); p:=bintohex(p1); end;
if (c[length(c)]='b') and (b='dd') then begin //двоичная система для dd
p1:=c; delete(p1,length(p1),1); prov:=true; p:=bintohex(p1); prov:=false; end;
case b of
'db': dt:='byte';
'dw': dt:='word';
'dd': dt:='dword'; end;
if (b='db') or (b='dw') or (b='dd') then
writeln(il,a,' ',dt,'| ',hxd(m),' ',seg,'*');
l1:writeln(dataseg,hxd(m),' ',p,' ',ms);
if (a='data') and (b='ends') then break;
b1:=b; c1:=c;
a:=''; b:=''; c:=''; p:='';
end;

writeln('Data segment successfully analized!');

end;
begin
datasegment;
close(dataseg);close(g);
close(il); close(main);
readln;
end.
