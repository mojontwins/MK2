// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// levels128.h
// Level definition for 128k games

// This is the level manager used in Ninjajar!

// Right away, the levelset is containted in two structures, the
// levels [] array, which has an entry for each unique level, and the
// level_sequence [] array, which defines an order for the levels
// (in case you want to reuse a level - like we do in Ninjajar!)

// Definitions
// This is fixed. 32 bolts per level.
#define MAX_BOLTS 32

// Types:
// This contains the level data for current level. Not really needed, but
// this is here because of legacy support of 128K full-contained levels like
// those found in Goku Mal and others
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
	unsigned char x, y;
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
	#ifndef DEACTIVATE_KEYS
		unsigned char bolts_res;
	#endif
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
extern LEVELHEADER level_data;
#asm
	._level_data defs 16
#endasm

extern unsigned char map [0];
#ifdef UNPACKED_MAP
	#asm
		._map defs MAP_W * MAP_H * 150
	#endasm
#elif defined PACKED_MAP
	#asm
		._map defs MAP_W * MAP_H * 75
	#endasm
#else
	#asm
		._map defs 1024 // MAKE ROOM FOR YOUR BIGGEST RLE'D MAP!
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
	._tileset 
	._font
		BINARY "../bin/font.bin"
	._metatileset
		defs 192*8+256
#endasm

extern unsigned char spriteset [0];
#include "assets/sprites-empty.h"

#ifdef EXTRA_SPRITES
	extern unsigned char sprite_e [0];
	#asm
		._sprite_e defs 144 * EXTRA_SPRITES
	#endasm
#endif

extern BADDIE baddies [0];
#asm
	._baddies defs MAP_W * MAP_H * 3 * 10
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
#include "assets/extrasprites.h"

