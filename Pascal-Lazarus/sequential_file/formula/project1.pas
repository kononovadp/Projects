{11. Записати у файл g усі парні числа файлу f типу integer, а у файл 6 - усі непарні.
Порядок проходження чисел зберігається. Формула № 11.}
program z1;
var f,b:file of integer; x:integer; n:byte;
  begin
  assign(f,'file-f.dat');reset(f);
  assign(b,'file-b.dat');reset(b);
write('file F of even numbers'); writeln;
  while not (eof(f)) do  begin
     read(f,x);writeln(x);
     end;   close(f); readln;
write('file B odd numbers'); writeln;
  while not (eof(b)) do  begin
     read(b,x);writeln(x);
     end;   close(b); readln;

     end.
