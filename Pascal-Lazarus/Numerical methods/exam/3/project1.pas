{Побудувати таблицю інтегральної кривої звичайного диференціального рівняння
x*y” + 2*y’ + x*y=0,  y(0)=1,  y’(0)=0, xe[0, 0.05] методом Ейлера з кроком h=0.01.}
Program ysov_metod_eilera;
uses crt;
var a,b,x,y,z,h:real;
i:integer;
function f(x,y,z:real):real; //вторая производная от ф-и
begin
f:=-2*z/x-y;
end;
Begin
clrscr;
{writeln('vvedite h-shag');
writeln('vvedite y nylevoe - y');
writeln('vvedite x nylevoe - a');
writeln('vvedite x kone4nyy to4ky - b');
readln(h,y,a,b);}
h:=0.01; y:=1; a:=0; b:=0.05;
x:=a;z:=0;
i:=0;
repeat
i:=i+1;  x:=x+h/2;
z:=z+h/2*f(x,y,z);  writeln(z);
y:=y+h*z;
x:=x+h/2;
writeln('x',i,'=',x:6:3,' ','y',i,'=',y:6:3);
until x>b;
readln;
End.

{program MetodEilera;
uses CRT;
var i,t:integer;
y,y1:array[0..11] of real;
h,x0,x1:real;
function F(x2,y2:real):real;
begin
F:=x2*y2+2*y2+x2*y2;
end;
begin
clrscr;
writeln('‚vvedem x0, y0:');
writeln;
x0:=1; y[0]:=0;
{write('x0=');
readln(x0);
write('y0=');
readln(y[0]);}
writeln; h:=0.01;
{writeln('‚vvedite shag:');
writeln;
readln(h);}
i:=0;
while x0<=2 do
begin
x1:=x0;
x1:=x1+h/2;
y1[i]:=y[i]+h/2*F(x0,y[i]);
y[i+1]:=y[i]+h*F(x1,y1[i]);
x0:=x0+h;
i:=i+1;
end;
writeln;
writeln(' y(x)');
writeln;
for t:=0 to i do
writeln(y[t]:10:6);
readln;
end. }
