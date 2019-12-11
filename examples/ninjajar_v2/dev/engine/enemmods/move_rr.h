				// Random Respawn (Zombie Calavera Prologue)
				
				active = 1;
				gpen_cx = en_an_x [enit] >> 6;
				gpen_cy = en_an_y [enit] >> 6;
				if (player_hidden ()) {
					en_an_vx [enit] = limit (
						en_an_vx [enit] + addsign (en_an_x [enit] - p_x, FANTIES_A >> 1),
						-FANTIES_MAX_V, FANTIES_MAX_V);
					en_an_vy [enit] = limit (
						en_an_vy [enit] + addsign (en_an_y [enit] - p_y, FANTIES_A >> 1),
						-FANTIES_MAX_V, FANTIES_MAX_V);
				} else if ((rand () & 7) > 1) {
					en_an_vx [enit] = limit (
						en_an_vx [enit] + addsign (p_x - en_an_x [enit], FANTIES_A),
						-FANTIES_MAX_V, FANTIES_MAX_V);
					en_an_vy [enit] = limit (
						en_an_vy [enit] + addsign (p_y - en_an_y [enit], FANTIES_A),
						-FANTIES_MAX_V, FANTIES_MAX_V);
				}

				en_an_x [enit] = limit (en_an_x [enit] + en_an_vx [enit], 0, 14336);
				en_an_y [enit] = limit (en_an_y [enit] + en_an_vy [enit], 0, 9216);
