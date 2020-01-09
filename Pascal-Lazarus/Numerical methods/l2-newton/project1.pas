{Метод Ньютона решения нелинейного уравнения}
program Newton;
uses crt; {модуль управления экраном}
var a,b,x,en,e:real; exp1,i:integer;
function f(x:real):real; {Исходная функция}
begin
 f:=exp(ln(e)*x)-3*cos(2*x)+2*x+1; //f:=sqr(sqr(x))-5*sqr(x)-x+1;
end;

function f1(x:real):real; {Первая производная функции}
begin
 f1:= exp(ln(e)*x)+6*sin(2*x)+2;//f1:=4*x*sqr(x)-10*x-1;
end;

begin
 clrscr; {очистить экран}
 write ('a:  '); read (a);
 write ('b:  '); read (b);
 exp1:=2;
 en:=abs(a-b);
 x:=b;
 i:=1;
 while (abs(en)>e) do begin {Пока не достигнута точность}
  x:=x-f(x)/f1(x); {выполнить шаг метода}
  writeln (i:10,x:4:4); {вывести значение X с шага}
  en:=abs(x-b); {Новая точность}
  b:=x; {Значение границы для следующего шага}
  i:=i+1;   {Номер шага}
 end;  readln;
readln;   readln;
end.
