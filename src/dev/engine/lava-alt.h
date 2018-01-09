// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// lava-alt.h
// Experimento para Ninjajar de la Covertape

unsigned char *lava_ptr;
unsigned char lava_ct, lava_sct, lava_it, lava_t;
unsigned char lava_state;
unsigned char lava_y, lava_yy;
unsigned char lava_half;

#define LAVA_TICK_SPEED 7	// power of two minus 1!
#define LAVA_IDLE_TIME	8

void lava_init (void) {
	lava_ct = lava_state = 0;
	lava_sct = LAVA_IDLE_TIME;
	lava_y = 20;
}

void lava_do (void) {
	// Lava tick:
	lava_ct = (lava_ct + 1) & LAVA_TICK_SPEED;
	if (lava_ct) return;
	
	// Do
	switch (lava_state) {
		case 0:
			// Idle for some time
			if (lava_sct) {
				lava_sct --;
			} else {
				lava_state = 1;
			}
			break;
			
		case 1:
			// Raise lava!
			lava_y --;
			
			if (lava_y < 20) {
				for (lava_it = 0; lava_it < 30; lava_it += 2) {
					draw_coloured_tile (VIEWPORT_X + lava_it, VIEWPORT_Y + lava_y, 32);
				}
			}
			
			if (lava_y == 17) {
				lava_state = 2;
				lava_ct = LAVA_IDLE_TIME;
			}
			
		case 2:
			// Idle for some time
			if (lava_sct) {
				lava_sct --;
			} else {
				lava_state = 3;
			}
			break;
			
		case 3:
			// Lower lava!
			lava_half = (lava_y & 1) << 1;
			lava_yy = lava_y >> 1;
			lava_ptr = map_buff + (lava_yy << 4) - lava_yy;
			for (lava_it = 0; lava_it < 30; lava_it += 2) {
				lava_t = (*lava_ptr << 2) + 64 + lava_half;
				lava_ptr ++;
				gen_pt = tileset + 2048 + lava_t;
				sp_PrintAtInv (lava_y, lava_it, *gen_pt ++, lava_t ++);
				sp_PrintAtInv (lava_y, lava_it + 1, *gen_pt ++, lava_t ++);
			}
			
			lava_y ++;
			if (lava_y == 20) {
				lava_state = 0;
				lava_ct = LAVA_IDLE_TIME;
			}
	}
}
