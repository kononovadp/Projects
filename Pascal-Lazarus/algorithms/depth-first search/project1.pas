var a:array[1..8,1..8] of byte; i,j,n,x,y:byte; e:boolean;
begin e:=false; n:=0;
a[1,1]:=0; a[2,1]:=0; a[3,1]:=0; a[4,1]:=0; a[5,1]:=0; a[6,1]:=0; a[7,1]:=0; a[8,1]:=0;
a[1,2]:=0; a[2,2]:=1; a[3,2]:=1; a[4,2]:=1; a[5,2]:=1; a[6,2]:=0; a[7,2]:=0; a[8,2]:=0;
a[1,3]:=0; a[2,3]:=0; a[3,3]:=0; a[4,3]:=0; a[5,3]:=1; a[6,3]:=0; a[7,3]:=0; a[8,3]:=0;
a[1,4]:=0; a[2,4]:=0; a[3,4]:=0; a[4,4]:=0; a[5,4]:=1; a[6,4]:=1; a[7,4]:=1; a[8,4]:=0;
a[1,5]:=0; a[2,5]:=0; a[3,5]:=0; a[4,5]:=0; a[5,5]:=0; a[6,5]:=0; a[7,5]:=1; a[8,5]:=0;
a[1,6]:=0; a[2,6]:=0; a[3,6]:=0; a[4,6]:=0; a[5,6]:=0; a[6,6]:=0; a[7,6]:=1; a[8,6]:=0;
a[1,7]:=0; a[2,7]:=0; a[3,7]:=0; a[4,7]:=0; a[5,7]:=0; a[6,7]:=9; a[7,7]:=1; a[8,7]:=0;
a[1,8]:=0; a[2,8]:=0; a[3,8]:=0; a[4,8]:=0; a[5,8]:=0; a[6,8]:=0; a[7,8]:=0; a[8,8]:=0;
for i:=1 to 8 do begin
for j:=1 to 8 do write(a[j,i]); writeln; end;
write('horizontal point is '); readln(i);
write('vertical point is '); readln(j);
while (n<56) and (e<>true) do begin
inc(n);
if (a[i+1,j]=9) or (a[i-1,j]=9)
or (a[i,j+1]=9) or (a[i,j-1]=9) then e:=true;
if (a[i+1,j]=1) then begin inc(i); a[i,j]:=2; end else
if (a[i-1,j]=1) then begin dec(i); a[i,j]:=2; end else
if (a[i,j+1]=1) then begin inc(j); a[i,j]:=2; end else
if (a[i,j-1]=1) then begin dec(j); a[i,j]:=2; end; end;
for i:=1 to 8 do begin
for j:=1 to 8 do write(a[j,i]); writeln; end;
if e=true then writeln('The point was arrived for ',n,' steps') else
writeln('There are no way to the point');
readln; end.
