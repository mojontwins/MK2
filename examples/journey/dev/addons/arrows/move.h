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

				baddies [enoffsmasi].y2 = 0;
				if (baddies [enoffsmasi].my) {
					baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
					en_an_n_f [gpit] = arrow_sprites + (baddies [enoffsmasi].mx < 0 ? 0 : 144);
					if (baddies [enoffsmasi].x == baddies [enoffsmasi].x2) baddies [enoffsmasi].my = 0;
				} else {
					en_an_n_f [gpit] = sprite_18_a;
					if (0 == enemy_shoots || (addons_between (gpy, baddies [enoffsmasi].y1, baddies [enoffsmasi].y1, 15, 15) && addons_between (gpx, baddies [enoffsmasi].x1, baddies [enoffsmasi].x2, 15, 31))){
						baddies [enoffsmasi].y2 = 1;
					}
					
				}
				if (baddies [enoffsmasi].y2) {
					baddies [enoffsmasi].my = 1;
					baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
					_AY_PL_SND (7);
				}

				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;

				active = 1;
