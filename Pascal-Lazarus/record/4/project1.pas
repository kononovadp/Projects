{3. Проаналізувати оцінки студентів у своїй групі і надрукувати список
потенційних відмінників групи, тобто прізвища та імена студентів, які отримали
одну оцінку “добре”, а інші – “відмінно”.}
program z1;
uses crt;
type student=record
     Fam,Im,Otch,zodiak:string;
      La,Pr, SDA, MathAn:byte;
      marks:real;
     end;
     gruppa = array[0..30] of student;

var F:text; St:student; gr:gruppa; n,i,good,excellent,k:byte;  sr_m,sr_w,sr:real;

procedure print(gr:gruppa);
begin

for i:=1 to n do
with gr[i] do writeln(fam,'  ',im,' ',otch,' ',zodiak,' ',la,' ',pr,' ',sda,' ',mathan);

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

   read(f,b);  zodiak:='';
   while b<>' 'do begin zodiak:=zodiak+b;  read(f,b); end;//до следующего пробела - зодиак

  read(f,la,Pr, SDA, MathAn); //целочисленный тип считывает от пробела до пробела

    marks:=la+Pr+SDA+MathAn;
    n:=n+1;
    gr[n]:=st;
    read(f,b);

{for k:=1 to k do begin
if (gr[i].la=4) or (gr[i].pr=4) or (gr[i].sda=4) or (gr[i].mathan=4)
then good:=good+1;
if (gr[i].la=5) or (gr[i].pr=5) or (gr[i].sda=5) or (gr[i].mathan=5)
then excellent:=excellent+1; end;}
    end;//конец цикла
  close(f);//завершение работы с файлом
end;

BEGIN
grread('st.txt',gr,n);//чтение информации из файла
print(gr);
writeln('_____________________________________________________');
for i:=1 to n do begin
good:=0;
if (gr[i].la=2) then good:=good+1;
if(gr[i].pr=2)then good:=good+1;
if (gr[i].sda=2)then good:=good+1;
if (gr[i].mathan=2)then good:=good+1;
if good>2 then
with gr[i] do writeln (fam,'  ',im,' ',otch,' ',zodiak,' ',la,' ',pr,' ',sda,' ',mathan);

end;
readln; end.
{writeln('_____________________________________________________'); }

