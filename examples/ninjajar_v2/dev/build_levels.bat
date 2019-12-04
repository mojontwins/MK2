@echo off

echo Building Levels
echo ===============

echo Level 0
..\..\..\src\utils\map2bin.exe ..\map\mapa0.map 1 12 99 work\map0.bin work\bolts0.bin >nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work0.png work\ts0.bin >nul
..\..\..\src\utils\sp2bin.exe ..\gfx\sprites0.png work\ss0.bin >nul
..\..\..\src\utils\ene2bin.exe 1 12 1 ..\enems\enems0.ene work\enems0.bin work\hotspots0.bin >nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs0.txt work\behs0.bin >nul
..\..\..\src\utils\apack.exe work\map0.bin ..\bin\map0c.bin >nul
..\..\..\src\utils\apack.exe work\ts0.bin ..\bin\ts0c.bin >nul
..\..\..\src\utils\apack.exe work\ss0.bin ..\bin\ss0c.bin >nul
..\..\..\src\utils\apack.exe work\enems0.bin ..\bin\enems0c.bin >nul
..\..\..\src\utils\apack.exe work\hotspots0.bin ..\bin\hotspots0c.bin >nul
..\..\..\src\utils\apack.exe work\behs0.bin ..\bin\behs0c.bin >nul

echo Level 1
..\..\..\src\utils\map2bin.exe ..\map\mapa1.map 12 1 99 work\map1.bin work\bolts1.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work1.png work\ts1.bin > nul
..\..\..\src\utils\sp2bin.exe ..\gfx\sprites1.png work\ss1.bin > nul
..\..\..\src\utils\ene2bin.exe 12 1 1 ..\enems\enems1.ene work\enems1.bin work\hotspots1.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs1.txt work\behs1.bin > nul
..\..\..\src\utils\apack.exe work\map1.bin ..\bin\map1c.bin > nul
..\..\..\src\utils\apack.exe work\ts1.bin ..\bin\ts1c.bin > nul
..\..\..\src\utils\apack.exe work\ss1.bin ..\bin\ss1c.bin > nul
..\..\..\src\utils\apack.exe work\enems1.bin ..\bin\enems1c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots1.bin ..\bin\hotspots1c.bin > nul
..\..\..\src\utils\apack.exe work\behs1.bin ..\bin\behs1c.bin > nul

echo Level 2
..\..\..\src\utils\map2bin.exe ..\map\mapa2.map 10 1 99 work\map2.bin work\bolts2.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work2.png work\ts2.bin > nul
..\..\..\src\utils\sp2bin.exe ..\gfx\sprites2.png work\ss2.bin > nul
..\..\..\src\utils\ene2bin.exe 10 1 1 ..\enems\enems2.ene work\enems2.bin work\hotspots2.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs2.txt work\behs2.bin > nul
..\..\..\src\utils\apack.exe work\map2.bin ..\bin\map2c.bin > nul
..\..\..\src\utils\apack.exe work\ts2.bin ..\bin\ts2c.bin > nul
..\..\..\src\utils\apack.exe work\ss2.bin ..\bin\ss2c.bin > nul
..\..\..\src\utils\apack.exe work\enems2.bin ..\bin\enems2c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots2.bin ..\bin\hotspots2c.bin > nul
..\..\..\src\utils\apack.exe work\behs2.bin ..\bin\behs2c.bin > nul

echo Level 3
..\..\..\src\utils\map2bin.exe ..\map\mapa3.map 10 2 99 work\map3.bin work\bolts3.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work3.png work\ts3.bin > nul
rem reuses sprites1
..\..\..\src\utils\ene2bin.exe 10 2 1 ..\enems\enems3.ene work\enems3.bin work\hotspots3.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs3.txt work\behs3.bin > nul
..\..\..\src\utils\apack.exe work\map3.bin ..\bin\map3c.bin > nul
..\..\..\src\utils\apack.exe work\ts3.bin ..\bin\ts3c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ss3.bin ..\bin\ss3c.bin > nul
..\..\..\src\utils\apack.exe work\enems3.bin ..\bin\enems3c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots3.bin ..\bin\hotspots3c.bin > nul
..\..\..\src\utils\apack.exe work\behs3.bin ..\bin\behs3c.bin > nul

