{5. Дано непорожню послідовність із малих латинських літер. Між сусідніми
словами – кома, після останнього слова – крапка. Надрукувати в алфавітному
порядку всі голосні літери, які входять в кожне слово.}
program z1;
var s:string; i,n:byte;  k,pr:set of char; c:char; m:boolean;
begin
    readln(s);
    n:=length(s); s[n]:=','; i:=1;
    pr:=['e','y','u','i','o','a'];
  while i <=n do begin
  if s[i]=',' then begin pr:=pr*k; k:=[]; end//m:=tue; r
      else k:=[s[i]]+k;  i:=i+1;
  end;
  for c:='a' to 'z' do if (c in pr)  then write(c);
  if pr=[] then writeln('there are no equal vowels in different words');
readln;
end.
{5. Дано непорожню послідовність із малих латинських літер. Між сусідніми
словами – кома, після останнього слова – крапка. Надрукувати в алфавітному
порядку всі голосні літери, які входять в кожне слово.}
{program z1;
var s:string; i,n:byte;  k,gl:set of char; c:char;
begin
    readln(s);
    n:=length(s)+1; s[n]:=',';
    i:=1; gl:=['e','y','u','i','o','a'];
  while i < n do
  begin
    k:=[];
  while s[i] <>','  do begin
    if s[i] in gl then  k:=[s[i]]+k;
    i:=i+1;  end;
  for c:='a' to 'z' do if c in k then write(c); writeln;
    i:=i+1;
  end;
  readln;
end. }
