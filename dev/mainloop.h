// mainloop.h
// Churrera 5 Copyleft 2014 the Mojon Twins

void saca_a_todo_el_mundo_de_aqui (unsigned char which_ones) {
	if (which_ones == 0) sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	for (gpit = 0; gpit < 3; gpit ++)
		sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++)
		sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
#endif
#ifdef ENABLE_SHOOTERS
	for (gpit = 0; gpit < MAX_COCOS; gpit ++)
		sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
#endif
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
	sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
#endif
}

unsigned char action_pressed;
unsigned char objs_old, keys_old, life_old, killed_old;

#ifdef MAX_AMMO
unsigned char ammo_old;
#endif

#if defined(TIMER_ENABLE) && defined(PLAYER_SHOW_TIMER)
unsigned char timer_old;
#endif

#ifdef PLAYER_SHOW_FLAG
unsigned char flag_old;
#endif

#ifdef GET_X_MORE
unsigned char *getxmore = " GET X MORE ";
#endif

#ifdef SCRIPTING_KEY_M
int key_m;
#endif

#ifdef PAUSE_ABORT
int key_h, key_y;
#endif

#ifdef MSC_MAXITEMS
int key_z;
unsigned char key_z_pressed = 0;
#endif

#ifdef COMPRESSED_LEVELS
unsigned char mlplaying;
#endif

unsigned char success;
unsigned char playing;

// Main loop
//void do_game (void) {
void main (void) {
	// *********************
	// SYSTEM INITIALIZATION
	// *********************

	cortina ();
	
	#asm
		di
	#endasm

#ifdef MODE_128K
	// Install ISR

	sp_InitIM2(0xf1f1);
	sp_CreateGenericISR(0xf1f1);
	sp_RegisterHook(255, ISR);
#endif

	// splib2 initialization
	sp_Initialize (0, 0);
	sp_Border (BLACK);

	// Reserve memory blocks for sprites
	sp_AddMemory(0, NUMBLOCKS, 14, AD_FREE);

	// Define keys and default controls
#ifdef USE_TWO_BUTTONS
	keys.up    = sp_LookupKey('w');
	keys.down  = sp_LookupKey('s');
	keys.left  = sp_LookupKey('a');
	keys.right = sp_LookupKey('d');
	keys.fire  = sp_LookupKey('m');
	key_jump   = sp_LookupKey('n');
	key_fire   = keys.fire;
#else
	keys.up    = sp_LookupKey('n');
	keys.down  = sp_LookupKey('s');
	keys.left  = sp_LookupKey('a');
	keys.right = sp_LookupKey('d');
	keys.fire  = sp_LookupKey('m');
	key_jump   = sp_LookupKey('w'); // CUSTOM!!
#endif
#ifdef SCRIPTING_KEY_M
	key_m = sp_LookupKey ('m');
#endif
#ifdef PAUSE_ABORT
	key_h = sp_LookupKey ('h');
	key_y = sp_LookupKey ('y');
#endif
#ifdef MSC_MAXITEMS
	key_z = sp_LookupKey ('z');
#endif
	joyfunc = sp_JoyKeyboard;

	// Load tileset
	gen_pt = tileset;
	gpit = 0; do {
		sp_TileArray (gpit, gen_pt);
		gen_pt += 8;
		gpit ++;
	} while (gpit);
	
	// Clipping rectangle
	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 20;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;

	// Sprite creation
#ifdef NO_MASKS
	sp_player = sp_CreateSpr (sp_OR_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	p_current_frame = p_next_frame = sprite_2_a;

	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_OR_SPRITE, 3, sprite_9_a, 1, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);
		en_an_current_frame [gpit] = sprite_9_a;
	}
#else
	sp_player = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 1, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_b, TRANSPARENT);
	sp_AddColSpr (sp_player, sprite_2_c, TRANSPARENT);
	p_current_frame = p_next_frame = sprite_2_a;

	for (gpit = 0; gpit < 3; gpit ++) {
		sp_moviles [gpit] = sp_CreateSpr(sp_MASK_SPRITE, 3, sprite_9_a, 3, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_b, TRANSPARENT);
		sp_AddColSpr (sp_moviles [gpit], sprite_9_c, TRANSPARENT);
		en_an_current_frame [gpit] = en_an_next_frame [gpit] = sprite_9_a;
	}
