:: run this from a command prompt
:: TODO: change it to LocalAppdata when GLib is updated
@echo off

set DEPS_ROOT=C:\mozilla-build\xchatus
set SPELLING_DEST=..\build\spelling

rmdir /q /s %SPELLING_DEST%
mkdir %SPELLING_DEST%
xcopy /q /s /i %DEPS_ROOT%\myspell\dicts %SPELLING_DEST%\myspell
cd ..
echo [Setup] > build\spelling\xchatus-spelling.iss
echo WizardImageFile=%cd%\installer\wizardimage.bmp >> build\spelling\xchatus-spelling.iss
echo WizardSmallImageFile=%cd%\installer\wizardsmallimage.bmp >> build\spelling\xchatus-spelling.iss
cd ..\share\icons
echo SetupIconFile=%cd%\xchatus.ico >> win32\build\spelling\xchatus-spelling.iss
cd ..\..
type win32\spelling\xchatus-spelling.skel.iss >> win32\build\spelling\xchatus-spelling.iss
set PATH=%PROGRAMFILES(X86)%\Inno Setup 5
compil32 /cc win32\build\spelling\xchatus-spelling.iss
cd win32\spelling
pause
