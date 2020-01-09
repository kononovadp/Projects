{7. Дано непорожню послідовність із малих латинських літер.
Між сусідніми словами – кома, після останнього слова – крапка.
Надрукувати в алфавітному порядку всі приголосні літери, які входять тільки
в одне слово.}
program z1;
var s:string; i,n:byte;  k,pr,one:set of char; c:char;
  begin
    readln(s);
    n:=length(s)+1; s[n]:=','; i:=1;
    pr:=['q','w','r','t','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'];
  while i < n do begin
  k:=[];
      while s[i] <>','  do begin
      if s[i] in pr then  k:=k+[s[i]];
      i:=i+1;
      end;
      one:=(one+k)-(one*k);
     i:=i+1;
   end;
  for c:='a' to 'z' do if c in one then write(c); readln;
end.
