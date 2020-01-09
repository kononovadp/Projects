{1. Дано текст із цифр та малих латинських літер. В кінці тексту – крапка.
Визначити, яких літер: голосних (a, e, i, o, u, y) чи приголосних більше
в цьому тексті.}
program z1;
var s:string; i,n,g,p:byte;  pr,gl:set of char; c:char;
begin
    readln(s);
    n:=length(s); g:=0; p:=0; i:=1;
gl:=['e','y','u','i','o','a'];
for i:=97 to 122 do pr:=pr+[ chr(i) ];  pr:=pr-gl;
for i:=1 to n do
    begin
      if s[i] in gl then g:=g+1;
      if s[i] in pr then p:=p+1;
    end;
writeln('number of vowels: ',g,' number of consonants: ',p);
if g>p then writeln('there are vowels more');
if g<p then writeln('there are consonants more') else writeln('number of consonants and vowels is equal');
readln;
end.
