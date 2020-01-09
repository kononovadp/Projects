var s,ss:string;
function substr (s,ss:string):integer;
var t:string; i,j:integer;
begin i:=0;
while i<length(s) do begin t:=''; substr:=i+1;
for j:=1 to length(ss) do t:= t+s[j+i];
if t=ss then exit else if (i=length(s)-1) and (t<>ss) then substr:=0;
inc(i); end; end;
begin
writeln(substr('101023a','01'));
readln; end.
