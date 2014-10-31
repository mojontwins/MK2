@echo off
echo ### COMPILANDO TEXTOS ###
cd ..\texts
rem 24 is the word-wrap size.
..\utils\textstuffer.exe texts.txt texts.bin 24
copy texts.bin ..\bin\preload6.bin
echo ### COMPILANDO SCRIPT ###
cd ..\script
..\utils\msc3.exe ninjajar.spt 21 rampage
rem ..\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h
echo #define SCRIPT_INIT 49152 >> msc-config.h
copy msc.h ..\dev
copy msc-config.h ..\dev
copy scripts.bin ..\bin\preload7.bin
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### GENERANDO BINARIOS ###
echo * Building reubica
..\utils\pasmo reubica.asm reubica.bin
echo * Building levels
cd ..\levels
call makelevelsadv.bat
echo * Building extra RAM binaries
cd ..\bin
librarian.exe
copy RAM3.bin ..\dev\ram3.bin
copy RAM4.bin ..\dev\ram4.bin
copy RAM6.bin ..\dev\ram6.bin
copy RAM7.bin ..\dev\ram7.bin
copy librarian.h ..\dev
echo -------------------------------------------------------------------------------
echo ### COMPILANDO WYZ PLAYER ###
cd ..\mus
..\utils\pasmo WYZproPlay47aZXc.ASM ram1.bin
copy ram1.bin ..\dev
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### COMPILANDO GUEGO ###
zcc +zx -vn ninjajar.c -o ninjajar.bin -lsplib2 -zorg=24200
echo -------------------------------------------------------------------------------
echo ### CONSTRUYENDO CINTA ###
..\utils\bas2tap -a10 -sNINJAJAR! loader.bas loader.tap
..\utils\bin2tap -o reubica.tap -a 25000 reubica.bin
..\utils\bin2tap -o ram1.tap -a 32768 ram1.bin
..\utils\bin2tap -o ram3.tap -a 32768 ram3.bin
..\utils\bin2tap -o ram4.tap -a 32768 ram4.bin
..\utils\bin2tap -o ram6.tap -a 32768 ram6.bin
..\utils\bin2tap -o ram7.tap -a 32768 ram7.bin
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 ninjajar.bin
copy /b loader.tap + screen.tap + reubica.tap + ram1.tap + ram3.tap + ram4.tap + ram6.tap + ram7.tap + main.tap ninjajar.tap
echo -------------------------------------------------------------------------------
echo ### COPIANDO ../tape TODOS LOS BINARIOS
copy loading.bin ..\tape
copy ram?.bin ..\tape
copy ninjajar.bin ..\tape
echo -------------------------------------------------------------------------------
echo ### LIMPIANDO ###
del loader.tap
del screen.tap
del main.tap
del reubica.tap
del ram1.bin
del ram3.bin
del ram4.bin
del ram6.bin
del ram7.bin
del ram1.tap
del ram3.tap
del ram4.tap
del ram6.tap
del ram7.tap
del ninjajar.bin
del zcc_opt.def
echo -------------------------------------------------------------------------------
echo ### DONE ###
