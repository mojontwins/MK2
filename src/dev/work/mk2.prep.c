# 1 "mk2.c"

# 26 "c:\z88dk10\include/spritepack.h"
typedef unsigned char uchar;
typedef unsigned int uint;




extern void *u_malloc;
extern void *u_free;
# 133
struct sp_SS {
uchar row;
uchar col;
uchar height;
uchar width;
uchar hor_rot;
uchar ver_rot;
uchar *first;
uchar *last_col;
uchar *last;
uchar plane;
uchar type;
};




struct sp_CS {
uchar *next_in_spr;
uchar *prev;
uchar spr_attr;
uchar *left_graphic;
uchar *graphic;
uchar hor_rot;
uchar colour;
uchar *next;
uchar unused;
};




struct sp_Rect {
uchar row_coord;
uchar col_coord;
uchar height;
uchar width;
};




struct sp_PSS {
struct sp_Rect *bounds;
uchar flags;
uchar x;
uchar y;
uchar colour;
void *dlist;
void *dirtychars;
uchar dirtybit;
};




struct sp_LargeRect {
uint top;
uint bottom;
uint left;
uint right;
};

struct sp_Interval {
uint x1;
uint x2;
};




struct sp_UDK {
uint fire;
uint right;
uint left;
uint down;
uint up;
};




struct sp_MD {
uchar maxcount;
uint dx;
uint dy;
};

struct sp_UDM {
struct sp_UDK *keys;
void *joyfunc;
struct sp_MD **delta;
uchar state;
uchar count;
uint y;
uint x;
};




struct sp_ListNode {
void *item;
struct sp_ListNode *next;
struct sp_ListNode *prev;
};

struct sp_List {
uint count;
uchar state;
struct sp_ListNode *current;
struct sp_ListNode *head;
struct sp_ListNode *tail;
};




struct sp_HashCell {
void *key;
void *value;
struct sp_HashCell *next;
};

struct sp_HashTable {
uint size;
struct sp_HashCell **table;
void *hashfunc;
void *match;
void *delete;
};




struct sp_HuffmanJoin {
union {
uint freq;
void *parent;
} u;
void *left;
void *right;
};

struct sp_HuffmanLeaf {
union {
uint freq;
void *parent;
} u;
uint c;
};

struct sp_HuffmanCodec {
uint symbols;
void *addr;
uchar bit;
void *root;
union {
struct sp_HuffmanLeaf **heap;
struct sp_HuffmanLeaf **encoder;

} u;
};
# 398
extern void __LIB__ sp_InitIM2(void *default_isr);
extern void __LIB__ *sp_InstallISR(uchar vector, void *isr);
extern void __LIB__ sp_EmptyISR(void);
extern void __LIB__ *sp_CreateGenericISR(void *addr);
extern void __LIB__ sp_RegisterHook(uchar vector, void *hook);
extern void __LIB__ sp_RegisterHookFirst(uchar vector, void *hook);
extern void __LIB__ sp_RegisterHookLast(uchar vector, void *hook);
extern int __LIB__ sp_RemoveHook(uchar vector, void *hook);




extern void __LIB__ sp_Initialize(uchar colour, uchar udg);
extern void __LIB__ *sp_SwapEndian(void *ptr);
extern void __LIB__ sp_Swap(void *addr1, void *addr2, uint bytes);
extern int __LIB__ sp_PFill(uint xcoord, uchar ycoord, void *pattern, uint stackdepth);
extern int __LIB__ sp_StackSpace(void *addr);
extern uint __LIB__ sp_Random32(uint *hi);
extern void __LIB__ sp_Border(uchar colour);
extern uchar __LIB__ sp_inp(uint port);
extern void __LIB__ sp_outp(uint port, uchar value);




extern int __LIB__ sp_IntRect(struct sp_Rect *r1, struct sp_Rect *r2, struct sp_Rect *result);
extern int __LIB__ sp_IntLargeRect(struct sp_LargeRect *r1, struct sp_LargeRect *r2, struct sp_LargeRect *result);
extern int __LIB__ sp_IntPtLargeRect(uint x, uint y, struct sp_LargeRect *r);
extern int __LIB__ sp_IntIntervals(struct sp_Interval *i1, struct sp_Interval *i2, struct sp_Interval *result);
extern int __LIB__ sp_IntPtInterval(uint x, struct sp_Interval *i);




extern struct sp_SS __LIB__ *sp_CreateSpr(uchar type, uchar rows, void *graphic, uchar plane, uchar extra);
extern int __LIB__ sp_AddColSpr(struct sp_SS *sprite, void *graphic, uchar extra);
extern void __LIB__ sp_DeleteSpr(struct sp_SS *sprite);
extern void __LIB__ sp_IterateSprChar(struct sp_SS *sprite, void *hook);

extern void __LIB__ sp_RemoveDList(struct sp_SS *sprite);
extern void __LIB__ sp_MoveSprAbs(struct sp_SS *sprite, struct sp_Rect *clip, int animate, uchar row, uchar col, uchar hpix, uchar vpix);
extern void __LIB__ sp_MoveSprAbsC(struct sp_SS *sprite, struct sp_Rect *clip, int animate, uchar row, uchar col, uchar hpix, uchar vpix);
extern void __LIB__ sp_MoveSprAbsNC(struct sp_SS *sprite, struct sp_Rect *clip, int animate, uchar row, uchar col, uchar hpix, uchar vpix);
extern void __LIB__ sp_MoveSprRel(struct sp_SS *sprite, struct sp_Rect *clip, int animate, char rel_row, char rel_col, char rel_hpix, char rel_vpix);
extern void __LIB__ sp_MoveSprRelC(struct sp_SS *sprite, struct sp_Rect *clip, int animate, char rel_row, char rel_col, char rel_hpix, char rel_vpix);
extern void __LIB__ sp_MoveSprRelNC(struct sp_SS *sprite, struct sp_Rect *clip, int animate, char rel_row, char rel_col, char rel_hpix, char rel_vpix);




extern void __LIB__ sp_PrintAt(uchar row, uchar col, uchar colour, uchar udg);
extern void __LIB__ sp_PrintAtInv(uchar row, uchar col, uchar colour, uchar udg);
extern uint __LIB__ sp_ScreenStr(uchar row, uchar col);
extern void __LIB__ sp_PrintAtDiff(uchar row, uchar col, uchar colour, uchar udg);
extern void __LIB__ sp_PrintString(struct sp_PSS *ps, uchar *s);
extern void __LIB__ sp_ComputePos(struct sp_PSS *ps, uchar x, uchar y);
extern void __LIB__ *sp_TileArray(uchar c, void *addr);
extern void __LIB__ *sp_Pallette(uchar c, void *addr);
extern void __LIB__ sp_GetTiles(struct sp_Rect *r, void *dest);
extern void __LIB__ sp_PutTiles(struct sp_Rect *r, void *src);
extern void __LIB__ sp_IterateDList(struct sp_Rect *r, void *hook);
# 464
extern void __LIB__ *sp_AddMemory(uchar queue, uchar number, uint size, void *addr);
extern void __LIB__ *sp_BlockAlloc(uchar queue);
extern void __LIB__ *sp_BlockFit(uchar queue, uchar numcheck);
extern void __LIB__ sp_FreeBlock(void *addr);
extern void __LIB__ sp_InitAlloc(void);
extern uint __LIB__ sp_BlockCount(uchar queue);




extern void __LIB__ sp_Invalidate(struct sp_Rect *area, struct sp_Rect *clip);
extern void __LIB__ sp_Validate(struct sp_Rect *area, struct sp_Rect *clip);
extern void __LIB__ sp_ClearRect(struct sp_Rect *area, uchar colour, uchar udg, uchar flags);
extern void __LIB__ sp_UpdateNow();
extern void __LIB__ *sp_CompDListAddr(uchar row, uchar col);
extern void __LIB__ *sp_CompDirtyAddr(uchar row, uchar col, uchar *mask);




extern uchar __LIB__ sp_JoySinclair1(void);
extern uchar __LIB__ sp_JoySinclair2(void);
extern uchar __LIB__ sp_JoyTimexEither(void);
extern uchar __LIB__ sp_JoyTimexLeft(void);
extern uchar __LIB__ sp_JoyTimexRight(void);
extern uchar __LIB__ sp_JoyFuller(void);
extern uchar __LIB__ sp_JoyKempston(void);
extern uchar __LIB__ sp_JoyKeyboard(struct sp_UDK *keys);
extern void __LIB__ sp_WaitForKey(void);
extern void __LIB__ sp_WaitForNoKey(void);
extern uint __LIB__ sp_Pause(uint ticks);
extern void __LIB__ sp_Wait(uint ticks);
extern uint __LIB__ sp_LookupKey(uchar c);
extern uchar __LIB__ sp_GetKey(void);
extern uchar __LIB__ sp_Inkey(void);
extern int __LIB__ sp_KeyPressed(uint scancode);
extern void __LIB__ sp_MouseAMXInit(uchar xvector, uchar yvector);
extern void __LIB__ sp_MouseAMX(uint *xcoord, uchar *ycoord, uchar *buttons);
extern void __LIB__ sp_SetMousePosAMX(uint xcoord, uchar ycoord);
extern void __LIB__ sp_MouseKempston(uint *xcoord, uchar *ycoord, uchar *buttons);
extern void __LIB__ sp_SetMousePosKempston(uint xcoord, uchar ycoord);
extern void __LIB__ sp_MouseSim(struct sp_UDM *m, uint *xcoord, uchar *ycoord, uchar *buttons);
extern void __LIB__ sp_SetMousePosSim(struct sp_UDM *m, uint xcoord, uchar ycoord);




extern void __LIB__ *sp_CharDown(void *scrnaddr);
extern void __LIB__ *sp_CharLeft(void *scrnaddr);
extern void __LIB__ *sp_CharRight(void *scrnaddr);
extern void __LIB__ *sp_CharUp(void *scrnaddr);
extern void __LIB__ *sp_GetAttrAddr(void *scrnaddr);
extern void __LIB__ *sp_GetCharAddr(uchar row, uchar col);
extern void __LIB__ *sp_GetScrnAddr(uint xcoord, uchar ycoord, uchar *mask);
extern void __LIB__ *sp_PixelDown(void *scrnaddr);
extern void __LIB__ *sp_PixelUp(void *scrnaddr);
extern void __LIB__ *sp_PixelLeft(void *scrnaddr, uchar *mask);
extern void __LIB__ *sp_PixelRight(void *scrnaddr, uchar *mask);
# 540
extern struct sp_List __LIB__ *sp_ListCreate(void);
extern uint __LIB__ sp_ListCount(struct sp_List *list);
extern void __LIB__ *sp_ListFirst(struct sp_List *list);
extern void __LIB__ *sp_ListLast(struct sp_List *list);
extern void __LIB__ *sp_ListNext(struct sp_List *list);
extern void __LIB__ *sp_ListPrev(struct sp_List *list);
extern void __LIB__ *sp_ListCurr(struct sp_List *list);
extern int __LIB__ sp_ListAdd(struct sp_List *list, void *item);
extern int __LIB__ sp_ListInsert(struct sp_List *list, void *item);
extern int __LIB__ sp_ListAppend(struct sp_List *list, void *item);
extern int __LIB__ sp_ListPrepend(struct sp_List *list, void *item);
extern void __LIB__ *sp_ListRemove(struct sp_List *list);
extern void __LIB__ sp_ListConcat(struct sp_List *list1, struct sp_List *list2);
extern void __LIB__ sp_ListFree(struct sp_List *list, void *free);

