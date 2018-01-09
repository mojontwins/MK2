				// Random Respawn (Zombie Calavera Prologue)
				
				active = 1;
				gpen_cx = en_an_x [gpit] >> 6;
				gpen_cy = en_an_y [gpit] >> 6;
				if (player_hidden ()) {
					en_an_vx [gpit] = limit (
						en_an_vx [gpit] + addsign (en_an_x [gpit] - p_x, FANTIES_A >> 1),
						-FANTIES_MAX_V, FANTIES_MAX_V);
					en_an_vy [gpit] = limit (
						en_an_vy [gpit] + addsign (en_an_y [gpit] - p_y, FANTIES_A >> 1),
						-FANTIES_MAX_V, FANTIES_MAX_V);
				} else if ((rand () & 7) > 1) {
					en_an_vx [gpit] = limit (
						en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTIES_A),
						-FANTIES_MAX_V, FANTIES_MAX_V);
					en_an_vy [gpit] = limit (
						en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTIES_A),
						-FANTIES_MAX_V, FANTIES_MAX_V);
				}

				en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
				en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
