{5. Визначити кількість квадратів непарних чисел серед компонентів файлу F типу integer.
Формула № 11.}
program z1;
var f,b:file of integer; x:integer; k,n:byte;
  begin
  assign(f,'file-f.dat');reset(f); k:=0;
  while not (eof(f)) do  begin
     read(f,x);writeln(x);
     if (x mod 2 = 1) and (frac(x)=0)  then k:=k+1; //подвоєні непарні числа - це парні числа
     end; writeln('number of even numbers: ',k);  close(f); readln;
     end.