#endif

#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
#ifdef MASKED_BULLETS
		sp_bullets [gpit] = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
#else
		sp_bullets [gpit] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
#endif
		sp_AddColSpr (sp_bullets [gpit], sprite_19_a + 32, TRANSPARENT);
	}
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
	sp_hitter = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_20_a, 2, TRANSPARENT);
	sp_AddColSpr (sp_hitter, sprite_20_a + 32, TRANSPARENT);
	hitter_current_frame = sprite_20_a;
#endif

#ifdef ENABLE_SHOOTERS
	for (gpit = 0; gpit < MAX_COCOS; gpit ++) {
#ifdef MASKED_BULLETS
		sp_cocos [gpit] = sp_CreateSpr (sp_MASK_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
#else
		sp_cocos [gpit] = sp_CreateSpr (sp_OR_SPRITE, 2, sprite_19_a, 1, TRANSPARENT);
#endif
		sp_AddColSpr (sp_cocos [gpit], sprite_19_a + 32, TRANSPARENT);
	}
#endif

#ifdef MODE_128K
	#asm
		ei
	#endasm

	// Music player initialization
	wyz_init ();
#endif

	get_resource (DEDICADO_BIN, 16384);
	#asm
		ld hl, 22528
		ld (hl), 71
		ld de, 22529
		ld bc, 767
		ldir
	#endasm
	espera_activa (250);

	while (1) {

		// ************
		// TITLE SCREEN
		// ************

		sp_UpdateNow();
		//blackout ();
#ifdef MODE_128K
		// Resource 0 = title.bin
		get_resource (0, 16384);
#else
		unpack ((unsigned int) (s_title), 16384);
#endif
#ifdef MODE_128K
		wyz_play_music (4);
#endif
		select_joyfunc ();

		// *******************
		// GAME INITIALIZATION
		// *******************

#ifdef ACTIVATE_SCRIPTING
#ifndef CLEAR_FLAGS
		msc_init_all ();
#endif
#endif

#ifdef COMPRESSED_LEVELS
		mlplaying = 1;
		silent_level = 0;
// =======[CUSTOM MODIFICATION]=======
		//level = 0;
//
#ifndef REFILL_ME
// =======[CUSTOM MODIFICATION]=======
		//p_life = PLAYER_LIFE;
//
#endif
#endif

// =======[CUSTOM MODIFICATION]=======
		simple_menu (); 	// Fills level, flags [1] and p_life
		espera_activa (40);
//

#ifndef DIRECT_TO_PLAY
		// Clear screen and show game frame
		cortina ();
		sp_UpdateNow();
// =======[CUSTOM MODIFICATION]=======
/*		
#ifdef MODE_128K
		// Resource 1 = marco.bin
		get_resource (1, 16384);
#else
		unpack ((unsigned int) (s_marco), 16384);
#endif
*/
//
#endif

#ifdef ACTIVATE_SCRIPTING
		script_result = 0;
#endif

#ifdef COMPRESSED_LEVELS
		while (mlplaying) {
			p_killme = 0;
			prepare_level ();

			// ****************
			// NEW LEVEL SCREEN
			// ****************

			if (!silent_level) {
// =======[CUSTOM MODIFICATION]=======
				level_screen ();
				is_cutscene = 0;
/*
				blackout_area ();
				print_str (12, 12, 71, "LEVEL");
				print_number2 (18, 12, level + 1);

				if (level > 0) {
					gen_password ();
					print_str (12, 14, 71, password_text);
				}


				sp_UpdateNow ();
#ifdef MODE_128K
				//wyz_play_sound (3);
				wyz_play_music (5);
#else
				peta_el_beeper (1);
#endif
				//espera_activa (2500);
				espera_activa (250);
*/
			}
			silent_level = 0;
#endif

		// ********************
		// LEVEL INITIALIZATION
		// ********************

		playing = 1;
		init_player ();
#ifndef COMPRESSED_LEVELS
		init_hotspots ();
#endif
#ifndef COMPRESSED_LEVELS
#ifndef DEACTIVATE_KEYS
		init_cerrojos ();
#endif
#endif
#if defined(PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
#ifndef COMPRESSED_LEVELS
		init_malotes ();
#endif
#endif
#ifdef PLAYER_CAN_FIRE
		init_bullets ();
#endif

#ifdef ENABLE_SHOOTERS
		init_cocos ();
#endif

#ifndef COMPRESSED_LEVELS
		n_pant = SCR_INICIO;
#endif
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
		maincounter = 0;
#endif

#ifdef ACTIVATE_SCRIPTING
		script_result = 0;
#ifdef CLEAR_FLAGS
		msc_init_all ();
#endif
#endif

#ifdef ACTIVATE_SCRIPTING
#ifdef EXTENDED_LEVELS
		if (level_data->activate_scripting) {
#endif
			// Entering game script
			run_script (MAP_W * MAP_H * 2);
#ifdef EXTENDED_LEVELS
		}
#endif
#endif

#ifdef ENABLE_LAVA
		init_lava ();
#endif

		do_respawn = 1;

#ifdef PLAYER_KILLS_ENEMIES
#ifdef SHOW_TOTAL
		// Show total of enemies next to the killed amount.

		sp_PrintAtInv (KILLED_Y, 2 + KILLED_X, 71, 15);
		sp_PrintAtInv (KILLED_Y, 3 + KILLED_X, 71, 16 + BADDIES_COUNT / 10);
		sp_PrintAtInv (KILLED_Y, 4 + KILLED_X, 71, 16 + BADDIES_COUNT % 10);
#endif
#endif

		objs_old = keys_old = life_old = killed_old = 0xff;
#ifdef MAX_AMMO
		ammo_old = 0xff;
#endif
#if defined(TIMER_ENABLE) && defined(PLAYER_SHOW_TIMER)
		timer_old = 0;
#endif
#ifdef PLAYER_SHOW_FLAG
		flag_old = 99;
#endif
		success = 0;

#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
#ifdef BREAKABLE_ANIM
		do_process_breakable = 0;
		gen_pt = breaking_f;
		for (gpit = 0; gpit < MAX_BREAKABLE; gpit ++) *gen_pt ++ = 0;
#endif
#endif

#ifdef MODE_128K
		// Play music
#ifdef COMPRESSED_LEVELS
		wyz_play_music (level_data->music_id);
#else
		wyz_play_music (1);
#endif
#endif
		o_pant = 0xff;
		
#ifdef MSC_MAXITEMS
		display_items ();
#endif

		// *********
		// MAIN LOOP
		// *********

		while (playing) {
			if (n_pant != o_pant) {
				draw_scr ();
				o_pant = n_pant;
#ifdef ENABLE_LAVA
				if (flags [LAVA_FLAG] == 1) lava_reenter ();
#endif
			}

#ifdef TIMER_ENABLE
			// Timer
			if (ctimer.on) {
				ctimer.count ++;
				if (ctimer.count == ctimer.frames) {
					ctimer.count = 0;
					ctimer.t --;
					if (ctimer.t == 0) ctimer.zero = 1;
				}
			}

#if defined(TIMER_SCRIPT_0) && defined(ACTIVATE_SCRIPTING)
			if (ctimer.zero) {
				ctimer.zero = 0;
#ifdef SHOW_TIMER_OVER
				saca_a_todo_el_mundo_de_aqui (0);
				time_over ();
				espera_activa (500);
#endif
#ifdef EXTENDED_LEVELS
				if (level_data->activate_scripting) {
#endif
					run_script (MAP_W * MAP_H * 2 + 3);
#ifdef EXTENDED_LEVELS
				}
#endif
			}
#endif

#ifdef TIMER_KILL_0
			if (ctimer.zero) {
#ifdef SHOW_TIMER_OVER
#ifndef TIMER_SCRIPT_0
				saca_a_todo_el_mundo_de_aqui (0);
				time_over ();
				espera_activa (500);
#endif
#endif
				ctimer.zero = 0;
#ifdef TIMER_AUTO_RESET
				ctimer.t = TIMER_INITIAL;
#endif
#ifdef MODE_128K
				kill_player (7);
#else
				kill_player (4);
#endif
#if defined(TIMER_WARP_TO_X) && defined(TIMER_WARP_TO_Y)
				p_x = TIMER_WARP_TO_X << 10;
				p_y = TIMER_WARP_TO_Y << 10;
#endif
#ifdef TIMER_WARP_TO
				n_pant = TIMER_WARP_TO;
				draw_scr ();
#endif
			}
#endif
#endif

#ifndef DEACTIVATE_OBJECTS
			if (p_objs != objs_old) {
				draw_objs ();
				objs_old = p_objs;
			}
#endif

			if (p_life != life_old) {
				print_number2 (LIFE_X, LIFE_Y, p_life);
				life_old = p_life;
			}

#ifndef DEACTIVATE_KEYS
			if (p_keys != keys_old) {
				print_number2 (KEYS_X, KEYS_Y, p_keys);
				keys_old = p_keys;
			}
#endif

#if defined(PLAYER_KILLS_ENEMIES) || defined(PLAYER_CAN_FIRE)
#ifdef PLAYER_SHOW_KILLS
			if (p_killed != killed_old) {
				print_number2 (KILLED_X, KILLED_Y, p_killed);
				killed_old = p_killed;
			}
#endif
#endif

#ifdef MAX_AMMO
			if (p_ammo != ammo_old) {
				print_number2 (AMMO_X, AMMO_Y, p_ammo);
				ammo_old = p_ammo;
			}
#endif

#if defined(TIMER_ENABLE) && defined(PLAYER_SHOW_TIMER)
			if (ctimer.t != timer_old) {
				print_number2 (TIMER_X, TIMER_Y, ctimer.t);
				timer_old = ctimer.t;
			}
#endif

#ifdef PLAYER_SHOW_FLAG
			if (flags [PLAYER_SHOW_FLAG] != flag_old) {
				print_number2 (FLAG_X, FLAG_Y, flags [PLAYER_SHOW_FLAG]);
				flag_old = flags [PLAYER_SHOW_FLAG];
			}
#endif
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
			maincounter ++;
#endif
			half_life = !half_life;

			// Move player
			move ();

			// Move hitter 
#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
			if (hitter_on) render_hitter ();
#endif			
			
			// Move enemies
			mueve_bicharracos ();

#ifdef ENABLE_SHOOTERS
			move_cocos ();
#endif

#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
#ifdef BREAKABLE_ANIM
			// Breakable
			if (do_process_breakable) process_breakable ();
#endif
#endif

#ifdef PLAYER_CAN_FIRE
			// Move bullets
			mueve_bullets ();
#endif

#ifdef ENABLE_TILANIMS
			do_tilanims ();
#endif

			for (gpit = 0; gpit < 3; gpit ++) {
				enoffsmasi = enoffs + gpit;
#if defined (RANDOM_RESPAWN) || defined (ENABLE_CUSTOM_TYPE_6)
				if (
#ifdef RANDOM_RESPAWN
					en_an_fanty_activo [gpit]
#ifdef ENABLE_CUSTOM_TYPE_6
					|| (malotes [enoffsmasi].t & 0xEF) == 6
#endif
#else
					(malotes [enoffsmasi].t & 0xEF) == 6
#endif
				) {
					gpen_x = en_an_x [gpit] >> 6;
					gpen_y = en_an_y [gpit] >> 6;
				} else {
#endif
					gpen_x = malotes [enoffsmasi].x;
					gpen_y = malotes [enoffsmasi].y;
#if defined (RANDOM_RESPAWN) || defined (ENABLE_CUSTOM_TYPE_6)
				}
#endif
				sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_y >> 3), VIEWPORT_X + (gpen_x >> 3),gpen_x & 7, gpen_y & 7);
				en_an_current_frame [gpit] = en_an_next_frame [gpit];
			}

			if ( !(p_estado & EST_PARP) || half_life == 0) {
				sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
			} else {
				sp_MoveSprAbs (sp_player, spritesClip, p_next_frame - p_current_frame, -2, -2, 0, 0);
			}

			p_current_frame = p_next_frame;


#ifdef PLAYER_CAN_FIRE
			for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
				if (bullets_estado [gpit] == 1) {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, VIEWPORT_Y + (bullets_y [gpit] >> 3), VIEWPORT_X + (bullets_x [gpit] >> 3), bullets_x [gpit] & 7, bullets_y [gpit] & 7);
				} else {
					sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif

#ifdef ENABLE_SHOOTERS
			for (gpit = 0; gpit < MAX_COCOS; gpit ++) {
				if (coco_s [gpit] == 1) {
					sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, VIEWPORT_Y + (coco_y [gpit] >> 3), VIEWPORT_X + (coco_x [gpit] >> 3), coco_x [gpit] & 7, coco_y [gpit] & 7);
				} else {
					sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
				}
			}
#endif

// Experimental
#ifdef ENABLE_LAVA
			if (flags [LAVA_FLAG] == 1) {
				if (do_lava ()) {
#ifdef MODE_128K
					kill_player (7);
#else
					kill_player (4);
#endif
					success = 2;	// repeat
					playing = 0;
					//continue;
				}
			}
#endif

			// Update to screen
			sp_UpdateNow();

#ifdef PLAYER_CAN_FIRE
			for (gpit = 0; gpit < 3; gpit ++)
				if (en_an_morido [gpit] == 1) {
#ifdef MODE_128K
					wyz_play_sound (7);
#else
					peta_el_beeper (1);
#endif
					en_an_morido [gpit] = 0;
				}
#endif

#ifdef PLAYER_FLICKERS
			// Flickering
			if (p_estado == EST_PARP) {
				p_ct_estado --;
				if (p_ct_estado == 0)
					p_estado = EST_NORMAL;
			}
#endif

			// Hotspot interaction.
			if (collide (gpx, gpy, hotspot_x, hotspot_y)) {
				// Deactivate hotspot
				draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
				gpit = 0;
#ifndef USE_HOTSPOTS_TYPE_3
				// Was it an object, key or life boost?
				if (hotspots [n_pant].act == 0) {
					p_life += PLAYER_REFILL;
#ifndef DONT_LIMIT_LIFE
					if (p_life > PLAYER_LIFE)
						p_life = PLAYER_LIFE;
#endif
					hotspots [n_pant].act = 2;
#ifdef MODE_128K
					wyz_play_sound (5);
#else
					peta_el_beeper (8);
#endif
				} else {
					switch (hotspots [n_pant].tipo) {
#ifndef DEACTIVATE_OBJECTS
						case 1:
#ifdef ONLY_ONE_OBJECT
							if (p_objs == 0) {
								p_objs ++;
#ifdef MODE_128K
								wyz_play_sound (3);
#else
								peta_el_beeper (9);
#endif
							} else {
#ifdef MODE_128K
								wyz_play_sound (5);
#else
								peta_el_beeper (4);
#endif
								draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
								gpit = 1;
							}
#else
							p_objs ++;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (9);
#endif
#endif
							break;
#endif
#ifndef DEACTIVATE_KEYS
						case 2:
							p_keys ++;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (7);
#endif
							break;
#endif
#ifdef MAX_AMMO
						case 4:
							if (MAX_AMMO - p_ammo > AMMO_REFILL)
								p_ammo += AMMO_REFILL;
							else
								p_ammo = MAX_AMMO;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (9);
#endif
							break;
#endif
#ifdef TIMER_ENABLE
						case 5:
							if (99 - ctimer.t > TIMER_REFILL)
								ctimer.t += TIMER_REFILL;
							else
								ctimer.t = 99;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (7);
#endif
							break;
#endif
					}
					hotspots [n_pant].act = gpit;
				}
				hotspot_y = 240;
			}
#else
				// Modificación para que los hotspots de tipo 3 sean recargas directas
				// Was it an object, key or life boost?
				if (hotspots [n_pant].act) {
					hotspots [n_pant].act = 0;
					switch (hotspots [n_pant].tipo) {
#ifndef DEACTIVATE_OBJECTS
						case 1:
#ifdef ONLY_ONE_OBJECT
							if (p_objs == 0) {
								p_objs ++;
#ifdef MODE_128K
								wyz_play_sound (3);
#else
								peta_el_beeper (9);
#endif
							} else {
#ifdef MODE_128K
								wyz_play_sound (5);
#else
								peta_el_beeper (4);
#endif
								draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
								hotspots [n_pant].act = 1;
							}
#else
							p_objs ++;
#ifdef MODE_128K
							wyz_play_sound (5);
#else
							peta_el_beeper (9);
#endif
#ifdef GET_X_MORE
							if (level_data.max_objs > p_objs) {
								print_str (10, 11, 79, spacer);
								getxmore [5] = '0' + level_data.max_objs - p_objs;
								print_str (10, 12, 79, getxmore);
								print_str (10, 13, 79, spacer);
								sp_UpdateNow ();
								sp_WaitForNoKey ();
								espera_activa (100);
								draw_scr_background ();
							}
#endif
							break;
#endif
#endif

#ifndef DEACTIVATE_KEYS
						case 2:
							p_keys ++;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (7);
#endif
							break;
#endif
						case 3:
							p_life += PLAYER_REFILL;
#ifndef DONT_LIMIT_LIFE
							if (p_life > PLAYER_LIFE)
								p_life = PLAYER_LIFE;
#endif
#ifdef MODE_128K
							wyz_play_sound (5);
#else
							peta_el_beeper (8);
#endif
							break;
#ifdef MAX_AMMO
						case 4:
							if (MAX_AMMO - p_ammo > AMMO_REFILL)
								p_ammo += AMMO_REFILL;
							else
								p_ammo = MAX_AMMO;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (9);
#endif
							break;
#endif
#ifdef TIMER_ENABLE
						case 5:
							if (99 - ctimer.t > TIMER_REFILL)
								ctimer.t += TIMER_REFILL;
							else
								ctimer.t = 99;
#ifdef MODE_128K
							wyz_play_sound (3);
#else
							peta_el_beeper (7);
#endif
							break;
#endif
					}

				}
				hotspot_y = 240;
			}
