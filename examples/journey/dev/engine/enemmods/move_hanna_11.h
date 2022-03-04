
// Hanna monsters type 11.
// They will free-roam. They will switch to "pursue" if you are close and visible.
// "Visible" means (Lights are on OR Torch is on) AND (You are on a non-hiding (type 2) tile).

_en_cx = _en_x; _en_cy = _en_y;

switch (en_an_state [enit]) {
	case 0:
		// Free roaming.
		if (0 == en_an_count [enit] --) {
			gpjt = rand () & 8;
			_en_mx = gpjt > 1 ? 0 : gpjt ? -1 : 1;
			_en_my = (gpjt < 2 || gpjt > 3) ? 0 : gpjt == 2 ? 1 : -1;
			en_an_count [enit] == (2 + (rand () & 7)) << 4;
		}

		// Does the monster see you?
		if (i_can_see_you ()) {
			en_an_state [enit] = 1;
		}
		break;
	case 1:
		// Pursuing.
		_en_mx = (signed char) (addsign (((gpx >> 2) << 2) - gpen_x, 2);
		_en_my = (signed char) (addsign (((gpy >> 2) << 2) - gpen_y, 2);
		if (0 == i_can_see_you ()) {
			en_an_state [enit] = 0;
		}
		break;
	case 2:
		// Stunned
		if (0 == en_an_count [enit] --) {
			en_an_state [enit] = 0;
		}
}

// move / collide?

_en_x += _en_mx;
#ifdef WALLS_STOP_ENEMIES
	if (mons_col_sc_x ()) _en_x = _en_cx;
#endif

_en_y += _en_my;
#ifdef WALLS_STOP_ENEMIES
	if (mons_col_sc_x ()) _en_y = _en_cy;
#endif
