
// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// mainloop.h
// This is, the main game loop (plus initializations, plus menu, plus level screen...

#include "mainloop/hide_sprites.h"

unsigned char action_pressed;

#ifdef GET_X_MORE
	unsigned char *getxmore = " GET X MORE ";
#endif

#ifdef COMPRESSED_LEVELS
	unsigned char mlplaying;
#endif

unsigned char success;
unsigned char playing;

// Main loop

void main (void) {
	// *********************
	// SYSTEM INITIALIZATION
	// *********************

	cortina ();

	#asm
		di
	#endasm

	// System initialization
	#include "mainloop/mysystem.h"

	// Sprite creation
	#include "mainloop/sprdefs.h"

	#ifdef MODE_128K
			#asm
				ei
			#endasm

			// Music player initialization
		#ifndef NO_SOUND
			#ifdef USE_ARKOS
				_AY_ST_ALL ();
			#else
				wyz_init ();
			#endif
		#endif
	#endif

	// If not using compressed levels, make backup of enemy types now!
	#if defined (ENEMY_BACKUP) && !defined (COMPRESSED_LEVELS)
		backup_baddies ();
	#endif

	while (1) {

		// ************
		// TITLE SCREEN
		// ************

		#include "mainloop/title_screen.h"

		// *******************
		// GAME INITIALIZATION
		// *******************

		#include "mainloop/game_init.h"

		#ifdef COMPRESSED_LEVELS
			while (mlplaying) {
				prepare_level ();

				// ****************
				// NEW LEVEL SCREEN
				// ****************

				#include "mainloop/new_level.h"
		#endif

		// ********************
		// LEVEL INITIALIZATION
		// ********************

		#include "mainloop/level_init.h"

		// *********
		// MAIN LOOP
		// *********

		while (playing) {

			// Timer stuff
			#include "mainloop/timer.h"

			// New screen?
			if (n_pant != o_pant) {
				o_pant = n_pant;
				draw_scr ();
				#ifdef ENABLE_LAVA
					if (flags [LAVA_FLAG] == 1) lava_reenter ();
				#endif
			}

			// Update HUD
			update_hud ();

			// Main counter and main flip-flop
			maincounter ++;
			half_life = !half_life;

			// Move player
			move ();

			// Move hitter
			#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
				if (hitter_on) render_hitter ();
			#endif
			#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
				gpx = p_x;
				gpy = p_y;
			#endif
			// Move enemies
			mueve_bicharracos ();
			#ifdef CARRIABLE_BOXES_THROWABLE
				if (n_pant != o_pant) continue;
			#endif

			#ifdef ENABLE_SHOOTERS
				move_cocos ();
			#endif

			#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
				#ifdef BREAKABLE_ANIM
					// Breakable
					if (do_process_breakable) process_breakable ();
				#endif
			#endif

			#ifdef PLAYER_SIMPLE_BOMBS
				// Update bombas
				bomb_run ();
			#endif

			#ifdef PLAYER_CAN_FIRE
				// Move bullets
				mueve_bullets ();
			#endif

			#ifdef ENABLE_TILANIMS
				do_tilanims ();
			#endif

			// Update sprites
			#include "mainloop/update_sprites.h"

			// Update to screen
			sp_UpdateNow();

			// Experimental
			#ifdef ENABLE_LAVA
				if (flags [LAVA_FLAG] == 1) {
					if (do_lava ()) {
						kill_player (SFX_PLAYER_DEATH_LAVA);
						success = 2;	// repeat
						playing = 0;
						//continue;
					}
				}
			#endif

			#ifdef PLAYER_FLICKERS
				// Flickering
				if (p_state == EST_PARP) {
					p_state_ct --;
					if (p_state_ct == 0)
						p_state = EST_NORMAL;
				}
			#endif

			#ifndef DISABLE_HOTSPOTS
				#include "mainloop/hotspots.h"
			#endif

			// Select object
			#if defined (MSC_MAXITEMS) || defined (ENABLE_SIM)
				do_inventory_fiddling ();
			#endif

			// Scripting related stuff
			#include "mainloop/scripting.h"

			// Interact w/floating objects
			#ifdef ENABLE_FLOATING_OBJECTS
				FO_do ();
			#endif

			// Pause/Abort handling
			#ifdef PAUSE_ABORT
				#include "mainloop/pause_abort.h"
			#endif

			// Win game condition
			#include "mainloop/win_game.h"

			// Game over condition
			#include "mainloop/game_over.h"

			// Warp to level condition (3)
			// Game ending (4)
			#if defined (COMPRESSED_LEVELS) && defined (MODE_128K)
				if (script_result > 2) {
					success = script_result;	// Warp_to (3), Game ending (4)
					playing = 0;
				}
			#endif
			
			// Respawn
			#ifdef DIE_AND_RESPAWN
				#include "mainloop/die_and_respawn.h"
			#endif

			// Flick screen
			#ifndef PLAYER_CANNOT_FLICK_SCREEN
				flick_screen ();
			#elif defined (PLAYER_WRAP_AROUND)
				// Wrap around!
				wrap_around ();
			#endif

			// Main loop is done!
		}

		#ifdef MODE_128K
			_AY_ST_ALL ();
		#endif

		hide_sprites (0);
		sp_UpdateNow ();

		#ifdef COMPRESSED_LEVELS
			switch (success) {
				case 0:
					#if defined (TIMER_ENABLE) && defined (TIMER_GAMEOVER_0) && defined (SHOW_TIMER_OVER)
						if (ctimer.zero) time_over (); else game_over ();
					#else
						#ifdef MODE_128K
							//_AY_PL_MUS (8);
						#endif
						//game_over ();
						print_message (" GAME OVER! ");
					#endif
					mlplaying = 0;
					active_sleep (250);
					break;
				case 1:
					//_AY_PL_MUS (7);
					print_message (" ZONE CLEAR ");
					level ++;
					active_sleep (250);
					//do_extern_action (0);
					break;
				case 3:
					blackout_area ();
					level = warp_to_level;
					break;
				case 4:
					get_resource (2, 16384);
					active_sleep (1000);
					_AY_ST_ALL ();
					cortina ();
					//_AY_PL_MUS (12);
					active_sleep (130);
					// credits ();
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
			//_AY_PL_MUS (8)
			game_over ();
		}
		active_sleep (500);
		cortina ();
	#endif
	}
}
