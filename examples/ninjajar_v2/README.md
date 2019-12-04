# Ninjajar! v2
### Ported to MK2 as an excercise, illustration and example - with enhancements!

Now this is a mammoth project. I've been wanting to update Ninjajar for a long time, and five years later I think it's time. Ninjajar was the game which we were developing when MK1 made its transition to MK2, so it's built in a somewhat old, buggy, and more cumbersome engine. Porting it to the latest (current) MK2 will make te game generally better - more robust, faster, and smaller.

Ninjajar is a 128K MK2 game, which means that it's almost like a 48K game with empty assets but with tons of compressed binaries stored in the extra memory which is decompressed to the main buffers on demand. The script and text messages reside also in extended RAM.

There's lots to do to make this game work in the latest MK2. I'm going to take a clean approach just like I have just done with **The Hobbit** and **Journey**. First of all, I'll copy the base project, then fetch all the resources. Next thing will be creating a makelevels.bat to convert and compress all resources and configure the librarian. Once all the resources are in place, it will be time to make changes to `config.h` and then fix `levels128.h` to construct all 21 levels, configure the scripting system, build `extern.h`, set up the OGT, and then get a first version where you can execute and play any level.

Once that is done I'll add the title screen, cutscenes, password system, etc.

This document contains every step I've made, so it will be a nice guide to build a full-fledged game with MK2.

Let's get busy!

## Graphic assets: fixed screens

The game contains lots of fixed screens. The original game does not have a script to automate the building and compression of these screens which we'll promptly add, `build_fixed.bat`:

```
	@echo off
	echo Building fixed screens
	echo ======================
	echo Converting...
	..\..\..\src\utils\png2scr.exe ..\gfx\dedicado.png work\dedicado.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\ending.png work\ending.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\ending1.png work\ending1.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\ending2.png work\ending2.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\ending3.png work\ending3.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\ending4.png work\ending4.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\level.png work\level.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\marco.png work\marco.src >nul
	..\..\..\src\utils\png2scr.exe ..\gfx\title.png work\title.src >nul

	echo Compressing...
	..\..\..\src\utils\apack.exe work\dedicado.src ..\bin\dedicado.bin >nul 
	..\..\..\src\utils\apack.exe work\ending.src ..\bin\ending.bin >nul 
	..\..\..\src\utils\apack.exe work\ending1.src ..\bin\ending1.bin >nul 
	..\..\..\src\utils\apack.exe work\ending2.src ..\bin\ending2.bin >nul 
	..\..\..\src\utils\apack.exe work\ending3.src ..\bin\ending3.bin >nul 
	..\..\..\src\utils\apack.exe work\ending4.src ..\bin\ending4.bin >nul 
	..\..\..\src\utils\apack.exe work\level.src ..\bin\level.bin >nul 
	..\..\..\src\utils\apack.exe work\loading.src ..\bin\loading.bin >nul 
	..\..\..\src\utils\apack.exe work\marco.src ..\bin\marco.bin >nul 
	..\..\..\src\utils\apack.exe work\title.src ..\bin\title.bin >nul 

	echo Cleaning...
	del work\*.src >nul 

	echo DONE
```

## Graphics assets: spritesets and tilesets

We'll just copy those to gfx. Conversion and compression will be taken care by `build_levels.bat`, except for `font.png`. The files are:

- font.png
- sprites0.png
- sprites1.png
- sprites2.png
- sprites4.png
- work0.png
- work1.png
- work2.png
- work3.png
- work4.png
- work5.png
- work8.png
- work9.png
- workA.png
- workb.png
- workc.png
- workX.png
- workY.png
- workZ.png

`font.png` contains the font and characters to draw the text boxes. `sprites?.png` are the four spritesets and `work?.png` are the 14 different tilesets used in this game.

As mentionted, `font.png` isn't covered in `build_levels.bat` and has to be converted from the main `compile.bat`:

```
	echo ### MAKING TILESET ###
	..\..\..\src\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin forcezero
```

## Map data

