 uses sysutils,crt;
type ob=record
     x,y:byte;
     p:char; end;

var f:array[1..8,1..8] of ob; i,j,kb:byte; e:boolean;
n,vr,b:ob;   k:char;

procedure sf;
begin
  gotoxy(1,1);
  for i:=1 to 8 do begin
  for j:=1 to 8 do   write(' ', f[i,j].p); writeln; end;
end;

procedure step(k:char; var n:ob);
begin
     case k of
    '1': if n.x>1  then
        begin
          gotoxy(2*n.x,n.y); write('-');
            n.x:=n.x-1;

           gotoxy(2*n.x,n.y); write(n.p);
         end;
    '2': if n.x<8  then
          begin
            gotoxy(2*n.x,n.y); write('-');
           n.x:=n.x+1;
           gotoxy(2*n.x,n.y); write(n.p);
         end;
    end;
       if f[n.x,n.y].p='?' then begin   kb:=kb-1;
         gotoxy(24,2); writeln('  ',kb);  end;




end;


begin  e:=false; kb:=4; randomize;
  n.x:=5; n.y:=5; n.p:='@';
  vr.x:=8; vr.y:=8; vr.p:='O';
    b.p:='?';
    gotoxy(24,1); writeln('Bonus');
     gotoxy(24,2); writeln('  ',kb);
  for i:=1 to 8 do
  for j:=1 to 8 do begin f[i,j].x:=i; f[i,j].y:=j; f[i,j].p:='-'; end;

    f[5,5]:=n; f[8,8]:=vr;
    b.x:=random(8); b.y:=random(8);
    for i:=1 to kb do    begin
               while  f[b.x,b.y].p='?' do
                  begin   b.x:=random(8); b.y:=random(8);  end;

                  f[b.x,b.y]:=b end;

   f[5,6].p:='?';

    sf;

    repeat
    k:=readkey;
      step(k,n);

     gotoxy(1,9);

  if n.x<>vr.x then   step('1',vr)
         else  if n.y<>vr.y then     step('3',vr)
                 else e:=true ;


  until    (k=#13) or e or (kb=0);

   gotoxy(1,12);

{begin e:=false; n:=0;
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
writeln('There are no way to the point');           }
readln; end.
