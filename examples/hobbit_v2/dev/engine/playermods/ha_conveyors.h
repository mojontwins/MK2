#ifdef PLAYER_GENITAL

#else
	if (possee) {
		cy1 = cy2 = (gpy + 16) >> 4;
		cx1 = ptx1; cx2 = ptx2;
		cm_two_points ();
		
		if (at1 & 32) {
			p_gotten = 1; ptgmy = 0;
			ptgmx = (at1 & 1) ? 64 : -64;
		}
		if (at2 & 32) {
			p_gotten = 1; ptgmy = 0;
			ptgmx = (at2 & 1) ? 64 : -64;
		}
	}
#endif
