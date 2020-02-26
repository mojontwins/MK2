@echo off

rem set here the game name (used in filenames)

SET game=mk2

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
rem ..\utils\mksubts.exe ..\gfx\items.png 0 ..\gfx\items.beh ..\bin\itemsts.bin

rem but for 48K/single level games... 
echo ### MAKING MAPS ###

rem the "Force" parameter is to force 16 tiles maps even if the actual map data
rem has more tan 16 tiles. Extra tiles are written to extra.spt. We have to move
rem that file to the script folder.

rem the "TwoTS" parameter is to force 16 tiles maps for games which use two
rem tilesets. Check on whatsnew.txt for directions.

..\utils\map2bin.exe ..\map\mapa.map 10 2 99 ..\bin\map.bin ..\bin\bolts.bin force > nul
move ..\bin\map.bin.spt ..\script > nul

echo ### MAKING ENEMS ###
..\utils\ene2bin.exe 10 2 1 ..\enems\enems.ene ..\bin\enems.bin ..\bin\hotspots.bin > nul


echo ### MAKING TILESET ###
rem use this for 48K games:
..\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png ..\bin\ts.bin forcezero > nul

rem use this for 128K games:
rem ..\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin forcezero > nul

echo ### MAKING SPRITESET ###
..\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 18 > nul

rem If you use arrows and/or drops this will make the sprites binary:

rem ..\utils\spg2bin.exe ..\gfx\drop.png spdrop.bin
..\utils\spg2bin.exe ..\gfx\arrow.png ..\bin\sparrow.bin > nul

rem ###########################################################################
rem ## FIXED SCREENS
rem ###########################################################################

echo ### MAKING FIXED ###
..\utils\png2scr.exe ..\gfx\title.png ..\gfx\title.scr > nul
..\utils\apack.exe ..\gfx\title.scr ..\bin\title.bin > nul
..\utils\png2scr.exe ..\gfx\ending.png ..\gfx\ending.scr > nul
..\utils\apack.exe ..\gfx\ending.scr ..\bin\ending.bin > nul
del ..\gfx\*.scr > nul

echo ### MAKING LOADING ###
..\utils\png2scr.exe ..\gfx\loading.png work\loading.bin > nul

rem ###########################################################################
rem ## GAME TEXT
rem ###########################################################################

rem Each line in text.txt contains a text string for the game.
rem textstuffer2.exe will compress and pack all text strings in
rem a binary file called texts.bin. The parameters define how
rem many chars per line. Word wrapping is automatic.

REM echo ### MAKING TEXTS ###
REM cd ..\texts
REM ..\utils\textstuffer2.exe texts.bin textfile=texts.txt mode=simple wordwrap=24 
REM copy texts.bin ..\bin\texts.bin
REM ..\utils\textstuffer2.exe texts-eng.bin textfile=texts-eng.txt mode=simple wordwrap=24 
REM copy texts-eng.bin ..\bin\texts-eng.bin

rem echo ### MAKING PORTRAITS ####
rem ..\utils\portraits.exe ..\bin\portraits.bin ..\gfx\portraits\00_meghan.png ..\gfx\portraits\01_sold.png

rem echo ### MAKIN ITEM DESCRIPTIONS ###
rem ..\utils\itemstuffer.exe ..\texts\items.txt ..\bin\items.bin

rem ###########################################################################
rem ## GAME SCRIPT
rem ###########################################################################

rem The game script is compiled by msc3.exe. For 128K games use "rampage" at
rem the end so the script compiler generates code to stuff everything in
rem extra pages; the second parameter is the # of screens in your game.
rem i.e. "msc3_mk2_1.exe ninjajar.spt 21 rampage"

echo ### MAKING SCRIPT ###
cd ..\script
..\utils\msc3_mk2_1.exe script.spt 20 > nul

rem If scripts and texts are going to share the same RAM page, use this line
rem (for 128K games)
rem This calculates an offset for the scripts binary automaticly.
rem ..\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h

rem Otherwise use this one:
rem echo #define SCRIPT_INIT 49152 >> msc-config.h

copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
rem copy scripts.bin ..\bin\preload7.bin
copy scripts.bin ..\bin\ > nul
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
rem ..\utils\librarian.exe
rem copy ram?.bin ..\dev\work
rem copy librarian.h ..\dev\my\
rem cd ..\dev

rem ###########################################################################
rem ## MUSIC
rem ###########################################################################
rem echo ### BUILDING ARKOS ###
rem cd ..\mus
rem if [%1]==[nomus] goto :nomus
rem ..\utils\build_mus_bin.exe ram1.bin
rem :nomus
rem copy ram1.bin ..\dev\work
rem copy arkos-addresses.h ..\dev\sound
rem cd ..\dev

rem echo ### BUILDING WYZ PLAYER ###
rem cd ..\mus
rem ..\utils\pasmo WYZproPlay47aZXc.ASM ram1.bin
rem copy ram1.bin ..\dev\work
rem cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200 > nul

echo ### MAKING TAPS ###
..\utils\bas2tap -a10 -sFINAL loader\loader.bas work\loader.tap  > nul
..\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin  > nul
..\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin  > nul
REM ..\utils\bin2tap -o work\maine.tap -a 24200 work\%game%e.bin  > nul
copy /b work\loader.tap + work\loading.tap + work\main.tap %game%.tap  > nul
REM copy /b work\loader.tap + work\loading.tap + work\maine.tap %game%e.tap  > nul

rem Example for 128K games:
rem ..\utils\bas2tap -a10 -sFINAL loader\loader128.bas work\loader.tap  > nul
rem ..\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin  > nul
rem ..\utils\bin2tap -o work\reubica.tap -a 25000 loader\reubica.bin  > nul
rem ..\utils\bin2tap -o work\RAM1.tap -a 32768 work\ram1.bin  > nul
rem ..\utils\bin2tap -o work\RAM3.tap -a 32768 work\ram3.bin  > nul
rem ..\utils\bin2tap -o work\RAM4.tap -a 32768 work\ram4.bin  > nul
rem ..\utils\bin2tap -o work\RAM6.tap -a 32768 work\ram6.bin  > nul
rem ..\utils\bin2tap -o work\RAM7.tap -a 32768 work\ram7.bin  > nul
rem ..\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin  > nul
rem copy /b work\loader.tap + work\loading.tap + work\reubica.tap + work\ram1.tap + work\ram3.tap + work\ram4.tap + work\ram6.tap + work\ram7.tap + work\main.tap %game%.tap > nul
