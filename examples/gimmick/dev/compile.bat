@echo off

SET game=zxgimmick
SET lang=es

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

if [%1]==[justcompile] goto :compilestage

echo ### MAKING TILESET ###
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin forcezero > nul

echo ### MAKING SPRITESET ###
..\..\..\src\utils\spg2bin.exe ..\gfx\drop.png ..\bin\spdrop.bin > nul
..\..\..\src\utils\spg2bin.exe ..\gfx\arrow.png ..\bin\sparrow.bin > nul

echo ### MAKING TEXTS ###
cd ..\texts
..\..\..\src\utils\textstuffer2.exe texts_es.bin textfile=texts_es.txt mode=simple wordwrap=24  > nul
..\..\..\src\utils\textstuffer2.exe texts_en.bin textfile=texts_en.txt mode=simple wordwrap=24  > nul

copy texts_%lang%.bin ..\bin\texts.bin > nul

echo ### MAKING SCRIPT ###
cd ..\script
copy variables.spt + level0.spt + level1.spt + level2.spt + level3.spt + level4.spt + level5.spt + level6.spt + level7.spt + level8.spt script.spt > nul
..\..\..\src\utils\msc3_mk2_1.exe script.spt 20 rampage > nul

rem If scripts and texts are going to share the same RAM page, use this line
rem (for 128K games)
rem This calculates an offset for the scripts binary automaticly.
..\..\..\src\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h
rem Otherwise use this one:
rem echo #define SCRIPT_INIT 49152 >> msc-config.h

copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
copy scripts.bin ..\bin\ > nul
cd ..\dev

rem For 128K games with text + script sharing the same page, use this to
rem bundle both binaries...
echo ### BUNDLING TEXT + SCRIPT ###
copy /b ..\texts\texts_es.bin + ..\script\scripts.bin ..\bin\preload6.bin > nul

echo ### BUILDING RAMS ###
cd ..\bin
..\..\..\src\utils\librarian.exe > nul
copy ram?.bin ..\dev\work > nul
copy librarian.h ..\dev\my\ > nul
cd ..\dev

echo ### BUILDING WYZ PLAYER ###
cd ..\mus

..\..\..\src\utils\apack.exe pueblofast.mus pueblofastc.mus > nul
..\..\..\src\utils\apack.exe pueblo.mus puebloc.mus > nul
..\..\..\src\utils\apack.exe sonic2.mus sonic2c.mus > nul
..\..\..\src\utils\apack.exe mario.mus marioc.mus > nul
..\..\..\src\utils\apack.exe shinobigg.mus shinobiggc.mus > nul
..\..\..\src\utils\apack.exe bloodlines.mus bloodlinesc.mus > nul
..\..\..\src\utils\apack.exe abrepuerta.mus abrepuertac.mus > nul
..\..\..\src\utils\apack.exe bosstheme.mus bossthemec.mus > nul
..\..\..\src\utils\apack.exe chinatown.mus chinatownc.mus > nul
..\..\..\src\utils\apack.exe intro.mus introc.mus > nul
..\..\..\src\utils\apack.exe vampire.mus vampirec.mus > nul
..\..\..\src\utils\apack.exe goblins.mus goblinsc.mus > nul
..\..\..\src\utils\apack.exe gradius.mus gradiusc.mus > nul
..\..\..\src\utils\apack.exe wbisla.mus wbislac.mus > nul
..\..\..\src\utils\apack.exe wb3final.mus wb3finalc.mus > nul
..\..\..\src\utils\apack.exe melonbeach.mus melonbeachc.mus > nul
..\..\..\src\utils\apack.exe gameover.mus gameoverc.mus > nul
..\..\..\src\utils\apack.exe feels.mus feelsc.mus > nul
..\..\..\src\utils\apack.exe logogw.mus logogwc.mus > nul

..\..\..\src\utils\pasmo WYZproPlay47aZXc.ASM ram1.bin > nul
copy ram1.bin ..\dev\work > nul
cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200 > nul
zcc +zx -vn -a mk2.c -o work\%game%.asm -lsplib2_mk2 -zorg=24200 > nul

echo ### MAKING TAPS ###
REM ..\..\..\src\utils\bas2tap -a10 -sFINAL loader\loader.bas work\loader.tap  > nul
REM ..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin  > nul
REM ..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin  > nul
REM ..\..\..\src\utils\bin2tap -o work\maine.tap -a 24200 work\%game%e.bin  > nul
REM copy /b work\loader.tap + work\loading.tap + work\main.tap %game%.tap  > nul
REM copy /b work\loader.tap + work\loading.tap + work\maine.tap %game%e.tap  > nul

rem Example for 128K games:
..\..\..\src\utils\bas2tap -a10 -s%game% loader\loader128.bas work\loader.tap  > nul
..\..\..\src\utils\bin2tap -o work\loading.tap -a 16384 work\loading.bin  > nul
..\..\..\src\utils\bin2tap -o work\reubica.tap -a 25000 loader\reubica.bin  > nul
..\..\..\src\utils\bin2tap -o work\RAM1.tap -a 25000 work\ram1.bin  > nul
..\..\..\src\utils\bin2tap -o work\RAM3.tap -a 25000 work\ram3.bin  > nul
..\..\..\src\utils\bin2tap -o work\RAM4.tap -a 25000 work\ram4.bin  > nul
..\..\..\src\utils\bin2tap -o work\RAM6.tap -a 25000 work\ram6.bin  > nul
..\..\..\src\utils\bin2tap -o work\RAM7.tap -a 25000 work\ram7.bin  > nul
..\..\..\src\utils\bin2tap -o work\main.tap -a 24200 work\%game%.bin  > nul
copy /b work\loader.tap + work\loading.tap + work\reubica.bin + work\ram1.tap + work\ram3.tap + work\ram4.tap + work\ram6.tap + work\ram7.tap + work\main.tap %game%-%lang%.tap > nul
del /a /s work\*.tap > nul

copy work\%game%.bin ..\tzx

rem ####################################
rem ###   UTOPIAN TZX TURBO LOADER   ###
rem ####################################

copy ..\bin\loading.bin ..\tzx\loading.scr > nul
copy work\ram*.bin ..\tzx\ > nul
copy work\zxgimmick.bin ..\tzx\ > nul

cd ..\tzx
buildtzx -l 1 -i template.txt -o %game%-%lang%.tzx -n Gimmick > nul
cd ..\dev
