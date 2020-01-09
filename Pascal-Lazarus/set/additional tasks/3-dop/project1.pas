{3. Дано текст із малих латинських літер. В кінці тексту – крапка.
Надрукувати всі літери, які входять в текст не менше ніж два рази.}
program set11;
var a1,a2:set of char; i:byte; s:string; c:char;
begin
    readln(s);
    for i:=1 to length(s) do
    if not(s[i] in a1 ) then   a1:=a1+[s[i]] else  a2:=a2+[s[i]];
    for c:='a' to 'z' do if c in a2 then write(c);
    readln;
end.
