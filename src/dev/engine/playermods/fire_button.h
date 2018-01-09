#if defined (PLAYER_CAN_FIRE) || defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
	if (!BUTTON_FIRE) {
		p_disparando = 0;
#ifdef SCRIPTING_KEY_FIRE
		invalidate_fire = 0;
#endif
	}
#endif
