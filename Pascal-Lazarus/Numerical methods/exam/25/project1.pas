{За допомогою інтерполяційного полінома Лагранжа, побудованого на проміжку
 [1;9], обчислити значення функції
0.02*exp(x)*sin(3*x)
в точках [1.45, 2.33, 6.5, 7.7, 8.8] з точністю не гірше за 10^-2.}
Uses crt;
Const nmax = 100;
Var n,k,m,I,j : integer;
    ct,u:real;
    x,y,r,pt:array[1..nmax] of real;
 function f(x:real):real;
 begin
   f:= 0.2*exp(x)*sin(3*x);
 end;

begin
n:=5;
x[1]:=  1.45;
x[2]:=2.33;
x[3]:=6.5;
x[4]:=7.7;
x[5]:=8.8;
{repeat
write('Число узлов интерполирования от 2 до ',nmax,' n=');
readln(n);
until n in [2..nmax];
writeln('Введите массив узлов интерполирования:');
for i:=1 to n do
 begin
  write('x[',i,']=');
  readln(x[i]);
 end;
writeln('Введите массив значений функции в узлах:');   }
for i:=1 to n do
 y[i]:=f(x[i]);

writeln('Array of components:'); //массив узлов
for i:=1 to n do
write(x[i]:6:4,' ');
writeln;
writeln;
writeln('array of values:');
for i:=1 to n do
write(y[i]:6:4,' ');
writeln;
writeln;
for i:=1 to n do R[i]:=0;
for i:=1 to n do
 begin
  ct:=1;pt[1]:=1;k:=1;
  for j:=1 to n do
  if i<>j then
   begin
    ct:=ct*(x[i]-x[j]);
    pt[k+1]:=1;
    if k>1 then
    for m:=k downto 2 do
    pt[m]:=pt[m-1]-pt[m]*x[j];
    pt[1]:=-pt[1]*x[j];
    k:=k+1;
   end;
  u:=y[i]/ct;
  for m:=1 to n do
  r[m]:=r[m]+pt[m]*u;
 end;
writeln('Array cof:');
for i:=1 to n do
write('R[', i, ']=', r[i]:6:4,' ');
readln
end.

