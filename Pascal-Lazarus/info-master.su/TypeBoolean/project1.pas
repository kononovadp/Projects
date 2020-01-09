program logika;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

begin
  Writeln('Boolean : ',  Low(Boolean), '..', High(Boolean));
  Writeln('ByteBool : ',  Low(ByteBool), '..', High(ByteBool));
  Writeln('WordBool : ',  Low(WordBool), '..', High(WordBool));
  Writeln('LongBool : ',  Low(LongBool), '..', High(LongBool));
  Readln;
end.
