program lab2;
uses crt;
const max_iter=100;
var a,b,en,x: real; fti:text; i,k: integer; const e=0.001;
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
procedure MethodOfIterations;
var l,d:real;
begin
 k:=0;
 d:=0.8;//дробь между 1 и второй производной от fi
 l:=-0.1;
 if (a>=-1.3) and ( a<=-0.3) then l:=-l;
 repeat
 b:=a;   a:=a+l*f(a);       inc(k);
 writeln('E= ',e:6:3,' Root value ',a:6:3,' Achived accuracy ',f(a):6:4,' Step ',k);
 writeln(fti,'Specified accuracy ',e:6:3,' Root value ',a:6:3,' Achived accuracy ',f(a):6:4,' Step ',k);
 until (abs(a-b)<=e*(1-d)/d) or (k>max_iter);
 if k>max_iter then  writeln('Answer not found!');
end;
procedure MethodOfNewton;
var x1:real;
begin
if f2p(a/2+b/2)*f(b)>0 then begin x:=b; x1:=a; end
else begin x:=a; x1:=b; end;
en:=1; i:=0;
while (abs(en)>e) do begin {Пока не достигнута точность}
 x:=x-f(x)/f1p(x);// {выполнить шаг метода}
 en:=abs(x-x1); {Новая точность}
 x1:=x; {Значение границы для следующего шага}
 i:=i+1; {Номер шага}
 writeln('E= ',e:6:3,' Root value ',x:6:3,' Achived accuracy ',en:6:4,' Step ',i);
 writeln(fti,'Specified accuracy ',e:6:3,' Root value ',x:6:3,' Achived accuracy ',en:6:4,' Step ',i);
end;
end;
begin
assign(fti,'Results.txt'); rewrite(fti);
a:=-2; b:= -1.5;
writeln(fti,'a= ',a:2:1, '  b= ',b:2:1); writeln;
 write('a= ',a:2:2);
 write('b= ',b:2:2);
 writeln('Method of Iterations'); writeln(fti,'Method of Iterations');
 MethodOfIterations;
 writeln('Method of Newton'); writeln(fti,'Method of Newton');
 MethodOfNewton;
a:=-1; b:= -0.5;
writeln(fti,'a= ',a:2:1, '  b= ',b:2:1); writeln;
 write('a= ',a:2:2);
 write('b= ',b:2:2);
 writeln('Method of Iterations'); writeln(fti,'Method of Iterations');
 MethodOfIterations;
 writeln('Method of Newton'); writeln(fti,'Method of Newton');
 MethodOfNewton;
a:=0; b:= 0.5;
writeln(fti,'a= ',a:2:1, '  b= ',b:2:1); writeln;
 write('a= ',a:2:2);
 write('b= ',b:2:2);
 writeln('Method of Iterations'); writeln(fti,'Method of Iterations');
 MethodOfIterations;
 writeln('Method of Newton'); writeln(fti,'Method of Newton');
 MethodOfNewton;
close(fti);
writeln('All results were written in text file!'); readln;
end.
