// MT MK2 ZX v1.0 
// Copyleft 2010-2015, 2019 by The Mojon Twins

// config.h
// game engine configuration & behaviour

//#define DEBUG
//#define SHOW_FPS

// FOR 128K GAMES:
//#pragma output STACKPTR=24199

// FOR 48K GAMES:
#pragma output STACKPTR=61937

/* splib2 memory map
61440 - 61696 IM2 vector table
61697 - 61936 FREEPOOL (240 bytes)
61937 - 61948 ISR
61949 - 61951 Free (3 bytes)
61952 - 65535 Horizontal Rotation Tables
*/

// If you use a frame limiter you need the isrc counter
#define ISRC_ADDRESS 		23296

// For two integers & one char which are never paged out (reserve 5 bytes)
#define SAFE_INT_ADDRESS 	23297

// Safe memory pool (use it carefully)
#define SAFE_MEMORY_POOL 	23302

// Free space in the splib2 area we can use
#define FREEPOOL 			61697

// Define where to store and how many sprite descriptors are needed.
// This game = 4*10 = 40 blocks
#define NUMBLOCKS			40
unsigned char AD_FREE [NUMBLOCKS * 15];

// Note the 15: blocks are 14 bytes, but there's an overhead of 1 byte per block

// For each sprite you need 1+R*C blocks, where R = rows, C = columns.
// For example, a 16x16 sprite needs 1+3*3 = 10 blocks.
// For games with just 4 16x16 sprites (no shoots/hitter/etc) you need 40 blocks.
// For each shoot/hiter/coco you need 1+2*2 = 5 extra blocks.
// Special: the whip, the shadow which is 1 + 3*2 = 7 extra blocks.

// For example: shoots activated need 4 * 10 + 3 * 5 = 55 blocks.
// hitter and no shoots need 4 * 10 + 1 * 5 = 45 blocks.
// hitter and cocos need 4 * 10 + 4 * 5 = 60 blocks.
// carriable plus nothing else 5 * 10 = 50 blocks
// carriable and cocos 5 * 10 + 3 * 5 = 65 blocks
// Just a whip: 4 * 10 + 7 ? 47 blocks.
// Just a whip plus 1 shoot = 4*10 + 7 + 5 = 52 blocks.
// Just do the math.

// Optimal place to compile if using 48K and standard COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_BOLTS * 4 + 49
// Check "Journey to the centre of the Nose" for some insight.

// ============================================================================
// I. General configuration
// ============================================================================

// While developing...
// #define DEBUG

// 128K support
//#define MODE_128K 					// 128K mode.

// Music engine
//#define USE_ARKOS						// Just comment this to use the default WYZ player.
//#define ARKOS_SFX_CHANNEL		1		// SFX Channel (0-2)
//#define NO_SOUND						// Durante el desarrollo, no llama al player.
//#define PLAY_SAMPLE_ON_DEATH 	0 		// Ninjajar!

// Multi-level support

//#define COMPRESSED_LEVELS 			// use levels.h/levels128.h instead of mapa.h and enems.h (!)
//#define EXTENDED_LEVELS				// Ninjajar! style full-featured levelset
//#define LEVEL_SEQUENCE				// Ninjajar! style level sequence array
#define SCRIPTED_GAME_ENDING			// Game ending is triggered from the script
//#define SIMPLE_LEVEL_MANAGER			// Custom level manager "simple" <- UNFINISHED. DON'T USE!

#define MIN_FAPS_PER_FRAME 		2		// Experimental. Adds an ISR even in 48K mode.
										// Limits the max. speed to 50/N fps.

// In this section we define map dimensions, initial and authomatic ending conditions, etc.

#define MAP_W					10		//
#define MAP_H					2		// Map dimensions in screens
//#define ENABLE_CUSTOM_CONNECTIONS 	// Custom connections array. MAP_W/MAP_H just define how many screens
#define SCR_INI					10		//  Initial screen
#define PLAYER_INI_X			1		//
#define PLAYER_INI_Y			8		// Initial tile coordinates
//#define SCR_END 				99		// Last screen. 99 = deactivated.
//#define PLAYER_END_X			99		//
//#define PLAYER_END_Y			99		// Player tile coordinates to finish game
//#define PLAYER_MAX_OBJECTS	99		// Objects to get to finish game
#define PLAYER_LIFE 			10		// Max and starting life gauge.
//#define DONT_LIMIT_LIFE				// If defined, no upper limit to life gauge.
//#define PLAYER_REFILL			1		// Life recharge
//#define MAX_LEVELS			1		// # of compressed levels
//#define REFILL_ME 					// If defined, refill player on each level
#define WIN_CONDITION			2		// 0 = objects collected, 1 = screen 'N', 2 = scripting, 3 = SIM
//#define EXTRA_SPRITES 		2 		// For 128K games -> # of extra sprite faces to make room for.

