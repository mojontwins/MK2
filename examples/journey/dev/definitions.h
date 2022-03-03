// MT MK2 ZX v1.0 
// Copyleft 2010-2015, 2019 by The Mojon Twins

// definitions.h
// Main definitions

// General defines

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
#define EST_DIZZY 		8
#define sgni(n)			(n < 0 ? -1 : 1)
#define saturate(n)		(n < 0 ? 0 : n)
#define WTOP 			1
#define WBOTTOM 		2
#define WLEFT 			3
#define WRIGHT 			4

#define FACING_RIGHT 	0
#define FACING_LEFT 	2
#define FACING_UP 		4
#define FACING_DOWN 	6

#define SENG_JUMP 		0
#define SENG_SWIM 		1
#define SENG_COPT 		2
#define SENG_JETP 		3
#define SENG_BOOT 		4

#define FANTIES_IDLE 		0
#define FANTIES_PURSUING	1
#define FANTIES_RETREATING	2
#define GENERAL_DYING		4

#define MAX_FLAGS 		32

#define BUFFER_IDX(x,y) x+(y<<4)-y

#define TILE_EVIL 		1
#define TILE_HOLE 		2

#define MAX_TILANIMS 	16
#define TILANIMS_PRIME  3 			// Prime to MAX_TILANIMS, ideally /4-1

// Keys

#define KEY_L 					0x02bf
#define KEY_M 					0x047f
#define KEY_H					0x08bf
#define KEY_Y 					0x10df

// General externs

unsigned int asm_int 	@ SAFE_INT_ADDRESS;
unsigned int asm_int_2 	@ SAFE_INT_ADDRESS + 2;
unsigned int safe_byte 	@ SAFE_INT_ADDRESS + 4;

// Gigaglobals

struct sp_UDK keys;
unsigned char (*joyfunc)(struct sp_UDK *) = sp_JoyKeyboard;

const void *joyfuncs [] = {
	sp_JoyKeyboard, sp_JoyKeyboard, sp_JoyKempston, sp_JoySinclair1
};

unsigned char *gen_pt;
 
void *my_malloc(uint bytes) {
   return sp_BlockAlloc(0);
}

void *u_malloc = my_malloc;
void *u_free = sp_FreeBlock;

struct sp_SS *sp_player;
struct sp_SS *sp_moviles [3];
#ifdef PLAYER_CAN_FIRE
	struct sp_SS *sp_bullets [MAX_BULLETS];
#endif
#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	struct sp_SS *sp_hitter;
#endif
#ifdef ENABLE_SHOOTERS
	struct sp_SS *sp_cocos [MAX_COCOS];
#endif
#ifdef ENABLE_FLOATING_OBJECTS
	#ifdef ENABLE_FO_CARRIABLE_BOXES
		struct sp_SS *sp_carriable;
	#endif
#endif
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	struct sp_SS *sp_shadow;
#endif

#asm
	.vpClipStruct defb VIEWPORT_Y, VIEWPORT_Y + 20, VIEWPORT_X, VIEWPORT_X + 30
	.fsClipStruct defb 0, 24, 0, 32
#endasm	

unsigned char enoffs;

// Aux

unsigned char half_life = 0;

// Player
signed int p_x, p_y;
#if defined (HANNA_ENGINE)
	signed char p_v;
#else
	signed char p_vx, p_vy, ptgmx, ptgmy;
#endif
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	signed int p_z, p_vz;
	unsigned char p_jmp_facing, gpz;
#endif
signed char p_g;
#if defined (PLAYER_NEW_GENITAL) && defined (ENABLE_BEH_64) 
	signed char p_ax, p_rx;
#endif
#ifdef PLAYER_GENITAL
	signed char p_thrust;
#endif
unsigned char p_jmp_ct;
unsigned char *p_c_f, *p_n_f;
unsigned char p_jmp_on;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_state;
unsigned char p_state_ct;
unsigned char p_gotten;
unsigned char p_life, p_objs, p_keys;
#ifndef BODY_COUNT_ON
	unsigned char p_killed;
#endif
unsigned char p_disparando;
#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	unsigned char p_hitting;
#endif
#ifdef PLAYER_HAZ_SWORD
	unsigned char p_up; 
#endif
unsigned char p_facing_v, p_facing_h;
unsigned char p_killme;
#ifdef DIE_AND_RESPAWN
	unsigned char p_safe_pant, p_safe_x, p_safe_y;
