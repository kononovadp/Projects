{11. Надрукувати заданий непорожній текст, вилучивши з нього всі знаки плюс (+),
безпосередньо за якими слідує цифра.}
program z1;
var s:string; i,n,k,m:byte;  pr,pr2:set of char; c:char;
  begin
    readln(s);
    i:=1;
    pr:=['0','1','2','3','4','5','6','7','8','9'];
  while i < length(s) do
  begin
    inc(i);
    if (s[i]='+') and (s[i+1] in pr) then
    begin
      delete(s,i,1);
      i:=i-1;
    end;
  end;
writeln(s);
readln;
end.
