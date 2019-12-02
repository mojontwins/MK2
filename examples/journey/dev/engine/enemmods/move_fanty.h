// Move Fanty
#ifdef FANTIES_SIGHT_DISTANCE
	// Complex fanties
	active = killable = animate = 1;
	gpen_cx = en_an_x [gpit] >> 6;
	gpen_cy = en_an_y [gpit] >> 6;
	switch (en_an_state [gpit]) {
		case FANTIES_IDLE:
#ifdef FANTIES_NUMB_ON_FLAG
			if (flags [FANTIES_NUMB_ON_FLAG])
#endif
				if (distance (gpx, gpy, gpen_cx, gpen_cy) <= FANTIES_SIGHT_DISTANCE)
					en_an_state [gpit] = FANTIES_PURSUING;
			break;
		case FANTIES_PURSUING:
#ifdef FANTIES_NUMB_ON_FLAG
			if (0 == flags [FANTIES_NUMB_ON_FLAG]) en_an_state [gpit] = FANTIES_RETREATING;
#endif				
			if (distance (gpx, gpy, gpen_cx, gpen_cy) > FANTIES_SIGHT_DISTANCE) {
				en_an_state [gpit] = FANTIES_RETREATING;
			} else {				
				en_an_vx [gpit] = limit (
					en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
				en_an_vy [gpit] = limit (
					en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
				en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
				en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
			}
			break;
		case FANTIES_RETREATING:
			en_an_x [gpit] += addsign (baddies [enoffsmasi].x - gpen_cx, 64);
			en_an_y [gpit] += addsign (baddies [enoffsmasi].y - gpen_cy, 64);

#ifdef FANTIES_NUMB_ON_FLAG
			if (flags [FANTIES_NUMB_ON_FLAG])
#endif
				if (distance (gpx, gpy, gpen_cx, gpen_cy) <= FANTIES_SIGHT_DISTANCE)
					en_an_state [gpit] = FANTIES_PURSUING;
			break;
	}
	gpen_cx = en_an_x [gpit] >> 6;
	gpen_cy = en_an_y [gpit] >> 6;
	if (en_an_state [gpit] == FANTIES_RETREATING &&
		gpen_cx == baddies [enoffsmasi].x &&
		gpen_cy == baddies [enoffsmasi].y
		)
		en_an_state [gpit] = FANTIES_IDLE;
#else
	// Plain fanties
	en_an_vx [gpit] = limit (
		en_an_vx [gpit] + addsign (p_x - en_an_x [gpit], FANTIES_A),
		-FANTIES_MAX_V, FANTIES_MAX_V);
	en_an_vy [gpit] = limit (
		en_an_vy [gpit] + addsign (p_y - en_an_y [gpit], FANTIES_A),
		-FANTIES_MAX_V, FANTIES_MAX_V);

#ifdef FANTIES_NUMB_ON_FLAG
	if (flags [FANTIES_NUMB_ON_FLAG])
#endif				
	{
		en_an_x [gpit] = limit (en_an_x [gpit] + en_an_vx [gpit], 0, 14336);
		en_an_y [gpit] = limit (en_an_y [gpit] + en_an_vy [gpit], 0, 9216);
	}
	
	gpen_cx = en_an_x [gpit] >> 6;
	gpen_cy = en_an_y [gpit] >> 6;
#endif
