{2. Визначити найбільше зі значень компонентів по модулю з непарними номерами.}
program z1;
uses crt;
var f,b:file of integer; n,x,k:integer; i:byte;
  begin
    n:=10; x:=0; k:=1;
    assign(f,'file-f.dat');rewrite(f);
    for i:=1 to n do begin
    x:=i+(x+(x*k)); //for real: x:=i+(x+exp(ln(2)*i))
    if i mod 2 = 1 then
    write(f,x)
    end;
    close(f);
    end.
