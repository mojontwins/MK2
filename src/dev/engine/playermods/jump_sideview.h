#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_JUMP) {
#endif

#ifdef PLAYER_CUMULATIVE_JUMP
		if (BUTTON_JUMP && (possee || p_gotten)) {
			p_vy = -p_vy - PLAYER_JMP_VY_INITIAL;
#ifdef PLAYER_VARIABLE_JUMP
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#else
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#endif
#else
		if (BUTTON_JUMP && p_jmp_on == 0 && (possee || p_gotten)) {
#endif
			p_jmp_on = 1;
			p_jmp_ct = 0;
#ifdef MODE_128K
			_AY_PL_SND (SFX_JUMP);
#else
			beep_fx (SFX_JUMP);
#endif
		}

#ifndef PLAYER_CUMULATIVE_JUMP
		if (BUTTON_JUMP && p_jmp_on) {
			p_vy -= (PLAYER_JMP_VY_INITIAL + PLAYER_JMP_VY_INCR - (p_jmp_ct>>1));
#ifdef PLAYER_VARIABLE_JUMP
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#else
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#endif
			p_jmp_ct ++;
			if (p_jmp_ct == 8)
				p_jmp_on = 0;
		}
#endif
	
		if (!BUTTON_JUMP) p_jmp_on = 0;
#ifdef SWITCHABLE_ENGINES
	}
#endif
#endif

#ifdef PLAYER_BOOTEE
#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_BOOT) {
#endif
		// Bootee engine
		if ( p_jmp_on == 0 && (possee || p_gotten) ) {
			p_jmp_on = 1;
			p_jmp_ct = 0;
#ifdef DIE_AND_RESPAWN
			p_safe_pant = n_pant;
			p_safe_x = gpxx;
			p_safe_y = gpyy;
#endif
#ifdef MODE_128K
			_AY_PL_SND (SFX_JUMP);
#else
			beep_fx (SFX_JUMP);
#endif
		}
	
		if (p_jmp_on ) {
			p_vy -= (PLAYER_JMP_VY_INITIAL + PLAYER_JMP_VY_INCR - (p_jmp_ct>>1));
#ifdef PLAYER_VARIABLE_JUMP
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#else
			if (p_vy < -PLAYER_JMP_VY_MAX) p_vy = -PLAYER_JMP_VY_MAX;
#endif
			p_jmp_ct ++;
			if (p_jmp_ct == 8)
				p_jmp_on = 0;
		}
#ifdef SWITCHABLE_ENGINES
	}
#endif
