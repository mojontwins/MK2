// Fire.h
#ifdef PLAYER_CAN_FIRE
	if (BUTTON_FIRE && !p_disparando
#ifdef FIRE_TO_PUSH
		&& !pushed_any
#endif
#ifdef PLAYER_CAN_FIRE_INV
		&& items [flags [FLAG_SLOT_SELECTED]] == PLAYER_CAN_FIRE_INV
#endif
#ifdef SCRIPTING_KEY_FIRE
		&& invalidate_fire == 0
#endif

	) {

		p_disparando = 1;
		fire_bullet ();
	}
#endif	
