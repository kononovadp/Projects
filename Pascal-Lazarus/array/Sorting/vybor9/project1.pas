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
function sum(m:byte):integer;begin
for j:=1 to 5 do i:=1;
{var n:byte; s:integer;
begin
    s:=0;
    for n:=1 to 5 do s:= s+a[n,m,p];
    sum:=s;}
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
    {for i:=1 to 25 do write('-');writeln;
   for j:=1 to 5 do write(sum(j):5);}
end; end;
procedure sort(var a:mas);
var k:byte; m,sum:integer;
begin
   for p:=1 to 2 do
   for i:= 1 to 4 do
     begin
     k:=i;
     for j:=i to 5 do if a[j,1,p]>a[k,1,p] then k:=j;//к - указатель на больший элемент
     if k>i then //меняем строки
         for j:=1 to 5 do
         begin
         m:=a[i,j,p];//откладываем элемент из i-й строки
         a[i,j,p]:=a[k,j,p]; //в i-ю строку перемещаем элемент из k-й
         a[k,j,p]:=m;//в k-ю строку записываем то что было отложено
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
