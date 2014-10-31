@echo off

echo *******************
echo * BUILDING LEVELS *
echo *******************
echo.

echo ***********
echo * LEVEL 0 *
echo ***********
..\utils\map2bin.exe ..\map\mapa0.map 1 12 99 map0.bin bolts0.bin
..\utils\ts2bin.exe nofont ..\gfx\work0.png ts0.bin
..\utils\sp2bin.exe ..\gfx\sprites0.png ss0.bin
..\utils\ene2bin.exe 1 12 1 ..\enems\enems0.ene enems0.bin hotspots0.bin
..\utils\behs2bin.exe behs0.txt behs0.bin
echo "Compressing map"
..\utils\apack.exe map0.bin ..\bin\map0c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts0.bin ..\bin\bolts0c.bin
echo "Compressing tileset"
..\utils\apack.exe ts0.bin ..\bin\ts0c.bin
echo "Compressing spriteset"
..\utils\apack.exe ss0.bin ..\bin\ss0c.bin
echo "Compressing enems"
..\utils\apack.exe enems0.bin ..\bin\enems0c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots0.bin ..\bin\hotspots0c.bin
echo "Compressing behs"
..\utils\apack.exe behs0.bin ..\bin\behs0c.bin
echo "Cleanup"
del map0.bin
del bolts0.bin
del ts0.bin
del ss0.bin
del enems0.bin
del hotspots0.bin
del behs0.bin

echo ***********
echo * LEVEL 1 *
echo ***********
..\utils\map2bin.exe ..\map\mapa1.map 12 1 99 map1.bin bolts1.bin
..\utils\ts2bin.exe nofont ..\gfx\work1.png ts1.bin
..\utils\sp2bin.exe ..\gfx\sprites1.png ss1.bin
..\utils\ene2bin.exe 12 1 1 ..\enems\enems1.ene enems1.bin hotspots1.bin
..\utils\behs2bin.exe behs1.txt behs1.bin
echo "Compressing map"
..\utils\apack.exe map1.bin ..\bin\map1c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts1.bin ..\bin\bolts1c.bin
echo "Compressing tileset"
..\utils\apack.exe ts1.bin ..\bin\ts1c.bin
echo "Compressing spriteset"
..\utils\apack.exe ss1.bin ..\bin\ss1c.bin
echo "Compressing enems"
..\utils\apack.exe enems1.bin ..\bin\enems1c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots1.bin ..\bin\hotspots1c.bin
echo "Compressing behs"
..\utils\apack.exe behs1.bin ..\bin\behs1c.bin
echo "Cleanup"
del map1.bin
del bolts1.bin
del ts1.bin
del ss1.bin
del enems1.bin
del hotspots1.bin
del behs1.bin

echo ***********
echo * LEVEL 2 *
echo ***********
..\utils\map2bin.exe ..\map\mapa2.map 10 1 99 map2.bin bolts2.bin
..\utils\ts2bin.exe nofont ..\gfx\work2.png ts2.bin
..\utils\sp2bin.exe ..\gfx\sprites2.png ss2.bin
..\utils\ene2bin.exe 10 1 1 ..\enems\enems2.ene enems2.bin hotspots2.bin
..\utils\behs2bin.exe behs2.txt behs2.bin
echo "Compressing map"
..\utils\apack.exe map2.bin ..\bin\map2c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts2.bin ..\bin\bolts2c.bin
echo "Compressing tileset"
..\utils\apack.exe ts2.bin ..\bin\ts2c.bin
echo "Compressing spriteset"
..\utils\apack.exe ss2.bin ..\bin\ss2c.bin
echo "Compressing enems"
..\utils\apack.exe enems2.bin ..\bin\enems2c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots2.bin ..\bin\hotspots2c.bin
echo "Compressing behs"
..\utils\apack.exe behs2.bin ..\bin\behs2c.bin
echo "Cleanup"
del map2.bin
del bolts2.bin
del ts2.bin
del ss2.bin
del enems2.bin
del hotspots2.bin
del behs2.bin

