program z1;
uses crt;
type mas=array[1..5,1..5,1..2] of integer;
var a:mas; i,j,x,k,l,p:integer;
procedure create_mas(var a:mas);
begin
    randomize;
    for p:= 1 to 2 do
    for i:= 1 to 5 do
    for k:= 1 to 5 do a[i,k,p]:=random(50);
    end;
procedure print(a:mas);
begin
    for p:=1 to 2 do
    begin
    writeln;
    for k:=1 to 5 do
    begin
    writeln;
    for i:=1 to 5 do write(a[i,k,p]:5);
    end;writeln;
end; end;
procedure sort(var a:mas);
begin
  for p:=1 to 2 do
  for k:=1 to 4 do  //номер шага
  for i:=1 to 5-k do


  if a[1,i,p]>a[1,i+1,p] then
    for j:=1 to 5 do
    begin
    x:=a[j,i,p];
    a[j,i,p]:=a[j,i+1,p];
    a[j,i+1,p]:=x;  end; end;

begin
   create_mas(a);
   print(a);
   sort(a);writeln; readln;
   print(a);
   readln;
   end.

