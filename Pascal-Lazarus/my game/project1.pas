 uses sysutils,crt;
type ob=record
     x,y:byte;
     p:char; end;
var f:array[1..8,1..8] of ob; i,j,kb,sh,se:integer; e:boolean;
n,vr,b,w:ob;   k:char;
procedure createfield;
begin
randomize;
gotoxy(1,1);
for i:=1 to 8 do
for j:=1 to 8 do begin f[i,j].x:=i;
f[i,j].y:=j; f[i,j].p:='-'; end;
b.x:=random(8); b.y:=random(8);
for i:=1 to 8 do begin
for j:=1 to 8 do write(' ', f[i,j].p);
writeln; end;

n.x:=5; n.y:=5; vr.x:=8; vr.y:=8;
n.p:='@'; vr.p:='O';
f[5,5]:=n; f[8,8]:=vr;

b.p:='?';
for i:=1 to kb do begin
while  f[b.x,b.y].p<>'-' do begin
b.x:=random(8); b.y:=random(8); end;
f[b.x,b.y]:=b; end;

w.p:='X';
 for i:=1 to 10 do begin
while  f[b.x,b.y].p<>'-' do begin
b.x:=random(8); b.y:=random(8); end;
f[b.x,b.y]:=w; end;



{n.x:=5; n.y:=5; vr.x:=8; vr.y:=8;
n.p:='@'; vr.p:='O';
f[5,5]:=n; f[8,8]:=vr;
for i:=1 to 8 do begin
for j:=1 to 8 do
if f[i,j].p='?' then inc(kb); end; }

gotoxy(1,1);
for i:=1 to 8 do begin
for j:=1 to 8 do write(' ',f[i,j].p); writeln; end;
gotoxy(24,1);  writeln('Steps (hero/enemy): ',sh,'/',se);
gotoxy(24,2); writeln('Bonus: ',kb);
end;

procedure stepvr;
var a:array[1..8,1..8] of byte; i,j,k,x,y:byte; e:boolean;
begin e:=false; k:=0;
for i:=1 to 8 do
for j:=1 to 8 do a[i,j]:=0;

i:=vr.x; j:=vr.y;  a[i,j]:=1;
while (k<56) and (e<>true) do begin
inc(k);
if (f[i+1,j].p=n.p) or (f[i-1,j].p=n.p)
or (f[i,j+1].p=n.p) or (f[i,j-1].p=n.p) then e:=true;
 for i:=1 to 8 do
for j:=1 to 8 do
if a[i,j]=k then
begin
if (f[i+1,j].p<>'X') and(a[i+1,j]=0) then begin  a[i+1,j]:=k+1; end ;
if (f[i-1,j].p<>'X')and(a[i-1,j]=0) then begin  a[i-1,j]:=k+1; end ;
if (f[i,j+1].p<>'X') and(a[i,j+1]=0)then begin  a[i,j+1]:=k+1; end ;
if (f[i,j-1].p<>'X')and(a[i,j-1]=0) then begin  a[i,j-1]:=k+1; end; end;
end;


for i:=1 to 8 do  begin
for j:=1 to 8 do write(a[i,j],' '); writeln; end;

//if e=true then writeln('The point was arrived for ',k,' steps') else
//writeln('There are no way to the point');

                                           end;


procedure step;//(k:char; var n:ob);
var tx,ty,ex,ey:byte;
begin tx:=n.x; ty:=n.y; ex:=vr.x; ey:=vr.y;
gotoxy(2*n.x,n.y); f[n.y,n.x].p:='-';
write(f[n.y,n.x].p);
gotoxy(2*vr.x,vr.y); f[vr.y,vr.X].p:='-';
write(f[vr.y,vr.x].p);
case k of
#75: if (n.x>1) and (f[n.y,n.x-1].p<>'X')  then dec(n.x); //движение влево
#77: if (n.x<8) and (f[n.y,n.x+1].p<>'X') then inc(n.x); //движение вправо
#72: if (n.y>1)and (f[n.y-1,n.x].p<>'X')  then dec(n.y); //движение вверх
#80: if (n.y<8) and (f[n.y+1,n.x].p<>'X') then inc(n.y); end; //движение вниз
   f[n.y,n.x]:=n;

if (k=#75) or (k=#77) then
if (n.x>vr.x)and (f[vr.y,vr.x+1].p<>'X') then inc(vr.x)
else   if (n.x<vr.x)and (f[vr.y,vr.x-1].p<>'X') then dec(vr.x) else if f[vr.y-1,vr.x].p<>'X' then dec(vr.y);

if (k=#72) or (k=#80) then   if (n.y>vr.y)and (f[vr.y+1,vr.x].p<>'X') then inc(vr.y)
else  if (n.y<vr.y)and (f[vr.y-1,vr.x].p<>'X') then dec(vr.y) else  if f[vr.y,vr.x-1].p<>'X' then dec(vr.x) ;
    f[vr.y,vr.x]:=vr;

gotoxy(2*n.x,n.y); write(n.p);
gotoxy(2*vr.x,vr.Y); write(vr.p);

if (tx<>n.x) or (ty<>n.y) then inc(sh);
if (ex<>vr.x) or (ey<>vr.y) then inc(se);
if (f[vr.y,vr.x].p='?') or ((f[vr.y,vr.x].p='?')  and (f[n.y,n.x].p='?'))
                  then begin; inc(kb); createfield; end
                 else if f[n.y,n.x].p='?' then dec(kb);

gotoxy(24,1); writeln('Steps (hero/enemy): ',sh,'/',se);
gotoxy(24,2); writeln('Bonus: ',kb);
// gotoxy(1,11); stepvr;
end;

begin kb:=4;
createfield; e:=false;
f[n.y,n.x]:=n;
while (k<>#13) and (e=false) and (kb>0) do begin
k:=readkey; step;
gotoxy(1,9);
if (n.x=vr.x) and (n.y=vr.y) then e:=true;
end; gotoxy(1,9);
if e=true then write('Sorry, you have lost the game!') else
if kb=0 then
write('Congratulations! You have won the game!') else
write('The game was interrupted.'); readln; end.
