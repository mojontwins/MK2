@echo off

echo Building Levels
echo ===============

echo Level 0 Pueblo
..\..\..\src\utils\buildLevel.exe work\Level0.bin mapfile=..\map\mapa0.map map_w=5 map_h=4 decorations=..\script\decorations0.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work0.png behsfile=..\Levels\w0.beh spritesfile=..\gfx\Levels\sprites0.png nsprites=16 enemsfile=..\enems\enems0.ene scr_ini=18 ini_x=6 ini_y=7 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level0.bin ..\bin\Level0c.bin > nul
rem del work\Level0.bin > nul

echo Level 1 Sonic world
..\..\..\src\utils\buildLevel.exe work\Level1.bin mapfile=..\map\mapa1.map map_w=20 map_h=1 decorations=..\script\decorations1.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work1.png behsfile=..\Levels\w1.beh spritesfile=..\gfx\Levels\sprites1.png nsprites=16 enemsfile=..\enems\enems1.ene scr_ini=0 ini_x=2 ini_y=7 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level1.bin ..\bin\Level1c.bin > nul
del work\Level1.bin > nul

echo Level 2 Mario world 
..\..\..\src\utils\buildLevel.exe work\Level2.bin mapfile=..\map\mapa2.map map_w=20 map_h=1 decorations=..\script\decorations2.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work2.png behsfile=..\Levels\w2.beh spritesfile=..\gfx\Levels\sprites2.png nsprites=16 enemsfile=..\enems\enems2.ene scr_ini=0 ini_x=2 ini_y=8 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level2.bin ..\bin\Level2c.bin > nul
del work\Level2.bin > nul

echo Level 3 Castlevania world
..\..\..\src\utils\buildLevel.exe work\Level3.bin mapfile=..\map\mapa3.map map_w=10 map_h=2 decorations=..\script\decorations3.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work3.png behsfile=..\Levels\w3.beh spritesfile=..\gfx\Levels\sprites3.png nsprites=16 enemsfile=..\enems\enems3.ene scr_ini=10 ini_x=2 ini_y=8 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level3.bin ..\bin\Level3c.bin > nul
del work\Level3.bin > nul

echo Level 4 Wonder Boy3 world
..\..\..\src\utils\buildLevel.exe work\Level4.bin mapfile=..\map\mapa4.map map_w=5 map_h=4 decorations=..\script\decorations4.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work4.png behsfile=..\Levels\w4.beh spritesfile=..\gfx\Levels\sprites4.png nsprites=16 enemsfile=..\enems\enems4.ene scr_ini=0 ini_x=2 ini_y=6 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level4.bin ..\bin\Level4c.bin > nul
del work\Level4.bin > nul

echo Level 5 Shinobi world
..\..\..\src\utils\buildLevel.exe work\Level5.bin mapfile=..\map\mapa5.map map_w=10 map_h=2 decorations=..\script\decorations5.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work5.png behsfile=..\Levels\w5.beh spritesfile=..\gfx\Levels\sprites5.png nsprites=16 enemsfile=..\enems\enems5.ene scr_ini=0 ini_x=2 ini_y=8 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level5.bin ..\bin\Level5c.bin > nul
del work\Level5.bin > nul

echo Level 6 Rooms
..\..\..\src\utils\buildLevel.exe work\Level6.bin mapfile=..\map\mapa6.map map_w=5 map_h=4 decorations=..\script\decorations6.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work6.png behsfile=..\Levels\w6.beh spritesfile=..\gfx\Levels\sprites1.png nsprites=16 enemsfile=..\enems\enems6.ene scr_ini=0 ini_x=4 ini_y=8 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level6.bin ..\bin\Level6c.bin > nul
del work\Level6.bin > nul

echo Level 7 G and G world
..\..\..\src\utils\buildLevel.exe work\Level7.bin mapfile=..\map\mapa7.map map_w=10 map_h=2 decorations=..\script\decorations7.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work7.png behsfile=..\Levels\w7.beh spritesfile=..\gfx\Levels\sprites7.png nsprites=16 enemsfile=..\enems\enems7.ene scr_ini=0 ini_x=2 ini_y=8 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level7.bin ..\bin\Level7c.bin > nul
del work\Level7.bin > nul

echo Level 8 WB1 y Gradius world
..\..\..\src\utils\buildLevel.exe work\Level8.bin mapfile=..\map\mapa8.map map_w=10 map_h=2 decorations=..\script\decorations8.spt fontfile=..\gfx\font.png tilesfile=..\gfx\Levels\work8.png behsfile=..\Levels\w8.beh spritesfile=..\gfx\Levels\sprites8.png nsprites=16 enemsfile=..\enems\enems8.ene scr_ini=0 ini_x=0 ini_y=7 enems_life=1 > nul
..\..\..\src\utils\apack.exe work\Level8.bin ..\bin\Level8c.bin > nul
del work\Level8.bin > nul
