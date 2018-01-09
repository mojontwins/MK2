// Bombs.h

#ifdef PLAYER_SIMPLE_BOMBS
	if (BUTTON_FIRE && !p_disparando
#ifdef PLAYER_BOMBS_INV
		&& items [flags [FLAG_SLOT_SELECTED]] == PLAYER_BOMBS_INV
#endif
#ifdef SCRIPTING_KEY_FIRE
		&& invalidate_fire == 0
#endif
	) {
		p_disparando = 1;
		if (0 == bomb_state && possee) {
			bomb_set ();
			_AY_PL_SND (9);
#ifdef PLAYER_BOMBS_INV
			items [flags [FLAG_SLOT_SELECTED]] = 0;
			display_items ();
#endif		
		}
	}
#endif
