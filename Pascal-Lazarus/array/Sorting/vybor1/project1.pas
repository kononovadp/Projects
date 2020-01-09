program z1;
uses crt;
type mas=array[1..5,1..5,1..2] of integer;
var a:mas; i,j,p:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for p:= 1 to 2 do
    for i:= 1 to 5 do
    for j:= 1 to 5 do a[i,j,p]:=random(50);
    end;
function sum(m:byte):integer;
var n:byte; s:integer;
begin
    s:=0;
    for n:=1 to 5 do s:= s+a[n,m,p];
    sum:=s;
end;
procedure print(a:mas);
begin
    for p:=1 to 2 do
    begin
    writeln;
    for i:=1 to 5 do
    begin writeln;
    for j:=1 to 5 do write(a[i,j,p]:5);
    end;writeln;
    for i:=1 to 25 do write('-');writeln;
   for j:=1 to 5 do write(sum(j):5);
end; end;
procedure sort(var a:mas);
var k:byte; m:integer;
begin
   for p:=1 to 2 do
   for i:= 1 to 4 do
     begin
     k:=i;
     for j:=i to 5 do if sum(j)>sum(k) then k:=j;//к - указатель на самую большую сумму
     if k>i then //меняем столбцы
         for j:=1 to 5 do
         begin
         m:=a[j,i,p];//откладываем элемент из i-го стобца
         a[j,i,p]:=a[j,k,p]; //в i-й столбец перемещаем элемент из k-го
         a[j,k,p]:=m;//в k-й столбец записываем то что было отложено
         end;

     end;
     end;
begin
   create_mas(a);
   print(a);
   sort(a);writeln; readln;
   print(a);
   readln;
   end.
