@echo off
echo Building fixed screens
echo ======================
echo Converting...
..\..\..\src\utils\png2scr.exe ..\gfx\dedicado.png work\dedicado.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png work\ending.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending1.png work\ending1.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending2.png work\ending2.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending3.png work\ending3.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending4.png work\ending4.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\level.png work\level.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\marco.png work\marco.scr >nul
..\..\..\src\utils\png2scr.exe ..\gfx\title.png work\title.scr >nul

echo Compressing...
..\..\..\src\utils\apack.exe work\dedicado.scr ..\bin\dedicado.bin >nul 
..\..\..\src\utils\apack.exe work\ending.scr ..\bin\ending.bin >nul 
..\..\..\src\utils\apack.exe work\ending1.scr ..\bin\ending1.bin >nul 
..\..\..\src\utils\apack.exe work\ending2.scr ..\bin\ending2.bin >nul 
..\..\..\src\utils\apack.exe work\ending3.scr ..\bin\ending3.bin >nul 
..\..\..\src\utils\apack.exe work\ending4.scr ..\bin\ending4.bin >nul 
..\..\..\src\utils\apack.exe work\level.scr ..\bin\level.bin >nul 
..\..\..\src\utils\apack.exe work\loading.scr ..\bin\loading.bin >nul 
..\..\..\src\utils\apack.exe work\marco.scr ..\bin\marco.bin >nul 
..\..\..\src\utils\apack.exe work\title.scr ..\bin\title.bin >nul 
copy work\loading.scr ..\bin\loading.scr > nul

echo DONE
