Program ProcedureType;
type func=function(x:real):real;
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
end;
function igs1(n:integer;f:func):real;
begin
x:=a+h;
for i:=1 to n-1 do
begin   s:=s+f(x); x:=x+h;end;
igs1:=s;
end;
function igs2(n:integer;f:func):real;
begin
x:=a+h; 
for i:=1 to n div 2 do 
begin
  s1:=s1+f(x);
  x:=x+2*h; 
end;
 igs2:=s;
end;
begin
a:=0; b:=4; n:=10; s:=(f(a)+f(b))/2;
 h:=(b-a)/n;
 s:=igs1(n,f);
s1:=s; 
intg1:=s1*h;
repeat
 n:=n*2;  h:=(b-a)/n;
  s:=igs2(n,f);
intg:=s*h;
d:=(1/3)*abs(intg-intg1);
writeln('steps=',n,'  integral= ',intg1:0:4,'  miscalculation= ',d:5:5);
s:=s1; intg:=intg1; 
until  d<0.001;
readln;
end.