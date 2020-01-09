program z1;
uses crt;
type mas=array[1..5,1..5] of integer;
var a:mas; i,j,x,k:integer;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do
    for k:= 1 to 5 do a[i,k]:=random(50);
    end;
procedure print(a:mas);
begin
    for k:=1 to 5 do
    begin
    writeln;
    for i:=1 to 5 do write(a[i,k]:5);
    end;writeln;
end;
procedure sort(var a:mas);
begin
  for k:=1 to 5 do
    for i:=1 to 4 do
    for j:=i+1 to 5 do
  if a[i,k]>a[j,k] then
    begin
    x:=a[i,k];
    a[i,k]:=a[j,k];
    a[j,k]:=x;  end; end;

begin
   create_mas(a);
   print(a);
   sort(a);writeln; readln;
   print(a);
   readln;
   end.
