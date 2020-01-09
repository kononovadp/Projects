{За допомогою узагальненої формули трапецій обчислити визначений інтеграл
f:2:7(1+ln(x))*sin(x)+ln(x)*x*cos(x)}
var a,b,s,s1,h,x,d,intg,intg1:real;
i,n,k:integer;
function f(x:real):real;
begin
f:=(1+ln(x))*sin(x)+ln(x)*x*cos(x);
end;
procedure ing1(n:integer; var s,intg:real);
begin
 h:=(b-a)/n;
x:=a+h;
for i:=1 to n-1 do
begin   s:=s+f(x); x:=x+h;end;
intg:=s*h;
writeln('pri n=',n,'  integral= ',intg:0:4);
end;
begin
a:=2; b:=7; n:=10;    s:=(f(a)+f(b))/2;
//обчислення і-го значення интеграла
s1:=s; //запам'ятовування сумми
repeat
 n:=n*2;
 h:=(b-a)/n; //подвоєння кількості та розрахунок нового кроку
 x:=a+h; //переміщення в першу точку
for i:=1 to n div 2 do //рух по непарним точкам
begin
  s1:=s1+f(x);
  x:=x+2*h; //подвійний крок для "перестрибування парних точок"
end;
intg1:=s1*h;
d:=(1/3)*abs(intg-intg1);//обчислення похибки
writeln('steps=',n,'  integral= ',intg1:0:4,'  miscalculation= ',d:5:5);
s:=s1; intg:=intg1; //підготовка до наступного кроку
until  d<0.0001;
readln;
end.