The game features 19 different maps. I've copied them to the `map` folder and exported the `.map` files with mappy. The maps are:

- mapa0.fmp
- mapa1.fmp
- mapa2.fmp
- mapa3.fmp
- mapa4.fmp
- mapa5.fmp
- mapa6.fmp
- mapa7.fmp
- mapa8.fmp
- mapa9.fmp
- mapaA.fmp
- mapaB.fmp
- mapaC.fmp
- mapaD.fmp
- mapaE.fmp
- mapaF.fmp
- mapaX.fmp
- mapaY.fmp
- mapaZ.fmp

The actual conversion and compression is handled by `build_levels.bat` as well.

## Enems data

As always, enems data is always trickier as the format has changed and files have to be updated. I've copied every .ene file in the original to a scratch folder, edited them with an hex editor to fix the header and reat the tiles from a the .png file, and then executed `enemsupdater.exe` for each. 

```
	$ for /r %T in (..\scratch\*.ene) do ..\..\..\src\utils\enemsupdr.exe %T %~nxT verbose
```

The results are stored in the `enems` folder:

- enems0.ene
- enems1.ene
- enems2.ene
- enems3.ene
- enems4.ene
- enems5.ene
- enems6.ene
- enems7.ene
- enems8.ene
- enems9.ene
- enemsA.ene
- enemsB.ene
- enemsC.ene
- enemsD.ene
- enemsE.ene
- enemsf.ene
- enemsX.ene
- enemsY.ene
- enemsZ.ene

## Behs data

Metatileset behaviour data are stored in text files. We'll just copy them into the `levels` folder. I've never found a better (proper) place to store them.

## `build_levels.bat`

This file is a huge collection of calls to the converters and the compressor. For each level there's a construct that's simmilar to this:

```
	echo Level 0
	..\utils\map2bin.exe ..\map\mapa0.map 1 12 99 work\map0.bin work\bolts0.bin >nul
	..\utils\ts2bin.exe nofont ..\gfx\work0.png work\ts0.bin >nul
	..\utils\sp2bin.exe ..\gfx\sprites0.png work\ss0.bin >nul
	..\utils\ene2bin.exe 1 12 1 ..\enems\enems0.ene work\enems0.bin work\hotspots0.bin >nul
	..\utils\behs2bin.exe ..\levels\behs0.txt work\behs0.bin >nul
	..\utils\apack.exe work\map0.bin ..\bin\map0c.bin >nul
	..\utils\apack.exe work\ts0.bin ..\bin\ts0c.bin >nul
	..\utils\apack.exe work\ss0.bin ..\bin\ss0c.bin >nul
	..\utils\apack.exe work\enems0.bin ..\bin\enems0c.bin >nul
	..\utils\apack.exe work\hotspots0.bin ..\bin\hotspots0c.bin >nul
	..\utils\apack.exe work\behs0.bin ..\bin\behs0c.bin >nul
```

That should convert everything, compress it, and place it in the `bin` folder, ready to be parsed by the librarian and made into `RAMx.bin` files. Note how `bolts?.bin` are not included, as Ninjajar! doesn't use locks & keys.

## The librarian

The librarian is a rather simple program which parses a text file containing a list of binaries and creates several `RAMx.bin` binaries (3, 4, 6 and 7). For each `RAMx.bin` file it supports a `preloadX.bin` file with custom data to be included at the beginning. For ninjajar, two `preloadX.bin` files are used: `preload6.bin` contains the compressed game text and `preload7.bin` contains the script.

The librarian is rather stupid as it processes the list in order and can't calculate an optimal arrangement of files to best fit the four different 16K chunks, so the files were stuffed manually at the time when the game was being developed originally. The results is `list.txt` which I've directly lifted from the old project to this and placed it into the `bin` folder.

In our `compile.bat` file we'll start by creating `preload6.bin` and `preload7.bin`, then calling the librarian. But let's leave that for later.

## Stuffed text