// Level struct
#ifdef EXTENDED_LEVELS
	LEVEL levels [] = {
		// Fase 0: Intro.
		{MAP5C_BIN, TS5C_BIN, SS0C_BIN, ENEMS5C_BIN, HOTSPOTS5C_BIN, BEHS5C_BIN, 0, 
		 8, 7, 7, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0,
		 1, SCRIPT_INIT + LEVEL_TOWN},	
		 
		// Fase 1: Montaña.
		{MAP0C_BIN, TS0C_BIN, SS0C_BIN, ENEMS0C_BIN, HOTSPOTS0C_BIN, BEHS0C_BIN, 17, 
		 0, 2, 2, 99, 1, 12, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},	
		 
		// Fase 2: Atravesamos el lago verde.
		{MAP2C_BIN, TS2C_BIN, SS2C_BIN, ENEMS2C_BIN, HOTSPOTS2C_BIN, BEHS2C_BIN, 1,
		 9, 12, 2, 99, 10, 1, 1, 1, 0, SENG_SWIM, 0,
		 0, 0},	
		
		// Fase 3: Los llanos del marrano.
		{MAP4C_BIN, TS4C_BIN, SS4C_BIN, ENEMS4C_BIN, HOTSPOTS4C_BIN, BEHS4C_BIN, 2,
		 0, 3, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
		 1, SCRIPT_INIT + LEVEL_CLUB},	
		 
		// Fase 4: El pozo poroso
		{MAP6C_BIN, TS2C_BIN, SS2C_BIN, ENEMS6C_BIN, HOTSPOTS6C_BIN, BEHS2C_BIN, 1,
		 0, 1, 1, 99, 4, 3, 1, 1, 0, SENG_SWIM, 1,
		 0, 0},
		 				
		// Fase 5: Isla de la Bruja Sarollán
		{MAP8C_BIN, TS8C_BIN, SS4C_BIN, ENEMS8C_BIN, HOTSPOTS8C_BIN, BEHS8C_BIN, 0,
		 13, 10, 6, 99, 7, 3, 99, 1, 2, SENG_JUMP, 0, 
		 1, SCRIPT_INIT + LEVEL_SAROLLAN},
		 
		// Fase 6: Los llanos del marrano, 2
		{MAP7C_BIN, TS4C_BIN, SS4C_BIN, ENEMS7C_BIN, HOTSPOTS7C_BIN, BEHS4C_BIN, 2,
		 0, 2, 2, 99, 10, 2, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},						
		
		// Fase 7: La cueva Kave.
		{MAP3C_BIN, TS3C_BIN, SS1C_BIN, ENEMS3C_BIN, HOTSPOTS3C_BIN, BEHS3C_BIN, 2,
		 0, 3, 2, 99, 10, 2, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},	 
		 
		// Fase 8: El bosque de los monos chungos.
		{MAP1C_BIN, TS1C_BIN, SS1C_BIN, ENEMS1C_BIN, HOTSPOTS1C_BIN, BEHS1C_BIN, 0,
		 0, 2, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},
		 
		// Fase 9: El lago oscuro
		{MAPAC_BIN, TSAC_BIN, SS2C_BIN, ENEMSAC_BIN, HOTSPOTSAC_BIN, BEHSAC_BIN, 11,
		 0, 1, 1, 99, 7, 2, 99, 1, 2, SENG_SWIM, 1,
		 1, SCRIPT_INIT + LEVEL_OCTOPUS},
		 
		// Fase 10: El castillo de la carne de membrillo
		{MAP9C_BIN, TS9C_BIN, SS1C_BIN, ENEMS9C_BIN, HOTSPOTS9C_BIN, BEHS9C_BIN, 3,
		 9, 1, 6, 99, 4, 4, 1, 1, 2, SENG_JUMP, 1,
		 1, SCRIPT_INIT + LEVEL_CASTLE_A},	

		// Fase 11: Tienda (repetir)
		{MAPBC_BIN, TSBC_BIN, SS0C_BIN, ENEMSBC_BIN, HOTSPOTSBC_BIN, BEHSBC_BIN, 6,
		 0, 1, 3, 99, 2, 6, 1, 1, 2, SENG_JUMP, 1,
		 1, SCRIPT_INIT + LEVEL_SHOPS},
		 
		// Fase 12: Tutorial
		{MAPDC_BIN, TS1C_BIN, SS1C_BIN, ENEMSDC_BIN, HOTSPOTSDC_BIN, BEHS1C_BIN, 19,
		 0, 4, 2, 99, 12, 1, 1, 1, 0, SENG_JUMP, 1,
		 1, SCRIPT_INIT + LEVEL_TUTORIAL},
		 
		// Fase 13: Lava
		{MAPCC_BIN, TSCC_BIN, SS0C_BIN, ENEMSCC_BIN, HOTSPOTSCC_BIN, BEHSCC_BIN, 2, 
		 9, 12, 5, 99, 1, 10, 1, 1, 0, SENG_JUMP, 0,
		 1, SCRIPT_INIT + LEVEL_LAVA},
		 
		// Fase 14: Anju's Cave
		{MAPEC_BIN, TS3C_BIN, SS1C_BIN, ENEMSEC_BIN, HOTSPOTSEC_BIN, BEHS3C_BIN, 2,
		 0, 1, 1, 99, 8, 2, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},
		 
		// Fase 15: Zenman's Pit
		{MAPFC_BIN, TS0C_BIN, SS0C_BIN, ENEMSFC_BIN, HOTSPOTSFC_BIN, BEHS0C_BIN, 0,
		 0, 7, 1, 99, 1, 12, 1, 1, 0, SENG_JUMP, 1,
		 0, 0},
		 
		// Fase 16: Gonzalo's Castle!
		{MAPZC_BIN, TSZC_BIN, SS1C_BIN, ENEMSZC_BIN, HOTSPOTSZC_BIN, BEHSZC_BIN, 3,
		 15, 7, 7, 99, 4, 5, 99, 1, 2, SENG_JUMP, 0,
		 1, SCRIPT_INIT + LEVEL_CASTLE_B},
		 
		// Fase 17: Final mal (playa pepinoni)
		{MAPYC_BIN, TSYC_BIN, SS0C_BIN, ENEMSYC_BIN, HOTSPOTSYC_BIN, BEHSYC_BIN, 17,
		 0, 1, 1, 99, 20, 1, 1, 1, 0, SENG_JUMP, 1,
		 1, SCRIPT_INIT + LEVEL_ENDING_BAD},
		 
		// Fase 18: secuencia final bien animada
		{MAPXC_BIN, TSXC_BIN, SS0C_BIN, ENEMSXC_BIN, HOTSPOTSXC_BIN, BEHSXC_BIN, 3, 
		 0, 12, 8, 99, 3, 1, 99, 1, 2, SENG_JUMP, 0,
		 1, SCRIPT_INIT + LEVEL_ENDING_GOOD}
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
		{LEVEL0C_BIN, 0, SCRIPT_INIT + LEVEL_0},
	// etc
	};
#endif
