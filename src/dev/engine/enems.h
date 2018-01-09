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
#elif WAYS_TO_DIE == 2
#include "engine/enemmods/kill_enemy_multiple.h"
#endif

unsigned char pregotten;
#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
unsigned char enemy_shoots;
#endif
void mueve_bicharracos (void) {

#if !defined (PLAYER_GENITAL) || defined (PLAYER_NEW_GENITAL)
	p_gotten = 0;
	ptgmx = 0;
	ptgmy = 0;
#endif

	tocado = 0;
	p_gotten = 0;
	for (gpit = 0; gpit < 3; gpit ++) {
		active = killable = animate = 0;
		enoffsmasi = enoffs + gpit;
		gpen_x = baddies [enoffsmasi].x;
		gpen_y = baddies [enoffsmasi].y;

		if (en_an_state [gpit] == GENERAL_DYING) {
			en_an_count [gpit] --;
			if (0 == en_an_count [gpit]) {
				en_an_state [gpit] = 0;
				en_an_n_f [gpit] = sprite_18_a;
				continue;
			}
		}

		// Gotten preliminary:	
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

#if defined (ENABLE_SHOOTERS) || defined (ENABLE_ARROWS)
		if (baddies [enoffsmasi].t & 4) {
			enemy_shoots = 1;
		} else enemy_shoots = 0;
#endif
		gpt = baddies [enoffsmasi].t >> 3;

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
				if (gpt > 15 && en_an_state [gpit] != GENERAL_DYING) en_an_n_f [gpit] = sprite_18_a;
		}

		if (active) {
			if (animate) {
				#include "engine/enemmods/animate.h"
			}

			// Carriable box launched and hit...
#ifdef ENABLE_FO_CARRIABLE_BOXES
#ifdef CARRIABLE_BOXES_THROWABLE
			#include "engine/enemmods/throwable.h"
#endif
#endif

#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
			#include "engine/enemmods/hitter.h"
#endif

#if defined (PLAYER_SIMPLE_BOMBS)
			#include "engine/enemmods/bombs.h"
#endif

			// Collide with player
#if !defined (DISABLE_PLATFORMS)
#ifdef PLAYER_NEW_GENITAL
			#include "engine/enemmods/platforms_25d.h"
#elif !defined (PLAYER_GENITAL)
			#include "engine/enemmods/platforms.h"
#endif
#endif
			if ((tocado == 0) && collide (gpx, gpy, gpen_cx, gpen_cy) && p_state == EST_NORMAL) {
#ifdef PLAYER_KILLS_ENEMIES
				// Step over enemy
				if (
#ifdef PLAYER_CAN_KILL_FLAG
					flags [PLAYER_CAN_KILL_FLAG] &&
#endif
#if defined (PLAYER_HAS_SWIM) && defined (SWITCHABLE_ENGINES)
					p_engine != SENG_SWIM &&
#endif
					gpy < gpen_cy - 2 && p_vy >= 0 && baddies [enoffsmasi].t >= PLAYER_MIN_KILLABLE && killable) {

					en_an_n_f [gpit] = sprite_17_a;
#ifdef MODE_128K
					_AY_PL_SND (SFX_KILL_ENEMY);
					en_an_state [gpit] = GENERAL_DYING;
					en_an_count [gpit] = 8;
#else
					sp_MoveSprAbs (sp_moviles [gpit], spritesClip, en_an_n_f [gpit] - en_an_c_f [gpit], VIEWPORT_Y + (gpen_cy >> 3), VIEWPORT_X + (gpen_cx >> 3), gpen_cx & 7, gpen_cy & 7);
					en_an_c_f [gpit] = en_an_n_f [gpit];
					sp_UpdateNow ();
					beep_fx (SFX_KILL_ENEMY);
					en_an_n_f [gpit] = sprite_18_a;
#endif
					baddies [enoffsmasi].t |= 128;			// Mark as dead
#ifdef BODY_COUNT_ON
					flags [BODY_COUNT_ON] ++;
#else
					p_killed ++;
#endif					
#ifdef ACTIVATE_SCRIPTING
#ifdef RUN_SCRIPT_ON_KILL
#ifdef EXTENDED_LEVELS
					if (level_data->activate_scripting) {
#endif
						run_script (2 * MAP_W * MAP_H + 5);
#ifdef EXTENDED_LEVELS
					}
#endif
#endif
#endif
					continue;
				} else if (p_life > 0) {
#else
				if (p_life > 0) {
#endif
					tocado = 1;
#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
					if ((lasttimehit == 0) || ((maincounter & 3) == 0)) {
						kill_player (SFX_PLAYER_DEATH_ENEMY);
					}
#else
					kill_player (SFX_PLAYER_DEATH_ENEMY);
#endif
#ifdef FANTIES_KILL_ON_TOUCH
					if (gpt == 2) {
						en_an_n_f [gpit] = sprite_18_a;
						baddies [enoffsmasi].t |= 128;
					}
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

			// Render
			#include "engine\enemmods\render.h"

#ifdef PLAYER_CAN_FIRE
			#include "engine\enemmods\bullets.h"
#endif

		} else {
			sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, -2, -2, 0, 0);
		}
	}
#if defined (SLOW_DRAIN) && defined (PLAYER_BOUNCES)
	lasttimehit = tocado;
#endif

#ifdef CUSTOM_HIT
	// This is for kill_player.
	// If kill_player is called out of the enems loop,
	// we will know...
	gpt = 0xff;
#endif
}
