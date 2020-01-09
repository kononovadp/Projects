program z1;
uses crt;
type mas=array[1..5,1..5,1..2] of integer;
var a:mas; i,j,p:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do
    for j:= 1 to 5 do
    for p:= 1 to 2 do a[i,j,p]:=random(50);
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
var k:byte; m,n:integer;
begin
   for p:=1 to 2 do
   begin
     k:=5;
   while k>1  do
     begin  n:=k;
     for j:=1 to k-1 do
     if sum(j)<sum(j+1) then //меняем столбцы
         for i:=1 to 5 do
          begin
         m:=a[i,j,p];//откладываем элемент из j-го стобца
         a[i,j,p]:=a[i,j+1,p]; //в j-й столбец перемещаем элемент из j+1
         a[i,j+1,p]:=m;//в j+1-й столбец записываем то что было отложено
         k:=j;//место обмена
         end;
       if n=k then k:=0; //признак отсутствия обмена
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
