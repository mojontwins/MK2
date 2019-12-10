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
    ..\..\..\src\utils\png2scr.exe ..\gfx\dedicado.png work\dedicado.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\ending.png work\ending.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\ending1.png work\ending1.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\ending2.png work\ending2.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\ending3.png work\ending3.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\ending4.png work\ending4.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\level.png work\level.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\loading.png work\loading.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\marco.png work\marco.scr >nul
    ..\..\..\src\utils\png2scr.exe ..\gfx\title.png work\title.scr >nul

    echo Compressing...
    ..\..\..\src\utils\apack.exe work\dedicado.scr ..\bin\dedicado.bin >nul 
    ..\..\..\src\utils\apack.exe work\ending.scr ..\bin\ending.bin >nul 
    ..\..\..\src\utils\apack.exe work\ending1.scr ..\bin\ending1.bin >nul 
    ..\..\..\src\utils\apack.exe work\ending2.scr ..\bin\ending2.bin >nul 
    ..\..\..\src\utils\apack.exe work\ending3.scr ..\bin\ending3.bin >nul 
    ..\..\..\src\utils\apack.exe work\ending4.scr ..\bin\ending4.bin >nul 
    ..\..\..\src\utils\apack.exe work\level.scr ..\bin\level.bin >nul 
    ..\..\..\src\utils\apack.exe work\loading.scr ..\bin\loading.bin >nul 
    ..\..\..\src\utils\apack.exe work\marco.scr ..\bin\marco.bin >nul 
    ..\..\..\src\utils\apack.exe work\title.scr ..\bin\title.bin >nul 
    copy work\loading.scr ..\bin\loading.scr > nul

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

## Engine configuration

Luckily, even if early (the earliest), the original Ninjajar! is a MK2 game. That means that every `config.h` line in the original game should be available in the current version of the engine and the semantics are the same. As with the other games, we just put the two files side to side and replicate the configuration.

I'll try and drop some lines on the important bits so this document keeps being informative to developers who want to venture in writing a full fledged game with the engine.

### General configuration

```c
    // 128K support
    #define MODE_128K                       // 128K mode.

    // Music engine
    //#define USE_ARKOS                     // Just comment this to use the default WYZ player.
    //#define ARKOS_SFX_CHANNEL     1       // SFX Channel (0-2)
    //#define NO_SOUND                      // Durante el desarrollo, no llama al player.

    // Multi-level support

    #define COMPRESSED_LEVELS               // use levels.h/levels128.h instead of mapa.h and enems.h (!)
    #define EXTENDED_LEVELS                 // Ninjajar! style full-featured levelset
    #define LEVEL_SEQUENCE                  // Ninjajar! style level sequence array
    #define SCRIPTED_GAME_ENDING            // Game ending is triggered from the script
    //#define SIMPLE_LEVEL_MANAGER          // Custom level manager "simple" <- UNFINISHED. DON'T USE!

    #define MIN_FAPS_PER_FRAME      2       // Experimental. Adds an ISR even in 48K mode.
                                            // Limits the max. speed to 50/N fps.

    // In this section we define map dimmensions, initial and authomatic ending conditions, etc.

    #define MAP_W                   3       //
    #define MAP_H                   7       // Map dimmensions in screens
    //#define ENABLE_CUSTOM_CONNECTIONS     // Custom connections array. MAP_W/MAP_H just define how many screens
    //#define SCR_INI               99      //  Initial screen
    //#define PLAYER_INI_X          99      //
    //#define PLAYER_INI_Y          99      // Initial tile coordinates
    //#define SCR_END               99      // Last screen. 99 = deactivated.
    //#define PLAYER_END_X          99      //
    //#define PLAYER_END_Y          99      // Player tile coordinates to finish game
    //#define PLAYER_MAX_OBJECTS    99      // Objects to get to finish game
    #define PLAYER_LIFE             9       // Max and starting life gauge.
    #define DONT_LIMIT_LIFE                 // If defined, no upper limit to life gauge.
    #define PLAYER_REFILL           1       // Life recharge
   // #define MAX_LEVELS            99      // # of compressed levels
    //#define REFILL_ME                     // If defined, refill player on each level
    //#define WIN_CONDITION         99      // 0 = objects collected, 1 = screen 'N', 2 = scripting, 3 = SIM
    //#define EXTRA_SPRITES         2       // For 128K games -> # of extra sprite faces to make room for.
```

