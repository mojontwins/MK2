// Move Fanty
active = killable = animate = 1;

// Copy arrays as fast as you can
#asm
		ld  bc, (_enit)
		ld  b, 0

		ld  hl, _en_an_vx
		add hl, bc
		ld  a, (hl)
		ld  (__en_an_vx), a

		ld  hl, _en_an_vy
		add hl, bc
		ld  a, (hl)
		ld  (__en_an_vy), a

		ld  hl, _en_an_x
		add hl, bc
		add hl, bc
		ld  e, (hl)
		inc hl
		ld  d, (hl)
		ld  (__en_an_x), de

		ld  hl, _en_an_y
		add hl, bc
		add hl, bc
		ld  e, (hl)
		inc hl
		ld  d, (hl)
		ld  (__en_an_y), de		
#endasm

#ifdef FANTIES_SIGHT_DISTANCE
	// Complex fanties

	cx1 = gpx; cy1 = gpy; cx2 = _en_x; cy2 = _en_y; rda = distance ();

	switch (en_an_state [enit]) {
		case FANTIES_IDLE:
			#ifdef FANTIES_NUMB_ON_FLAG
				if (flags [FANTIES_NUMB_ON_FLAG])
			#endif
			
			if (rda <= FANTIES_SIGHT_DISTANCE)
				en_an_state [enit] = FANTIES_PURSUING;
			
			break;
			
		case FANTIES_PURSUING:
			#ifdef FANTIES_NUMB_ON_FLAG
				if (0 == flags [FANTIES_NUMB_ON_FLAG]) en_an_state [enit] = FANTIES_RETREATING;
			#endif				
			
			if (rda > FANTIES_SIGHT_DISTANCE) {
				en_an_state [enit] = FANTIES_RETREATING;
			} else {
				if (gpx < _en_x) rds = -FANTIES_A;
				else rds = FANTIES_A;
				
				if (_en_an_vx += rds);
				if (_en_an_vx < -FANTIES_MAX_V) _en_an_vx = -FANTIES_MAX_V;
				else if (_en_an_vx > FANTIES_MAX_V) _en_an_vx = FANTIES_MAX_V;

				_en_an_x += _en_an_vx;
				if (_en_an_x < 0) _en_an_x = 0;
				else if (_en_an_x > (224 << FIXBITS)) _en_an_x = (224 << FIXBITS);

				if (gpy < _en_y) rds = -FANTIES_A;
				else rds = FANTIES_A;
				
				if (_en_an_vy += rds);
				if (_en_an_vy < -FANTIES_MAX_V) _en_an_vy = -FANTIES_MAX_V;
				else if (_en_an_vy > FANTIES_MAX_V) _en_an_vy = FANTIES_MAX_V;

				_en_an_y += _en_an_vy;
				if (_en_an_y < 0) _en_an_y = 0;
				else if (_en_an_y > (144 << FIXBITS)) _en_an_y = (144 << FIXBITS);
			}
			break;
			
		case FANTIES_RETREATING:
			_en_an_x += addsign (_en_x1 - _en_x, 1 << FIXBITS);
			_en_an_y += addsign (_en_y1 - _en_y, 1 << FIXBITS);

			#ifdef FANTIES_NUMB_ON_FLAG
				if (flags [FANTIES_NUMB_ON_FLAG])
			#endif
				if (rda <= FANTIES_SIGHT_DISTANCE)
					en_an_state [enit] = FANTIES_PURSUING;
			
			break;
	}
	
	_en_x = _en_an_x >> FIXBITS;
	_en_y = _en_an_y >> FIXBITS;
	
	if (
		en_an_state [enit] == FANTIES_RETREATING &&
		_en_x == _en_x1 &&
		_en_y == _en_y1
	) en_an_state [enit] = FANTIES_IDLE;
#else
	// Plain fanties
	if (gpx < _en_x) rds = -FANTIES_A;
	else rds = FANTIES_A;
	
	if (_en_an_vx += rds);
	if (_en_an_vx < -FANTIES_MAX_V) _en_an_vx = -FANTIES_MAX_V;
	else if (_en_an_vx > FANTIES_MAX_V) _en_an_vx = FANTIES_MAX_V;

	if (gpy < _en_y) rds = -FANTIES_A;
	else rds = FANTIES_A;
	
	if (_en_an_vy += rds);
	if (_en_an_vy < -FANTIES_MAX_V) _en_an_vx = -FANTIES_MAX_V;
	else if (_en_an_vy > FANTIES_MAX_V) _en_an_vx = FANTIES_MAX_V;

	#ifdef FANTIES_NUMB_ON_FLAG
		if (flags [FANTIES_NUMB_ON_FLAG])
	#endif				
	{
		_en_an_x += _en_an_vx;
		if (_en_an_x < 0) _en_an_x = 0;
		if (_en_an_x > (224 << FIXBITS)) _en_an_x = (224 << FIXBITS);

		_en_an_y += _en_an_vy;
		if (_en_an_y < 0) _en_an_y = 0;
		if (_en_an_y > (144 << FIXBITS)) _en_an_y = (144 << FIXBITS);
	}
	
	_en_x = _en_an_x >> FIXBITS;
	_en_y = _en_an_y >> FIXBITS;
#endif

// Update arrays as fast as you can
#asm
		ld  bc, (_enit)
		ld  b, 0

		ld  hl, _en_an_vx
		add hl, bc
		ld  a, (__en_an_vx)
		ld  (hl), a

		ld  hl, _en_an_vy
		add hl, bc
		ld  a, (__en_an_vy)
		ld  (hl), a

		ld  hl, _en_an_x
		add hl, bc
		add hl, bc
		ld  de, (__en_an_x)
		ld  (hl), e 
		inc hl
		ld  (hl), d

		ld  hl, _en_an_y
		add hl, bc
		add hl, bc
		ld  de, (__en_an_y)
		ld  (hl), e 
		inc hl
		ld  (hl), d
#endasm