The text in ninjajar is read from a text file and then encoded & packed using 5 bits and escape codes. The files (`texts_EN.txt` for the English and `texts_EN.txt` for the Spanish language versions) are stored in the `texts` folder.

## Script

I'm actually crossing my fingers so no actual changes made to the `msc` compiler have broken the script for this game, which is literally *huge*.

## Music and sound

Just copy the original `mus` folder. The `WYZproPlay47aZXc.ASM` file contains WYZ player, aplib decompressor, and includes all compressed music files, instruments, and the beeper sample used in this game.

## `compile.bat`, first steps

We'll start building our `compile.bat` with the stuff we have right now. Namely converting the font, stuffing the text, compiling the script, setting up the `preloadX.bin` files, calling the librarian, and crossing our fingers so everything is in place at this point:

```
	@echo off

	SET game=ninjajar!
	SET lang=ES

	echo ------------------------------------------------------------------------------
	echo    BUILDING %game%
	echo ------------------------------------------------------------------------------

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

	echo ### BUILDING RAMS ###
	cd ..\bin
	..\..\..\src\utils\librarian.exe > nul
	copy ram?.bin ..\dev\work > nul
	copy librarian.h ..\dev\assets\ > nul
	cd ..\dev

	echo ### BUILDING WYZ PLAYER ###
	cd ..\mus
	..\..\..\src\utils\pasmo WYZproPlay47aZXc.ASM RAM1.bin > nul
	copy ram1.bin ..\dev\work
	cd ..\dev

	rem ###########################################################################
	rem ## COMPILATION AND TAPE BUILDING
	rem ###########################################################################
```

Note how you can generate the Spanish or English version just by modifying the `lang` environment variable at the top of the file. More on this later.

Interesting stuff:

1. First of all `font.png` is converted using `ts2bin.exe`, as usual.
2. `textstuffer` takes a third parameter for word wrapping. It will break lines every N characters properly, respecting word boundaries. Note how we directly place the encoded text as `preload6.bin` in the `bin` folder.
3. Next is a call to the msc compiler. The `rampage` parameter is added so the generated interpreter includes code to read the bites from a different RAM page. As the script will be placed at the beginning of the bankable memory, `#define SCRIPT_INIT 49152` is added to `msc-config.h`. Then both `msc.h` and `msc-config.h` are copied to `dev/my` and `scripts.bin` becomes `preload7.bin` in the `bin` folder.
4. Moving to `bin` and executing `librarian.exe` from there will generate four `RAMx.bin` files using the binaries listed in `list.txt` and the `preloadX.bin` files we just created. It will also generate a listing file, `librarian.h`, which is promptly copied to `dev/assets`.
5. Last but not least, `WYZproPlay47aZXc.ASM` is assembled to generate `RAM1.bin`.

It's a good idea to run the script at this point so we can check everything is in place and we haven't made mistakes.

## The levelset, `assets/levels128.h`

This may be a bit tricky for newcomers, so I'll explain how levelsets are made in `MK2`.

First of all, the engine internally uses a `level_data` struct of type `LEVELHEADER`, where it stores thinks like the map dimmensions, initial location, win codition, etc. This `level_data` struct is directly used by the *simple*, bundled level packs which games such as Mojon Twins' **Goku Mal** or Pat Morita Team's **Ninjakul**, **Gimmick** or **Black'n'White**, as the level headers are copied directly into it, and the whole level is compressed together and unpacked to the buffers which are set up in the correct order so everything ends up in place.

But as we were making Ninjajar! we realized we'd need to reuse tilesets and other assets, so we developed a different approach in which each asset is compressed separately and not bundled in any form, so a more complex `levels` is needed to list all the level assets and configurations. That's what we define at the end of `levels128.h`.

This *complex* mode is activated via the `EXTENDED_LEVELS` directive in `config.h` as we'll explain later.

The level structure is of type `LEVEL`, which, for `EXTENDED_LEVELS`, has these fields:

