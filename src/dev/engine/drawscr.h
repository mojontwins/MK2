// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// drawscr.h
// Screen drawing functions

#ifdef CUSTOM_BACKGROUND
	#include "my/custom_background.h"
#endif

void advance_worm (void) {
	#asm
		#ifdef ALT_TILE
			call _rand 
			ld   a, l
			and  15
			ld   (_gpjt), a
		#endif

			ld  bc, (_gpit)
			ld  b, 0

		#ifdef BREAKABLE_WALLS
			xor  a
			ld  hl, _brk_buff
			add hl, bc
			ld  (hl), a			
		#endif
			
			ld  de, (_gpt)
			ld  d, 0
			ld  hl, _behs
			add hl, de
			ld  a, (hl)

			ld  hl, _map_attr
			add hl, bc
			ld  (hl), a

	#endasm
	#ifdef CUSTOM_BACKGROUND
		custom_bg (); // Change gpd!
	#endif
	#asm
			ld  a, (_gpd)
			#ifdef ALT_TILE
				ld  d, a
				or  a
				jr  nz, _draw_scr_alt_tile_skip

				ld  a, (_gpjt)
				cp   1
				jr  nz, _draw_scr_alt_tile_skip

				ld  a, ALT_TILE				
				jr _draw_scr_alt_tile_done

			._draw_scr_alt_tile_skip
				ld  a, d

			._draw_scr_alt_tile_done
			#endif

			ld  hl, _map_buff
			add hl, bc
			ld  (hl), a

			ld  (__t), a
			call _draw_coloured_tile

	#ifdef ENABLE_TILANIMS
		#endasm
			
		if (IS_TILANIM (_t)) { 
				
			#asm
					ld  a, (__x)
					sub VIEWPORT_X
					;and 0xfe	; _x is always even!
					sla a
					sla a
					sla a
					ld  c, a
					ld  a, (__y)
					sub VIEWPORT_Y
					srl a
					add c
					ld  (__n), a
					call _tilanims_add
			#endasm
		}

		#asm
	#endif

			ld  a, (__x)
			add 2
			cp  30 + VIEWPORT_X
			jr  c, _advance_worm_no_inc_y

			ld  a, (__y)
			add 2
			ld  (__y), a

			ld  a, VIEWPORT_X

		._advance_worm_no_inc_y
			ld  (__x), a

			ld  hl, _gpit
			inc (hl)
	#endasm
}

#ifdef ENABLE_SHOOTERS
	void init_cocos (void);
#endif

#if defined (TWO_SETS) || defined (TWO_SETS_MAPPED)
	unsigned char t_offs;
