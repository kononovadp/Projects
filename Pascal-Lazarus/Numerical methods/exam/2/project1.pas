{За допомогою cхеми єдиного поділу обчислити корені системи лінійних рівнянь
134x0 + 27x1 + 40x2 + 49x3 + 17x4  = 3044
86x0 + 249x1 + 107x2 + 50x3 + 3x4  = 5446
14x0 + 13x1 + 134x2 + 86x3 + 19x4  = 3384
89x0 + 9x1 + 119x2 + 245x3 + 24x4  = 6514
14x0 + 43x1 + 36x2 + 102x3 + 197x4  = 6728}
uses
crt;
const
e = 0.000001; { точность вычислений }
var
a,a1: array[1..10, 1..10] of real;
b,b1: array[1..10] of real;
x: array[1..10] of real;
n, i, j, k: integer;z, r, g: real;
begin
clrscr;
n:=5;
A[1, 1] := 134; A[1, 2] := 27;  A[1, 3] := 40;  A[1, 4] := 49; A[1, 5] := 17;
A[2, 1] := 86;  A[2, 2] := 249; A[2, 3] := 107; A[2, 4] := 50; A[2, 5] := 3;
A[3, 1] := 14;  A[3, 2] := 13;  A[3, 3] := 134; A[3, 4] := 86; A[3, 5] := 19;
A[4, 1] := 89;  A[4, 2] := 9;   A[4, 3] := 119; A[4, 4] := 245; A[4, 5] := 24;
A[5, 1] := 14;  A[5, 2] := 43;  A[5, 3] := 36;  A[5, 4] := 102; A[5, 5] := 197;
b[1] := 3044; b[2] :=5446; b[3] := 3384; b[4] := 6514; b[5] := 6728;
writeln('Matrix A: ');
for i := 1 to n do
begin
for j := 1 to n do
begin
write(a[i,j]:5:2);
a1[i,j]:=a[i,j];
end;
writeln;
end;
writeln;
Writeln('Matrix B: ');
for i:=1 to n do
writeln(b[i]:5:2);
for k := 1 to n do { прямой ход Гаусса }
begin
for j := k + 1 to n do
begin
r := a[j, k] / a[k, k];
for i := k to n do
begin
a[j, i] := a[j, i] - r * a[k, i];
end;
b[j] := b[j] - r * b[k];
end;
end;
for k := n downto 1 do { обратный ход Гаусса }
begin
r := 0;
for j := k + 1 to n do
begin
g := a[k, j] * x[j];
r := r + g;
end;
x[k] := (b[k] - r) / a[k, k];
end;
writeln('Roots of the system:');
for i := 1 to n do
write('x', i, '=', x[i]:0:2, '   ');
readln;
end.
