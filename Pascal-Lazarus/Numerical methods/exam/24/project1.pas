{Побудувати таблицю інтегральної кривої звичайного диференціального рівняння
xy’=yln(y/x) f=yln(y/x)/x з початковими умовами y(1) = exp(3)
на проміжку a = 1, b = 3 з кроком (b - a)/5 і з точністю не гірше за 10-2.}
uses crt;
function fxy(x, y: Real): Real;
begin
fxy:=y*ln(y/x);
end;
function f(x:real):real;//точное значение, рассчитанное отдельно
begin
f:=0;
end;

const
a=1; b=3;
//x0=0;
//y0=0;//1;??????????????????????
//h=0.0001;//0.2;
n=50000;
var
x, ye, yem, z, yr, k1, k2, k3, k4,h: Real;
i: Integer;
begin
h:=(b-a)/50000;
x:=a;//x0;
ye:=exp(3);
Writeln('   x    |     y');
for i:=0 to n do
begin
ye:=ye+h*fxy(x, ye);
if i mod 10000=0 then
Writeln(x:5:3,'   |',ye:10:5,'  |  ',f(x):10:5,' |  ', f(x)-ye:5:10);
x:=x+h;
end;
readln;
end.
