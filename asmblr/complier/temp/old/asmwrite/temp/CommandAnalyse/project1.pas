program z1;
uses crt;
const
cq=9; //кол-во комманд
rq=33; //общее кол-во команд и регистров
var s,s1,c,reg,ds,ad,cs,cd:string; i,j,n:byte; s5: set of char;
f,a_res,temp1,temp2,temp3,temp4,f3:text; ch:char;
coms: array[1..cq] of string;
regs: array[1..rq] of string;
label label1, label2;
begin
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)];  i:=0; j:=1;
s5:=s5+[chr(39)];//символ "'";

assign(f3,'InitialData.txt'); reset(f3); //assign(f2,'1.txt'); rewrite(f2);
while i<cq do begin
inc(i); readln(f3,s); coms[i]:=s; end;
while not (eof(f3)) do begin
inc(i); readln(f3,s); regs[i]:=s; end;

assign(f,'1.asm'); reset(f); //исходный файл
assign(a_res,'res.asm'); rewrite(a_res); //файл результатов распределения
assign(temp1,'temp1.txt'); rewrite(temp1); //временный файл списка сегментов
assign(temp2,'temp2.txt'); rewrite(temp2); //временный файл списка идентификаторов
assign(temp3,'temp3.txt'); rewrite(temp3); //временный файл списка директив
assign(temp4,'temp4.txt'); rewrite(temp4); //временный файл списка правильных команд для дальнейшего анализа
j:=1;
while not(eof(f)) do begin
readln(f,s);
if (s='jb') or (s='cli') or (s='end') then begin c:=s; s:=''; reg:=''; goto label1; end;
if length(s)=0 then goto label1; //пропуск пустых строк
while not(s[i] in s5) do begin inc(i); //удаление пробелов в начале
while s[i]=' ' do delete(s,i,1); end; i:=0;
for i:=1 to length(s) do begin //удаление комментариев
if s[i]=';' then delete(s,i,length(s)-i+1); end; i:=0;
while s[i] <>' ' do begin c:=c+s[i]; i:=i+1; end; //выделение команды
delete(s,1,length(c)); delete(c,1,1); //удаление лишних символов
i:=0;
if s='segment' then begin reg:=s; s:='';
writeln(temp1,c); goto label1; end;
if s='ends' then begin reg:=s; s:=''; goto label1; end;
if (c='inc') or (c='dec') then begin reg:=s; s:=''; goto label1; end;
if c='assume' then begin
while s[i] <>':' do begin ds:=ds+s[i]; inc(i); end; //выделение 'ds'
delete(s,1,length(ds));  delete(ds,1,1);i:=0;
while s[i] <>',' do begin ad:=ad+s[i]; inc(i); end; //выделение 'data1'
delete(s,1,length(ad));  delete(ad,1,1);i:=0;
while s[i] <>':' do begin cs:=cs+s[i]; inc(i); end; //выделение 'cs'
delete(s,1,length(cs));  delete(cs,1,1);i:=0; cd:=s;
writeln(a_res,'|',c,'|',ds,'|',ad,'|',cs,'|',cd,'|'); goto label2; end;
for j:=1 to length(s) do begin if pos(',',s)<>0 then ch:=',' else ch:=' '; end;
while s[i] <>ch do begin reg:=reg+s[i]; i:=i+1; end; //выделение регистра-приемника
delete(s,1,length(reg)); delete(reg,1,1); i:=0;
if (reg='db') or (reg='dw') or (reg='dd') then writeln(temp2,c);
{while i<length(s) do begin //удаление лишних символов в названии регистра-источника
inc(i); if not (s[i] in s5) then begin delete(s,i,1); i:=i-1; end; end;}
label1: writeln(a_res,c,'|',reg,'/',s,'\');
if (c='end') or (reg='segment') or (reg='ends')
then writeln(temp3,c,' ',reg);
j:=0; for j:=0 to cq do if coms[j]=c then writeln(temp4,c,' ',reg,' ',s);
{if (reg='dd') or (reg='dw') and (s[1]=chr(39)) and (s[length(s)]=chr(39)) then
writeln(a_res,'Text constant can be used for db only!');}
label2:c:=''; s:=''; reg:=''; ds:=''; ad:=''; cs:=''; cd:='';
end; j:=1; i:=0;
writeln(a_res); writeln(a_res,'Segments:'); reset(temp1);
while not eof(temp1) do begin readln(temp1,s); writeln(a_res,s); end;
writeln(a_res); writeln(a_res,'Identifiers:'); reset(temp2);
while not eof(temp2) do begin readln(temp2,s); writeln(a_res,s); end;
close(f); close(a_res); close(temp1); close(temp2); close(temp3); close(temp4); close(f3);
erase(temp1); erase(temp2);
writeln('Analysing executed successful! Results were written of file res.asm.');
readln;
end.
