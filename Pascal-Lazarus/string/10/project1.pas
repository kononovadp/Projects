{10.	Задано непустий текст довжиною до 255 символів, що містить у слова, у
кожному з яких від 1 до 5 малих латинських літер; між сусідніми словами – коми,
за останнім словом – крапка. Надрукувати :
а) цю літери кожного слова в зворотному порядку, розділивши слова комами;
б) ті слова, яким передують у послідовності менші (за лексикографічним порядком)
слова, а за ними – більші.}
program z1;
var k,k1,s,prev,next,sl:string; i,n,m,p,g:byte;  z,y:set of char;
  begin
    readln(s);
    n:=length(s); s[n]:=',';
    i:=1; prev:=''; next:='';sl:='';
  while i < n do begin
     k:='';k1:='';
    while s[i] <>','  do begin k:=s[i]+k; k1:=k1+s[i];i:=i+1;  end;
    write(k);
    if i<n then write(',') else write('.');
    i:=i+1;
    if (prev<next) and (next<k1) then sl:=sl+next;
    prev:=next; next:=k1;
  end;
    writeln(sl);
    readln; end.
