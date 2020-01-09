{1. Сформувати типізований послідовний файл F , компоненти якого обчислюються по формулі,}
program z1;
var f:file of real; x:real;i,n:byte;
  begin
    assign(f,'text.dat');rewrite(f);
    n:=10;
    for i:=1 to n do
    begin
      x:=sqr(i-3);
      write(f,x);
      end;   close(f);
      end.
