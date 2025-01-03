uses sysutils,crt,dos;
var jbl{адрес метки (для jb)},m{//$}:integer;
    g,labels,temp,f{.asm},f2{файл .lst},segf:text;
    s,a,b,c,{исходные строки} a1,b1,c1,cop1,{предыдущие строки}
    com,{комментарий}dt,{тип переменной (db,dw,dd)}
    cop{код операции},regn{номер регистра},dtb{код регистра},
    cc{код команды},pr,pr2{префиксы},od{смещение переменной},
    s0,sn{строка исходного файла .asm},mis{error},labl:string;
    i{counter}:integer; numbers:set of char; t:longint;
    bol{комментарий},ordb{bin или dec},
    jbprov,decprov,prov:boolean; we,se{errors}:byte;
    r:integer;{результат определения типа}
//перевод числа из десятичной в 16-ричную систему
function hxd(n:integer):string;
var i,c:integer; s,sr:string; ch:char;
begin
for i:=1 to 4 do begin
  c:=n mod 16;
  n:=n div 16;
  sr:=inttostr(c);
  if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
  if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
  s:=sr+s;
end;
hxd:=s; end;
//перевод числа из двоичнуой системы в десятичную
function bintodec(s:string):string;
var n,i,k,b,r,j:integer;
begin
k:= length(s); i:=1; b:=1;
for i:=2 to k do b:=b*2+strtoint(s[i]);
bintodec:=inttostr(b); end;
//перевод числа из двоичной в 16-ричную систему
function bintohex(s:string):string;
var n,i,k,b,r,j:integer;
begin
k:= length(s)-1; i:=1; b:=0;
while i<>length(s)+1 do begin
n:=strtoint(s[i]); inc(i);
r:=1; for j:=1 to k do r:=r*2; k:=k-1;
b:=b+(r*n);
end; bintohex:=inttostr(b);
bintohex:=hxd(b);
end;

//перевод числа из 16ричной системы в десятичную
function hextodec(s:string):string;
var r,b:int64; i,j,k,n:byte; s6:set of char;
begin
for i:= 65 to 70 do s6:=s6+[chr(i)];
for i:= 97 to 102 do s6:=s6+[chr(i)];
k:=length(s)-1; i:=1; b:=0;
if s[length(s)]='h' then delete(s,length(s),1);
while i<>length(s)+1 do begin
if s[i] in s6 then
case s[i] of
'A':n:=10; 'B':n:=11; 'C':n:=12;
'a':n:=10; 'b':n:=11; 'c':n:=12;
'D':n:=13; 'E':n:=14; 'F':n:=15;
'd':n:=13; 'e':n:=14; 'f':n:=15; end
else n:=strtoint(s[i]);
inc(i);
b:=b*16+n; end;
hextodec:=inttostr(b); end;
function reg(s:string):byte; //определение разрядности регистра
begin
case s of
'al':reg:=8; 'ax':reg:=16; 'eax':reg:=32;
'cl':reg:=8; 'cx':reg:=16; 'ecx':reg:=32;
'dl':reg:=8; 'dx':reg:=16; 'edx':reg:=32;
'bl':reg:=8; 'bx':reg:=16; 'ebx':reg:=32;
'ah':reg:=8; 'sp':reg:=16; 'esp':reg:=32;
'ch':reg:=8; 'bp':reg:=16; 'ebp':reg:=32;
'dh':reg:=8; 'si':reg:=16; 'esi':reg:=32;
'bh':reg:=8; 'di':reg:=16; 'edi':reg:=32;
end; end;
//функции определения кода регистра
function regcode(s:string):string;
begin
if (s='al') or (s='ax') or (s='eax') then regcode:='000';
if (s='cl') or (s='cx') or (s='ecx') then regcode:='001';
if (s='dl') or (s='dx') or (s='edx') then regcode:='010';
if (s='bl') or (s='bx') or (s='ebx') then regcode:='011';
if (s='ah') or (s='sp') or (s='esp') then regcode:='100';
if (s='ch') or (s='bp') or (s='ebp') then regcode:='101';
if (s='dh') or (s='si') or (s='esi') then regcode:='110';
if (s='bh') or (s='di') or (s='edi') then regcode:='111';
end;
//ф-я определения типа переменной (db,dw,dd)
function typedef(k:string):string;
var f:text; s,a,b:string; i:byte;
begin
assign(f,'idlist.txt'); reset(f);
while not eof(f) do begin
readln(f,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(b,1,1);
if k=a then typedef:=b; a:=''; b:='';
end;
close(f); end;
//ф-я определения смещения переменной
function offsetdef(k:string):string;
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
if k=a then offsetdef:=c;
a:=''; b:=''; c:='';
end; close(f); end;
//ф-я определения типа числа (2,10 или 16)
function numdef(s:string):byte;
var s5:set of char; i:byte;
begin
for i:= 48 to 57 do s5:=s5+[chr(i)];
if s[length(s)]='b' then numdef:=2;
if s[length(s)] in s5 then numdef:=10;
if s[length(s)]='d' then numdef:=11;
if s[length(s)]='h' then numdef:=16; end;
//ф-я определения количества байт
function dollar(s:string):integer;
var c:string; i,j,n,k:integer;
begin
n:=0; s:=s+' ';
for j:=1 to length(s) do if s[j]=' ' then inc(n);
dollar:=n; end;
//===============================коды команд====================================
//----------inc----------
function com_inc(b:string):string;
begin
r:=reg(b); if r=8 then regn:='11000' else regn:='1000';
dtb:=regcode(b); regn:=regn+dtb;
cop:=bintohex(regn); delete(cop,1,2);
if r=8 then begin cc:='FE '; insert(cc,cop,1); end;
if r=32 then insert(pr,cop,1);
com_inc:=cop; end;
//----------dec----------
function com_dec(b:string):string;
var s1,s2,s3,r:string; j:byte; ch:char;
l1:set of char; t1,t2:integer;
begin r:=b;
for i:= 97 to 122 do l1:=l1+[chr(i)]; i:=0;
if pos('[',r)=0 then begin; s1:=r; regn:=''; end;//begin reg:='0E '; s1:=r; end;
if pos('[',r)<>0 then begin
while r[i]<>'[' do begin s1:=s1+r[i]; inc(i); end; delete(s1,1,1);//идентификатор
j:=pos('[',r)+1;
while r[j]<>']' do begin s2:=s2+r[j]; inc(j); end; regn:=s2;//полное выражение в скобках
if (pos('-',r)<>0) or (pos('+',r)<>0) then begin
i:=pos('-',r); j:=pos('+',r); if i>0 then ch:='-' else ch:='+'; i:=0;
while s2[i]<>ch do begin s3:=s3+s2[i]; inc(i); end;
delete(s3,1,1); regn:=s3; delete(s2,1,length(s3)); ch:=s2[1];//действие
delete(s2,1,1);t1:=strtoint(s2);//операнд
end; end; //========================================
dt:=typedef(s1); if dt='byte' then r:='FE ';
if (dt='word') or (dt='dword') then r:='FF ';
if dt='dword' then insert(pr,r,1); od:=offsetdef(s1);
if ch<>'' then begin //вычисление выражения
od:=hextodec(od); t2:=strtoint(od);
case ch of '-': t2:=t2-t1; '+': t2:=t2+t1; end;
od:=hxd(t2); end;
case regn of 'di': s1:='8D '; 'si': s1:='8C '; 'bx': s1:='8F ';
'ebx': s1:='8B '; 'esi': s1:='8E '; 'edi': s1:='8F '; '': s1:='0E 'end;
if (regn='ebx') or (regn='esi') or (regn='edi') then begin
insert(pr2,r,1); for i:=1 to 4 do insert('0',od,1); decprov:=true; end;
com_dec:=r+s1+od+' R';
end;
//----------adc----------
function com_adc(b,c:string):string;
begin
regn:='11'; dtb:=regcode(b); insert(dtb,regn,3);
dtb:=regcode(c); insert(dtb,regn,6);
cop:=bintohex(regn); delete(cop,1,2);
r:=reg(b); if r=8 then cc:='12 ' else cc:='13 ';
insert(cc,cop,1);
if r=32 then insert(pr,cop,1);
com_adc:=cop; end;
//----------cmp----------
function com_cmp(b,c:string):string;
var sc,s1,s2,s3,r1,r2,
pr1,pr2,pr3:string; l1,l2:set of char;
n1,n2,k:longint; ch:char; r:byte;
label m1;
begin sc:=c; n1:=0; n2:=0; k:=0;
for i:= 97 to 122 do l1:=l1+[chr(i)];
for i:= 48 to 57 do l2:=l2+[chr(i)];
if pos('[',sc)=0 then begin
dt:=typedef(sc);
if dt='byte' then cop:='3A ';
if (dt='word') or (dt='dword') then cop:='3B ';
regn:=regcode(b)+'110';
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(sc); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1);
end else begin //---------------------------
i:=0; while sc[i]<>'[' do begin s1:=s1+sc[i]; inc(i); end;
delete(s1,1,1); //const----------------------------
delete(sc,1,length(s1)+1); delete(sc,length(sc),1);
if (pos('+',sc)=0) and (pos('-',sc)=0)
then begin s2:=sc; goto m1; end
else begin if pos('+',sc)>0 then ch:='+' else ch:='-';
i:=0; while sc[i]<>ch do begin s2:=s2+sc[i]; inc(i); end;
delete(s2,1,1); delete(sc,1,length(s2)+1);
if (pos('+',sc)=0) and (pos('-',sc)=0) then begin
if sc[1] in l1 then begin s2:=s2+'+'+sc; goto m1; end;
if sc[1] in l2 then begin n1:=strtoint(sc); goto m1; end;
end else begin if pos('+',sc)>0 then ch:='+' else ch:='-';
i:=0; while sc[i]<>ch do begin s3:=s3+sc[i]; inc(i); end;
delete(s3,1,1); s2:=s2+'+'+s3; delete(sc,1,length(s3)+1);
n1:=strtoint(sc);
end; end;
m1:
r:=reg(s2); if r=32 then r2:=regcode(s2) else
case s2 of
'bx+si': r2:='000'; 'bx+di': r2:='001';
'bp+si': r2:='010'; 'bp+di': r2:='011';
'si': r2:='100'; 'di': r2:='101';
'bp': r2:='110'; 'bx': r2:='111'; end;
r1:=regcode(b);
if (s2='bp+si') or (s2='bp+di') or (s2='bp') or (s2='ebp')
then pr3:='3E: ';
regn:='10'+r1+r2; regn:=bintohex(regn); delete(regn,1,2);
dt:=typedef(s1);
if dt='dword' then pr2:='66| ';
if dt='byte' then dt:='3A ';
if (dt='word') or (dt='dword') then dt:='3B ';
//-------
s2:=offsetdef(s1);
if ch<>'' then begin  s3:=hextodec(s2); n2:=strtoint(s3);
if ch='+' then k:=n1+n2 else k:=n2-n1;
s2:=hxd(k); end;
if r=32 then pr1:='67& ';
if r=32 then begin insert('0000',s2,1); decprov:=true; end;
cop:=pr1+pr2+pr3+cop+dt+regn+' '+s2+' R';
end;
com_cmp:=cop; cop:='';
end;
//----------xor----------
function com_xor(b,c:string):string;
begin
dt:=typedef(c);
if dt='byte' then cop:='32 ';
if (dt='word') or (dt='dword') then cop:='33 ';
regn:='110'; dtb:=regcode(b); insert(dtb,regn,1);
cc:=bintohex(regn); delete(cc,1,2);
cop:=cop+cc+' '; od:=offsetdef(c); cop:=cop+od+' R';
if dt='dword' then insert(pr,cop,1);
com_xor:=cop; end;
//----------sal----------
function com_sal(b,c:string):string;
begin
r:=reg(b); if r=8 then cop:='C0 ' else cop:='C1 ';
dtb:=regcode(b); insert('11100',dtb,1);
cc:=bintohex(dtb); delete(cc,1,2);
cop:=cop+cc+' '; if r=32 then insert(pr,cop,1);
r:=numdef(c);
if r=2 then begin dtb:=c;
delete(dtb,length(dtb),1); cc:=bintohex(dtb); delete(cc,1,2); end;
if r=10 then begin t:=strtoint(c); cc:=hxd(t); delete(cc,1,2); end;
if r=11 then begin dtb:=c; delete(dtb,length(dtb),1);
t:=strtoint(dtb); cc:=hxd(t); delete(cc,1,2); end;
if r=16 then begin dtb:=c;
delete(dtb,length(dtb),1); cc:=dtb; end;
cop:=cop+cc; com_sal:=cop; end;
//----------or----------
function com_or(b,c:string):string;
begin r:=0; dtb:=''; dt:=''; cc:=''; regn:=''; t:=0; regn:=''; cop:='';
dtb:=c;
r:=numdef(dtb);
dt:=offsetdef(b);
regn:=typedef(b);
if r=2 then begin
delete(dtb,length(dtb),1);
cc:=bintodec(dtb);
t:=strtoint(cc);
cc:=hxd(t); end;
if r=10 then begin t:=strtoint(dtb); cc:=hxd(t); end;
if r=11 then begin delete(dtb,length(dtb),1);
t:=strtoint(dtb); cc:=hxd(t); end;
if r=16 then begin delete(dtb,length(dtb),1);
cc:=hextodec(dtb); t:=strtoint(cc); cc:=dtb; end;
if (regn='byte') and (t<256) then begin cop:='80 0E '; delete(cc,1,2); end;
if (regn<>'byte') and (t>127) then cop:='81 0E ';
if (regn<>'byte') and (t<128) then cop:='83 0E ';
if (regn<>'byte') and (t<128)
and (length(cc)=4) then delete(cc,1,2);
if (regn='dword') and (t>128) then
for i:=1 to 8-length(cc) do insert('0',cc,1);
cop:=cop+dt+' R '+cc;
if regn='dword' then insert(pr,cop,1);
r:=(length(cc) div 2-1);
t:=dollar(cop)+r;
com_or:=cop; end;
//----------jb----------
function com_jb(k:string):string;
var x,y:string; k1,k2:integer;
begin k:=k+':';
assign(labels,'labels.asm'); reset(labels);
while not eof(labels) do begin
readln(labels,x); i:=0;
while x[i]<>' ' do begin y:=y+x[i]; inc(i); end;
delete(y,1,1); delete(x,1,length(y)+1);
if x=k then cc:=y;
y:=''; end; close(labels);
k1:=strtoint(cc);
if k1>m then k2:=k1-m;
if k2<127 then begin k2:=k2-2; t:=2; cc:='72 ';
x:=hxd(k2); delete(x,1,2); end
else begin k2:=k2-2; t:=4; cc:='0F 82 '; x:=hxd(k2); end;
if k1<m then //begin
if m<127 then begin k2:=256-m+k1-2; t:=2; cc:='72 ';
x:=hxd(k2); delete(x,1,2); end
else begin k2:=65536-m+k1-4; t:=4; cc:='0F 82 '; x:=hxd(k2); end;
com_jb:=cc+x//hxd(k2);
end;
//ф-я дописывает "0", если дата или время меньше 10
function lz(w:word):string;
var s:string;
begin
str(w:0,s); if length(S)=1
then s:='0'+S; lz:=s;
end;
procedure FirstPass;
var s,c,l,reg,ds,ad,cs,cd,s2:string; i,j,n:byte; s5: set of char;
a_res,temp1,temp2,temp3:text; ch:char; b:boolean; h,m,s8,hd:word;
label label1, label2,label3,l4;
begin
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)];  i:=0; j:=1;
s5:=s5+[chr(39)];//символ "'";
write('name of source file (.asm): '); read(sn); s2:=sn; readln;
n:= length(sn); b:= false;
for i:=0 to n do
if copy(sn,n-3,4)<>'.asm' then b:=true;
if b=true then begin sn:=sn+'.asm'; s2:=s2+'.lst'; end else begin
delete(s2,length(s2)-2,3); insert('lst',s2,length(s2)+1);end;
assign(f,sn);
{$I-} reset(f); {$I+}
if IOResult <> 0 then begin writeln('file does not exist'); readln; halt; end
else begin assign(f2,s2); rewrite(f2); end;
write(f2,'Assembler complier variant 11                    ');
getdate(h,m,s8,hd);write(f2,lz(s8),'.',lz(m),'.',lz(h));
gettime(h,m,s8,hd);write(f2,' ',lz(h),':',lz(m),':',lz(s8));
writeln(f2);
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
erase(temp1);
writeln('Analysing executed successful!'); end;
procedure datasegment;
var g,temp,il:text;
    s,a,b,c,b1,c1,l,p,p1,seg,dt,ms:string;
    i,m,k,pt:integer;
    t,t1:real; numbers,ml:set of char;
