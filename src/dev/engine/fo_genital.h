// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// Floating objects for top-down
// Preliminary version 0.1
// This only works for top-down with "new genital" style collision for now

// Will just make containers, for now

// TODO: When this is working, cleanup, refactor and optimize!

// Let's go!
// Use a power of 2!
#define MAX_FLOATING_OBJECTS 	8

#include "engine/fo_common.h"

void FO_do (void) {
	fo_gp = (joyfunc) (&keys);

	if ((fo_gp & sp_FIRE) == 0) {
		if (0 == d_prs) {
			fo_it = 0;
			while (fo_it < MAX_FLOATING_OBJECTS) {
				// Collision / interaction (is the player touching the f.o.?)
				// tile->pixel
				fo_x = f_o_x [fo_it] << 4;
				fo_y = f_o_y [fo_it] << 4;

				// Bounding box to check if player is around.
				// (adapted for NEW_GENITAL-style collision)
				if (gpx + 15 >= fo_x && gpx <= fo_x + 15 && gpy + 16 >= fo_y && gpy <= fo_y + 8) {

	#if defined(ENABLE_FO_OBJECT_CONTAINERS)
					// Containers...
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

				}

				fo_it ++;
			}
			d_prs = 1;
		}
	} else d_prs = 0;
}