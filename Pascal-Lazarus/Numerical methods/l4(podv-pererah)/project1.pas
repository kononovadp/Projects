Program lab4;
var a,b,s,s1,h,x,d,intg,intg1,m,intgT:real; fr:text;
i,n,k:integer;
function f(x:real):real;
begin
f:=x*(2*cos(x/2)-x/2*sin(x/2));
end;
function f4(x:real):real;
begin
f4:=abs(2*cos(x/2)+x*(0.5*(-0.5*(x*cos(x/2))-sin(x/2))-sin(x/2))-0.5*x*sin(x/2));
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
writeln('Exact integral value'); writeln(fr,'Exact integral value');
intgT:=36*36*cos(18);
writeln('integralT= ',intgT:0:4); writeln(fr,'integralT= ',intgT:0:4);
a:=0; b:=36;
x:=a; m:=f4(a);
while x<=b do begin if abs(f4(x))>m then m:=abs(f4(x)); x:=x+0.001; end;
h:=0.00001*180/(b-a)/m;
h:=sqrt(sqrt(h));  n:=round((b-a)/h);
h:=(b-a)/n;
ing1(n,intg);  d:=intgT-intg;
writeln('Integral Simpson'); writeln(fr,'Integral Simpson');
writeln('step ',h:5:5,' integral= ',intg:0:4,' inaccuracy= ',d:5:5);
writeln(fr,'step ',h:5:5,' integral= ',intg:0:4,' inaccuracy= ',d:5:5);
//удвоенный перерассчет
n:=100;
h:=(b-a)/n;
ing1(n,intg);
writeln('Double recalculation'); writeln(fr,'Double recalculation');
repeat
n:=n*2;   //удваиваем кол-во
h:=(b-a)/n;
ing1(n,intg1);
d:=(1/15)*abs(intg-intg1);//ищем погрешность
writeln('step ',h:5:5,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
writeln(fr,'step ',h:5:5,' integral= ',intg1:0:4,' inaccuracy= ',d:5:5);
intg:=intg1; //подготовка к следующему шагу (новые значения становятся старыми)
until  d<0.001;
close(fr);
writeln('All results were written in text file!'); readln;
end.
