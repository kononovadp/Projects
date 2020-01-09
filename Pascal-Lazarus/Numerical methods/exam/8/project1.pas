{За допомогою виключення Гаусса-Жордана обчислити корені системи лінійних рівнянь
154x0 + 79x1 + 1x2 + 58x3 + 12x4  = 882
22x0 + 188x1 + 86x2 + 46x3 + 31x4  = 1214
9x0 + 23x1 + 176x2 + 82x3 + 58x4  = 906
30x0 + 75x1 + 99x2 + 267x3 + 62x4  = 1750
40x0 + 55x1 + 15x2 + 72x3 + 185x4  = 988 }
uses crt;
const n=5;
type T=real;
var a:array [1..n,1..n+1] of T;
x:array [1..n] of real;
i,j,k:integer;
r:real;
begin
A[1, 1] := 154; A[1, 2] := 79;  A[1, 3] := 1;  A[1, 4] := 58; A[1, 5] := 12;
A[2, 1] := 22;  A[2, 2] := 188; A[2, 3] := 86; A[2, 4] := 46; A[2, 5] := 31;
A[3, 1] := 9;   A[3, 2] := 23;  A[3, 3] := 176; A[3, 4] := 82; A[3, 5] := 58;
A[4, 1] := 30;  A[4, 2] := 75;   A[4, 3] := 99; A[4, 4] := 267; A[4, 5] := 62;
A[5, 1] := 40;  A[5, 2] := 55;  A[5, 3] := 15;  A[5, 4] := 72; A[5, 5] := 185;
A[1, 6] := 882; A[2, 6] :=1214; A[3, 6] := 906; A[4, 6] := 1750; A[5, 6] := 988;
{for i:=1 to n do
for j:=1 to n+1 do
begin
Writeln('Введите ',j,' элемент ',i,' строки');
read(a[i,j]);
end;}
for k:=1 to n do
begin
for j:=k+1 to n+1 do
if a[k,k]<>0 then
a[k,j]:=a[k,j]/a[k,k];
for i:=k+1 to n do
for j:=k+1 to n+1 do
a[i,j]:=a[i,j]-a[k,j]*a[i,k];
x[n]:=a[n,n+1];
end;
for k:=n-1 downto 1 do
begin
r:=0;
for j:=n downto k+1 do
r:=r+a[k,j]*x[j];
x[k]:=a[k,n+1]-r;
end;
writeln('roots of equations:');
for i:=1 to n do
write(i:3,' root: ',x[i]:1:1,';');
readln;
end.
