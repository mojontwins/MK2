#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_SWIM)
#endif
{
	p_gotten = 1;
	if ( ! ((pad0 & sp_DOWN) == 0 || (pad0 & sp_UP) == 0)) {
		p_vy -= PLAYER_ASWIM >> 1;
		if (p_vy < PLAYER_MAX_VSWIM >> 1) p_vy = -(PLAYER_MAX_VSWIM >> 1);
	}

	if ((pad0 & sp_DOWN) == 0) {
		if (p_vy < PLAYER_MAX_VSWIM) p_vy += PLAYER_ASWIM;
	}

	//if ((pad0 & sp_UP) == 0) {	
	//CUSTOM!
	if ((pad0 & sp_UP) == 0 || BUTTON_JUMP) {			
		if (p_vy > -PLAYER_MAX_VSWIM) p_vy -= PLAYER_ASWIM;
	}
}
