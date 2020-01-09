{За допомогою методу простої ітерації обчислити корені системи лінійних рівнянь
318x0 + 85x1 + 24x2 + 112x3 + 92x4  = 5420
114x0 + 362x1 + 115x2 + 81x3 + 49x4  = 3147
34x0 + 26x1 + 205x2 + 92x3 + 49x4  = 3056
74x0 + 117x1 + 121x2 + 333x3 + 17x4  = 4517
120x0 + 107x1 + 8x2 + 42x3 + 280x4  = 6698
з точністю не гірше за 10^-7.}
uses CRT;
var i,j,k:integer;
A:array [1..4,1..4] of double;
Ek,max,q,e: double;
x_prev,x_tmp, B: array [1..4] of double;
begin
e:=0.1;
a[1,1]:=36; a[1,2]:=2;  a[1,3]:=11.5; a[1,4]:=-3; b[1]:=149.5;
a[2,1]:=0;  a[2,2]:=16; a[2,3]:=5;    a[2,4]:=10; b[2]:=161;
a[3,1]:=11; a[3,2]:=5;  a[3,3]:=25;   a[3,4]:=8;  b[3]:=147;
a[4,1]:=0;  a[4,2]:=3;  a[4,3]:=-3;   a[4,4]:=24; b[4]:=159;

Writeln('Original matrix:');
for i:=1 to 4 do begin
for j:=1 to 4 do
 write('  ',a[i,j]:1:3);
 writeln;
end;
Writeln('Converted matrix:');
for i:=1 to 4 do
 b[i]:=b[i]/a[i,i];
for i:=1 to 4 do
for j:=1 to 4 do
 if i<>j then  a[i,j]:=(-a[i,j])/(a[i,i]);
for i:=1 to 4 do   a[i,i]:=0;
for i:=1 to 4 do begin
for j:=1 to 4 do
write('  ',a[i,j]:1:3);
writeln;
end;
//Перевірка достатньої умови збіжності системи
Writeln('convergence:' ); q:=0;
for i:=1 to 4 do begin
 Ek:=0;
for j:=1 to 4 do   Ek:=Ek+abs(a[i,j]);
 if Ek>1 then
  begin
   writeln (' s[',i, ']',Ek:1:3,'>1; condition is not true.'); readln;
   exit;
  end
  else   writeln (' s[',i, ']',Ek:1:3,'<1; condition is true.');
  if ek>q then q:=ek;
  end;
 k:=0;
for i:=1 to 4 do
 x_tmp[i]:=b[i];


Repeat
inc(k);
for i:=1 to 4 do
 x_prev[i]:=x_tmp[i];
for i:=1 to 4 do
begin
 x_tmp[i]:= b[i];
for j:=1 to 4 do
 x_tmp[i]:=x_tmp[i]+ a[i,j] * x_prev[j];
end;
//оцінка похибки
ek:=0;
for j:= 1 to 4 do ek:=ek+abs(x_tmp[j]-x_prev[j]);
 Until  ek < (1-q)/q*e;
  writeln('quantity of iterations=',k);
  writeln('roots of the system:');
for i:=1 to 4 do
  write('  x[',i,']=',x_tmp[i]:2:3);
readln;
END.
