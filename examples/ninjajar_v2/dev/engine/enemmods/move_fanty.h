// Move Fanty
active = killable = animate = 1;

#ifdef FANTIES_SIGHT_DISTANCE
	// Complex fanties

	gpen_cx = en_an_x [enit] >> 6;
	gpen_cy = en_an_y [enit] >> 6;
	switch (en_an_state [enit]) {
		case FANTIES_IDLE:
#ifdef FANTIES_NUMB_ON_FLAG
			if (flags [FANTIES_NUMB_ON_FLAG])
#endif
				if (distance (gpx, gpy, gpen_cx, gpen_cy) <= FANTIES_SIGHT_DISTANCE)
					en_an_state [enit] = FANTIES_PURSUING;
			break;
		case FANTIES_PURSUING:
#ifdef FANTIES_NUMB_ON_FLAG
			if (0 == flags [FANTIES_NUMB_ON_FLAG]) en_an_state [enit] = FANTIES_RETREATING;
#endif				
			if (distance (gpx, gpy, gpen_cx, gpen_cy) > FANTIES_SIGHT_DISTANCE) {
				en_an_state [enit] = FANTIES_RETREATING;
			} else {				
				en_an_vx [enit] = limit (
					en_an_vx [enit] + addsign (p_x - en_an_x [enit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
				en_an_vy [enit] = limit (
					en_an_vy [enit] + addsign (p_y - en_an_y [enit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
				en_an_x [enit] = limit (en_an_x [enit] + en_an_vx [enit], 0, 14336);
				en_an_y [enit] = limit (en_an_y [enit] + en_an_vy [enit], 0, 9216);
			}
			break;
		case FANTIES_RETREATING:
			en_an_x [enit] += addsign (baddies [enoffsmasi].x - gpen_cx, 64);
			en_an_y [enit] += addsign (baddies [enoffsmasi].y - gpen_cy, 64);

#ifdef FANTIES_NUMB_ON_FLAG
			if (flags [FANTIES_NUMB_ON_FLAG])
#endif
				if (distance (gpx, gpy, gpen_cx, gpen_cy) <= FANTIES_SIGHT_DISTANCE)
					en_an_state [enit] = FANTIES_PURSUING;
			break;
	}
	gpen_cx = en_an_x [enit] >> 6;
	gpen_cy = en_an_y [enit] >> 6;
	if (en_an_state [enit] == FANTIES_RETREATING &&
		gpen_cx == baddies [enoffsmasi].x &&
		gpen_cy == baddies [enoffsmasi].y
		)
		en_an_state [enit] = FANTIES_IDLE;
#else
	// Plain fanties
	en_an_vx [enit] = limit (
		en_an_vx [enit] + addsign (p_x - en_an_x [enit], FANTIES_A),
		-FANTIES_MAX_V, FANTIES_MAX_V);
	en_an_vy [enit] = limit (
		en_an_vy [enit] + addsign (p_y - en_an_y [enit], FANTIES_A),
		-FANTIES_MAX_V, FANTIES_MAX_V);

#ifdef FANTIES_NUMB_ON_FLAG
	if (flags [FANTIES_NUMB_ON_FLAG])
#endif				
	{
		en_an_x [enit] = limit (en_an_x [enit] + en_an_vx [enit], 0, 14336);
		en_an_y [enit] = limit (en_an_y [enit] + en_an_vy [enit], 0, 9216);
	}
	
	gpen_cx = en_an_x [enit] >> 6;
	gpen_cy = en_an_y [enit] >> 6;
#endif
