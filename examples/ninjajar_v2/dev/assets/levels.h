// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

#define MAX_BOLTS 32

// levels.h
// Level manager for 48K games.

// Types

typedef struct {
    unsigned char np, x, y, st;
} BOLTS;

typedef struct {
	int x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	unsigned char t, life;
} BADDIE;

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

typedef struct {
	unsigned char map_w, map_h;
	unsigned char scr_ini, ini_x, ini_y;
	unsigned char scr_fin;
	unsigned char max_objs;
	unsigned char win_condition;
	unsigned char enems_life;

	unsigned char *map_c;
	unsigned char *bolts_c;
	unsigned char *enems_c;
	unsigned char *hotspots_c;
	unsigned char *behs_c;
	unsigned char *ts_c;
} LEVEL;

// This contains the level data for current level. Not really needed, but
// this is here because of legacy support of 128K full-contained levels like
// those found in Goku Mal.
typedef struct {
	unsigned char map_w, map_h;
	unsigned char scr_ini, ini_x, ini_y;
	unsigned char max_objs;
	unsigned char enems_life;
	unsigned char win_condition;
	unsigned char scr_fin;
	unsigned char activate_scripting;
	unsigned char music_id;
	unsigned char d05;
	unsigned char d06;
	unsigned char d07;
	unsigned char d08;
	unsigned char d09;
} LEVELHEADER;

#ifdef ENABLE_CUSTOM_CONNECTIONS
	typedef struct {
		unsigned char left, right, up, down;
	} CUSTOM_CONNECTION;

	CUSTOM_CONNECTION custom_connections [MAP_W * MAP_H];
#endif

// Heap

extern LEVELHEADER level_data [0];
#asm
	._level_data defs 16
#endasm

extern unsigned char map [0];
#asm
	._map 
		defs 1800 		// Make room from the biggest map in the set *uncompressed*
#endasm

#ifndef DEACTIVATE_KEYS	
	extern BOLTS bolts [0];
	#asm
		._bolts 
			defs 4*MAX_BOLTS
	#endasm
#endif

extern BADDIE baddies [0];
#asm
	._baddies 
		defs MAP_W * MAP_H * 3 * 12
#endasm

#ifndef DISABLE_HOTSPOTS
	extern HOTSPOT hotspots [0];
	#asm
		._hotspots defs MAP_W * MAP_H * 3
	#endasm
#endif

extern unsigned char behs [0];
#asm
	._behs 
		defs 48
#endasm

extern unsigned char tileset [0];
#asm
	._tileset
		BINARY "../bin/font.bin"

		// And space for 48 metatiles + 256 attributes
		defs 192*8+256
#endasm

// Compressed assets

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

// Levelset array

LEVEL levels [] = {
	{
		4, 7, 
		16, 4, 5, 
		99, 
		12,
		0, 1,

		level0_map, level0_bolts, 
		level0_enems, level0_hotspots,
		level0_behs, level0_ts
	},

	{
		4, 7, 
		0, 1, 5, 
		99, 
		12,
		0, 1,

		level1_map, level1_bolts, 
		level1_enems, level1_hotspots,
		level1_behs, level1_ts
	}
};

#include "assets/sprites.h"
#include "assets/extrasprites.h"

