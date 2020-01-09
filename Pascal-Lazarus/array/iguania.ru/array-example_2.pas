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
writeln('Выводим элементы массива');
for i:=0 to 5 do
begin  for j:= 0 to 5 do write (a[i,j]:5); writeln;  end;
end;

function min(a:mas):integer;
var m:integer;
begin
m:=a[0,0];
for i:= 0 to 5 do
for j:= 0 to 5 do
if a[i,j]<m then m:=a[i,j];
min:= m;
end;

function max(a:mas):integer;
var m:integer;
begin
m:=a[0,0];
for i:= 0 to 5 do
for j:= 0 to 5 do
if a[i,j]>m then m:=a[i,j];
max:= m;
end;


begin
create_mas(a);
for i:=0 to 5 do begin
s:=0;
for j:=0 to 5 do s:=s+a[i,j];
writeln('sum',i,'=',s);
 end;

print_mas(a);
writeln('Переворачиваем массив');
for i:=0 to 2 do
   for j:=1 to 5 do
      begin
      s:=a[i,j]; a[i,j]:=a[5-i,j];a[5-i,j]:=s;
      end;

print_mas(a);
writeln('min: ',min(a));
write('max: ',max(a));
readln;

end.
