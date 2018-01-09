// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// levels128.h
// Level definition for 128k games

// This is the level manager used in Ninjajar!

// This can be considered completely custom but also can be reused/refined.
// I will probably come with something more simple for future games.

// Right away, the levelset is containted in two structures, the
// levels [] array, which has an entry for each unique level, and the
// level_sequence [] array, which defines an order for the levels
// (in case you want to reuse a level - like we do in Ninjajar!)

// Definitions
// This is fixed. 32 bolts per level.
#define MAX_bolts 32

// Types:
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

typedef struct {
    unsigned char np, x, y, st;
} BOLTS;

typedef struct {
	int x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	unsigned char t, life;
} BADDIE;

#ifndef DISABLE_HOTSPOTS
typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;
#endif

typedef struct {
#ifdef EXTENDED_LEVELS
	unsigned char map_res;
	unsigned char bolts_res;
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
#else
	unsigned char resource;
	unsigned char music_id;
	unsigned int script_offset;
#endif
} LEVEL;

// Space reserved for levels
// This will be overwritten with the unpacked data

// Esta forma mierder-rara de hacerlo es porque z88dk no se aclara... O no me aclaro yo.
extern LEVELHEADER level_data [0];
#asm
	._level_data defs 16
#endasm
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
#ifdef MAP_ATTRIBUTES
extern unsigned char map_attrs [0];
#asm
	._map_attrs defs MAP_W * MAP_H
#endasm
#endif
#ifndef DEACTIVATE_KEYS
extern BOLTS bolts [0];
#asm
	; 32 * 4
	._bolts defs 128
#endasm
#endif
extern unsigned char tileset [0];
#asm
	._tileset BINARY "../bin/basicts.bin"
#endasm
extern unsigned char spriteset [0];
#include "sprites-empty.h"
#ifdef EXTRA_SPRITES
extern unsigned char sprite_e [0];
#asm
	._sprite_e defs 144 * EXTRA_SPRITES
#endasm
#endif
extern BADDIE baddies [0];
#asm
	._baddies defs MAP_W * MAP_H * 3 * 12
#endasm
#ifndef DISABLE_HOTSPOTS
extern HOTSPOT hotspots [0];
#asm
	._hotspots defs MAP_W * MAP_H * 3
#endasm
#endif
extern unsigned char behs [0];
#asm
	._behs defs 48
#endasm

// This is different - we take extrasprites.h from the main chunk
// so we can use level bundles without having to worry.
#include "extrasprites.h"

// Level struct
#ifdef EXTENDED_LEVELS
LEVEL levels [] = {
	// Fase 0: Intro.
	{MAP5C_BIN, BOLTS5C_BIN, TS5C_BIN, SS0C_BIN, ENEMS5C_BIN, HOTSPOTS5C_BIN, BEHS5C_BIN, 0,
	 8, 7, 7, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_0}
	 // ... etc
};

#ifdef LEVEL_SEQUENCE
unsigned char level_sequence [] = {
	// ... list of level #s
};
#endif

#else
LEVEL levels [] = {
	{LEVEL0C_BIN, 0, SCRIPT_INIT + LEVEL_0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{LEVEL5C_BIN, 4, SCRIPT_INIT + LEVEL_5},
	{LEVEL6C_BIN, 5, SCRIPT_INIT + LEVEL_6},
	{0, 0, 0},
	{0, 0, 0},
	{LEVELTC_BIN, 5, SCRIPT_INIT + LEVEL_TARDIS}
};
#endif
