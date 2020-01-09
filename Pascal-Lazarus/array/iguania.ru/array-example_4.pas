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

begin
 s:=0;
for i:=0 to 5 do
 if i mod 2=0
 then
   for j:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for j:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;
print_mas(a); readln;

s:=0;
for i:=5 downto 0 do
 if i mod 2=1
 then
   for j:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for j:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;
print_mas(a); readln;


s:=0;
for j:=0 to 5 do
 if j mod 2=0
 then
   for i:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for i:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;


print_mas(a); readln;

 s:=0;
for j:=5 downto 0 do
 if j mod 2=0
 then
   for i:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for i:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;
 print_mas(a); readln;

 s:=0;
for j:=5 downto 0 do
 if j mod 2=1
 then
   for i:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for i:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;



   print_mas(a); readln;

 s:=0;
for j:=0 to 5 do
 if j mod 2=1
 then
   for i:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;end
 else
   for i:=5 downto 0 do begin a[i,j]:= s;  s:=s+1;end;
print_mas(a); readln;


 s:=0;
for j:=0 to 2 do

    for i:= 0 to 5 do begin a[i,j]:= s;  s:=s+1;
   a[5-i,5-j]:=s; s:=s+1;
   end ;

print_mas(a);
readln;

end.
