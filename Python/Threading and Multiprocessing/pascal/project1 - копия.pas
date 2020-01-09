var i,j,cn,ln,mc:integer; a:array[1..5,1..3] of integer;
b:boolean;
function difelements(j,n:integer):integer;
var i,k,t,t1,t2:integer;
begin
k:=1; t2:=0;
for k:=1 to n do begin
t:=a[k,j]; t1:=0;
for i:=1 to n do
if t=a[i,j] then inc(t1);
if t1<2 then inc(t2); end;
difelements:=t2; end;

procedure lines;
var mc:integer;
begin mc:=0;
for i:=1 to ln do
if difelements(i,cn)=cn then inc(mc);
writeln('lines: ',mc); end;
begin cn:=5; ln:=3;
{randomize;
while j<ln do begin
for i:=1 to cn do begin a[i,j]:=random(20);
write(a[i,j],'  '); end; inc(j); writeln; end;}
a[1,1]:=1; a[2,1]:=2; a[3,1]:=3; a[4,1]:=4; a[5,1]:=5;
a[1,2]:=6; a[2,2]:=7; a[3,2]:=8; a[4,2]:=9; a[5,2]:=10;
a[1,3]:=11; a[2,3]:=12; a[3,3]:=13; a[4,3]:=14; a[5,3]:=15;
for j:= 1 to ln do begin
for i:=1 to cn do write(a[i,j],' '); writeln; end;
lines;


{while j<ln do begin
for k:=1 to cn do
if column(k,j)=true then inc(mc); inc(j)
end;}


readln; end.
