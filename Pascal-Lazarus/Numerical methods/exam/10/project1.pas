{За допомогою інтерполяційного полінома Лагранжа, побудованого на проміжку
 [1;15], обчислити значення функції
5*ln(x)*sin(x)*sin(x)
в точках [1.45, 4.33, 6.5, 11.7, 14.8] з точністю не гірше за 10-4.}
Uses crt;
Const nmax = 100;
Var n,k,m,I,j : integer;
    ct,u:real;
    x,y,r,pt:array[1..nmax] of real;
 function f(x:real):real;
 begin
   f:= 5*ln(x)*sin(x)*sin(x)  ;
 end;

begin
clrscr;   n:=5;
x[1]:=  1.45;
x[2]:=4.33;
x[3]:=6.5;
x[4]:=11.7;
x[5]:=14.8;
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

writeln('Массив узлов:');
for i:=1 to n do
write(x[i]:6:4,' ');
writeln;
writeln;
writeln('Массив значений:');
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
