rem EXAMPLE!
@echo off
echo BUILDING LEVELS!
echo ================
echo.
rem Example level with two subtilesets.
echo LEVEL 0
echo MAIN
..\utils\buildlevel.exe level0.bin mapfile=..\map\map0.map map_w=4 map_h=4 attrsfile=..\map\map0.sts decorations=..\script\decos0.spt nohotspots fontfile=..\gfx\font.png tilesfile=..\gfx\levels\w0.png behsfile=..\gfx\levels\w0.beh spritesfile=..\gfx\levels\sprites0.png nsprites=18 enemsfile=..\enems\enems0.ene scr_ini=0 ini_x=7 ini_y=4 enems_life=1
..\utils\apack.exe level0.bin ..\bin\level0c.bin > nul
echo Compressed to \bin\level0c.bin
echo SUBTS1
..\utils\mksubts ..\gfx\levels\w0r1.png 0 ..\gfx\levels\w0r1.beh ..\bin\level0r1.bin
echo SUBTS2
..\utils\mksubts ..\gfx\levels\w0r2.png 0 ..\gfx\levels\w0r2.beh ..\bin\level0r2.bin
echo DONE!
del level0.bin > nul
echo -------------------------------------------------------------------------------
echo.
