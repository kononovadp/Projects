Program ProcedureType;
var a,b,s,s1,h,x,d,intg,intg1:real;
i,n,k:integer;
{function ArcCos(X:Extended):Extended;
BEGIN
    IF ROUND(X*10000000)=10000000 THEN ArcCos:=0 ELSE
    IF ROUND(X*10000000)=-10000000 THEN ArcCos:=Pi ELSE
    ArcCos:=(Pi/2)-ArcTan(X/SQRT(1-X*X));
END;}
function f(x:real):real;
begin
f:=arctan(1/(1+sqrt(x))+sin(x));
end;//оскільки ф-я arccos(1/(1+sqrt(x))+sin(x)) не існує, вона була замінена на ф-ю arctan(1/(1+sqrt(x))+sin(x));
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
a:=0; b:=4; n:=10;    s:=(f(a)+f(b))/2;
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
until  d<0.001;
readln;
end.