#endif
void draw_scr_background (void) {
	#ifdef COMPRESSED_LEVELS
		seed1 [0] = n_pant; seed2 [0] = level;
		srand ();
	#else
		seed1 [0] = n_pant; seed2 [0] = n_pant + 1;
		srand ();
	#endif

	#if defined PACKED_MAP || defined UNPACKED_MAP

		#ifdef UNPACKED_MAP
			map_pointer = map + (n_pant << 7) + (n_pant << 4) + (n_pant << 2) + (n_pant << 1);
		#else
			map_pointer = map + (n_pant << 6) + (n_pant << 3) + (n_pant << 1) + (n_pant);
		#endif

		#ifdef TWO_SETS
			t_offs = TWO_SETS_SEL;
		#endif
		#ifdef TWO_SETS_MAPPED
			t_offs = (*(map + (MAP_W * MAP_H * 75) + n_pant)) << 5;
		#endif

		// Draw 150 tiles

		/*
		gpit = 0; _x = VIEWPORT_X; _y = VIEWPORT_Y;
		do {
			gpjt = rand () & 15;

			#ifdef UNPACKED_MAP
				// Mapa tipo UNPACKED
				gpt = gpd = *map_pointer ++;				
			#else
				// Mapa tipo PACKED
				if (gpit & 1) {
					gpd = gpc & 15;
				} else {
					gpc = *map_pointer ++;
					gpd = gpc >> 4;
				}

				#if defined (TWO_SETS) || defined (TWO_SETS_MAPPED)
					gpd += t_offs;
				#endif
				
				gpt = gpd;

				#ifndef NO_ALT_TILE
					if (gpd == 0 && gpjt == 1) gpd = 19;
				#endif
			#endif
			
			#ifdef BREAKABLE_WALLS
				brk_buff [gpit] = 0;
			#endif
			
			advance_worm ();			
		} while (gpit < 150);
		*/

		#asm
			._draw_scr_packed_unpacked
				ld  a, VIEWPORT_X
				ld  (__x), a
				ld  a, VIEWPORT_Y
				ld  (__y), a

				xor a
				ld  (_gpit), a				
			._draw_scr_background_loop				

		#ifdef UNPACKED_MAP
				ld  hl, (_map_pointer)
				ld  a, (hl)
				inc hl
				ld  (_map_pointer), hl
				ld  (_gpd), a
				ld  (_gpt), a
		#else
				and 1
				jr  z, draw_scr_background_new_byte

				ld  a, (_gpc)
				and 15
				jr  draw_scr_background_set_t

			.draw_scr_background_new_byte
				ld  hl, (_map_pointer)
				ld  a, (hl)
				inc hl
				ld  (_map_pointer), hl
				ld  (_gpc), a
				srl a
				srl a
				srl a
				srl a

			.draw_scr_background_set_t

			#if defined (TWO_SETS) || defined (TWO_SETS_MAPPED)
				ld  c, a
				ld  a, (_t_offs)
				add c
			#endif

				ld  (_gpt), a
				ld  (_gpd), a				

		#endif
				call _advance_worm

				ld  a, (_gpit)
				cp  150
				jr  nz, _draw_scr_background_loop
		#endasm

	#else

		#asm
			// Get screen address from index.
			// RLE format

			._draw_scr_get_scr_address
				ld  a, (_n_pant)
				sla a
				ld  d, 0
				ld  e, a
				ld  hl, _map
				add hl, de 		; HL = map + (n_pant << 1)
				ld  e, (hl)
				inc hl
				ld  d, (hl) 	; DE = index
				ld  hl, _map
				add hl, de      ; HL = map + index
				ld  (_map_pointer), hl

			// Now decode & render the current screen 

			._draw_scr_rle
				xor a
				ld  (_gpit), a
				ld  a, VIEWPORT_X
				ld  (__x), a
				ld  a, VIEWPORT_Y
				ld  (__y), a

			._draw_scr_loop
				ld  a, (_gpit)
				cp  150
				jr  z, _draw_scr_loop_done

				ld  hl, (_map_pointer)
				ld  a, (hl)
				inc hl
				ld  (_map_pointer), hl
				
				ld  c, a
			#if RLE_MAP == 44
				and 0x0f
			#elif RLE_MAP == 53
				and 0x1f
			#else
				and 0x3f
			#endif			
				ld  (_gpt), a
				ld  (_gpd), a

				ld  a, c
				ld  (_gpc), a

			._draw_scr_advance_loop
				ld  a, (_gpc)
			#if RLE_MAP == 44
				cp  0x10
			#elif RLE_MAP == 53			
				cp  0x20
			#else
				cp  0x40
			#endif

				jr  c, _draw_scr_advance_loop_done

			#if RLE_MAP == 44
				sub 0x10
			#elif RLE_MAP == 53
				sub 0x20
			#else
				sub 0x40
			#endif
				ld  (_gpc), a

				call _advance_worm

				jr _draw_scr_advance_loop

			._draw_scr_advance_loop_done
				call _advance_worm

				jr _draw_scr_loop

			._draw_scr_loop_done			
		#endasm

	#endif

	// Object setup
	#ifndef DISABLE_HOTSPOTS
		/*
		hotspot_y = 240;
		_x = (hotspots [n_pant].xy >> 4);
		_y = (hotspots [n_pant].xy & 15);
	
		if (
			(hotspots [n_pant].act && hotspots [n_pant].tipo) 
			#ifndef USE_HOTSPOTS_TYPE_3				
				|| (hotspots [n_pant].act == 0 && (rand () & 7) == 2)
			#endif
		) {
			hotspot_x = _x << 4;
			hotspot_y = _y << 4;
			orig_tile = map_buff [(_y << 4) - _y + _x];

			#ifdef USE_HOTSPOTS_TYPE_3
				_t = 16 + (hotspots [n_pant].tipo != 3 ? hotspots [n_pant].tipo : 0);
			#else
				_t = 16 + (hotspots [n_pant].act ? hotspots [n_pant].tipo : 0);				
			#endif
			draw_coloured_tile_gamearea ();
		}	
		*/
		#asm 
				ld  a, 240
				ld  (_hotspot_y), a

				// Hotspots are 3-byte wide structs. No game will have more than 85 screens
				// in the same map so we can do the math in 8 bits:

				ld  a, (_n_pant)
				ld  b, a
				sla a
				add b

				ld  c, a
				ld  b, 0

				// BC = Index to the hotspots struct, which happens to be {xy, type, act}

				ld  hl, _hotspots
				add hl, bc

				// Now HL points to hotspots [n_pant]

				ld  a, (hl) 		// A = hotspots [n_pant].xy
				ld  b, a

				srl a
				srl a
				srl a
				srl a
				ld  (__x), a

				ld  a, b
				and 15
				ld  (__y), a

				inc hl 				// HL->hotspots [n_pant].type
				ld  b, (hl) 		// B = hotspots [n_pant].type
				inc hl 				// HL->hotspots [n_pant].type
				ld  c, (hl) 		// C = hotspots [n_pant].act

				// if (
				// 	(hotspots [n_pant].act && hotspots [n_pant].tipo) 

				ld  a, b
				and c
			
			#ifndef USE_HOTSPOTS_TYPE_3						
				jr  nz, _hotspots_setup_do

				// || (hotspots [n_pant].act == 0 && (rand () & 7) == 2)

				call _rand
				ld  a, l
				and 7
				cp  2		
			#endif

				jr  z, _hotspots_setup_done

			._hotspots_setup_do
				ld  a, (__x)
				ld  e, a
				sla a
				sla a
				sla a
				sla a
				ld  (_hotspot_x), a

				ld  a, (__y)
				ld  d, a
				sla a
				sla a
				sla a
				sla a
				ld  (_hotspot_y), a

				// orig_tile = map_buff [(_y << 4) - _y + _x];
				// A = (_y << 4), D = _y, E = _x, so
				sub d
				add e

				ld  e, a
				ld  d, 0
				ld  hl, _map_buff
				add hl, de
				ld  a, (hl)
				ld  (_orig_tile), a

			#ifdef USE_HOTSPOTS_TYPE_3
				// _t = 16 + (hotspots [n_pant].tipo != 3 ? hotspots [n_pant].tipo : 0);
				ld  a, b
				cp  3
				jp  nz, _hotspots_setup_set
			#else
				// _t = 16 + (hotspots [n_pant].act ? hotspots [n_pant].tipo : 0);	
				ld  a, c
				or  a
				jr  z, _hotspots_setup_set_refill

				ld  a, b
				jp  _hotspots_setup_set
			#endif

			._hotspots_setup_set_refill
				xor a
			._hotspots_setup_set
				add 16
				ld  (__t), a		

				call _draw_coloured_tile_gamearea

			._hotspots_setup_done
		#endasm
	#endif

	#ifndef DEACTIVATE_KEYS
		// Open locks
		/*
		for (gpit = 0; gpit < MAX_BOLTS; gpit ++) {
			if (bolts [gpit].np == n_pant && !bolts [gpit].st) {
				_x = bolts [gpit].x;
				_y = bolts [gpit].y;
				gpd = _x + (_y << 4) - _y;
				map_attr [gpd] = 0;
				map_buff [gpd] = 0;

				_t = 0;
				draw_coloured_tile_gamearea ();				
			}
		}
		*/

		#asm
				// BOLTS structure is 4 bytes wide: { np, x, y, st }
				ld  hl, _bolts
				ld  b, MAX_BOLTS
			._open_locks_loop
				push bc
				
				ld  a, (_n_pant)
				ld  c, a

				ld  a, (hl)			// A = bolts [gpit].np
				inc hl

				cp  c
				jr  nz, _open_locks_done
				
				ld  a, (hl)
				inc hl

				ld  d, a 			// D = bolts [gpit].x;

				ld  a, (hl)
				inc hl

				ld  e, a 			// E = bolts [gpit].y;

				ld  a, (hl)			// A = bolts [gpit].st
				inc hl

				or  a
				jr  nz, _open_locks_done				
				
			._open_locks_do
				ld  a, d
				ld  (__x), a
				ld  a, e
				ld  (__y), a
				
				sla a
				sla a
				sla a
				sla a
				sub e
				add d

				ld  b, 0
				ld  c, a
				xor a
				
				push hl 			// Save for later.
				
				ld  hl, _map_attr
				add hl, bc
				ld  (hl), a
				ld  hl, _map_buff
				add hl, bc
				ld  (hl), a

				ld  (__t), a

				call _draw_coloured_tile_gamearea

				pop hl

			._open_locks_done
				
				pop bc
				dec b
				jr  nz, _open_locks_loop
		#endasm
	#endif
}

