program z1;
var i,j:byte; f:text; s,c,reg,m:string; s5:set of char; ch:char;
cli,inc1,dec1,adc,cmp,xor1,sal,or1,jb:boolean;
label l1;
begin
cli:=false; inc1:=false; dec1:=false; adc:=false; cmp:=false;
xor1:=false; sal:=false; or1:=false; jb:=false;
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)]; i:=0;
assign(f,'temp4.txt'); reset(f);
i:=0;
while not(eof(f)) do begin
readln(f,s);
while not(s[i] in s5) do begin inc(i); //удаление пробелов в начале
while s[i]=' ' do delete(s,i,1); end; i:=0;
while s[i] <>' ' do begin c:=c+s[i]; i:=i+1; end; //выделение команды
delete(s,1,length(c)); delete(c,1,1); //удаление лишних символов
j:=0; i:=0;
if (c='jb') or (c='cli') then begin reg:=''; s:=''; goto l1; end;
for j:=1 to length(s) do begin if pos(',',s)<>0 then ch:=',' else ch:=' '; end;
while s[i] <>ch do begin reg:=reg+s[i]; i:=i+1; end; //выделение регистра-приемника
delete(s,1,length(reg)); delete(reg,1,1); i:=0;
while i<length(s) do begin //удаление лишних символов в названии регистра-источника
inc(i); if not (s[i] in s5) then begin delete(s,i,1); i:=i-1; end; end;


l1:writeln('|',c,'|',reg,'|',s,'|');
//проверка команд и их операндов
if (c='cli') and (reg='') and (s='') then begin cli:=true;
writeln('Operands of the command "',c,'" are ',cli); end;
if (c='jb') and (reg='') and (s='') then begin jb:=true;
writeln('Operands of the command "',c,'" are ',jb); end;


c:='';reg:='';
end;
close(f);
readln;
end.
