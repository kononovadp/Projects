var a:array[1..6,1..6] of byte;
  st,z:array[1..6] of byte;
  i,j,s,f,n,k:byte;
  begin
a[1,1]:=0; write(a[1,1],' '); a[1,2]:=1; write(a[1,2],' '); a[1,3]:=4; write(a[1,3],' ');
a[1,4]:=0; write(a[1,4],' '); a[1,5]:=2; write(a[1,5],' '); a[1,6]:=0; write(a[1,6],' '); writeln;
a[2,1]:=0; write(a[2,1],' '); a[2,2]:=0; write(a[2,2],' '); a[2,3]:=0; write(a[2,3],' ');
a[2,4]:=9; write(a[2,4],' '); a[2,5]:=0; write(a[2,5],' '); a[2,6]:=0; write(a[2,6],' '); writeln;
a[3,1]:=4; write(a[3,1],' '); a[3,2]:=0; write(a[3,2],' '); a[3,3]:=0; write(a[3,3],' ');
a[3,4]:=7; write(a[3,4],' '); a[3,5]:=0; write(a[3,5],' '); a[3,6]:=0; write(a[3,6],' '); writeln;
a[4,1]:=0; write(a[4,1],' '); a[4,2]:=9; write(a[4,2],' '); a[4,3]:=7; write(a[4,3],' ');
a[4,4]:=0; write(a[4,4],' '); a[4,5]:=0; write(a[4,5],' '); a[4,6]:=2; write(a[4,6],' '); writeln;
a[5,1]:=0; write(a[5,1],' '); a[5,2]:=0; write(a[5,2],' '); a[5,3]:=0; write(a[5,3],' ');
a[5,4]:=0; write(a[5,4],' '); a[5,5]:=0; write(a[5,5],' '); a[5,6]:=8; write(a[5,6],' '); writeln;
a[6,1]:=0; write(a[6,1],' '); a[6,2]:=0; write(a[6,2],' '); a[6,3]:=0; write(a[6,3],' ');
a[6,4]:=0; write(a[6,4],' '); a[6,5]:=0; write(a[6,5],' '); a[6,6]:=0; write(a[6,6],' '); writeln;
//for i:=1 to 6 do write(a[i,j]); writeln;
//for j:=1 to 6 do write(a[i,j]); writeln;
{    randomize;
    for i:=1 to 5 do
        begin
        for j:=1 to 5 do    begin
    a[i,j]:=random(10);  write(a[i,j]:5); end;
        writeln;
        end; }
write('b= '); readln(s);   write('f= '); readln(f);
for i :=1 to 5 do z[i]:=100;
for i :=1 to 5 do st[i]:=100;
n:=1;  i:=s;  st[s]:=1; z[s]:=0;
while (n<5)and(st[f]=100) do begin
  for k:=1 to 5 do
      if st[k]=n then
            for j:=1 to 5 do
                if (a[i,j]>0 )and (z[j]>z[k]+ a[i,j])then
                      begin z[j]:=z[k]+ a[i,j]; st[j]:=n+1; end;
      for i :=1 to 5 do write(st[i],' (',z[i],')   - '); writeln;
  n:=n+1
end;
readln; end.

 {program DijkstraAlgorithm;
uses crt;
const V=6; inf=100000;
type vektor=array[1..V] of integer;
var start: integer; a:array[1..V, 1..V] of integer;
const GR: array[1..V, 1..V] of integer=(
(0, 1, 4, 0, 2, 0),
(0, 0, 0, 9, 0, 0),
(4, 0, 0, 7, 0, 0),
(0, 9, 7, 0, 0, 2),
(0, 0, 0, 0, 0, 8),
(0, 0, 0, 0, 0, 0));
{алгоритм Дейкстры}
procedure Dijkstra(a:array[1..6, 1..6] of integer; st: integer);
var count, index, i, u, m, min: integer;
distance: vektor;
visited: array[1..V] of boolean;
begin
m:=st;
for i:=1 to V do
begin
distance[i]:=inf; visited[i]:=false;
end;
distance[st]:=0;
for count:=1 to V-1 do
begin
min:=inf;
for i:=1 to V do
if (not visited[i]) and (distance[i]<=min) then
begin
min:=distance[i]; index:=i;
end;
u:=index;
visited[u]:=true;
for i:=1 to V do
if (not visited[i]) and (a[u, i]<>0) and (distance[u]<>inf) and
(distance[u]+a[u, i]<distance[i]) then
distance[i]:=distance[u]+a[u, i];
end;
write('Stoimost puti iz nachalnoy vershini do ostalnih: '); writeln;
for i:=1 to V do
if distance[i]<>inf then
writeln(m,' > ', i,' = ', distance[i])
else writeln(m,' > ', i,' = ', 'marshrut nedostupen');
end;
{основной блок программы}
begin
clrscr;
a[1,1]:=0; write(a[1,1],' '); a[1,2]:=1; write(a[1,2],' '); a[1,3]:=4; write(a[1,3],' ');
a[1,4]:=0; write(a[1,4],' '); a[1,5]:=2; write(a[1,5],' '); a[1,6]:=0; write(a[1,6],' '); writeln;
a[2,1]:=0; write(a[2,1],' '); a[2,2]:=0; write(a[2,2],' '); a[2,3]:=0; write(a[2,3],' ');
a[2,4]:=9; write(a[2,4],' '); a[2,5]:=0; write(a[2,5],' '); a[2,6]:=0; write(a[2,6],' '); writeln;
a[3,1]:=4; write(a[3,1],' '); a[3,2]:=0; write(a[3,2],' '); a[3,3]:=0; write(a[3,3],' ');
a[3,4]:=7; write(a[3,4],' '); a[3,5]:=0; write(a[3,5],' '); a[3,6]:=0; write(a[3,6],' '); writeln;
a[4,1]:=0; write(a[4,1],' '); a[4,2]:=9; write(a[4,2],' '); a[4,3]:=7; write(a[4,3],' ');
a[4,4]:=0; write(a[4,4],' '); a[4,5]:=0; write(a[4,5],' '); a[4,6]:=2; write(a[4,6],' '); writeln;
a[5,1]:=0; write(a[5,1],' '); a[5,2]:=0; write(a[5,2],' '); a[5,3]:=0; write(a[5,3],' ');
a[5,4]:=0; write(a[5,4],' '); a[5,5]:=0; write(a[5,5],' '); a[5,6]:=8; write(a[5,6],' '); writeln;
a[6,1]:=0; write(a[6,1],' '); a[6,2]:=0; write(a[6,2],' '); a[6,3]:=0; write(a[6,3],' ');
a[6,4]:=0; write(a[6,4],' '); a[6,5]:=0; write(a[6,5],' '); a[6,6]:=0; write(a[6,6],' '); writeln;
write('Nachalnaya vershina >> '); read(start);
Dijkstra(GR, start);
end.       }
