// MT Engine MK2
// Copyleft 2014 the Mojon Twins

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

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

typedef struct {
#ifdef EXTENDED_LEVELS
	unsigned char map_res;
	unsigned char bolts_res;
	unsigned char ts_res;
	unsigned char ss_res;
	unsigned char enems_res;
	unsigned char hotspots_res;
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
#ifndef DEACTIVATE_KEYS
extern BOLTS bolts [0];
#asm
	; 32 * 4
	._bolts defs 128
#endasm
#endif
extern unsigned char tileset [0];
#asm
	._tileset BINARY "basicts.bin"
#endasm
extern unsigned char spriteset [0];
#include "sprites-empty.h"
#include "extrasprites.h"
extern BADDIE baddies [0];
#asm
	._baddies defs MAP_W * MAP_H * 3 * 12
#endasm
extern HOTSPOT hotspots [0];
#asm
	._hotspots defs MAP_W * MAP_H * 3
#endasm
extern unsigned char behs [0];
#asm
	._behs defs 48
#endasm

// Level struct
#ifdef EXTENDED_LEVELS
LEVEL levels [] = {
	// Fase 0: Intro.
	{MAP5C_BIN, BOLTS5C_BIN, TS5C_BIN, SS0C_BIN, ENEMS5C_BIN, HOTSPOTS5C_BIN, BEHS5C_BIN, 0,
	 8, 7, 7, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_0},

	// Fase 1: Montaña.
	{MAP0C_BIN, BOLTS0C_BIN, TS0C_BIN, SS0C_BIN, ENEMS0C_BIN, HOTSPOTS0C_BIN, BEHS0C_BIN, 17,
	 0, 2, 2, 99, 1, 12, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 2: Atravesamos el lago verde.
	{MAP2C_BIN, BOLTS2C_BIN, TS2C_BIN, SS2C_BIN, ENEMS2C_BIN, HOTSPOTS2C_BIN, BEHS2C_BIN, 1,
	 9, 12, 2, 99, 10, 1, 1, 1, 0, SENG_SWIM, 0,
	 0, 0},

	// Fase 3: Los llanos del marrano.
	{MAP4C_BIN, BOLTS4C_BIN, TS4C_BIN, SS4C_BIN, ENEMS4C_BIN, HOTSPOTS4C_BIN, BEHS4C_BIN, 2,
	 0, 3, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
	 1, SCRIPT_INIT + SCRIPT_11},

	// Fase 4: El pozo poroso
	{MAP6C_BIN, BOLTS6C_BIN, TS2C_BIN, SS2C_BIN, ENEMS6C_BIN, HOTSPOTS6C_BIN, BEHS2C_BIN, 1,
	 0, 1, 1, 99, 4, 3, 1, 1, 0, SENG_SWIM, 1,
	 0, 0},

	// Fase 5: Isla de la Bruja Sarollán
	{MAP8C_BIN, BOLTS8C_BIN, TS8C_BIN, SS4C_BIN, ENEMS8C_BIN, HOTSPOTS8C_BIN, BEHS8C_BIN, 0,
	 13, 10, 6, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_2},

	// Fase 6: Los llanos del marrano, 2
	{MAP7C_BIN, BOLTS7C_BIN, TS4C_BIN, SS4C_BIN, ENEMS7C_BIN, HOTSPOTS7C_BIN, BEHS4C_BIN, 2,
	 0, 2, 2, 99, 10, 2, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 7: La cueva Kave.
	{MAP3C_BIN, BOLTS3C_BIN, TS3C_BIN, SS1C_BIN, ENEMS3C_BIN, HOTSPOTS3C_BIN, BEHS3C_BIN, 2,
	 0, 3, 2, 99, 10, 2, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 8: El bosque de los monos chungos.
	{MAP1C_BIN, BOLTS1C_BIN, TS1C_BIN, SS1C_BIN, ENEMS1C_BIN, HOTSPOTS1C_BIN, BEHS1C_BIN, 0,
	 0, 2, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 9: El lago oscuro
	{MAPAC_BIN, BOLTSAC_BIN, TSAC_BIN, SS2C_BIN, ENEMSAC_BIN, HOTSPOTSAC_BIN, BEHSAC_BIN, 11,
	 0, 1, 1, 99, 7, 2, 99, 1, 2, SENG_SWIM, 1,
	 1, SCRIPT_INIT + SCRIPT_5},

	// Fase 10: El castillo de la carne de membrillo
	{MAP9C_BIN, BOLTS9C_BIN, TS9C_BIN, SS1C_BIN, ENEMS9C_BIN, HOTSPOTS9C_BIN, BEHS9C_BIN, 3,
	 9, 1, 6, 99, 4, 4, 1, 1, 2, SENG_JUMP, 1,
	 1, SCRIPT_INIT + SCRIPT_3},

	// Fase 11: Tienda (repetir)
	{MAPBC_BIN, BOLTSBC_BIN, TSBC_BIN, SS0C_BIN, ENEMSBC_BIN, HOTSPOTSBC_BIN, BEHSBC_BIN, 6,
	 0, 1, 3, 99, 2, 6, 1, 1, 2, SENG_JUMP, 1,
	 1, SCRIPT_INIT + SCRIPT_4},

	// Fase 12: Tutorial
	{MAPDC_BIN, BOLTSDC_BIN, TS1C_BIN, SS1C_BIN, ENEMSDC_BIN, HOTSPOTSDC_BIN, BEHS1C_BIN, 19,
	 0, 4, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
	 1, SCRIPT_INIT + SCRIPT_6},

	// Fase 13: Lava
	{MAPCC_BIN, BOLTSCC_BIN, TSCC_BIN, SS0C_BIN, ENEMSCC_BIN, HOTSPOTSCC_BIN, BEHSCC_BIN, 2,
	 9, 12, 5, 99, 1, 10, 1, 1, 0, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_7},

	// Fase 14: Anju's Cave
	{MAPEC_BIN, BOLTSEC_BIN, TS3C_BIN, SS1C_BIN, ENEMSEC_BIN, HOTSPOTSEC_BIN, BEHS3C_BIN, 2,
	 0, 1, 1, 99, 8, 2, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 15: Zenman's Pit
	{MAPFC_BIN, BOLTSFC_BIN, TS0C_BIN, SS0C_BIN, ENEMSFC_BIN, HOTSPOTSFC_BIN, BEHS0C_BIN, 0,
	 0, 7, 1, 99, 1, 12, 1, 1, 0, SENG_JUMP, 1,
	 0, 0},

	// Fase 16: Gonzalo's Castle!
	{MAPZC_BIN, BOLTSZC_BIN, TSZC_BIN, SS1C_BIN, ENEMSZC_BIN, HOTSPOTSZC_BIN, BEHSZC_BIN, 3,
	 15, 7, 7, 99, 4, 5, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_8},

	// Fase 17: Final mal (playa pepinoni)
	{MAPYC_BIN, BOLTSYC_BIN, TSYC_BIN, SS0C_BIN, ENEMSYC_BIN, HOTSPOTSYC_BIN, BEHSYC_BIN, 17,
	 0, 1, 1, 99, 20, 1, 1, 1, 0, SENG_JUMP, 1,
	 1, SCRIPT_INIT + SCRIPT_9},

	// Fase 18: secuencia final bien animada
	{MAPXC_BIN, BOLTSXC_BIN, TSXC_BIN, SS0C_BIN, ENEMSXC_BIN, HOTSPOTSXC_BIN, BEHSXC_BIN, 3,
	 0, 12, 8, 99, 3, 1, 99, 1, 2, SENG_JUMP, 0,
	 1, SCRIPT_INIT + SCRIPT_10}
};

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

#else
LEVEL levels [] = {
	{3,3},
	{4,4},
	{5,5},
	{7,7},
	{6,3}
};
#endif
