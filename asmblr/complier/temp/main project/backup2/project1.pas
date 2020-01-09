program complier;
uses crt,dos,sysutils;
const
cq=9; //кол-во комманд
rq=33; //общее кол-во команд и регистров
var f1,f2:text; i:byte;
    s,c,reg,ds,ad,cs,cd:string;
    s1: set of char;
    coms: array[1..cq] of string;
    regs: array[1..rq] of string;
{procedure filecreation; //формирование имени, создание пустого файла .lst
var s1,s2:string; n:byte; b:boolean;
begin
write('name of source file (.asm): '); read(s1); s2:=s1; readln;
n:= length(s1); b:= false;
for i:=0 to n do
if copy(s1,n-3,4)<>'.asm' then b:=true;
if b=true then begin s1:=s1+'.asm'; s2:=s2+'.lst'; end else begin
delete(s2,length(s2)-2,3); insert('lst',s2,length(s2)+1);end;
assign(f1,s1);
{$I-} reset(f1); {$I+}
if IOResult <> 0 then begin writeln('file does not exist'); readln; exit; end
else begin
assign(f2,s2); rewrite(f2);
writeln('Empty file .lst was successfully created!');
end; end;}

{Function lz(W : Word) : String; //ф-я дописывает "0", если дата или время меньше 10
Var S : String;
Begin
Str(W:0, S);
If Length(S) = 1 Then S:='0'+S;
lz:=S;
End;

function hxd(n:integer):string; //перевод числа в 16-ричную систему
var i,c,w,k:integer; s,sr:string; ch:char;
begin
for i:=1 to 4 do begin
  c:=n mod 16;
  n:=n div 16;
  sr:=inttostr(c);
  if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
  if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
  s:=s+sr;
end;
n:= length(s) div 2;
for i:= 1 to n do begin
ch:= s[i];
s[i]:= s[length(s)-i+1];
s[length(s)-i+1] := ch;
end;
hxd:=s;
end; }
{procedure filefilling; //заполнение результирующего файла .lst
Var h,m,s,hd:word;//h-год,час, m-месяц,минута, s-день месяца,секунда
    s1:string; c:integer;
begin
write(f2,'Assembler complier variant 11                    ');
getdate(h,m,s,hd);write(f2,lz(s),'.',lz(m),'.',lz(h));
gettime(h,m,s,hd);write(f2,' ',lz(h),':',lz(m),':',lz(s));
writeln(f2);
c:=0;
while not(eof(f1)) do begin
readln(f1,s1); inc(c); if c<10 then write(f2,' ');
writeln(f2,c,'  ',hxd(c),'  ',s1);
end;
writeln('File .lst successfully writed!');
end;}
procedure FileAnalyse;
var
   a_res,temp1,temp2:text;
   ch:char;
   s5: set of char;
   j,n:byte;
label label1,label2;
begin
  assign(a_res,'res.asm'); rewrite(a_res); //файл результатов распределения
  assign(temp1,'temp1.txt'); rewrite(temp1); //временный файл списка сегментов
  assign(temp2,'temp2.txt'); rewrite(temp2);  //временный файл списка идентификаторов
  j:=1;
  assign(f1,'1.asm'); reset(f1);
  while not(eof(f1)) do begin
  readln(f1,s);
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
  while i<length(s) do begin //удаление лишних символов в названии регистра-источника
  inc(i); if not (s[i] in s5) then begin delete(s,i,1); i:=i-1; end; end;
  label1:
  writeln(a_res,'|',c,'|',reg,'|',s,'|');
  label2:c:=''; s:=''; reg:=''; ds:=''; ad:=''; cs:=''; cd:='';
  end;
  j:=1; i:=0;
  writeln(a_res); writeln(a_res,'Segments:'); reset(temp1);
  while not eof(temp1) do begin readln(temp1,s); writeln(a_res,s); end;
  writeln(a_res); writeln(a_res,'Identifiers:'); reset(temp2);
  while not eof(temp2) do begin readln(temp2,s); writeln(a_res,s); end;
  {close(f);} close(f1); close(a_res); close(temp1); close(temp2);
  erase(temp1); erase(temp2);
  writeln('Analysing executed successful! Results were written of file res.asm.');
end;
{procedure FileAnalyse;
label label1;
begin
while not(eof(f1)) do begin
readln(f1,s);
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
end; end; }
procedure DataInit;
var f:text;
begin
for i:= 65 to 122 do s1:=s1+[chr(i)]; i:=0;
for i:= 48 to 57 do s1:=s1+[chr(i)];  i:=0;
s1:=s1+[chr(39)];//символ "'";
assign(f,'InitialData.txt'); reset(f);
while i<cq do begin
inc(i); readln(f,s); coms[i]:=s; end;
while not (eof(f)) do begin
inc(i); readln(f,s); regs[i]:=s; end;
close(f);
end;
begin
//filecreation;
//filefilling;
DataInit;
FileAnalyse;
close(f1); //close(f2);
readln;
end.
