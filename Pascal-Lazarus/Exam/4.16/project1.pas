{Составить процедуру, результатом работы которой является символ, заданный при обращении к процедуре,
если этот символ не является буквой, и соответствующая строчная (малая) буква в противном случае. }
program z1;
uses crt;
var a:string;i,n,s:integer; ch:char;
  begin
    readln(a);
    readln(ch);
    n:=length(a);
    s:=-1;
    for i:=1 to n do
      if a[i]=ch then s:=i;
    writeln(s);
    readln;
    end.