echo Level 4
..\..\..\src\utils\map2bin.exe ..\map\mapa4.map 12 1 99 work\map4.bin work\bolts4.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work4.png work\ts4.bin > nul
..\..\..\src\utils\sp2bin.exe ..\gfx\sprites4.png work\ss4.bin > nul
..\..\..\src\utils\ene2bin.exe 12 1 1 ..\enems\enems4.ene work\enems4.bin work\hotspots4.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs4.txt work\behs4.bin > nul
..\..\..\src\utils\apack.exe work\map4.bin ..\bin\map4c.bin > nul
..\..\..\src\utils\apack.exe work\ts4.bin ..\bin\ts4c.bin > nul
..\..\..\src\utils\apack.exe work\ss4.bin ..\bin\ss4c.bin > nul
..\..\..\src\utils\apack.exe work\enems4.bin ..\bin\enems4c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots4.bin ..\bin\hotspots4c.bin > nul
..\..\..\src\utils\apack.exe work\behs4.bin ..\bin\behs4c.bin > nul

echo Level 5
..\..\..\src\utils\map2bin.exe ..\map\mapa5.map 7 3 99 work\map5.bin work\bolts5.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work5.png work\ts5.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\sprites5.png work\ss5.bin > nul
..\..\..\src\utils\ene2bin.exe 7 3 1 ..\enems\enems5.ene work\enems5.bin work\hotspots5.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs5.txt work\behs5.bin > nul
..\..\..\src\utils\apack.exe work\map5.bin ..\bin\map5c.bin > nul
..\..\..\src\utils\apack.exe work\ts5.bin ..\bin\ts5c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ss5.bin ..\bin\ss5c.bin > nul
..\..\..\src\utils\apack.exe work\enems5.bin ..\bin\enems5c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots5.bin ..\bin\hotspots5c.bin > nul
..\..\..\src\utils\apack.exe work\behs5.bin ..\bin\behs5c.bin > nul

echo Level 6
..\..\..\src\utils\map2bin.exe ..\map\mapa6.map 4 3 99 work\map6.bin work\bolts6.bin > nul
..\..\..\src\utils\ene2bin.exe 4 3 1 ..\enems\enems6.ene work\enems6.bin work\hotspots6.bin > nul
..\..\..\src\utils\apack.exe work\map6.bin ..\bin\map6c.bin > nul
..\..\..\src\utils\apack.exe work\enems6.bin ..\bin\enems6c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots6.bin ..\bin\hotspots6c.bin > nul

echo Level 7
..\..\..\src\utils\map2bin.exe ..\map\mapa7.map 10 2 99 work\map7.bin work\bolts7.bin > nul
rem ..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work7.png work\ts7.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\sprites7.png work\ss7.bin > nul
..\..\..\src\utils\ene2bin.exe 10 2 1 ..\enems\enems7.ene work\enems7.bin work\hotspots7.bin > nul
rem..\..\..\src\utils\behs2bin.exe ..\levels\behs7.txt work\behs7.bin > nul
..\..\..\src\utils\apack.exe work\map7.bin ..\bin\map7c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ts7.bin ..\bin\ts7c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ss7.bin ..\bin\ss7c.bin > nul
..\..\..\src\utils\apack.exe work\enems7.bin ..\bin\enems7c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots7.bin ..\bin\hotspots7c.bin > nul
rem ..\..\..\src\utils\apack.exe work\behs7.bin ..\bin\behs7c.bin > nul

echo Level 8
..\..\..\src\utils\map2bin.exe ..\map\mapa8.map 7 3 99 work\map8.bin work\bolts8.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work8.png work\ts8.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\sprites8.png work\ss8.bin > nul
..\..\..\src\utils\ene2bin.exe 7 3 1 ..\enems\enems8.ene work\enems8.bin work\hotspots8.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs8.txt work\behs8.bin > nul
..\..\..\src\utils\apack.exe work\map8.bin ..\bin\map8c.bin > nul
..\..\..\src\utils\apack.exe work\ts8.bin ..\bin\ts8c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ss8.bin ..\bin\ss8c.bin > nul
..\..\..\src\utils\apack.exe work\enems8.bin ..\bin\enems8c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots8.bin ..\bin\hotspots8c.bin > nul
..\..\..\src\utils\apack.exe work\behs8.bin ..\bin\behs8c.bin > nul