//#define USE_TWO_BUTTONS 				// Alternate keyboard scheme for two-buttons games
#ifndef PHANTOMAS_ENGINE
	// To define different keys, the first two hex digits are the COLUMN, the next the ROW
	/*
		    01 02 04 08 10
		f7   1  2  3  4  5
		fb   Q  W  E  R  T
		fd   A  S  D  F  G
		fe  CS  Z  X  C  V

		ef   0  9  8  7  6
		df   P  O  I  U  Y
		bf  EN  L  K  J  H
		7f  SP SS  M  N  B

	*/

	// UP DOWN LEFT RIGHT FIRE JUMP <- with fire/hitter/throwable
	// UP DOWN LEFT RIGHT JUMP xxxx <- with just jump, so configure ahead:
	unsigned int keyscancodes [] = {
	#ifdef USE_TWO_BUTTONS
		0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x047f, 0x087f,		// WSADMN
		0x01fb, 0x01fd, 0x02df, 0x01df, 0x047f, 0x087f, 	// QAOPMN
	#else
		0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x017f, 0,			// WSADs-
		0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0, 			// QAOPs-
	#endif
	};
#endif

// ============================================================================
// II. Engine type
// ============================================================================

// This section is used to define the game engine behaviour. Many directives are related,
// and others are mutually exclusive. I think this will be pretty obvious when you look at them.

// Phantomas Engine
// ----------------
// Coment everything here for normal engine
/*
#define PHANTOMAS_ENGINE		4		// Which phantomas engine:
										// 1 = Phantomas 1
										// 2 = Phantomas 2
										// 3 = LOKOsoft Phantomas
										// 4 = Abu Simbel Profanation (*)

#define PHANTOMAS_FALLING		4		// Falling speed (pixels/frame)
#define PHANTOMAS_WALK			2		// Walking speed

#define PHANTOMAS_INCR_1		2		// Used for jumping
#define PHANTOMAS_INCR_2		4
#define PHANTOMAS_JUMP_CTR		16		// Total jumping steps up&down

#define RESET_TO_WHEN_STOPPED	1		// If defined, reset to frame # when player stopped
#define ADVANCE_FRAME_COUNTER	4		// advance 1 anim. frame every # game frames, use 1 for Phantomas.

// In abu simbel profanation mode, player jumps using PHANTOMAS_INCR_1 increments:
// Long jump: PHANTOMAS_JUMP_CTR steps up, PHANTOMAS_JUMP_CTR steps down.
// Short jump: PHANTOMAS_JUMP_CTR/2 steps up, PHANTOMAS_JUMP_CTR/2 steps down.
*/
// Most things from now on won't apply if PHANTOMAS_ENGINE is on...
// Try... And if you need something, just ask us... Maybe it's possible to add.

// For example, BOUNDING_BOX_8_BOTTOM works for PHANTOMAS/PROFANANTION engines.

// Bounding box size
// -----------------

// This setting controls the size of the collision box for the main sprite with
// the background.
// PLAYER_NEW_GENITAL works best with BOUNDING_BOX_TINY_BOTTOM

										// Comment all of them for normal 16x16 bounding box
//#define BOUNDING_BOX_8_BOTTOM			// 8x8 aligned to bottom center in 16x16
//#define BOUNDING_BOX_8_CENTERED		// 8x8 aligned to center in 16x16
//#define BOUNDING_BOX_TINY_BOTTOM		// 8x2 aligned to bottom center in 16x16
#define SMALL_COLLISION 				// 8x8 centered collision instead of 12x12

// General directives:
// -------------------

#define PLAYER_CHECK_MAP_BOUNDARIES		// If defined, you can't exit the map.
//#define PLAYER_CYCLIC_MAP				// Cyclic, endless map in all directions.
//#define PLAYER_CANNOT_FLICK_SCREEN	// If defined, automatic screen flicking is disabled.
//#define PLAYER_WRAP_AROUND			// If defined, wrap-around. Needs PLAYER_CANNOT_FLICK_SCREEN
#define DIRECT_TO_PLAY					// If defined, title screen is also the game frame.
#define DISABLE_HOTSPOTS				// Disable them completely. Saves tons of memory.
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
// #define ONLY_VERTICAL_EVIL_TILE		// Does as it suggests.

// Enemy engine
// ------------

// General directives

#define ENABLE_PATROLLERS				// Yeah, you can now deactivate good ol' patrollers...
//#define PATROLLERS_HIT			9 	// If defined, patrollers take THIS life, otherwise 1
#define ENEMS_DYING_FRAMES 			12	// Show explosion for # frames

