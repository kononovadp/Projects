{За допомогою метод прогону обчислити корені системи лінійних рівнянь
107x0 + 78x1 + 0x2 + 0x3 + 0x4  = 2706
19x0 + 11x1 + 82x2 + 0x3 + 0x4  = 862
0x0 + 20x1 + 59x2 + 20x3 + 0x4  = 915
0x0 + 0x1 + 37x2 + 72x3 + 96x4  = 3809
0x0 + 0x1 + 0x2 + 109x3 + 223x4  = 7195}
program lalala;
const n=5;
var i,j:integer;
a:array[1..n,1..n] of real;
b,x,k,m,t,p,q:array[1..n] of real;
tmp:real;
begin
A[1, 1] := 107; A[1, 2] := 78;  A[1, 3] := 0;  A[1, 4] := 0; A[1, 5] := 0;
A[2, 1] := 19;  A[2, 2] := 11; A[2, 3] := 82; A[2, 4] := 0; A[2, 5] := 0;
A[3, 1] := 0;  A[3, 2] := 20;  A[3, 3] := 59; A[3, 4] := 20; A[3, 5] := 0;
A[4, 1] := 0;  A[4, 2] := 0;   A[4, 3] := 37; A[4, 4] := 72; A[4, 5] := 96;
A[5, 1] := 0;  A[5, 2] := 0;  A[5, 3] := 0;  A[5, 4] := 109; A[5, 5] := 223;
b[1] := 2706; b[2] :=862; b[3] := 915; b[4] := 3809; b[5] := 7195;
{for i:=1 to n do
    begin
    for j:=1 to n do
        begin
        write('a(',i,',',j,')=');
        readln(a[i,j]);
        end;
    write('b(',i,')=');
    readln(b[i]);
    end;}

for i:=1 to n do
    begin
    if i=1 then
       k[i]:=0
    else
        k[i]:=a[i,i-1];
        m[i]:=-a[i,i];
    if i=n then
        t[i]:=0
    else
        t[i]:=a[i,i+1];
    end;

p[1]:=t[1]/m[1];
q[1]:=-b[1]/m[1];
for i:=2 to n do
    begin
    p[i]:=-t[i]/(k[i]*p[i-1]-m[i]);
    q[i]:=(b[i]-k[i]*q[i-1])/(k[i]*p[i-1]-m[i]);
    end;

x[n]:=(b[n]-k[n]*q[n-1])/(k[n]*p[n-1]-m[n]);
for i:=n-1 downto 1 do
    x[i]:=p[i]*x[i+1]+q[i];

for i:=1 to n do
    writeln('x(',i,')=',x[i]:5:2);  readln;
end.
