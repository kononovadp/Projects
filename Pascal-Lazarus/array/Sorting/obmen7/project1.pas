program z1;
uses crt;
type mas=array[1..5,1..3,1..5] of integer;
var a:mas; i,j,k,p,x:byte;
procedure create_mas(var a:mas);
begin
    randomize;
    for i:= 1 to 5 do
    for k:= 1 to 5 do
    for p:= 1 to 3 do
    a[i,p,k]:=random(50);
    end;
function sum(k:byte):integer;
var s:integer;
begin
    s:=0;
    for i:=1 to 5 do
    for j:=1 to 5 do
    s:= s+a[i,k,j];
    sum:=s;
end;
procedure print(a:mas);
begin
    for p:=1 to 3 do
    begin
    for i:=1 to 5 do
    begin
    writeln;
    for k:=1 to 5 do write(a[i,p,k]:5);
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
    x:=a[i,p,j];
    a[i,p,j]:=a[i,p+1,j];
    a[i,p+1,j]:=x;  end;
end;

begin
   create_mas(a);
   print(a);
   readln;
   sort(a);writeln;
   print(a);
   readln;
   end.


