@echo off

SET game=journey

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

if [%1]==[justcompile] goto :compilestage

del ..\bin\*.bin /a /s >nul

echo ### MAKING MAPS ###
..\..\..\src\utils\map2rlebin.exe rle=44 in=..\map\level0.map out=..\bin\level0 size=4,7 tlock=15 fulllocks >nul
..\..\..\src\utils\map2rlebin.exe rle=44 in=..\map\level1.map out=..\bin\level1 size=4,7 tlock=15 fulllocks >nul

echo ### COMPRESSING MAPS ###
..\..\..\src\utils\apack.exe ..\bin\level0.map.bin ..\bin\level0.map.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.map.bin ..\bin\level1.map.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level0.locks.bin ..\bin\level0.locks.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.locks.bin ..\bin\level1.locks.c.bin > nul

echo ### MAKING ENEMS ###
..\..\..\src\utils\ene2bin.exe 4 7 1 ..\enems\level0.ene ..\bin\level0.enems.bin ..\bin\level0.hotspots.bin >nul
..\..\..\src\utils\ene2bin.exe 4 7 1 ..\enems\level1.ene ..\bin\level1.enems.bin ..\bin\level1.hotspots.bin >nul

echo ### COMPRESSING ENEMS ###
..\..\..\src\utils\apack.exe ..\bin\level0.enems.bin ..\bin\level0.enems.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.enems.bin ..\bin\level1.enems.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level0.hotspots.bin ..\bin\level0.hotspots.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.hotspots.bin ..\bin\level1.hotspots.c.bin > nul

echo ### MAKING TILESET ###
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin  >nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\tileset0.png ..\bin\level0.ts.bin  >nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\tileset1.png ..\bin\level1.ts.bin  >nul

echo ### COMPRESSING METATILESETS ###
..\..\..\src\utils\apack.exe ..\bin\level0.ts.bin ..\bin\level0.ts.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.ts.bin ..\bin\level1.ts.c.bin > nul

echo ### MAKING BEHS ###
..\..\..\src\utils\behs2bin.exe ..\gfx\level0.behs.txt ..\bin\level0.behs.bin >nul
..\..\..\src\utils\behs2bin.exe ..\gfx\level1.behs.txt ..\bin\level1.behs.bin >nul

echo ### COMPRESSING BEHS ###
..\..\..\src\utils\apack.exe ..\bin\level0.behs.bin ..\bin\level0.behs.c.bin > nul
..\..\..\src\utils\apack.exe ..\bin\level1.behs.bin ..\bin\level1.behs.c.bin > nul

echo ### MAKING SPRITESET ###
..\..\..\src\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 16 >nul

echo ### MAKING FIXED ###
..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr >nul
..\..\..\src\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin > nul
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr >nul
..\..\..\src\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin > nul
del ..\gfx\*.scr >nul

echo ### MAKING LOADING ###
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.bin >nul

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200 >nul
zcc +zx -vn -a mk2.c -o work\%game%.asm -lsplib2_mk2 -zorg=24200 >nul

echo ### MAKING TAPS ###
..\..\..\src\utils\bas2tap -a10 -sJOURNEY loader\loader.bas work\loader.tap >nul
..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin >nul
..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin >nul
copy /b work\loader.tap + work\loading.tap + work\main.tap %game%.tap >nul
