// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// simplelevels.h
// Level manager Sencillón

// This level manager just stores maps / script offsets.
// Everything else is fixed (or has to be switched from an "extern")

typedef struct {
	unsigned char scr_ini;
	unsigned char xy_ini;
	unsigned char flags;
	unsigned char script_offset;

	unsigned char map_res;				// Resource containing map data (plus connections)
	unsigned char enems_res;			// Resource containing enemies
	unsigned char hotspots_res;			// Resource containing hotspots
	unsigned char behs_res;				// Resource containing tile behaviours
} LEVEL;

// Buffers in low ram to decompress stuff

// Map data
extern unsigned char map [0];
#ifdef UNPACKED_MAP
	#asm
		._map defs MAP_W * MAP_H * 150
	#endasm
#else
	#asm
		._map defs MAP_W * MAP_H * 75
	#endasm
#endif

// Custom connections data
#ifdef ENABLE_CUSTOM_CONNECTIONS
	typedef struct {
		unsigned char left, right, up, down;
	} CUSTOM_CONNECTION;
	extern CUSTOM_CONNECTION custom_connections [MAP_W * MAP_H];
	#asm
		._custom_connections defs MAP_W * MAP_H * 4
	#endasm
#endif

// Tileset
extern unsigned char tileset [0];
#asm
	._tileset BINARY "../bin/ts.bin"
#endasm

// Spriteset
extern unsigned char spriteset [0];
#include "sprites.h"
#include "extrasprites.h"

// Baddies
extern BADDIE baddies [0];
#asm
	._baddies defs MAP_W * MAP_H * 3 * 12
#endasm

// Hotspots
extern HOTSPOT hotspots [0];
#asm
	._hotspots defs MAP_W * MAP_H * 3
#endasm

// Behaviours
extern unsigned char behs [0];
#asm
	._behs defs 48
#endasm

// Level data. Each "chapter" can contain many "sub-levels".
// sub levels are small, 16 screens each.

// scr_ini, xy_ini, flags, script_offset
// map_res, ts_res, ss_res, enems_res, hotspots_res, behs_res

LEVEL levels [] = {
	// Chapter 1
	// Level 0, streets
	{0, 0x22, 0, SCRIPT_INIT+SCRIPT_0,
	MAP0C_BIN, ENEMS0C_BIN, HOTSPOTS0C_BIN, BEHS0C_BIN}

	// Level 1, park
	// Level 2, house
	// Level 3, alt. house
}

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