echo Level 9
..\..\..\src\utils\map2bin.exe ..\map\mapa9.map 4 4 99 work\map9.bin work\bolts9.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\work9.png work\ts9.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\sprites9.png work\ss9.bin > nul
..\..\..\src\utils\ene2bin.exe 4 4 1 ..\enems\enems9.ene work\enems9.bin work\hotspots9.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behs9.txt work\behs9.bin > nul
..\..\..\src\utils\apack.exe work\map9.bin ..\bin\map9c.bin > nul
..\..\..\src\utils\apack.exe work\ts9.bin ..\bin\ts9c.bin > nul
rem ..\..\..\src\utils\apack.exe work\ss9.bin ..\bin\ss9c.bin > nul
..\..\..\src\utils\apack.exe work\enems9.bin ..\bin\enems9c.bin > nul
..\..\..\src\utils\apack.exe work\hotspots9.bin ..\bin\hotspots9c.bin > nul
..\..\..\src\utils\apack.exe work\behs9.bin ..\bin\behs9c.bin > nul

echo Level A
..\..\..\src\utils\map2bin.exe ..\map\mapaA.map 7 2 99 work\mapA.bin work\boltsA.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workA.png work\tsA.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\sprites2.png work\ss2.bin > nul
..\..\..\src\utils\ene2bin.exe 7 2 1 ..\enems\enemsA.ene work\enemsA.bin work\hotspotsA.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsA.txt work\behsA.bin > nul
..\..\..\src\utils\apack.exe work\mapA.bin ..\bin\mapAc.bin > nul
..\..\..\src\utils\apack.exe work\tsA.bin ..\bin\tsAc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssA.bin ..\bin\ssAc.bin > nul
..\..\..\src\utils\apack.exe work\enemsA.bin ..\bin\enemsAc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsA.bin ..\bin\hotspotsAc.bin > nul
..\..\..\src\utils\apack.exe work\behsA.bin ..\bin\behsAc.bin > nul

echo Level B
..\..\..\src\utils\map2bin.exe ..\map\mapaB.map 2 6 99 work\mapB.bin work\boltsB.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workB.png work\tsB.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\spritesB.png work\ssB.bin > nul
..\..\..\src\utils\ene2bin.exe 2 6 1 ..\enems\enemsB.ene work\enemsB.bin work\hotspotsB.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsB.txt work\behsB.bin > nul
..\..\..\src\utils\apack.exe work\mapB.bin ..\bin\mapBc.bin > nul
..\..\..\src\utils\apack.exe work\tsB.bin ..\bin\tsBc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssB.bin ..\bin\ssBc.bin > nul
..\..\..\src\utils\apack.exe work\enemsB.bin ..\bin\enemsBc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsB.bin ..\bin\hotspotsBc.bin > nul
..\..\..\src\utils\apack.exe work\behsB.bin ..\bin\behsBc.bin > nul

echo Level C
..\..\..\src\utils\map2bin.exe ..\map\mapaC.map 1 10 99 work\mapC.bin work\boltsC.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workC.png work\tsC.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\spritesC.png work\ssC.bin > nul
..\..\..\src\utils\ene2bin.exe 1 10 1 ..\enems\enemsC.ene work\enemsC.bin work\hotspotsC.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsC.txt work\behsC.bin > nul
..\..\..\src\utils\apack.exe work\mapC.bin ..\bin\mapCc.bin > nul
..\..\..\src\utils\apack.exe work\tsC.bin ..\bin\tsCc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssC.bin ..\bin\ssCc.bin > nul
..\..\..\src\utils\apack.exe work\enemsC.bin ..\bin\enemsCc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsC.bin ..\bin\hotspotsCc.bin > nul
..\..\..\src\utils\apack.exe work\behsC.bin ..\bin\behsCc.bin > nul

echo Level D
..\..\..\src\utils\map2bin.exe ..\map\mapaD.map 10 1 99 work\mapD.bin work\boltsD.bin > nul
..\..\..\src\utils\ene2bin.exe 10 1 1 ..\enems\enemsD.ene work\enemsD.bin work\hotspotsD.bin > nul
..\..\..\src\utils\apack.exe work\mapD.bin ..\bin\mapDc.bin > nul
..\..\..\src\utils\apack.exe work\enemsD.bin ..\bin\enemsDc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsD.bin ..\bin\hotspotsDc.bin > nul

