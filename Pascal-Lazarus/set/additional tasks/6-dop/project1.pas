{6. Дано непорожню послідовність із малих латинських літер. Між сусідніми
словами – кома, після останнього слова – крапка. Надрукувати в алфавітному
порядку всі приголосні літери, які не входять  в жодне слово.}
program z1;
var s:string; i,n:byte;  k,pr:set of char; c:char;
begin
    readln(s);
    n:=length(s); s[n]:=','; i:=1;
    pr:=['q','w','r','t','p','s','d','f','g','h','j','k','l','z','x','c','v','b','n','m'];
  while i < n do begin
      if s[i] in pr then  k:=[s[i]]+k;
      i:=i+1;  end;
  for c:='a' to 'z' do if (c in pr) and not (c in k) then write(c); writeln;
      readln;
end.