#endif

// Select object
#ifdef MSC_MAXITEMS
			if (sp_KeyPressed (key_z)) {
				if (!key_z_pressed) {
#ifdef MODE_128K
					wyz_play_sound (0);
#else
					peta_el_beeper (2);
#endif
					flags [FLAG_SLOT_SELECTED] = (flags [FLAG_SLOT_SELECTED] + 1) % MSC_MAXITEMS;
					display_items ();
				}
				key_z_pressed = 1;
			} else {
				key_z_pressed = 0;
			}
#endif

			// Flick screen checks and scripting related stuff
			gpit = (joyfunc) (&keys);

#ifdef ACTIVATE_SCRIPTING
#ifdef EXTENDED_LEVELS
			if (level_data->activate_scripting) {
#endif
#ifdef SCRIPTING_KEY_M
				if (sp_KeyPressed (key_m)) {
#endif
#ifdef SCRIPTING_DOWN
				if ((gpit & sp_DOWN) == 0) {
#endif
#ifdef SCRIPTING_KEY_FIRE
				if ((gpit & sp_FIRE) == 0) {
#endif
					if (action_pressed == 0)  {
						action_pressed = 1;
						// Any scripts to run in this screen?
						run_fire_script ();
					}
				} else {
					action_pressed = 0;
				}
#ifdef EXTENDED_LEVELS
			}
#endif
#endif

#ifdef ACTIVATE_SCRIPTING
#ifdef ENABLE_FIRE_ZONE
#ifdef EXTENDED_LEVELS
			if (level_data->activate_scripting) {
#endif
				if (f_zone_ac) {
					if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
						run_fire_script ();
					}
				}
#ifdef EXTENDED_LEVELS
			}
#endif
#endif
#endif

#ifdef PAUSE_ABORT
			// Pause/Abort handling
			if (sp_KeyPressed (key_h)) {
				sp_WaitForNoKey ();
#ifdef MODE_128K
				wyz_stop_sound ();
				wyz_play_sound (1);
#endif
				//saca_a_todo_el_mundo_de_aqui (0);
				//pause_screen ();
				while (sp_KeyPressed (key_h) == 0);
				sp_WaitForNoKey ();
				//draw_scr_background ();
#ifdef ACTIVATE_SCRIPTING
				//run_entering_script ();
#endif
#ifdef MODE_128K
				// Play music
#ifdef COMPRESSED_LEVELS
				wyz_play_music (level_data->music_id);
#else
				wyz_play_music (1);
#endif
#endif
			}
			if (sp_KeyPressed (key_y)) {
				playing = 0;
			}

#endif

			// Win game condition

#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
			// 128K
			if (
				(level_data->win_condition == 0 && p_objs == level_data->max_objs) ||
				(level_data->win_condition == 1 && n_pant == level_data->scr_fin)
#ifdef ACTIVATE_SCRIPTING
				|| (level_data->win_condition == 2 && script_result == 1)
#endif
			) {
#elif !defined (MODE_128K) && defined(COMPRESSED_LEVELS)
			// 48K, compressed levels.
			if (
				(win_condition == 0 && p_objs == PLAYER_NUM_OBJETOS) ||
				(win_condition == 1 && n_pant == SCR_FIN)
#ifdef ACTIVATE_SCRIPTING
				|| (win_condition == 2 && script_result == 1)
#endif
			) {
#else
			// 48K, legacy
#if WIN_CONDITION == 0
			if (p_objs == PLAYER_NUM_OBJETOS) {
#elif WIN_CONDITION == 1
			if (n_pant == SCR_FIN) {
#elif WIN_CONDITION == 2
			if (script_result == 1 || script_result > 2) {
#endif
#endif
				success = 1;	// Next
				playing = 0;
			}

			// Game over condition
			if (p_life == 0
#ifdef ACTIVATE_SCRIPTING
				|| script_result == 2
#endif
#if defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0)
				|| ctimer.zero
#endif
			) {
				playing = 0;
			}

			// Warp to level condition (3)
			// Game ending (4)
#if defined (COMPRESSED_LEVELS) && defined (MODE_128K)
			if (script_result > 2) {
				success = script_result;	// Warp_to (3), Game ending (4)
				playing = 0;
			}
#endif
			// Change screen

#ifdef DIE_AND_RESPAWN
			// Respawn
			if (p_killme) {
				p_estado = EST_PARP;
				sp_UpdateNow ();
				wyz_play_sample (0);
				espera_activa (50);
				if (p_engine != SENG_SWIM) {
					if (n_pant != p_safe_pant) {
						o_pant = n_pant = p_safe_pant;
						draw_scr ();
					}
					while (
						!(attr (p_safe_x, p_safe_y + 1) & 12) ||
						(attr (p_safe_x, p_safe_y) & 8)
					) p_safe_x ++;
					p_x = p_safe_x << 10;
					p_y = p_safe_y << 10;
					p_vx = 0;
					p_vy = 0;
					p_saltando = 0;
				}

				p_killme = 0;
#ifdef MODE_128K
				// Play music
#ifdef COMPRESSED_LEVELS
				wyz_play_music (level_data->music_id);
#else
				wyz_play_music (1);
#endif
#endif
			}
#endif

#ifdef PLAYER_CHECK_MAP_BOUNDARIES
			if (p_x == 0 && p_vx < 0 && x_pant > 0) {
				n_pant --;
				p_x = 14336;
			}
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
			if (p_x == 14336 && p_vx > 0 && x_pant < (level_data->map_w - 1)) {
#else
			if (p_x == 14336 && p_vx > 0 && x_pant < (MAP_W - 1)) {
#endif
				n_pant ++;
				p_x = 0;
			}
			if (p_y == 0 && p_vy < 0 && y_pant > 0) {
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
				n_pant -= level_data->map_w;
#else
				n_pant -= MAP_W;
#endif
				p_y = 9216;
			}
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
			if (p_y == 9216 && p_vy > 0 && y_pant < (level_data->map_h - 1)) {
				n_pant += level_data->map_w;
#else
			if (p_y == 9216 && p_vy > 0 && y_pant < (MAP_H - 1)) {
				n_pant += MAP_W;
#endif
				p_y = 0;
				if (p_vy > 256) p_vy = 256;
			}
#else
#ifdef PLAYER_AUTO_CHANGE_SCREEN
			if (p_x == 0 && p_vx < 0) {
				n_pant --;
				p_x = 14336;
			}
			if (p_x == 14336 && p_vx > 0) {
				n_pant ++;
				p_x = 0;
			}
#else
			if (p_x == 0 && ((gpit & sp_LEFT) == 0)) {
				n_pant --;
				p_x = 14336;
			}
			if (p_x == 14336 && ((gpit & sp_RIGHT) == 0)) {		// 14336 = 224 * 64
				n_pant ++;
				p_x = 0;
			}
#endif
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
			if (p_y == 0 && p_vy < 0 && n_pant >= level_data->map_w) {
				n_pant -= level_data->map_w;
#else
			if (p_y == 0 && p_vy < 0 && n_pant >= MAP_W) {
				n_pant -= MAP_W;
#endif
				p_y = 9216;
			}
			if (p_y == 9216 && p_vy > 0) {				// 9216 = 144 * 64
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS)
				if (n_pant < level_data->map_w * (level_data->map_h - 1)) {
					n_pant += level_data->map_w;
#else
				if (n_pant < MAP_W * MAP_H - MAP_W) {
					n_pant += MAP_W;
#endif
					p_y = 0;
					if (p_vy > 256) p_vy = 256;
#ifdef MAP_BOTTOM_KILLS
				} else {
					p_vy = -PLAYER_MAX_VY_CAYENDO;
					if (p_life > 0) {
#ifdef MODE_128K
						kill_player (1);
#else
						kill_player (4);
#endif
					}
#endif
				}
			}
#endif
		}

#ifdef MODE_128K
		wyz_stop_sound ();
#endif

		saca_a_todo_el_mundo_de_aqui (0);
		sp_UpdateNow ();

#ifdef COMPRESSED_LEVELS
		switch (success) {
			case 0:
#if defined(TIMER_ENABLE) && defined(TIMER_GAMEOVER_0) && defined(SHOW_TIMER_OVER)
				if (ctimer.zero) time_over (); else game_over ();
#else
#ifdef MODE_128K
				wyz_play_music (8);
#endif
				//game_over ();
				print_message (" GAME OVER! ");
#endif
				mlplaying = 0;
				espera_activa (250);
				break;
			case 1:
				wyz_play_music (7);
				print_message (" ZONE CLEAR ");
				level ++;
				espera_activa (250);
				do_extern_action (0);
				break;
			case 3:
				blackout_area ();
				level = warp_to_level;
				break;				
			case 4:
// =======[CUSTOM MODIFICATION]=======		
				wyz_play_music (9);	
				if (flags [28] == 0) {
					// Final malo
					do_cutscene (cutscene0);
				} else {
					// Final bueno
					do_cutscene (cutscene1);
				}
//						
				get_resource (2, 16384);
				espera_activa (1000);
				wyz_stop_sound ();
				cortina ();
				wyz_play_music (12);	
				espera_activa (130);
				credits ();
				mlplaying = 0;
		}

#ifndef SCRIPTED_GAME_ENDING
		if (level == MAX_LEVELS) {
			game_ending ();
			mlplaying = 0;
		}
#endif
	}
	cortina ();
#else
		if (success) {
			game_ending ();
		} else {
			//wyz_play_music (8)
			game_over ();
		}
		espera_activa (500);
		cortina ();
#endif
	}
}
