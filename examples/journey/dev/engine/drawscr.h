// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// drawscr.h
// Screen drawing functions

void advance_worm (void) {
	_x = rdx; _y = rdy; _n = behs [_rdt]; _t = gpd; update_tile ();
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

	#if defined UNPACKED || defined PACKED
		#ifdef UNPACKED_MAP
			map_pointer = map + (n_pant * 150);
		#else
			map_pointer = map + (n_pant * 75);
		#endif

		gpit = gpx = gpy = 0;
		#ifdef TWO_SETS
			t_offs = TWO_SETS_SEL;
		#endif
		#ifdef TWO_SETS_MAPPED
			t_offs = (*(map + (MAP_W * MAP_H * 75) + n_pant)) << 5;
		#endif

		// Draw 150 tiles
		do {
			gpjt = rand () & 15;

			#ifdef UNPACKED_MAP
				// Mapa tipo UNPACKED
				gpd = *map_pointer ++;
				map_attr [gpit] = behs [gpd];
				map_buff [gpit] = gpd;
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
				
				_rdt = gpd;
				#ifndef NO_ALT_TILE
					if (gpd == 0 && gpjt == 1) gpd = 19;
				#endif
			#endif
			
			#ifdef BREAKABLE_WALLS
				brk_buff [gpit] = 0;
			#endif
			
			advance_worm ();

			++ gpx; if (gpx == 15) { gpx = 0; ++ gpy; }
		} while (gpit ++ < 149);
	#else

		#asm
			// Get screen address from index.
			// RLE format

			._draw_scr_get_scr_address
				ld  a, (_n_pant)
				sla a
				ld  d, 0
				ld  e, a
				ld  hl, _mapa
				add hl, de 		; HL = map + (n_pant << 1)
				ld  e, (hl)
				inc hl
				ld  d, (hl) 	; DE = index
				ld  hl, _mapa
				add hl, de      ; HL = map + index
				ld  (_gp_map), hl

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

				ld  hl, (_gp_map)
				ld  a, (hl)
				inc hl
				ld  (_gp_map), hl
				
				ld  c, a
			#if RLE_MAP == 44
				and 0x0f
			#elif RLE_MAP == 53
				and 0x1f
			#else
				and 0x3f
			#endif			
				ld  (_rdt), a

				ld  a, c
				ld  (_rdct), a

			._draw_scr_advance_loop
				ld  a, (_rdct)
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
				ld  (_rdct), a

				call _advance_worm

				// That's it!

				jr _draw_scr_advance_loop

			._draw_scr_advance_loop_done
				call _advance_worm

				jr _draw_scr_loop

			._draw_scr_loop_done			
		#endasm

	#endif

	// Object setup
	#ifndef DISABLE_HOTSPOTS
		hotspot_x = hotspot_y = 240;
		gpx = (hotspots [n_pant].xy >> 4);
		gpy = (hotspots [n_pant].xy & 15);

		#ifndef USE_HOTSPOTS_TYPE_3
			if ((hotspots [n_pant].act == 1 && hotspots [n_pant].tipo) ||
				(hotspots [n_pant].act == 0 && (rand () & 7) == 2)) {
				hotspot_x = gpx << 4;
				hotspot_y = gpy << 4;
				orig_tile = map_buff [15 * gpy + gpx];
				_x = gpx; _y = gpy;
				_t = 16 + (hotspots [n_pant].act ? hotspots [n_pant].tipo : 0);
				draw_coloured_tile_gamearea ();
			}
		#else
			// Modificación para que los hotspots de tipo 3 sean recargas directas:
			if (hotspots [n_pant].act == 1 && hotspots [n_pant].tipo) {
		        hotspot_x = gpx << 4;
		        hotspot_y = gpy << 4;
		        orig_tile = map_buff [15 * gpy + gpx];
		        _x = gpx; _y = gpy;
		        _t = 16 + (hotspots [n_pant].tipo != 3 ? hotspots [n_pant].tipo : 0);
		        draw_coloured_tile_gamearea ();
		    }
		#endif
	#endif

	#ifndef DEACTIVATE_KEYS
		// Open locks
		for (gpit = 0; gpit < MAX_BOLTS; gpit ++) {
			if (bolts [gpit].np == n_pant && !bolts [gpit].st) {
				_x = bolts [gpit].x;
				_y = bolts [gpit].y;
				_t = 0;
				draw_coloured_tile_gamearea ();
				gpd = 15 * gpy + gpx;
				map_attr [gpd] = 0;
				map_buff [gpd] = 0;
			}
		}
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
			_x = 12; _y = 12; _t = 71; gp_gen = "LEVEL"; print_str ();
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
	enoffs = n_pant * 3;

	#include "engine/enemsinit.h"

	#ifndef RESPAWN_ON_REENTER
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
			x_pant = n_pant % level_data->map_w;
			y_pant = n_pant / level_data->map_w;
		#else
			x_pant = n_pant % MAP_W; y_pant = n_pant / MAP_W;
		#endif
	#endif

	#if defined (DIE_AND_RESPAWN)
		#if defined (SWITCHABLE_ENGINES)
			if (p_engine == SENG_SWIM) {
				p_safe_pant = n_pant;
				p_safe_x = (p_x >> 10);
				p_safe_y = (p_y >> 10);
			}
		#endif
		#if defined (PLAYER_GENITAL)
			p_safe_pant = n_pant;
			p_safe_x = (p_x >> 6);
			p_safe_y = (p_y >> 6);
		#endif
	#endif

	// CUSTOM {
		// Shows screen name
		// do_extern_action (1 + n_pant);
	// }
	invalidate_viewport ();

	is_rendering = 0;
}
