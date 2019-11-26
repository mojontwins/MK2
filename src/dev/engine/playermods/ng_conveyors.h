// New Genital Conveyors
	if (possee) {
		if (at1 & 32) {
			p_gotten = 1;
			// Read behaviour bits
			switch ((at1 >> 1) & 3) {
				case 0:	// Up
					ptgmy = -PLAYER_VX_MAX;
					break;
				case 1: // Down
					ptgmy = PLAYER_VX_MAX;
					break;
				case 2: // Left
					ptgmx = -PLAYER_VX_MAX;
					break;
				case 3: // Right
					ptgmx = PLAYER_VX_MAX;
					break;
			}
		}
	}
