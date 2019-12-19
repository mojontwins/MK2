// Move Fanty

#asm
		ld  a, 1
		ld  (_active), a
		ld  (_killable), a
		ld  (_animate), a

		// Copy arrays as fast as you can

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

	#ifdef FANTIES_SIGHT_DISTANCE

		#ifdef FAMTIES_NUMB_ON_FLAG
			ld  de, FANTIES_NUMB_ON_FLAG
			ld  hl, _flags
			add hl, de
			ld  a, (hl)
			or  a
			jp  nz, _move_fanty_state_done
		#endif

		ld  a, (_gpx)
		ld  (_cx1), a

		ld  a, (_gpy)
		ld  (_cy1), a

		ld  a, (__en_x)
		ld  (_cx2), a

		ld  a, (__en_y)
		ld  (_cy2), a

		call _distance

		ld  a, l
		ld  (_rda), a

		// Check state

		ld  bc, (_enit)
		ld  b, 0

		ld  hl, _en_an_state
		add hl, bc
		ld  a, (hl)
		ld  (_rdb), a 		// Copy state to rdb

		cp  FANTIES_PURSUING
		jp  z, _move_fanty_pursuing

		cp  FANTIES_RETREATING
		jp  z, _move_fanty_retreating

	._move_fanty_idle

		ld  a, (_rda)
		cp  FANTIES_SIGHT_DISTANCE
		jp  nc, _move_fanty_state_done

		ld  a, FANTIES_PURSUING
		ld  (_rdb), a

		jp  _move_fanty_state_done

	._move_fanty_pursuing

		ld  a, (_rda)
		cp  FANTIES_SIGHT_DISTANCE
		jr  c, _move_fanty_pursuing_do

		ld  a, FANTIES_PURSUING
		ld  (_rdb), a

		jp  _move_fanty_state_done

	._move_fanty_pursuing_do

		// Horizontal axis
		// ---------------

		// Decide in which direction to accelerate based upon player's coordinates
		ld  a, (__en_x)
		ld  c, a
		ld  a, (_gpx)
		cp  c
		jr  nc, _move_fanty_ax_pos
	._move_fanty_ax_neg
		ld  a, -FANTIES_A
		jr  _move_fanty_ax_set
	._move_fanty_ax_pos
		ld  a, FANTIES_A
	._move_fanty_ax_set
		
		// Modify velocity 
		ld  c, a
		ld  a, (__en_an_vx)
		add c
		
		// Enforce limits: Positive or negative?
		bit 7, a
		jr  nz, _move_fanty_vx_limit_neg

	._move_fanty_vx_limit_pos
		ld  b, 0 	// Positive sign extension
		
		cp 	FANTIES_MAX_V
		jr  c, _move_fanty_vx_limit_set

		ld  a, FANTIES_MAX_V
		jr _move_fanty_vx_limit_set

	._move_fanty_vx_limit_neg
		ld  b, 0xff // Negative sign extension
		
		neg a
		cp 	FANTIES_MAX_V
		jr  c, _move_fanty_vx_limit_neg_ok

		ld  a, -FANTIES_MAX_V
		jr  _move_fanty_vx_limit_set

	._move_fanty_vx_limit_neg_ok
		neg a

	._move_fanty_vx_limit_set
		ld  (__en_an_vx), a

		// Move X
		ld  hl, (__en_an_x)

		ld  c, a
		add hl, bc

		// Limit X
		// _en_an_x < 0, 16 bits:
		bit 7, h
		jr  nc, _move_fanty_x_limit_0

		ld  hl, 0
		jr  _move_fanty_x_set

	._move_fanty_x_limit_0
		// _en_an_x > 224<<FIXBITS
		ld  d, h
		ld  e, l
		ld  bc, 3584 // 224<<FIXBITS
		sbc hl, bc
		jr  c, _move_fanty_x_limit_224

		ld  h, d
		ld  l, e
		jr  _move_fanty_x_set

	._move_fanty_x_limit_224
		ld  hl, 3584 // 224<<FIXBITS

	._move_fanty_x_set
		ld  (__en_an_x), hl

		// Vertical axis
		// -------------

		// Decide in which direction to accelerate based upon player's coordinates
		ld  a, (__en_y)
		ld  c, a
		ld  a, (_gpy)
		cp  c
		jr  nc, _move_fanty_ay_pos
	._move_fanty_ay_neg
		ld  a, -FANTIES_A
		jr  _move_fanty_ay_set
	._move_fanty_ay_pos
		ld  a, FANTIES_A
	._move_fanty_ay_set
		
		// Modify velocity 
		ld  c, a
		ld  a, (__en_an_vy)
		add c
		
		// Enforce limits: Positive or negative?
		bit 7, a
		jr  nz, _move_fanty_vy_limit_neg

	._move_fanty_vy_limit_pos
		ld  b, 0		// Positive sign extension
		cp 	FANTIES_MAX_V
		jr  c, _move_fanty_vy_limit_set

		ld  a, FANTIES_MAX_V
		jr _move_fanty_vy_limit_set

	._move_fanty_vy_limit_neg
		ld  b, 0xff		// Negative sign extension
		neg a
		cp 	FANTIES_MAX_V
		jr  c, _move_fanty_vy_limit_neg_ok

		ld  a, -FANTIES_MAX_V
		jr  _move_fanty_vy_limit_set

	._move_fanty_vy_limit_neg_ok
		neg a

	._move_fanty_vy_limit_set
		ld  (__en_an_vy), a

		// Move Y
		ld  hl, (__en_an_y)
		ld  c, a
		add hl, bc

		// Limit Y
		// _en_an_y < 0, 16 bits:
		bit 7, h
		jr  nc, _move_fanty_y_limit_0

		ld  hl, 0
		jr  _move_fanty_y_set

	._move_fanty_y_limit_0
		// _en_an_y > 144<<FIXBITS
		ld  d, h
		ld  e, l
		ld  bc, 2304 // 144<<FIXBITS
		sbc hl, bc
		jr  c, _move_fanty_y_limit_144

		ld  h, d
		ld  l, e
		jr  _move_fanty_y_set

	._move_fanty_y_limit_144
		ld  hl, 2304 // 144<<FIXBITS

	._move_fanty_y_set
		ld  (__en_an_y), hl

		jp  _move_fanty_state_done

	._move_fanty_retreating	
		// _en_an_x += addsign (_en_x1 - _en_x, 1 << FIXBITS);
		// Which means:
		// if (_en_x == _en_x1) _en_an_x += 0;
		// else if (_en_x < _en_x1) _en_an_x += 16;
		// else _en_an_x -= 16;

		ld  hl, (__en_an_x)
		ld  bc, 16

		ld  a, (__en_x1)
		ld  c, a
		ld  a, (__en_x)
		cp  c
		jr  z, _move_fanty_r_x_done

		jr  nc, _move_fanty_r_x_neg

	._move_fanty_r_x_pos		
		add hl, bc
		jr  _move_fanty_r_x_set

	._move_fanty_r_x_neg
		sbc hl, bc

	._move_fanty_r_x_set
		ld  (__en_an_x), hl

	._move_fanty_r_x_done

		// _en_an_y += addsign (_en_y1 - _en_y, 1 << FIXBITS);
		// Which means:
		// if (_en_y == _en_y1) _en_an_y += 0;
		// else if (_en_y < _en_y1) _en_an_y += 16;
		// else _en_an_y -= 16;

		ld  hl, (__en_an_y)
		ld  bc, 16

		ld  a, (__en_y1)
		ld  c, a
		ld  a, (__en_y)
		cp  c
		jr  z, _move_fanty_r_y_done

		jr  nc, _move_fanty_r_y_neg

	._move_fanty_r_y_pos		
		add hl, bc
		jr  _move_fanty_r_y_set

	._move_fanty_r_y_neg
		sbc hl, bc

	._move_fanty_r_y_set
		ld  (__en_an_y), hl

	._move_fanty_r_y_done

		// if (_en_x == _en_x1 && _en_y == _en_y1) en_an_state [enit] = FANTIES_IDLE;
		ld  a, (__en_x1)
		ld  c, a
		ld  a, (__en_x)
		cp  c
		jr  nz, _move_fanty_r_chstate_done
	
		ld  a, (__en_y1)
		ld  c, a
		ld  a, (__en_y)
		cp  c
		jr  nz, _move_fanty_r_chstate_done

		ld  a, FANTIES_IDLE
		ld  (_rdb), a
		jr  _move_fanty_state_done

	._move_fanty_r_chstate_done

		// if (rda <= FANTIES_SIGHT_DISTANCE) en_an_state [enit] = FANTIES_PURSUING;
		ld  a, (_rda)
		cp  FANTIES_SIGHT_DISTANCE
		jr  nc, _move_fanty_state_done

		ld  a, FANTIES_PURSUING
		ld  (_rdb), a

	._move_fanty_state_done

		// Update new state

		ld  bc, (_enit)
		ld  b, 0
		ld  a, (_rdb)
		ld  hl, _en_an_state
		add hl, bc
		ld  (hl), a

		#endasm
		_en_x = _en_an_x >> FIXBITS;
		_en_y = _en_an_y >> FIXBITS;
		#asm

	#else

		// Plain fanties to do

	#endif

		// Update arrays as fast as you can
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
_x=0;_y=1;_t=abs(_en_an_vx);print_number2 ();