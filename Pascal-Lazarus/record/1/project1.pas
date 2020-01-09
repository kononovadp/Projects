program z1;
uses crt;
type student=record
     Fam,Im,Otch,pol:string;
     La,Pr, SDA, MathAn:byte;//оценки по предметам
      marks:real;
     end;
     gruppa = array[0..30] of student;
var F:text; St:student; gr:gruppa; n,i,m,w:byte;  sr_m,sr_w,sr:real;

  procedure print(gr:gruppa);
begin
for i:=1 to n do
with gr[i] do writeln(fam,'  ',pol,' ',marks:0:1);
end;

procedure GrRead(s:string;var gr:gruppa; var  n:byte);//считываем группу и считаем средний балл для каждого
var b:char;//читаем посимвольно
begin
assign(f,s);//связь с файлом
reset(f); ///подготовка файла к чтению
n:=0;//количество общих студентов
while not (eof(f)) do//читать файл до конца
   with st do
   begin

   read(f,b); fam:='';//читаем посимвольно
   while b<>' 'do begin fam:=fam+b;  read(f,b); end;//до первого пробела - фамилия

   read(f,b); im:='';
   while b<>' 'do begin im:=im +b; read(f,b); end;//до следующего пробела - имя

   read(f,b);  otch:='';
   while b<>' 'do begin otch:=otch+b;  read(f,b); end;//до следующего пробела - отчество

   read(f,b);  pol:=b;
   read(f,la,Pr, SDA, MathAn); //целочисленный тип считывает от пробела до пробела

    marks:=(la+Pr+SDA+MathAn)/4;

    n:=n+1;
      gr[n]:=st;
   read(f,b);
   end;//конец цикла
  close(f);//завершение работы с файлом
end;

BEGIN
grread('st.txt',gr,n);//чтение информации из файла
writeln('____________________________________');//вывод
for i:=1 to n do begin
if gr[i].pol='m' then begin m:=m+1; sr_m:=sr_m+gr[i].marks end
                 else begin w:=w+1; sr_w:=sr_w+gr[i].marks end;
sr:= sr+gr[i].marks
end;
  sr_m:=sr_m/m;  sr_w:=sr_w/w; sr:=sr/n;
 writeln(sr:6:2,sr_w:6:1,sr_m:6:1);
print(gr);//выводит на экран
readln;



END.