echo ***********
echo * LEVEL 3 *
echo ***********
..\utils\map2bin.exe ..\map\mapa3.map 10 2 99 map3.bin bolts3.bin
..\utils\ts2bin.exe nofont ..\gfx\work3.png ts3.bin
rem reuses sprites1
..\utils\ene2bin.exe 10 2 1 ..\enems\enems3.ene enems3.bin hotspots3.bin
..\utils\behs2bin.exe behs3.txt behs3.bin
echo "Compressing map"
..\utils\apack.exe map3.bin ..\bin\map3c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts3.bin ..\bin\bolts3c.bin
echo "Compressing tileset"
..\utils\apack.exe ts3.bin ..\bin\ts3c.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ss3.bin ..\bin\ss3c.bin
echo "Compressing enems"
..\utils\apack.exe enems3.bin ..\bin\enems3c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots3.bin ..\bin\hotspots3c.bin
echo "Compressing behs"
..\utils\apack.exe behs3.bin ..\bin\behs3c.bin
echo "Cleanup"
del map3.bin
del bolts3.bin
del ts3.bin
del enems3.bin
del hotspots3.bin
del behs3.bin

echo ***********
echo * LEVEL 4 *
echo ***********
..\utils\map2bin.exe ..\map\mapa4.map 12 1 99 map4.bin bolts4.bin
..\utils\ts2bin.exe nofont ..\gfx\work4.png ts4.bin
..\utils\sp2bin.exe ..\gfx\sprites4.png ss4.bin
..\utils\ene2bin.exe 12 1 1 ..\enems\enems4.ene enems4.bin hotspots4.bin
..\utils\behs2bin.exe behs4.txt behs4.bin
echo "Compressing map"
..\utils\apack.exe map4.bin ..\bin\map4c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts4.bin ..\bin\bolts4c.bin
echo "Compressing tileset"
..\utils\apack.exe ts4.bin ..\bin\ts4c.bin
echo "Compressing spriteset"
..\utils\apack.exe ss4.bin ..\bin\ss4c.bin
echo "Compressing enems"
..\utils\apack.exe enems4.bin ..\bin\enems4c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots4.bin ..\bin\hotspots4c.bin
echo "Compressing behs"
..\utils\apack.exe behs4.bin ..\bin\behs4c.bin
echo "Cleanup"
del map4.bin
del bolts4.bin
del ts4.bin
del ss4.bin
del enems4.bin
del hotspots4.bin
del behs4.bin

echo ***********
echo * LEVEL 5 *
echo ***********
..\utils\map2bin.exe ..\map\mapa5.map 7 3 99 map5.bin bolts5.bin
..\utils\ts2bin.exe nofont ..\gfx\work5.png ts5.bin
rem ..\utils\sp2bin.exe ..\gfx\sprites5.png ss5.bin
..\utils\ene2bin.exe 7 3 1 ..\enems\enems5.ene enems5.bin hotspots5.bin
..\utils\behs2bin.exe behs5.txt behs5.bin
echo "Compressing map"
..\utils\apack.exe map5.bin ..\bin\map5c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts5.bin ..\bin\bolts5c.bin
echo "Compressing tileset"
..\utils\apack.exe ts5.bin ..\bin\ts5c.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ss5.bin ..\bin\ss5c.bin
echo "Compressing enems"
..\utils\apack.exe enems5.bin ..\bin\enems5c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots5.bin ..\bin\hotspots5c.bin
echo "Compressing behs"
..\utils\apack.exe behs5.bin ..\bin\behs5c.bin
echo "Cleanup"
del map5.bin
del bolts5.bin
del ts5.bin
rem del ss5.bin
del enems5.bin
del hotspots5.bin
del behs5.bin

echo ***********
echo * LEVEL 6 *
echo ***********
..\utils\map2bin.exe ..\map\mapa6.map 4 3 99 map6.bin bolts6.bin
..\utils\ene2bin.exe 4 3 1 ..\enems\enems6.ene enems6.bin hotspots6.bin
echo "Compressing map"
..\utils\apack.exe map6.bin ..\bin\map6c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts6.bin ..\bin\bolts6c.bin
echo "Compressing enems"
..\utils\apack.exe enems6.bin ..\bin\enems6c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots6.bin ..\bin\hotspots6c.bin
echo "Cleanup"
del map6.bin
del bolts6.bin
del enems6.bin
del hotspots6.bin

