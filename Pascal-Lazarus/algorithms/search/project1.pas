//поиск в массиве
var n,i,j,w,k,p:integer; a,b:array[0..10000] of char; f:text;
ch:char; s:string;
{procedure delarrel;
var i:byte; b:array[0..10000] of char;
begin //for i:=1 to n do b:=b+a[i];
for i:=0 to n do a[i]:=a[i+1];
a:=b; end;}
begin n:=0;
s:='ma'; for i:=1 to length(s) do b:=b+s[i];
assign(f,'1.txt'); reset(f);
while not(eof(f)) do begin read(f,ch);
inc(n); a:=a+ch; end;
for i:=0 to n do write(a[i]);
a:=a+'*';//из-за проблемы на последнем символе
writeln; writeln('-----------');
k:=0; w:=0;
while n>length(s)-1 do begin
for i:=0 to length(s) do
if a[i]=b[i] then inc(k);
if k=length(s) then inc(w);
for j:=0 to n do a[j]:=a[j+1];
dec(n); k:=0; end;
writeln('number of words<',s,'> ',w);
close(f); readln; end.
//поиск в строке
{var s,p,r:string; i,n,c:byte;
begin n:=0;
s:='1234512367812391230'; writeln(s);
p:='123';
r:=copy(s,1,length(p)); i:=length(r);
while i<length(s) do begin
if r=p then begin inc(n); writeln('position of the found word:  ',i-length(p)+1); end;
inc(i); r:=r+s[i]; delete(r,1,1); end;
writeln('number of found words:  ',n);
readln; end.}

//temp
{var n:int64;   i,k,j,p:integer;
f:text; ch:char;
a,b,r,t:array [0..10000] of char; s:string;
begin s:='ma'; for i:=0 to length(s) do b:=b+s[i];
assign(f,'1.txt'); reset(f);
while not eof(f) do begin read(f,ch); inc(n);
a:=a+ch; end;
for i:=0 to n do begin //write(a[i]);
for j:=0 to length(s) do
if a[j]=b[j] then inc(k); writeln(k);
if k=length(s) then inc(p);
k:=0; end;
writeln(p);
readln; close(f); end.}

