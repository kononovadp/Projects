{За допомогою методу послідовних наближень обчислити корінь рівняння
3.0 / (2 + cos(x)) + x/1.5 = 0
з точністю не гірше за 10^-7.}
function pow(var base:real; n:integer):real;
var
i:byte;
begin
pow := 1;
for i:=1 to n do
pow := pow*base;
end;
function f(x:real):real;
var k:real;
begin
k:=-0.5;
f:= x+k*(3.0/(2 + cos(x))+x/3*2);//(N-1)/N*x + A/(N*pow(x,n-1));
end;
var
x1,x2,A:real;
Eps:real;
n:integer;
begin
Eps := 1E-7;
A   := 0.45;
n   := 2;
x2  := -1000;
repeat
x1 := x2;
x2 := f(x1);
writeln(x1:5:8,'     ',x2:5:8);
until (abs(x1-x2) <= Eps);
writeln;
writeln(f(x1):0:8,'   ',f(x1)-x1:0:10);    readln;
end.
