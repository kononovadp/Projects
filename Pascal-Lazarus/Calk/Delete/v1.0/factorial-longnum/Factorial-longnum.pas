uses crt;
const nmax=1024;
type ts = 0..9;
chislo=array[1..nmax] of ts;
procedure nul(var a:chislo);
var i:integer;
begin
for i:=1 to nmax do
a[i]:=0;
end;
procedure perevod(s:string;var a:chislo);
var i,n :1..nmax;
begin
n:=length(s);
nul(a);
for i:=1 to n do
a[n-i+1]:=ord(s[i])-ord('0');
end;
function kol(const a: chislo):integer;
var i:1..nmax;
begin
i:=nmax;
while(a[i]=0)and(i>1) do
i:=i-1;
kol:=i;
end;
procedure umn(var a,b,c:chislo);
var i,g,n,m:1..nmax; p:0..9; v:byte;
begin
nul(c);
m:=kol(a);
n:=kol(b);
for i:=1 to m do
begin
p:=0;
for g:=1 to n do
begin
v:=a[i]*b[g]+p+c[i+g-1];
c[i+g-1]:=v mod 10;
p:=v div 10;
end;
c[i+n]:=p;
end;
end;
procedure pechat(var a : chislo);
var i:1..nmax;
begin
for i:=kol(a) downto 1 do
write(a[i]);
writeln;
end;
procedure sum(a,b:chislo;var c:chislo);
var i,j,r:longint; p:0..9;
begin
p:=0;
for j:=1 to kol(a) do
begin
r:=b[j]+a[j]+p;
p:=r div 10;
c[j]:=r mod 10;
end;
c[j+1]:=p;
end;
var s:string; a,b,c,d,q:chislo; i,n,f:integer;
begin
clrscr;
write('Factorial ');
readln(n);
nul(b);
b[1]:=1;
nul(c);
nul(a);
a[1]:=1;
c[1]:=1;
d[1]:=1;
for i:=2 to n do
begin
for f:=1 to nmax do
a[f]:=c[f];
sum(a,d,c);
umn(b,c,q);
for f:=1 to nmax do
b[f]:=q[f];
end;
pechat(q);
readln
end.