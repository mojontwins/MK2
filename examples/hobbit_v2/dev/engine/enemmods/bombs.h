			if (bomb_state == 2) {

				if (gpen_cx + 15 >= bomb_px && gpen_cx <= bomb_px + 47 &&
					gpen_cy + 15 >= bomb_py && gpen_cy <= bomb_py + 47) {
					enemy_kill (PLAYER_BOMBS_STRENGTH);
					continue;
				}
			}
