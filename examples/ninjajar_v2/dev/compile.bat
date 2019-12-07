@echo off

rem set here the game name (used in filenames)

SET game=ninjajar!
SET lang=ES

echo ------------------------------------------------------------------------------
echo    BUILDING %game%
echo ------------------------------------------------------------------------------

if [%1]==[justcompile] goto :compilestage

del /a /s work\*.bin  > nul

echo ### MAKING TILESET ###
..\..\..\src\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin forcezero > nul

echo ### MAKING TEXT ###
..\..\..\src\utils\textstuffer.exe ..\texts\texts_%lang%.txt ..\bin\preload6.bin 24 > nul

echo ### MAKING SCRIPT ###
cd ..\script
..\..\..\src\utils\msc3_mk2_1.exe script.spt 21 rampage > nul
echo #define SCRIPT_INIT 49152 >> msc-config.h
copy msc.h ..\dev\my > nul
copy msc-config.h ..\dev\my > nul
copy scripts.bin ..\bin\preload7.bin > nul
cd ..\dev

rem For 128K games with text + script sharing the same page, use this to
rem bundle both binaries...
rem echo ### BUNDLING TEXT + SCRIPT ###
rem copy /b ..\texts\texts.bin + ..\script\scripts.bin ..\bin\preload7.bin

rem ###########################################################################
rem ## LIBRARIAN
rem ###########################################################################
echo ### BUILDING RAMS ###
cd ..\bin
..\..\..\src\utils\librarian.exe > nul
copy ram?.bin ..\dev\work > nul
copy librarian.h ..\dev\my\ > nul
cd ..\dev

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

echo ### BUILDING WYZ PLAYER ###
cd ..\mus
..\..\..\src\utils\pasmo WYZproPlay47aZXc.ASM RAM1.bin > nul
copy RAM1.bin ..\dev\work\RAM1.bin > nul
cd ..\dev

rem ###########################################################################
rem ## COMPILATION AND TAPE BUILDING
rem ###########################################################################

:compilestage

echo ### COMPILING ###
zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200 > nul

echo ### MAKING TAPS ###
..\..\..\src\utils\imanol.exe ^
    in=loader\loaderzx.asm-orig ^
    out=loader\loader.asm ^
    ram1_length=?work\RAM1.bin ^
    ram3_length=?work\RAM3.bin ^
    ram4_length=?work\RAM4.bin ^
    ram6_length=?work\RAM6.bin ^
    ram7_length=?work\RAM7.bin ^
    mb_length=?work\%game%.bin  > nul
..\..\..\src\utils\pasmo.exe loader\loader.asm work\loader.bin loader.txt
..\..\..\src\utils\GenTape.exe %game%.tap ^
    basic 'NINJAJAR' 10 work\loader.bin ^
    data                ..\bin\loading.scr ^
    data                work\RAM1.bin ^
    data                work\RAM3.bin ^
    data                work\RAM4.bin ^
    data                work\RAM6.bin ^
    data                work\RAM7.bin ^
    data                work\%game%.bin

echo DONE!