This is a `MODE_128K` game which uses Wyz Player for music (so the other sound options are commented out). It uses `COMPRESSED_LEVELS` in the format already explained: `EXTENDED_LEVELS`. Also a `LEVEL_SEQUENCE` array is used. The game ending won't be launched after completing the last level, so `SCRIPTED_GAME_ENDING` should be enabled so the game ends when the script decides.

We set up `MAP_W` and `MAP_H`, as with every multi-level game, no matter the individual size of each level, so `MAP_W*MAP_H` is greater or equal to the amount of rooms in the biggest level. In this game, no level is bigger than 21 rooms, so 3 and 7 work.

The next group of directives are commented out as the initial screen, position, number of objects, etc. are managed by the level manager.

`MAX_LEVELS` is also commented out as the game ending will be launched from the script.

### Keyboard bindings

Note that Ninjajar! is not a "two buttons" game, as the "UP" direction is never used so it will be mapped to the jump function. In order to make this work with WASD and OPQA we have to change the key assignations, also in `config.h`, so they look this way:

```c 
    // UP DOWN LEFT RIGHT FIRE JUMP <- with fire/hitter/throwable
    // UP DOWN LEFT RIGHT JUMP xxxx <- with just jump, so configure ahead:
    unsigned int keyscancodes [] = {
    #ifdef USE_TWO_BUTTONS
        0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,     // WSADMN
        0x01fb, 0x01fd, 0x02df, 0x01df, 0x047f, 0x087f,     // QAOPMN
    #else
        0x087f, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0,          // NSADM-  <-- HERE
        0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0,          // QAOPs-
    #endif
    };
```

### Engine type configuration

```c
                                            // Comment all of them for normal 16x16 bounding box
    #define BOUNDING_BOX_8_BOTTOM           // 8x8 aligned to bottom center in 16x16
    //#define BOUNDING_BOX_8_CENTERED       // 8x8 aligned to center in 16x16
    //#define BOUNDING_BOX_TINY_BOTTOM      // 8x2 aligned to bottom center in 16x16
    #define SMALL_COLLISION                 // 8x8 centered collision instead of 12x12

    // General directives:
    // -------------------

    #define PLAYER_CHECK_MAP_BOUNDARIES     // If defined, you can't exit the map.
    //#define PLAYER_CYCLIC_MAP             // Cyclic, endless map in all directions.
    //#define PLAYER_CANNOT_FLICK_SCREEN    // If defined, automatic screen flicking is disabled.
    //#define PLAYER_WRAP_AROUND            // If defined, wrap-around. Needs PLAYER_CANNOT_FLICK_SCREEN
    //#define DIRECT_TO_PLAY                // If defined, title screen is also the game frame.
    //#define DISABLE_HOTSPOTS              // Disable them completely. Saves tons of memory.
    #define DEACTIVATE_KEYS                 // If defined, keys are not present.
    //#define DEACTIVATE_OBJECTS            // If defined, objects are not present.
    //#define DEACTIVATE_REFILLS
    //#define ONLY_ONE_OBJECT               // If defined, only one object can be carried at a time.
    //#define OBJECT_COUNT              1   // Defines which FLAG will be used to store the object count.
    //#define OBJECTS_COLLECTABLE_IF    2   // If defined, Objs. can be collected if FLAG # == 1
    //#define DEACTIVATE_EVIL_TILE          // If defined, no killing tiles (behaviour 1) are detected.
    #define FULL_BOUNCE                     // If defined, evil tile bounces equal MAX_VX, otherwise v/2
    //#define PLAYER_BOUNCES                // If defined, collisions make player bounce
    //#define SLOW_DRAIN                    // Works with bounces. Drain is 4 times slower
    //#define PLAYER_DIZZY                  // Enable dizzy state for player
    //#define PLAYER_DIZZ_EXPR              (((rand () & 15) - 7) << 3)
    #define PLAYER_FLICKERS                 // If defined, collisions make player flicker instead.
    //#define MAP_BOTTOM_KILLS              // If defined, exiting the map bottomwise kills.
    #define WALLS_STOP_ENEMIES              // If defined, enemies react to the scenary (new: if bit 5 on!)
    //#define EVERYTHING_IS_A_WALL          // If defined, any tile <> type 0 is a wall, otherwise just 8.
    //#define COUNT_SCR_ENEMS_ON_FLAG 1     // If defined, count # of enems on screen and store in flag #
    //#define SHOW_LEVEL_ON_SCREEN          // If defined, show level # whenever we enter a new screen
    //#define CUSTOM_HIT                    // If defined, different agents take different amounts of life (needs to be refined, don't use)
    //#define CUSTOM_HIT_DEFAULT        10
    #define IS_EVIL &1                      // ==1 or &1, depending on what you need.
    //#define ONLY_VERTICAL_EVIL_TILE       // Does as it suggests.
```

