program vybor;
uses crt;
var
mas1:array[1..10] of integer;
k,l,n:integer;
begin
clrscr;
randomize;
for n:=1 to 10 do mas1[n]:=random(100);
for n:=1 to 10 do write (mas1[n], '   ');
   writeln;
for k:= 1 to 9 do
begin
l:=k;//ustanovili ukasatel
for n:=k+1 to 10 do
if mas1[n]<mas1[l] then l:=n;
if l>k then  //menyaem elementy l i k
  begin
    n:=mas1[k];mas1[k]:=mas1[l];mas1[l]:=n;
  end;
 for n:=1 to 10 do write (mas1[n], '   ');
   writeln('Step ',k,'  point of change - ', l) ;  readln;


end;

for n:=1 to 10 do write (mas1[n], '   ');
readln
end.
