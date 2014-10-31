// enems.h
// Enemy management

#if defined (ENABLE_CUSTOM_TYPE_6) || defined (ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
// Funciones auxiliares custom
unsigned char distance (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
	unsigned char dx = abs (x2 - x1);
	unsigned char dy = abs (y2 - y1);
	unsigned char mn = dx < dy ? dx : dy;
	return (dx + dy - (mn >> 1) - (mn >> 2) + (mn >> 4));
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
unsigned char coco_x [MAX_COCOS], coco_y [MAX_COCOS], coco_s [MAX_COCOS], ctx, cty;
signed char coco_vx [MAX_COCOS], coco_vy [MAX_COCOS];
void __FASTCALL__ init_cocos (void) {
	for (gpit = 0; gpit < MAX_COCOS;) coco_s [gpit++] = 0;
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
unsigned char coco_it, coco_d, coco_x0;
void __FASTCALL__ shoot_coco (void) {
	coco_x0 = gpen_cx + 4;
#ifdef TYPE_8_FIRE_ONE
	coco_it = gpit;
	{
#else	
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
#endif
		if (coco_s [coco_it] == 0) {
			coco_d = distance (coco_x0, gpen_cy, gpx, gpy);
			if (coco_d >= TYPE_8_SAFE_DISTANCE) {
#ifdef MODE_128K
				wyz_play_sound (3);
#endif
				coco_s [coco_it] = 1;
				coco_x [coco_it] = coco_x0;
				coco_y [coco_it] = gpen_cy;	
				if (gpt == 8) {			
					coco_vx [coco_it] = (COCO_SPEED_8 * (gpx - coco_x0) / coco_d);
					coco_vy [coco_it] = (COCO_SPEED_8 * (gpy - gpen_cy) / coco_d);
				} else {
					coco_vx [coco_it] = 0;
					coco_vy [coco_it] = COCO_SPEED_9;
				}
			}
		}		
	}
}
#endif

#if defined(ENABLE_SHOOTERS) || defined (ENABLE_CLOUDS)
void __FASTCALL__ move_cocos (void) {
	for (coco_it = 0; coco_it < MAX_COCOS; coco_it ++) {
		if (coco_s [coco_it]) {
			coco_x [coco_it] += coco_vx [coco_it];
			coco_y [coco_it] += coco_vy [coco_it];
			
			if (coco_x [coco_it] >= 240 || coco_y [coco_it] >= 160) coco_s [coco_it] = 0;
			// Collide player
			ctx = coco_x [coco_it] + 3;
			cty = coco_y [coco_it] + 3;
			if (p_estado == EST_NORMAL) {
				//if (ctx >= gpx + 2 && ctx <= gpx + 13 && cty >= gpy + 2 && cty <= gpy + 13) {
				if (collide_pixel (ctx, cty, gpx, gpy)) {
					coco_s [coco_it] = 0;
#ifdef MODE_128K
						kill_player (7);
#else
						kill_player (4);
#endif		
				}		
			}
		}
	}
}
#endif

#ifdef ENABLE_RANDOM_RESPAWN
char player_hidden (void) {
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
	if ( (gpy & 15) == 0 && p_vx == 0 ) {
		if (attr (gpxx, gpyy) == 2 || (attr (1 + gpxx, gpyy) == 2 && (gpx & 15)) ) {
			return 1;
		}
	}
	return 0;
}
#endif

#ifdef WALLS_STOP_ENEMIES
unsigned char __FASTCALL__ mons_col_sc_x (void) {
	gpaux = gpen_xx + (malotes [enoffsmasi].mx > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpaux, gpen_yy) || ((malotes [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1)));
#else
	return (attr (gpaux, gpen_yy) & 8 || ((malotes [enoffsmasi].y & 15) && attr (gpaux, gpen_yy + 1) & 8));
#endif
}

unsigned char __FASTCALL__ mons_col_sc_y (void) {
	gpaux = gpen_yy + (malotes [enoffsmasi].my > 0);
#ifdef EVERYTHING_IS_A_WALL
	return (attr (gpen_xx, gpaux) || ((malotes [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux)));
#else
	return (attr (gpen_xx, gpaux) & 8 || ((malotes [enoffsmasi].x & 15) && attr (gpen_xx + 1, gpaux) & 8));
#endif
}
#endif

#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
unsigned char lasttimehit;
#endif

#if defined(ENABLE_CUSTOM_TYPE_6) || defined(ENABLE_RANDOM_RESPAWN)
int limit (int val, int min, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
#endif

unsigned char pregotten;
void mueve_bicharracos (void) {
	gpx = p_x >> 6;
	gpy = p_y >> 6;
#ifndef PLAYER_MOGGY_STYLE	
	p_gotten = 0;
	ptgmx = 0;
	ptgmy = 0;
#endif

	tocado = 0;
	p_gotten = 0;
	for (gpit = 0; gpit < 3; gpit ++) {
		active = 0;
		enoffsmasi = enoffs + gpit;
		gpen_x = malotes [enoffsmasi].x;
		gpen_y = malotes [enoffsmasi].y;
		gpt = malotes [enoffsmasi].t;

		if (en_an_state [gpit] == GENERAL_DYING) {
			en_an_count [gpit] --;
			if (0 == en_an_count [gpit]) {
				en_an_state [gpit] = 0;
				en_an_next_frame [gpit] = sprite_18_a;
				continue;
			}
		}
		
#ifndef PLAYER_MOGGY_STYLE
		// Gotten preliminary:
#if defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_8_BOTTOM)
		pregotten = (gpx + 11 >= malotes [enoffsmasi].x && gpx <= malotes [enoffsmasi].x + 11);
#else
		pregotten = (gpx + 15 >= malotes [enoffsmasi].x && gpx <= malotes [enoffsmasi].x + 15);
#endif
#endif
		
#ifdef ENABLE_RANDOM_RESPAWN
		if (en_an_fanty_activo [gpit]) gpt = 5;
#endif
		switch (gpt) {
			case 1:
			case 2:
			case 3:
			case 4:
#if defined (ENABLE_SHOOTERS) && defined (TYPE_8_LINEAR_BEHAVIOUR)
			case 8:
#endif
				active = 1;
				malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
				malotes [enoffsmasi].y += malotes [enoffsmasi].my;
				gpen_cx = malotes [enoffsmasi].x;
				gpen_cy = malotes [enoffsmasi].y;
				gpen_xx = gpen_cx >> 4;
				gpen_yy = gpen_cy >> 4;
#ifdef WALLS_STOP_ENEMIES
				if (gpen_cx == malotes [enoffsmasi].x1 || gpen_cx == malotes [enoffsmasi].x2 || mons_col_sc_x ())
					malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
				if (gpen_cy == malotes [enoffsmasi].y1 || gpen_cy == malotes [enoffsmasi].y2 || mons_col_sc_y ())
					malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
#else
				if (gpen_cx == malotes [enoffsmasi].x1 || gpen_cx == malotes [enoffsmasi].x2)
					malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
				if (gpen_cy == malotes [enoffsmasi].y1 || gpen_cy == malotes [enoffsmasi].y2)
					malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
#endif

#if defined (ENABLE_SHOOTERS) && defined (TYPE_8_LINEAR_BEHAVIOUR)
				// Shoot a coco
				if (gpt == 8 && (rand () & TYPE_8_SHOOT_FREQ) == 1) {					
					shoot_coco ();
				}
#endif
				break;
#ifdef ENABLE_RANDOM_RESPAWN
			case 5:
				active = 1;
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				if (player_hidden ()) {
					en_an_vx [gpit] = limit (
						en_an_vx [gpit] + addsign (en_an_x [gpit] - p_x, FANTY_A >> 1),
						-FANTY_MAX_V, FANTY_MAX_V);
					en_an_vy [gpit] = limit (
						en_an_vy [gpit] + addsign (en_an_y [gpit] - p_y, FANTY_A >> 1),
						-FANTY_MAX_V, FANTY_MAX_V);
				} else if ((rand () & 7) > 1) {
					en_an_vx [gpit] = limit (
						en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTY_A),
						-FANTY_MAX_V, FANTY_MAX_V);
					en_an_vy [gpit] = limit (
						en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTY_A),
						-FANTY_MAX_V, FANTY_MAX_V);
				}

				en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
				en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);

				break;
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
			case 6:
				active = 1;
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				switch (en_an_state [gpit]) {
					case TYPE_6_IDLE:
						if (distance (gpx, gpy, gpen_cx, gpen_cy) <= SIGHT_DISTANCE)
							en_an_state [gpit] = TYPE_6_PURSUING;
						break;
					case TYPE_6_PURSUING:
						if (distance (gpx, gpy, gpen_cx, gpen_cy) > SIGHT_DISTANCE) {
							en_an_state [gpit] = TYPE_6_RETREATING;
						} else {
							en_an_vx [gpit] = limit (
								en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTY_A),
								-FANTY_MAX_V, FANTY_MAX_V);
							en_an_vy [gpit] = limit (
								en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTY_A),
								-FANTY_MAX_V, FANTY_MAX_V);

							en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
							en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
						}
						break;
					case TYPE_6_RETREATING:
						en_an_x [gpit] += addsign (malotes [enoffsmasi].x - gpen_cx, 64);
						en_an_y [gpit] += addsign (malotes [enoffsmasi].y - gpen_cy, 64);

						if (distance (gpx, gpy, gpen_cx, gpen_cy) <= SIGHT_DISTANCE)
							en_an_state [gpit] = TYPE_6_PURSUING;
						break;
				}
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				if (en_an_state [gpit] == TYPE_6_RETREATING &&
					gpen_cx == malotes [enoffsmasi].x &&
					gpen_cy == malotes [enoffsmasi].y
					)
					en_an_state [gpit] = TYPE_6_IDLE;
				break;
#endif
#ifdef ENABLE_PURSUERS
			case 7:
				switch (en_an_alive [gpit]) {
					case 0:
						if (en_an_dead_row [gpit] == 0) {
							malotes [enoffsmasi].x = malotes [enoffsmasi].x1;
							malotes [enoffsmasi].y = malotes [enoffsmasi].y1;
							en_an_alive [gpit] = 1;
							en_an_rawv [gpit] = 1 << (rand () % 5);
							if (en_an_rawv [gpit] > 4) en_an_rawv [gpit] = 2;
							en_an_dead_row [gpit] = 11 + (rand () & 7);
#if defined(PLAYER_KILLS_ENEMIES) || defined(PLAYER_CAN_FIRE)
							malotes [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
#endif
						} else {
							en_an_dead_row [gpit] --;
						}
						break;
					case 1:
						if (en_an_dead_row [gpit] == 0) {
#ifdef TYPE_7_FIXED_SPRITE
							en_an_base_frame [gpit] = (TYPE_7_FIXED_SPRITE - 1) << 1;
#else
							en_an_base_frame [gpit] = (rand () & 3) << 1;
#endif
							en_an_alive [gpit] = 2;
						} else {
							en_an_dead_row [gpit] --;
							en_an_next_frame [gpit] = sprite_17_a;
						}
						break;
					case 2:
						active = 1;
						if (p_estado == EST_NORMAL) {
							malotes [enoffsmasi].mx = (signed char) (addsign (((gpx >> 2) << 2) - gpen_x, en_an_rawv [gpit]));
							malotes [enoffsmasi].x += malotes [enoffsmasi].mx;
							gpen_xx = malotes [enoffsmasi].x >> 4;
							gpen_yy = malotes [enoffsmasi].y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_x ()) malotes [enoffsmasi].x = gpen_x;
#endif
							malotes [enoffsmasi].my = (signed char) (addsign (((gpy >> 2) << 2) - gpen_y, en_an_rawv [gpit]));
							malotes [enoffsmasi].y += malotes [enoffsmasi].my;
							gpen_xx = malotes [enoffsmasi].x >> 4;
							gpen_yy = malotes [enoffsmasi].y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_y ()) malotes [enoffsmasi].y = gpen_y;
#endif
						}
						gpen_cx = malotes [enoffsmasi].x;
						gpen_cy = malotes [enoffsmasi].y;
				}
				break;
#endif
#ifdef ENABLE_CLOUDS
			case 9:
				active = 1;
				gpen_cx = malotes [enoffsmasi].x;
				gpen_cy = malotes [enoffsmasi].y;
				if (gpx != gpen_cx) {
					malotes [enoffsmasi].x += addsign (gpx - gpen_cx, malotes [enoffsmasi].mx);
				}

				// Shoot a coco
				if ((rand () & TYPE_9_SHOOT_FREQ) == 1) {
					shoot_coco ();
				}

				break;
#endif				
			default:
				en_an_next_frame [gpit] = sprite_18_a;
		}

		if (active) {
			// Animate
			en_an_count [gpit] ++;
#ifdef ENABLE_CUSTOM_TYPE_6
			if (gpt != 6) {
#endif
				if (en_an_count [gpit] == 4) {
					en_an_count [gpit] = 0;
					en_an_frame [gpit] = !en_an_frame [gpit];
					en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + en_an_frame [gpit]];
				}
#ifdef ENABLE_CUSTOM_TYPE_6 
			} else {
				en_an_next_frame [gpit] = enem_frames [en_an_base_frame [gpit] + (en_an_vx [gpit] > 0)];
			}
