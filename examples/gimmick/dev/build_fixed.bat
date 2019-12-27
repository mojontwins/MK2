@echo off
echo Building fixed screens
echo ======================
echo Converting...
..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr   > nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\dragon.png ..\gfx\dragon.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\fingod.png ..\gfx\fingod.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\logogw.png ..\gfx\logogw.scr > nul
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png ..\work\loading.bin > nul

echo Compressing...
..\..\..\src\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin   > nul
..\..\..\src\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin > nul
..\..\..\src\utils\apack.exe ..\gfx\dragon.scr ..\bin\dragon.bin > nul
..\..\..\src\utils\apack.exe ..\gfx\fingod.scr ..\bin\fingod.bin > nul
..\..\..\src\utils\apack.exe ..\gfx\logogw.scr ..\bin\logogw.bin > nul

del ..\gfx\*.scr > nul