echo ***********
echo * LEVEL 8 *
echo ***********
..\utils\map2bin.exe ..\map\mapa8.map 7 3 99 map8.bin bolts8.bin
..\utils\ts2bin.exe nofont ..\gfx\work8.png ts8.bin
rem ..\utils\sp2bin.exe ..\gfx\sprites8.png ss8.bin
..\utils\ene2bin.exe 7 3 1 ..\enems\enems8.ene enems8.bin hotspots8.bin
..\utils\behs2bin.exe behs8.txt behs8.bin
echo "Compressing map"
..\utils\apack.exe map8.bin ..\bin\map8c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts8.bin ..\bin\bolts8c.bin
echo "Compressing tileset"
..\utils\apack.exe ts8.bin ..\bin\ts8c.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ss8.bin ..\bin\ss8c.bin
echo "Compressing enems"
..\utils\apack.exe enems8.bin ..\bin\enems8c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots8.bin ..\bin\hotspots8c.bin
echo "Compressing behs"
..\utils\apack.exe behs8.bin ..\bin\behs8c.bin
echo "Cleanup"
del map8.bin
del bolts8.bin
del ts8.bin
rem del ss8.bin
del enems8.bin
del hotspots8.bin
del behs8.bin

echo ***********
echo * LEVEL 9 *
echo ***********
..\utils\map2bin.exe ..\map\mapa9.map 4 4 99 map9.bin bolts9.bin
..\utils\ts2bin.exe nofont ..\gfx\work9.png ts9.bin
rem ..\utils\sp2bin.exe ..\gfx\sprites9.png ss9.bin
..\utils\ene2bin.exe 4 4 1 ..\enems\enems9.ene enems9.bin hotspots9.bin
..\utils\behs2bin.exe behs9.txt behs9.bin
echo "Compressing map"
..\utils\apack.exe map9.bin ..\bin\map9c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts9.bin ..\bin\bolts9c.bin
echo "Compressing tileset"
..\utils\apack.exe ts9.bin ..\bin\ts9c.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ss9.bin ..\bin\ss9c.bin
echo "Compressing enems"
..\utils\apack.exe enems9.bin ..\bin\enems9c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots9.bin ..\bin\hotspots9c.bin
echo "Compressing behs"
..\utils\apack.exe behs9.bin ..\bin\behs9c.bin
echo "Cleanup"
del map9.bin
del bolts9.bin
del ts9.bin
rem del ss9.bin
del enems9.bin
del hotspots9.bin
del behs9.bin

echo ***********
echo * LEVEL B *
echo ***********
..\utils\map2bin.exe ..\map\mapaB.map 2 6 99 mapB.bin boltsB.bin
..\utils\ts2bin.exe nofont ..\gfx\workB.png tsB.bin
rem ..\utils\sp2bin.exe ..\gfx\spritesB.png ssB.bin
..\utils\ene2bin.exe 2 6 1 ..\enems\enemsB.ene enemsB.bin hotspotsB.bin
..\utils\behs2bin.exe behsB.txt behsB.bin
echo "Compressing map"
..\utils\apack.exe mapB.bin ..\bin\mapBc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsB.bin ..\bin\boltsBc.bin
echo "Compressing tileset"
..\utils\apack.exe tsB.bin ..\bin\tsBc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssB.bin ..\bin\ssBc.bin
echo "Compressing enems"
..\utils\apack.exe enemsB.bin ..\bin\enemsBc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsB.bin ..\bin\hotspotsBc.bin
echo "Compressing behs"
..\utils\apack.exe behsB.bin ..\bin\behsBc.bin
echo "Cleanup"
del mapB.bin
del boltsB.bin
del tsB.bin
rem del ssB.bin
del enemsB.bin
del hotspotsB.bin
del behsB.bin

echo ***********
echo * LEVEL 7 *
echo ***********
..\utils\map2bin.exe ..\map\mapa7.map 10 2 99 map7.bin bolts7.bin
rem ..\utils\ts2bin.exe nofont ..\gfx\work7.png ts7.bin
rem ..\utils\sp2bin.exe ..\gfx\sprites7.png ss7.bin
..\utils\ene2bin.exe 10 2 1 ..\enems\enems7.ene enems7.bin hotspots7.bin
rem..\utils\behs2bin.exe behs7.txt behs7.bin
echo "Compressing map"
..\utils\apack.exe map7.bin ..\bin\map7c.bin
echo "Compressing bolts"
..\utils\apack.exe bolts7.bin ..\bin\bolts7c.bin
rem echo "Compressing tileset"
rem ..\utils\apack.exe ts7.bin ..\bin\ts7c.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ss7.bin ..\bin\ss7c.bin
echo "Compressing enems"
..\utils\apack.exe enems7.bin ..\bin\enems7c.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspots7.bin ..\bin\hotspots7c.bin
rem echo "Compressing behs"
rem ..\utils\apack.exe behs7.bin ..\bin\behs7c.bin
echo "Cleanup"
del map7.bin
del bolts7.bin
rem del ts7.bin
rem del ss7.bin
del enems7.bin
del hotspots7.bin
rem del behs7.bin

