program z1;
uses crt;
type mas=array[1..5,1..2,1..5] of integer;
var a:mas; i,j,p:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for p:= 1 to 2 do
    for i:= 1 to 5 do
    for j:= 1 to 5 do a[i,p,j]:=random(50);
    end;
procedure print(a:mas);
begin
    for p:=1 to 2 do
    begin
    writeln;
    for i:=1 to 5 do
    begin
    writeln;
    for j:=1 to 5 do write(a[i,p,j]:5);
    end;writeln;
   writeln;
 end; end;
procedure sort(var a:mas);
var k:byte; m:integer;
begin
   for p:= 1 to 2 do
   for i:= 1 to 4 do     //i - номер шага
     begin
     k:=i;
     for j:=i to 5 do if a[j,p,j]>a[k,p,k] then k:=j;//к - указатель на самый большой элемент
     if k>i then //меняем элементы
         begin
         m:=a[k,p,k];//откладываем k-й диагональный элемент
         a[k,p,k]:=a[i,p,i]; //в k-й столбец перемещаем элемент из i-го
         a[i,p,i]:=m;//в i-й столбец записываем то что было отложено
         end; end; end;
begin
   create_mas(a);
   print(a);
   sort(a);writeln; readln;
   print(a);
   readln;
   end.
