@echo off

rem set here the game name (used in filenames)

SET game=hobbit_v2

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

if [%1]==[justcompile] goto :compilestage

rem ###########################################################################
rem ## LEVELS
rem ###########################################################################

rem we will delegate on makelevels.bat - if your game supports several levels,etc
rem echo ### BUILDING LEVELS
rem cd ..\levels
rem call buildlevels.bat
rem cd ..\dev

rem Custom: subtileset with objects
rem ..\..\..\src\utils\mksubts.exe ..\gfx\items.png 0 ..\gfx\items.beh ..\bin\itemsts.bin

rem but for 48K/single level games... 
rem echo ### MAKING MAPS ###

rem the "Force" parameter is to force 16 tiles maps even if the actual map data
rem has more tan 16 tiles. Extra tiles are written to extra.spt. We have to move
rem that file to the script folder.

rem the "TwoTS" parameter is to force 16 tiles maps for games which use two
rem tilesets. Check on whatsnew.txt for directions.

..\..\..\src\utils\map2bin.exe ..\map\mapa.map 7 5 99 ..\bin\map.bin ..\bin\bolts.bin force
move ..\bin\map.bin.spt ..\script

echo ### MAKING ENEMS ###
..\..\..\src\utils\ene2bin.exe 7 5 1 ..\enems\enems.ene ..\bin\enems.bin ..\bin\hotspots.bin

echo ### MAKING TILESET ###
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png ..\bin\ts.bin forcezero

echo ### MAKING SPRITESET ###
..\..\..\src\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 16

:skiplevels

rem If you use arrows and/or drops this will make the sprites binary:

rem ..\..\..\src\utils\spg2bin.exe ..\gfx\drop.png spdrop.bin
rem ..\..\..\src\utils\spg2bin.exe ..\gfx\arrow.png ..\bin\sparrow.bin

rem ###########################################################################
rem ## FIXED SCREENS
rem ###########################################################################

echo ### MAKING FIXED ###
..\..\..\src\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr
..\..\..\src\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin
..\..\..\src\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr
..\..\..\src\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin
del ..\gfx\*.scr

echo ### MAKING LOADING ###
..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.bin

rem ###########################################################################
rem ## GAME TEXT
rem ###########################################################################

rem Each line in text.txt contains a text string for the game.
rem textstuffer2.exe will compress and pack all text strings in
rem a binary file called texts.bin. The parameters define how
rem many chars per line. Word wrapping is automatic.

REM echo ### MAKING TEXTS ###
REM cd ..\texts
REM ..\..\..\src\utils\textstuffer2.exe texts.bin textfile=texts.txt mode=simple wordwrap=24 
REM copy texts.bin ..\bin\texts.bin
REM ..\..\..\src\utils\textstuffer2.exe texts-eng.bin textfile=texts-eng.txt mode=simple wordwrap=24 
REM copy texts-eng.bin ..\bin\texts-eng.bin

rem echo ### MAKING PORTRAITS ####
rem ..\..\..\src\utils\portraits.exe ..\bin\portraits.bin ..\gfx\portraits\00_meghan.png ..\gfx\portraits\01_sold.png

rem echo ### MAKIN ITEM DESCRIPTIONS ###
rem ..\..\..\src\utils\itemstuffer.exe ..\texts\items.txt ..\bin\items.bin

rem ###########################################################################
rem ## GAME SCRIPT
rem ###########################################################################

rem The game script is compiled by msc3.exe. For 128K games use "rampage" at
rem the end so the script compiler generates code to stuff everything in
rem extra pages; the second parameter is the # of screens in your game.
rem i.e. "msc3_mk2_1.exe ninjajar.spt 21 rampage"

echo ### MAKING SCRIPT ###
cd ..\script
..\..\..\src\utils\msc3_mk2_1.exe script.spt 35

rem If scripts and texts are going to share the same RAM page, use this line
rem (for 128K games)
rem This calculates an offset for the scripts binary automaticly.
rem ..\..\..\src\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h

rem Otherwise use this one:
rem echo #define SCRIPT_INIT 49152 >> msc-config.h

copy msc.h ..\dev\my
copy msc-config.h ..\dev\my
rem copy scripts.bin ..\bin\preload7.bin
copy scripts.bin ..\bin\
cd ..\dev

rem For 128K games with text + script sharing the same page, use this to
rem bundle both binaries...
rem echo ### BUNDLING TEXT + SCRIPT ###
rem copy /b ..\texts\texts.bin + ..\script\scripts.bin ..\bin\preload7.bin

rem ###########################################################################
rem ## LIBRARIAN
rem ###########################################################################
rem echo ### BUILDING RAMS ###
rem cd ..\bin
rem ..\..\..\src\utils\librarian.exe
rem copy ram?.bin ..\dev\work
rem copy librarian.h ..\dev\assets\
rem cd ..\dev

rem ###########################################################################
rem ## MUSIC
rem ###########################################################################
rem echo ### BUILDING ARKOS ###
rem cd ..\mus
rem if [%1]==[nomus] goto :nomus
rem ..\..\..\src\utils\build_mus_bin.exe ram1.bin
rem :nomus
rem copy ram1.bin ..\dev\work
rem copy arkos-addresses.h ..\dev\sound
rem cd ..\dev

rem echo ### BUILDING WYZ PLAYER ###
rem cd ..\mus
rem ..\..\..\src\utils\pasmo WYZproPlay47aZXc.ASM ram1.bin
rem copy ram1.bin ..\dev\work
rem cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200
REM zcc +zx -vn %game%e.c -o work\%game%e.bin -lsplib2_mk2 -zorg=24200

echo ### MAKING TAPS ###
..\..\..\src\utils\bas2tap -a10 -sHOBBIT_V2 loader\loader.bas work\loader.tap
..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin
..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin
REM ..\..\..\src\utils\bin2tap -o work\maine.tap -a 24200 work\%game%e.bin
copy /b work\loader.tap + work\loading.tap + work\main.tap %game%.tap
REM copy /b work\loader.tap + work\loading.tap + work\maine.tap %game%e.tap

rem Example for 128K games:
rem ..\..\..\src\utils\bas2tap -a10 -sFINAL loader\loader128.bas work\loader.tap
rem ..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin
rem ..\..\..\src\utils\bin2tap -o work\reubica.tap -a 25000 loader\reubica.bin
rem ..\..\..\src\utils\bin2tap -o work\RAM1.tap -a 25000 work\ram1.bin
rem ..\..\..\src\utils\bin2tap -o work\RAM3.tap -a 25000 work\ram3.bin
rem ..\..\..\src\utils\bin2tap -o work\RAM4.tap -a 25000 work\ram4.bin
rem ..\..\..\src\utils\bin2tap -o work\RAM6.tap -a 25000 work\ram6.bin
rem ..\..\..\src\utils\bin2tap -o work\RAM7.tap -a 25000 work\ram7.bin
rem ..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin
rem copy /b work\loader.tap + work\loading.tap + work\reubica.bin + work\ram1.tap + work\ram3.tap + work\ram4.tap + work\ram6.tap + work\ram7.tap + work\main.tap %game%.tap
