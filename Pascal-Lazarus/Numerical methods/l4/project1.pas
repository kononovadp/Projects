Program lab4;
var a,b,s,s1,h,x,d,intg,intg1:real; fr:text;
i,n,k:integer;
function f(x:real):real;
begin
f:=x*(2*cos(x/2)-x/2*sin(x/2));
end;
procedure ing1(n:integer; var intg:real);
var s1,s2:real;
begin   s:=f(a)+f(b);
 h:=(b-a)/n;
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
a:=0; b:=36; n:=100;
ing1(n,intg);
repeat
n:=n*2;   //удваиваем кол-во
ing1(n,intg1);
d:=(1/15)*abs(intg-intg1);//ищем погрешность
writeln('steps ',n,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
writeln(fr,'steps ',n,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
intg:=intg1; //подготовка к следующему шагу (новые значения становятся старыми)
until  d<0.001;
intg:=36*36*cos(18); writeln('integral= ',intg:0:4); writeln(fr,'integral= ',intg:0:4);
readln; close(fr);
end.
