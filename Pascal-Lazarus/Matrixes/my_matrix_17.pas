program array4;
uses crt;
type mas=array[0..5,0..5] of integer;
var a:mas; i,j: byte; s:integer;
procedure print_mas(a:mas);
begin
writeln('�뢮��� �������� ���ᨢ� #17');
for i:=0 to 5 do
begin  for j:= 0 to 5 do write (a[i,j]:5); writeln;  end;
end;
begin
s:=1;
for i:=0 to 2 do
   for j:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;
   a[5-i,5-j]:=s; s:=s+1;
   end ;
print_mas(a);
readln;
end.