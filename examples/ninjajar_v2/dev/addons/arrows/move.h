// move arrows

/* Drops are as follows:
	baddies [enoffsmasi].
	x1/x2, y1 = initial position
	mx = Arrow speed
	x, y = position
	my = state (0: off, 1: on)
	y2 = activate me!

	enemy_shoots = 1: flag is only activated when player collides tile row
*/

				_en_y2 = 0;
				if (_en_my) {
					_en_x += _en_mx;
					en_an_n_f [gpit] = arrow_sprites + (_en_mx < 0 ? 0 : 144);
					if (_en_x == _en_x2) _en_my = 0;
				} else {
					en_an_n_f [gpit] = sprite_18_a;
					if (0 == enemy_shoots || (addons_between (gpy, _en_y1, _en_y1, 15, 15) && addons_between (gpx, _en_x1, _en_x2, 15, 31))){
						_en_y2 = 1;
					}
					
				}
				if (_en_y2) {
					_en_my = 1;
					_en_x = _en_x1;
					_AY_PL_SND (7);
				}
				
				active = 1;
