unit bignums;
{$mode objfpc}{$H+}
interface
function TestExpressions():PChar;cdecl; external 'bignums.dll';
procedure UpdateLimits; cdecl; external 'bignums.dll';
var
	MinCountOfDigits: integer; cvar; external 'bignums.dll';
	MaxCountOfDigits: integer; cvar; external 'bignums.dll';
	CountOfExpressions: integer; cvar; external 'bignums.dll';
	MinCountOfOperations: integer; cvar; external 'bignums.dll';
	MaxCountOfOperations: integer; cvar; external 'bignums.dll';
implementation
end.

