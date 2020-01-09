var x, y  : integer;

begin
  y := -4;

  x := -y + 1 + 6 div 2 - 3 * 4;
  if x = y then
    WriteLn('x = y')
  else
    WriteLn('x <> y');
  writeln(x);
  ReadLn;
end.

