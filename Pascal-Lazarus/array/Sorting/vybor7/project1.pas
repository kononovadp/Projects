program z1;
uses crt;
type mas=array[1..4,1..3,1..5] of integer;
var a:mas; i,j,k:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 4 do
    for j:= 1 to 5 do
    for k:= 1 to 3do
    a[i,k,j]:=random(50);
    end;
function sum(k:byte):integer;
var s:integer;
begin
    s:=0;
    for i:=1 to 4 do
    for j:=1 to 5 do
    s:= s+a[i,k,j];
    sum:=s;
end;
procedure print(a:mas);
begin
    for k:=1 to 3 do
    begin
    for i:=1 to 4 do
    begin
    writeln;
    for j:=1 to 5 do write(a[i,k,j]:5);
    end;writeln;
     write(sum(k):5);
    for i:=1 to 25 do write('-');writeln;
     end;
end;
procedure sort(var a:mas);
var p,l:byte; m:integer;
begin
   for l:= 1 to 2 do//количество шагов в сортировке
     begin
     p:=l;
     for k:=l to 3 do if sum(p)>sum(k) then p:=k;//p - указатель на самую меньшую сумму
     if p>l then //меняем слои
         for i:=1 to 4 do
         for j:=1 to 5 do
         begin
         m:=a[i,p,j];//откладываем элемент из слоя p
         a[i,p,j]:=a[i,l,j]; //в слой p перемещаем элемент из l-го
         a[i,l,j]:=m;//в l-й слой записываем то что было отложено
         end;

     end;
     end;
begin
   create_mas(a);
   print(a);
   readln;
   sort(a);writeln;
   print(a);
   readln;
   end.
