{За допомогою методу дотичних обчислити корінь рівняння
x*x*x -10*cos(x)- 5 = 0 з точністю не гірше за 10^-7. }
uses Crt;
var x,a,b,e: double;
function f1(z: double): double; {Основная функция}
begin
f1:= x*x*x-10*cos(x)-5;
end;
function f2(z:double): double; {Производная от основной функции}
begin
f2:=3*x*x-10-sin(x);
end;
begin
Clrscr;
a:=2;b:=3;
e:=0.0001;
clrscr;
if f1(a)*f2(a)>0 then x:=a
else x:=b;
while abs(f1(x))>e do
begin
x:=x-f1(x)/f2(x);
end;
Writeln (' V intervale ot ',a:0:0,' do ',b:0:0,' s pogr ',e:0:5);
Writeln ('x=',x:0:5,' f(x)=',f1(x):0:5);
Readln
end.
