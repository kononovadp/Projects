{Составить процедуру, результатом работы которой является символ, заданный при обращении к процедуре,
если этот символ не является буквой, и соответствующая строчная (малая) буква в противном случае. }
program z1;
uses crt;
var a:string;i,p,s:integer; ch:char;
  begin
    readln(a);
    readln(ch);
     i:=0;
    s:=0;  p:=pos(ch,a);
    while p>0 do
       begin s:=p; delete(a,p,1);
         p:=pos(ch,a); i:=i+1;
       end;
    writeln(s+i-1);
    readln;
    end.
