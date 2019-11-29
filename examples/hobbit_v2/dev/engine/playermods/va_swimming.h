#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_SWIM) {
#endif
		p_gotten = 1;
		if ( ! ((gpit & sp_DOWN) == 0 || (gpit & sp_UP) == 0)) {
			p_vy -= PLAYER_ASWIM >> 1;
			if (p_vy < PLAYER_MAX_VSWIM >> 1) p_vy = -(PLAYER_MAX_VSWIM >> 1);
		}
	
		if ((gpit & sp_DOWN) == 0) {
			if (p_vy < PLAYER_MAX_VSWIM) p_vy += PLAYER_ASWIM;
		}

		//if ((gpit & sp_UP) == 0) {	
		//CUSTOM!
		if ((gpit & sp_UP) == 0 || sp_KeyPressed (key_jump)) {			
			if (p_vy > -PLAYER_MAX_VSWIM) p_vy -= PLAYER_ASWIM;
		}
#ifdef SWITCHABLE_ENGINES
	}
#endif
