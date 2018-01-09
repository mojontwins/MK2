#ifdef PLAYER_GENITAL

#else
	if (possee) {
		gpy = p_y >> 6;
		pt1 = attr (ptx1, pty3);
		pt2 = attr (ptx2, pty3);
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
