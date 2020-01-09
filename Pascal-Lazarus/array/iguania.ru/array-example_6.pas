program z3;
var
	n, i:byte;
	a, b: array[1..10] of integer;
	sqr_sum: integer;
begin
	n := 0;
	while (n > 10) or (n < 1) do begin
		write('n = '); readln(n); end;

	sqr_sum := 0;
	for i:=1 to n do begin
		write('a',i,' = '); readln(a[i]);
		write('b',i,' = '); readln(b[i]);
		sqr_sum := sqr_sum + sqr(a[i] - b[i])
	end;
	writeln(sqrt(sqr_sum):10:3);readln;
end.
