	rda = (gpit & sp_LEFT) == 0 || (gpit & sp_RIGHT) == 0;

	if (
		!rda 
		#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
			&& p_z == 0 
		#endif
		#if defined PLAYER_DIZZY
			&& (((p_state & EST_DIZZY) == 0) || p_vy == 0)
		#endif
	) {
		#ifdef PLAYER_GENITAL
			p_facing_h = 0xff;
		#endif
		if (p_vx > 0) {
			p_vx -= RXVAL; if (p_vx < 0) p_vx = 0;
		} else if (p_vx < 0) {
			p_vx += RXVAL; if (p_vx > 0) p_vx = 0;
		}
	}
	// Dizzy
	#ifdef PLAYER_DIZZY
		if (rda && (p_state & EST_DIZZY)) { 
			p_vy += PLAYER_DIZZ_EXPR;
		}
	#endif 


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
