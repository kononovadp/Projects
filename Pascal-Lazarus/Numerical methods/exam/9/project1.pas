{За допомогою узагальненої формули Сімпсона обчислити визначений інтеграл
f(1:10)-((10+10*ln(x))*x+10*ln(x)*x)*1/3}
uses crt;
label xx2,xy2;
var i1,i2,x1,x2,x0,s,y0,y1,y2,a,b,h,x,s0,s1,n,e: real;
i: integer;
function f(x: real): real;
begin
f:=-((10+10*ln(x))*x+10*ln(x)*x)*(1/3);
end;
begin
clrscr;
{writeln('Границы a/b: '); //как раз от 0 до 1
readln(a,b);} a:=1; b:=10;
e:=0.001;//точность
i1:=0;
n:=4;
h:=(b-a)/4 ;
xy2:
 i2:=0;
i:=2;
xx2:
x2:=a+i*h;
x1:=x2-h;
x0:=x1-h;
y0:=f(x0);
y1:=f(x1);
y2:=f(x2);
s:=y0+4*y1+y2;
i2:=i2+s;
if i<n then
begin
i:=i+2;
goto xx2;
end
else
begin
i2:=i2*h/3;
if abs(i1-i2)<e then
writeln('Result: ',i2:3:2)
else
begin
i1:=i2;
n:=n*2;
h:=h/2;
goto xy2;
end;
end;
readln;
end.