label l1,m8,m9;
begin m:=0;
for i:= 97 to 122 do ml:=ml+[chr(i)];
assign(f,sn); reset(f);
assign(segf,'segments.txt'); rewrite(segf);
assign(g,'res.asm'); reset(g); b1:='segment'; prov:=false;
assign(il,'idlist.txt'); rewrite(il);
for i:= 48 to 57 do numbers:=numbers+[chr(i)];
for i:= 97 to 122 do ml:=ml+[chr(i)]; i:=0;
while not eof(g) do begin
i:=0; readln(g,s);
readln(f,ms);
while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(s,1,length(a)); delete(a,1,1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
if b='segment' then seg:=a;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
//--------errors----------
if length(a)>8 then mis:='Identifier can not contain more then 8 symbols!';
if (b<>'ends') and (b<>'segment') then
while i<length(a) do begin
  if a[i] in ml then
  mis:='Small letters are not supported in identifier!';
  inc(i); end;
{m9:if (b<>'ends') and (b<>'segment') then
if (b<>'db') and (b<>'dw') and (b<>'dd') then begin writeln(f2,ms);
mis:='Directive not supported!'; goto m8; end;}
//------------------------
if b1='db' then m:=m+1;
if b1='dw' then m:=m+2;
if b1='dd' then m:=m+4;
if (b1='db') and (c1[1]=chr(39)) and (c1[length(c1)]=chr(39)) then m:=m+length(c1)-3;
if c='' then goto l1;
if (c[1]=chr(39)) and (c[length(c)]=chr(39)) then begin //текстовая константа для db
p1:=c; delete(p1,1,1); delete(p1,length(p1),1);
for i:=1 to length(p1) do begin
k:=ord(p1[i]); l:=hxd(k); delete(l,1,2); p:=p+l+' '; end; delete(p,length(p),1); end;
if (c[length(c)]='h') and (b='db') then begin //шестнадцатиричная система для db
p:=c; delete(p,length(p),1); end;
if (c[length(c)]='h') and (b='dw') then begin //шестнадцатиричная система для dw
p1:=c; delete(p1,length(p1),1); for i:=1 to 4-length(p1) do p:=p+'0'; p:=p+p1; end;
if (c[length(c)]='h') and (b='dd') then begin //шестнадцатиричная система для dd
p1:=c; delete(p1,length(p1),1); for i:=1 to 8-length(p1) do p:=p+'0'; p:=p+p1; end;
{if (c[length(c)]='d') and (b='db') then begin //десятичная система для db
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); p:=hxd(pt); delete(p,1,2); end;}
if (c[length(c)] in numbers) and (b='db') then begin
p1:=c; pt:=strtoint(p1); p:=hxd(pt); delete(p,1,2); end;
if (c[length(c)]='d') and (b='dw') then begin //десятичная система для dw
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); p:=hxd(pt); end;
if (c[length(c)] in numbers) and (b='dw') then begin
p1:=c; pt:=strtoint(p1); p:=hxd(pt) end;
if (c[length(c)]='d') and (b='dd') then begin //десятичная система для dd
p1:=c; delete(p1,length(p1),1); pt:=strtoint(p1); prov:=true; p:=hxd(pt);
prov:=false; end;
if (c[length(c)] in numbers) and (b='dd') then begin
p1:=c; pt:=strtoint(p1); prov:=true; p:=hxd(pt);
prov:=false; end;
if (c[length(c)]='b') and (b='db') then begin //двоичная система для db
p1:=c; delete(p1,length(p1),1); p:=bintohex(p1); delete(p,1,2); end;
if (c[length(c)]='b') and (b='dw') then begin //двоичная система для dw
p1:=c; delete(p1,length(p1),1); p:=bintohex(p1); end;
if (c[length(c)]='b') and (b='dd') then begin //двоичная система для dd
p1:=c; delete(p1,length(p1),1); prov:=true; p:=bintohex(p1); prov:=false; end;
case b of
'db': dt:='byte';
'dw': dt:='word';
'dd': dt:='dword'; end;
if (b='db') or (b='dw') or (b='dd') then
writeln(il,a,' ',dt,'| ',hxd(m),' ',seg,'*');
l1:writeln(f2,hxd(m),' ',p,'  ',ms);
m8: if mis<>'' then begin writeln(f2,'ERROR: ',ms,' ',mis);
writeln('ERROR: ',ms,' ',mis); case mis of
'Identifier can not contain more then 8 symbols!': inc(we);
'Small letters are not supported in identifier!': inc(we);
//'Directive not supported!': inc(se);
end;
end;
if b='ends' then writeln(segf,a,' . . . . . 16 bit ', hxd(m));
if (a='data') and (b='ends') then break;
b1:=b; c1:=c;
a:=''; b:=''; c:=''; p:=''; mis:='';
end;
close(g); close(il); close(f);
writeln('Data segment successfully analized!');
end;
procedure commandcode;
label l1,l2,m9; var ms:string; temp:text;
begin
assign(f,sn); reset(f);
assign(temp,'tmp.txt'); reset(f);
assign(g,'res.asm'); reset(g); b1:='segment';
if jbprov=false then begin
assign(labels,'labels.asm'); rewrite(labels); end;
assign(temp,'temp.asm'); rewrite(temp);
for i:= 48 to 57 do numbers:=numbers+[chr(i)]; i:=0;
a:=''; b:=''; c:='';
pr:='66| '; //префикс замены разрядности (для 32-разрядных данных)
pr2:='67& ';
while not eof(g) do begin
l2:readln(g,s); readln(f,ms); if s='end' then break;
i:=0; bol:=false;
if pos('*',s)<>0 then
begin i:=0; while s[i]<>'*' do begin com:=com+s[i]; inc(i); end;
delete(s,1,length(com)); delete(com,1,1); i:=0; end;
i:=0; while s[i]<>'|' do begin a:=a+s[i]; inc(i); end;
delete(a,1,1);
if (a='assume') and (jbprov=false) then begin a:=''; goto l2; end;
if (a='assume') and (jbprov=true) then begin writeln(f2,ms); a:=''; goto l2; end;
delete(s,1,length(a)+1); i:=0;
while s[i]<>'/' do begin b:=b+s[i]; inc(i); end;
delete(s,1,length(b)); delete(b,1,1); i:=0;
if (b='db') or (b='dw') or (b='dd') or (a='data') or (s='end')
then begin a:=''; b:=''; goto l2; end;
while s[i]<>'\' do begin c:=c+s[i]; inc(i); end;
delete(s,1,length(c)); delete(c,1,1); i:=0;
if (cop1<>'') and (a1<>'or') and(a1<>'jb') {and (jbprov=false)} then m:=m+dollar(cop1);
if (a1='jb') and(jbprov=false) then m:=m+2;//найти почему нужно там +2 а там +1
if (a1='jb') and(jbprov=true) then m:=m+t;//m:=m+1;
if a1='or' then m:=m+t;
if (b1='segment') or (a1='end') or (a='end') then m:=0;
if decprov=true then begin m:=m+2; decprov:=false; end;
case a of'cli': cop:='FA'; 'inc': cop:=com_inc(b);
'dec': cop:=com_dec(b); 'adc': cop:=com_adc(b,c);
'cmp': cop:=com_cmp(b,c); 'xor': cop:=com_xor(b,c);
'sal': cop:=com_sal(b,c); 'or': cop:=com_or(b,c); end;
if (a='jb') and (jbprov=true) then cop:=com_jb(b);
if (jbprov=false) and(com<>'') then writeln(labels,m,' ',com);
//=============================================================================
l1: if jbprov=true then begin
writeln(f2,hxd(m),' ',cop,' ',com,' ',ms);
m9: if mis<>'' then begin writeln(f2,'ERROR: ',ms,' ',mis);
writeln('ERROR: ',ms,' ',mis); inc(se); end;
if b='ends' then writeln(segf,a,' . . . . . 16 bit ', hxd(m));
end;
if a='end' then break;
a1:=a; b1:=b; c1:=c; cop1:=cop;
a:=''; b:=''; c:=''; com:=''; cop:=''; regn:=''; mis:='';
end;
close(g); close(temp);
if jbprov=false then close(labels);
end;

