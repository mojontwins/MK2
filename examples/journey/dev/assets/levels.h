// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// levels.h
// Level manager for 48K games.
// Needs serious improvement. I need to write a 48K game with several levels and refine it.

#define MAP_DATA 		23296
#define BEHAVIOURS		MAP_DATA+MAP_W*MAP_H*75
#define ENEMS_DATA		BEHAVIOURS+48
#define HOTSPOTS_DATA	ENEMS_DATA+MAP_W*MAP_H*30
#define NBOLTS_PEEK		HOTSPOTS_DATA+MAP_W*MAP_H*3
#define BOLTS_DATA		NBOLTS_PEEK+1

#define MAX_bolts	9

unsigned char n_bolts;

#define BADDIES_COUNT 104

typedef struct {
    unsigned char np, x, y, st;
} BOLTS;

typedef struct {
	unsigned char x, y;
	unsigned char x1, y1, x2, y2;
	char mx, my;
	unsigned char t, life;
} BADDIE;

typedef struct {
	unsigned char xy, tipo, act;
} HOTSPOT;

unsigned char *map = (unsigned char *) (MAP_DATA);
bolts *bolts = (BOLTS *) (BOLTS_DATA);
BADDIE *baddies = (BADDIE *) (ENEMS_DATA);
HOTSPOT *hotspots = (HOTSPOT *) (HOTSPOTS_DATA);
unsigned char *behs = (unsigned char *) (BEHAVIOURS);

extern unsigned char *level1c;
extern unsigned char *level2c;
extern unsigned char *tileset1c;
extern unsigned char *tileset2c;

typedef struct {
	unsigned char *leveldata_c;
	unsigned char *tileset_c;
	unsigned char *spriteset_c;
	unsigned char maxobjs;
	unsigned char ini_pant, ini_x, ini_y;
	int script_offset;
} LEVELTYPE;

LEVELTYPE levelset [MAX_LEVELS] = {
	{level1c, tileset1c, 0, 12, 16, 4, 5, 0},
	{level2c, tileset2c, 0, 12, 0, 1, 5, 0}
};

#asm
	._level1c
		BINARY "level1c.bin"
	._level2c
		BINARY "level2c.bin"
	._tileset1c
		BINARY "tileset1c.bin"
	._tileset2c
		BINARY "tileset2c.bin"
#endasm
