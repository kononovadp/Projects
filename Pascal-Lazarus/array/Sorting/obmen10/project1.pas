program obmen;
uses crt,dos;
type pereriz=array [1..2,1..5,1..5] of integer;



var x,y,z,k,m,n:integer; h,min,hs:word;
    a:pereriz; el:integer;
    Mas:pereriz; Sum1:pereriz;

procedure create_mas(var a:pereriz);
begin
randomize;
for z:=0 to 2 do
for y:=0 to 5 do
for x:=0 to 5 do a[x,y,z]:=random(50);
end;

function opred_sum(m:byte):integer;
var n:byte; s,sum:integer;
begin
    s:=0;
    for n:=1 to 5 do s:= s+mas[x,y,z];
    sum:=s;
end;

procedure print(Mas:pereriz;v:integer);
BEGIN

for z:=0 to k do
begin
for y:=0 to m do
 begin
     gotoXY(5*z+1,(m+2)*z+y+2+(m*k+2*k+18)*v);
     for x:=0 to n do write(Mas[z][x,y]:5);
     if y=0 then writeln('   Sum = ',sum1[x,y,z])
            else  writeln;
 end;
writeln;
end;
end;

{procedure sort(var a:mas);
begin
  for p:=1 to 2 do
  for k:=1 to 4 do  //номер шага
  for i:=1 to 5-k do


  if a[1,i,p]>a[1,i+1,p] then
    for j:=1 to 5 do
    begin
    x:=a[j,i,p];
    a[j,i,p]:=a[j,i+1,p];
    a[j,i+1,p]:=x;  end; end; }

begin
   create_mas(mas);
   print(mas,0);
   {sort(a);writeln; readln;
   print(a);}
   readln;
   end.


