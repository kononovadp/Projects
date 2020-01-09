{2. Дано текст із малих латинських літер. В кінці тексту – крапка. Надрукувати
перші входження літер в текст, зберігаючи їх початковий взаємний порядок.}
program set11;
var a:set of char; i:byte; s:string;
  begin
    readln(s);
    for i:=1 to length(s) do
    if not(s[i] in a) then begin write(s[i]); a:=a+[s[i]]; end;
    readln;
    end.
