{3. Знайти кількість парних чисел серед компонентів файлу F типу integer. Формула № 11.}
program z1;
var f,b:file of integer; x:integer; k,n:byte;
  begin
  assign(f,'file-f.dat');reset(f); k:=0;
  while not (eof(f)) do  begin
     read(f,x);writeln(x);
     if x mod 2 = 0 then k:=k+1;
     end; writeln('number of even numbers: ',k);  close(f); readln;
     end.
