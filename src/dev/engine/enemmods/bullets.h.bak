// Collide with bullets

#ifdef FIRE_MIN_KILLABLE
	if (_en_t >= FIRE_MIN_KILLABLE) 
#endif
#ifdef BULLETS_DONT_COLLIDE_PLATFORMS
	if (gpt != 8)
#endif
{
	for (gpjt = 0; gpjt < MAX_BULLETS; gpjt ++) {
		if (bullets_estado [gpjt] == 1) {
			cx1 = bullets_x [gpjt] + 3; cy1 = bullets_y [gpjt] + 3;
			cx2 = _en_x; cy2 = _en_y;
			if (collide_pixel ()) {
				bullets_estado [gpjt] = 0;						
				enems_kill (PLAYER_BULLETS_STRENGTH);
				goto enems_loop_continue;
			}
		}
	}
}
