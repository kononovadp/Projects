var p:string;
function dollardef(s:string):integer;
var c:string; i,j,n,k:integer;
begin
if (s[1]='6') and (s[3]='|') then delete(s,1,4);
s:=s+' '; n:=0;
for j:=1 to length(s) do if s[j]=' ' then inc(n);
j:=0; k:=0;
for i:=1 to n do begin
while s[j]<>' ' do begin c:=c+s[j]; inc(j); end; j:=0;
delete(c,1,1); delete (s,1,length(c)); delete(s,1,1);
if length(c)=1 then c:=c+'*';
k:=k+(length(c) div 2); c:=''; end;
dollardef:=k; end;
begin
p:= 'FF 0E 000C R';
writeln(dollardef(p));
readln;
end.
