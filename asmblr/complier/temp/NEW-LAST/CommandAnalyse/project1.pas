program z1;
var s,c,l,reg,ds,ad,cs,cd:string; i,j,n:byte; s5: set of char;
f,a_res,temp1,temp2,temp3:text; ch:char;
label label1, label2,label3,l4;
begin
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)];  i:=0; j:=1;
s5:=s5+[chr(39)];//символ "'";
assign(f,'1.asm'); reset(f); //исходный файл
assign(a_res,'res.asm'); rewrite(a_res); //файл результатов распределения
assign(temp1,'temp1.txt'); rewrite(temp1); //временный файл списка сегментов
assign(temp2,'temp2.txt'); rewrite(temp2); //временный файл списка идентификаторов
assign(temp3,'temp3.txt'); rewrite(temp3); //временный файл списка директив
while not(eof(f)) do begin
l4:readln(f,s);
if s='' then goto l4; //пропуск пустых строк или строк-комментариев
if (s[1]=';') or (length(s)=0) then goto l4;
label3:if (s='cli') or (s='end') then begin c:=s; s:=''; reg:=''; goto label1; end;
while not(s[i] in s5) do begin inc(i); //удаление пробелов в начале
while s[i]=' ' do delete(s,i,1); end; i:=0;
for i:=1 to length(s) do begin //удаление комментариев
if s[i]=';' then delete(s,i,length(s)-i+1); end;
n:=length(s); while s[n]=' ' do begin delete(s,n,1); n:=n-1; end;
if s='' then goto label1; i:=0;
while s[i] <>' '{ch2} do begin c:=c+s[i]; i:=i+1; end; //выделение команды
delete(s,1,length(c)); delete(c,1,1); i:=0; //удаление лишних символов
while not(c[i] in s5) do begin inc(i); //удаление пробелов в начале
while c[i]=' ' do delete(c,i,1); end; i:=0;
if c[length(c)]=':' then begin l:=c; l:=l+'*'; delete(c,1,length(l)); goto label3 end;
if s='segment' then begin reg:=s; s:='';
writeln(temp1,c); goto label1; end;
if s='ends' then begin reg:=s; s:=''; goto label1; end;
if (c='inc') or (c='dec') or (c='jb') then begin reg:=s; s:=''; goto label1; end;
if c='assume' then begin
while s[i] <>':' do begin ds:=ds+s[i]; inc(i); end; //выделение 'ds'
delete(s,1,length(ds));  delete(ds,1,1);i:=0;
while s[i] <>',' do begin ad:=ad+s[i]; inc(i); end; //выделение 'data1'
delete(s,1,length(ad));  delete(ad,1,1);i:=0;
while s[i] <>':' do begin cs:=cs+s[i]; inc(i); end; //выделение 'cs'
delete(s,1,length(cs));  delete(cs,1,1);i:=0; cd:=s;
writeln(a_res,c,'|',ds,'|',ad,'|',cs,'|',cd,'|'); goto label2; end;
for j:=1 to length(s) do begin if pos(',',s)<>0 then ch:=',' else ch:=' '; end;
while s[i] <>ch do begin reg:=reg+s[i]; i:=i+1; end; //выделение регистра-приемника
delete(s,1,length(reg)); delete(reg,1,1); i:=0;
while not(reg[i] in s5) do begin inc(i); //удаление пробелов в начале
while reg[i]=' ' do delete(reg,i,1); end; i:=0;
while not(s[i] in s5) do begin inc(i); //удаление пробелов в начале
while s[i]=' ' do delete(s,i,1); end; i:=0;
if (reg='db') or (reg='dw') or (reg='dd') then writeln(temp2,c,' ',reg);
label1:
writeln(a_res,l,c,'|',reg,'/',s,'\');
if (c='end') or (reg='segment') or (reg='ends')
then writeln(temp3,c,' ',reg);
label2:c:=''; s:=''; reg:=''; ds:=''; ad:=''; cs:=''; cd:=''; l:='';
end; j:=1; i:=0;
writeln(a_res); writeln(a_res,'Segments:'); reset(temp1);
while not eof(temp1) do begin readln(temp1,s); writeln(a_res,s); end;
writeln(a_res); writeln(a_res,'Identifiers:'); reset(temp2);
while not eof(temp2) do begin readln(temp2,s); writeln(a_res,s); end;
close(f); close(a_res); close(temp1); close(temp2); close(temp3);
erase(temp1); //erase(temp2);
writeln('Analysing executed successful!');
readln;
end.

