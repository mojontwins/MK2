# Journey to the Centre of the Nose MK2 version
### Ported to MK2 as an excercise, illustration and example

This game was created with the first revision of the original version of MK1, so it's a rather simple game. My intention when porting it is adding map RLE compression to the engine. RLE compression for maps was developed for our NES engines and divides each byte in "tile number" and "run length". There are three flavours: RLE44, RLE53 and RLE62, with 4 bits for tile number / 4 bits for run length (16 tiles max., runs of 16 identic tiles max.), 5 bits for tile number / 3 bits for run length (32 tiles max., runs of 8 identic tiles max.) and 6 bits for tile number / 2 bits for run length (64 tiles max., runs of 4 identic tiles max.), respectively.

Choosing which combination of tile count / max. run length depends on the project. Classic unpacked maps which allowed for 48 different tiles are forced to use RLE62, but packed maps with 16 tiles plus decorations may benefit greatly from the RLE53 version (as long as you can keep the total tile count under 32). For **Journey to the Centre of the Nose** we'll be choosing the RLE44 which should give the best results as this game uses just 16 different tiles with no decorations.

This game also has two different levels featuring different tilesets which will demonstrate the `level.h` 48K level manager.

This document is a walk through the process of taking the base project and building a new game.

## 48K multilevel games

48K Multilevel games are managed using `levels.h`. This provides infrastructures to define which map, tileset, enems set, and level values to use for each level.

## Copy the base project

I just copied the base project to a new folder and changed the name of the game. Edit `compile.bat`

1. Set `SET game=journey` at the top. 
2. Also change the name of the loader in the tap file towards the end, at line 162:

```
    ..\utils\bas2tap -a10 -sJOURNEY loader\loader.bas work\loader.tap
```

## Prepare main assets: graphics

Next is replacing all the graphics assets in the `gfx` folder:

- Ending screen: `ending.png`
- Loading screen: `loading.png`
- Title / frame: `title.png`
- Font: `font.png`
- Spriteset: `sprites.png`
- Tileset for level 1: `tileset0.png`
- Tileset for level 2: `tileset1.png`

Now let's modify `compile.bat` to properly convert *and compress* both tilesets. Notice how we generate the font and the metatilesets separately, as we will be compressing just the tilesets to save space.

Original (line 42):

```
	echo ### MAKING TILESET ###
	..\utils\ts2bin.exe ..\gfx\font.png ..\gfx\work.png ..\bin\ts.bin forcezero
```

Change for:

```
	echo ### MAKING TILESET ###
	..\utils\ts2bin.exe ..\gfx\font.png notiles ..\bin\font.bin forcezero
	..\utils\ts2bin.exe nofont ..\gfx\tileset0.png ..\bin\level0.ts.bin forcezero
	..\utils\ts2bin.exe nofont ..\gfx\tileset1.png ..\bin\level1.ts.bin forcezero

	echo ### COMPRESSING METATILESETS ###
	..\utils\apack.exe ..\bin\ts0.bin ..\bin\level0.ts.c.bin > nul
	..\utils\apack.exe ..\bin\ts1.bin ..\bin\level1.ts.c.bin > nul
```

## Prepare main assets: map

This is a matter of putting the original map files `level0.fmp` and `level1.fmp`, then generating `level0.map` and `level1.map`. Finally, `compile.bat` should be modified to replace the `map2bin.exe` converter to `map2rlebin.exe` with the right parameters. Both maps are 4x7 screens:

```
..\utils\map2rlebin.exe rle=44 in=..\map\level0.map out=..\bin\level0 size=4,7 tlock=15
..\utils\map2rlebin.exe rle=44 in=..\map\level1.map out=..\bin\level1 size=4,7 tlock=15
```

Now run those command lines and write down the size of the uncompressed binaries, as we'll have to make room in `levels.h` for the biggest. In this case, generated maps are 1577 and 875 bytes, so we'll have to reserve 1577 bytes.

Each call to `map2rlebin.exe` generates two binaries: one with the map data (<name>.map.bin) and another with the locks data (<name>.locks.bin). We'll have to compress all those assets to include them from `levels.h`:

```
	echo ### COMPRESSING MAPS ###
	..\..\..\src\utils\apack.exe ..\bin\level0.map.bin ..\bin\level0.map.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level1.map.bin ..\bin\level1.map.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level0.locks.bin ..\bin\level0.locks.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level1.locks.bin ..\bin\level1.locks.c.bin > nul
```

## Prepare main assets: enems

This is a bit trickier. The original .ene files in this game use the old '2 bytes per hotspot' format, which will work fine with the mk2 converters, but this game uses the old enemy type format.

1. I've copied the original `.ene` files as `orig0.ene` and `orig1.ene`.
2. I've copied `level0.map`, `lavel1.map`, `tileset0.png` and `tileset1.png` to `enems`, then I've modified the original `orig0.ene` and `orig1.ene` header with an hex editor.
3. The enemy type format is solved by the converter `enemsupdr.exe`:

```
    $ enemsupdr.exe orig1.ene level0.ene
    $ enemsupdr.exe orig0.ene level1.ene
```

3. Opening the resulting `level0.ene` and `level1.ene` with **ponedor** shows the results. Also notice the `2b` which means that hotspots use 2 bytes (legacy format) which is what the converters expect.

Once more, we'll have to modify `compile.bat` to convert *and compress* both `.ene` files:

```
	echo ### MAKING ENEMS ###
	..\..\..\src\utils\ene2bin.exe 4 7 1 ..\enems\level0.ene ..\bin\level0.enems.bin ..\bin\level0.hotspots.bin
	..\..\..\src\utils\ene2bin.exe 4 7 1 ..\enems\level1.ene ..\bin\level1.enems.bin ..\bin\level1.hotspots.bin

	echo ### COMPRESSING ENEMS ###
	..\..\..\src\utils\apack.exe ..\bin\level0.enems.bin ..\bin\level0.enems.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level1.enems.bin ..\bin\level1.enems.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level0.hotspots.bin ..\bin\level0.hotspots.c.bin > nul
	..\..\..\src\utils\apack.exe ..\bin\level1.hotspots.bin ..\bin\level1.hotspots.c.bin > nul
```

## Prepare main assets: metatile behaviours

For single level games, those are defined directly in an array in `config.h`, but for multi-level games they should be included as compressed binaries in `levels.h`, so we have to prepare them.

First of all we create two text files with the metatile behaviours for each level:

1. `gfx/level0.behs.txt`:

```
	0, 0, 0, 8, 8, 8, 0, 1, 1, 8, 8, 8, 8, 8, 0, 10,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
```

2. `gfx/level0.behs.txt`:

```
	0, 0, 0, 8, 8, 8, 0, 1, 1, 8, 8, 4, 4, 8, 0, 10,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
```

The modify once more `compile.bat` to convert and compress them:

```
```

## Prepare main assets: music

Just replace the 48K beeper tune in `sound/music.h`.

## No script

There's no script for this game, so comment out all related lines in `compile.bat`:

```
	rem echo ### MAKING SCRIPT ###
	rem cd ..\script
	rem ..\utils\msc3_mk2_1.exe script.spt 20

	rem If scripts and texts are going to share the same RAM page, use this line
	rem (for 128K games)
	rem This calculates an offset for the scripts binary automaticly.
	rem ..\utils\sizeof.exe ..\bin\texts.bin 49152 "#define SCRIPT_INIT" >> msc-config.h

	rem Otherwise use this one:
	rem echo #define SCRIPT_INIT 49152 >> msc-config.h

	rem copy msc.h ..\dev\my
	rem copy msc-config.h ..\dev\my
	rem copy scripts.bin ..\bin\preload7.bin
	rem copy scripts.bin ..\bin\
	rem cd ..\dev
```

## Configure

As mentioned, the original game is a MK1 v2.X game, so everything we need should be there. So let's open both `config.h` side to side and let's try to replicate the main behaviour. I'll drop a line on every directive I replace:

### Initial configuration section

