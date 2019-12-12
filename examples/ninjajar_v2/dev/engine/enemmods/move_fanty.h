// Move Fanty
active = killable = animate = 1;

#ifdef FANTIES_SIGHT_DISTANCE
	// Complex fanties

	switch (en_an_state [enit]) {
		case FANTIES_IDLE:
			#ifdef FANTIES_NUMB_ON_FLAG
				if (flags [FANTIES_NUMB_ON_FLAG])
			#endif
			
			if (distance (gpx, gpy, _en_x, _en_y) <= FANTIES_SIGHT_DISTANCE)
				en_an_state [enit] = FANTIES_PURSUING;
			
			break;
			
		case FANTIES_PURSUING:
			#ifdef FANTIES_NUMB_ON_FLAG
				if (0 == flags [FANTIES_NUMB_ON_FLAG]) en_an_state [enit] = FANTIES_RETREATING;
			#endif				
			
			if (distance (gpx, gpy, _en_x, _en_y) > FANTIES_SIGHT_DISTANCE) {
				en_an_state [enit] = FANTIES_RETREATING;
			} else {				
				en_an_vx [enit] = limit (
					en_an_vx [enit] + addsign (p_x - en_an_x [enit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
				en_an_vy [enit] = limit (
					en_an_vy [enit] + addsign (p_y - en_an_y [enit], FANTIES_A),
					-FANTIES_MAX_V, FANTIES_MAX_V);
			
				en_an_x [enit] = limit (en_an_x [enit] + en_an_vx [enit], 0, 224 << FIXBITS);
				en_an_y [enit] = limit (en_an_y [enit] + en_an_vy [enit], 0, 144 << FIXBITS);
			}
			break;
			
		case FANTIES_RETREATING:
			en_an_x [enit] += addsign (_en_x1 - _en_x, 1 << FIXBITS);
			en_an_y [enit] += addsign (_en_y1 - _en_y, 1 << FIXBITS);

			#ifdef FANTIES_NUMB_ON_FLAG
				if (flags [FANTIES_NUMB_ON_FLAG])
			#endif
				if (distance (gpx, gpy, _en_x, _en_y) <= FANTIES_SIGHT_DISTANCE)
					en_an_state [enit] = FANTIES_PURSUING;
			
			break;
	}
	
	_en_x = en_an_x [enit] >> FIXBITS;
	_en_y = en_an_y [enit] >> FIXBITS;
	
	if (
		en_an_state [enit] == FANTIES_RETREATING &&
		_en_x == _en_x1 &&
		_en_y == _en_y1
	) en_an_state [enit] = FANTIES_IDLE;
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
		en_an_x [enit] = limit (en_an_x [enit] + en_an_vx [enit], 0, 224 << FIXBITS);
		en_an_y [enit] = limit (en_an_y [enit] + en_an_vy [enit], 0, 144 << FIXBITS);
	}
	
	_en_x = en_an_x [enit] >> FIXBITS;
	_en_y = en_an_y [enit] >> FIXBITS;
#endif
