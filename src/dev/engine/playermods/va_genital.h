#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	if ( ! ((gpit & sp_UP) == 0 || (gpit & sp_DOWN) == 0) && p_z == 0) 
#else
	if ( ! ((gpit & sp_UP) == 0 || (gpit & sp_DOWN) == 0)) 
#endif
	{
		p_facing_v = 0xff;
		if (p_vy > 0) {
			p_vy -= RXVAL; if (p_vy < 0) p_vy = 0;
		} else if (p_vy < 0) {
			p_vy += RXVAL; if (p_vy > 0) p_vy = 0;
		}
	}

	if ((gpit & sp_UP) == 0) {
		p_facing_v = FACING_UP;
		p_thrust = 1;
		if (p_vy > -PLAYER_VX_MAX) p_vy -= AXVAL;
	}

	if ((gpit & sp_DOWN) == 0) {
		p_facing_v = FACING_DOWN;
		p_thrust = 1;
		if (p_vy < PLAYER_VX_MAX) p_vy += AXVAL;
	}
	