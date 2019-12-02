
// Hanna monsters type 11.
// They will free-roam. They will switch to "pursue" if you are close and visible.
// "Visible" means (Lights are on OR Torch is on) AND (You are on a non-hiding (type 2) tile).

				switch (en_an_state [gpit]) {
					case 0:
						// Free roaming.
						if (0 == en_an_count [gpit] --) {
							gpjt = rand () & 8;
							baddies [enoffsmasi].mx = gpjt > 1 ? 0 : gpjt ? -1 : 1;
							baddies [enoffsmasi].my = (gpjt < 2 || gpjt > 3) ? 0 : gpjt == 2 ? 1 : -1;
							en_an_count [gpit] == (2 + (rand () & 7)) << 4;
						}

						// Does the monster see you?
						if (i_can_see_you ()) {
							en_an_state [gpit] = 1;
						}
						break;
					case 1:
						// Pursuing.
						baddies [enoffsmasi].mx = (signed char) (addsign (((gpx >> 2) << 2) - gpen_x, 2);
						baddies [enoffsmasi].my = (signed char) (addsign (((gpy >> 2) << 2) - gpen_y, 2);
						if (0 == i_can_see_you ()) {
							en_an_state [gpit] = 0;
						}
						break;
					case 2:
						// Stunned
						if (0 == en_an_count [gpit] --) {
							en_an_state [gpit] = 0;
						}
				}

				// move / collide?

				baddies [enoffsmasi].x += baddies [enoffsmasi].mx;
#ifdef WALLS_STOP_ENEMIES
				if (mons_col_sc_x ()) baddies [enoffsmasi].x = gpen_x;
#endif

				baddies [enoffsmasi].y += baddies [enoffsmasi].my;
#ifdef WALLS_STOP_ENEMIES
				if (mons_col_sc_x ()) baddies [enoffsmasi].y = gpen_x;
#endif

				gpen_cx = baddies [enoffsmasi].x;
				gpen_cy = baddies [enoffsmasi].y;