#define ENABLE_FANTIES					// If defined, add code for flying enemies.
#define FANTIES_SIGHT_DISTANCE		96	// If defined, used in our type 6 enemies.
//#define FANTIES_KILL_ON_TOUCH			// If defined, enemy also dies when collision happens
//#define FANTIES_NUMB_ON_FLAG		31	// If defined, flag = 0 makes them not move.
#define FANTIES_MAX_V 				64	// Flying enemies max speed (also for custom type 6 if you want)
#define FANTIES_A 					4	// Flying enemies acceleration.
#define FANTIES_LIFE_GAUGE			1	// Amount of shots needed to kill flying enemies.
#define FANTIES_HIT 				12 	// If defined, fanties take THIS life, otherwise 1
//#define FANTIES_FIXED_CELL 		2	// Always use this
//#define FANTIES_WITH_FACING 			// If defined, 0 = facing left, 1 = facing right

//#define ENABLE_PURSUE_ENEMIES 		// If defined, type 7 enemies are active
//#define DEATH_COUNT_EXPRESSION	20+(rand()&15)
//#define TYPE_7_FIXED_SPRITE		4	// If defined, type 7 enemies are always #

//#define ENABLE_SIMPLE_PURSUERS		// Simpler type 7s [NOT YET]

//#define MAX_COCOS 				1	// Max # of cocos.
//#define COCOS_COLLIDE					// Cocos will die with beh 8

//#define ENABLE_SHOOTERS				// Activate this if your raise bit 4 in any enemies.

//#define SHOOTER_SHOOT_FREQ		63	// Shoot frequency (2^n-1)
//#define SHOOTER_SAFE_DISTANCE		64	// if closer won't shoot
//#define SHOOTER_FIRE_ONE 				// If defined, just fire one coco per enemy
//#define ENEMY_SHOOT_SPEED			4	// pixels per frame

//#define ENABLE_DROPS					// Enemy type 9 = drops
//#define DROPS_KILLABLE				// Define if drops can be killed 

#define ENABLE_ARROWS					// Enemy type 10 = arrows
#define ARROWS_KILLABLE					// Define if drops can be killed 

//#define ENABLE_CLOUDS					// If defined, type 4 enemies are active
#define CLOUDS_SHOOT_FREQ			31	// Shoot frequency (2^n-1)
#define CLOUDS_FIXED_SPRITE			0	// Type 8 enemies are always # - 1
#define CLOUDS_SAFE_DISTANCE		48	// if closer won't shoot
#define CLOUDS_FIRE_ONE					// If defined, just fire one coco per enemy
#define CLOUD_SHOOT_SPEED			8	// pixels per frame

// Extra engine configuration
// --------------------------

//#define USE_HOTSPOTS_TYPE_3 			// Alternate logic for recharges.
//#define TILE_GET					13	// If defined, player can "get" tile #
//#define TILE_GET_REPLACE  		0 	// Replace tile got with tile #
//#define TILE_GET_FLAG 			1	// And this increments flag #
//#define TILE_GET_SCRIPT				// Run PLAYER_GETS_COIN when player gets tile TILE_GET
//#define DIE_AND_RESPAWN				// If defined, dying = respawn on latest safe.
//#define DISABLE_AUTO_SAFE_SPOT		// If defined, you have to define the save spot via scripting
//#define REENTER_ON_DEATH				// Reenter screen when killed, for 1-screen arcades.
#define PLAYER_STEP_SOUND				// Sound while walking. No effect in the BOOTEE engine.
//#define DISABLE_PLATFORMS				// If defined, disable platforms (all engines)
//#define ENABLE_CONVEYORS				// Enable conveyors (all engines)

// Body count
// ----------
// In MK1, every kill was counted on the p_killed variable, which offers
// little control but can be enough for simple games. If you want to have more control
// over # of enemies killed (for example, to reset it!) just define this. p_killed will
// no longer work, instead flag # will be used. 
//#define BODY_COUNT_ON				2	// Increment flag # everytime the player kills an enemy
//#define RUN_SCRIPT_ON_KILL			// If defined, PLAYER_KILLS_ENEMY scripts are triggered on kills
//#define ENEMY_BACKUP					// If you want a backup in case you change the enemy types
										// ingame, define this. Useful for 48K or non-compressed level
										// games (in compressed level games you can save this and just
										// decompress the enemies again!)
//#define RESTORE_ON_INIT				// Restore enemies when entering game.										

// Pushable tile
// -------------

