program array4;
uses crt;
type mas=array[0..5,0..5] of integer;
var a:mas; i,j: byte; s:integer;

procedure create_mas(var a:mas);
begin
randomize;
for i:=0  to 5 do
for j:=0 to 5 do
a[i,j]:= random(200)-100 ;
end;

procedure print_mas(a:mas);
begin
writeln('�뢮��� ����� "1" �� ������� ��������� � "2" �� ����筮�');
for i:=0 to 5 do
begin  for j:= 0 to 5 do write (a[i,j]:5); writeln;  end;
end;



begin
for i:= 0 to 5 do
for j:= 0 to 5 do
a[i,j]:=0;

for i:= 0 to 5 do a[i,i]:=1;
for i:= 0 to 5 do a[i,5-i]:=2;
print_mas(a);
readln;

end.
