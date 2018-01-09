#ifdef PLAYER_GENITAL
	// First, preliminary version. No real collision, just ground level.
	if (p_vz < PLAYER_FALL_VY_MAX) p_vz += PLAYER_G; else p_vz = PLAYER_FALL_VY_MAX;
#else
	if (do_gravity) {
		// Gravity
		if (p_vy < PLAYER_FALL_VY_MAX) p_vy += PLAYER_G; else p_vy = PLAYER_FALL_VY_MAX;
	}

#ifdef PLAYER_CUMULATIVE_JUMP
	if (!p_jmp_on)
#endif
		if (p_gotten) p_vy = 0;
#endif
