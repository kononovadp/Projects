program z1;
var s,c,reg:string; i:byte; s1: set of char; f:text;
label label1;
begin
for i:= 65 to 122 do s1:=s1+[chr(i)]; i:=0;
for i:= 48 to 57 do s1:=s1+[chr(i)];  i:=0;
assign(f,'1.asm'); reset(f);
while not(eof(f)) do begin
readln(f,s);
if length(s)=0 then goto label1; //пропуск пустых строк
while not(s[i] in s1) do begin inc(i); //удаление пробелов в начале
while s[i]=' ' do delete(s,i,1); end; i:=0;
for i:=1 to length(s) do begin //удаление комментариев
if s[i]=';' then delete(s,i,length(s)-i+1);
end; i:=0;
while s[i]<>' ' do begin c:=c+s[i]; i:=i+1; end; //выделение команды
delete(s,1,length(c)); i:=0;
while s[i]<>',' do begin reg:=reg+s[i]; i:=i+1; end; //выделение регистра-приемника
delete(s,1,length(reg)); i:=0;
while i<length(c) do begin //удаление лишних символов в названии команды
inc(i); if not (c[i] in s1) then begin delete(c,i,1); i:=i-1; end; end;
i:=0;
while i<length(reg) do begin //удаление лишних символов в названии регистра-приемника
inc(i); if not (reg[i] in s1) then begin delete(reg,i,1); i:=i-1; end; end;
i:=0;
while i<length(s) do begin //удаление лишних символов в названии регистра-источника
inc(i); if not (s[i] in s1) then begin delete(s,i,1); i:=i-1; end; end;
i:=0;
writeln('|',c,'|',reg,'|',s,'|');
label1:c:=''; s:=''; reg:='';
end;
close(f);
readln;
end.
