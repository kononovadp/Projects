{12. Задано непустий текст довжиною до 255 символів, що містить у собі слова,
у кожному з яких від 1 до 5 малих латинських літер; між сусідніми словами –
коми, за останнім словом – крапка. Надрукувати :
а) усі різні слова, вказавши для кожного слова кількість його входжень у текст;
б) усі слова в алфавітному порядку.}
program z1;
var k,s:string; i,n,m,p,g:byte;  sl:array[1..130] of string; count:array[1..130] of byte;
  begin
    readln(s);
    n:=length(s); s[n]:=',';
    i:=1; m:=0;
  while i < n do begin
     k:=''; g:=0;
    while s[i] <>','  do begin  k:=k+s[i];i:=i+1;  end;
    for p:=1 to m do  if sl[p]=k then begin g:=1; count[p]:=count[p]+ 1;  end;
    if g=0 then begin m:=m+1; sl[m]:=k; count[m]:=1; end;
     i:=i+1;
     end;
     for p:= 1 to m-1 do
     for i:= 1 to m-p do
     if sl[i]>sl[i+1] then begin
       k:=sl[i];       g:=count[i];
       sl[i]:=sl[i+1];  count[i]:=count[i+1] ;
       sl[i+1]:=k;      count[i+1]:=g;
     end;
    for i:=1 to m do writeln(sl[i],' - ',count[i]);

    readln; end.
