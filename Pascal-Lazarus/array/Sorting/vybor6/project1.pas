program z1;
uses crt;
 const x=5;y=3;z=2;
type mas=array[1..z,1..y,1..x] of integer;
var a:mas; i,j,k:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for k:=1 to z do
    for i:= 1 to y do
    for j:= 1 to x do a[k,i,j]:=random(50);
    end;
function sum(k,m:byte):integer;
var n:byte; s:integer;
begin
    s:=0;
    for n:=1 to y do s:= s+a[k,n,m];
    sum:=s;
end;
procedure print(a:mas);
begin
    for k:=1 to z do
    begin
    writeln;
    for i:=1 to y do
     begin
    writeln;
    for j:=1 to x do write(a[k,i,j]:5);
    end;writeln;
    for i:=1 to 5*x do write('-');writeln;
   for j:=1 to x do write(sum(k,j):5); end;
end;
procedure sort(var a:mas);
var p:byte; m:integer;
begin
   for k:=1 to z do
   for i:= 1 to x-1 do
     begin
     p:=i;
     for j:=i to x do if sum(k,j)>sum(k,p) then p:=j;//p - указатель на самую большую сумму
     if p>i then //меняем столбцы
         for j:=1 to y do
         begin
         m:=a[k,j,i];//откладываем элемент из i-го стобца
         a[k,j,i]:=a[k,j,p]; //в i-й столбец перемещаем элемент из p-го
         a[k,j,p]:=m;//в p-й столбец записываем то что было отложено
         end;

     end;
     end;
begin
   create_mas(a);
   print(a);
   sort(a);writeln;
   print(a);
   readln;
   end.
