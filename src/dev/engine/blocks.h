// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// blocks.h
// Block processing helper

#ifdef FIRE_TO_PUSH
unsigned char pushed_any;
#endif

#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
void process_tile (unsigned char x0, unsigned char y0, signed char x1, signed char y1) {
#ifdef PLAYER_PUSH_BOXES
#ifdef FIRE_TO_PUSH
	gpit = (joyfunc) (&keys);
#ifdef USE_TWO_BUTTONS
	if ((gpit & sp_FIRE) == 0 || sp_KeyPressed (key_fire)) {
#else
	if ((gpit & sp_FIRE) == 0) {
#endif
#endif
		if (qtile (x0, y0) == 14 && attr (x1, y1) == 0 && x1 >= 0 && x1 < 15 && y1 >= 0 && y1 < 10) {
#if defined (ACTIVATE_SCRIPTING) && defined (ENABLE_PUSHED_SCRIPTING)
			flags [MOVED_TILE_FLAG] = map_buff [15 * y1 + x1];
			flags [MOVED_X_FLAG] = x1;
			flags [MOVED_Y_FLAG] = y1;
#endif
			update_tile (x1, y1, 10, 14);
			update_tile (x0, y0, 0, 0);
			// Sonido
#ifdef MODE_128K
			_AY_PL_SND (SFX_PUSH_BOX);
#else
			beep_fx (SFX_PUSH_BOX);
#endif
#ifdef FIRE_TO_PUSH
			// Para no disparar...
			pushed_any = 1;
#endif
#if defined (ACTIVATE_SCRIPTING) && defined (ENABLE_PUSHED_SCRIPTING) && defined (PUSHING_ACTION)
			// Call scripting
			just_pushed = 1;
			run_fire_script ();
			just_pushed = 0;
#endif
		}
#ifdef FIRE_TO_PUSH
	}
#endif
#endif
#ifndef DEACTIVATE_KEYS
	if (qtile (x0, y0) == 15 && p_keys) {
		update_tile (x0, y0, 0, 0);
#ifdef COMPRESSED_LEVELS
#ifdef MODE_128K
		for (gpit = 0; gpit < MAX_bolts; gpit ++) {
#else
		for (gpit = 0; gpit < n_bolts; gpit ++) {
#endif
#else
		for (gpit = 0; gpit < MAX_bolts; gpit ++) {
#endif
			if (bolts [gpit].x == x0 && bolts [gpit].y == y0 && bolts [gpit].np == n_pant) {
				bolts [gpit].st = 0;
				break;
			}
		}
		p_keys --;
#ifdef MODE_128K
		_AY_PL_SND (SFX_LOCK);
#else
		beep_fx (SFX_LOCK);
#endif
	}
#endif
}
#endif
