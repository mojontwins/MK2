#ifdef PLAYER_GENITAL

#else
	if (possee) {
		cy1 = cy2 = (gpy + 16) >> 4;
		cx1 = ptx1; cx2 = ptx2;
		cm_two_points ();
		
		if (pt1 & 32) {
			p_gotten = 1; ptgmy = 0;
			ptgmx = (pt1 & 1) ? 64 : -64;
		}
		if (pt2 & 32) {
			p_gotten = 1; ptgmy = 0;
			ptgmx = (pt2 & 1) ? 64 : -64;
		}
	}
#endif
