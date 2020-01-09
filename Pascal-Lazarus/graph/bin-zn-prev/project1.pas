uses sysutils;
var s,p:string; w:boolean;
function bintodec(s:string):string;
var n,i,k,b,r,j:integer; b1:boolean;
begin
b1:=false;
if s[1]='-' then begin delete(s,1,1); b1:=true; end;
k:= length(s); i:=1; b:=1;
for i:=2 to k do b:=b*2+strtoint(s[i]);
bintodec:=inttostr(b);
if b1=true then bintodec:='-'+bintodec;end;

function compare(s1,s2:string):string;
var i:byte; a,b,t:integer;
begin
if s1=s2 then begin compare:='full equal'; exit;
end else begin
a:=0; b:=0;
for i:=1 to length(s1) do
if s1[i]='1' then begin
t:=pos('1',s1); a:=a+t; end;
for i:=1 to length(s2) do
if s2[i]='1' then begin
t:=pos('1',s2); b:=b+t; end;
if a>b then compare:='s1>s2';
if a<b then compare:='s1<s2';
if a=b then compare:='s1=s2'; end;
end;

function addcode(s:string):string;
var i,c,d,r,p:byte; s2,t:string;
begin
for i:=1 to length(s) do
case s[i] of
'1': s[i]:='0';
'0': s[i]:='1'; end;
i:=length(s);
for c:=1 to i-1 do s2:=s2+'0';
s2:=s2+'1';
p:=0;
while i>0 do begin
c:=strtoint(s[i]); d:=strtoint(s2[i]);
i:=i-1;
r:=c+d+p;
p:=r div 2;
r:=r mod 2;
t:=inttostr(r)+t;
end;
if p=1 then t:=inttostr(p)+t;
//i:=pos('1',t); if i>1 then delete(t,1,i-1);
addcode:=t;
end;

function binplus(s1,s2:string):string;
var i,c,d,r,p:byte; b1,b2:boolean;
rs,t:string;
begin b1:=false;
//обработка знака (вариант 1)
{if (s1[1]='-') or (s2[1]='-') then begin
if (s1[1]='-') and (s2[1]='-') //-255+(-255)
then begin b1:=true;
delete(s1,1,1); delete(s2,1,1); end;
//===========
if (s1[1]='-') and (s2[1]<>'-') then begin
delete(s1,1,1); rs:=compare(s1,s2);
if rs='s1>s2' then b1:=true; //-255+250
if rs='s1<s2' then begin //-250+255
t:=s1; s1:=s2; s2:=t; end;
if rs='full equal' then delete(s1,1,1);
t:=addcode(s2); s2:=t; end;
//===========
if (s1[1]<>'-') and (s2[1]='-') then begin
delete(s2,1,1); rs:=compare(s1,s2);
if rs='s1<s2' then begin //250+(-255)
t:=s1; s1:=s2; s2:=t; b1:=true; end;
if rs='full equal' then delete(s1,1,1);
t:=addcode(s2); s2:=t; end;
end;}
//обработка знака (вариант 2 проще)
if (s1[1]='-') or (s2[1]='-') then begin
if (s1[1]<>'-') and (s2[1]<>'-') then begin
t:=compare(s1,s2); if t='s1<s2' then begin
t:=s1; s1:=s2; s2:=t; b1:=true; end; end;
if (s1[1]<>'-') and (s2[1]='-') then b2:=true;
if s1[1]='-' then begin delete(s1,1,1); s1:=addcode(s1); end;
if s2[1]='-' then begin delete(s2,1,1); s2:=addcode(s2); end;
end;
//выравнивание строк
if length(s1)<>length(s2) then
   if length(s1)<length(s2) then
   for i:=1 to length(s2)-length(s1) do s1:='0'+s1 else
   for i:=1 to length(s1)-length(s2) do s2:='0'+s2;
//сложение
i:=length(s1); p:=0;
while i>0 do begin
c:=strtoint(s1[i]); d:=strtoint(s2[i]);
i:=i-1;
r:=c+d+p;
p:=r div 2;
r:=r mod 2;
binplus:=inttostr(r)+binplus;
end;
if p=1 then binplus:=inttostr(p)+binplus;
if b1=true then binplus:=addcode(binplus);
if length(binplus)>length(s1) then delete(binplus,1,1);
i:=pos('1',binplus); if i>1 then delete(binplus,1,i-1);
if i=0 then binplus:='0';
end;
function binminus(s1,s2:string):string;
var a,b,t:string; i:byte; b1,b2:boolean;
begin b1:=false; b2:=false;
//обработка знака
if (s1[1]='-') or (s2[1]='-') then begin
if (s1[1]<>'-') and (s2[1]<>'-') then begin
t:=compare(s1,s2); if t='s1<s2' then begin
t:=s1; s1:=s2; s2:=t; b1:=true; end; end;
if (s1[1]<>'-') and (s2[1]='-') then b2:=true;
if s1[1]='-' then begin delete(s1,1,1); s1:=addcode(s1); end;
if s2[1]='-' then begin delete(s2,1,1); s2:=addcode(s2); end;
end;
//выравнивание строк
if length(s1)<>length(s2) then
   if length(s1)<length(s2) then
   for i:=1 to length(s2)-length(s1) do s1:='0'+s1 else
   for i:=1 to length(s1)-length(s2) do s2:='0'+s2;
//отнимание
a:=addcode(s2); b:=(binplus(s1,a));
if length(b)<length(s1) then
for i:=1 to length(s1)-length(b) do b:='0'+b;
if (length(b)=length(s1)+1) and (b2=false) then delete(b,1,1);
if b1=true then b:=addcode(b);
i:=pos('1',b); if i>1 then delete(b,1,i-1);
binminus:=b; end;

function binmult(a,b:string):string;
var r:string; i:byte; c:integer;
begin
c:=length(a)*2;
for i:=1 to c do r:=r+'0';
for i:=1 to length(a) do a:='0'+a;
for i:=1 to length(b) do b:='0'+b;
while c>0 do begin
if a[c]='1' then r:=binplus(b,r);
b:=b+'0'; r:='0'+r;
dec(c);
end;
i:=pos('1',r);
if i>1 then delete(r,1,i-1);
binmult:=r; end;
begin
s:='11111010'; p:='11111111';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='-11111111'; p:='-11111010';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='-11111010'; p:='-11111111';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='-11111111'; p:='11111010';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='-11111010'; p:='11111111';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='11111111'; p:='-11111010';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
s:='11111010'; p:='-11111111';
writeln(bintodec(s),' - ',bintodec(p),' = ',binminus(s,p));
writeln('-----------------------------------------------');
//проверка сложения
s:='11111010'; p:='11111111';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='-11111111'; p:='-11111010';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='-11111010'; p:='-11111111';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='-11111111'; p:='11111010';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='-11111010'; p:='11111111';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='11111111'; p:='-11111010';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
s:='11111010'; p:='-11111111';
writeln(bintodec(s),' + ',bintodec(p),' = ',binplus(s,p));
writeln('-----------------------------------------------');
//проверка умножения
s:='11111010'; p:='11111111';
writeln(bintodec(s),' * ',bintodec(p),' = ',binmult(s,p));
readln;
end.