```c
typedef struct {
	unsigned char map_res;
	#ifndef DEACTIVATE_KEYS
		unsigned char bolts_res;
	#endif
	unsigned char ts_res;
	unsigned char ss_res;
	unsigned char enems_res;
	#ifndef DISABLE_HOTSPOTS
		unsigned char hotspots_res;
	#endif
	unsigned char behs_res;

	unsigned char music_id;
	unsigned char scr_ini, ini_x, ini_y;
	unsigned char scr_fin;
	unsigned char map_w, map_h;
	unsigned char max_objs;
	unsigned char enems_life;
	unsigned char win_condition;
	unsigned char switchable_engine_type;
	unsigned char facing;
	unsigned char activate_scripting;
	unsigned int script_offset;
} LEVEL;
```

Note how the `bolts_res` and `hotspots_res` fields may or may not be present.

So each level entry of our levels array for Ninjajar (which doesn't use locks, but does use hotspots) is as follows (this is the entry for the first level:

```c
	{MAP5C_BIN, TS5C_BIN, SS0C_BIN, ENEMS5C_BIN, HOTSPOTS5C_BIN, BEHS5C_BIN, 0, 
	 8, 7, 7, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_0},
```

Here is what we found in the struct:

1. Resource number for the map data. `MAP5C_BIN` and the other `*_BIN` constants are generated by the librarian. The key is pretty simple: the original compressed asset `map5c.bin` which is stored somewhere in extended RAM can be easily located using the librarian and the automaticly generated constant `MAP5C_BIN`.
2. Resource number for the tileset.
3. Resource number for the spriteset.
4. Resource number for the enems array.
5. Resource number for the hotspots array.
6. Resource number for the metatile behaviour array.
7. Background music track number
8. Initial room number
9. Initial X position (in metatile coordinates).
10. Initial Y position (in metatile coordinates).
11. Final room number. 99 for 'not used' (in fact, any number which is out of bounds).
12. Map width.
13. Map height. The total amount of screen (width*height) must be <= `MAP_W * MAP_H`, as explained later.
14. Number of collectable objects, which in this game is always 1, as the onigiri you must bite to end most levels is actually a hotspot of type 1 (collectable object). 
15. Enemy life, always 1 in this game.
16. Win condition: 0 for "level ends after collecting all collectable objects", 1 for "level ends upon getting to the final room", 2 for "level ends on WIN LEVEL or WIN GAME in the script", 3 for "level ends when `flag [FLAG_SLOT_ALLDONE]` is set". In this game, when a level (most of them) should end when getting the onigiri, `max_objs` is set to 1 and `win_condition` is set to 0. Other levels are more scripting driven. Those end when `WIN LEVEL` is issued from the script. In those, `max_objs` is set to 99 (unreachable, out of bounds, or just a marker) and `win_condition` is set to 2.
17. Engine type: **MK2** supports activating several engines and switching them as per level basis. In Ninjajar, the jumping engine and the swimming engine are enabled. `SENG_JUMP` makes a level to use the jumping engine; `SENG_SWIM` selects the swimming engine.
18. Facing: start this level facing left (1) or right (0).
19. Scripting is enabled for this level (1) or not (0).
20. If 19 is set, the script offset. This offset is easily calculated, as `msc` will output constants for every section in the script. The actual value is `SCRIPT_INIT + CONSTANT` where `CONSTANT` is the constant output by `msc` for the desired section.

In addition to all this, Ninjajar! uses `LEVEL_SEQUENCE`, which allows to use a list of indexes to the `level` array to define a custom level order.

Notice how the first level to be executed is the tutorial, and then a set of levels in order intersped with level 11 which is the shop.

```c
	#ifdef LEVEL_SEQUENCE
		unsigned char level_sequence [] = {
			12,
			0, 1, 2, 11, 
			3, 4, 5, 11,
			6, 7, 8, 11,
			9, 10, 11,
			15, 14, 13, 11,
			11, 17, 16, 18
		};
	#endif
```

## Building

Run these commands to completely rebuild Ninjajar! v2

```
	$ setenv.bat
	$ build_fixed.bat
	$ build_levels.bat
	$ compile.bat
```