#endif

#if defined(PLAYER_CAN_PUNCH) || defined(PLAYER_CAN_SWORD)
			if (hitter_on && malotes [enoffsmasi].t != 4) {
#ifdef PLAYER_CAN_PUNCH
				if (hitter_frame <= 3) {
					if (collide_pixel (hitter_x + (p_facing ? 6 : 1), hitter_y + 3, gpen_cx, gpen_cy)) {
#endif
#ifdef PLAYER_CAN_SWORD
#endif
						// HIT
#ifdef ENABLE_CUSTOM_TYPE_6
						if (malotes [enoffsmasi].t == 6) {
							en_an_vx [gpit] = addsign (gpen_x - gpx, FANTY_MAX_V);
							en_an_x [gpit] += en_an_vx [gpit];
						}
#endif
						malotes [enoffsmasi].x = gpen_x;
						malotes [enoffsmasi].y = gpen_y;
						en_an_next_frame [gpit] = sprite_17_a;
						//en_an_morido [gpit] = 1;

						malotes [enoffsmasi].life --;
						
						if (malotes [enoffsmasi].life == 0) {
							
#ifdef MODE_128K
							en_an_state [gpit] = GENERAL_DYING;
							en_an_count [gpit] = 8;
							
							wyz_play_sound (6);
#else
							sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
							en_an_current_frame [gpit] = en_an_next_frame [gpit];
							sp_UpdateNow ();
							peta_el_beeper (5);
							en_an_next_frame [gpit] = sprite_18_a;
#endif
#ifdef ENABLE_PURSUERS
							if (gpt != 7) malotes [enoffsmasi].t |= 16;
#else
							malotes [enoffsmasi].t |= 16;
#endif							
							p_killed ++;
#ifdef RANDOM_RESPAWN
							en_an_fanty_activo [gpit] = 0;
							malotes [enoffsmasi].life = FANTIES_LIFE_GAUGE;
#endif
#ifdef ENABLE_PURSUERS
							en_an_alive [gpit] = 0;
							en_an_dead_row [gpit] = DEATH_COUNT_EXPRESSION;
#endif
						} else {
							malotes [enoffsmasi].mx = -malotes [enoffsmasi].mx;
							malotes [enoffsmasi].my = -malotes [enoffsmasi].my;
						}
						
						continue;
					}
				}
			}
