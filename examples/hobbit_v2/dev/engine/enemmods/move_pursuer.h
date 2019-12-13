				// Move pursuers

				switch (en_an_alive [enit]) {
					case 0:
						if (en_an_dead_row [enit] == 0) {
							_en_x = _en_x1;
							_en_y = _en_y1;
							en_an_alive [enit] = 1;
							en_an_rawv [enit] = 1 << (rand () % 5);
							if (en_an_rawv [enit] > 4) en_an_rawv [enit] = 2;
							en_an_dead_row [enit] = 11 + (rand () & 7);
#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
							_en_life = ENEMS_LIFE_GAUGE;
#endif
						} else {
							en_an_dead_row [enit] --;
						}
						break;
					case 1:
						if (en_an_dead_row [enit] == 0) {
#ifdef TYPE_7_FIXED_SPRITE
							en_an_base_frame [enit] = (TYPE_7_FIXED_SPRITE - 1) << 1;
#else
							en_an_base_frame [enit] = (rand () & 3) << 1;
#endif
							en_an_alive [enit] = 2;
						} else {
							en_an_dead_row [enit] --;
							en_an_n_f [enit] = sprite_17_a;
						}
						break;
					case 2:
						active = killable = animate = 1;
						if (p_state == EST_NORMAL) {
							_en_mx = (signed char) (addsign (((gpx >> 2) << 2) - gpen_x, en_an_rawv [enit]));
							_en_x += _en_mx;
							gpen_xx = _en_x >> 4;
							gpen_yy = _en_y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_x ()) _en_x = gpen_x;
#endif
							_en_my = (signed char) (addsign (((gpy >> 2) << 2) - gpen_y, en_an_rawv [enit]));
							_en_y += _en_my;
							gpen_xx = _en_x >> 4;
							gpen_yy = _en_y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_y ()) _en_y = gpen_y;
#endif
						}
						gpen_cx = _en_x;
						gpen_cy = _en_y;
				}
