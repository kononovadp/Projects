//определение смещения переменной
var p:string;
function typedef(k:string):string;
var f:text; s,a,b,c:string; i:byte;
begin
assign(f,'idlist.txt'); reset(f);
while not eof(f) do begin
readln(f,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)+1); delete(b,1,1); i:=0;
while s[i]<>' ' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1);
if k=a then typedef:=c;
writeln(a,'/',b,'\',c,'|');
a:=''; b:=''; c:='';
end;
close(f);
end;
begin
p:='const7'; writeln(typedef(p));
readln;
end.
//определения типа переменной
{var p:string;
function typedef(k:string):string;
var f:text; s,a,b:string; i:byte;
begin
assign(f,'idlist.txt'); reset(f);
while not eof(f) do begin
readln(f,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(b,1,1); if k=a then typedef:=b;
a:=''; b:='';
end;
close(f);
end;
begin
readln(p); writeln(typedef(p));
readln;
end.}