extern void __LIB__ *sp_ListTrim(struct sp_List *list);
extern void __LIB__ *sp_ListSearch(struct sp_List *list, void *match, void *item1);
# 562
extern struct sp_HashTable __LIB__ *sp_HashCreate(uint size, void *hashfunc, void *match, void *delete);
extern struct sp_HashCell __LIB__ *sp_HashRemove(struct sp_HashTable *ht, void *key);
extern void __LIB__ *sp_HashLookup(struct sp_HashTable *ht, void *key);
extern void __LIB__ *sp_HashAdd(struct sp_HashTable *ht, void *key, void *value);
extern void __LIB__ sp_HashDelete(struct sp_HashTable *ht);
# 579
extern void __LIB__ sp_Heapify(void **array, uint n, void *compare);
extern void __LIB__ sp_HeapSiftDown(uint start, void **array, uint n, void *compare);
extern void __LIB__ sp_HeapSiftUp(uint start, void **array, void *compare);
extern void __LIB__ sp_HeapAdd(void *item, void **array, uint n, void *compare);
extern void __LIB__ sp_HeapExtract(void **array, uint n, void *compare);
# 611
extern struct sp_HuffmanCodec __LIB__ *sp_HuffCreate(uint symbols);
extern void __LIB__ sp_HuffDelete(struct sp_HuffmanCodec *hc);
extern void __LIB__ sp_HuffAccumulate(struct sp_HuffmanCodec *hc, uchar c);
extern int __LIB__ sp_HuffExtract(struct sp_HuffmanCodec *hc, uint n);

extern void __LIB__ sp_HuffSetState(struct sp_HuffmanCodec *hc, void *addr, uchar bit);
extern void __LIB__ *sp_HuffGetState(struct sp_HuffmanCodec *hc, uchar *bit);
extern uchar __LIB__ sp_HuffDecode(struct sp_HuffmanCodec *hc);
extern void __LIB__ sp_HuffEncode(struct sp_HuffmanCodec *hc, uchar c);
#asm
# 12 "mk2.c"
LIB SPMoveSprAbs
LIB SPPrintAtInv
LIB SPTileArray
LIB SPInvalidate
LIB SPCompDListAddr
#endasm

#pragma  output STACKPTR=61952
# 550 "config.h"
unsigned char behs [] = {
0, 8, 0, 0, 0, 0, 0, 4, 8, 0, 0, 8, 0, 0, 0, 0,
0,24, 8, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
# 85 "definitions.h"
unsigned int asm_int;
unsigned int asm_int_2;



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
#asm
# 123
.vpClipStruct defb 1, 1 + 20, 1, 1 + 30
#endasm


unsigned char enoffs;



unsigned char half_life = 0;


int p_x, p_y;
# 139
int p_vx, p_vy, ptgmx, ptgmy;
# 145
char p_g;
# 152
unsigned char p_jmp_ct;
unsigned char *p_c_f, *p_n_f;
unsigned char p_jmp_on;
unsigned char p_frame, p_subframe, p_facing;
unsigned char p_state;
unsigned char p_state_ct;
unsigned char p_gotten;
unsigned char p_life, p_objs, p_keys;

unsigned char p_killed;

unsigned char p_disparando;
# 170
unsigned char p_facing_v, p_facing_h;
# 199
unsigned char en_an_base_frame [3];

unsigned char en_an_count [3];
unsigned char *en_an_c_f [3], *en_an_n_f [3];
unsigned char en_an_state [3];
# 214
int en_an_x [3];
int en_an_y [3];
int en_an_vx [3];
int en_an_vy [3];
# 256
unsigned char map_attr [150];




unsigned char *map_buff = 61440;



unsigned char hotspot_x;
unsigned char hotspot_y;
unsigned char orig_tile;
unsigned char do_respawn;
unsigned char no_draw;



unsigned char flags[32];



unsigned char n_pant, o_pant;
unsigned char level = 0;
unsigned char silent_level;
unsigned char is_rendering;

unsigned char maincounter;
# 312
unsigned char fzx1, fzy1, fzx2, fzy2, f_zone_ac;
# 349
unsigned char x_pant, y_pant;


unsigned char do_gravity = 1, p_engine;
# 359
unsigned char enoffsmasi;
# 371
unsigned char gpx, gpy, gpd, gpc, gpt, gps, rdx, rdy, rda, rdb;
unsigned char gpxx, gpyy, gpcx, gpcy;
unsigned char possee, hit_v, hit_h, hit, wall_h, wall_v;
unsigned char gpen_x, gpen_y, gpen_cx, gpen_cy, gpen_xx, gpen_yy, gpaux;
unsigned char tocado, active, killable, animate;
unsigned char gpit, gpjt;
unsigned char *map_pointer;
# 391
unsigned char _x, _y, _t, _n;
unsigned char *gp_gen;




void __FASTCALL__ draw_scr_background (void);
void __FASTCALL__ draw_scr (void);

void active_sleep (int espera);
void run_fire_script (void);
# 418
void tilanims_add (void);
void tilanims_do (void);


void cortina (void);
unsigned char rand (void);
void hide_sprites (unsigned char which_ones);
void draw_coloured_tile (void);
void draw_coloured_tile_gamearea (void);
unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);
unsigned char collide_pixel (unsigned char x, unsigned char y, unsigned char x1, unsigned char y1);


void update_hud ();
# 5 "my/msc-config.h"
unsigned char sc_x, sc_y, sc_n, sc_m, sc_c;
unsigned char script_result = 0;
unsigned char sc_terminado = 0;
unsigned char sc_continuar = 0;
unsigned int main_script_offset;

extern unsigned char main_script [0];
#asm

._main_script
BINARY "../bin/scripts.bin"
#endasm


unsigned char warp_to_level;
extern unsigned char *script;
#asm

._script defw 0
#endasm
# 7 "system/aplib.h"
extern unsigned int ram_address [];
extern unsigned int ram_destination [];
#asm
# 14
; aPPack decompressor
; original source by dwedit
; very slightly adapted by utopian
; optimized by Metalbrain

;hl = source
;de = dest

.depack ld ixl,128
.apbranch1 ldi
.aploop0 ld ixh,1 ;LWM = 0
.aploop call ap_getbit
jr nc,apbranch1
call ap_getbit
jr nc,apbranch2
ld b,0
call ap_getbit
jr nc,apbranch3
ld c,16 ;get an offset
.apget4bits call ap_getbit
rl c
jr nc,apget4bits
jr nz,apbranch4
ld a,b
.apwritebyte ld (de),a ;write a 0
inc de
jr aploop0
.apbranch4 and a
ex de,hl ;write a previous byte (1-15 away from dest)
sbc hl,bc
ld a,(hl)
add hl,bc
ex de,hl
jr apwritebyte
.apbranch3 ld c,(hl) ;use 7 bit offset, length = 2 or 3
inc hl
rr c
ret z ;if a zero is encountered here, it is EOF
ld a,2
adc a,b
push hl
ld iyh,b
ld iyl,c
ld h,d
ld l,e
sbc hl,bc
ld c,a
jr ap_finishup2
.apbranch2 call ap_getgamma ;use a gamma code * 256 for offset, another gamma code for length
dec c
ld a,c
sub ixh
jr z,ap_r0_gamma ;if gamma code is 2, use old r0 offset,
dec a
;do I even need this code?
;bc=bc*256+(hl), lazy 16bit way
ld b,a
ld c,(hl)
inc hl
ld iyh,b
ld iyl,c

push bc

call ap_getgamma

ex (sp),hl ;bc = len, hl=offs
push de
ex de,hl

ld a,4
cp d
jr nc,apskip2
inc bc
or a
.apskip2 ld hl,127
sbc hl,de
jr c,apskip3
inc bc
inc bc
.apskip3 pop hl ;bc = len, de = offs, hl=junk
push hl
or a
.ap_finishup sbc hl,de
pop de ;hl=dest-offs, bc=len, de = dest
.ap_finishup2 ldir
pop hl
ld ixh,b
jr aploop

.ap_r0_gamma call ap_getgamma ;and a new gamma code for length
push hl
push de
ex de,hl

ld d,iyh
ld e,iyl
jr ap_finishup


.ap_getbit ld a,ixl
add a,a
ld ixl,a
ret nz
ld a,(hl)
inc hl
rla
ld ixl,a
ret

.ap_getgamma ld bc,1
.ap_getgammaloop call ap_getbit
rl c
rl b
call ap_getbit
jr c,ap_getgammaloop
ret
#endasm
#asm




._ram_address
defw 0
._ram_destination
defw 0
#endasm
#asm
#endasm
#asm
#endasm
# 167
void unpack (unsigned int address, unsigned int destination) {
if (address != 0) {
ram_address [0] = address;
ram_destination [0] = destination;
#asm


ld hl, (_ram_address)
ld de, (_ram_destination)
call depack
#endasm

}
}
# 8 "assets/pantallas.h"
extern unsigned char s_title [];
extern unsigned char s_marco [];
extern unsigned char s_ending [];
#asm


._s_title
BINARY "../bin/title.bin"
._s_marco
#endasm
#asm
#endasm
#asm
# 23
._s_ending
BINARY "../bin/ending.bin"
#endasm
# 8 "assets/mapa.h"
extern unsigned char map [0];
#asm


._map
BINARY "../bin/map.bin"
#endasm



typedef struct {
unsigned char np, x, y, st;
} BOLTS;
#asm
#endasm
# 8 "assets/tileset.h"
extern unsigned char tileset [0];
#asm

._tileset
BINARY "../bin/ts.bin"
#endasm
# 5 "assets/sprites.h"
extern unsigned char sprite_1_a [];
extern unsigned char sprite_1_b [];
extern unsigned char sprite_1_c [];
extern unsigned char sprite_2_a [];
extern unsigned char sprite_2_b [];
extern unsigned char sprite_2_c [];
extern unsigned char sprite_3_a [];
extern unsigned char sprite_3_b [];
extern unsigned char sprite_3_c [];
extern unsigned char sprite_4_a [];
extern unsigned char sprite_4_b [];
extern unsigned char sprite_4_c [];
extern unsigned char sprite_5_a [];
extern unsigned char sprite_5_b [];
extern unsigned char sprite_5_c [];
extern unsigned char sprite_6_a [];
extern unsigned char sprite_6_b [];
extern unsigned char sprite_6_c [];
extern unsigned char sprite_7_a [];
extern unsigned char sprite_7_b [];
extern unsigned char sprite_7_c [];
extern unsigned char sprite_8_a [];
extern unsigned char sprite_8_b [];
extern unsigned char sprite_8_c [];
extern unsigned char sprite_9_a [];
extern unsigned char sprite_9_b [];
extern unsigned char sprite_9_c [];
extern unsigned char sprite_10_a [];
extern unsigned char sprite_10_b [];
extern unsigned char sprite_10_c [];
extern unsigned char sprite_11_a [];
extern unsigned char sprite_11_b [];
extern unsigned char sprite_11_c [];
extern unsigned char sprite_12_a [];
extern unsigned char sprite_12_b [];
extern unsigned char sprite_12_c [];
extern unsigned char sprite_13_a [];
extern unsigned char sprite_13_b [];
extern unsigned char sprite_13_c [];
extern unsigned char sprite_14_a [];
extern unsigned char sprite_14_b [];
extern unsigned char sprite_14_c [];
extern unsigned char sprite_15_a [];
extern unsigned char sprite_15_b [];
extern unsigned char sprite_15_c [];
extern unsigned char sprite_16_a [];
extern unsigned char sprite_16_b [];
extern unsigned char sprite_16_c [];
extern unsigned char sprite_e [];
#asm


defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_1_a
defb 0, 224
defb 31, 192
defb 15, 224
defb 31, 192
defb 28, 192
defb 59, 128
defb 59, 128
defb 123, 0
defb 124, 0
defb 127, 0
defb 111, 0
defb 31, 128
defb 63, 128
defb 31, 128
defb 47, 128
defb 0, 192
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_1_b
defb 0, 63
defb 192, 15
defb 240, 7
defb 240, 7
defb 64, 3
defb 184, 3
defb 48, 3
defb 48, 1
defb 68, 1
defb 254, 0
defb 254, 0
defb 142, 0
defb 254, 0
defb 252, 1
defb 248, 3
defb 0, 7
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_1_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_2_a
defb 0, 136
defb 55, 128
defb 31, 192
defb 31, 192
defb 28, 192
defb 59, 128
defb 58, 128
defb 122, 0
defb 124, 0
defb 127, 0
defb 111, 0
defb 31, 128
defb 63, 128
defb 57, 128
defb 22, 192
defb 0, 224
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_2_b
defb 0, 63
defb 192, 15
defb 240, 7
defb 240, 7
defb 64, 3
defb 184, 3
defb 32, 3
defb 32, 1
defb 68, 1
defb 254, 0
defb 254, 0
defb 30, 0
defb 254, 0
defb 252, 1
defb 248, 3
defb 0, 7
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_2_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_3_a
defb 0, 24
defb 103, 0
defb 63, 128
defb 31, 192
defb 28, 192
defb 59, 128
defb 56, 128
defb 120, 0
defb 124, 0
defb 111, 0
defb 55, 128
defb 15, 192
defb 63, 128
defb 62, 128
defb 29, 192
defb 0, 224
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_3_b
defb 0, 63
defb 192, 15
defb 240, 7
defb 240, 7
defb 64, 3
defb 184, 3
defb 136, 3
defb 136, 1
defb 68, 1
defb 254, 0
defb 254, 0
defb 62, 0
defb 254, 0
defb 60, 1
defb 216, 3
defb 0, 7
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_3_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_4_a
defb 0, 248
defb 3, 240
defb 12, 224
defb 11, 128
defb 90, 0
defb 90, 0
defb 124, 0
defb 127, 0
defb 60, 0
defb 24, 128
defb 56, 128
defb 24, 192
defb 28, 192
defb 3, 128
defb 120, 0
defb 0, 135
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_4_b
defb 0, 63
defb 192, 15
defb 64, 7
defb 184, 3
defb 32, 3
defb 32, 3
defb 68, 1
defb 252, 1
defb 124, 1
defb 56, 1
defb 54, 0
defb 54, 0
defb 118, 0
defb 230, 0
defb 0, 25
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_4_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_5_a
defb 0, 252
defb 3, 240
defb 15, 224
defb 15, 224
defb 2, 192
defb 29, 192
defb 12, 192
defb 12, 128
defb 34, 128
defb 127, 0
defb 127, 0
defb 113, 0
defb 127, 0
defb 63, 128
defb 31, 192
defb 0, 224
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_5_b
defb 0, 7
defb 248, 3
defb 240, 7
defb 248, 3
defb 56, 3
defb 220, 1
defb 220, 1
defb 222, 0
defb 62, 0
defb 254, 0
defb 246, 0
defb 248, 1
defb 252, 1
defb 248, 1
defb 244, 1
defb 0, 3
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_5_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_6_a
defb 0, 252
defb 3, 240
defb 15, 224
defb 15, 224
defb 2, 192
defb 29, 192
defb 4, 192
defb 4, 128
defb 34, 128
defb 127, 0
defb 127, 0
defb 120, 0
defb 127, 0
defb 63, 128
defb 31, 192
defb 0, 224
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_6_b
defb 0, 17
defb 236, 1
defb 248, 3
defb 248, 3
defb 56, 3
defb 220, 1
defb 92, 1
defb 94, 0
defb 62, 0
defb 254, 0
defb 246, 0
defb 248, 1
defb 252, 1
defb 156, 1
defb 104, 3
defb 0, 7
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_6_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_7_a
defb 0, 252
defb 3, 240
defb 15, 224
defb 15, 224
defb 2, 192
defb 29, 192
defb 17, 192
defb 17, 128
defb 34, 128
defb 127, 0
defb 127, 0
defb 124, 0
defb 127, 0
defb 60, 128
defb 27, 192
defb 0, 224
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_7_b
defb 0, 24
defb 230, 0
defb 252, 1
defb 248, 3
defb 56, 3
defb 220, 1
defb 28, 1
defb 30, 0
defb 62, 0
defb 246, 0
defb 236, 1
defb 240, 3
defb 252, 1
defb 124, 1
defb 184, 3
defb 0, 7
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_7_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_8_a
defb 0, 252
defb 3, 240
defb 2, 224
defb 29, 192
defb 4, 192
defb 4, 192
defb 34, 128
defb 63, 128
defb 62, 128
defb 28, 128
defb 108, 0
defb 108, 0
defb 110, 0
defb 103, 0
defb 0, 152
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_8_b
defb 0, 31
defb 192, 15
defb 48, 7
defb 208, 1
defb 90, 0
defb 90, 0
defb 62, 0
defb 254, 0
defb 60, 0
defb 24, 1
defb 28, 1
defb 24, 3
defb 56, 3
defb 192, 1
defb 30, 0
defb 0, 225
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_8_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_9_a
defb 0, 252
defb 3, 240
defb 15, 224
defb 29, 192
defb 25, 192
defb 25, 192
defb 27, 192
defb 15, 224
defb 15, 224
defb 21, 128
defb 32, 128
defb 16, 192
defb 0, 224
defb 0, 224
defb 30, 192
defb 0, 193
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_9_b
defb 0, 127
defb 128, 31
defb 224, 15
defb 112, 7
defb 48, 7
defb 48, 7
defb 176, 7
defb 224, 15
defb 224, 15
defb 64, 31
defb 0, 7
defb 8, 3
defb 4, 1
defb 0, 1
defb 120, 3
defb 0, 131
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_9_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_10_a
defb 0, 254
defb 1, 248
defb 7, 240
defb 14, 224
defb 12, 224
defb 12, 224
defb 13, 224
defb 7, 240
defb 7, 240
defb 2, 248
defb 0, 224
defb 16, 192
defb 32, 128
defb 16, 128
defb 14, 224
defb 0, 225
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_10_b
defb 0, 63
defb 192, 15
defb 240, 7
defb 184, 3
defb 152, 3
defb 152, 3
defb 216, 3
defb 240, 7
defb 240, 7
defb 168, 1
defb 4, 1
defb 8, 3
defb 0, 7
defb 0, 15
defb 112, 7
defb 0, 135
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_10_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_11_a
defb 0, 255
defb 0, 248
defb 7, 224
defb 31, 192
defb 51, 128
defb 45, 128
defb 97, 0
defb 105, 0
defb 115, 0
defb 127, 0
defb 127, 0
defb 61, 128
defb 63, 128
defb 29, 192
defb 13, 224
defb 0, 242
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_11_b
defb 0, 255
defb 0, 63
defb 192, 15
defb 240, 7
defb 152, 3
defb 104, 3
defb 12, 1
defb 76, 1
defb 156, 1
defb 252, 1
defb 252, 1
defb 252, 1
defb 252, 1
defb 220, 3
defb 216, 3
defb 0, 39
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_11_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_12_a
defb 0, 248
defb 7, 224
defb 31, 192
defb 51, 128
defb 45, 128
defb 97, 0
defb 101, 0
defb 115, 0
defb 127, 0
defb 127, 0
defb 62, 128
defb 63, 128
defb 30, 192
defb 7, 224
defb 0, 248
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_12_b
defb 0, 63
defb 192, 15
defb 240, 7
defb 152, 3
defb 104, 3
defb 12, 1
defb 44, 1
defb 156, 1
defb 254, 0
defb 254, 0
defb 254, 0
defb 254, 0
defb 222, 0
defb 108, 1
defb 0, 147
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_12_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_13_a
defb 0, 248
defb 7, 224
defb 1, 192
defb 63, 128
defb 17, 128
defb 51, 128
defb 17, 128
defb 63, 128
defb 1, 192
defb 15, 192
defb 35, 128
defb 96, 0
defb 23, 0
defb 0, 192
defb 56, 131
defb 0, 199
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_13_b
defb 0, 31
defb 128, 7
defb 240, 3
defb 224, 1
defb 24, 1
defb 48, 1
defb 24, 1
defb 240, 1
defb 240, 0
defb 2, 0
defb 206, 0
defb 0, 1
defb 192, 3
defb 28, 1
defb 0, 227
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_13_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_14_a
defb 0, 248
defb 7, 224
defb 3, 192
defb 63, 128
defb 17, 128
defb 57, 128
defb 17, 128
defb 63, 128
defb 3, 0
defb 79, 0
defb 115, 0
defb 0, 128
defb 3, 192
defb 56, 128
defb 0, 199
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_14_b
defb 0, 31
defb 128, 7
defb 240, 3
defb 224, 1
defb 24, 1
defb 144, 1
defb 24, 1
defb 240, 1
defb 240, 3
defb 128, 3
defb 196, 1
defb 6, 0
defb 232, 0
defb 0, 3
defb 28, 193
defb 0, 227
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_14_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_15_a
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_15_b
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_15_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_16_a
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_16_b
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

._sprite_16_c
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

; Extra sprites ahead...
._sprite_e
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 255, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255

defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
#endasm
# 10 "assets/extrasprites.h"
extern unsigned char sprite_18_a [];
#asm
#endasm
#asm
# 50
._sprite_18_a
defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
._sprite_18_b
defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
._sprite_18_c
defb 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
# 11 "assets/enems.h"
typedef struct {
int x, y;
unsigned char x1, y1, x2, y2;
signed char mx, my;
char t;
unsigned char life;
} BADDIE;

extern BADDIE baddies [0];
#asm


._baddies
BINARY "../bin/enems.bin"
#endasm
#asm
#endasm
# 2 "addons/helpers.h"
unsigned char addons_between (unsigned char x, unsigned char a, unsigned char b, unsigned char h1, unsigned char h2) {
return ((a < b ? a : b) <= x + h1 && x <= (a < b ? b : a) + h2);
}
# 7 "addons/arrows/sprites.h"
extern unsigned char arrow_sprites [0];
#asm

defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
defb 0, 255
._arrow_sprites
BINARY "../bin/sparrow.bin"
#endasm
#asm
# 13 "sound/beeper.h"
.sound_play

ld hl, soundEffectsData ;address of sound effects data

;di
push iy

ld b,0
ld c,a
add hl,bc
add hl,bc
ld a,(hl)
inc hl
ld h,(hl)
ld l,a
push hl
pop ix ;put it into ix

.readData
ld a,(ix+0) ;read block type
or a
jr nz,readData_sound
pop iy
;ei
ret

.readData_sound
ld c,(ix+1) ;read duration 1
ld b,(ix+2)
ld e,(ix+3) ;read duration 2
ld d,(ix+4)
push de
pop iy

dec a
jr nz,sfxRoutineNoise



;this routine generate tone with many parameters

.sfxRoutineTone
ld e,(ix+5) ;freq
ld d,(ix+6)
ld a,(ix+9) ;duty
ld (sfxRoutineTone_duty + 1),a
ld hl,0

.sfxRoutineTone_l0
push bc
push iy
pop bc
.sfxRoutineTone_l1
add hl,de
ld a,h
.sfxRoutineTone_duty
cp 0
sbc a,a
and 16
.sfxRoutineTone_border
or 0
out ($fe),a

dec bc
ld a,b
or c
jr nz,sfxRoutineTone_l1

ld a,(sfxRoutineTone_duty + 1)
add a,(ix+10) ;duty change
ld (sfxRoutineTone_duty + 1),a

ld c,(ix+7) ;slide
ld b,(ix+8)
ex de,hl
add hl,bc
ex de,hl

pop bc
dec bc
ld a,b
or c
jr nz,sfxRoutineTone_l0

ld c,11
.nextData
add ix,bc ;skip to the next block
jr readData

;this routine generate noise with two parameters

.sfxRoutineNoise
ld e,(ix+5) ;pitch

ld d,1
ld h,d
ld l,d
.sfxRoutineNoise_l0
push bc
push iy
pop bc
.sfxRoutineNoise_l1
ld a,(hl)
and 16
.sfxRoutineNoise_border
or 0
out ($fe),a
dec d
jr nz,sfxRoutineNoise_l2
ld d,e
inc hl
ld a,h
and $1f
ld h,a
.sfxRoutineNoise_l2
dec bc
ld a,b
or c
jr nz,sfxRoutineNoise_l1

ld a,e
add a,(ix+6) ;slide
ld e,a

pop bc
dec bc
ld a,b
or c
jr nz,sfxRoutineNoise_l0

ld c,7
jr nextData

