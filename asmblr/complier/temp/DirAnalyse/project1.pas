program dir;
var f:text; i:byte; s,s1,s2,s3:string; s5: set of char;
label l1;
begin
assign(f,'1.asm'); reset(f);
while not(eof(f)) do begin
readln(f,s);    i:=0;
while s[i] <>' ' do begin s1:=s1+s[i]; i:=i+1; end; //выделение директивы
delete(s,1,length(s1));  i:=0;
delete(s1,1,1);//удаление лишних символов в названии директивы
if (s2='segment') or (s2='ends') then goto l1;
while s[i] <>' ' do begin s2:=s2+s[i]; i:=i+1; end; //выделение регистра-приемника
delete(s,1,length(s2)); i:=0;
delete(s2,1,1); s3:=s;
i:=0;




l1:writeln('|',s1,'|',s2,'|',s3,'|');
s:=''; s1:=''; s2:=''; s:='';


end;
close(f); readln;
end.
