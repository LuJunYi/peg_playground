@echo off


set QtDir=C:\Qt\Qt5.13.1\5.13.1\msvc2017_64
set PATH=%QtDir%\bin;%PATH%

set bat_path=%~dp0\build\bin\RelWithDebInfo
 REM set bat_path=%~dp0\build\bin\Debug

cd /d "%bat_path%"
@REM for /r "%bat_path%" %%i in (*.ipdb,*.iobj,*.lib,*.ilk,*.exp,*.metagen) do @del /f /q "%%i"

windeployqt.exe --release --compiler-runtime PEGPlayground.exe 

if %ERRORLEVEL% neq 0 (
	echo "windeployqt failed to deploy dependencies for %%F."
	exit /b 1
)

echo "All Qt dependencies deployed successfully."

@REM pause