.soundEffectsData
defw soundEffectsData_sfx0
defw soundEffectsData_sfx1
defw soundEffectsData_sfx2
defw soundEffectsData_sfx3
defw soundEffectsData_sfx4
defw soundEffectsData_sfx5
defw soundEffectsData_sfx6
defw soundEffectsData_sfx7
defw soundEffectsData_sfx8
defw soundEffectsData_sfx9
defw soundEffectsData_sfx10
defw soundEffectsData_sfx11

.soundEffectsData_sfx0
defb 0x01
defw 0x000a,0x03e8,0x00c8,0x0016,0x1680
defb 0x00
.soundEffectsData_sfx1
defb 0x01
defw 0x0064,0x0014,0x01f4,0x0002,0x0010
defb 0x00
.soundEffectsData_sfx2
defb 0x02
defw 0x0001,0x03e8,0x000a
defb 0x01
defw 0x0014,0x0064,0x0190,0xfff0,0x0080
defb 0x02
defw 0x0001,0x07d0,0x0001
defb 0x00
.soundEffectsData_sfx3
defb 0x01
defw 0x0014,0x00c8,0x0d48,0x000a,0x0040
defb 0x00
.soundEffectsData_sfx4
defb 0x01
defw 0x0050,0x0014,0x03e8,0xffff,0x0080
defb 0x00
.soundEffectsData_sfx5
defb 0x01
defw 0x0004,0x03e8,0x03e8,0x0190,0x0080
defb 0x00
.soundEffectsData_sfx6
defb 0x01
defw 0x0002,0x0fa0,0x0190,0x00c8,0x0040
defb 0x01
defw 0x0002,0x0fa0,0x00c8,0x00c8,0x0020
defb 0x00
.soundEffectsData_sfx7
defb 0x01
defw 0x000a,0x03e8,0x00c8,0x0002,0x0010
defb 0x01
defw 0x0001,0x0fa0,0x0000,0x0000,0x0000
defb 0x01
defw 0x000a,0x03e8,0x00c8,0xfffe,0x0010
defb 0x01
defw 0x0001,0x07d0,0x0000,0x0000,0x0000
defb 0x01
defw 0x000a,0x03e8,0x00b4,0xfffe,0x0010
defb 0x01
defw 0x0001,0x0fa0,0x0000,0x0000,0x0000
defb 0x00
.soundEffectsData_sfx8
defb 0x02
defw 0x0001,0x03e8,0x0014
defb 0x01
defw 0x0001,0x03e8,0x0000,0x0000,0x0000
defb 0x02
defw 0x0001,0x03e8,0x0001
defb 0x00
.soundEffectsData_sfx9
defb 0x02
defw 0x0014,0x0032,0x0101
defb 0x00
.soundEffectsData_sfx10
defb 0x02
defw 0x0064,0x01f4,0x0264
defb 0x00
.soundEffectsData_sfx11
defb 0x01
defw 0x0014,0x01f4,0x00c8,0x0005,0x0110
defb 0x01
defw 0x0001,0x03e8,0x0000,0x0000,0x0000
defb 0x01
defw 0x001e,0x01f4,0x00c8,0x0008,0x0110
defb 0x01
defw 0x0001,0x07d0,0x0000,0x0000,0x0000
defb 0x00
#endasm
# 255
void beep_fx (unsigned char n) {

asm_int = n;
#asm

push ix
push iy
ld a, (_asm_int)
call sound_play
pop ix
pop iy
#endasm

}
# 8 "engine/printer.h"
unsigned char *spacer = "            ";
# 25
unsigned char attr (char x, char y) {

if (x < 0 || y < 0 || x > 14 || y > 9) return 0;
return map_attr [x + (y << 4) - y];
}

unsigned char qtile (unsigned char x, unsigned char y) {

return map_buff [x + (y << 4) - y];
}

void draw_coloured_tile (void) {
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
# 173
ld a, (__x)
ld c, a
ld a, (__y)
call SPCompDListAddr
ex de, hl




ld a, (__t)
sla a
sla a
add 64

ld hl, _tileset + 2048
ld b, 0
ld c, a
add hl, bc


ld c, a



ld a, (hl)
ld (de), a
inc de
inc hl

ld a, c
ld (de), a
inc de
inc a
ld c, a

inc de
inc de

ld a, (hl)
ld (de), a
inc de
inc hl

ld a, c
ld (de), a
inc a

ex de, hl
ld bc, 123
add hl, bc
ex de, hl
ld c, a

ld a, (hl)
ld (de), a
inc de
inc hl

ld a, c
ld (de), a
inc de
inc a
ld c, a

inc de
inc de

ld a, (hl)
ld (de), a
inc de

ld a, c
ld (de), a
#endasm


}


void invalidate_tile (void) {
#asm

; Invalidate Rectangle
;
; enter: B = row coord top left corner
; C = col coord top left corner
; D = row coord bottom right corner
; E = col coord bottom right corner
; IY = clipping rectangle, set it to "ClipStruct" for full screen

ld a, (__x)
inc a
ld e, a
ld a, (__y)
inc a
ld d, a
ld a, (__x)
ld c, a
ld a, (__y)
ld iy, vpClipStruct
call SPInvalidate
#endasm


}

void invalidate_viewport (void) {
#asm

; Invalidate Rectangle
;
; enter: B = row coord top left corner
; C = col coord top left corner
; D = row coord bottom right corner
; E = col coord bottom right corner
; IY = clipping rectangle, set it to "ClipStruct" for full screen

ld b, 1
ld c, 1
ld d, 1+19
ld e, 1+29
ld iy, vpClipStruct
call SPInvalidate
#endasm

}

void draw_invalidate_coloured_tile_g (void) {

if ((_t==20)) tilanims_add ();

draw_coloured_tile_gamearea ();
invalidate_tile ();
}

void draw_coloured_tile_gamearea (void) {
_x = 1 + (_x << 1); _y = 1 + (_y << 1); draw_coloured_tile ();
}

void print_number2 (void) {
rda = 16 + (_t / 10); rdb = 16 + (_t % 10);
#asm

; enter: A = row position (0..23)
; C = col position (0..31/63)
; D = pallette #
; E = graphic #

ld a, (_rda)
ld e, a

ld d, 7

ld a, (__x)
ld c, a

ld a, (__y)

call SPPrintAtInv

ld a, (_rdb)
ld e, a

ld d, 7

ld a, (__x)
inc a
ld c, a

ld a, (__y)

call SPPrintAtInv
#endasm

}
#asm
#endasm
# 411
void print_str (void) {
#asm

.print_str_loop
ld hl, (_gp_gen)
ld a, (hl)
or a

ret z

inc hl
ld (_gp_gen), hl

sub 32
ld e, a

ld a, (__t)
ld d, a

ld hl, __x
ld c, (hl)
inc (hl)

ld a, (__y)

call SPPrintAtInv

jr print_str_loop
#endasm

}
#asm
#endasm
# 472
unsigned char utaux = 0;
void update_tile (void) {
#asm
# 481
ld a, (__x)
ld c, a
ld a, (__y)
ld b, a
sla a
sla a
sla a
sla a
sub b
add c
ld b, 0
ld c, a
ld hl, _map_attr
add hl, bc
ld a, (__n)
ld (hl), a
ld hl, _map_buff
add hl, bc
ld a, (__t)
ld (hl), a

call _draw_coloured_tile_gamearea

ld a, (_is_rendering)
or a
ret nz

call _invalidate_tile
#endasm

}

void print_message (void) {
_x = 10; _y = 12; _t = 87; print_str ();
_x = 10; _y = 11; _t = 87; gp_gen = spacer; print_str ();
_x = 10; _y = 13; _t = 87; gp_gen = spacer; print_str ();

sp_UpdateNow ();
sp_WaitForNoKey ();
}

unsigned char button_pressed (void) {
return (sp_GetKey () || ((((joyfunc) (&keys)) & 0x80) == 0));
}
#asm
#endasm
# 6 "my/msc.h"
void msc_init_all (void) {
for (sc_c = 0; sc_c < 32; ++ sc_c)
flags [sc_c] = 0;
}


unsigned char read_byte (void) {
unsigned char sc_b;
#asm
#endasm
# 21
sc_b = *script ++;
#asm
#endasm
# 29
return sc_b;
}

unsigned char read_vbyte (void) {
sc_c = read_byte ();
return (sc_c & 128) ? flags [sc_c & 127] : sc_c;
}

void readxy (void) {
sc_x = read_vbyte ();
sc_y = read_vbyte ();
}


void __FASTCALL__ stop_player (void) {
p_vx = p_vy = 0;
}


void __FASTCALL__ reloc_player (void) {




p_x = read_vbyte () << (4+6);
p_y = read_vbyte () << (4+6);
stop_player ();

}

unsigned char *next_script;
void run_script (unsigned char whichs) {


asm_int = main_script_offset + whichs + whichs;
#asm
#endasm
#asm
# 77
ld hl, (_asm_int)
ld a, (hl)
inc hl
ld h, (hl)
ld l, a
ld (_script), hl
#endasm
#asm
#endasm
# 93
if (script == 0)
return;

script += main_script_offset;
# 102
while ((sc_c = read_byte ()) != 0xFF) {
next_script = script + sc_c;
sc_terminado = sc_continuar = 0;
while (!sc_terminado) {
switch (read_byte ()) {
case 0xF0:


break;
case 0xFF:


sc_terminado = 1;
sc_continuar = 1;
break;
}
}
if (sc_continuar) {
sc_terminado = 0;
while (!sc_terminado) {
switch (read_byte ()) {
case 0xF4:

while (0xff != (sc_x = read_byte ())) {
sc_n = read_byte ();
_x = sc_x >> 4; _y = sc_x & 15; _n = behs [sc_n]; _t = sc_n; update_tile ();
}
break;
case 0xFF:
sc_terminado = 1;
break;
}
}
}
script = next_script;
}
}
# 7 "engine/engine.h"
void enem_move_spr_abs (void) {
#asm



; enter: IX = sprite structure address
; IY = clipping rectangle, set it to "ClipStruct" for full screen
; BC = animate bitdef displacement (0 for no animation)
; H = new row coord in chars
; L = new col coord in chars
; D = new horizontal rotation (0..7) ie horizontal pixel position
; E = new vertical rotation (0..7) ie vertical pixel position


ld a, (_gpit)
sla a
ld c, a
ld b, 0
ld hl, _sp_moviles
add hl, bc
ld e, (hl)
inc hl
ld d, (hl)
push de
pop ix


ld iy, vpClipStruct



ld hl, _en_an_c_f
add hl, bc
ld e, (hl)
inc hl
ld d, (hl)

ld hl, _en_an_n_f
add hl, bc
ld a, (hl)
inc hl
ld h, (hl)
ld l, a

or a
sbc hl, de

push bc

ld b, h
ld c, l


ld a, (_gpen_cy)
srl a
srl a
srl a
add 1
ld h, a

ld a, (_gpen_cx)
srl a
srl a
srl a
add 1
ld l, a


ld a, (_gpen_cx)
and 7
ld d, a

ld a, (_gpen_cy)
and 7
ld e, a

call SPMoveSprAbs



pop bc

ld hl, _en_an_c_f
add hl, bc
ex de, hl

ld hl, _en_an_n_f
add hl, bc

ldi
ldi
#endasm

}
# 37 "./engine/frames.h"
unsigned char *player_frames [] = {
sprite_5_a, sprite_6_a, sprite_7_a, sprite_6_a,
sprite_1_a, sprite_2_a, sprite_3_a, sprite_2_a,
sprite_8_a, sprite_4_a
};



unsigned char *enem_frames [] = {
sprite_9_a, sprite_10_a, sprite_11_a, sprite_12_a,
sprite_13_a, sprite_14_a, sprite_15_a, sprite_16_a
};
# 7 "./engine/initplayer.h"
void init_player (void) {
# 16
p_x = 1 << 10;
p_y = 8 << 10;
# 27
p_vy = 0;
p_vx = 0;

p_jmp_ct = 1;
p_jmp_on = 0;

p_frame = 0;
p_subframe = 0;
# 43
p_facing = 1;


p_facing_v = p_facing_h = 0xff;
p_state = 0;
p_state_ct = 0;

p_life = 10;

p_objs = 0;
p_keys = 0;



p_killed = 0;

p_disparando = 0;
# 106
}
# 7 "./engine/collision.h"
unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {

return (x1 + 8 >= x2 && x1 <= x2 + 8 && y1 + 8 >= y2 && y1 <= y2 + 8);
# 13
}