#endif
#ifdef MAX_AMMO
	unsigned char p_ammo;
#endif
#ifdef ENABLE_FO_CARRIABLE_BOXES
	unsigned char p_hasbox;
#endif
#ifdef JETPAC_DEPLETES
	unsigned char p_fuel;
#endif
#ifdef ENABLE_HOLES
	unsigned char p_ct_hole;
#endif
#ifdef ENABLE_KILL_SLOWLY
	unsigned char p_ks_gauge;
	unsigned char p_ks_fc;
#endif

// Collisions
unsigned char cx1, cx2, cy1, cy2, at1, at2;
unsigned char ptx1, pty1, ptx2, pty2;

// Make some player values variable. Preliminary, just the maximum jump speed...

#ifdef PLAYER_VARIABLE_JUMP
	signed int PLAYER_JMP_VY_MAX;
#endif

// Enems on screen

unsigned char en_an_base_frame [3];
//unsigned char en_an_frame [3];
unsigned char en_an_count [3];
unsigned char *en_an_c_f [3], *en_an_n_f [3];
unsigned char en_an_state [3];

#ifdef ENEMY_BACKUP
	unsigned char enemy_backup [3 * MAP_W * MAP_H];
#endif

#ifdef PLAYER_CAN_FIRE
	unsigned char en_an_morido [3];
#endif

#if defined (RANDOM_RESPAWN) || defined (ENABLE_CUSTOM_FANTIES)
	signed int en_an_x [3];
	signed int en_an_y [3];
	signed char en_an_vx [3];
	signed char en_an_vy [3];
	#ifdef RANDOM_RESPAWN
		unsigned char en_an_fanty_activo [3];
	#endif

	signed int _en_an_x, _en_an_y;
	signed char _en_an_vx, _en_an_vy;
#endif

#ifdef ENABLE_PURSUERS
	unsigned char en_an_alive [3];
	unsigned char en_an_dead_row [3];
	unsigned char en_an_rawv [3];
#endif

#ifdef ENABLE_HANNA_MONSTERS_11
	unsigned char en_an_dir [3];
	unsigned char _en_cx, _en_cy;
#endif

#if defined (ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
	unsigned char coco_x [MAX_COCOS], coco_y [MAX_COCOS], coco_s [MAX_COCOS], ctx, cty;
	signed char coco_vx [MAX_COCOS], coco_vy [MAX_COCOS];
	unsigned char coco_it, coco_d, coco_x0;
#endif
	
unsigned char pregotten;
#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
	unsigned char enemy_shoots;
#endif

#ifdef ENEMS_MAY_DIE
	unsigned char enemy_was_killed;
#endif

// Bullets

#ifdef PLAYER_CAN_FIRE
	unsigned char bullets_x [MAX_BULLETS];
	unsigned char bullets_y [MAX_BULLETS];
	signed char bullets_mx [MAX_BULLETS];
	signed char bullets_my [MAX_BULLETS];
	unsigned char bullets_estado [MAX_BULLETS];
	#ifdef LIMITED_BULLETS
		unsigned char bullets_life [MAX_BULLETS];
	#endif	
#endif

#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	unsigned char hitter_on;
	unsigned char hitter_type;
	unsigned char hitter_frame;
	unsigned char hitter_x, hitter_y;
	unsigned char *hitter_c_f, *hitter_n_f;
	unsigned char hitter_hit;
#endif

// Current screen buffers
unsigned char map_attr [150];
// There's XXX bytes free at FREEPOOL according to splib2's doc.
// (240 if in 128K mode, 512 - stack size (do not risk!) in 48K mode)
// Why not use them?
unsigned char map_buff [150] @ FREEPOOL;
//

// Current screen hotspot
unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char orig_tile;
unsigned char do_respawn; 
unsigned char no_draw; 

// Flags para scripting
#if defined (ACTIVATE_SCRIPTING) || defined (TILE_GET) || defined (ENABLE_SIM)
	unsigned char flags[MAX_FLAGS];
#endif

// Globalized
unsigned char n_pant, o_pant;
unsigned char level = 0;
unsigned char silent_level;
unsigned char is_rendering;

unsigned char maincounter;

