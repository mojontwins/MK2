// MT Engine MK2 v0.88
// Copyleft 2014 the Mojon Twins

// mk2.c
// Main file

// Your main binary may run from 24000 to 61439 (37440 bytes max.)

#define FIXBITS 4
#include <spritepack.h>
//#define DEBUG
//#define SHOW_FPS

// We are using some stuff from splib2 directly.
#asm
		LIB SPMoveSprAbs
		LIB SPPrintAtInv
		LIB SPTileArray
		LIB SPInvalidate
		LIB SPCompDListAddr
#endasm

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

#include "config.h"

// Cosas del juego:

#include "definitions.h"
#include "autodefs.h"

#ifdef ACTIVATE_SCRIPTING
	#include "my/msc-config.h"
#endif

#ifdef MODE_128K
	#include "system/128k.h"
#endif

#include "system/aplib.h"
#include "assets/pantallas.h"

#ifdef MODE_128K
	#include "my/librarian.h"

	#if defined (COMPRESSED_LEVELS)
		#include "assets/levels128.h"
	#elif defined (HANNA_LEVEL_MANAGER)
		#include "assets/levels-hanna.h"
	#else
		#include "assets/mapa.h"
		#include "assets/tileset.h"
		#include "assets/sprites.h"
		#include "assets/extrasprites.h"
		#include "assets/enems.h"
	#endif
#else
	#ifdef COMPRESSED_LEVELS
		#include "assets/levels.h"
	#else
		#include "assets/mapa.h"
		#include "assets/tileset.h"
		#include "assets/sprites.h"
		#include "assets/extrasprites.h"
		#include "assets/enems.h"
	#endif
#endif

#include "addons/helpers.h"
#ifdef ENABLE_DROPS
	#include "addons/drops/sprites.h"
#endif
#ifdef ENABLE_ARROWS
	#include "addons/arrows/sprites.h"
#endif

#ifdef MODE_128K
	#ifdef NO_SOUND
		#include "sound/nosoundplayer.h"
	#else
		#ifdef USE_ARKOS
			#include "sound/arkosplayer.h"
		#else
			#include "sound/wyzplayer.h"
		#endif	
	#endif
#else
	#include "sound/beeper.h"
	#ifdef MIN_FAPS_PER_FRAME
		#include "engine/isrc.h"
	#endif
#endif

#include "engine/printer.h"

#include "engine/general.h"

#ifdef ACTIVATE_SCRIPTING
	#ifdef ENABLE_EXTERN_CODE
		#ifdef EXTERN_E
			#include "my/extern_e.h"
		#else
			#include "my/extern.h"
		#endif
	#endif
	#include "my/msc.h"
#endif

#ifdef ACTIVATE_SCRIPTING
	#include "engine/scripting.h"
#endif

// Animation frames
#include "engine/frames.h"

// Prepare level (compressed levels)
#if defined (SIMPLE_LEVEL_MANAGER)
	#include "engine/clevels-s.h"
#elif defined (COMPRESSED_LEVELS)
	#include "engine/clevels.h"
#endif

// Collision
#include "engine/collision.h"

// Random
#include "engine/random.h"

// Messages
#include "engine/messages.h"


// Floating objects
#if defined (ENABLE_FLOATING_OBJECTS) || defined (ENABLE_SIM)
	#ifdef PLAYER_GENITAL
		#include "engine/fo_genital.h"
	#else
		#include "engine/fo_sideview.h"
	#endif
	#ifdef ENABLE_SIM
		#include "engine/sim.h"
	#endif
#endif

// Animated tiles
#ifdef ENABLE_TILANIMS
	#include "engine/tilanim.h"
#endif

// Breakable tiles helper functions
#ifdef BREAKABLE_WALLS
	#include "engine/breakable.h"
#endif

#ifdef BREAKABLE_WALLS_SIMPLE
	#include "engine/breakable-s.h"
#endif

// Initialization functions
#include "engine/inits.h"

// Hitter (punch/sword) helper functions
#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	#include "engine/hitter_asm.h"
#endif

// Bullets helper functions
#ifdef PLAYER_CAN_FIRE
	#include "engine/bullets.h"
#endif

// Simple bomb helper functions
#ifdef PLAYER_SIMPLE_BOMBS
	#include "engine/bombs-s.h"
#endif

// Block processing
#include "engine/blocks.h"

// Main player movement
#if defined (PHANTOMAS_ENGINE)
	#include "engine/phantomas.h"
#else
	#include "engine/player.h"
#endif

// Extra prints (screen drawing helpers)
#ifdef ENABLE_EXTRA_PRINTS
	#include "engine/extraprints.h"
#endif

// Level names (screen drawing helpers)
#ifdef ENABLE_LEVEL_NAMES
	#include "engine/levelnames.h"
#endif

// Enemies
#include "engine/enems.h"

// Screen drawing
#include "engine/drawscr.h"

// Hud
#include "engine/hud.h"

// Experimental
#ifdef ENABLE_LAVA
	#include "engine/lava.h"
#endif

#ifndef PLAYER_CANNOT_FLICK_SCREEN
	#include "engine/flickscreen.h"
#elif defined (PLAYER_WRAP_AROUND)
	#include "engine/wraparound.h"	
#endif

#include "mainloop/mainloop.h"

#ifndef MODE_128K
	// From beepola. Phaser engine by Shiru.
	#include "sound/music.h"
#endif
