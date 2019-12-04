@echo off
echo Building fixed screens
echo ======================
echo Converting...
..\..\..\src\utils\png2scr.exe ..\gfx\dedicado.png work\dedicado.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png work\ending.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending1.png work\ending1.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending2.png work\ending2.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending3.png work\ending3.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending4.png work\ending4.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\level.png work\level.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\marco.png work\marco.src >nul
..\..\..\src\utils\png2scr.exe ..\gfx\title.png work\title.src >nul

echo Compressing...
..\..\..\src\utils\apack.exe work\dedicado.src ..\bin\dedicado.bin >nul 
..\..\..\src\utils\apack.exe work\ending.src ..\bin\ending.bin >nul 
..\..\..\src\utils\apack.exe work\ending1.src ..\bin\ending1.bin >nul 
..\..\..\src\utils\apack.exe work\ending2.src ..\bin\ending2.bin >nul 
..\..\..\src\utils\apack.exe work\ending3.src ..\bin\ending3.bin >nul 
..\..\..\src\utils\apack.exe work\ending4.src ..\bin\ending4.bin >nul 
..\..\..\src\utils\apack.exe work\level.src ..\bin\level.bin >nul 
..\..\..\src\utils\apack.exe work\loading.src ..\bin\loading.bin >nul 
..\..\..\src\utils\apack.exe work\marco.src ..\bin\marco.bin >nul 
..\..\..\src\utils\apack.exe work\title.src ..\bin\title.bin >nul 

echo DONE
