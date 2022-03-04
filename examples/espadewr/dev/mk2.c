// MT MK2 ZX v1.0 
// Copyleft 2010-2015, 2019 by The Mojon Twins

// mk2.c
// Main file

// Your main binary may run from 24000 to 61439 (37440 bytes max.)

#define FIXBITS 4
#include <spritepack.h>

// We are using some stuff from splib2 directly.
#asm
		LIB SPMoveSprAbs
		LIB SPPrintAtInv
		LIB SPTileArray
		LIB SPInvalidate
		LIB SPValidate
		LIB SPCompDListAddr
#endasm

#include "my/config.h"
#include "my/sfx_config.h"

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

// Update sprites
#include "engine/update_sprites.h"

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