In the bounding / collision box configuration, Ninjajar! uses the small 8x8 bottom-centered bounding box to collide with the background (`BOUNDING_BOX_8_BOTTOM`) and a centered 8x8 collision box (`SMALL_COLLISION`).

Most levels have open air rooms, so `PLAYER_CHECK_MAP_BOUNDARIES` is needed. Also there's no keys/bolts, so `DEACTIVATE_KEYS` is on. `FULL_BOUNCE` makes the game more playable in the swimming sections. Also, the player must flicker when respawn after being hit (`PLAYER_FLICKERS`). 

All enemy trajectories should be affected by non walkable background tiles, hence `WALLS_STOP_ENEMIES`.

To finish with, `IS_EVIL` has to be configured to `&1` as that was the way killing metatiles were detected in MK2 when Ninjajar! was developed.

### Enemy engine

We need patrollers, that is, good ol' linear enemies. 

```c
    #define ENABLE_PATROLLERS               // Yeah, you can now deactivate good ol' patrollers...
    //#define PATROLLERS_HIT            9   // If defined, patrollers take THIS life, otherwise 1
```

We also need fanties of the *homing* type, which will stay dormant until you approach them (`FANTIES_SIGHT_DISTANCE`). They must die if the collide the player (who, of course, will die too): `FANTILES_KILL_ON_TOUCH`. They are also pretty fast. They should die after one hit.

```c
    #define ENABLE_FANTIES                  // If defined, add code for flying enemies.
    #define FANTIES_SIGHT_DISTANCE  96      // If defined, used in our type 6 enemies.
    #define FANTIES_KILL_ON_TOUCH           // If defined, enemy also dies when collision happens
    //#define FANTIES_NUMB_ON_FLAG  31      // If defined, flag = 0 makes them not move.
    #define FANTIES_MAX_V           256     // Flying enemies max speed (also for custom type 6 if you want)
    #define FANTIES_A               16      // Flying enemies acceleration.
    #define FANTIES_LIFE_GAUGE      1       // Amount of shots needed to kill flying enemies.
    //#define FANTIES_HIT           12      // If defined, fanties take THIS life, otherwise 1 
```

We need some enemies to throw cocos - those were the old "type 8" enemies. This is now encoded as linear enemies with the "shooting" flag enabled.  I've replicated the values from the original (the constants had different names):

```c
    #define MAX_COCOS           3           // Max # of cocos.
    // #define COCOS_COLLIDE                // Cocos will die with beh 8

    #define ENABLE_SHOOTERS                 // Activate this if your raise bit 4 in any enemies.

    #define SHOOTER_SHOOT_FREQ      63      // Shoot frequency (2^n-1)
    #define SHOOTER_SAFE_DISTANCE   64      // if closer won't shoot
    #define SHOOTER_FIRE_ONE                // If defined, just fire one coco per enemy
    #define ENEMY_SHOOT_SPEED       6       // pixels per frame
```