echo ***********
echo * LEVEL A *
echo ***********
..\utils\map2bin.exe ..\map\mapaA.map 7 2 99 mapA.bin boltsA.bin
..\utils\ts2bin.exe nofont ..\gfx\workA.png tsA.bin
rem ..\utils\sp2bin.exe ..\gfx\sprites2.png ss2.bin
..\utils\ene2bin.exe 7 2 1 ..\enems\enemsA.ene enemsA.bin hotspotsA.bin
..\utils\behs2bin.exe behsA.txt behsA.bin
echo "Compressing map"
..\utils\apack.exe mapA.bin ..\bin\mapAc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsA.bin ..\bin\boltsAc.bin
echo "Compressing tileset"
..\utils\apack.exe tsA.bin ..\bin\tsAc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssA.bin ..\bin\ssAc.bin
echo "Compressing enems"
..\utils\apack.exe enemsA.bin ..\bin\enemsAc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsA.bin ..\bin\hotspotsAc.bin
echo "Compressing behs"
..\utils\apack.exe behsA.bin ..\bin\behsAc.bin
echo "Cleanup"
del mapA.bin
del boltsA.bin
del tsA.bin
rem del ssA.bin
del enemsA.bin
del hotspotsA.bin
del behsA.bin

echo ***********
echo * LEVEL D *
echo ***********
..\utils\map2bin.exe ..\map\mapaD.map 10 1 99 mapD.bin boltsD.bin
..\utils\ene2bin.exe 10 1 1 ..\enems\enemsD.ene enemsD.bin hotspotsD.bin
echo "Compressing map"
..\utils\apack.exe mapD.bin ..\bin\mapDc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsD.bin ..\bin\boltsDc.bin
echo "Compressing enems"
..\utils\apack.exe enemsD.bin ..\bin\enemsDc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsD.bin ..\bin\hotspotsDc.bin
echo "Cleanup"
del mapD.bin
del boltsD.bin
del enemsD.bin
del hotspotsD.bin

echo ***********
echo * LEVEL C *
echo ***********
..\utils\map2bin.exe ..\map\mapaC.map 1 10 99 mapC.bin boltsC.bin
..\utils\ts2bin.exe nofont ..\gfx\workC.png tsC.bin
rem ..\utils\sp2bin.exe ..\gfx\spritesC.png ssC.bin
..\utils\ene2bin.exe 1 10 1 ..\enems\enemsC.ene enemsC.bin hotspotsC.bin
..\utils\behs2bin.exe behsC.txt behsC.bin
echo "Compressing map"
..\utils\apack.exe mapC.bin ..\bin\mapCc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsC.bin ..\bin\boltsCc.bin
echo "Compressing tileset"
..\utils\apack.exe tsC.bin ..\bin\tsCc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssC.bin ..\bin\ssCc.bin
echo "Compressing enems"
..\utils\apack.exe enemsC.bin ..\bin\enemsCc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsC.bin ..\bin\hotspotsCc.bin
echo "Compressing behs"
..\utils\apack.exe behsC.bin ..\bin\behsCc.bin
echo "Cleanup"
del mapC.bin
del boltsC.bin
del tsC.bin
rem del ssC.bin
del enemsC.bin
del hotspotsC.bin
del behsC.bin

echo ***********
echo * LEVEL E *
echo ***********
..\utils\map2bin.exe ..\map\mapaE.map 8 2 99 mapE.bin boltsE.bin
..\utils\ene2bin.exe 8 2 1 ..\enems\enemsE.ene enemsE.bin hotspotsE.bin
echo "Compressing map"
..\utils\apack.exe mapE.bin ..\bin\mapEc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsE.bin ..\bin\boltsEc.bin
echo "Compressing enems"
..\utils\apack.exe enemsE.bin ..\bin\enemsEc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsE.bin ..\bin\hotspotsEc.bin
echo "Cleanup"
del mapE.bin
del boltsE.bin
del enemsE.bin
del hotspotsE.bin

