{Побудувати таблицю інтегральної кривої звичайного диференціального рівняння
y” + x*y’ = e-sqr( x),  y(0)=1,  y’(0)=0, x[0, 1]
методом Эйлера-Коши с кроком h=0.01.}
Program eiler_Koshi;
uses crt;
var z,x,y,a,b,h:real;i:integer;
function f(x,y,z:real):real;
begin f:= -x*z+exp(1)-sqr(x); end;{Opisanie funkcii}
begin
{clrscr;
writeln('y-Na4alna9a to4ka y');
writeln('a-Na4alna9a to4ka x');
writeln('b-Kone4na9a to4ka x');
writeln('h-Shag');
writeln('VVedite y, a, b, h');
readln(y,a,b,h); }
a:=0; b:=1; y:=1; z:=0;h:=0.1;
x:=a;
i:=0;
repeat
i:=i+1;
y:=y+h*z;
z:=z+h*f(x,y,z);
x:=x+h;
writeln('x',i,'=',x:0:2,' ','y',i,'=',y:0:2);
until x>b-h; readln;
end.
