// drawscr.h
// Screen drawing functions

#ifdef ENABLE_SHOOTERS
void __FASTCALL__ init_cocos (void);
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
	map_pointer = mapa + (n_pant * 150);
#else
	map_pointer = mapa + (n_pant * 75);
#endif
	
	gpit = gpx = gpy = 0;	

	// Draw 150 tiles
	do {
		gpjt = rand () & 15;
		
#ifdef UNPACKED_MAP
		// Mapa tipo UNPACKED
		gpd = *map_pointer ++;
		map_attr [gpit] = comportamiento_tiles [gpd];
		map_buff [gpit] = gpd;
#else
		// Mapa tipo PACKED
		if (gpit & 1) {
			gpd = gpc & 15;
		} else {
			gpc = *map_pointer ++;
			gpd = gpc >> 4;
		}
		map_attr [gpit] = comportamiento_tiles [gpd];
		if (gpd == 0 && gpjt == 1) gpd = 19;
		map_buff [gpit] = gpd;
#endif	
#ifdef BREAKABLE_WALLS
		brk_buff [gpit] = 0;
#endif		
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

#ifndef DEACTIVATE_KEYS
	// Open locks
#ifdef COMPRESSED_LEVELS
	for (gpit = 0; gpit < n_bolts; gpit ++) {
#else
	for (gpit = 0; gpit < MAX_CERROJOS; gpit ++) {
#endif
		if (cerrojos [gpit].np == n_pant && !cerrojos [gpit].st) {
			gpx = cerrojos [gpit].x;
			gpy = cerrojos [gpit].y;
			draw_coloured_tile_gamearea (gpx, gpy, 0);
			gpd = 15 * gpy + gpx;
			map_attr [gpd] = 0;
			map_buff [gpd] = 0;
		}
	}
#endif
}

void __FASTCALL__ draw_scr (void) {
	draw_scr_background ();
	
#ifdef ENABLE_FIRE_ZONE
	f_zone_ac = 0;
#endif	

	// Movemos y cambiamos a los enemigos según el tipo que tengan
	enoffs = n_pant * 3;
	
	for (gpit = 0; gpit < 3; gpit ++) {
		en_an_frame [gpit] = 0;
		en_an_count [gpit] = 3;
		en_an_state [gpit] = 0;
		enoffsmasi = enoffs + gpit;
#ifdef ENABLE_RANDOM_RESPAWN
		en_an_fanty_activo [gpit] = 0;
#endif
#ifdef RESPAWN_ON_ENTER
		// Back to life!
		if (do_respawn) {
			malotes [enoffsmasi].t &= 0xEF;	
#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
#ifdef MODE_128K
			malotes [enoffsmasi].life = level_data.enems_life;
#else
			malotes [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
#endif
#endif
		}
#endif
		switch (malotes [enoffs + gpit].t) {
			case 1:
			case 2:
			case 3:
			case 4:
				en_an_base_frame [gpit] = (malotes [enoffs + gpit].t - 1) << 1;
				break;
#ifdef ENABLE_RANDOM_RESPAWN
			case 5: 
				en_an_base_frame [gpit] = 4;
				break;
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
			case 6:
				// Añade aquí tu código custom. Esto es un ejemplo:
				en_an_base_frame [gpit] = TYPE_6_FIXED_SPRITE << 1;
				en_an_x [gpit] = malotes [enoffsmasi].x << 6;
				en_an_y [gpit] = malotes [enoffsmasi].y << 6;
				en_an_vx [gpit] = en_an_vy [gpit] = 0;
				en_an_state [gpit] = TYPE_6_IDLE;				
				break;				
#endif
#ifdef ENABLE_PURSUERS
			case 7:
				en_an_alive [gpit] = 0;
				en_an_dead_row [gpit] = 0;//DEATH_COUNT_EXPRESSION;
				break;
#endif
#ifdef ENABLE_SHOOTERS
			case 8:
				en_an_base_frame [gpit] = TYPE_8_FIXED_SPRITE << 1;
				break;
#endif
#ifdef ENABLE_CLOUDS
			case 9:
				en_an_base_frame [gpit] = TYPE_9_FIXED_SPRITE << 1;
				malotes [enoffsmasi].mx = abs (malotes [enoffsmasi].mx);
				break;
#endif
			default:
				en_an_next_frame [gpit] = sprite_18_a;
		}
	}
	do_respawn = 1;
	
#ifdef ACTIVATE_SCRIPTING
	run_entering_script ();
#endif

#ifdef PLAYER_CAN_FIRE
	init_bullets ();
#endif	

#ifdef ENABLE_SHOOTERS
	init_cocos ();
#endif

#ifdef PLAYER_CHECK_MAP_BOUNDARIES
#ifdef MODE_128K
		x_pant = n_pant % level_data->map_w;
		y_pant = n_pant / level_data->map_w;
#else
		x_pant = n_pant % MAP_W; y_pant = n_pant / MAP_W;
#endif
#endif

#if defined (DIE_AND_RESPAWN)
#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_SWIM) {
		p_safe_pant = n_pant;
		p_safe_x = (p_x >> 10);
		p_safe_y = (p_y >> 10);	
	}	
#endif		
#endif
/*
	for (gpit = 0; gpit < 16; gpit ++) {
		sp_PrintAtInv (23, gpit + gpit, 71, 16 + flags [gpit]);
	}
*/
}
