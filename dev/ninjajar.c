// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2014 The Mojon Twins

// version 5

#include <spritepack.h>

// Para 128K descomenta la 24199 y comenta la otra
#pragma output STACKPTR=24199
//#pragma output STACKPTR=61952

// Define where to store and how many sprite descriptors are needed.
#define NUMBLOCKS			60
#define AD_FREE				61440 - NUMBLOCKS * 14

// For each sprite you need 1+R*C blocks, where R = rows, C = columns.
// For example, a 16x16 sprite needs 1+3*3 = 10 blocks.
// For games with just 4 16x16 sprites (no shoots/hitter/etc) you need 40 blocks.
// For each shoot/hiter/coco you need 1+2*2 = 5 extra blocks.

// For example: shoots activated need 4 * 10 + 3 * 5 = 55 blocks.
// hitter and no shoots need 4 * 10 + 1 * 5 = 45 blocks.
// hitter and cocos need 5 * 10 + 4 * 5 = 60 blocks.
// Just do the math.

// Optimal place to compile if using 48K and standard COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_CERROJOS * 4 + 49
// Check "Journey to the centre of the Nose" for some insight.

#include "config.h"

// Cosas del juego:

#include "definitions.h"

#ifdef ACTIVATE_SCRIPTING
	#include "msc-config.h"
#endif

#ifdef MODE_128K
	#include "128k.h"
#endif

#include "aplib.h"
#include "pantallas.h"

#ifdef MODE_128K
	#include "librarian.h"
	
	#ifdef COMPRESSED_LEVELS
		#include "levels128.h"
	#else
		#include "mapa.h"
		#include "tileset.h"
		#include "sprites.h"
		#include "extrasprites.h"
		#include "enems.h"
	#endif
#else
	#ifdef COMPRESSED_LEVELS
		#include "levels.h"
	#else
		#include "mapa.h"
	#endif

	#include "tileset.h"
	#include "sprites.h"
	#include "extrasprites.h"
	
	#ifndef COMPRESSED_LEVELS
		#include "enems.h"
	#endif
#endif

#ifdef MODE_128K
	#include "wyzplayer.h"
#else
	#include "beeper.h"
#endif

#include "printer.h"

#ifdef ACTIVATE_SCRIPTING
	#ifdef ENABLE_EXTERN_CODE
		#include "extern.h"
	#endif
	#include "msc.h"
#endif

#include "engine.h"
// =======[CUSTOM MODIFICATION]=======
#include "credits.h"
#include "password.h"
#include "newlevel.h"
#include "cutscene.h"
//
#include "mainloop.h"

// Y el main
/*
void main (void) {
	do_game ();
}
*/

#ifndef MODE_128K
// From beepola. Phaser engine by Shiru.
#include "music.h"
#endif