//#define PLAYER_PUSH_BOXES 			// If defined, tile #14 is pushable. Must be type 10.
//#define FIRE_TO_PUSH					// If defined, you have to press FIRE+direction to push.
//#define ENABLE_PUSHED_SCRIPTING		// If defined, nice goodies (below) are activated:
//#define MOVED_TILE_FLAG		1		// Current tile "overwritten" with block is stored here.
//#define MOVED_X_FLAG			2		// X after pushing is stored here.
//#define MOVED_Y_FLAG			3		// Y after pushing is stored here.
//#define PUSHING_ACTION				// If defined, pushing a tile runs PRESS_FIRE script

// Shooting / killing behaviour
// ----------------------------

//#define PLAYER_CAN_FIRE 				// If defined, shooting engine is enabled.
//#define CAN_FIRE_UP					// If defined, player can fire upwards and diagonal.
//#define PLAYER_CAN_FIRE_FLAG		1	// If defined, player can only fire when flag # is 1 Needs flags
//#define PLAYER_CAN_FIRE_INV		45	// If defined, player con only fire if item # is selected! Needs flags
//#define PLAYER_BULLET_SPEED 		8	// Pixels/frame.
//#define MAX_BULLETS 				1	// Max number of bullets on screen. Be careful!.
//#define PLAYER_BULLET_Y_OFFSET	6	// vertical offset from the player's top.
//#define PLAYER_BULLET_X_OFFSET	0	// vertical offset from the player's left/right.
//#define PLAYER_BULLETS_STRENGTH 	1	// Amount of life bullets take from baddies.
//#define BULLETS_BREAK_WALLS			// If defined, bullets break breakable walls.
#define BULLETS_DONT_COLLIDE_PLATFORMS	// Bullets and platforms don't collide

//#define LIMITED_BULLETS 				// If defined, bullets die after N frames
//#define LB_FRAMES					4	// If defined, defines the # of frames bullets live (fixed)
//#define LB_FRAMES_FLAG			2	// If defined, defines which flag determines the # of frames

// Hitter. Define only *ONE* of these. More to come.
// -------------------------------------------------

//#define PLAYER_CAN_PUNCH				// Player can punch. (Ninjajar! (side))
//#define PLAYER_HAZ_SWORD				// Player haz sword. (Espadewr (side))
//#define PLAYER_HAZ_WHIP				// Player haz whip. (Nicanor (side) / Key to time (top-down))

//#define PLAYER_HITTER_INV			46	// If defined, player can use hitter only if item # is selected!
#define PLAYER_HITTER_STRENGTH		0	// Hitter strength. 0 = just makes monsters turn around.
//#define HITTER_BREAKS_WALLS			// If defined, hitter breaks breakable walls.

//#define PLAYER_SIMPLE_BOMBS			// If defined, bombs-s.h module is enabled (Nicanor)
//#define PLAYER_BOMBS_STRENGTH	1		// Amount of life bombs take from baddies.
//#define BOMBS_EXPLOSION_TILE		42	// Tile # for explosion.
//#define BOMBS_BREAK_WALLS				// If defined, bombs break breakable walls.
//#define PLAYER_BOMBS_TILE			44	// ... You know the drill...
//#define PLAYER_BOMBS_INV			44	// If defined, player can use bombs only if item # is selected!
										// NOTE! As of 0.89, this is the only option implemented! 

#define ENEMS_LIFE_GAUGE			1	// Amount of shots/hits needed to kill enemies.
//#define RESPAWN_ON_ENTER				// Enemies respawn when entering screen
//#define RESPAWN_ON_REENTER			// Respawn even on a REENTER in the script (by default REENTER doesn't respawn enemies!)
//#define FIRE_MIN_KILLABLE 		3	// If defined, only enemies >= N can be killed.

//#define MAX_AMMO					5	// If defined, ammo is not infinite!
//#define AMMO_REFILL				5	// ammo refill, using tile 20 (hotspot #4)
//#define INITIAL_AMMO				0	// If defined, ammo = X when entering game.

// Breakable walls
// ---------------

//#define BREAKABLE_WALLS_SIMPLE

//#define BREAKABLE_ANIM				// If defined, breakable tiles look "broken"
#define BREAKABLE_TILE				43	// "broken tile"
#define MAX_BREAKABLE				7	// Max tiles showing "breaking"
#define MAX_BREAKABLE_FRAMES		4	// Frames to show "breaking"

//#define BREAKABLE_TILE_GET		12	// If defined, tile "TILE GET" may appear when breaking tile #
#define BREAKABLE_TILE_FREQ 		3	// Breakable tile frequency (AND)
#define BREAKABLE_TILE_FREQ_T		2	// <= this value = true.

//#define PERSISTENT_BREAKABLE			// Only works with compressed levels/128K games.

// Kill slowly (Ramiro)
// --------------------