The original Ninjajar! had a special enemy type called "clouds" (type 9). I left them out when I changed the enemy format, so a custom modification will be needed. We'll discuss that later.

### Extra engine configuration

```c 
    //#define USE_TWO_BUTTONS               // Alternate keyboard scheme for two-buttons games
    #define USE_HOTSPOTS_TYPE_3             // Alternate logic for recharges.
    #define TILE_GET                22      // If defined, player can "get" tile #
    #define TILE_GET_REPLACE        0       // Replace tile got with tile #
    #define TILE_GET_FLAG           1       // And this increments flag #
    //#define TILE_GET_SCRIPT               // Run PLAYER_GETS_COIN when player gets tile TILE_GET
    #define DIE_AND_RESPAWN                 // If defined, dying = respawn on latest safe.
    //#define DISABLE_AUTO_SAFE_SPOT        // If defined, you have to define the save spot via scripting
    //#define REENTER_ON_DEATH              // Reenter screen when killed, for 1-screen arcades.
    //#define PLAYER_STEP_SOUND             // Sound while walking. No effect in the BOOTEE engine.
    //#define DISABLE_PLATFORMS             // If defined, disable platforms (all engines)
    #define ENABLE_CONVEYORS                // Enable conveyors (all engines)
```

This game uses refills placed in the `.ene` files, so `USE_HOTSPOTS_TYPE_3`. You can get coins, wich are metatile #22 in all metatilesets, so `TILE_GET` equals 22. It should be replaced with metatile 0: `TILE_GET_REPLACE` defined as 0, and increment flag 1 (`TILE_GET_FLAG`) so they can be counted.

`DIE_AND_RESPAWN` makes the player respawn from the latest safe spot after being killed. This game also uses conveyors, so `ENABLE_CONVEYORS` is on.

### The hitter

Ninjajar!'s was the first hitter, so it had nothing to configure. We have some stuff to configure now, though:

```c
    #define PLAYER_CAN_PUNCH                // Player can punch. (Ninjajar! (side))
    //#define PLAYER_HAZ_SWORD              // Player haz sword. (Espadewr (side))
    //#define PLAYER_HAZ_WHIP               // Player haz whip. (imanol (side) / Key to time (top-down))

    //#define PLAYER_HITTER_INV     46      // If defined, player can use hitter only if item # is selected!
    #define PLAYER_HITTER_STRENGTH  1       // Hitter strength. 0 = just makes monsters turn around.
    #define HITTER_BREAKS_WALLS             // If defined, hitter breaks breakable walls.
```

Our hitter must kill enemies (so `PLAYER_HITTER_STRENGTH` must equal 1) and also break breakable tiles: `HITTER_BREAK_WALLS`.

### Breakable walls

To make rocks destructible, the `BREAKABLE_WALLS_SIMPLE` engine must be enabled and configured:

```c 
    #define BREAKABLE_WALLS_SIMPLE

    #define BREAKABLE_ANIM                  // If defined, breakable tiles look "broken"
    #define BREAKABLE_TILE          31      // "broken tile"
    #define MAX_BREAKABLE           3       // Max tiles showing "breaking"
    #define MAX_BREAKABLE_FRAMES    4       // Frames to show "breaking"
```

`BREAKABLE_ANIM` is on, which means that rocks won't disappear right away. Instead, a "broken tile" (number in `BREAKABLE_TILE`) is shown for some (`MAX_BREAKABLE_FRAMES`) frames. Three simultaneous breaking tiles are enough for this game (`MAX_BREAKABLE`). There's no way the player can move so fast so it destroys more than 3 tiles in less than 4 frames. The optimal value has to be configured via trial and error. For example, our NES game **Nin Nin** runs at 50fps so `MAX_BREAKABLE_FRAMES` is higher and `MAX_BREAKABLE` had to be raised to 8.

### Breakable rocks spawn coins

This is achieved enabling and configuring `BREAKABLE_TILE_GET`:

```c
    #define BREAKABLE_TILE_GET      12      // If defined, tile "TILE GET" may appear when breaking tile #
    #define BREAKABLE_TILE_FREQ     3       // Breakable tile frequency (AND)
    #define BREAKABLE_TILE_FREQ_T   2       // <= this value = true.
```

