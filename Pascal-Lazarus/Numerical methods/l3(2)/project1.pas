program lab3;
uses CRT;
var i,j,k:integer;
A:array [1..4,1..4] of double;
Ek,max,q,e: double;
x, B: array [1..4] of double;
begin
e:=0.1;
a[1,1]:=6;  a[1,2]:=3;  a[1,3]:=11; a[1,4]:=17; b[1]:=155;
a[2,1]:=0;  a[2,2]:=16; a[2,3]:=5;  a[2,4]:=10; b[2]:=161;
a[3,1]:=11; a[3,2]:=5;  a[3,3]:=25; a[3,4]:=8;  b[3]:=147;
a[4,1]:=5;  a[4,2]:=5;  a[4,3]:=11; a[4,4]:=15; b[4]:=151;
Writeln('Original matrix:');
for i:=1 to 4 do begin
for j:=1 to 4 do
  write('  ',a[i,j]:1:3);
  writeln;
end;
  writeln;
for k:=1 to 3 do //преобразование матрицы в треугольный вид
begin
//сводим матрицу к треугольному виду
for i:=k+1 to 4 do
 begin
  q:=a[i,k]/a[k,k];
  for j:=1 to 4 do  a[i,j]:=a[i,j]-a[k,j]*q;
  b[i]:=b[i]-b[k]*q;
 end;
end;
writeln('Converted matrix');
for i:=1 to 4 do begin
for j:=1 to 4 do
  write('  ',a[i,j]:1:3);     write('  |  ',b[i]:0:3);
  writeln;
end;
  writeln;
for i:=1 to 4 do x[i]:=0;
for i:=4 downto 1 do
 begin    q:=0;
  for j:=1 to 4 do   q:=q+x[j]*a[i,j]; //cумма произведений x на коэфициенты
   x[i]:=(b[i]-q)/a[i,i];
 end;
writeln('roots of the system:');
for i:=1 to 4 do
 write('  x[',i,']=',x[i]:2:3);
 readln;
END.
