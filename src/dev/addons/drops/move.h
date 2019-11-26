// move drops

/* Drops are as follows:
	x1, y1 = initial position
	my = drop speed
	x, y = position
	mx = state: 0 fall, 1, 2, 3 hit
	x2 = subframe counter (hit)
*/

				if (baddies [enoffsmasi].mx) {
					en_an_n_f [gpit] = drop_sprites + (baddies [enoffsmasi].mx << 7) + (baddies [enoffsmasi].mx << 4);
					baddies [enoffsmasi].x2 = (baddies [enoffsmasi].x2 + 1) & 3;
					if (0 == baddies [enoffsmasi].x2) {
						baddies [enoffsmasi].mx = (baddies [enoffsmasi].mx + 1) & 3;
						if (0 == baddies [enoffsmasi].mx);
					}
				} else {
					if (0 == baddies [enoffsmasi].x2) {
						baddies [enoffsmasi].y = baddies [enoffsmasi].y1;
						baddies [enoffsmasi].x2 = 1;
					}
					en_an_n_f [gpit] = drop_sprites;
					baddies [enoffsmasi].y += baddies [enoffsmasi].my;
					if ((baddies [enoffsmasi].y & 15) == 0) {
						cx1 = baddies [enoffsmasi].x >> 4;
						cy1 = (baddies [enoffsmasi].y + 15) >> 4;
						if (attr () & 12) {
							baddies [enoffsmasi].mx = 1;
							baddies [enoffsmasi].x2 = 0;
							_AY_PL_SND (16);
						}
					}
				}
				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;

				active = 1;
