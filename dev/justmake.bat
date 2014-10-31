@echo off
cd ..\bin
copy RAM3.bin ..\dev\ram3.bin
copy RAM4.bin ..\dev\ram4.bin
copy RAM6.bin ..\dev\ram6.bin
copy RAM7.bin ..\dev\ram7.bin
cd ..\mus
copy ram1.bin ..\dev
cd ..\dev
zcc +zx -vn ninjajar.c -o ninjajar.bin -lsplib2 -zorg=24200
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
