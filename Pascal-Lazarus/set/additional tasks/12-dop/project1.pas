{12. Надрукувати заданий непорожній текст, вилучивши з нього всі букви  "b",
безпосередньо перед якими знаходиться буква  "с".}
program z1;
var s:string; i,n,k,m:byte;  pr,pr2:set of char; c:char;
  begin
    readln(s);
    n:=length(s); i:=1;
    {pr:=['0','1','2','3','4','5','6','7','8','9']; }
  while i < n do
  begin
    inc(i);
    if (s[i]='b') and (s[i-1]='c') then
    begin
      delete(s,i,1);
     i:=i-1;
    end;
  end;
writeln(s);
readln;
end.
