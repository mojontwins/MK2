@echo off

SET game=game

echo ### COMPILING ###
zcc +zx -vn %game%.c -o %game%.bin -lsplib2 -zorg=24200
echo ### MAKING TAPS ###
..\utils\bas2tap -a10 -s%game% loader.bas loader.tap
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 %game%.bin
copy /b loader.tap + screen.tap + main.tap %game%.tap
echo ### LIMPIANDO ###
del loader.tap
del screen.tap
del main.tap
del %game%.bin
echo ### DONE ###
