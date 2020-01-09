 uses sysutils,crt;
type ob=record
     x,y,vx,vy:byte;
     p:char; end;
var f:array[1..8,1..8] of ob; i,j,kb,sh,se:integer; e:boolean;
n,vr,b:ob;   k:char;
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
b.p:='?';
for i:=1 to kb do begin
while  f[b.x,b.y].p='?' do begin
b.x:=random(8); b.y:=random(8); end;
f[b.x,b.y]:=b; end;  kb:=0;
n.x:=5; n.y:=5; vr.vx:=8; vr.vy:=8;
n.p:='@'; vr.p:='O';
f[5,5]:=n; f[8,8]:=vr;
for i:=1 to 8 do begin
for j:=1 to 8 do
if f[i,j].p='?' then inc(kb); end;
gotoxy(1,1); for i:=1 to 8 do begin
for j:=1 to 8 do write(' ',f[i,j].p); writeln; end;
gotoxy(24,1);  writeln('Steps (hero/enemy): ',sh,'/',se);
gotoxy(24,2); writeln('Bonus: ',kb); end;

procedure step;//(k:char; var n:ob);
var tx,ty,ex,ey:byte;
begin tx:=n.x; ty:=n.y; ex:=vr.vx; ey:=vr.vy;
gotoxy(2*n.x,n.y); f[n.y,n.x].p:='-';
write(f[n.y,n.x].p);
gotoxy(2*vr.vx,vr.vy); f[vr.vy,vr.vx].p:='-';
write(f[vr.vy,vr.vx].p);
case k of
#75: if n.x>1  then dec(n.x); //движение влево
#77: if n.x<8  then inc(n.x); //движение вправо
#72: if n.y>1  then dec(n.y); //движение вверх
#80: if n.y<8  then inc(n.y); end; //движение вниз
if (k=#75) or (k=#77) then
if n.x>vr.vx then inc(vr.vx) else
if n.x<vr.vx then dec(vr.vx) else dec(vr.vy);
if (k=#72) or (k=#80) then
if n.y>vr.vy then inc(vr.vy) else
if n.y<vr.vy then dec(vr.vy) else dec(vr.vx);
gotoxy(2*n.x,n.y); write(n.p);
gotoxy(2*vr.vx,vr.vy); write(vr.p);
if (tx<>n.x) or (ty<>n.y) then inc(sh);
if (ex<>vr.vx) or (ey<>vr.vy) then inc(se);
if (f[vr.vy,vr.vx].p='?') or ((f[vr.vy,vr.vx].p='?')
and (f[n.y,n.x].p='?')) then begin; inc(kb);
createfield; end else if f[n.y,n.x].p='?' then dec(kb);
gotoxy(24,1); writeln('Steps (hero/enemy): ',sh,'/',se);
gotoxy(24,2); writeln('Bonus: ',kb); end;

begin kb:=4;
createfield; e:=false;
while (k<>#13) and (e=false) and (kb>0) do begin
k:=readkey; step;
gotoxy(1,9);
if (n.x=vr.vx) and (n.y=vr.vy) then e:=true;
end; gotoxy(1,9);
if e=true then write('Sorry, you have lost the game!') else
if kb=0 then
write('Congratulations! You have won the game!') else
write('The game was interrupted.'); readln; end.