#endif
						
			// Collide with player

#ifndef PLAYER_MOGGY_STYLE
			// Platforms: 2013 rewrite!
			// This time coded in a SMARTER way...!
			if (malotes [enoffsmasi].t == 4) {
				if (pregotten && (p_gotten == 0) && (p_saltando == 0)) {
					// Horizontal moving platforms
					if (malotes [enoffsmasi].mx) {
						if (gpy + 16 >= malotes [enoffsmasi].y && gpy + 10 <= malotes [enoffsmasi].y) {
							p_gotten = 1;
							ptgmx = malotes [enoffsmasi].mx << 6;
							p_y = (malotes [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
						}
					}
					
					// Vertical moving platforms
					if (
						(malotes [enoffsmasi].my < 0 && gpy + 18 >= malotes [enoffsmasi].y && gpy + 10 <= malotes [enoffsmasi].y) ||
						(malotes [enoffsmasi].my > 0 && gpy + 17 + malotes [enoffsmasi].my >= malotes [enoffsmasi].y && gpy + 10 <= malotes [enoffsmasi].y)
					) {
						p_gotten = 1;
						ptgmy = malotes [enoffsmasi].my << 6;
						p_y = (malotes [enoffsmasi].y - 16) << 6; gpy = p_y >> 6;
						p_vy = 0;
					}
				}
			} else if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_estado == EST_NORMAL) {
#else
			if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_estado == EST_NORMAL) {
#endif
#ifdef PLAYER_KILLS_ENEMIES
				// Step over enemy
#ifdef PLAYER_CAN_KILL_FLAG
				if (flags [PLAYER_CAN_KILL_FLAG] != 0 &&
					gpy < gpen_cy - 2 && p_vy >= 0 && malotes [enoffsmasi].t >= PLAYER_MIN_KILLABLE) {
#else				
				if (gpy < gpen_cy - 2 && p_vy >= 0 && malotes [enoffsmasi].t >= PLAYER_MIN_KILLABLE) {
#endif					
					en_an_next_frame [gpit] = sprite_17_a;					
#ifdef MODE_128K
					wyz_play_sound (6);
					en_an_state [gpit] = GENERAL_DYING;
					en_an_count [gpit] = 8;
#else					
					sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
					en_an_current_frame [gpit] = en_an_next_frame [gpit];
					sp_UpdateNow ();
					peta_el_beeper (5);
					en_an_next_frame [gpit] = sprite_18_a;
#endif					
					malotes [enoffsmasi].t |= 16;			// Mark as dead				
					p_killed ++;
#ifdef ACTIVATE_SCRIPTING
#ifdef EXTENDED_LEVELS
					if (level_data->activate_scripting) {
#endif
						// Run this screen fire script or "entering any".
						run_script (n_pant + n_pant + 1);
						run_script (2 * MAP_W * MAP_H + 1);
#ifdef EXTENDED_LEVELS
					}
#endif						
#endif
				} else if (p_life > 0) {
#else
				if (p_life > 0) {
#endif
					tocado = 1;
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
					if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
#ifdef MODE_128K
						kill_player (7);
#else
						kill_player (4);
#endif
					}
#else
#ifdef MODE_128K
					kill_player (7);
#else
					kill_player (4);
#endif
#endif
#ifdef TYPE_6_KILL_ON_TOUCH
					if (gpt == 6) {
						en_an_next_frame [gpit] = sprite_18_a;
						malotes [enoffsmasi].t |= 16;
					}
#endif
#ifdef PLAYER_BOUNCES
#ifndef PLAYER_MOGGY_STYLE
#ifdef RANDOM_RESPAWN
					if (en_an_fanty_activo [gpit] == 0) {
						p_vx = addsign (malotes [enoffsmasi].mx, PLAYER_MAX_VX);
						p_vy = addsign (malotes [enoffsmasi].my, PLAYER_MAX_VX);
					} else {
						p_vx = en_an_vx [gpit] + en_an_vx [gpit];
						p_vy = en_an_vy [gpit] + en_an_vy [gpit];
					}
#else
					p_vx = addsign (malotes [enoffsmasi].mx, PLAYER_MAX_VX);
					p_vy = addsign (malotes [enoffsmasi].my, PLAYER_MAX_VX);
#endif
#else
					if (malotes [enoffsmasi].mx) {
						p_vx = addsign (gpx - gpen_cx, abs (malotes [enoffsmasi].mx) << 8);
					}
					if (malotes [enoffsmasi].my) {
						p_vy = addsign (gpy - gpen_cy, abs (malotes [enoffsmasi].my) << 8);
					}
#endif
#endif
				}
			}

#ifdef PLAYER_CAN_FIRE
			// Collide with bullets
#ifdef FIRE_MIN_KILLABLE
			if (malotes [enoffsmasi].t >= FIRE_MIN_KILLABLE) {
#endif
				for (gpjt = 0; gpjt < MAX_BULLETS; gpjt ++) {
					if (bullets_estado [gpjt] == 1) {
						blx = bullets_x [gpjt] + 3;
						bly = bullets_y [gpjt] + 3;
						if (blx >= gpen_cx && blx <= gpen_cx + 15 && bly >= gpen_cy && bly <= gpen_cy + 15) {
#ifdef RANDOM_RESPAWN
							if (en_an_fanty_activo [gpit]) {
								en_an_vx [gpit] += addsign (bullets_mx [gpjt], 128);
							}
#endif
#ifdef ENABLE_CUSTOM_TYPE_6
							if (malotes [enoffsmasi].t == 6) {
								en_an_vx [gpit] += addsign (bullets_mx [gpjt], 128);
							}
#endif
							malotes [enoffsmasi].x = gpen_x;
							malotes [enoffsmasi].y = gpen_y;
							en_an_next_frame [gpit] = sprite_17_a;
							en_an_morido [gpit] = 1;
							bullets_estado [gpjt] = 0;
#ifndef PLAYER_MOGGY_STYLE
							if (malotes [enoffsmasi].t != 4) malotes [enoffsmasi].life --;
#else
							malotes [enoffsmasi].life --;
#endif
							if (malotes [enoffsmasi].life == 0) {
								sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_next_frame [gpit] - en_an_current_frame [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
								en_an_current_frame [gpit] = en_an_next_frame [gpit];
								sp_UpdateNow ();
#ifdef MODE_128K
								#asm
									halt
								#endasm
								wyz_play_sound (6);
#else
								peta_el_beeper (5);
#endif
								en_an_next_frame [gpit] = sprite_18_a;
								if (gpt != 7) malotes [enoffsmasi].t |= 16;
								p_killed ++;
#ifdef RANDOM_RESPAWN
								en_an_fanty_activo [gpit] = 0;
								malotes [enoffsmasi].life = FANTIES_LIFE_GAUGE;
#endif
#ifdef ENABLE_PURSUERS
								en_an_alive [gpit] = 0;
								en_an_dead_row [gpit] = DEATH_COUNT_EXPRESSION;
#endif
							}
						}
					}
				}
#ifdef FIRE_MIN_KILLABLE
			}
#endif
#endif

#ifdef RANDOM_RESPAWN
			// Activar fanty

			if (malotes [enoffsmasi].t > 15 && en_an_fanty_activo [gpit] == 0 && (rand () & 31) == 1) {
				en_an_fanty_activo [gpit] = 1;
				if (p_y > 5120) en_an_y [gpit] = -1024; else en_an_y [gpit] = 10240;
				en_an_x [gpit] = (rand () % 240 - 8) << 6;
				en_an_vx [gpit] = en_an_vy [gpit] = 0;
				en_an_base_frame [gpit] = 4;
			}
#endif
		}
	}
#if defined(SLOW_DRAIN) && defined(PLAYER_BOUNCES)
	lasttimehit = tocado;
#endif
}