unsigned char collide_pixel (unsigned char x, unsigned char y, unsigned char x1, unsigned char y1) {
if (x >= x1 + 1 && x <= x1 + 14 && y >= y1 + 1 && y <= y1 + 14) return 1;
return 0;
}
# 7 "./engine/random.h"
extern unsigned int seed1 [0];
extern unsigned int seed2 [0];
extern unsigned char randres [0];
#asm

._seed1 defw 0
._seed2 defw 0
._randres defb 0
#endasm


unsigned char rand (void) {
#asm

.rnd
ld hl,0xA280
ld de,0xC0DE
ld a,h ; t = x ^ (x << 1)
add a,a
xor h
ld h,l ; x = y
ld l,d ; y = z
ld d,e ; z = w
ld e,a
rra ; t = t ^ (t >> 1)
xor e
ld e,a
ld a,d ; w = w ^ ( w << 3 ) ^ t
add a,a
add a,a
add a,a
xor d
xor e
ld e,a
ld (rnd+1),hl
ld (rnd+4),de
ld (_randres), a
#endasm

return randres [0];
}

void srand (void) {
#asm

ld hl, (_seed1)
ld (rnd+1),hl
ld hl, (_seed2)
ld (rnd+4),hl
#endasm

}
# 9 "./engine/messages.h"
unsigned char bs;


void game_ending (void) {
sp_UpdateNow();
# 19
unpack ((unsigned int) (s_ending), 16384);



bs = 4; do {
beep_fx (2);
beep_fx (3);
} while (--bs);
beep_fx (6);

}

void game_over (void) {
_x = 1; _y = 23; _t = p_life; print_number2 ();
gp_gen = " GAME OVER! "; print_message ();



bs = 4; do {
beep_fx (2);
beep_fx (3);
} while (--bs);
beep_fx (10);

}
# 127 "engine/engine.h"
void step (void) {
#asm

ld a, 16
out (254), a
nop
nop
nop
nop
nop
nop
nop
nop
nop
xor 16
out (254), a
#endasm

}


void cortina (void) {
#asm

ld b, 7
.fade_out_extern
push bc

ld e, 3 ; 3 tercios
ld hl, 22528 ; aquí empiezan los atributos
#endasm
#asm
#endasm
#asm
# 161
.fade_out_bucle
ld a, (hl ) ; nos traemos el atributo actual

ld d, a ; tomar atributo
and 7 ; aislar la tinta
jr z, ink_done ; si vale 0, no se decrementa
dec a ; decrementamos tinta
.ink_done
ld b, a ; en b tenemos ahora la tinta ya procesada.

ld a, d ; tomar atributo
and 56 ; aislar el papel, sin modificar su posiciÃ³n en el byte
jr z, paper_done ; si vale 0, no se decrementa
sub 8 ; decrementamos papel restando 8
.paper_done
ld c, a ; en c tenemos ahora el papel ya procesado.
ld a, d
and 192 ; nos quedamos con bits 6 y 7 (0x40 y 0x80)
or c ; añadimos paper
or b ; e ink, con lo que recompuesto el atributo
ld (hl),a ; lo escribimos,
inc l ; e incrementamos el puntero.
jr nz, fade_out_bucle ; continuamos hasta acabar el tercio (cuando L valga 0)
inc h ; siguiente tercio
dec e
jr nz, fade_out_bucle ; repetir las 3 veces
pop bc
djnz fade_out_extern
#endasm

}

signed int addsign (signed int n, signed int value) {

return n == 0 ? 0 : n > 0 ? value : -value;
}

unsigned int abs (int n) {
if (n < 0)
return (unsigned int) (-n);
else
return (unsigned int) n;
}

void kill_player (unsigned char sound) {
# 227
p_life --;
# 234
beep_fx (sound);
# 247
p_state = 2;
p_state_ct = 50;
# 254
}
# 10 "./engine/tilanim.h"
unsigned char max_tilanims;
unsigned char tacount;
unsigned char tilanims_xy [16];
unsigned char tilanims_ft [16];

void tilanims_add (void) {
tilanims_xy [max_tilanims] = (_x << 4) + _y;
tilanims_ft [max_tilanims] = _t;
++ max_tilanims;
}

unsigned char tait;
void tilanims_do (void) {
if (max_tilanims == 0) return;

tacount = (tacount + 1) & 7;
if (!tacount) {

++ tait; if (tait >= max_tilanims) tait = 0;


_t = tilanims_ft [tait] = tilanims_ft [tait] ^ 128;


rda = tilanims_xy [tait];
#asm


ld a, (_rda)
srl a
srl a
srl a
srl a
ld (_x), a

ld a, (_rda)
and 15
ld (_y), a

ld a, (__t)
bit 7, a
jr z, _tilanims_do_noinc
inc a
._tilanims_do_noinc
and 127
ld (__t), a
#endasm


draw_invalidate_coloured_tile_g ();
}
}
# 25 "./engine/playermove.h"
unsigned char ptx1, ptx2, pty1, pty2, pty3, pt1, pt2;
unsigned char move (void) {

wall_v = wall_h = 0;
gpit = (joyfunc) (&keys);
# 5 "./engine/playermods/va_gravity.h"
if (do_gravity) {

if (p_vy < 512) p_vy += 32; else p_vy = 512;
}
# 13
if (p_gotten) p_vy = 0;
# 22 "./engine/playermods/va.h"
p_y += p_vy;
# 36
if (p_y < 0) p_y = 0;
if (p_y > 9216) p_y = 9216;
# 3 "./engine/playermods/va_collision.h"
gpx = p_x >> 6;
gpy = p_y >> 6;
# 22
ptx1 = (gpx) >> 4;
ptx2 = (gpx + 15) >> 4;
pty1 = (gpy) >> 4;
pty2 = (gpy + 15) >> 4;


hit_v = 0;



if (p_vy + ptgmy < 0)

{
pt1 = attr (ptx1, pty1);
pt2 = attr (ptx2, pty1);
if ((pt1 & 8) || (pt2 & 8)) {



p_vy = 0;
# 50
p_y = ((pty1 + 1) << 10);

wall_v = 1;
}

}



if (p_vy + ptgmy > 0)

{
pt1 = attr (ptx1, pty2);
pt2 = attr (ptx2, pty2);
# 69
if ((pt1 & 8) || (pt2 & 8) || (((gpy - 1) & 15) < 8 && ((pt1 & 4) || (pt2 & 4))))


{
# 81
p_vy = 0;
# 88
p_y = ((pty2 - 1) << 10);

wall_v = 2;
}
}


if (p_vy) hit_v = ((pt1 ==1) || (pt2 ==1));


gpy = p_y >> 6;
gpxx = gpx >> 4;
gpyy = gpy >> 4;
# 7 "./engine/playermods/possee.h"
pty3 = (gpy + 16) >> 4;
possee = ((attr (ptx1, pty3) & 12) || (attr (ptx2, pty3) & 12)) && (gpy & 15) < 8;
# 14 "./engine/playermods/jump_sideview.h"
if (((gpit & 0x80) == 0) && p_jmp_on == 0 && (possee || p_gotten)) {

p_jmp_on = 1;
p_jmp_ct = 0;



beep_fx (1);

}


if (((gpit & 0x80) == 0) && p_jmp_on) {
p_vy -= (128 + 96 - (p_jmp_ct>>1));



if (p_vy < -256) p_vy = -256;

p_jmp_ct ++;
if (p_jmp_ct == 8)
p_jmp_on = 0;
}


if (!((gpit & 0x80) == 0)) p_jmp_on = 0;
# 4 "./engine/playermods/ha_controller.h"
if ( ! ((gpit & 0x04) == 0 || (gpit & 0x08) == 0))

{
# 10
if (p_vx > 0) {
p_vx -= 48; if (p_vx < 0) p_vx = 0;
} else if (p_vx < 0) {
p_vx += 48; if (p_vx > 0) p_vx = 0;
}
}

if ((gpit & 0x04) == 0) {
# 22
if (p_vx > -256) {

p_facing = 0;

p_vx -= 64;
}
}

if ((gpit & 0x08) == 0) {
# 35
if (p_vx < 256) {
p_vx += 64;

p_facing = 1;

}
}
# 10 "./engine/playermods/ha.h"
p_x = p_x + p_vx;

if (p_gotten) p_x += ptgmx;



if (p_x < 0) p_x = 0;
if (p_x > 14336) p_x = 14336;
# 3 "./engine/playermods/ha_collision.h"
gpx = p_x >> 6;
gpy = p_y >> 6;
# 22
ptx1 = (gpx) >> 4;
ptx2 = (gpx + 15) >> 4;
pty1 = (gpy) >> 4;
pty2 = (gpy + 15) >> 4;



hit_h = 0;
# 35
if (p_vx + ptgmx < 0)

{
pt1 = attr (ptx1, pty1);
pt2 = attr (ptx1, pty2);
if ((pt1 & 8) || (pt2 & 8)) {



p_vx = 0;




p_x = ((ptx1 + 1) << 10);

wall_h = 3;
}


else if ((pt1 ==1) || (pt2 ==1)) {
hit_h = 1;
}


}



if (p_vx + ptgmx > 0)

{
pt1 = attr (ptx2, pty1);
pt2 = attr (ptx2, pty2);
if ((pt1 & 8) || (pt2 & 8)) {



p_vx = 0;




p_x = ((ptx2 - 1) << 10);

wall_h = 4;
}



else if ((pt1 ==1) || (pt2 ==1)) {
hit_h = 1;
}


}

gpx = p_x >> 6;
# 263 "./engine/playermove.h"
hit = 0;
if (hit_v == 1) {
hit = 1;



p_vy = -p_vy;

} else if (hit_h == 1) {
hit = 1;



p_vx = -p_vx;

}
if (hit) {

if (p_life > 0 && p_state == 0)
# 285
{
kill_player (3);
}
}
# 307
if (!possee && !p_gotten) {
p_n_f = player_frames [8 + p_facing];
} else {
gpit = p_facing << 2;
if (p_vx == 0) {



p_n_f = player_frames [gpit + 1];

} else {
p_subframe ++;
if (p_subframe == 4) {
p_subframe = 0;



p_frame = (p_frame + 1) & 3;


step ();

}
p_n_f = player_frames [gpit + p_frame];
}
}
# 357
}
# 311 "engine/engine.h"
void run_entering_script (void) {
# 320
run_script (2 * 10 * 2 + 1);
run_script (n_pant + n_pant);
# 325
}
# 14 "./engine/drawscr.h"
void draw_scr_background (void) {
is_rendering = 1;
# 21
seed1 [0] = n_pant; seed2 [0] = n_pant + 1;
srand ();
# 28
map_pointer = map + (n_pant * 75);


gpit = gpx = gpy = 0;
# 40
do {
gpjt = rand () & 15;
# 50
if (gpit & 1) {
gpd = gpc & 15;
} else {
gpc = *map_pointer ++;
gpd = gpc >> 4;
}
# 60
map_attr [gpit] = behs [gpd];
# 76
map_buff [gpit] = gpd;
_x = gpx; _y = gpy; _t = gpd;
draw_coloured_tile_gamearea ();


if (gpd >= ) {
add_tilanim (gpx >> 1, gpy >> 1, gpd);
}


gpx ++;
if (gpx == 15) {
gpx = 0;
gpy ++;
}
} while (gpit ++ < 149);
# 139
}

