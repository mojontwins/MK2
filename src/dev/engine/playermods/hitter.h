// Hitter.h

#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	if (BUTTON_FIRE && !p_disparando
#ifdef PLAYER_HITTER_INV
		&& items [flags [FLAG_SLOT_SELECTED]] == PLAYER_HITTER_INV
#endif
#ifdef SCRIPTING_KEY_FIRE
		&& invalidate_fire == 0
#endif
	) {
		p_disparando = 1;
#ifdef PLAYER_HAZ_SWORD		
		p_up = ((gpit & sp_UP) == 0);
#endif		
		if (0 == hitter_on) {
			hitter_hit = 0;
			hitter_on = 1;
			hitter_frame = 0;
			p_hitting = 1;
#ifdef MODE_128K
			_AY_PL_SND (SFX_HITTER_HIT);
#else
			beep_fx (SFX_HITTER_HIT);
#endif
		}
	}
#endif	
