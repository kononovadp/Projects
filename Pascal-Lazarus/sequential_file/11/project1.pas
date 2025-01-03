{11. Записати у файл g усі парні числа файлу f типу integer, а у файл 6 - усі непарні.
Порядок проходження чисел зберігається. Формула № 11.}
program z1;
type int=file of integer;
var x:integer; n,i:byte; b,f,g: int;
    procedure writefile(var f:int);//створюємо файл f за формулою
    begin
    n:=10; x:=0;
    rewrite(f);
    for i:=1 to n do begin
    x:=i+round(exp(ln(2)*i));
    write(f,x); end;
    end;
    procedure operations(var f,g,b:int);//записуємо у файл g усі парні числа, а у файл b - усі непарні
    begin
    reset(f);
    assign(g,'file-g.dat');rewrite(g);
    assign(b,'file-b.dat');rewrite(b);
    while not (eof(f)) do  begin
    read(f,x);
    if x mod 2 = 0 then
    write(g,x) else write(b,x); end;
    end;
    procedure read_f(var f:int);//зчитуємо файл f
    begin
    write('Components of file f'); writeln;
    reset(f);
    while not (eof(f)) do  begin
    read(f,x);writeln(x); end;
    end;
    procedure read_g(var g:int);//зчитуємо файл g з парними числами
    begin
    write('Components of file G with even numbers'); writeln;
    reset(g);
    while not (eof(g)) do  begin
    read(g,x);writeln(x); end;
    end;
    procedure read_b(var b:int);//зчитуємо файл b з непарними числами
    begin
    write('Components of file B with odd numbers'); writeln;
    reset(b);
    while not (eof(b)) do  begin
    read(b,x);writeln(x); end;
    end;
    begin
    assign(f,'file-f.dat');
    writefile(f);
    operations(f,g,b);
    read_f(f);
    read_g(g);
    read_b(b);
    readln;
    close(f); close(g); close(b);
end.