```c
	#define COMPRESSED_LEVELS 				// use levels.h/levels128.h instead of mapa.h and enems.h (!)
	//#define EXTENDED_LEVELS				// Experimental!
	//#define LEVEL_SEQUENCE				// Experimental!
	//#define SCRIPTED_GAME_ENDING			// Game ending is triggered from the script
	//#define SIMPLE_LEVEL_MANAGER			// Custom level manager "simple" <- UNFINISHED. DON'T USE!

	#define MIN_FAPS_PER_FRAME 		2		// Experimental. Adds an ISR even in 48K mode.
											// Limits the max. speed to 50/N fps.
```

### General configuration section

Pretty straightforward:

```c
	#define MAP_W					4		//
	#define MAP_H					7		// Map dimmensions in screens
	//#define ENABLE_CUSTOM_CONNECTIONS 	// Custom connections array. MAP_W/MAP_H just define how many screens
	//#define SCR_INI				1		//  Initial screen
	//#define PLAYER_INI_X			5		//
	//#define PLAYER_INI_Y			1		// Initial tile coordinates
	//#define SCR_END 				99		// Last screen. 99 = deactivated.
	//#define PLAYER_END_X			99		//
	//#define PLAYER_END_Y			99		// Player tile coordinates to finish game
	//#define PLAYER_MAX_OBJECTS	99		// Objects to get to finish game
	#define PLAYER_LIFE 			9		// Max and starting life gauge.
	//#define DONT_LIMIT_LIFE				// If defined, no upper limit to life gauge.
	#define PLAYER_REFILL			1		// Life recharge
	#define MAX_LEVELS				2		// # of compressed levels
	#define REFILL_ME 						// If defined, refill player on each level
	#define WIN_CONDITION			0		// 0 = objects collected, 1 = screen 'N', 2 = scripting, 3 = SIM
	//#define EXTRA_SPRITES 		2 		// For 128K games -> # of extra sprite faces to make room for.
```

Note that `MAP_W` and `MAP_H` are used to dimension the biggest map in the game. In this case, both maps are 4x7. Also, `SCR_INI`, `PLAYER_INI_X` and `PLAYER_INI_Y` are ignored for multi-level games. We'll define all these values when customizing `levels.h`.

We define `MAX_LEVELS` as 2 so the ending is shown after two levels. Also, `REFILL_ME` will refill the player life count to `PLAYER_LIFE` before each level. `WIN_CONDITION` should be 0, which means *all collectable objects collected*.

### Engine type section

Collision:

```c
	#define BOUNDING_BOX_8_BOTTOM			// 8x8 aligned to bottom center in 16x16
	//#define BOUNDING_BOX_8_CENTERED		// 8x8 aligned to center in 16x16
	//#define BOUNDING_BOX_TINY_BOTTOM		// 8x2 aligned to bottom center in 16x16
	//#define SMALL_COLLISION 				// 8x8 centered collision instead of 12x12
```

And engine configuration:

```c 
	#define PLAYER_CHECK_MAP_BOUNDARIES		// If defined, you can't exit the map.
	//#define PLAYER_CYCLIC_MAP				// Cyclic, endless map in all directions.
	//#define PLAYER_CANNOT_FLICK_SCREEN	// If defined, automatic screen flicking is disabled.
	//#define PLAYER_WRAP_AROUND			// If defined, wrap-around. Needs PLAYER_CANNOT_FLICK_SCREEN
	#define DIRECT_TO_PLAY					// If defined, title screen is also the game frame.
	//#define DISABLE_HOTSPOTS				// Disable them completely. Saves tons of memory.
	//#define DEACTIVATE_KEYS 				// If defined, keys are not present.
	//#define DEACTIVATE_OBJECTS			// If defined, objects are not present.
	//#define DEACTIVATE_REFILLS
	//#define ONLY_ONE_OBJECT				// If defined, only one object can be carried at a time.
	//#define OBJECT_COUNT				1	// Defines which FLAG will be used to store the object count.
	//#define OBJECTS_COLLECTABLE_IF	2 	// If defined, Objs. can be collected if FLAG # == 1
	//#define DEACTIVATE_EVIL_TILE			// If defined, no killing tiles (behaviour 1) are detected.
	//#define FULL_BOUNCE 					// If defined, evil tile bounces equal MAX_VX, otherwise v/2
	//#define PLAYER_BOUNCES				// If defined, collisions make player bounce
	//#define SLOW_DRAIN					// Works with bounces. Drain is 4 times slower
	//#define PLAYER_DIZZY 					// Enable dizzy state for player
	//#define PLAYER_DIZZ_EXPR 				(((rand () & 15) - 7) << 3)
	#define PLAYER_FLICKERS 				// If defined, collisions make player flicker instead.
	//#define MAP_BOTTOM_KILLS				// If defined, exiting the map bottomwise kills.
	//#define WALLS_STOP_ENEMIES			// If defined, enemies react to the scenary (new: if bit 5 on!)
	//#define EVERYTHING_IS_A_WALL			// If defined, any tile <> type 0 is a wall, otherwise just 8.
	//#define COUNT_SCR_ENEMS_ON_FLAG 1		// If defined, count # of enems on screen and store in flag #
	//#define SHOW_LEVEL_ON_SCREEN			// If defined, show level # whenever we enter a new screen
	//#define CUSTOM_HIT					// If defined, different agents take different amounts of life (needs to be refined, don't use)
	//#define CUSTOM_HIT_DEFAULT		10
	#define IS_EVIL ==1 					// ==1 or &1, depending on what you need.
	#define ONLY_VERTICAL_EVIL_TILE			// Does as it suggests.
```

