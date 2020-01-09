{Побудувати таблицю інтегральної кривої звичайного диференціального рівняння
y’-3y/x = x з початковими умовами y(1) = 1 на проміжку a = 1, b = 5 з кроком
(b - a)/5 і з точністю не гірше за 10^-4.}
uses crt;
function fxy(x, y: Real): Real;
begin
fxy:=x+3*y/x;
end;
function f(x:real):real;//точное решение уравнения
begin
f:=(2-1/x)*x*x*x;
end;

const
a=1; b=5;
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
ye:=1;
{yem:=1;
yr:=1;}
Writeln('   x    |     y');
for i:=0 to n do
begin

{Эйлер}
ye:=ye+h*fxy(x, ye);

if i mod 10000=0 then
Writeln(x:5:3,'   |',ye:10:5,'  |  ',f(x):10:5,' |  ', f(x)-ye:5:10);
{Эйлер +}
{z:=fxy(x, yem);
yem:=yem+h/2*(z+fxy(x, yem+h*z));
{Рунге-Кутты}
k1:=h*fxy(x, yr);
k2:=h*fxy(x+h/2, yr+k1/2);
k3:=h*fxy(x+h/2, yr+k2/2);
k4:=h*fxy(x+h, yr+k3);
yr:=yr+(k1+2*k2+2*k3+k4)/6;  }
x:=x+h;
end;
readln;
end.