procedure tablefilling;
begin
assign(g,'segments.txt'); reset(g);
writeln(f2,'');
writeln(f2,'     LIST OF SEGMENTS');
while not eof(g) do begin
readln(g,s); writeln(f2,s); end;
writeln(f2,''); a:=''; b:=''; c:=''; close(g);
assign(g,'idlist.txt'); reset(g);
writeln(f2,'   LIST OF IDENTIFIERS AND LABELS');
writeln(f2,'Name            Type  Offset  Attr');
while not eof(g) do begin
readln(g,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete(a,1,1); delete(s,1,length(a)+1); i:=0;
while s[i]<>'|' do begin b:=b+s[i]; inc(i); end;
delete(b,1,1); delete(s,1,length(b)+2); i:=0;
while s[i]<>' ' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1); delete(s,1,length(c)); i:=0;
delete(s,1,1); delete(s,length(s),1);
writeln(f2,a,' . . . . . ',b,'   ',c,'   ',s);
a:=''; b:=''; c:='';
end; close(g); a:='';
assign(g,'labels.asm'); reset(g);
while not eof(g) do begin
readln(g,s); i:=0;
while s[i]<>' ' do begin a:=a+s[i]; inc(i); end;
delete (a,1,1); delete(s,1,length(a)); delete(s,1,1);
delete(s,length(s),1);
m:=strtoint(a);
writeln(f2,s,' . . . . . . . Near    ',hxd(m),'   code');
a:='';
end;
writeln(f2,'');
writeln(f2,'Warning errors: ',we,'  Severe errors: ',se);
end;
begin
FirstPass;
datasegment;
jbprov:=false;
commandcode;
jbprov:=true;
commandcode; close(segf);
writeln('Code segment successfully analized!');
tablefilling;
close(f); close(f2);
writeln('File .lst successfully created');
writeln('--------------------------------------');
writeln('Warning errors: ',we,'  Severe errors: ',se);
readln;
end.