void draw_scr (void) {
# 150
if (no_draw) {
no_draw = 0;
} else {
# 161
draw_scr_background ();
}


f_zone_ac = 0;



enoffs = n_pant * 3;
# 25 "./engine/enemsinit.h"
for (gpit = 0; gpit < 3; gpit ++) {

en_an_count [gpit] = 3;
en_an_state [gpit] = 0;
enoffsmasi = enoffs + gpit;
# 54
gpt = baddies [enoffsmasi].t >> 3;
if (gpt && gpt < 16) {
en_an_base_frame [gpit] = (baddies [enoffsmasi].t & 3) << 1;

switch (gpt) {

case 2:
# 65
en_an_x [gpit] = baddies [enoffsmasi].x << 6;
en_an_y [gpit] = baddies [enoffsmasi].y << 6;
en_an_vx [gpit] = en_an_vy [gpit] = 0;

en_an_state [gpit] = 0;

break;
# 85
default:
break;
}
# 96
} else {
en_an_n_f [gpit] = sprite_18_a;
}
}
# 174 "./engine/drawscr.h"
do_respawn = 1;
# 194
run_entering_script ();
# 210
x_pant = n_pant % 10; y_pant = n_pant / 10;
# 233
invalidate_viewport ();

is_rendering = 0;
}
# 2 "./engine/enemmods/helper_funcs.h"
unsigned char distance (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
unsigned char dx = abs (x2 - x1);
unsigned char dy = abs (y2 - y1);
unsigned char mn = dx < dy ? dx : dy;
return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
}
# 121
int limit (int val, int min, int max) {
if (val < min) return min;
if (val > max) return max;
return val;
}
# 24 "./engine/enems.h"
unsigned char pregotten;

unsigned char enemy_shoots;

void mueve_bicharracos (void) {


p_gotten = 0;
ptgmx = 0;
ptgmy = 0;


tocado = 0;
p_gotten = 0;
for (gpit = 0; gpit < 3; gpit ++) {
active = killable = animate = 0;
enoffsmasi = enoffs + gpit;
gpen_x = baddies [enoffsmasi].x;
gpen_y = baddies [enoffsmasi].y;

if (en_an_state [gpit] == 4) {
en_an_count [gpit] --;
if (0 == en_an_count [gpit]) {
en_an_state [gpit] = 0;
en_an_n_f [gpit] = sprite_18_a;
continue;
}
}
# 61
pregotten = (gpx + 15 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 15);




if (baddies [enoffsmasi].t & 4) {
enemy_shoots = 1;
} else enemy_shoots = 0;

gpt = baddies [enoffsmasi].t >> 3;

switch (gpt) {

case 1:
killable = 1;
case 8:
# 3 "./engine/enemmods/move_linear.h"
active = animate = 1;
baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
baddies [enoffsmasi].y += baddies [enoffsmasi].my;
gpen_cx = baddies [enoffsmasi].x;
gpen_cy = baddies [enoffsmasi].y;
gpen_xx = gpen_cx >> 4;
gpen_yy = gpen_cy >> 4;
# 16
if (gpen_cx == baddies [enoffsmasi].x1 || gpen_cx == baddies [enoffsmasi].x2)
baddies [enoffsmasi].mx = -baddies [enoffsmasi].mx;
if (gpen_cy == baddies [enoffsmasi].y1 || gpen_cy == baddies [enoffsmasi].y2)
baddies [enoffsmasi].my = -baddies [enoffsmasi].my;
# 78 "./engine/enems.h"
break;


case 2:
# 4 "./engine/enemmods/move_fanty.h"
active = killable = animate = 1;
gpen_cx = en_an_x [gpit] >> 6;
gpen_cy = en_an_y [gpit] >> 6;
switch (en_an_state [gpit]) {
case 0:
# 12
if (distance (gpx, gpy, gpen_cx, gpen_cy) <= 96)
en_an_state [gpit] = 1;
break;
case 1:
# 19
if (distance (gpx, gpy, gpen_cx, gpen_cy) > 96) {
en_an_state [gpit] = 2;
} else {
en_an_vx [gpit] = limit (
en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], 16),
-128, 128);
en_an_vy [gpit] = limit (
en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], 16),
-128, 128);
en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
}
break;
case 2:
en_an_x [gpit] += addsign (baddies [enoffsmasi].x - gpen_cx, 64);
en_an_y [gpit] += addsign (baddies [enoffsmasi].y - gpen_cy, 64);
# 39
if (distance (gpx, gpy, gpen_cx, gpen_cy) <= 96)
en_an_state [gpit] = 1;
break;
}
gpen_cx = en_an_x [gpit] >> 6;
gpen_cy = en_an_y [gpit] >> 6;
if (en_an_state [gpit] == 2 &&
gpen_cx == baddies [enoffsmasi].x &&
gpen_cy == baddies [enoffsmasi].y
)
en_an_state [gpit] = 0;
# 83 "./engine/enems.h"
break;
# 96
case 10:
# 14 "./addons/arrows/move.h"
baddies [enoffsmasi].y2 = 0;
if (baddies [enoffsmasi].my) {
baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
en_an_n_f [gpit] = arrow_sprites + (baddies [enoffsmasi].mx < 0 ? 0 : 144);
if (baddies [enoffsmasi].x == baddies [enoffsmasi].x2) baddies [enoffsmasi].my = 0;
} else {
en_an_n_f [gpit] = sprite_18_a;
if (0 == enemy_shoots || (addons_between (gpy, baddies [enoffsmasi].y1, baddies [enoffsmasi].y1, 15, 15) && addons_between (gpx, baddies [enoffsmasi].x1, baddies [enoffsmasi].x2, 15, 31))){
baddies [enoffsmasi].y2 = 1;
}

}
if (baddies [enoffsmasi].y2) {
baddies [enoffsmasi].my = 1;
baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
beep_fx (7);
}

gpen_cx = baddies [enoffsmasi].x;
gpen_cy = baddies [enoffsmasi].y;

active = 1;
# 98 "./engine/enems.h"
break;
# 105
default:
if (gpt > 15 && en_an_state [gpit] != 4) en_an_n_f [gpit] = sprite_18_a;
}

if (active) {
if (animate) {
# 20 "./engine/enemmods/animate.h"
gpjt = baddies [enoffsmasi].mx ? ((gpen_cx + 4) >> 3) & 1 : ((gpen_cy + 4) >> 3) & 1;
en_an_n_f [gpit] = enem_frames [en_an_base_frame [gpit] + gpjt];
# 112 "./engine/enems.h"
}
# 3 "./engine/enemmods/platforms.h"
if (gpt == 8) {



if (pregotten && (p_gotten == 0) && (p_jmp_on == 0))

{

if (baddies [enoffsmasi].mx) {
if (gpy + 16 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) {
p_gotten = 1;
# 20
ptgmx = baddies [enoffsmasi].mx << 6;
p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;

}
}


if (
(baddies [enoffsmasi].my < 0 && gpy + 18 >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y) ||
(baddies [enoffsmasi].my > 0 && gpy + 17 + baddies [enoffsmasi].my >= baddies [enoffsmasi].y && gpy + 10 <= baddies [enoffsmasi].y)
) {
p_gotten = 1;
# 37
ptgmy = baddies [enoffsmasi].my << 6;
p_y = (baddies [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
p_vy = 0;

}
}
} else
# 138 "./engine/enems.h"
if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_state == 0) {
# 183
if (p_life > 0) {
tocado = 1;
}
# 192
kill_player (2);
# 217
}
# 6 "./engine\enemmods\render.h"
enem_move_spr_abs ();
# 226 "./engine/enems.h"
} else {
#asm


; enter: IX = sprite structure address
; IY = clipping rectangle, set it to "ClipStruct" for full screen
; BC = animate bitdef displacement (0 for no animation)
; H = new row coord in chars
; L = new col coord in chars
; D = new horizontal rotation (0..7) ie horizontal pixel position
; E = new vertical rotation (0..7) ie vertical pixel position


ld a, (_gpit)
sla a
ld c, a
ld b, 0
ld hl, _sp_moviles
add hl, bc
ld e, (hl)
inc hl
ld d, (hl)
push de
pop ix


ld iy, vpClipStruct


ld bc, 0


ld hl, 0xfefe


ld de, 0

call SPMoveSprAbs
#endasm

}
}
# 276
}
# 344 "engine/engine.h"
void active_sleep (int espera) {
do {

gpjt = 250; do { gpit = 1; } while (--gpjt);
#asm
#endasm
# 356
if (button_pressed ()) break;

} while (--espera);
sp_Border (0);
}


void run_fire_script (void) {
run_script (2 * 10 * 2 + 2);
run_script (n_pant + n_pant + 1);
}
# 372
unsigned int keyscancodes [] = {




0x02fb, 0x02fd, 0x01fd, 0x04fd, 0x017f, 0,
0x01fb, 0x01fd, 0x02df, 0x01df, 0x017f, 0,

};


void select_joyfunc (void) {
#asm
#endasm
#asm
# 400
; Music generated by beepola
call musicstart
#endasm



while (1) {
gpit = sp_GetKey ();

if (gpit == '1' || gpit == '2') {
joyfunc = sp_JoyKeyboard;
gpjt = (gpit - '1') ? 6 : 0;
# 419
keys.up = keyscancodes [gpjt ++];
keys.down = keyscancodes [gpjt ++];
keys.left = keyscancodes [gpjt ++];
keys.right = keyscancodes [gpjt ++];
keys.fire = keyscancodes [gpjt ++];

break;
} else if (gpit == '3') {
joyfunc = sp_JoyKempston;
break;
} else if (gpit == '4') {
joyfunc = sp_JoySinclair1;
break;
}
}
#asm
# 439
di
#endasm



}
# 7 "./engine/hud.h"
unsigned char objs_old, keys_old, life_old, killed_old;
# 18
unsigned char flag_old;
# 29
void update_hud (void) {
# 37
if (p_life != life_old) {
_x = 1; _y = 23; _t = p_life; print_number2 ();
life_old = p_life;
}
# 80
if (flags [1] != flag_old) {
_x = 4; _y = 23; _t = flags [1]; print_number2 ();
flag_old = flags [1];
}
# 100
}
# 53 "engine/flickscreen.h"
void flick_screen (void) {
# 88
if (p_x == 0 && p_vx < 0 && x_pant > 0) {
n_pant = n_pant - 1; p_x = 14336;
}
if (p_x == 14336 && p_vx > 0 && (x_pant < (10 - 1))) {
n_pant = n_pant + 1; p_x = 0;
}
if (p_y == 0 && p_vy < 0 && y_pant > 0) {
n_pant = n_pant - 10; p_y = 9216;
}
if (p_y == 9216 && p_vy > 0 && (y_pant < (2 - 1))) {
n_pant = n_pant + 10; p_y = 0;
if (p_vy > 256) p_vy = 256;
}

}
# 1 "./mainloop/hide_sprites.h"
void hide_sprites (unsigned char which_ones) {
if (which_ones == 0) {
#asm


ld ix, (_sp_player)
ld iy, vpClipStruct
ld bc, 0
ld hl, 0xdede
ld de, 0
call SPMoveSprAbs
#endasm

}
#asm
# 19
xor a
.hide_sprites_enems_loop
ld (_gpit), a

sla a
ld c, a
ld b, 0
ld hl, _sp_moviles
add hl, bc
ld e, (hl)
inc hl
ld d, (hl)
push de
pop ix

ld iy, vpClipStruct
ld bc, 0
ld hl, 0xfefe
ld de, 0

call SPMoveSprAbs

ld a, (_gpit)
inc a
cp 3
jr nz, hide_sprites_enems_loop
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
# 150
}
# 10 "mainloop/mainloop.h"
unsigned char action_pressed;
# 20
unsigned char success;
unsigned char playing;



