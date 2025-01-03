program z1;
uses crt,sysutils,dos;
const cq=9; //кол-во комманд
      rq=33; //общее кол-во команд и регистров
var s,s1,c,reg,ds,ad,cs,cd:string;
    i:byte;
    s5: set of char;
    coms: array[1..cq] of string;
    regs: array[1..rq] of string;
    f,f2,temp3:text;
    //имя файла, который нужно компилировать - 1.asm

procedure DataInit;
var ID:text;
begin
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)];  i:=0;
s5:=s5+[chr(39)];//символ "'";
assign(ID,'InitialData.txt'); reset(ID);
while i<cq do begin
inc(i); readln(ID,s); coms[i]:=s; end;
while not (eof(ID)) do begin
inc(i); readln(ID,s); regs[i]:=s; end;
close(ID);
end;

procedure filecreation; //формирование имени, создание пустого файла .lst
var s1,s2:string; n:byte; b:boolean;
begin
write('name of source file (.asm): '); read(s1); s2:=s1; readln;
n:= length(s1); b:= false;
for i:=0 to n do
if copy(s1,n-3,4)<>'.asm' then b:=true;
if b=true then begin s1:=s1+'.asm'; s2:=s2+'.lst'; end else begin
delete(s2,length(s2)-2,3); insert('lst',s2,length(s2)+1);end;
assign(f,s1);
{$I-} reset(f); {$I+}
if IOResult <> 0 then begin writeln('file does not exist'); readln; halt; end
else begin
assign(f2,s2); rewrite(f2);
writeln('Empty file .lst was successfully created!');
end; end;

Function lz(W : Word) : String; //ф-я дописывает "0", если дата или время меньше 10
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
end;
procedure filefilling; //заполнение результирующего файла .lst
Var h,m,s,hd:word;//h-год,час, m-месяц,минута, s-день месяца,секунда
    s1:string; c:integer;
begin
reset(f);
write(f2,'Assembler complier variant 11                    ');
getdate(h,m,s,hd);write(f2,lz(s),'.',lz(m),'.',lz(h));
gettime(h,m,s,hd);write(f2,' ',lz(h),':',lz(m),':',lz(s));
writeln(f2);
c:=0;
while not(eof(f)) do begin
readln(f,s1); inc(c); if c<10 then write(f2,' ');
writeln(f2,c,'  ',hxd(c),'  ',s1);
end;
writeln('File .lst successfully writed!');
end;

procedure CommandAnalyse;
var j,n:byte; a_res,temp1,temp2:text; ch:char;
label label1, label2;
begin
assign(a_res,'res.asm'); rewrite(a_res); //файл результатов распределения
assign(temp1,'temp1.txt'); rewrite(temp1); //временный файл списка сегментов
assign(temp2,'temp2.txt'); rewrite(temp2);  //временный файл списка идентификаторов
assign(temp3,'temp3.txt'); rewrite(temp3);  //временный файл списка директив
//assign(temp4,'temp4.txt'); rewrite(temp4); //временный файл списка правильных команд для дальнейшего анализа
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
while i<length(s) do begin //удаление лишних символов в названии регистра-источника
inc(i); if not (s[i] in s5) then begin delete(s,i,1); i:=i-1; end; end;
label1: writeln(a_res,'|',c,'|',reg,'|',s,'|');
if (c='end') or (reg='segment') or (reg='ends')
then writeln(temp3,c,' ',reg);
//j:=0; for j:=0 to cq do if coms[j]=c then writeln(temp4,c,' ',reg,' ',s);
if (reg='dd') or (reg='dw') and (s[1]=chr(39)) and (s[length(s)]=chr(39)) then
writeln(a_res,'Text constant can be used for db only!');
label2:c:=''; s:=''; reg:=''; ds:=''; ad:=''; cs:=''; cd:='';
end; j:=1; i:=0;
writeln(a_res); writeln(a_res,'Segments:'); reset(temp1);
while not eof(temp1) do begin readln(temp1,s); writeln(a_res,s); end;
writeln(a_res); writeln(a_res,'Identifiers:'); reset(temp2);
while not eof(temp2) do begin readln(temp2,s); writeln(a_res,s); end;
close(a_res); close(temp1); close(temp2);
erase(temp1); erase(temp2);
writeln('Analysing executed successful! Results were written of file res.asm.');
end;
{--------------------Процедуры и функции проверки ошибок--------------------}
function identifier(s:string):boolean;
var a:set of char; b:boolean;
il,ic: boolean; //ic - содержимое, il - длина
begin
il:=false; ic:=false;
for i:= 48 to 57 do a:=a+[chr(i)]; i:=0;
for i:= 65 to 90 do a:=a+[chr(i)]; i:=0;
if length(s)>8 then il:=true;
for i:=1 to length(s) do if not (s[i] in a) then ic:=true;
if il=true then writeln('Incorrect length of identifier!');
if ic=true then writeln('Undefined symbols of identifier!');
if (il=true) or (ic=true) then identifier:=false else identifier:=true;
end;

function constant(s:string):boolean;
var h1,d1,b1:set of char;
    h,d,b,t:boolean;
    k:integer; ch:char;
begin
h:=false; d:=false; b:=false; t:=false;
for i:= 48 to 57 do h1:=h1+[chr(i)]; i:=0;
for i:= 97 to 102 do h1:=h1+[chr(i)]; i:=0;
for i:= 48 to 57 do d1:=d1+[chr(i)]; i:=0;
for i:= 48 to 49 do b1:=b1+[chr(i)]; i:=0;
if s[length(s)]='h' then h:=true;
if s[length(s)]='b' then b:=true;
if (s[length(s)]='d') or (s[length(s)] in d1) then d:=true;
if (s[1]=chr(39)) and (s[length(s)]=chr(39)) then t:=true;
if (h=false) and (d=false) and (b=false) and (t=false)
then begin writeln('Incorrect constant'); exit; end;
if h=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in h1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect hexadecimal constant');
if k=0 then exit;
end; i:=0; k:=0;
if d=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in d1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect decimal constant ');
if k=0 then exit;
end; i:=0; k:=0;
if b=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in b1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect binary constant ');
if k=0 then exit;
end;
if t=true then exit;
constant:=false;
end;

procedure directive;
var
ds,cs,de,ce,e:boolean;
begin
reset(temp3);
while not eof(temp3) do begin
readln(temp3,s);
if s='data segment' then ds:=true;
if s='data ends' then de:=true;
if s='code segment' then cs:=true;
if s='code ends' then ce:=true;
if s='end ' then e:=true;
end;
if ds=false then writeln('Data segment does not exist!');
if de=false then writeln('No data ends directive!');
if cs=false then writeln('Code segment does not exist!');
if ce=false then writeln('No code ends directive!');
if e=false then writeln('No end directive!');
if (ds=true) and(de=true) and(cs=true) and(ce=true) and(e=true)
then writeln('All directives are right');
close(temp3); erase(temp3);
end;

begin
DataInit;
filecreation;
CommandAnalyse;
directive;
filefilling;

close(f); close(f2);
readln;
end.
