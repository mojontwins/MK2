#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	if ( ! ((gpit & sp_LEFT) == 0 || (gpit & sp_RIGHT) == 0) && p_z == 0) 
#else
	if ( ! ((gpit & sp_LEFT) == 0 || (gpit & sp_RIGHT) == 0)) 
#endif
	{
#ifdef PLAYER_GENITAL
		p_facing_h = 0xff;
#endif
		if (p_vx > 0) {
			p_vx -= RXVAL; if (p_vx < 0) p_vx = 0;
		} else if (p_vx < 0) {
			p_vx += RXVAL; if (p_vx > 0) p_vx = 0;
		}
	}

	if ((gpit & sp_LEFT) == 0) {
#ifdef PLAYER_GENITAL
		p_thrust = 1;
		p_facing_h = FACING_LEFT;
#endif
		if (p_vx > -PLAYER_VX_MAX) {
#ifndef PLAYER_GENITAL
			p_facing = 0;
#endif
			p_vx -= AXVAL;
		}
	}

	if ((gpit & sp_RIGHT) == 0) {
#ifdef PLAYER_GENITAL
		p_thrust = 1;
		p_facing_h = FACING_RIGHT;
#endif
		if (p_vx < PLAYER_VX_MAX) {
			p_vx += AXVAL;
#ifndef PLAYER_GENITAL
			p_facing = 1;
#endif
		}
	}
