{10. Надрукувати заданий непорожній текст, вилучивши з нього всі цифри і
подвоївши знаки плюс (+)  і  мінус (-).}
program z1;
var s:string; i,n,k,m:byte;  pr,pr2:set of char; c:char;
  begin
    readln(s);
    i:=0;
    pr:=['0','1','2','3','4','5','6','7','8','9'];
 while i < length(s) do
  begin
    inc(i);
    if s[i]='+' then
    begin
      insert('+',s,i);
      i:=i+1;
    end;
  if s[i]='-' then
    begin
      insert('-',s,i);
      i:=i+1;
    end;
  end;
 n:=length(s);
  for i:=1 to n do
  if not (s[i] in pr) then write(s[i]);
  readln;
end.
