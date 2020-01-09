{3. Проаналізувати оцінки студентів у своїй групі і надрукувати список
потенційних відмінників групи, тобто прізвища та імена студентів, які отримали
одну оцінку “добре”, а інші – “відмінно”.}
program z1;
uses crt;
type student=record
     Fam,Im,Otch,zodiak:string;
      La,Pr, SDA, MathAn:byte;
     end;
     gruppa = array[0..30] of student;

var F:text; St:student; gr:gruppa; n,i,min,max:byte;  sr:array[1..4] of real;

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

    n:=n+1;
    gr[n]:=st;
    read(f,b);


    end;//конец цикла
  close(f);//завершение работы с файлом
end;

BEGIN
grread('st.txt',gr,n);//чтение информации из файла
print(gr);
writeln('_____________________________________________________');
for i:=1 to n do
with gr[i] do
begin
sr[1]:=sr[1]+ la; sr[2]:=sr[2]+ pr;
sr[3]:=sr[3]+ sda; sr[4]:=sr[4]+ mathan;
end;
for i:=1 to 4 do sr[i]:=sr[i]/n;
 min:=1;
for i:=2 to 4 do  if sr[i]<sr[min] then min:=i;
 max:=1;
for i:=2 to 4 do  if sr[i]>sr[max] then max:=i;
write('min sr:  ',sr[min]:1:2,' ');
case min of
  1: writeln('la');
  2: writeln('pr');
  3: writeln('sda');
  4: writeln('mathan');
end;

 write('max sr:  ',sr[max]:1:2,' ');
case max of
  1: writeln('la');
  2: writeln('pr');
  3: writeln('sda');
  4: writeln('mathan');
end;
readln; end.
{writeln('_____________________________________________________'); }

