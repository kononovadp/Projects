{Составить процедуру, результатом работы которой является символ, заданный при обращении к процедуре,
если этот символ не является буквой, и соответствующая строчная (малая) буква в противном случае. }
program z1;
uses crt;
var a:string;i,n:byte;
  begin
    readln(a);
    n:=length(a);
    for i:=1 to n do
      if (ord(a[i])>=65) and (ord(a[i])<=90) then a[i]:=chr(ord(a[i])+32);
    writeln(a);
    readln;
    end.
