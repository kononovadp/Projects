program z1;
uses crt;
type mas=array[1..5,1..5] of integer;
var a:mas; i,j:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do
    for j:= 1 to 5 do a[i,j]:=random(50);
    end;
procedure print(a:mas);
begin
    for i:=1 to 5 do
    begin
    writeln;
    for j:=1 to 5 do write(a[i,j]:5);
    end;writeln;
   writeln;

end;
procedure sort(var a:mas);
var k:byte; m:integer;
begin
   for i:= 1 to 4 do     //i - номер шага
     begin
     k:=i;
     for j:=i to 5 do if a[6-j,j]>a[6-k,k] then k:=j;//к - указатель на самый большой элемент
     if k>i then //меняем элементы

         begin
         m:=a[6-k,k];//откладываем k-й диагональный элемент
         a[6-k,k]:=a[6-i,i]; //в k-й столбец перемещаем элемент из i-го
         a[6-i,i]:=m;//в i-й столбец записываем то что было отложено
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
