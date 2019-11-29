# The Hobbit - Vaca's Cut MK2 version
### Ported to MK2 as an excercise, illustration and example.

This game is rather old and rather incompatible with both the released MK1 and MK2, as it was created using the abandoned 4.X branch of MK1. It featured several unique elements which I think I can replicate using MK2. This document is a walk through the process of taking the base project and building a new game.

## Copy the base project

I just copied the base project to a new folder and changed the name of the game:

1. Rename `mk2.c` to `hobbit_v2.c`.
2. Edit `compile.bat` and set `SET game=hobbit_v2` at the top. Also change the name of the loader in the tap file towards the end, at line 162:

```
	..\utils\bas2tap -a10 -sHOBBIT_V2 loader\loader.bas work\loader.tap
```

## Prepare main assets: graphics

Next is replacing all the graphics assets in the `gfx` folder:

- Ending screen: `ending.png`
- Loading screen: `loading.png`
- Title / frame: `title.png`
- Font: `font.png`
- Spriteset: `sprites.png`
- Tileset: `work.png`

## Prepare main assets: map

Replacing the map is a matter of replacing `mapa.fmp` and then exporting `mapa.map` from it using Mappy. Note how this map is 7x5 screens.

## Prepare main assets: enems

This is a bit trickier. The .ene file in this game uses the old '2 bytes per hotspot' format, while MK2's converters expect three. Also, this game uses the old enemy type format.

1. I've copied `mapa.map` and `work.png` to `enems`, then I've modified the original `hobbit.ene` header with an hex editor.
2. The 2 vs 3 bytes per hotspot is promptly solved using **ponedor**. When you open de original `hobbit.ene` file you'll notice a `2b` sign on top. Just press L so it changes to `3b`, then save and exit.
3. The enemy type format is solved by the converter `enemsupdr.exe`:

```
	$ enemsupdr.exe hobbit.ene enems.ene
```

4. Opening the resulting `enems.ene` with **ponedor** shows the results.

## Prepare main assets: music

Just replace the 48K beeper tune in `sound/music.h`.

## Configure

As mentioned, the original game is a MK1 v4.X game, which implies that some stuff is no longer there, other stuff was reimplemented, etc. So let's open both `config.h` side to side and let's try to replicate the main behaviour. I'll drop a line on every directive I replace:

### General configuration section

Pretty straightforward:

```c
	#define MAP_W					7		//
	#define MAP_H					5		// Map dimmensions in screens
	//#define ENABLE_CUSTOM_CONNECTIONS 	// Custom connections array. MAP_W/MAP_H just define how many screens
	#define SCR_INI					28		//  Initial screen
	#define PLAYER_INI_X			8		//
	#define PLAYER_INI_Y			3		// Initial tile coordinates
	//#define SCR_END 				99		// Last screen. 99 = deactivated.
	//#define PLAYER_END_X			99		//
	//#define PLAYER_END_Y			99		// Player tile coordinates to finish game
	#define PLAYER_MAX_OBJECTS		13		// Objects to get to finish game
	#define PLAYER_LIFE 			5		// Max and starting life gauge.
	//#define DONT_LIMIT_LIFE				// If defined, no upper limit to life gauge.
	#define PLAYER_REFILL			1		// Life recharge
	//#define MAX_LEVELS			1		// # of compressed levels
	//#define REFILL_ME 					// If defined, refill player on each level
	#define WIN_CONDITION			2		// 0 = objects collected, 1 = screen 'N', 2 = scripting, 3 = SIM
	//#define EXTRA_SPRITES 		2 		// For 128K games -> # of extra sprite faces to make room for.
```

### Engine type section

The original doesn't use keys, but uses objects. No killing tiles, no bouncing, but flickering. Deactivate refills as well. This game uses the dizzy state, so `PLAYER_DIZZY` should be on.

```c
	// General directives:
	// -------------------

	//#define PLAYER_CHECK_MAP_BOUNDARIES	// If defined, you can't exit the map.
	//#define PLAYER_CYCLIC_MAP				// Cyclic, endless map in all directions.
	//#define PLAYER_CANNOT_FLICK_SCREEN	// If defined, automatic screen flicking is disabled.
	//#define PLAYER_WRAP_AROUND			// If defined, wrap-around. Needs PLAYER_CANNOT_FLICK_SCREEN
	#define DIRECT_TO_PLAY					// If defined, title screen is also the game frame.
	//#define DISABLE_HOTSPOTS				// Disable them completely. Saves tons of memory.
	#define DEACTIVATE_KEYS 				// If defined, keys are not present.
	//#define DEACTIVATE_OBJECTS			// If defined, objects are not present.
	#define DEACTIVATE_REFILLS
	//#define ONLY_ONE_OBJECT				// If defined, only one object can be carried at a time.
	#define OBJECT_COUNT			3		// Defines which FLAG will be used to store the object count.
	#define OBJECTS_COLLECTABLE_IF	2 		// If defined, Objs. can be collected if FLAG # == 1
	#define DEACTIVATE_EVIL_TILE			// If defined, no killing tiles (behaviour 1) are detected.
	//#define FULL_BOUNCE 					// If defined, evil tile bounces equal MAX_VX, otherwise v/2
	//#define PLAYER_BOUNCES				// If defined, collisions make player bounce
	//#define SLOW_DRAIN					// Works with bounces. Drain is 4 times slower
	#define PLAYER_DIZZY 					// Enable dizzy state for player
	#define PLAYER_FLICKERS 				// If defined, collisions make player flicker instead.
	//#define MAP_BOTTOM_KILLS				// If defined, exiting the map bottomwise kills.
	//#define WALLS_STOP_ENEMIES			// If defined, enemies react to the scenary (new: if bit 5 on!)
	//#define EVERYTHING_IS_A_WALL			// If defined, any tile <> type 0 is a wall, otherwise just 8.
	//#define COUNT_SCR_ENEMS_ON_FLAG 1		// If defined, count # of enems on screen and store in flag #
	//#define SHOW_LEVEL_ON_SCREEN			// If defined, show level # whenever we enter a new screen
	//#define CUSTOM_HIT					// If defined, different agents take different amounts of life (needs to be refined, don't use)
	//#define CUSTOM_HIT_DEFAULT	10
	#define IS_EVIL ==1 					// ==1 or &1, depending on what you need.
	// #define ONLY_VERTICAL_EVIL_TILE		// Does as it suggests.
```

