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
procedure print(a:mas);
begin
    for p:=1 to 2 do
    begin
    writeln;
    for i:=1 to 5 do
    begin
    writeln;
    for j:=1 to 5 do write(a[i,j,p]:5);
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
     for j:=i to 5 do if a[6-j,j,p]>a[6-k,k,p] then k:=j;//к - указатель на самый большой элемент
     if k>i then //меняем элементы

         begin
         m:=a[6-k,k,p];//откладываем k-й диагональный элемент
         a[6-k,k,p]:=a[6-i,i,p]; //в k-й столбец перемещаем элемент из i-го
         a[6-i,i,p]:=m;//в i-й столбец записываем то что было отложено
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
