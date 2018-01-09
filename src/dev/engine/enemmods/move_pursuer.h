				// Move pursuers

				switch (en_an_alive [gpit]) {
					case 0:
						if (en_an_dead_row [gpit] == 0) {
							baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
							baddies [enoffsmasi].y = baddies [enoffsmasi].y1;
							en_an_alive [gpit] = 1;
							en_an_rawv [gpit] = 1 << (rand () % 5);
							if (en_an_rawv [gpit] > 4) en_an_rawv [gpit] = 2;
							en_an_dead_row [gpit] = 11 + (rand () & 7);
#if defined (PLAYER_KILLS_ENEMIES) || defined (PLAYER_CAN_FIRE)
							baddies [enoffsmasi].life = ENEMIES_LIFE_GAUGE;
#endif
						} else {
							en_an_dead_row [gpit] --;
						}
						break;
					case 1:
						if (en_an_dead_row [gpit] == 0) {
#ifdef TYPE_7_FIXED_SPRITE
							en_an_base_frame [gpit] = (TYPE_7_FIXED_SPRITE - 1) << 1;
#else
							en_an_base_frame [gpit] = (rand () & 3) << 1;
#endif
							en_an_alive [gpit] = 2;
						} else {
							en_an_dead_row [gpit] --;
							en_an_n_f [gpit] = sprite_17_a;
						}
						break;
					case 2:
						active = killable = animate = 1;
						if (p_state == EST_NORMAL) {
							baddies [enoffsmasi].mx = (signed char) (addsign (((gpx >> 2) << 2) - gpen_x, en_an_rawv [gpit]));
							baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
							gpen_xx = baddies [enoffsmasi].x >> 4;
							gpen_yy = baddies [enoffsmasi].y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_x ()) baddies [enoffsmasi].x = gpen_x;
#endif
							baddies [enoffsmasi].my = (signed char) (addsign (((gpy >> 2) << 2) - gpen_y, en_an_rawv [gpit]));
							baddies [enoffsmasi].y += baddies [enoffsmasi].my;
							gpen_xx = baddies [enoffsmasi].x >> 4;
							gpen_yy = baddies [enoffsmasi].y >> 4;
#ifdef WALLS_STOP_ENEMIES
							if (mons_col_sc_y ()) baddies [enoffsmasi].y = gpen_y;
#endif
						}
						gpen_cx = baddies [enoffsmasi].x;
						gpen_cy = baddies [enoffsmasi].y;
				}
