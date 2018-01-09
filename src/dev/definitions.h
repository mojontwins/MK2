// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// definitions.h
// Main definitions

// General defines

#define EST_NORMAL 		0
#define EST_PARP 		2
#define EST_MUR 		4
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

// Sound effects. Alter here and you are done!
#define SFX_PUSH_BOX	2
#define SFX_LOCK		8
#define SFX_BREAK_WALL	10
#define SFX_BREAK_WALL_ANIM 10
#define SFX_SHOOT		9
#define SFX_KILL_ENEMY	2
#define SFX_ENEMY_HIT	2
#define SFX_EXPLOSION	10
#define SFX_CONTAINER	6
#define SFX_FO_DRAIN	2
#define SFX_FO_DESTROY	10
#define SFX_FO_DROP		2
#define SFX_FO_GET		2
#define SFX_JUMP 		1
#define SFX_JUMP_ALT 	1
#define SFX_TILE_GET 	5
#define SFX_HITTER_HIT 	2
#define SFX_FALL_HOLE 	9
#define SFX_KS_TICK 	4
#define SFX_KS_DRAIN 	3
#define SFX_REFILL 		7
#define SFX_OBJECT 		6
#define SFX_KEY 		6
#define SFX_AMMO		6
#define SFX_TIME		6
#define SFX_FUEL		6
#define SFX_WRONG 		2
#define SFX_INVENTORY 	2
#define SFX_PLAYER_DEATH_BOMB 2
#define SFX_PLAYER_DEATH_COCO 2
#define SFX_PLAYER_DEATH_ENEMY 2
#define SFX_PLAYER_DEATH_SPIKE 3
#define SFX_PLAYER_DEATH_HOLE 10
#define SFX_PLAYER_DEATH_TIME 2
#define SFX_PLAYER_DEATH_LAVA 10
#define SFX_ENDING_LAME_1 2
#define SFX_ENDING_LAME_2 3
#define SFX_ENDING_LAME_WIN 6
#define SFX_ENDING_LAME_LOSE 10

// General externs

extern unsigned int asm_int [1];
extern unsigned int asm_int_2 [1];

#asm
._asm_int
	defw 0
._asm_int_2
	defw 0
#endasm

// Gigaglobals

struct sp_UDK keys;
void *joyfunc;				

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

struct sp_Rect spritesClipValues;
struct sp_Rect *spritesClip;

unsigned char enoffs;

// Aux

unsigned char half_life = 0;

// Player
int p_x, p_y;
#if defined (PHANTOMAS_ENGINE)
char p_vx, p_vy, ptgmx, ptgmy;
#elif defined (HANNA_ENGINE)
char p_v;
#else
int p_vx, p_vy, ptgmx, ptgmy;
#endif
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
int p_z, p_vz;
unsigned char p_jmp_facing, gpz;
#endif
char p_g;
#if defined (PLAYER_NEW_GENITAL) && defined (ENABLE_BEH_64) 
char p_ax, p_rx;
#endif
#ifdef PLAYER_GENITAL
char p_thrust;
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
#ifdef DIE_AND_RESPAWN
unsigned char p_killme, p_safe_pant, p_safe_x, p_safe_y;
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

// Make some player values variable. Preliminary, just the maximum jump speed...

#ifdef PLAYER_VARIABLE_JUMP
int PLAYER_JMP_VY_MAX;
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
int en_an_x [3];
int en_an_y [3];
int en_an_vx [3];
int en_an_vy [3];
#ifdef RANDOM_RESPAWN
unsigned char en_an_fanty_activo [3];
#endif
#endif

#ifdef ENABLE_PURSUERS
unsigned char en_an_alive [3];
unsigned char en_an_dead_row [3];
unsigned char en_an_rawv [3];
#endif

#ifdef ENABLE_HANNA_MONSTERS_11
unsigned char en_an_dir [3];
#endif

// Bullets

#ifdef PLAYER_CAN_FIRE
unsigned char bullets_x [MAX_BULLETS];
unsigned char bullets_y [MAX_BULLETS];
unsigned char bullets_mx [MAX_BULLETS];
unsigned char bullets_my [MAX_BULLETS];
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
//unsigned char map_buff [150];
// There's XXX bytes free at FREEPOOL according to splib2's doc.
// (240 if in 128K mode, 512 - stack size (do not risk!) in 48K mode)
// Why not use them?
unsigned char *map_buff = FREEPOOL;
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

unsigned char maincounter;

// Breakable walls/etc
#ifdef BREAKABLE_WALLS
unsigned char brk_buff [150];
#ifdef BREAKABLE_ANIM
// Store this in the free memory pool (see ^)
unsigned char *breaking_x = FREEPOOL + 150;
unsigned char *breaking_y = FREEPOOL + 150 + MAX_BREAKABLE;
unsigned char *breaking_f = FREEPOOL + 150 + MAX_BREAKABLE + MAX_BREAKABLE;

unsigned char breaking_idx = 0;
unsigned char do_process_breakable = 0;
#endif
#endif

#ifdef BREAKABLE_WALLS_SIMPLE
#ifdef BREAKABLE_ANIM
unsigned char *breaking_x = FREEPOOL + 150;
unsigned char *breaking_y = FREEPOOL + 150 + MAX_BREAKABLE;
unsigned char *breaking_f = FREEPOOL + 150 + MAX_BREAKABLE + MAX_BREAKABLE;
//

unsigned char breaking_idx = 0;
unsigned char do_process_breakable = 0;
#endif
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
int key_jump, key_fire;
#endif

#ifdef SCRIPTING_KEY_M
int key_m;
#endif

#ifdef PAUSE_ABORT
int key_h, key_y;
#endif

#if defined (ENABLE_SIM)
int key_z;
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

unsigned char gpx, gpy, gpd, gpc, gpt, gps;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpen_xx, gpen_yy, gpaux;
unsigned char tocado, active, killable, animate;
unsigned char gpit, gpjt;
unsigned char *map_pointer;

// Needed prototypes

#ifdef ACTIVATE_SCRIPTING
void __FASTCALL__ draw_scr_background (void);
void __FASTCALL__ draw_scr (void);
#endif
void active_sleep (int espera);
void run_fire_script (void);

#ifdef MODE_128K
void blackout_area (void);
void get_resource (unsigned char res, unsigned int dest);

void __FASTCALL__ _AY_PL_SND (unsigned char fx_number);
void __FASTCALL__ _AY_PL_MUS (unsigned char song_number);
#endif

#ifdef ENABLE_FLOATING_OBJECTS
unsigned char FO_add (unsigned char x, unsigned char y, unsigned char t);
void FO_paint (unsigned char idx);
void FO_paint_all (void);
#endif

void cortina (void);
unsigned char rand (void);
void hide_sprites (unsigned char which_ones);
void draw_coloured_tile (unsigned char x, unsigned char y, unsigned char t);
unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
unsigned char collide_pixel (unsigned char x, unsigned char y, unsigned char x1, unsigned char y1);

// CUSTOM FOR K2T
void update_hud ();
