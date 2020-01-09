uses crt;
const max_iter=100; e=0.000001;
var a,b,q,f1,f2,x0,en,x: real; ftn,fti:text;
    i,k,exp1: integer;
//интерваллы содержащие корень: (-2,-1.5),(-1,-0.5), (0,0.5)
function f(x: real): real;
begin
 f:=exp(x)-3*cos(2*x)+2*x+1;
end;
function f1p(x:real):real;{первая производная функции f}
begin
 f1p:= exp(x)+6*sin(2*x)+2;
end;
function f2p(x:real):real;{вторая производная функции f}
begin
 f2p:= exp(x)+12*cos(2*x);
end;
function fi(x:real):real;{Первая производная функции f}
begin
 fi:= 1/3*x-1/3*exp(x)+cos(2*x)-1/3;
end;
procedure MethodOfNewton;
var x1:real;
begin
assign(ftn,'results-n.txt'); rewrite(ftn);
if f2p(a/2+b/2)*f(b)>0 then begin x:=b; x1:=a; end
else begin x:=a; x1:=b; end;
en:=1;
i:=1;
while (abs(en)>e) do begin {Пока не достигнута точность}
 x:=x-f(x)/f1p(x);// {выполнить шаг метода}
 writeln ('Iteration:',i,  'x=',x:4:4); {вывести значение X с шага}
 writeln(ftn,'Iteration: ',i,  ' x= ',x:4:4);
 en:=abs(x-x1); {Новая точность}
 x1:=x; {Значение границы для следующего шага}
 i:=i+1;   {Номер шага}
end;
close(ftn);
end;
begin
a:=-2; b:=-1.5;
writeln('Method of Newton');
MethodOfNewton;
readln;
end.