`BREAKABLE_TILE_GET` enables this engine and also define which tile number will spawn a `TILE_GET` when broken. In our case is number 12 which, in all metatilesets, is the "box with a star" tile. That way we may have several breakable tiles (all kinds of rocks) but only have the special boxes to spawn coins.

Coins are spawned when this formula evaluates to true:

```c
    ((rand () & BREAKABLE_TILE_FREQ) < BREAKABLE_TILE_FREQ_T)
```

This gives us a 50% chance (rand () & 3 makes the random number be either 0, 1, 2 or 3), but as the random number generator is a bit crap to be fast, this works better that simply calculating `rand () & 1`...

### Scripting engine (msc)

```c
    #define ACTIVATE_SCRIPTING          // Activates msc3 scripting and flag related stuff.
    #define SCRIPT_PAGE     7           // Which RAM page holds the script (128)
    //#define CLEAR_FLAGS               // If defined, clear flags each level/beginning.
    #define SCRIPTING_DOWN              // Use DOWN as the action key.
    //#define SCRIPTING_KEY_M           // Use M as the action key instead.
    //#define SCRIPTING_KEY_FIRE        // User FIRE as the action key instead.
    #define ENABLE_EXTERN_CODE          // Enables custom code to be run from the script using EXTERN n
    //#define EXTERN_E                  // Uncomment this as well if you use EXTERN_E in your script
    #define ENABLE_FIRE_ZONE            // Allows to define a zone which auto-triggers "FIRE"
```

