echo off
cls
if exist bin\Debug\dm.exe (del \timetable\bin\Debug.exe)
call "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
msbuild.exe timetable.csproj
if exist bin\Debug\timetable.exe (
	cls
	bin\Debug\timetable.exe
) else (
	echo.
	pause
)