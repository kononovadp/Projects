program z1;
uses crt;
type mas=array[1..5] of integer;
var a:mas; i,j,x,k:integer;
procedure create_mas(var a:mas);
begin
    randomize;
    for j:= 1 to 5 do a[j]:=random(50);
    end;
procedure print(a:mas);
begin
    for j:=1 to 5 do write(a[j]:5);
end;
procedure sort(var a:mas);
begin
    for i:=1 to 4 do
    for j:=i+1 to 5 do
    if a[i]>a[j] then
    begin
    k:=a[i];
    a[i]:=a[j];
    a[j]:=k;  end; end;

begin
   create_mas(a);
   print(a);
   sort(a);writeln; readln;
   print(a);
   readln;
   end.
