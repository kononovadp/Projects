echo off
cls
if exist code.exe (del code.exe)
call "C:\Program Files\Microsoft Visual Studio 11.0\Common7\Tools\vsvars32.bat"
cl code.c
del code.obj
if exist code.exe (
	"D:\��������� �����\���������\����������������\�������� ������ ����������\ResourceHacker.exe" -open code.exe -save code.exe -action addoverwrite -res "D:\��������� �����\���������\����������������\�������� ������ ����������\icon.ico" -mask ICONGROUP,32512
	set /p asd=""
	cls
	code.exe
	echo.
	echo.
	echo ��������� ��������� �������
	pause
) else (
	echo.
	pause
)