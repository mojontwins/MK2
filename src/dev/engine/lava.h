// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// lava.h
// Experimental

unsigned char lava_y;
unsigned char lava_ct;

void init_lava (void) {
	// FIX: Esto solo funciona en modo 128k/compressed levels.
	// Si lo necesitas en otra configuración, hay que cambiar esto
	lava_y = 20 * level_data->map_h;
	lava_ct = 0;
	flags [LAVA_FLAG] = 0;
}

void lava_reenter (void) {
	// Solo vale para fases verticales. Si quieres otra cosa, modifica
	if (lava_y / 20 == n_pant) {
		gpd = VIEWPORT_Y + (lava_y % 20);
		for (gpjt = 18 + VIEWPORT_Y; gpjt >= gpd; gpjt --) {
			for (gpit = VIEWPORT_X + LAVA_X1; gpit < VIEWPORT_X + LAVA_X2; gpit += 2) {
				draw_coloured_tile (gpit, gpjt, LAVA_T);
			}	
		}
	}
}

unsigned char do_lava (void) {
	gpd = lava_y % 20;
	gpjt = (lava_y / 20 == n_pant);
	if (LAVA_PERIOD == lava_ct ++) {
		lava_y --;
		lava_ct = 0;
		if (gpjt) {
			_AY_PL_SND (9);
			if (gpd < 19) {
				for (gpit = VIEWPORT_X + LAVA_X1; gpit < VIEWPORT_X + LAVA_X2; gpit += 2) {
					draw_coloured_tile (gpit, VIEWPORT_Y + gpd, LAVA_T);
				}
			}
		}
	}
	if (gpjt && (gpy >> 3) >= gpd - 1) return 1; else return 0;
}