void main (void) {




cortina ();
#asm


di
#endasm
# 10 "./mainloop/mysystem.h"
sp_Initialize (0, 0);
sp_Border (0x00);


sp_AddMemory(0, 40, 14, 61440 - 40 * 15);
# 26
joyfunc = sp_JoyKeyboard;


gen_pt = tileset;
gpit = 0; do {
sp_TileArray (gpit, gen_pt);
gen_pt += 8;
gpit ++;
} while (gpit);
# 15 "./mainloop/sprdefs.h"
sp_player = sp_CreateSpr (0x00, 3, sprite_2_a, 1, 0x80);
sp_AddColSpr (sp_player, sprite_2_b, 0x80);
sp_AddColSpr (sp_player, sprite_2_c, 0x80);
p_c_f = p_n_f = sprite_2_a;

for (gpit = 0; gpit < 3; gpit ++) {
sp_moviles [gpit] = sp_CreateSpr(0x00, 3, sprite_9_a, 3, 0x80);
sp_AddColSpr (sp_moviles [gpit], sprite_9_b, 0x80);
sp_AddColSpr (sp_moviles [gpit], sprite_9_c, 0x80);
en_an_c_f [gpit] = en_an_n_f [gpit] = sprite_9_a;
}
#asm
#endasm
# 62 "mainloop/mainloop.h"
while (1) {
# 1 "./mainloop/title_screen.h"
sp_UpdateNow();
# 8
unpack ((unsigned int) (s_title), 16384);
# 14
select_joyfunc ();
# 3 "./mainloop/game_init.h"
msc_init_all ();
# 31
script_result = 0;
# 5 "./mainloop/level_init.h"
playing = 1;
# 20
main_script_offset = (unsigned int) (main_script);
# 43
n_pant = 10;


init_player ();
maincounter = 0;


script_result = 0;

msc_init_all ();
# 58
{


run_script (10 * 2 * 2);
}
# 68
do_respawn = 1;
#asm
#endasm
# 102
objs_old = keys_old = life_old = killed_old = 0xff;
# 111
flag_old = 99;
# 119
success = 0;
# 143
o_pant = 0xff;
# 149
no_draw = 0;
# 97 "mainloop/mainloop.h"
while (playing) {
# 103
if (n_pant != o_pant) {
o_pant = n_pant;
draw_scr ();
# 109
}


update_hud ();


maincounter ++;
half_life = !half_life;


move ();
# 130
mueve_bicharracos ();
# 157
do_tilanims ();
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
# 104 "./mainloop/update_sprites.h"
if (!(p_state & 2) || half_life == 0)

{
#asm


ld ix, (_sp_player)
ld iy, vpClipStruct

ld hl, (_p_n_f)
ld de, (_p_c_f)
or a
sbc hl, de
ld b, h
ld c, l

ld a, (_gpy)
srl a
srl a
srl a
add 1
ld h, a

ld a, (_gpx)
srl a
srl a
srl a
add 1
ld l, a

ld a, (_gpx)
and 7
ld d, a

ld a, (_gpy)
and 7
ld e, a

call SPMoveSprAbs
#endasm

} else {
#asm


ld ix, (_sp_player)
ld iy, vpClipStruct

ld hl, (_p_n_f)
ld de, (_p_c_f)
or a
sbc hl, de
ld b, h
ld c, l

ld hl, 0xfefe
ld de, 0
call SPMoveSprAbs
#endasm

}


p_c_f = p_n_f;
#asm
#endasm
#asm
#endasm
#asm
#endasm
#asm
#endasm
# 164 "mainloop/mainloop.h"
sp_UpdateNow();
# 180
if (p_state == 2) {
p_state_ct --;
if (p_state_ct == 0)
p_state = 0;
}
# 1 "./mainloop/scripting.h"
gpit = (joyfunc) (&keys);
# 11
if ((gpit & 0x02) == 0) {
# 16
if (action_pressed == 0) {
action_pressed = 1;

run_fire_script ();
}
} else {
action_pressed = 0;
}
# 34
if (f_zone_ac) {
if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
run_fire_script ();
}
}
# 28 "./mainloop/win_game.h"
if (script_result == 1 || script_result > 2) {
# 33
success = 1;
playing = 0;
}
# 1 "./mainloop/game_over.h"
if (p_life == 0

|| script_result == 2
# 8
) {
playing = 0;
}
# 231 "mainloop/mainloop.h"
flick_screen ();
# 238
}
# 244
hide_sprites (0);
sp_UpdateNow ();
# 293
if (success) {
game_ending ();
} else {

game_over ();
}
active_sleep (500);
cortina ();

}
}
#asm
# 9 "sound/music.h"
; *****************************************************************************
; * Phaser1 Engine, with synthesised drums
; *
; * Original code by Shiru - .http
; * Modified by Chris Cowley
; *
; * Produced by Beepola v1.05.01
; ******************************************************************************

.musicstart
LD HL,MUSICDATA ; <- Pointer to Music Data. Change
; this to play a different song
LD A,(HL) ; Get the loop start pointer
LD (PATTERN_LOOP_BEGIN),A
INC HL
LD A,(HL) ; Get the song end pointer
LD (PATTERN_LOOP_END),A
INC HL
LD E,(HL)
INC HL
LD D,(HL)
INC HL
LD (INSTRUM_TBL),HL
LD (CURRENT_INST),HL
ADD HL,DE
LD (PATTERN_ADDR),HL
XOR A
LD (PATTERN_PTR),A ; Set the pattern pointer to zero
LD H,A
LD L,A
LD (NOTE_PTR),HL ; Set the note offset (within this pattern) to 0

.player
;DI
PUSH IY
;LD A,BORDER_COL
xor a
LD H,$00
LD L,A
LD (CNT_1A),HL
LD (CNT_1B),HL
LD (DIV_1A),HL
LD (DIV_1B),HL
LD (CNT_2),HL
LD (DIV_2),HL
LD (OUT_1),A
LD (OUT_2),A
JR MAIN_LOOP

