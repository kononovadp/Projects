unit bignums;
{$mode objfpc}{$H+}
interface
function TestExpressions():PChar;cdecl; external 'bignums.dll';
procedure FreeString(s:PChar);cdecl; external 'bignums.dll';
var
  MaxFractPartLength: integer; cvar; external 'bignums.dll';
  MaxBignumLength: integer; cvar; external 'bignums.dll';

implementation
end.
