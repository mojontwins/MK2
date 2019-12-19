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

		//

		jp  _move_fanty_state_done

	._move_fanty_retreating	

	._move_fanty_state_done

		// Update new state

		ld  a, (_rdb)
		ld  hl, _en_an_state
		add hl, bc
		ld  (hl), a


	#else



	#endif

#endasm
