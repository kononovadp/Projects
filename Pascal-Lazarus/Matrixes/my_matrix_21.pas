program array4;
uses crt;
type mas=array[0..6,0..5] of integer;
var a:mas; i,j: byte; s:integer;
procedure print_mas(a:mas);
begin
writeln('Выводим элементы массива #21');
for i:=0 to 6 do
begin  for j:= 0 to 5 do write (a[i,j]:5); writeln;  end;
end;
begin
 s:=1;
 i:=3;
    for j:= 2 downto 0 do
    begin a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1; end;
for i:=2downto 0 do
if i mod 2=0
then
    for j:= 0 to 5 do
    begin
    a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1;
    end
else
   for j:= 5 downto 0 do
    begin
    a[i,j]:= s;  s:=s+1;
    a[6-i,5-j]:=s; s:=s+1;
    end;
print_mas(a); readln; end.