//#define ENABLE_KILL_SLOWLY			// Beh 3 kills slowly
//#define KILL_SLOWLY_ON_FLAG		30 	// If defined, flag controls behaviour. If 0,beh 1.
//#define KILL_SLOWLY_GAUGE			32 	// # of ticks before kill
//#define KILL_SLOWLY_FRAMES		8 	// # of frames per tick

// Scripting
// ---------

#define ACTIVATE_SCRIPTING				// Activates msc3 scripting and flag related stuff.
//#define SCRIPT_PAGE				7	// Which RAM page holds the script (128)
#define CLEAR_FLAGS						// If defined, clear flags each level/beginning.
#define SCRIPTING_DOWN					// Use DOWN as the action key.
//#define SCRIPTING_KEY_M				// Use M as the action key instead.
//#define SCRIPTING_KEY_FIRE			// User FIRE as the action key instead.
//#define ENABLE_EXTERN_CODE			// Enables custom code to be run from the script using EXTERN n
//#define EXTERN_E						// Uncomment this as well if you use EXTERN_E in your script
#define ENABLE_FIRE_ZONE				// Allows to define a zone which auto-triggers "FIRE"

// Simple Item Manager
// -------------------
// Uncompatible with scripting. USE ONLY WITH SCRIPTING OFF!
//#define ENABLE_SIM

// General
//#define SIM_MAXCONTAINERS 		6
//#define SIM_DOWN
//#define SIM_KEY_M
//#define SIM_KEY_FIRE

// Display:
//#define SIM_DISPLAY_HORIZONTAL
//#define SIM_DISPLAY_MAXITEMS		2
//#define SIM_DISPLAY_X				24
//#define SIM_DISPLAY_Y				21
//#define SIM_DISPLAY_ITEM_EMPTY	31
//#define SIM_DISPLAY_ITEM_STEP		3
//#define SIM_DISPLAY_SEL_C			66
//#define SIM_DISPLAY_SEL_CHAR1		62
//#define SIM_DISPLAY_SEL_CHAR2		63

// Timer
// -----
//#define TIMER_ENABLE					// Enable timer
//#define TIMER_INITIAL				99	// For unscripted games, initial value.
//#define TIMER_REFILL				30	// Timer refill, using tile 21 (hotspot #5)
//#define TIMER_LAPSE 				32	// # of frames between decrements
//#define TIMER_START 					// If defined, start timer from the beginning
//#define TIMER_SCRIPT_0				// If defined, timer = 0 runs "ON_TIMER_OFF" in the script
//#define TIMER_GAMEOVER_0				// If defined, timer = 0 causes "game over"
//#define TIMER_KILL_0					// If defined, timer = 0 causes "one life less".
//#define TIMER_WARP_TO 0				// If defined, warp to screen X after "one life less".
//#define TIMER_WARP_TO_X			1	//
//#define TIMER_WARP_TO_Y			1	// "warp to" coordinates.
//#define TIMER_AUTO_RESET				// If defined, timer resets after "one life less"
//#define SHOW_TIMER_OVER				// If defined, "TIME OVER" shows when time is up.

// Lava:
// -----
// Experimental & custom. Use @ your own risk. Not supported __AT ALL__
// Only 128K/Multilevel/Enhaced levels. This was custom for Ninjajar! - I wonder why it's still here

//#define ENABLE_LAVA
//#define LAVA_FLAG					30
//#define LAVA_PERIOD 				7
//#define LAVA_X1 					2
//#define LAVA_X2 					28	// LAVA_X1 <= x < LAVA_X2
//#define LAVA_T					18

// Floating objects:
// -----------------

//#define ENABLE_FLOATING_OBJECTS		// Activate this for floating objects support

//#define FO_GRAVITY					// If defined, floating objects are affected by gravity
//#define FO_SOLID_FLOOR				// If defined, floating objects won't fall off the screen

//#define FO_DETECT_INTERACTION_CENTER	// If defined, "active" hotspot is @ player center
										// Otherwise it's on the floor, depending where he's facing.
										// Just for side-view. 

//#define ENABLE_FO_CARRIABLE_BOXES		// Boxes the player can carry/place elsewhere.
//#define FT_CARRIABLE_BOXES		17	// Tile for carriable boxes.
//#define CARRIABLE_BOXES_ALTER_JUMP 180// You jump less if defined. Modifies "PLAYER_JMP_VY_MAX"
//#define CARRIABLE_BOXES_THROWABLE 	// If defined, carriable boxes are throwable!
//#define CARRIABLE_BOXES_COUNT_KILLS 2 // If defined, count # of kills and store in flag N.
//#define CARRIABLE_BOXES_DRAIN		7	// Boxes drain life if held every N+1 frames (power of two minus 1!)
//#define CARRIABLE_BOXES_CORCHONETA	// Corchonetas de sartar!
//#define CARRIABLE_BOXES_MAX_C_VY	1024// Max vertical velocity

