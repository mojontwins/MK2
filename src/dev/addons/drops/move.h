// move drops

/* Drops are as follows:
	x1, y1 = initial position
	my = drop speed
	x, y = position
	mx = state: 0 fall, 1, 2, 3 hit
	x2 = subframe counter (hit)
*/

	if (_en_mx) {
		en_an_n_f [gpit] = drop_sprites + (_en_mx << 7) + (_en_mx << 4);
		_en_x2 = (_en_x2 + 1) & 3;
		if (0 == _en_x2) {
			_en_mx = (_en_mx + 1) & 3;
			if (0 == _en_mx);
		}
	} else {
		if (0 == _en_x2) {
			_en_y = _en_y1;
			_en_x2 = 1;
		}
		en_an_n_f [gpit] = drop_sprites;
		_en_y += _en_my;
		if ((_en_y & 15) == 0) {
			cx1 = _en_x >> 4;
			cy1 = (_en_y + 15) >> 4;
			if (attr () & 12) {
				_en_mx = 1;
				_en_x2 = 0;
				_AY_PL_SND (16);
			}
		}
	}
	
	active = 1;