; ********************************************************************************************************
; * NEXT_PATTERN
; *
; * Select the next pattern in sequence (and handle looping if weve reached PATTERN_LOOP_END
; * Execution falls through to PLAYNOTE to play the first note from our next pattern
; ********************************************************************************************************
.next_pattern
LD A,(PATTERN_PTR)
INC A
INC A
DEFB $FE ; CP n
.pattern_loop_end DEFB 0
JR NZ,NO_PATTERN_LOOP
; Handle Pattern Looping at and of song
DEFB $3E ; LD A,n
.pattern_loop_begin DEFB 0
.no_pattern_loop LD (PATTERN_PTR),A
LD HL,$0000
LD (NOTE_PTR),HL ; Start of pattern (NOTE_PTR = 0)

.main_loop
LD IYL,0 ; Set channel = 0

.read_loop
LD HL,(PATTERN_ADDR)
LD A,(PATTERN_PTR)
LD E,A
LD D,0
ADD HL,DE
LD E,(HL)
INC HL
LD D,(HL) ; Now DE = Start of Pattern data
LD HL,(NOTE_PTR)
INC HL ; Increment the note pointer and...
LD (NOTE_PTR),HL ; ..store it
DEC HL
ADD HL,DE ; Now HL = address of note data
LD A,(HL)
OR A
JR Z,NEXT_PATTERN ; select next pattern

BIT 7,A
JP Z,RENDER ; Play the currently defined note(S) and drum
LD IYH,A
AND $3F
CP $3C
JP NC,OTHER ; Other parameters
ADD A,A
LD B,0
LD C,A
LD HL,FREQ_TABLE
ADD HL,BC
LD E,(HL)
INC HL
LD D,(HL)
LD A,IYL ; IYL = 0 for channel 1, or = 1 for channel 2
OR A
JR NZ,SET_NOTE2
LD (DIV_1A),DE
EX DE,HL

DEFB $DD,$21 ; LD IX,nn
.current_inst
DEFW $0000

LD A,(IX+$00)
OR A
JR Z,L809B ; Original code jumps into byte 2 of the DJNZ (invalid opcode FD)
LD B,A
.l8098 ADD HL,HL
DJNZ L8098
.l809b LD E,(IX+$01)
LD D,(IX+$02)
ADD HL,DE
LD (DIV_1B),HL
LD IYL,1 ; Set channel = 1
LD A,IYH
AND $40
JR Z,READ_LOOP ; No phase reset

LD HL,OUT_1 ; Reset phaser
RES 4,(HL)
LD HL,$0000
LD (CNT_1A),HL
LD H,(IX+$03)
LD (CNT_1B),HL
JR READ_LOOP

.set_note2
LD (DIV_2),DE
LD A,IYH
LD HL,OUT_2
RES 4,(HL)
LD HL,$0000
LD (CNT_2),HL
JP READ_LOOP

.set_stop
LD HL,$0000
LD A,IYL
OR A
JR NZ,SET_STOP2
; Stop channel 1 note
LD (DIV_1A),HL
LD (DIV_1B),HL
LD HL,OUT_1
RES 4,(HL)
LD IYL,1
JP READ_LOOP
.set_stop2
; Stop channel 2 note
LD (DIV_2),HL
LD HL,OUT_2
RES 4,(HL)
JP READ_LOOP

.other CP $3C
JR Z,SET_STOP ; Stop note
CP $3E
JR Z,SKIP_CH1 ; No changes to channel 1
INC HL ; Instrument change
LD L,(HL)
LD H,$00
ADD HL,HL
LD DE,(NOTE_PTR)
INC DE
LD (NOTE_PTR),DE ; Increment the note pointer

DEFB $01 ; LD BC,nn
.instrum_tbl
DEFW $0000

ADD HL,BC
LD (CURRENT_INST),HL
JP READ_LOOP

.skip_ch1
LD IYL,$01
JP READ_LOOP

.exit_player
LD HL,$2758
EXX
POP IY
;EI
RET

.render
AND $7F ; L813A
CP $76
JP NC,DRUMS
LD D,A
EXX
DEFB $21 ; LD HL,nn
.cnt_1a DEFW $0000
DEFB $DD,$21 ; LD IX,nn
.cnt_1b DEFW $0000
DEFB $01 ; LD BC,nn
.div_1a DEFW $0000
DEFB $11 ; LD DE,nn
.div_1b DEFW $0000
DEFB $3E ; LD A,n
.out_1 DEFB $0
EXX
EX AF,AF ; beware!
DEFB $21 ; LD HL,nn
.cnt_2 DEFW $0000
DEFB $01 ; LD BC,nn
.div_2 DEFW $0000
DEFB $3E ; LD A,n
.out_2 DEFB $00

.play_note
; Read keyboard
LD E,A
XOR A
IN A,($FE)
OR $E0
INC A

.player_wait_key
JR NZ,EXIT_PLAYER
LD A,E
LD E,0

.l8168 EXX
EX AF,AF ; beware!
ADD HL,BC
OUT ($FE),A
JR C,L8171
JR L8173
.l8171 XOR $10
.l8173 ADD IX,DE
JR C,L8179
JR L817B
.l8179 XOR $10
.l817b EX AF,AF ; beware!
OUT ($FE),A
EXX
ADD HL,BC
JR C,L8184
JR L8186
.l8184 XOR $10
.l8186 NOP
JP L818A

.l818a EXX
EX AF,AF ; beware!
ADD HL,BC
OUT ($FE),A
JR C,L8193
JR L8195
.l8193 XOR $10
.l8195 ADD IX,DE
JR C,L819B
JR L819D
.l819b XOR $10
.l819d EX AF,AF ; beware!
OUT ($FE),A
EXX
ADD HL,BC
JR C,L81A6
JR L81A8
.l81a6 XOR $10
.l81a8 NOP
JP L81AC

.l81ac EXX
EX AF,AF ; beware!
ADD HL,BC
OUT ($FE),A
JR C,L81B5
JR L81B7
.l81b5 XOR $10
.l81b7 ADD IX,DE
JR C,L81BD
JR L81BF
.l81bd XOR $10
.l81bf EX AF,AF ; beware!
OUT ($FE),A
EXX
ADD HL,BC
JR C,L81C8
JR L81CA
.l81c8 XOR $10
.l81ca NOP
JP L81CE

.l81ce EXX
EX AF,AF ; beware!
ADD HL,BC
OUT ($FE),A
JR C,L81D7
JR L81D9
.l81d7 XOR $10
.l81d9 ADD IX,DE
JR C,L81DF
JR L81E1
.l81df XOR $10
.l81e1 EX AF,AF ; beware!
OUT ($FE),A
EXX
ADD HL,BC
JR C,L81EA
JR L81EC
.l81ea XOR $10

.l81ec DEC E
JP NZ,L8168

EXX
EX AF,AF ; beware!
ADD HL,BC
OUT ($FE),A
JR C,L81F9
JR L81FB
.l81f9 XOR $10
.l81fb ADD IX,DE
JR C,L8201
JR L8203
.l8201 XOR $10
.l8203 EX AF,AF ; beware!
OUT ($FE),A
EXX
ADD HL,BC
JR C,L820C
JR L820E
.l820c XOR $10

.l820e DEC D
JP NZ,PLAY_NOTE

LD (CNT_2),HL
LD (OUT_2),A
EXX
EX AF,AF ; beware!
LD (CNT_1A),HL
LD (CNT_1B),IX
LD (OUT_1),A
JP MAIN_LOOP

; ************************************************************
; * DRUMS - Synthesised
; ************************************************************
.drums
ADD A,A ; On entry A=$75+Drum number (i.e. $76 to $7E)
LD B,0
LD C,A
LD HL,DRUM_TABLE - 236
ADD HL,BC
LD E,(HL)
INC HL
LD D,(HL)
EX DE,HL
JP (HL)

.drum_tone1 LD L,16
JR DRUM_TONE
.drum_tone2 LD L,12
JR DRUM_TONE
.drum_tone3 LD L,8
JR DRUM_TONE
.drum_tone4 LD L,6
JR DRUM_TONE
.drum_tone5 LD L,4
JR DRUM_TONE
.drum_tone6 LD L,2
.drum_tone
LD DE,3700
LD BC,$0101

xor a
.dt_loop0 OUT ($FE),A
DEC B
JR NZ,DT_LOOP1
XOR 16
LD B,C
EX AF,AF ; beware!
LD A,C
ADD A,L
LD C,A
EX AF,AF ; beware!
.dt_loop1 DEC E
JR NZ,DT_LOOP0
DEC D
JR NZ,DT_LOOP0
JP MAIN_LOOP

.drum_noise1 LD DE,2480
LD IXL,1
JR DRUM_NOISE
.drum_noise2 LD DE,1070
LD IXL,10
JR DRUM_NOISE
.drum_noise3 LD DE,365
LD IXL,101
.drum_noise
LD H,D
LD L,E

xor a
LD C,A
.dn_loop0 LD A,(HL)
AND 16
OR C
OUT ($FE),A
LD B,IXL
.dn_loop1 DJNZ DN_LOOP1
INC HL
DEC E
JR NZ,DN_LOOP0
DEC D
JR NZ,DN_LOOP0
JP MAIN_LOOP

.pattern_addr DEFW $0000
.pattern_ptr DEFB 0
.note_ptr DEFW $0000

; **************************************************************
; * Frequency Table
; **************************************************************
.freq_table
DEFW 178,189,200,212,225,238,252,267,283,300,318,337
DEFW 357,378,401,425,450,477,505,535,567,601,637,675
DEFW 715,757,802,850,901,954,1011,1071,1135,1202,1274,1350
DEFW 1430,1515,1605,1701,1802,1909,2023,2143,2270,2405,2548,2700
DEFW 2860,3030,3211,3402,3604,3818,4046,4286,4541,4811,5097,5400

; *****************************************************************
; * Synth Drum Lookup Table
; *****************************************************************
.drum_table
DEFW DRUM_TONE1,DRUM_TONE2,DRUM_TONE3,DRUM_TONE4,DRUM_TONE5,DRUM_TONE6
DEFW DRUM_NOISE1,DRUM_NOISE2,DRUM_NOISE3


.MUSICDATA
DEFB 0 ; Pattern loop begin * 2
DEFB 26 ; Song length * 2
DEFW 16 ; Offset to start of song (length of instrument table)
DEFB 0 ; Multiple
DEFW 20 ; Detune
DEFB 0 ; Phase
DEFB 1 ; Multiple
DEFW 5 ; Detune
DEFB 0 ; Phase
DEFB 0 ; Multiple
DEFW 10 ; Detune
DEFB 1 ; Phase
DEFB 1 ; Multiple
DEFW 25 ; Detune
DEFB 5 ; Phase

.PATTERNDATA DEFW PAT0
DEFW PAT1
DEFW PAT2
DEFW PAT3
DEFW PAT8
DEFW PAT4
DEFW PAT5
DEFW PAT6
DEFW PAT7
DEFW PAT4
DEFW PAT5
DEFW PAT10
DEFW PAT9

; *** Pattern data - $00 marks the end of a pattern ***
.PAT0
DEFB $BD,2
DEFB 149
DEFB 149
DEFB 6
DEFB 151
DEFB 6
DEFB 152
DEFB 6
DEFB 154
DEFB 6
DEFB 156
DEFB 148
DEFB 6
DEFB 157
DEFB 6
DEFB 160
DEFB 6
DEFB 161
DEFB 6
DEFB $00
.PAT1
DEFB $BD,2
DEFB 163
DEFB 145
DEFB 6
DEFB 164
DEFB 6
DEFB 166
DEFB 6
DEFB 168
DEFB 6
DEFB 169
DEFB 148
DEFB 6
DEFB 172
DEFB 6
DEFB 173
DEFB 6
DEFB 175
DEFB 6
DEFB $00
.PAT2
DEFB $BD,2
DEFB 176
DEFB 149
DEFB 6
DEFB 175
DEFB 6
DEFB 173
DEFB 6
DEFB 172
DEFB 6
DEFB 173
DEFB 151
DEFB 6
DEFB 175
DEFB 6
DEFB 176
DEFB 6
DEFB 175
DEFB 6
DEFB $00
.PAT3
DEFB $BD,2
DEFB 176
DEFB 152
DEFB 14
DEFB 175
DEFB 14
DEFB 173
DEFB 14
DEFB 172
DEFB 14
DEFB $00
.PAT4
DEFB $BD,2
DEFB 149
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 3
DEFB 151
DEFB 161
DEFB 118
DEFB 2
DEFB 190
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 126
DEFB 2
DEFB 151
DEFB 161
DEFB 3
DEFB 152
DEFB 149
DEFB 121
DEFB 2
DEFB 190
DEFB 161
DEFB 118
DEFB 2
DEFB 190
DEFB 148
DEFB 123
DEFB 2
DEFB 190
DEFB 160
DEFB 122
DEFB 2
DEFB 154
DEFB 160
DEFB 121
DEFB 2
DEFB 190
DEFB 148
DEFB 123
DEFB 2
DEFB 190
DEFB 160
DEFB 126
DEFB 2
DEFB 190
DEFB 160
DEFB 118
DEFB 2
DEFB 156
DEFB 148
DEFB 118
DEFB 2
DEFB 190
DEFB 160
DEFB 126
DEFB 2
DEFB $00
.PAT5
DEFB $BD,2
DEFB 190
DEFB 145
DEFB 118
DEFB 2
DEFB 190
DEFB 157
DEFB 3
DEFB 154
DEFB 157
DEFB 118
DEFB 2
DEFB 190
DEFB 145
DEFB 118
DEFB 2
DEFB 190
DEFB 157
DEFB 126
DEFB 2
DEFB 190
DEFB 157
DEFB 3
DEFB 152
DEFB 145
DEFB 121
DEFB 2
DEFB 190
DEFB 157
DEFB 118
DEFB 2
DEFB 190
DEFB 148
DEFB 123
DEFB 2
DEFB 190
DEFB 160
DEFB 122
DEFB 2
DEFB 151
DEFB 160
DEFB 121
DEFB 2
DEFB 190
DEFB 148
DEFB 123
DEFB 2
DEFB 190
DEFB 160
DEFB 126
DEFB 2
DEFB 190
DEFB 160
DEFB 118
DEFB 2
DEFB $BD,0
DEFB 152
DEFB 149
DEFB 118
DEFB 2
DEFB 154
DEFB 163
DEFB 126
DEFB 2
DEFB $00
.PAT6
DEFB $BD,0
DEFB 156
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 3
DEFB 190
DEFB 161
DEFB 118
DEFB 2
DEFB 157
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 126
DEFB 2
DEFB 190
DEFB 161
DEFB 3
DEFB 156
DEFB 149
DEFB 121
DEFB 2
DEFB 190
DEFB 161
DEFB 118
DEFB 2
DEFB 190
DEFB 151
DEFB 123
DEFB 2
DEFB 190
DEFB 163
DEFB 122
DEFB 2
DEFB 152
DEFB 163
DEFB 126
DEFB 2
DEFB 190
DEFB 151
DEFB 126
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB 190
DEFB 151
DEFB 126
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB $00
.PAT7
DEFB $BD,6
DEFB 164
DEFB 152
DEFB 118
DEFB 2
DEFB 190
DEFB 164
DEFB 3
DEFB 190
DEFB 164
DEFB 118
DEFB 2
DEFB 176
DEFB 152
DEFB 118
DEFB 2
DEFB 188
DEFB 164
DEFB 126
DEFB 2
DEFB 176
DEFB 164
DEFB 3
DEFB 188
DEFB 152
DEFB 121
DEFB 2
DEFB 164
DEFB 164
DEFB 118
DEFB 2
DEFB 166
DEFB 154
DEFB 123
DEFB 2
DEFB 190
DEFB 154
DEFB 122
DEFB 2
DEFB 190
DEFB 166
DEFB 126
DEFB 2
DEFB 178
DEFB 154
DEFB 126
DEFB 2
DEFB 188
DEFB 154
DEFB 126
DEFB 2
DEFB 178
DEFB 166
DEFB 126
DEFB 2
DEFB 188
DEFB 156
DEFB 126
DEFB 2
DEFB 166
DEFB 157
DEFB 126
DEFB 2
DEFB $00
.PAT8
DEFB $BD,0
DEFB 176
DEFB 154
DEFB 8
DEFB 175
DEFB 152
DEFB 8
DEFB 173
DEFB 151
DEFB 8
DEFB 172
DEFB 149
DEFB 8
DEFB 169
DEFB 148
DEFB 8
DEFB 168
DEFB 145
DEFB 8
DEFB 166
DEFB 144
DEFB 8
DEFB 164
DEFB 142
DEFB 8
DEFB 163
DEFB 140
DEFB 32
DEFB 161
DEFB 149
DEFB 32
DEFB $00
.PAT9
DEFB $BD,0
DEFB 171
DEFB 152
DEFB 118
DEFB 2
DEFB 190
DEFB 164
DEFB 3
DEFB 169
DEFB 164
DEFB 118
DEFB 2
DEFB 190
DEFB 152
DEFB 118
DEFB 2
DEFB 168
DEFB 164
DEFB 126
DEFB 2
DEFB 190
DEFB 164
DEFB 3
DEFB 166
DEFB 152
DEFB 121
DEFB 2
DEFB 190
DEFB 164
DEFB 118
DEFB 2
DEFB 190
DEFB 154
DEFB 123
DEFB 2
DEFB 190
DEFB 154
DEFB 122
DEFB 2
DEFB 168
DEFB 166
DEFB 126
DEFB 2
DEFB 190
DEFB 154
DEFB 126
DEFB 2
DEFB 169
DEFB 154
DEFB 126
DEFB 2
DEFB 190
DEFB 166
DEFB 126
DEFB 2
DEFB 190
DEFB 156
DEFB 126
DEFB 2
DEFB 190
DEFB 157
DEFB 126
DEFB 2
DEFB $00
.PAT10
DEFB $BD,0
DEFB 156
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 3
DEFB 190
DEFB 161
DEFB 118
DEFB 2
DEFB 157
DEFB 149
DEFB 118
DEFB 2
DEFB 190
DEFB 161
DEFB 126
DEFB 2
DEFB 190
DEFB 161
DEFB 3
DEFB 159
DEFB 149
DEFB 121
DEFB 2
DEFB 190
DEFB 161
DEFB 118
DEFB 2
DEFB 190
DEFB 151
DEFB 123
DEFB 2
DEFB 190
DEFB 163
DEFB 122
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB 190
DEFB 151
DEFB 126
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB 190
DEFB 163
DEFB 126
DEFB 2
DEFB 171
DEFB 151
DEFB 126
DEFB 2
DEFB 169
DEFB 163
DEFB 126
DEFB 2
DEFB $00
#endasm
