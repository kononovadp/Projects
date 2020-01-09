{За допомогою узагальненої формули Сімпсона обчислити визначений інтеграл
f(1:10)-((10+10*ln(x))*x+10*ln(x)*x)*1/3 з точністю не гірше за 10^-5.}
Program lab4;
var a,b,s,s1,h,x,d,intg,intg1,m,intgT:real; fr:text;
i,n,k:integer;
function f(x:real):real;
begin
f:= -exp(x)*(sin(x)+cos(x))/64;
end;
procedure ing1(n:integer; var intg:real);
var s1,s2:real;
begin   s:=f(a)+f(b);

x:=a+h;
for i:=0 to n div 2-1 do
begin s1:=s1+f(x); x:=x+h;
      s2:=s2+f(x); x:=x+h;
end;
s:=s+4*s1+2*s2;
intg:=h/3*s;
end;
begin
assign(fr,'res.txt'); rewrite(fr);



a:=2; b:=10;
x:=a;
//удвоенный перерассчет
n:=100;
h:=(b-a)/n;
ing1(n,intg);
writeln('Double recalculation');
repeat
n:=n*2;   //удваиваем кол-во
h:=(b-a)/n;
ing1(n,intg1);
d:=(1/15)*abs(intg-intg1);//ищем погрешность
writeln('step ',h:5:5,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
writeln(fr,'step ',h:5:5,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
intg:=intg1; //подготовка к следующему шагу (новые значения становятся старыми)
until  d<0.001;
readln; close(fr);
end.
