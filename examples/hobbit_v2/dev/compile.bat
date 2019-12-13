@echo off

rem set here the game name (used in filenames)

SET game=hobbit_v2

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

if [%1]==[justcompile] goto :compilestage

echo ### MAKING MAPS ###
..\..\..\src\utils\map2rlebin.exe rle=53 in=..\map\mapa.map out=..\bin\map size=7,5 tlock=99 fulllocks > nul

echo ### MAKING ENEMS ###
..\..\..\src\utils\ene2bin.exe 7 5 1 ..\enems\enems.ene ..\bin\enems.bin ..\bin\hotspots.bin > nul

echo ### MAKING TILESET ###
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png ..\bin\ts.bin forcezero > nul

echo ### MAKING SPRITESET ###
..\..\..\src\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 16 > nul

echo ### MAKING FIXED ###
..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr > nul
..\..\..\src\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin > nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr > nul
..\..\..\src\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin > nul
del ..\gfx\*.scr > nul

echo ### MAKING LOADING ###
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.bin > nul

echo ### MAKING SCRIPT ###
cd ..\script
..\..\..\src\utils\msc3_mk2_1.exe script.spt 35 > nul

copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
copy scripts.bin ..\bin\ > nul
cd ..\dev

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200 > nul
zcc +zx -vn -a mk2.c -o work\%game%.asm -lsplib2_mk2 -zorg=24200 > nul

echo ### MAKING TAPS ###
..\..\..\src\utils\bas2tap -a10 -sHOBBIT_V2 loader\loader.bas work\loader.tap > nul
..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin > nul
..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin > nul
copy /b work\loader.tap + work\loading.tap + work\main.tap %game%.tap > nul