//#define ENABLE_FO_SCRIPTING 			// Anytime a FO falls, PRESS_FIRE script is ran
//#define FO_X_FLAG					1
//#define FO_Y_FLAG					2
//#define FO_T_FLAG					3	// Flags to store X, Y, and Type of object which just fell.

//#define ENABLE_FO_OBJECT_CONTAINERS 	// Use with scripting. Helps to manage item collecting
//#define SHOW_EMPTY_CONTAINER			// If defined, show empty container tile

// Engine type: No effect if PHANTOMAS_ENGINE is defined...

// Top view:
// ---------

//#define PLAYER_GENITAL				// Enable top view.
//#define PLAYER_NEW_GENITAL			// Enable new pseudo 2.5D view (very, VERY preliminary)
//#define ENABLE_HOLES					// For new genital, behaviour 3 is a "hole"
//#define FALLING_FRAME		sprite_e	// Sprite frame to render when player falls
//#define PLAYER_JMP_PRE_INERTIA		// Jumps are affected by momentum generated by conveyors/platforms.
//#define ENABLE_BEH_64					// Enables behaviour 64 (alt RX/AX) in NEW_GENITAL mode.
//#define PIXEL_SHIFT				8   // Shift up enemy sprites N pixels UP (better perspective with horizontal movil baddies)
//#define TOP_OVER_SIDE 				// UP/DOWN has priority over LEFT/RIGHT

// Side view:
// ----------

#define PLAYER_HAS_JUMP 				// If defined, player is able to jump. EVEN IN TOP-DOWN!
//#define PLAYER_BOOTEE 				// Always jumping engine. Don't forget to disable "HAS_JUMP" and "HAS_JETPAC"!!!
//#define PLAYER_BOUNCE_WITH_WALLS		// Bounce when hitting a wall. Only really useful in MOGGY_STYLE mode
//#define PLAYER_CUMULATIVE_JUMP		// Keep pressing JUMP to JUMP higher in several bounces
//#define PLAYER_BOOST_WHEN_GOING_UP	// Boost pvy when jumping to the screen above.

//#define PLAYER_HAS_JETPAC 			// If defined, player can thrust a vertical jetpac
//#define JETPAC_DEPLETES			4	// If defined, jetpac depletes each # frames.
//#define JETPAC_FUEL_INITIAL		25	// needed by "JETPAC_DEPLETES", initial fuel value.
//#define JETPAC_FUEL_MAX			25	// needed by "JETPAC_DEPLETES" & "JETPAC_REFILLS", max fuel value.
//#define JETPAC_AUTO_REFILLS		2	// If defined, jetpac refills each # frames when not in use.
//#define JETPAC_REFILLS				// If defined, type 6 hotspots are refills.
//#define JETPAC_FUEL_REFILL		25	// needed by "JETPAC_REFILLS"

// Stepping over enemies...
//#define PLAYER_KILLS_ENEMIES			// If defined, stepping on enemies kills them
//#define PLAYER_CAN_KILL_FLAG		1	// If defined, player can only kill when flag # is "1"
//#define PLAYER_MIN_KILLABLE	  	3 	// Only kill enemies with id >= PLAYER_MIN_KILLABLE

//#define PLAYER_HAS_SWIM 				// If defined, player is able to swim
//#define SWITCHABLE_ENGINES			// WIP! VERY, VERY, VERY WIP! See Sir Ababol DX or Ninjajar!

// ============================================================================
// III. Screen configuration
// ============================================================================

// This sections defines how stuff is rendered, where to show counters, etcetera
// If you have a counter activated you don't have to show, define its X coord. as 99

#define VIEWPORT_X				1		//
#define VIEWPORT_Y				2		// Viewport character coordinates
#define LIFE_X					6 		//
#define LIFE_Y					0		// Life gauge counter character coordinates
#define OBJECTS_X				17		//
#define OBJECTS_Y				0		// Objects counter character coordinates
//#define REVERSE_OBJECTS_COUNT 		// If defined, from MAX to 0
#define OBJECTS_ICON_X			99		//
#define OBJECTS_ICON_Y			99		// Objects icon character coordinates (use with ONLY_ONE_OBJECT)
#define KEYS_X					99		//
#define KEYS_Y					99		// Keys counter character coordinates
#define KILLED_X				99		//
#define KILLED_Y				99		// Kills counter character coordinates
#define AMMO_X					99		//
#define AMMO_Y					99		// Ammo counter character coordinates
#define TIMER_X 				99		//
#define TIMER_Y 				99		// Timer counter coordinates
#define FLAG_X					4		//
#define FLAG_Y					23		// Custom flag character coordinates
#define PLAYER_SHOW_FLAG		1		// If defined, show flag #
#define FUEL_X					99		//
#define FUEL_Y					99		// Fuel counter in bla bla bla

