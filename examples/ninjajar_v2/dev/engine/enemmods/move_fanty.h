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
				if (gpx < _en_x) rds = -FANTIES_A;
				else rds = FANTIES_A;
				
				if (en_an_vx [enit] += rds);
				if (en_an_vx [enit] < -FANTIES_MAX_V) en_an_vx [enit] = -FANTIES_MAX_V;
				else if (en_an_vx [enit] > FANTIES_MAX_V) en_an_vx [enit] = FANTIES_MAX_V;

				en_an_x [enit] += en_an_vx [enit];
				if (en_an_x [enit] < 0) en_an_x [enit] = 0;
				if (en_an_x [enit] > (224 << FIXBITS)) en_an_x [enit] = (224 << FIXBITS);

				if (gpy < _en_y) rds = -FANTIES_A;
				else rds = FANTIES_A;
				
				if (en_an_vy [enit] += rds);
				if (en_an_vy [enit] < -FANTIES_MAX_V) en_an_vx [enit] = -FANTIES_MAX_V;
				else if (en_an_vy [enit] > FANTIES_MAX_V) en_an_vx [enit] = FANTIES_MAX_V;

				en_an_y [enit] += en_an_vy [enit];
				if (en_an_y [enit] < 0) en_an_y [enit] = 0;
				if (en_an_y [enit] > (144 << FIXBITS)) en_an_y [enit] = (144 << FIXBITS);
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
	if (gpx < _en_x) rds = -FANTIES_A;
	else rds = FANTIES_A;
	
	if (en_an_vx [enit] += rds);
	if (en_an_vx [enit] < -FANTIES_MAX_V) en_an_vx [enit] = -FANTIES_MAX_V;
	else if (en_an_vx [enit] > FANTIES_MAX_V) en_an_vx [enit] = FANTIES_MAX_V;

	if (gpy < _en_y) rds = -FANTIES_A;
	else rds = FANTIES_A;
	
	if (en_an_vy [enit] += rds);
	if (en_an_vy [enit] < -FANTIES_MAX_V) en_an_vx [enit] = -FANTIES_MAX_V;
	else if (en_an_vy [enit] > FANTIES_MAX_V) en_an_vx [enit] = FANTIES_MAX_V;

	#ifdef FANTIES_NUMB_ON_FLAG
		if (flags [FANTIES_NUMB_ON_FLAG])
	#endif				
	{
		en_an_x [enit] += en_an_vx [enit];
		if (en_an_x [enit] < 0) en_an_x [enit] = 0;
		if (en_an_x [enit] > (224 << FIXBITS)) en_an_x [enit] = (224 << FIXBITS);

		en_an_y [enit] += en_an_vy [enit];
		if (en_an_y [enit] < 0) en_an_y [enit] = 0;
		if (en_an_y [enit] > (144 << FIXBITS)) en_an_y [enit] = (144 << FIXBITS);
	}
	
	_en_x = en_an_x [enit] >> FIXBITS;
	_en_y = en_an_y [enit] >> FIXBITS;
#endif
