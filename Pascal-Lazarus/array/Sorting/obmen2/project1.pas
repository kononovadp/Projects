program z1;
uses crt;
type mas=array[1..5,1..5,1..3] of integer;
var a:mas; i,j,k,p,x:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do
    for k:= 1 to 5 do
    for p:= 1 to 3 do
    a[i,k,p]:=random(50);
    end;
function sum(k:byte):integer;
var s:integer;
begin
    s:=0;
    for i:=1 to 5 do
    for j:=1 to 5 do
    s:= s+a[i,j,k];
    sum:=s;
end;
procedure print(a:mas);
begin
    for p:=1 to 3 do
    begin
    for i:=1 to 5 do
    begin
    writeln;
    for k:=1 to 5 do write(a[i,k,p]:5);
    end;writeln;
     write(sum(p):5);
    for i:=1 to 25 do write('-');writeln;
     end;
end;
procedure sort(var a:mas);
begin
  for k:=1 to 2 do  //номер шага
   for p:=1 to 3-k do
  if sum(p)>sum(p+1) then
  for i:=1 to 5 do
  for j:=1 to 5 do
  begin
    x:=a[i,j,p];
    a[i,j,p]:=a[i,j,p+1];
    a[i,j,p+1]:=x;  end;
end;

begin
   create_mas(a);
   print(a);
   readln;
   sort(a);writeln;
   print(a);
   readln;
   end.

