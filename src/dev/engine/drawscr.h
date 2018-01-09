// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// drawscr.h
// Screen drawing functions

#ifdef ENABLE_SHOOTERS
void __FASTCALL__ init_cocos (void);
#endif

#if defined (TWO_SETS) || defined (TWO_SETS_MAPPED)
unsigned char t_offs;
#endif
void __FASTCALL__ draw_scr_background (void) {
#ifdef COMPRESSED_LEVELS
	seed1 [0] = n_pant; seed2 [0] = level;
	srand ();
#else
	seed1 [0] = n_pant; seed2 [0] = n_pant + 1;
	srand ();
#endif

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
		map_attr [gpit] = behs [gpd];
#ifndef NO_ALT_TILE
		if (gpd == 0 && gpjt == 1) gpd = 19;
#endif

#endif
#ifdef BREAKABLE_WALLS
		brk_buff [gpit] = 0;
#endif

// CUSTOM {
// if (0 == gpd) {
// Do custom scenery stuff here
// }
// } END OF CUSTOM 

		map_buff [gpit] = gpd;
		draw_coloured_tile_gamearea (gpx, gpy, gpd);
#ifdef ENABLE_TILANIMS
		// Detect tilanims
		if (gpd >= ENABLE_TILANIMS) {
			add_tilanim (gpx >> 1, gpy >> 1, gpd);
		}
#endif

		gpx ++;
		if (gpx == 15) {
			gpx = 0;
			gpy ++;
		}
	} while (gpit ++ < 149);

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
		draw_coloured_tile_gamearea (gpx, gpy, 16 + (hotspots [n_pant].act ? hotspots [n_pant].tipo : 0));
	}
#else
	// Modificación para que los hotspots de tipo 3 sean recargas directas:
	if (hotspots [n_pant].act == 1 && hotspots [n_pant].tipo) {
        hotspot_x = gpx << 4;
        hotspot_y = gpy << 4;
        orig_tile = map_buff [15 * gpy + gpx];
        draw_coloured_tile_gamearea (gpx, gpy, 16 + (hotspots [n_pant].tipo != 3 ? hotspots [n_pant].tipo : 0));
    }
#endif
#endif
#ifndef DEACTIVATE_KEYS
	// Open locks
#ifdef COMPRESSED_LEVELS
	for (gpit = 0; gpit < n_bolts; gpit ++) {
#else
	for (gpit = 0; gpit < MAX_bolts; gpit ++) {
#endif
		if (bolts [gpit].np == n_pant && !bolts [gpit].st) {
			gpx = bolts [gpit].x;
			gpy = bolts [gpit].y;
			draw_coloured_tile_gamearea (gpx, gpy, 0);
			gpd = 15 * gpy + gpx;
			map_attr [gpd] = 0;
			map_buff [gpd] = 0;
		}
	}
#endif
}

void __FASTCALL__ draw_scr (void) {

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
		print_str (12, 12, 71, "LEVEL");
		print_number2 (18, 12, n_pant + 1);
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
#ifdef MODE_128K
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
}
