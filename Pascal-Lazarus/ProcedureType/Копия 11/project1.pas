
program proc_tip;
uses crt;
type
  func = function(x,y:real):real;
//{$F+}
function F(x,y:real):real;
  begin
    f:=ln(x)-x+y;
   end;
function G(x,y:real):real;
  begin
    g:=exp(x)-y*sqr(x);
  end;
//{$F-}
procedure tab(xn,xk,hx,yn,yk,hy:real;ff:func);
var x,y:real;
    k:integer;
begin
k:=0;
x:=xn;
while x<=xk+hx/2 do
 begin
  y:=yn;
  while y<=yk+hy/2 do
   begin
    writeln('x=',x:4:1,'  y=',y:4:1,'  F(x,y)=',ff(x,y):6:2);
    k:=k+1;
    if k mod 20=0 then
     begin
      writeln('Нажмите Enter для продолжения');
      readln
     end;
    y:=y+hy;
   end;
  x:=x+hx;
 end;
end;

begin
clrscr;
writeln('Табулирование функций на интервале х=[1..4] с шагом 0.1, y=[1..3] с шагом 1.0');
writeln('Функция F(x)=lnx-x+y');
tab(1,4,0.1,1,3,1.0,F);
writeln('функция G(x,y)=e^x-yx^2');
tab(1,4,0.1,1,3,1.0,G);
writeln('Программа завершена, Нажмите Enter для выхода');
readln
end.
