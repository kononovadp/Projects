program obmen;
uses crt,dos;
type pereriz=array [0..50,0..50] of integer;
     ms=array [0..500] of pereriz;
     vektor =array [0..500] of integer;

var x,y,z,k,m,n:integer; h,min,s,hs:word;
    Mas:ms; Sum1:vektor;
    sl:pereriz; el:integer;


procedure opred_sum(var S:vektor);
begin
for z:=0 to k do
 begin
  s[z]:=0;
    for x:=0 to n do s[z]:=s[z]+Mas[z,x,0];
 end;
end;

procedure readmas(var Mas:ms;var n,m,k:integer);
var f:text;
BEGIN
assign(f,'Mas.txt'); reset(f);
read(f,n,m,k);
for z:=0 to k do
for y:=0 to m do
for x:=0 to n do
 read(f,Mas[z,x,y]);
 close(f);;
 end;


procedure print(Mas:ms;v:integer);
BEGIN
opred_sum(Sum1);
for z:=0 to k do
begin
for y:=0 to m do
 begin
     gotoXY(5*z+1,(m+2)*z+y+2+(m*k+2*k+18)*v);
     for x:=0 to n do write(Mas[z][x,y]:5);
     if y=0 then writeln('   Sum = ',sum1[z])
            else  writeln;
 end;
writeln;
end;
end;

procedure sortirovka(var Mas:ms);
begin
opred_sum(Sum1);
z:=k-1;
while z>=0 do
   begin
   y:=0;
   for x:=0 to z do
   if Sum1[x+1]<Sum1[x]
   then begin
               el:=Sum1[x];      sl:=Mas[x];
               sum1[x]:=sum1[x+1];  Mas[x]:=Mas[x+1];
               sum1[x+1]:=el;       Mas[x+1]:=sl;
               y:=x;
               end;
   z:=y-1;
   end;
end;

procedure perestanovka(var M:ms);
begin
 for z:=0 to k div 2 do
 begin
  sl:=M[z]; m[z]:=m[k-z]; m[k-z]:=sl;
 end;
end;

begin {program}
clrscr;
readmas(Mas,n,m,k);

writeln('Ishodniy massiv:'); print(Mas,0);
writeln('Razmer massava:', m+1,'  ',n+1,'  ',k+1);


readln;
{______________________________}
writeln('Sortirovka neuporjad. massiva');
GetTime(h,min,s,hs);   writeln('Begin  ',h:2,'.',min:2,'.',s:2,'.',hs:2);

SORTIROVKA(Mas);

GetTime(h,min,s,hs);  writeln('End  ',h:2,'.',min:2,'.',s:2,'.',hs:2);
{----------------------------------------}
writeln('Sortirovka uporjad. massiva');
GetTime(h,min,s,hs);   writeln('Begin  ',h:2,'.',min:2,'.',s:2,'.',hs:2);

SORTIROVKA(Mas);

GetTime(h,min,s,hs);  writeln('End  ',h:2,'.',min:2,'.',s:2,'.',hs:2);

{-----------------------------------------}

perestanovka(Mas); print(mas,2); readln;

{_____________________________________________}
writeln('Sortirovka obratnogo massiva');
GetTime(h,min,s,hs);   writeln('Begin  ',h:2,'.',min:2,'.',s:2,'.',hs:2);

SORTIROVKA(Mas);

GetTime(h,min,s,hs);  writeln('End  ',h:2,'.',min:2,'.',s:2,'.',hs:2);

{----------------------------------------------}


writeln; writeln('Rezult:');  print(Mas,1);



readln;




END.

