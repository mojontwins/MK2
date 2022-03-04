// linear movement

/*
active = animate = 1;
_en_x += _en_mx;
_en_y += _en_my;				
	
#ifdef WALLS_STOP_ENEMIES
	if (_en_x == _en_x1 || _en_x == _en_x2 || mons_col_sc_x ())	_en_mx = -_en_mx;
	if (_en_y == _en_y1 || _en_y == _en_y2 || mons_col_sc_y ())	_en_my = -_en_my;
#else
	if (_en_x == _en_x1 || _en_x == _en_x2)	_en_mx = -_en_mx;
	if (_en_y == _en_y1 || _en_y == _en_y2)	_en_my = -_en_my;
#endif
*/

#asm
		ld 	a, 1
		ld  (_active), a
		ld  (_animate), a

		ld  a, (__en_mx)
		ld  c, a
		ld  a, (__en_x)
		add a, c
		ld  (__en_x), a

		ld  c, a
		ld  a, (__en_x1)
		cp  c
		jr  z, _enems_lm_change_axis_x
		ld  a, (__en_x2)
		cp  c

	#ifdef WALLS_STOP_ENEMIES
		jr  z, _enems_lm_change_axis_x
		
		call _mons_col_sc_x
		xor a
		or l

		jr  z, _enems_lm_change_axis_x_done
	#else
		jr  nz, _enems_lm_change_axis_x_done
	#endif

	._enems_lm_change_axis_x
		ld  a, (__en_mx)
		neg
		ld  (__en_mx), a

	._enems_lm_change_axis_x_done

		ld  a, (__en_my)
		ld  c, a
		ld  a, (__en_y)
		add a, c
		ld  (__en_y), a

		ld  c, a
		ld  a, (__en_y1)
		cp  c
		jr  z, _enems_lm_change_axis_y
		ld  a, (__en_y2)
		cp  c

	#ifdef WALLS_STOP_ENEMIES
		jr  z, _enems_lm_change_axis_y
		
		call _mons_col_sc_y
		xor a
		or l

		jr  z, _enems_lm_change_axis_y_done
	#else
		jr  nz, _enems_lm_change_axis_y_done
	#endif

	._enems_lm_change_axis_y
		ld  a, (__en_my)
		neg
		ld  (__en_my), a

	._enems_lm_change_axis_y_done

#endasm

#ifdef ENABLE_SHOOTERS
	// Shoot a coco
	if (enemy_shoots && (rand () & SHOOTER_SHOOT_FREQ) == 1) shoot_coco ();
#endif
