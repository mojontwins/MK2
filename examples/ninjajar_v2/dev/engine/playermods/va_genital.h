#ifdef PLAYER_HAS_JUMP
	rda = ((pad0 & sp_UP) == 0 || (pad0 & sp_DOWN) == 0);

	if ( 
		!rda  
		#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
			&& p_z == 0
		#endif
		#if defined PLAYER_DIZZY
			&& (((p_state & EST_DIZZY) == 0) || p_vx == 0)
		#endif
	) {
		p_facing_v = 0xff;
		if (p_vy > 0) {
			p_vy -= RXVAL; if (p_vy < 0) p_vy = 0;
		} else if (p_vy < 0) {
			p_vy += RXVAL; if (p_vy > 0) p_vy = 0;
		}
	}
	// Dizzy
	#ifdef PLAYER_DIZZY
		if (rda && (p_state & EST_DIZZY)) { 
			p_vx += PLAYER_DIZZ_EXPR;
		}
	#endif 

	if ((pad0 & sp_UP) == 0) {
		p_facing_v = FACING_UP;
		p_thrust = 1;
		if (p_vy > -PLAYER_VX_MAX) p_vy -= AXVAL;
	}

	if ((pad0 & sp_DOWN) == 0) {
		p_facing_v = FACING_DOWN;
		p_thrust = 1;
		if (p_vy < PLAYER_VX_MAX) p_vy += AXVAL;
	}
#endif
	