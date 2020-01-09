Program P2;
type proc = procedure (n:integer;var s,intg:real);
var a,b,s,s1,h,x,d,intg,intg1:real;
i,n,k:integer;        integ:proc;

  function f(x:real):real;  far;
begin
f:=arctan(1/(1+sqrt(x))+sin(x));
end;

procedure ing1(n:integer; var s,intg:real); far;
begin
 h:=(b-a)/n;
x:=a+h;
for i:=1 to n-1 do
begin   s:=s+f(x); x:=x+h;end;
intg:=s*h;
writeln('pri n=',n,'  integral= ',intg:0:4);
end;




begin
a:=0; b:=4; n:=10;    s:=(f(a)+f(b))/2;
//вычисляем 1-е значение интеграла
 integ:=ing1;
integ(n,s,intg);
s1:=s; //запоминаем сумму
repeat
 n:=n*2;
 h:=(b-a)/n;  //удваиваем кол-во и рассчитываем новый шаг
 x:=a+h;   //перемещаемся в первую точку
for i:=1 to n div 2 do  //двигаемся по нечетным точкам
begin
  s1:=s1+f(x);
  x:=x+2*h; //перепрыгиваем через четные точки(поэтому двойной шаг)
end;
intg1:=s1*h;
d:=(1/3)*abs(intg-intg1);//ищем погрешность
writeln('pri n=',n,'  integral= ',intg1:0:4,'  d= ',d:5:5);
s:=s1; intg:=intg1; //подготовка к следующему шагу (новые значения становятся старыми)
until  d<0.001;
readln;
end.
