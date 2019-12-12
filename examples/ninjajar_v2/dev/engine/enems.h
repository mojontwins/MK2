// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// enems.h
// Enemy management, new style

// Ninjajar Clouds not supported, sorry!
// Type 5 "random respawn" not supported sorry! (but easily punchable!)

// There are new, more suitable defines now.
// ENABLE_FANTIES
// ENABLE_LINEAR_ENEMIES
// ENABLE_PURSUE_ENEMIES
// ENABLE_SHOOTERS

#include "engine/enemmods/helper_funcs.h"

#if WAYS_TO_DIE == 1
	#include "engine/enemmods/kill_enemy.h"
#elif WAYS_TO_DIE > 1
	#include "engine/enemmods/kill_enemy_multiple.h"
#endif

void mueve_bicharracos (void) {
	#if !defined (PLAYER_GENITAL) || defined (PLAYER_NEW_GENITAL)
		p_gotten = ptgmy = ptgmx = 0;
	#endif

	tocado = 0;

	for (enit = 0; enit < 3; ++ enit) {
		active = killable = animate = 0;
		enoffsmasi = enoffs + enit;

		gpen_x = baddies [enoffsmasi].x;
		gpen_y = baddies [enoffsmasi].y;

		if (baddies [enoffsmasi].t == 0) {
			en_an_n_f [enit] = sprite_18_a;
		} else if (en_an_state [enit] == GENERAL_DYING) {
			if (en_an_count [enit]) {
				-- en_an_count [enit];
				en_an_n_f [enit] = sprite_17_a;
			} else {
				en_an_state [enit] = 0;
				en_an_n_f [enit] = sprite_18_a;
			}
		} else {

			#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
				if (baddies [enoffsmasi].t & 4) {
					enemy_shoots = 1;
				} else enemy_shoots = 0;
			#endif
			gpt = baddies [enoffsmasi].t >> 3;

			// Gotten preliminary:	
			if (gpt == 8) {
				#ifdef PLAYER_NEW_GENITAL	
					pregotten =	(gpx + 12 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 12) &&
								(gpy + 15 >= baddies [enoffsmasi].y && gpy <= baddies [enoffsmasi].y);
				#elif !defined (PLAYER_GENITAL)
					#if defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_8_BOTTOM)
						pregotten = (gpx + 11 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 11);
					#else
						pregotten = (gpx + 15 >= baddies [enoffsmasi].x && gpx <= baddies [enoffsmasi].x + 15);
					#endif
				#endif
			}

			switch (gpt) {
				#ifdef ENABLE_PATROLLERS
					case 1:			// linear
						killable = 1;
					case 8:			// moving platforms
						#include "engine/enemmods/move_linear.h"
						break;
				#endif
				#ifdef ENABLE_FANTIES
					case 2:			// flying
						#include "engine/enemmods/move_fanty.h"
						break;
				#endif
				#ifdef ENABLE_PURSUERS
					case 3:			// pursuers
						#include "engine/enemmods/move_pursuers.h"
						break;
				#endif
				#ifdef ENABLE_DROPS
					case 9:			// drops
						#include "addons/drops/move.h"
						break;
				#endif
				#ifdef ENABLE_ARROWS
					case 10:		// arrows
						#include "addons/arrows/move.h"
						break;
				#endif
				#ifdef ENABLE_HANNA_MONSTERS_11
					case 11:		// Hanna monsters type 11
						#include "engine/enemmods/move_hanna_11.h"
						break;
				#endif
				default:
					if (gpt > 15 && en_an_state [enit] != GENERAL_DYING)
					en_an_n_f [enit] = sprite_18_a;
			}

			if (active) {
				if (animate) {
					gpjt = baddies [enoffsmasi].mx ? ((gpen_cx + 4) >> 3) & 1 : ((gpen_cy + 4) >> 3) & 1;
					en_an_n_f [enit] = enem_frames [en_an_base_frame [enit] + gpjt];
				}

				// Carriable box launched and hit...
				#ifdef ENABLE_FO_CARRIABLE_BOXES
					#ifdef CARRIABLE_BOXES_THROWABLE
						#include "engine/enemmods/throwable.h"
					#endif
				#endif	
				
				// Hitter
				#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
					#include "engine/enemmods/hitter.h"
				#endif		

				// Bombs
				#if defined (PLAYER_SIMPLE_BOMBS)
					#include "engine/enemmods/bombs.h"
				#endif

				// Bullets
				#ifdef PLAYER_CAN_FIRE
					#include "engine/enemmods/bullets.h"
				#endif

				// Collide with player
				#if !defined (DISABLE_PLATFORMS)
					#ifdef PLAYER_NEW_GENITAL
						#include "engine/enemmods/platforms_25d.h"
					#elif !defined (PLAYER_GENITAL)
						#include "engine/enemmods/platforms.h"
					#endif
				#endif 	// ends with  } else
				if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_state == EST_NORMAL) {
					#ifdef PLAYER_KILLS_ENEMIES
						#include "engine/enemmods/step_on.h"
					#endif
					if (p_life > 0) {
						tocado = 1;
					}

					#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
						if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
							p_killme = SFX_PLAYER_DEATH_ENEMY;
							#ifdef CUSTOM_HIT
								was_hit_by_type = gpt;
							#endif
						}
					#else
						p_killme = SFX_PLAYER_DEATH_ENEMY;
						#ifdef CUSTOM_HIT
							was_hit_by_type = gpt;
						#endif
					#endif

					#ifdef FANTIES_KILL_ON_TOUCH
						if (gpt == 2) enemy_kill (FANTIES_LIFE_GAUGE);
					#endif

					#ifdef PLAYER_BOUNCES
						#ifndef PLAYER_GENITAL

							p_vx = addsign (baddies [enoffsmasi].mx, PLAYER_VX_MAX << 1);
							p_vy = addsign (baddies [enoffsmasi].my, PLAYER_VX_MAX << 1);

						#else
							if (baddies [enoffsmasi].mx) {
								p_vx = addsign (gpx - gpen_cx, abs (baddies [enoffsmasi].mx) << 8);
							}
							if (baddies [enoffsmasi].my) {
								p_vy = addsign (gpy - gpen_cy, abs (baddies [enoffsmasi].my) << 8);
							}
						#endif
					#endif
				}
			}			
		}

		enems_loop_continue:

		// Render
		#ifdef PIXEL_SHIFT
			if ((baddies [enoffsmasi].t & 0x78) == 8) gpen_y -= PIXEL_SHIFT;
		#endif

		enem_move_spr_abs ();			
	}

	#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
		lasttimehit = tocado;
	#endif
}