#define KILL_SLOWLY_GAUGE_X		21		// For evil zone counters
#define KILL_SLOWLY_GAUGE_Y		23		//

// Text
//#define LINE_OF_TEXT			22		// If defined, scripts can show text @ Y = #
//#define LINE_OF_TEXT_X		1		// X coordinate.
//#define LINE_OF_TEXT_ATTR 	71		// Attribute
//#define LINE_OF_TEXT_SUBSTR	4 		// Line of text is max. 32-# characters

// Map data format. Choose one:

#define PACKED_MAP 						// Packed maps, 2 bytes per tile.
//#define UNPACKED_MAP					// Full, uncompressed maps. Shadows settings are ignored.
//#define RLE_MAP 				44		// Use RLE instead of packed/unpacked. 44, 53 or 62.

// Graphic FX, uncomment which applies...

//#define USE_AUTO_SHADOWS				// Automatic shadows made of darker attributes
//#define USE_AUTO_TILE_SHADOWS 		// Automatic shadows using specially defined tiles 32-47.
//#define ENABLE_SUBTILESETS			// Adds subtileset loader.
//#define MAP_ATTRIBUTES				// Enables multi-purpose map attributes array (only in multi-level games as of 0.90)
//#define NO_MASKS						// Sprites are rendered using OR instead of masks.
//#define PLAYER_ALTERNATE_ANIMATION	// If defined, animation is 1,2,3,1,2,3...
//#define MASKED_BULLETS				// If needed
#define ENABLE_TILANIMS					// If defined, animated tiles are enabled and will alternate between t and t+1
#define IS_TILANIM(t) 		((t)==20)	// Condition to detect if a tile is animated										
//#define PAUSE_ABORT					// Add h=PAUSE, y=ABORT
//#define GET_X_MORE					// Shows "get X more" when getting an object
//#define ALT_TILE 				19 		// If defined, automatic random tile # for tile 0 (was fixed to 19)
//#define TWO_SETS						// If defined, use two 16 sets in one (just ask)
//#define TWO_SETS_SEL (n_pant>8?32:0)	// This expresion must equal 0 for set 1 to be used, or 32 for set 2 to be used (just ask)
// #define TWO_SETS_MAPPED					// Two sets, but which set to use is mapped after map data (1 byte per screen)
//#define ENABLE_LEVEL_NAMES			// Give a name for each level/screen in engine/levelnames.h
//#define ENABLE_EXTRA_PRINTS			// Configure extra tile prints for some screens in engine/extraprints.h

// ============================================================================
// IV. Player movement configuration
// ============================================================================

// No effect if PHANTOMAS_ENGINE is on!

// This section is used to define which constants are used in the gravity/acceleration engine.
// If a side-view engine is configured, we have to define vertical and horizontal constants
// separately. If a top-view engine is configured instead, the horizontal values are also
// applied to the vertical component, vertical values are ignored.

// Speeds are 8 bits wide, so range is -128 to 127 !!

// IV.1. Vertical movement. Only for side-view.

#define PLAYER_FALL_VY_MAX		127 	// Max falling speed
#define PLAYER_G				8		// Gravity acceleration

#define PLAYER_JMP_VY_INITIAL	32		// Initial jump velocity
#define PLAYER_JMP_VY_MAX		64	 	// Max jump velocity
#define PLAYER_JMP_VY_INCR		24		// acceleration while JUMP is pressed

//#define PLAYER_JETPAC_VY_INCR	8		// Vertical jetpac gauge
//#define PLAYER_JETPAC_VY_MAX	64	 	// Max vertical jetpac speed

// IV.2. Horizontal (side view) or general (top view) movement.

#define PLAYER_VX_MAX			64 		// Max velocity
#define PLAYER_AX				16		// Acceleration
#define PLAYER_RX				24		// Friction

//#define PLAYER_AX_ALT			8 		// Acceleration (alternate) when stepping on tile w/beh. 64
//#define PLAYER_RX_ALT			8 		// Friction (alternate) when stepping on tile w/beh. 64

#define PLAYER_V_BOUNCE			100		// Bouncing speed

// IV.3. Swimming

//#define PLAYER_MAX_VSWIM		32
//#define PLAYER_ASWIM			8

// ============================================================================
// V. Tile behaviour
// ============================================================================

