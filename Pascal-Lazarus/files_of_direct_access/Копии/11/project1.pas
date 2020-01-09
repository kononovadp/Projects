{11. Сформувати файл з n дійсних чисел. Переписати файл так, щоб його
компоненти розташовувались в наступному порядку: }
program z1;
var f,h:file of real; m,x:real; k,n,i,j:byte;
  begin

    assign(f,'file-f.dat');rewrite(f);
    n:=10;
    for i:=1 to n div 2 do
    begin
    x:=i;  {m:=0;} write(f,x);
    end;
    k:=filesize(f);
    reset(f);
    while not (eof(f)) do begin read(f,x); writeln(x:0:3); end;
    readln;
    for i:=0 to k div 2-1 do
    begin
  //  seek(f,i); read(f,x); seek(f,2*i+1); write(f,x);
    seek(f,k-i-1); read(f,x); seek(f,2*i+1); write(f,x);
    end;
    if k mod 2>0 then    begin
    seek(f,i+1); read(f,x); seek(f,k-1); write(f,x);
    end;

     //seek(f,5); write(f,1);


    {for i:=0 to (k div 2)-1 do begin
    for j:=k div 2+1 to k do begin
    seek(f,i); read(f,x); seek(f,j); write(f,x);
    seek(f,k-i-1); read(f,x); seek(f,k-j+1); write(f,x);
    end; end;
    if k mod 2>0 then    begin
    seek(f,i+1); read(f,x); seek(f,j+1); write(f,x);
    end;
    seek(f,n div 2); write(f,1);}
    reset(f);
    while not (eof(f)) do begin read(f,x); writeln(x:0:3); end;
    close(f);
    readln;
    end.

