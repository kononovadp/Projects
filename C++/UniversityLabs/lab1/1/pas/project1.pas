function substr (const s1,s2:string):integer;
var t:string; i,j:integer;
begin i:=0;
while i<length(s1) do begin t:=''; substr:=i+1;
for j:=1 to length(s2) do t:= t+s1[j+i];
if t=s2 then exit else if (i=length(s1)-1) and (t<>s2) then substr:=0;
inc(i); end; end;
begin
writeln(substr('101023a','01'));
readln; end.
