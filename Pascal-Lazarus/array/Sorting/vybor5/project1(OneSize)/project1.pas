program z1;
uses crt;
type mas=array[1..5] of integer;
var a:mas; i,j:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do a[i]:=random(50);
    end;
procedure print(a:mas);
begin
    for i:=1 to 5 do write(a[i]:5);
end;
procedure sort(var a:mas);
var k:byte; m,x:integer;

  begin
  for k:=5 downto 2 do {k- количество элементов для поиска max }
        begin
         m:=1; { m - место max }
         for i:=2 to k do if a[i]>a[m] then m:=i;
         {меняем местами элементы с номером m и номером k}
         x:=a[m]; a[m]:=a[k]; a[k]:=x;
     end;end;

begin
   create_mas(a);
   print(a);
   sort(a);writeln;
   print(a);
   readln;
   end.


