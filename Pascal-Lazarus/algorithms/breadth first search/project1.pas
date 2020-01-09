var a:array[1..8,1..8] of byte; i,j,n,x,y,k,m:byte; e:boolean;
begin e:=false; n:=1;
a[1,1]:=0; a[2,1]:=0; a[3,1]:=0; a[4,1]:=0; a[5,1]:=0; a[6,1]:=1; a[7,1]:=1; a[8,1]:=1;
a[1,2]:=0; a[2,2]:=1; a[3,2]:=1; a[4,2]:=1; a[5,2]:=1; a[6,2]:=1; a[7,2]:=0; a[8,2]:=0;
a[1,3]:=0; a[2,3]:=1; a[3,3]:=0; a[4,3]:=0; a[5,3]:=1; a[6,3]:=0; a[7,3]:=0; a[8,3]:=0;
a[1,4]:=0; a[2,4]:=1; a[3,4]:=0; a[4,4]:=0; a[5,4]:=1; a[6,4]:=1; a[7,4]:=1; a[8,4]:=0;
a[1,5]:=0; a[2,5]:=1; a[3,5]:=1; a[4,5]:=0; a[5,5]:=1; a[6,5]:=0; a[7,5]:=0; a[8,5]:=0;
a[1,6]:=0; a[2,6]:=0; a[3,6]:=0; a[4,6]:=0; a[5,6]:=1; a[6,6]:=0; a[7,6]:=0; a[8,6]:=0;
a[1,7]:=0; a[2,7]:=1; a[3,7]:=0; a[4,7]:=0; a[5,7]:=1; a[6,7]:=99; a[7,7]:=0; a[8,7]:=0;
a[1,8]:=0; a[2,8]:=1; a[3,8]:=0; a[4,8]:=0; a[5,8]:=0; a[6,8]:=0; a[7,8]:=0; a[8,8]:=0;
for i:=1 to 8 do begin
for j:=1 to 8 do write(a[j,i]:2); writeln; end;
write('horizontal point is '); readln(i);
write('vertical point is '); readln(j);
a[i,j]:=2;
while (n<56) and (e<>true) do begin
inc(n);
for i:=1 to 8 do
for j:=1 to 8 do
if a[i,j]=n  then

begin
if (a[i+1,j]=99) or (a[i-1,j]=99)
or (a[i,j+1]=99) or (a[i,j-1]=99) then e:=true;
if (a[i+1,j]=1) then   a[i+1,j]:=n+1;
if (a[i-1,j]=1) then   a[i-1,j]:=n+1;
if (a[i,j+1]=1) then   a[i,j+1]:=n+1;
if (a[i,j-1]=1) then   a[i,j-1]:=n+1; end;
 end;





for i:=1 to 8 do begin
for j:=1 to 8 do write(a[j,i]); writeln; end;
if e=true then writeln('The point was arrived for ',n,' steps') else
writeln('There are no way to the point');


i:=6;j:=7;  e:=false;  a[i,j]:=101;
 while not(e) do
begin // a[i,j]:=22;
if (a[i+1,j]=2) or (a[i-1,j]=2)
or (a[i,j+1]=2) or (a[i,j-1]=2) then e:=true;
if (a[i+1,j]=n) then begin  a[i+1,j]:=101; inc(i); end else
if (a[i-1,j]=n) then begin  a[i-1,j]:=101 ; dec(i); end else
if (a[i,j+1]=n) then begin  a[i,j+1]:=101; inc(j); end else
if (a[i,j-1]=n) then  begin a[i,j-1]:=101; dec(j); end;
dec(n);
  end;

 for k:=1 to 8 do
    for m:=1 to 8 do
            if (a[m,k]<>0) and  (a[m,k]<>101)
                   then  a[m,k]:=1;

 for k:=1 to 8 do begin
for m:=1 to 8 do write(a[m,k]:3); writeln; end;



readln; end.