Very few are on. This is a rather simple game.

### Enemy types

Everything off, but patrollers:

```c 
	#define ENABLE_PATROLLERS				// Yeah, you can now deactivate good ol' patrollers...
```

### Scripting

Everything OFF

```c
	// Scripting
	// ---------
	//#define ACTIVATE_SCRIPTING		// Activates msc3 scripting and flag related stuff.
	//#define SCRIPT_PAGE		7		// Which RAM page holds the script (128)
	//#define CLEAR_FLAGS				// If defined, clear flags each level/beginning.
	//#define SCRIPTING_DOWN			// Use DOWN as the action key.
	//#define SCRIPTING_KEY_M			// Use M as the action key instead.
	//#define SCRIPTING_KEY_FIRE		// User FIRE as the action key instead.
	//#define ENABLE_EXTERN_CODE		// Enables custom code to be run from the script using EXTERN n
	//#define EXTERN_E					// Uncomment this as well if you use EXTERN_E in your script
	//#define ENABLE_FIRE_ZONE			// Allows to define a zone which auto-triggers "FIRE"
```

### Line of text

Everything off.

### Side view

Activate jumping (just that)

```c
	#define PLAYER_HAS_JUMP 				// If defined, player is able to jump. EVEN IN TOP-DOWN!
```

### Screen configuration

```c
	#define VIEWPORT_X				1		//
	#define VIEWPORT_Y				2		// Viewport character coordinates
	#define LIFE_X					6 		//
	#define LIFE_Y					0		// Life gauge counter character coordinates
	#define OBJECTS_X				17		//
	#define OBJECTS_Y				0		// Objects counter character coordinates
	#define OBJECTS_ICON_X			99		//
	#define OBJECTS_ICON_Y			99		// Objects icon character coordinates (use with ONLY_ONE_OBJECT)
	#define KEYS_X					29		//
	#define KEYS_Y					0		// Keys counter character coordinates
	#define KILLED_X				99		//
	#define KILLED_Y				99		// Kills counter character coordinates
	//#define PLAYER_SHOW_KILLS 			// If defined, show kill counter.
	#define AMMO_X					99		//
	#define AMMO_Y					99		// Ammo counter character coordinates
	#define TIMER_X 				99		//
	#define TIMER_Y 				99		// Timer counter coordinates
	//#define PLAYER_SHOW_TIMER 			// If defined, show timer counter
	#define FLAG_X					99		//
	#define FLAG_Y					99		// Custom flag character coordinates
	//#define PLAYER_SHOW_FLAG		1		// If defined, show flag #
	#define FUEL_X					99		//
	#define FUEL_Y					99		// Fuel counter in bla bla bla
	//#define PLAYER_SHOW_FUEL				// If defined, show fuel counter.

	#define KILL_SLOWLY_GAUGE_X		99		// For evil zone counters
	#define KILL_SLOWLY_GAUGE_Y		99		//
	//#define PLAYER_SHOW_KILL_SLOWLY_GAUGE	// Follow the leader.
```