### Scripting

Scripting is on, obviously, for this game.

```c
	#define ACTIVATE_SCRIPTING			// Activates msc3 scripting and flag related stuff.
	//#define SCRIPT_PAGE		7		// Which RAM page holds the script (128)
	#define CLEAR_FLAGS					// If defined, clear flags each level/beginning.
	//#define SCRIPTING_DOWN			// Use DOWN as the action key.
	#define SCRIPTING_KEY_M				// Use M as the action key instead.
	//#define SCRIPTING_KEY_FIRE		// User FIRE as the action key instead.
	//#define ENABLE_EXTERN_CODE		// Enables custom code to be run from the script using EXTERN n
	//#define EXTERN_E					// Uncomment this as well if you use EXTERN_E in your script
	#define ENABLE_FIRE_ZONE			// Allows to define a zone which auto-triggers "FIRE"
```

The script also needs the object count copied to `FLAG 3`, so define `OBJECT_COUNT` as `3` (in the previous section). 

Note that the old `OBJECTS_ON VAR` is covered somehow by `OBJECTS_COLLECTABLE_IF` (in the previous section). 

### Line of text

The game displayed text using the old fashioned `TEXT` directive in the script. Besides the location on screen (`21, 2`), it also defined a `LINE_OF_TEXT_SUBSTR` of 4 which means lines are 32-4 characters long.

### Top view

This game used a *no inertia top-down* engine which is no longer in the engine. We'll use the normal top-down engine in MK2 with tons of friction and high acceleration.

```c
	#define PLAYER_GENITAL					// Enable top view.
	//#define PLAYER_NEW_GENITAL			// Enable new pseudo 2.5D view (very, VERY preliminary)
	//#define ENABLE_HOLES					// For new genital, behaviour 3 is a "hole"
	//#define FALLING_FRAME		sprite_e	// Sprite frame to render when player falls
	//#define PLAYER_JMP_PRE_INERTIA		// Jumps are affected by momentum generated by conveyors/platforms.
	//#define ENABLE_BEH_64					// Enables behaviour 64 (alt RX/AX) in NEW_GENITAL mode.
	//#define PIXEL_SHIFT				8   // Shift up enemy sprites N pixels UP (better perspective with horizontal movil baddies)
	//#define TOP_OVER_SIDE 				// UP/DOWN has priority over LEFT/RIGHT
```

### Screen configuration

Simple placement for the object count

```c
	#define VIEWPORT_X				1		//
	#define VIEWPORT_Y				0		// Viewport character coordinates
	#define LIFE_X					28 		//
	#define LIFE_Y					23		// Life gauge counter character coordinates
	#define OBJECTS_X				14		//
	#define OBJECTS_Y				23		// Objects counter character coordinates
	#define OBJECTS_ICON_X			99		//
	#define OBJECTS_ICON_Y			99		// Objects icon character coordinates (use with ONLY_ONE_OBJECT)
	#define KEYS_X					99		//
	#define KEYS_Y					99		// Keys counter character coordinates
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

As mentioned, this game used a custom linear engine which used simple pixel increments with no momentum - and such engine is no longer in the engine. So we'll try to emulate it. The original speed was 2 pixels per frame, but MK1 ran much slower than MK2, so that might be excessive. Let's find a compromise using these values:

```c
	#define PLAYER_VX_MAX			120 	// Max velocity (192/64 = 3 pixels/frame)
	#define PLAYER_AX				64		// Acceleration (24/64 = 0,375 pixels/frame^2)
	#define PLAYER_RX				48		// Friction (32/64 = 0,5 pixels/frame^2)
```

### behs array (single level games)

```c
	#ifndef COMPRESSED_LEVELS
	unsigned char behs [] = {
		0, 8, 8, 8, 8, 0, 8, 8, 8, 8, 8, 8, 8, 8, 0, 8,
		0, 0, 0, 0, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	#endif
```

### Double check in case you missed something

MK2 has lots of directives. Always take time to double check if you didn't leave something in or out.

## Review the script

The original script was written for a very old `msc` so it may contain old fashioned stuff or things which are no longer supported in the engine. First rename it to `script.spt` and put it in th `script` folder. Let's review it.

... 

## Review the build script

This is, take a look at `compile.bat` to change some stuff. For example, the map dimensions:

```
	..\utils\map2bin.exe ..\map\mapa.map 7 5 99 ..\bin\map.bin ..\bin\bolts.bin force
	[...]
	..\utils\ene2bin.exe 7 5 1 ..\enems\enems.ene ..\bin\enems.bin ..\bin\hotspots.bin
```

Number of sprites:

```
	..\utils\sprcnv.exe ..\gfx\sprites.png assets\sprites.h 16
```

Number of screens:

```
	..\utils\msc3_mk2_1.exe script.spt 35
```

## Build

Let's build and test...