void draw_scr (void) {
	is_rendering = 1;

	#ifdef ENABLE_TILANIMS
		tilanim_reset ();
	#endif

	#ifdef MAP_ATTRIBUTES
		if (cur_map_attr != map_attrs [n_pant]) {
			cur_map_attr = map_attrs [n_pant];
			if (cur_map_attr) load_subtileset (levels [level].resource + cur_map_attr, 1);
		}
	#endif	
		
	if (no_draw) {
		no_draw = 0;
	} else {
		#ifdef SHOW_LEVEL_ON_SCREEN
			blackout_area ();
			_x = 12; _y = 12; _t = 71; gp_gen = (unsigned char *) ("LEVEL"); print_str ();
			_x = 18; _y = 12; _t = n_pant + 1; print_number2 ();
			sp_UpdateNow ();
			active_sleep (500);
		#endif
		draw_scr_background ();
	}

	#ifdef ENABLE_FIRE_ZONE
		f_zone_ac = 0;
	#endif

	// Enemy initialization for this screen
	enoffs = n_pant + (n_pant << 1);

	enems_init ();
	
	#ifdef RESPAWN_ON_ENTER
		do_respawn = 1;
	#endif
	
	#ifdef ENABLE_FLOATING_OBJECTS
		FO_clear ();
	#endif

	#ifdef ENABLE_SIM
		sim_paint ();
	#endif

	#ifdef ENABLE_EXTRA_PRINTS
		extra_prints ();
	#endif

	#ifdef ENABLE_LEVEL_NAMES
		print_level_name ();
	#endif

	#ifdef ACTIVATE_SCRIPTING
		run_entering_script ();
	#endif

	#ifdef PLAYER_CAN_FIRE
		init_bullets ();
	#endif

	#ifdef ENABLE_SHOOTERS
		init_cocos ();
	#endif

	#if defined (PLAYER_CHECK_MAP_BOUNDARIES) || defined (PLAYER_CYCLIC_MAP)
		#ifdef COMPRESSED_LEVELS
			x_pant = n_pant % level_data.map_w;
			y_pant = n_pant / level_data.map_w;
		#else
			x_pant = n_pant % MAP_W; y_pant = n_pant / MAP_W;
		#endif
	#endif

	#if defined (DIE_AND_RESPAWN)
		#if defined (SWITCHABLE_ENGINES)
			if (p_engine == SENG_SWIM) {
				p_safe_pant = n_pant;
				p_safe_x = gpx >> 4;
				p_safe_y = gpy >> 4;
			}
		#endif
		#if defined (PLAYER_GENITAL)
			p_safe_pant = n_pant;
			p_safe_x = (p_x >> FIXBITS);
			p_safe_y = (p_y >> FIXBITS);
		#endif
	#endif

	invalidate_viewport ();

	is_rendering = 0;
}