// Defines the behaviour for each tile. Remember that if keys are activated, tile #15 is a bolt
// and, therefore, it should be made a full obstacle!

// 0 = Walkable (no action)
// 1 = Walkable and kills.
// 2 = Walkable and hides.
// 4 = Platform (only stops player if falling on it)
// 8 = Full obstacle (blocks player from all directions)
// 10 = special obstacle (pushing blocks OR locks!)
// 16 = Breakable (#ifdef BREAKABLE_WALLS)
// 32 = Conveyor
// 64 = CUSTOM F.O. -> CORCHONETA!
// You can add the numbers to get combined behaviours
// Save for 10 (special), but that's obvious, innit?

// 0.90: top-down conveyors, bits 12=>direction, so:
// C  DD
// 100000 = 32 = conveyor up
// 100010 = 34 = conveyor down
// 100100 = 36 = conveyor left
// 100110 = 38 = conveyor right

// 0.90: top-down "holes" = 1 + 2 (3)

// 0.90: In new-genital mode, 64 = alt RX/AX.

// 0.90b: kill slowly = 1 + 2 (3), not super genital.

#ifndef COMPRESSED_LEVELS
unsigned char behs [] = {
	0, 8, 0, 0, 0, 0, 0, 4, 8, 0, 0, 8, 0, 0, 0, 0,
	0,24, 8, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
#endif

// WARNING!! Don't touch these.

#ifdef PLAYER_NEW_GENITAL
#define PLAYER_GENITAL
#endif

#if defined (CARRIABLE_BOXES_ALTER_JUMP)
#define PLAYER_VARIABLE_JUMP
#endif

#ifdef ENABLE_FANTIES
#define ENABLE_CUSTOM_FANTIES
#endif
#ifdef ENABLE_PURSUE_ENEMIES
#define ENABLE_PURSUERS
#endif

#ifdef SWITCHABLE_WEAPONS
#define SW_NOTHING				0
#define SW_HITTER				1
#define SW_GUN					2		// You don't need to touch these. JUST DON'T

#endif

#ifdef DISABLE_HOTSPOTS				
#define DEACTIVATE_KEYS 			
#define DEACTIVATE_OBJECTS			
#endif

// Sound driver macro

#ifdef MODE_128K
	#ifdef NO_SOUND
		#define _AY_PL_SND nosound_play_sound
		#define _AY_PL_MUS nosound_play_music
		#define _AY_ST_ALL nosound_stop_sound
	#elif defined USE_ARKOS
		#define _AY_PL_SND arkos_play_sound
		#define _AY_PL_MUS arkos_play_music
		#define _AY_ST_ALL arkos_stop_sound
	#else
		#define _AY_PL_SND wyz_play_sound
		#define _AY_PL_MUS wyz_play_music
		#define _AY_ST_ALL wyz_stop_sound
	#endif
#else
	#define _AY_PL_SND beep_fx
#endif

// General hitter

#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
#define PLAYER_HAZ_HITTER
#endif

// General dying checks

#if (defined (PLAYER_CAN_FIRE) + defined (PLAYER_HAZ_HITTER) + defined (PLAYER_SIMPLE_BOMBS)) == 0
#define WAYS_TO_DIE 0
#elif (defined (PLAYER_CAN_FIRE) + defined (PLAYER_HAZ_HITTER) + defined (PLAYER_SIMPLE_BOMBS)) == 1
#define WAYS_TO_DIE 1
#else
#define WAYS_TO_DIE 2
#endif

// Die & respawn in top-down

#ifdef PLAYER_GENITAL
#ifdef PLAYER_HAS_JUMP
#define DIE_AND_RESPAWN
#else
#undef DIE_AND_RESPAWN
#endif
#endif

// Two buttons

#ifdef PLAYER_GENITAL
#ifdef PLAYER_HAS_JUMP
#define USE_TWO_BUTTONS
#endif
#endif

// Modifiable rx/ax in new genital mode.

// Variable AX/RX 

#if defined (PLAYER_NEW_GENITAL) && defined (ENABLE_BEH_64)
#define AXVAL p_ax
#define RXVAL p_rx
#else
#define AXVAL PLAYER_AX
#define RXVAL PLAYER_RX
#endif

// Some things need "read_offset" from the librarian.
#if defined (ENABLE_SUBTILESETS)
#define NEED_RAMN_OFFSETS
#endif

// Enems may die
#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_KILLS_ENEMIES) || defined (ENABLE_PURSUERS) || defined (MODE_128K) || defined (PLAYER_CAN_PUNCH) || defined (CARRIABLE_BOXES_THROWABLE) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP) || defined (PLAYER_SIMPLE_BOMBS)
	#define ENEMS_MAY_DIE
#endif

// END OF WARNING.
