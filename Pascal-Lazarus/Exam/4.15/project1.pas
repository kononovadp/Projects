{Составить процедуру, результатом работы которой является символ, заданный при обращении к процедуре,
если этот символ не является буквой, и соответствующая строчная (малая) буква в противном случае. }
program z1;
uses crt;
var a,b,c:string;i,n,z,k:byte;
  begin
    b:=''; c:='';
    k:=1;
    readln(a);
    n:=length(a);   a:=a+' ';
    for i:=1 to n do
      if a[i]=a[i+1] then k:=k+1
    else begin
      b:=b+ a[i];
      if k>1 then
       begin b:=b+'(';
          while k>0 do //разложение числа на цифры
          begin  z:=k mod 10; k:=k div 10;
                 c:=chr(z+48)+c;
          end;
        b:=b+c+')';
       end;
      k:=1; c:='';
    end;
    writeln(b);
    readln;
    end.