### Player movement configuration

Very, very floaty:

```c
	#define PLAYER_FALL_VY_MAX		512 	// Max falling speed (512/64 = 8 pixels/frame)
	#define PLAYER_G				24		// Gravity acceleration (32/64 = 0.5 pixels/frame^2)

	#define PLAYER_JMP_VY_INITIAL	64		// Initial junp velocity (64/64 = 1 pixel/frame)
	#define PLAYER_JMP_VY_MAX		320 	// Max jump velocity (320/64 = 5 pixels/frame)
	#define PLAYER_JMP_VY_INCR		16		// acceleration while JUMP is pressed (48/64 = 0.75 pixels/frame^2)

	//#define PLAYER_JETPAC_VY_INCR	32		// Vertical jetpac gauge
	//#define PLAYER_JETPAC_VY_MAX	256 	// Max vertical jetpac speed

	// IV.2. Horizontal (side view) or general (top view) movement.

	#define PLAYER_VX_MAX			192 	// Max velocity (192/64 = 3 pixels/frame)
	#define PLAYER_AX				24		// Acceleration (24/64 = 0,375 pixels/frame^2)
	#define PLAYER_RX				16		// Friction (32/64 = 0,5 pixels/frame^2)

	//#define PLAYER_AX_ALT			8 		// Acceleration (alternate) when stepping on tile w/beh. 64
	//#define PLAYER_RX_ALT			8 		// Friction (alternate) when stepping on tile w/beh. 64

	#define PLAYER_V_BOUNCE			320		// Bouncing speed
```

## Multi-level configuration

This is where we customise `assets/levels.h`. This file has information about each level and imports the compressed binaries with each level assets. This file also provides buffers for the current level, where the engine will decompress each level assets.

`assets/levels.h` replaces `assets/enems.h`, `assets/map.h` and `assets/tileset.h` and includes `assets/sprites.h` and `assets/extrasprites.h`.

First thing we should do is make room for the map data. Our biggest map takes 1577, uncompressed. Look for this and adjust the size properly:

```c
	extern unsigned char map [0];
	#asm
		._map 
			defs 1800 		// Make room from the biggest map in the set *uncompressed*
	#endasm
```

Now you have to add an extern array for each of your compressed game assets (that is: map, bolts, enems, hotspots, behs and tileset for each level):

```c
	extern unsigned char level0_map [0];
	extern unsigned char level1_map [0];
	extern unsigned char level0_bolts [0];
	extern unsigned char level1_bolts [0];
	extern unsigned char level0_enems [0];
	extern unsigned char level1_enems [0];
	extern unsigned char level0_hotspots [0];
	extern unsigned char level1_hotspots [0];
	extern unsigned char level0_behs [0];
	extern unsigned char level1_behs [0];
	extern unsigned char level0_ts [0];
	extern unsigned char level1_ts [0];
```

And finaly you have to actually include the compressed data (note the labels are the same identifiers used in the extern arrays with a preceding underscore):

```c
	#asm
		._level0_map 
			BINARY "../bin/level0.map.c.bin"
		._level1_map
			BINARY "../bin/level1.map.c.bin"
		._level0_bolts
			BINARY "../bin/level0.locks.c.bin"
		._level1_bolts
			BINARY "../bin/level1.locks.c.bin"
		._level0_enems
			BINARY "../bin/level0.enems.c.bin"
		._level1_enems
			BINARY "../bin/level1.enems.c.bin"
		._level0_hotspots
			BINARY "../bin/level0.hotspots.c.bin"
		._level1_hotspots
			BINARY "../bin/level1.hotspots.c.bin"
		._level0_behs
			BINARY "../bin/level0.behs.c.bin"
		._level1_behs
			BINARY "../bin/level1.behs.c.bin"
		._level0_ts
			BINARY "../bin/level0.ts.c.bin"
		._level1_ts
			BINARY "../bin/level1.ts.c.bin"
	#endasm
```

## Review the build script

This is, take a look at `compile.bat` to change some stuff. For example, the number of sprites:

```
    ..\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 16
```

## Build

To build (asuming the compiler, etc. are in place):

```
    $ setenv.bat
    $ compile.bat
```

You should get `journey.tap`.
