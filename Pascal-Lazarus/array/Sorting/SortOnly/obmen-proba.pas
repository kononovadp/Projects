program vybor;
uses crt;
var
mas1:array[1..10] of integer;
k,l,n,j,s:integer;
begin
clrscr;
randomize;
for n:=1 to 10 do mas1[n]:=random(100);
for n:=1 to 10 do write (mas1[n], '   ');
   writeln;

n:=10;  s:=0;
while n>1 do //kolichestwo shagov
  begin
   s:=s+1;
   n:=1;//ukasatel na mesto obmena

   for l:=1 to 10-s do//kolichestvo proverok
     if mas1[l]<mas1[l+1] then
      begin
       j:=mas1[l];
       mas1[l]:= mas1[l+1];
       mas1[l+1]:=j;
       n:=l;
     end;
   for l:=1 to 10 do write (mas1[l], '   ');
     writeln('step ',s, 'point of change ',n);
 end;//konec cicla while
//for n:=1 to 10 do write (mas1[n], '   ');
readln
end.
