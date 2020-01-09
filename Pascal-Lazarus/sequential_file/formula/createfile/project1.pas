{11. Записати у файл g усі парні числа файлу f типу integer, а у файл 6 - усі непарні.
Порядок проходження чисел зберігається. Формула № 11.}
program z1;
uses crt;
var f,b,g:file of integer; n,x,k:integer; i:byte;
  begin
    n:=10; x:=0; k:=1;
    //створюємо файл f за формулою
    assign(f,'file-f.dat');rewrite(f);
    for i:=1 to n do begin
    x:=i+(x+(x*k)); //for real: x:=i+(x+exp(ln(2)*i))
    write(f,x); end; close(f);
    //записуємо у файл g усі парні числа, а у файл b - усі непарні
    assign(f,'file-f.dat');reset(f);
    assign(g,'file-g.dat');rewrite(g);
    assign(b,'file-b.dat');rewrite(b);
    while not (eof(f)) do  begin
    read(f,x);
    if x mod 2 = 0 then
    write(g,x) else write(b,x); end;
    close(f); close(g); close(b);
    //зчитуємо файл f
    write('current file'); writeln;
    assign(f,'file-f.dat');reset(f);
    while not (eof(f)) do  begin
    read(f,x);writeln(x);
    end;   close(f); readln;
    //зчитуємо файл g з парними числами
    write('file of even numbers'); writeln;
    assign(g,'file-g.dat');reset(g);
    while not (eof(g)) do  begin
    read(g,x);writeln(x);
    end;   close(g); readln;
    //зчитуємо файл b з непарними числами
    write('file of odd numbers'); writeln;
    assign(b,'file-b.dat');reset(b);
    while not (eof(b)) do  begin
    read(b,x);writeln(x);
    end;   close(b); readln;
end.