echo ***********
echo * LEVEL F *
echo ***********
..\utils\map2bin.exe ..\map\mapaF.map 1 12 99 mapF.bin boltsF.bin
..\utils\ene2bin.exe 1 12 1 ..\enems\enemsF.ene enemsF.bin hotspotsF.bin
echo "Compressing map"
..\utils\apack.exe mapF.bin ..\bin\mapFc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsF.bin ..\bin\boltsFc.bin
echo "Compressing enems"
..\utils\apack.exe enemsF.bin ..\bin\enemsFc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsF.bin ..\bin\hotspotsFc.bin
echo "Cleanup"
del mapF.bin
del boltsF.bin
del enemsF.bin
del hotspotsF.bin

echo ***********
echo * LEVEL Z *
echo ***********
..\utils\map2bin.exe ..\map\mapaZ.map 4 5 99 mapZ.bin boltsZ.bin
..\utils\ts2bin.exe nofont ..\gfx\workZ.png tsZ.bin
rem ..\utils\sp2bin.exe ..\gfx\spritesZ.png ssZ.bin
..\utils\ene2bin.exe 4 5 1 ..\enems\enemsZ.ene enemsZ.bin hotspotsZ.bin
..\utils\behs2bin.exe behsZ.txt behsZ.bin
echo "Compressing map"
..\utils\apack.exe mapZ.bin ..\bin\mapZc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsZ.bin ..\bin\boltsZc.bin
echo "Compressing tileset"
..\utils\apack.exe tsZ.bin ..\bin\tsZc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssZ.bin ..\bin\ssZc.bin
echo "Compressing enems"
..\utils\apack.exe enemsZ.bin ..\bin\enemsZc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsZ.bin ..\bin\hotspotsZc.bin
echo "Compressing behs"
..\utils\apack.exe behsZ.bin ..\bin\behsZc.bin
echo "Cleanup"
del mapZ.bin
del boltsZ.bin
del tsZ.bin
rem del ssZ.bin
del enemsZ.bin
del hotspotsZ.bin
del behsZ.bin

echo ***********
echo * LEVEL Y *
echo ***********
..\utils\map2bin.exe ..\map\mapaY.map 20 1 99 mapY.bin boltsY.bin
..\utils\ts2bin.exe nofont ..\gfx\workY.png tsY.bin
rem ..\utils\sp2bin.exe ..\gfx\spritesY.png ssY.bin
..\utils\ene2bin.exe 20 1 1 ..\enems\enemsY.ene enemsY.bin hotspotsY.bin
..\utils\behs2bin.exe behsY.txt behsY.bin
echo "Compressing map"
..\utils\apack.exe mapY.bin ..\bin\mapYc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsY.bin ..\bin\boltsYc.bin
echo "Compressing tileset"
..\utils\apack.exe tsY.bin ..\bin\tsYc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssY.bin ..\bin\ssYc.bin
echo "Compressing enems"
..\utils\apack.exe enemsY.bin ..\bin\enemsYc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsY.bin ..\bin\hotspotsYc.bin
echo "Compressing behs"
..\utils\apack.exe behsY.bin ..\bin\behsYc.bin
echo "Cleanup"
del mapY.bin
del boltsY.bin
del tsY.bin
rem del ssY.bin
del enemsY.bin
del hotspotsY.bin
del behsY.bin

echo ***********
echo * LEVEL X *
echo ***********
..\utils\map2bin.exe ..\map\mapaX.map 3 1 99 mapX.bin boltsX.bin
..\utils\ts2bin.exe nofont ..\gfx\workX.png tsX.bin
rem ..\utils\sp2bin.exe ..\gfx\spritesX.png ssX.bin
..\utils\ene2bin.exe 20 1 1 ..\enems\enemsX.ene enemsX.bin hotspotsX.bin
..\utils\behs2bin.exe behsX.txt behsX.bin
echo "Compressing map"
..\utils\apack.exe mapX.bin ..\bin\mapXc.bin
echo "Compressing bolts"
..\utils\apack.exe boltsX.bin ..\bin\boltsXc.bin
echo "Compressing tileset"
..\utils\apack.exe tsX.bin ..\bin\tsXc.bin
rem echo "Compressing spriteset"
rem ..\utils\apack.exe ssX.bin ..\bin\ssXc.bin
echo "Compressing enems"
..\utils\apack.exe enemsX.bin ..\bin\enemsXc.bin
echo "Compressing hotspots"
..\utils\apack.exe hotspotsX.bin ..\bin\hotspotsXc.bin
echo "Compressing behs"
..\utils\apack.exe behsX.bin ..\bin\behsXc.bin
echo "Cleanup"
del mapX.bin
del boltsX.bin
del tsX.bin
rem del ssX.bin
del enemsX.bin
del hotspotsX.bin
del behsX.bin
