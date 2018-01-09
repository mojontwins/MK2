// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// Floating objects
// Preliminary version 0.2
// This only works for side-view with bounding box 8 bottom by now.

// TODO: When this is working, cleanup, refactor and optimize!

// Let's go!
// Use a power of 2!
#define MAX_FLOATING_OBJECTS 	8

#include "engine/fo_common.h"

void FO_do (void) {

#ifdef FO_GRAVITY
		// Make fall
		fo_it = maincounter & (MAX_FLOATING_OBJECTS - 1);
		
		if (
			f_o_t [fo_it] && attr (f_o_x [fo_it], f_o_y [fo_it] + 1) < 4
#ifdef ENABLE_FO_FIREZONES
			&& f_o_t [fo_it] != FT_FIREZONES
#endif
#ifdef ENABLE_FO_CARRIABLE_BOXES
			&& fo_it != p_hasbox
#endif
#ifdef FO_SOLID_FLOOR
			&& f_o_y [fo_it] < 9
#endif
		) {
			FO_unpaint (fo_it);
			f_o_y [fo_it] ++;
			if (f_o_y [fo_it] == 10) f_o_t [fo_it] = 0; else FO_paint (fo_it);
#ifdef ENABLE_FO_SCRIPTING
			flags [FO_X_FLAG] = f_o_x [fo_it];
			flags [FO_Y_FLAG] = f_o_y [fo_it];
			flags [FO_T_FLAG] = f_o_t [fo_it];
			run_fire_script ();
#endif
		}
#endif

		// Make drain!
#if defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_DRAIN)
		if (0 == (maincounter & CARRIABLE_BOXES_DRAIN) && 99 != p_hasbox) {
			p_life --;
#ifdef MODE_128K
			_AY_PL_SND (SFX_FO_DRAIN);
#else
			beep_fx (SFX_FO_DRAIN);
#endif
		}
#endif
		// I don't think this is usable anywhere else. Good job, Leovigildo III.

#if defined (ENABLE_FO_CARRIABLE_BOXES) || defined (ENABLE_FO_OBJECT_CONTAINERS)
#ifdef CARRIABLE_BOXES_CORCHONETA
		fo_y = (gpy + 8) >> 4;
#else
		fo_y = (gpy >> 4) + 1;
#endif
		fo_x = (gpx + 8) >> 4;

		// Read keys / controller
		fo_gp = (joyfunc) (&keys);

#ifdef ENABLE_FO_CARRIABLE_BOXES
#ifdef CARRIABLE_BOXES_THROWABLE
		if ((fo_gp & sp_FIRE) == 0) {
			if (99 != p_hasbox && fo_fly == 0) {
				fo_fly = 1;
				if (p_facing) f_o_mx = 16; else f_o_mx = -16;
				f_o_xp = gpx;
				f_o_yp = gpy - 8;
				f_o_t [p_hasbox] = 0;
				p_hasbox = 99;
#ifdef CARRIABLE_BOXES_ALTER_JUMP
				// Restore jump
				PLAYER_JMP_VY_MAX = PLAYER_JMP_VY_MAX;
#endif
			}
		}

		if (fo_fly) {
			f_o_xp += f_o_mx;

			// Kill enemy? -> Moved to enems.h!!

			// Check if we should kill the box...
			if (f_o_xp > 239 || (attr ((f_o_xp + 8) >> 4, (f_o_yp + 8) >> 4) & 8)) {
				fo_fly = 0;
#ifdef MODE_128K
				_AY_PL_SND (SFX_FO_DESTROY);
#else
				beep_fx (SFX_FO_DESTROY);
#endif
				delete_box_sprite ();
			} else {
				draw_box_sprite ();
			}
		}
#endif
#endif

#if defined (SCRIPTING_DOWN)
		if ((fo_gp & sp_DOWN) == 0)
#elif defined (SCRIPTING_KEY_FIRE)
		if ((fo_gp & sp_FIRE) == 0)
#elif defined (SCRIPTING_KEY_M) {
		if (sp_KeyPressed (key_m))
#endif
		{
			if (0 == d_prs) {
				d_prs = 1;
#ifdef ENABLE_FO_CARRIABLE_BOXES
				if (99 != p_hasbox) {
					// Drop box?
					if ((attr (fo_x, fo_y - 2) & 8) == 0) {
						// revisa esto...
						if (attr (fo_x, fo_y - 1) & 8) {
							if (p_facing) fo_x --; else fo_x ++;
						}
						f_o_y [p_hasbox] = fo_y - 1;
						p_y = (fo_y - 2) << 10;
						f_o_x [p_hasbox] = fo_x;
						FO_paint (p_hasbox);
						p_hasbox = 99;
#ifdef MODE_128K
						_AY_PL_SND (SFX_FO_DROP);
#else
						beep_fx (SFX_FO_DROP);
#endif
#ifdef SCRIPTING_KEY_FIRE
						invalidate_fire = 1;
#endif
#ifdef CARRIABLE_BOXES_ALTER_JUMP
						// Restore jump
						PLAYER_JMP_VY_MAX = PLAYER_JMP_VY_MAX;
#endif
						delete_box_sprite ();
					}
				} else
#endif
				{
					
#ifdef FO_DETECT_INTERACTION_CENTER
					fo_x = (gpx + 8) >> 4;
#else				
					// Calculate interactuable cell - it depends where the player is facing	
					if (0 == p_facing) fo_x = (gpx + 4) >> 4; else fo_x = (gpx + 12) >> 4;
#endif					

					fo_it = 0;
					while (fo_it < MAX_FLOATING_OBJECTS) {
#ifdef ENABLE_FO_CARRIABLE_BOXES
						if (f_o_y [fo_it] == fo_y && f_o_x [fo_it] == fo_x) {
							if (f_o_t [fo_it] == FT_CARRIABLE_BOXES) {
								p_hasbox = fo_it;
								FO_unpaint (fo_it);
#ifdef MODE_128K
								_AY_PL_SND (SFX_FO_GET);
#else
								beep_fx (SFX_FO_GET);
#endif
#ifdef SCRIPTING_KEY_FIRE
								invalidate_fire = 1;
#endif
#ifdef CARRIABLE_BOXES_ALTER_JUMP
								// Alter jump
								PLAYER_JMP_VY_MAX = CARRIABLE_BOXES_ALTER_JUMP;
#endif
							}
						}
#endif

#if defined (ENABLE_FO_OBJECT_CONTAINERS) || defined (ENABLE_FO_FIREZONES)
						if (f_o_x [fo_it] == fo_x
#ifndef CARRIABLE_BOXES_CORCHONETA
							&& f_o_y [fo_it] == fo_y - 1
#else
							&& f_o_y [fo_it] == fo_y
#endif
						) {
#ifdef ENABLE_FO_OBJECT_CONTAINERS
							if (f_o_t [fo_it] & 128) {
								// Tengo que cambiar lo que haya en items [flags [FLAG_ITEM_SELECTED]]
								// por lo que haya en flags [f_o_t [fo_it] & 127]
								fo_st = f_o_t [fo_it] & 127;
								fo_au = flags [fo_st];
								flags [fo_st] = items [flags [FLAG_SLOT_SELECTED]];
								items [flags [FLAG_SLOT_SELECTED]] = fo_au;
								display_items ();
								
#ifdef SHOW_EMPTY_CONTAINER
								FO_paint (fo_it);
#else								
								if (flags [fo_st]) FO_paint (fo_it); else FO_unpaint (fo_it);
#endif
#ifdef MODE_128K
								_AY_PL_SND (SFX_CONTAINER);
#else								
								beep_fx (SFX_CONTAINER);
#endif								
#ifdef SCRIPTING_KEY_FIRE
								invalidate_fire = 1;
#endif
#ifdef ENABLE_SIM
								// If all objects are in place, FLAG 29 is set...
								sim_check ();
#endif
							}
#endif
#ifdef ENABLE_FO_FIREZONES
							if (f_o_t [fo_it] == FT_FIREZONES) {
								run_fire_script ();
							}
#endif
						}
#endif
						fo_it ++;
					}
				}
			}
		} else {
			d_prs = 0;
		}

#ifdef ENABLE_FO_CARRIABLE_BOXES
		// Update sprite?
		if (p_hasbox != 99) sp_MoveSprAbs (sp_carriable, spritesClip, 0, VIEWPORT_Y + (gpy >> 3) - 1, VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
#endif

#endif
}
