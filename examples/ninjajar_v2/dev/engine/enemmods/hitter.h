// Collide with hitter

if (hitter_on && killable && hitter_hit == 0) {
	#if defined (PLAYER_CAN_PUNCH)
		cx1 = hitter_x + (p_facing ? 6 : 1); cy1 = hitter_y + 3;
		cx2 = _en_x; cy2 = _en_y;
		if (
			hitter_frame <= 3 && 
			collide_pixel ()
		) 
	#elif defined (PLAYER_HAZ_SWORD)
		if (p_up) {
			cx1 = hitter_x + 4; cy1 = hitter_y;
		} else {
			cx1 = hitter_x + (p_facing ? 6 : 1); cy1 = hitter_y + 3;
		}
		cx2 = _en_x; cy2 = _en_y;
		if (
			hitter_frame > 2 && 
			hitter_frame < 7 &&
			collide_pixel ()
		) 
	#elif defined (PLAYER_HAZ_WHIP)
		cx1 = hitter_x + (p_facing ? 14 : 1); cy1 = hitter_y + 3;
		cx2 = _en_x; cy2 = _en_y;
		if (
			hitter_frame < 5 &&
			collide_pixel ()
		) 
	#endif
	{
		hitter_hit = 1;
		enems_kill (PLAYER_HITTER_STRENGTH);
		goto enems_loop_continue;
	}
}