echo Level E
..\..\..\src\utils\map2bin.exe ..\map\mapaE.map 8 2 99 work\mapE.bin work\boltsE.bin > nul
..\..\..\src\utils\ene2bin.exe 8 2 1 ..\enems\enemsE.ene work\enemsE.bin work\hotspotsE.bin > nul
..\..\..\src\utils\apack.exe work\mapE.bin ..\bin\mapEc.bin > nul
..\..\..\src\utils\apack.exe work\enemsE.bin ..\bin\enemsEc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsE.bin ..\bin\hotspotsEc.bin > nul

echo Level F
..\..\..\src\utils\map2bin.exe ..\map\mapaF.map 1 12 99 work\mapF.bin work\boltsF.bin > nul
..\..\..\src\utils\ene2bin.exe 1 12 1 ..\enems\enemsF.ene work\enemsF.bin work\hotspotsF.bin > nul
..\..\..\src\utils\apack.exe work\mapF.bin ..\bin\mapFc.bin > nul
..\..\..\src\utils\apack.exe work\enemsF.bin ..\bin\enemsFc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsF.bin ..\bin\hotspotsFc.bin > nul

echo Level X
..\..\..\src\utils\map2bin.exe ..\map\mapaX.map 3 1 99  work\mapX.bin  work\boltsX.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workX.png  work\tsX.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\spritesX.png  work\ssX.bin > nul
..\..\..\src\utils\ene2bin.exe 20 1 1 ..\enems\enemsX.ene  work\enemsX.bin  work\hotspotsX.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsX.txt  work\behsX.bin > nul
..\..\..\src\utils\apack.exe work\mapX.bin ..\bin\mapXc.bin > nul
..\..\..\src\utils\apack.exe work\tsX.bin ..\bin\tsXc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssX.bin ..\bin\ssXc.bin > nul
..\..\..\src\utils\apack.exe work\enemsX.bin ..\bin\enemsXc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsX.bin ..\bin\hotspotsXc.bin > nul
..\..\..\src\utils\apack.exe work\behsX.bin ..\bin\behsXc.bin > nul

echo Level Y
..\..\..\src\utils\map2bin.exe ..\map\mapaY.map 20 1 99 work\mapY.bin work\boltsY.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workY.png work\tsY.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\spritesY.png work\ssY.bin > nul
..\..\..\src\utils\ene2bin.exe 20 1 1 ..\enems\enemsY.ene work\enemsY.bin work\hotspotsY.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsY.txt work\behsY.bin > nul
..\..\..\src\utils\apack.exe work\mapY.bin ..\bin\mapYc.bin > nul
..\..\..\src\utils\apack.exe work\tsY.bin ..\bin\tsYc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssY.bin ..\bin\ssYc.bin > nul
..\..\..\src\utils\apack.exe work\enemsY.bin ..\bin\enemsYc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsY.bin ..\bin\hotspotsYc.bin > nul
..\..\..\src\utils\apack.exe work\behsY.bin ..\bin\behsYc.bin > nul

echo Level Z
..\..\..\src\utils\map2bin.exe ..\map\mapaZ.map 4 5 99 work\mapZ.bin work\boltsZ.bin > nul
..\..\..\src\utils\ts2bin.exe nofont ..\gfx\workZ.png work\tsZ.bin > nul
rem ..\..\..\src\utils\sp2bin.exe ..\gfx\spritesZ.png work\ssZ.bin > nul
..\..\..\src\utils\ene2bin.exe 4 5 1 ..\enems\enemsZ.ene work\enemsZ.bin work\hotspotsZ.bin > nul
..\..\..\src\utils\behs2bin.exe ..\levels\behsZ.txt work\behsZ.bin > nul
..\..\..\src\utils\apack.exe work\mapZ.bin ..\bin\mapZc.bin > nul
..\..\..\src\utils\apack.exe work\tsZ.bin ..\bin\tsZc.bin > nul
rem ..\..\..\src\utils\apack.exe work\ssZ.bin ..\bin\ssZc.bin > nul
..\..\..\src\utils\apack.exe work\enemsZ.bin ..\bin\enemsZc.bin > nul
..\..\..\src\utils\apack.exe work\hotspotsZ.bin ..\bin\hotspotsZc.bin > nul
..\..\..\src\utils\apack.exe work\behsZ.bin ..\bin\behsZc.bin > nul