Ninjajar! makes heavy use of the scripting engine. Scripts reside at the beginning of RAM 7 (as we have discussed earlier). The action key is DOWN. Also we need to `ENABLE_FIRE_ZONE` so we can define a zone on screen which will trigger the `PRESS_FIRE_ON` sections when the player touches it. We also need to use `EXTERN`to show text boxes (we'll discuss this later on).

### Lava

Lava was introduced for Ninjajar! and I doubt it works anywhere else, but thankfully I did not remove it as I did with clouds.

Just use the default configuration:

```c
    #define ENABLE_LAVA
    #define LAVA_FLAG           30
    #define LAVA_PERIOD         7
    #define LAVA_X1             2
    #define LAVA_X2             28          // LAVA_X1 <= x < LAVA_X2
    #define LAVA_T              18
```

### Side view

Just enable the jumping and swimming engines, and activate `SWITCHABLE_ENGINES` so they can be switched as per level basis:

```c
    #define PLAYER_HAS_JUMP                 // If defined, player is able to jump. EVEN IN TOP-DOWN!
    //#define PLAYER_BOOTEE                 // Always jumping engine. Don't forget to disable "HAS_JUMP" and "HAS_JETPAC"!!!
    //#define PLAYER_BOUNCE_WITH_WALLS      // Bounce when hitting a wall. Only really useful in MOGGY_STYLE mode
    //#define PLAYER_CUMULATIVE_JUMP        // Keep pressing JUMP to JUMP higher in several bounces
    //#define PLAYER_BOOST_WHEN_GOING_UP    // Boost pvy when jumping to the screen above.

    //#define PLAYER_HAS_JETPAC             // If defined, player can thrust a vertical jetpac
    //#define JETPAC_DEPLETES           4   // If defined, jetpac depletes each # frames.
    //#define JETPAC_FUEL_INITIAL       25  // needed by "JETPAC_DEPLETES", initial fuel value.
    //#define JETPAC_FUEL_MAX           25  // needed by "JETPAC_DEPLETES" & "JETPAC_REFILLS", max fuel value.
    //#define JETPAC_AUTO_REFILLS       2   // If defined, jetpac refills each # frames when not in use.
    //#define JETPAC_REFILLS                // If defined, type 6 hotspots are refills.
    //#define JETPAC_FUEL_REFILL        25  // needed by "JETPAC_REFILLS"

    // Stepping over enemies...
    //#define PLAYER_KILLS_ENEMIES          // If defined, stepping on enemies kills them
    //#define PLAYER_CAN_KILL_FLAG      1   // If defined, player can only kill when flag # is "1"
    //#define PLAYER_MIN_KILLABLE       3   // Only kill enemies with id >= PLAYER_MIN_KILLABLE

    #define PLAYER_HAS_SWIM                 // If defined, player is able to swim
    #define SWITCHABLE_ENGINES              // WIP! VERY, VERY, VERY WIP! See Sir Ababol DX or Ninjajar!
```

### Screen configuration

Note how stuff you don't want to show are defined with their X coordinate = 99:

```c
    #define VIEWPORT_X              1       //
    #define VIEWPORT_Y              2       // Viewport character coordinates
    #define LIFE_X                  3       //
    #define LIFE_Y                  0       // Life gauge counter character coordinates
    #define OBJECTS_X               99      //
    #define OBJECTS_Y               99      // Objects counter character coordinates
    //#define REVERSE_OBJECTS_COUNT         // If defined, from MAX to 0
    #define OBJECTS_ICON_X          99      //
    #define OBJECTS_ICON_Y          99      // Objects icon character coordinates (use with ONLY_ONE_OBJECT)
    #define KEYS_X                  99      //
    #define KEYS_Y                  99      // Keys counter character coordinates
    #define KILLED_X                99      //
    #define KILLED_Y                99      // Kills counter character coordinates
    #define AMMO_X                  99      //
    #define AMMO_Y                  99      // Ammo counter character coordinates
    #define TIMER_X                 99      //
    #define TIMER_Y                 99      // Timer counter coordinates
    #define FLAG_X                  29      //
    #define FLAG_Y                  0       // Custom flag character coordinates
    #define PLAYER_SHOW_FLAG        1       // If defined, show flag #
    #define FUEL_X                  99      //
    #define FUEL_Y                  99      // Fuel counter in bla bla bla

    #define KILL_SLOWLY_GAUGE_X     99      // For evil zone counters
    #define KILL_SLOWLY_GAUGE_Y     99      //
```

This is the case of collectable objects (onigiris). You don't want to show them on the hud even if they are enabled, so `OBJECTS_X` should equal 99.

`PLAYER_SHOW_FLAG` equals 1 so flag #1 is shown on the hud: the amount of coins. Note that this is safe: if the value of `PLAYER_SHOW_FLAG` and the value of `TILE_GET_FLAG` are the same, you can get a maximum of 99 `TILE_GET`s.

### Graphic and more misc. stuff

```c
    //#define USE_AUTO_SHADOWS              // Automatic shadows made of darker attributes
    //#define USE_AUTO_TILE_SHADOWS         // Automatic shadows using specially defined tiles 32-47.
    //#define ENABLE_SUBTILESETS            // Adds subtileset loader.
    //#define MAP_ATTRIBUTES                // Enables multi-purpose map attributes array (only in multi-level games as of 0.90)
    //#define NO_MASKS                      // Sprites are rendered using OR instead of masks.
    //#define PLAYER_ALTERNATE_ANIMATION    // If defined, animation is 1,2,3,1,2,3...
    #define MASKED_BULLETS                  // If needed
    //#define ENABLE_TILANIMS               // If defined, animated tiles are enabled and will alternate between t and t+1
    //#define IS_TILANIM(t)     ((t)==20)   // Condition to detect if a tile is animated                                        
    #define PAUSE_ABORT                     // Add h=PAUSE, y=ABORT
    //#define GET_X_MORE                    // Shows "get X more" when getting an object
    //#define NO_ALT_TILE                   // No alternate automatic tile 19 for tile 0.
    //#define TWO_SETS                      // If defined, use two 16 sets in one (just ask)
    //#define TWO_SETS_SEL (n_pant>8?32:0)  // This expresion must equal 0 for set 1 to be used, or 32 for set 2 to be used (just ask)
    //#define TWO_SETS_MAPPED               // Two sets, but which set to use is mapped after map data (1 byte per screen)
    //#define ENABLE_LEVEL_NAMES            // Give a name for each level/screen in engine/levelnames.h
    //#define ENABLE_EXTRA_PRINTS           // Configure extra tile prints for some screens in engine/extraprints.h
```

All off but `MASKED_BULLETS` so cocos show nicely against the background, and `PAUSE_ABORT`.

### Player movement configuration

Lifted directly from the original Ninjajar!.

```c
    // IV.1. Vertical movement. Only for side-view.

    #define PLAYER_FALL_VY_MAX      512     // Max falling speed (512/64 = 8 pixels/frame)
    #define PLAYER_G                48      // Gravity acceleration (32/64 = 0.5 pixels/frame^2)

    #define PLAYER_JMP_VY_INITIAL   96      // Initial junp velocity (64/64 = 1 pixel/frame)
    #define PLAYER_JMP_VY_MAX       312     // Max jump velocity (320/64 = 5 pixels/frame)
    #define PLAYER_JMP_VY_INCR      48      // acceleration while JUMP is pressed (48/64 = 0.75 pixels/frame^2)

    //#define PLAYER_JETPAC_VY_INCR 32      // Vertical jetpac gauge
    //#define PLAYER_JETPAC_VY_MAX  256     // Max vertical jetpac speed

    // IV.2. Horizontal (side view) or general (top view) movement.

    #define PLAYER_VX_MAX           256     // Max velocity (192/64 = 3 pixels/frame)
    #define PLAYER_AX               64      // Acceleration (24/64 = 0,375 pixels/frame^2)
    #define PLAYER_RX               96      // Friction (32/64 = 0,5 pixels/frame^2)

    //#define PLAYER_AX_ALT         8       // Acceleration (alternate) when stepping on tile w/beh. 64
    //#define PLAYER_RX_ALT         8       // Friction (alternate) when stepping on tile w/beh. 64

    #define PLAYER_V_BOUNCE         320     // Bouncing speed

    // IV.3. Swimming

    #define PLAYER_MAX_VSWIM        128
    #define PLAYER_ASWIM            32
```

## Sound effects

From examining the source code I've extracted this list of sounds Ninjajar! uses:

```
    0   Z (items)
    1   pause / start / 
    2   jump
    3   hotspot (collectable / key / ammo / time) / block / lock / broken / coco
    4   shoot
    5   hotspot (refill) / tile get
    6   enemy hit / stepped on / shot
    7   enemy dead / broken
    8   punch
```

Just edited the `SFX_?` constants in `definitions.h`.

## Text box renderer and text unstuffer

I found *text unstuffer* funny, sorry. If enabled, the scripting can fire up external code written in C via the `EXTERN N` command. In Ninjajar! it is used to display text. The original driver is there somehow but some stuff has changed. I will port the original `extern.h` and then make some adjustements (code enhancements). Just check out the results.

The text is read from RAM 6, decoded into a buffer, then displayed in a nice albeit simple text box. Just that.

## Test build

At this point I'll try and build the whole thing to correct stuff before I go on. That needs to complete the `compile.bat` file.

```c
    echo ### COMPILING ###
    zcc +zx -vn -m mk2.c -o work\%game%.bin -lsplib2_mk2 -zorg=24200
```

### The loader

The thing is, this game uses RAM7 and this page is used a some sort of scratchpad by the ROM if IM1 is on, so we can't use a BASIC loader. Thankfully, thanks to some explanations by the almighty Antonio Villena, I've crafted a little loader in assembly which loads every asset (aplib compressed) and decompresses everything in place.

This may bit a bit advanced as the original `loaderzx.asm-orig` file has to be patched in real time with the actual sizes of the binaries. I hate doing things by hand, that's why I use `imanol.exe`, which performs simple textual substitutions. If you don't get this but you are interested in assembly loaders you can drop me a line. You should know that [I love coffee](https://ko-fi.com/I2I0JUJ9).

The loader starts with a bit of magic by A.Villena that, to be honest, I don't really understand, but makes this code auto-executable:

```
        org $5ccb
        ld  sp, 24199
        di
        db  $de, $c0, $37, $0e, $8f, $39, $96 ;OVER USR 7 ($5ccb)
```

First thing is loading the screen to 16384. We'll be using the ROM loading routine on a headerless block, so we must know the exact length as we have to pass it to the routine in this case it is 6912.

```
    ; load screen
        scf
        ld  a, $ff
        ld  ix, $4000
        ld  de, 6912
        call $0556
        di
```

The ROM loading routine which resides in $0556 needs the loading address in IX and the number of bytes to oad in DE, and the carry flag set. It also enables interrupts at the end, so a DI is needed right after. 

Next block is the compressed RAM1. To load the block, we page in RAM1 and then load the block to $C000 (where RAM1 is mapped once it is paged in). DE should contain the block length, but as I said before, I like to automate things, so for this parameter I'll use a constant and later on I'll inject the actual length of the bin file using my utility `imanol.exe`.

```
    ; RAM1
        ld  a, $11      ; ROM 1, RAM 1
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram1_length%%%
        call $0556
        di
```

Same for the remaining RAM blocks:

```
    ; RAM3
        ld  a, $13      ; ROM 1, RAM 3
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram3_length%%%
        call $0556
        di

    ; RAM4
        ld  a, $14      ; ROM 1, RAM 4
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram4_length%%%
        call $0556
        di

    ; RAM6
        ld  a, $16      ; ROM 1, RAM 6
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram6_length%%%
        call $0556
        di

    ; RAM7
        ld  a, $17      ; ROM 1, RAM 7
        ld  bc, $7ffd
        out (C), a

        scf
        ld  a, $ff
        ld  ix, $C000
        ld  de, %%%ram7_length%%%
        call $0556
        di
```

The last block is the main binary. Same as before, but load to 24200. Oh, and dont' forget to put RAM0 back in!:

```
; Main binary
    ld  a, $10      ; ROM 1, RAM 0
    ld  bc, $7ffd
    out (C), a

    scf
    ld  a, $ff
    ld  ix, 24200
    ld  de, %%%mb_length%%%
    call $0556
    di
```

And now everything is in place, run the game:

```
    ; run game!
    jp 24200
```

What follows in the `loaderzx.asm-orig` file is the blackout routine which puts the screen black.

Now is when we put `imanol.exe` to use. This simple command line tool just takes a text file, makes some substitutions, and writes a new file with the changes. Substitutions are passed as parameters in the format `constant=expression`, where expression may be a literal, a file length, or a simple aritmetic expression (addition and substraction).

Those are the constants we have to substitute:

```
    ram1_length
    ram3_length
    ram4_length
    ram6_length
    ram7_length
    mb_length
```

And this is how `imanol.exe` is called (I've broken the command line into several lines using `^` for clarity - this is a feature of Windows' .cmd and .bat files):

```
    ..\utils\imanol.exe ^
        in=loader\loaderzx.asm-orig ^
        out=loader\loader.asm ^
        ram1_length=?work\RAM1.bin ^
        ram3_length=?work\RAM3.bin ^
        ram4_length=?work\RAM4.bin ^
        ram6_length=?work\RAM6.bin ^
        ram7_length=?work\RAM7.bin ^
        mb_length=?work\%game%.bin
```

If the value of a substitution begins with `?` that means "expression". A file name here equals its file length.

Next step is using `pasmo.exe` to assemble the loader:

```
    ..\utils\pasmo.exe loader\loader.asm work\loader.bin loader.txt
```

And now we have all the pieces of the puzzle, we have to build the tape using Antonio Villena's `GenTape.exe`:

```
    ..\..\..\src\utils\GenTape.exe %game%.tap ^
        basic 'NINJAJAR!' 10 work\loader.bin ^
        data                ..\bin\loading.scr ^
        data                 work\RAM1.bin ^
        data                 work\RAM3.bin ^
        data                 work\RAM4.bin ^
        data                 work\RAM6.bin ^
        data                 work\RAM7.bin ^
        data                 work\%game%.bin
```

And now - fingers crossed :D

## Building

Run these commands to completely rebuild Ninjajar! v2

```
    $ setenv.bat
    $ build_fixed.bat
    $ build_levels.bat
    $ compile.bat
```