// Breakable walls/etc
#if (defined BREAKABLE_WALLS || defined BREAKABLE_WALLS_SIMPLE) && defined BREAKABLE_ANIM
	// Store this in the free memory pool (see ^)
	unsigned char breaking_x [MAX_BREAKABLE] @ FREEPOOL + 150;
	unsigned char breaking_y [MAX_BREAKABLE] @ FREEPOOL + 150 + MAX_BREAKABLE;
	unsigned char breaking_f [MAX_BREAKABLE] @ FREEPOOL + 150 + MAX_BREAKABLE + MAX_BREAKABLE;

	unsigned char breaking_idx = 0;
	unsigned char do_process_breakable = 0;
#endif

#ifdef BREAKABLE_WALLS
	unsigned char brk_buff [150];
#endif

// Fire zone
#ifdef ENABLE_FIRE_ZONE
	unsigned char fzx1, fzy1, fzx2, fzy2, f_zone_ac;
#endif

// Timer
#ifdef TIMER_ENABLE
	typedef struct {
		unsigned char on;
		unsigned char t;
		unsigned char frames;
		unsigned char count;
		unsigned char zero;
	} CTIMER;
	CTIMER ctimer;
#endif

#if defined (ACTIVATE_SCRIPTING) && defined (ENABLE_PUSHED_SCRIPTING)
	unsigned char just_pushed;
#endif

#ifdef USE_TWO_BUTTONS
	signed int key_jump, key_fire;
#endif

#if defined (ENABLE_SIM)
	unsigned char key_z_pressed = 0;
#endif

#if defined (PLAYER_CHECK_MAP_BOUNDARIES) || defined (PLAYER_CYCLIC_MAP)
	unsigned char x_pant, y_pant;
#endif

unsigned char do_gravity = 1, p_engine;

#ifdef ENABLE_SIM
	unsigned char items [SIM_DISPLAY_MAXITEMS];
	void display_items (void);
#endif

unsigned char enoffsmasi;

#ifdef SCRIPTING_KEY_FIRE
	unsigned char invalidate_fire = 0;
#endif

#ifdef MAP_ATTRIBUTES
	unsigned char cur_map_attr = 99;
#endif

// Engine globals (for speed) & size!

unsigned char gpx, gpy, gpd, gpc, gpt, gps, rdx, rdy, rda, rdb;
signed char rds;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpaux;
unsigned char _en_x, _en_y, _en_x1, _en_y1, _en_x2, _en_y2, _en_t, _en_life;
signed char _en_mx, _en_my;
unsigned char *_baddies_pointer;
unsigned char tocado, active, killable, animate;
unsigned char gpit, gpjt;
unsigned char *map_pointer;
unsigned char enit;
signed int _val, _min, _max;

#if defined USE_AUTO_TILE_SHADOWS || defined USE_AUTO_SHADOWS
	unsigned char c1, c2, c3, c4;
	unsigned char t1, t2, t3, t4;
	unsigned char nocast, _ta;
	unsigned char xx, yy;
#endif
#ifdef USE_AUTO_TILE_SHADOWS
	unsigned a1, a2, a3;
	unsigned char *gen_pt_alt;
	unsigned char t_alt;
#endif

// Undo parameters
unsigned char _x, _y, _t, _n;
unsigned char *gp_gen;
#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
	unsigned char x0, y0, x1, y1;
#endif

#ifdef ENABLE_TILANIMS
	unsigned char tait;
	unsigned char max_tilanims;
	unsigned char tacount;
	unsigned char tilanims_xy [MAX_TILANIMS];
	unsigned char tilanims_ft [MAX_TILANIMS];
#endif

#ifdef MIN_FAPS_PER_FRAME
	unsigned char isrc @ ISRC_ADDRESS;
#endif

unsigned char pad0, pad_this_frame;

#ifdef CUSTOM_HIT
	unsigned char was_hit_by_type;
#endif

unsigned char action_pressed;

#ifdef GET_X_MORE
	unsigned char *getxmore = " GET X MORE ";
#endif

#ifdef COMPRESSED_LEVELS
	unsigned char mlplaying;
#endif

unsigned char success;
unsigned char playing;

#ifdef SHOW_FPS
	unsigned char game_frame_counter;
	unsigned char tv_frame_counter;
#endif
	
#ifdef MODE_128K
	unsigned char song_playing;
#endif

#ifdef ENABLE_TILANIMS
	#if TILANIMS_PERIOD > 1
		unsigned char tilanims_counter;
	#endif
	#if defined (TILANIMS_SEVERAL_TYPES) && !defined (TILANIMS_TYPE_SELECT_FLAG)
		unsigned char tilanims_type_select;
	#endif
#endif
