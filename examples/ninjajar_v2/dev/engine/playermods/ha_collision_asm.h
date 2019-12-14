// half-box collision. Check for tile behaviour in two points.
// Which points? It depends on the type of collision configured:

#asm
		call _player_calc_bounding_box

		#ifndef ONLY_VERTICAL_EVIL_TILE
			xor a 
			ld  (_hit_h), a
		#endif

		ld  a, (_pty1)
		ld  (_cy1), a
		ld  a, (_pty2)
		ld  (_cy2), a

		// Calculate horizontal velocity
		
		ld  a, (_p_vx)
		#if defined (ENABLE_CONVEYORS) || !defined (DISABLE_PLATFORMS)
			ld  c, a
			ld  a, (_ptgmx)
			add c
		#endif

		// Skip if not moving in the horizontal axis

		or  a
		jp  z, _ha_collision_done

		// Check sign

		bit 7, a
		jr  z, _ha_collision_vx_positive

	._ha_collision_vx_negative

		ld  a, (_ptx1)
		ld  (_cx1), a
		ld  (_cx2), a

		call _cm_two_points

		// if ((at1 & 8) || (at2 & 8)) {
		ld  a, (_at1)
		and 8
		jr  nz, _ha_col_vx_neg_do

		ld  a, (_at2)
		and 8
		jr  z, _va_collision_checkevil

	._va_col_vx_neg_do

		#ifdef PLAYER_BOUNCE_WITH_WALLS
			ld  a, (_p_vx)
			sra a
			neg a
		#else
			xor a
		#endif 
		ld  (_p_vx), a

		ld  a, (_ptx1)
		inc a
		sla a
		sla a
		sla a
		sla a

		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
			sub 4
		#endif

		ld (_gpx), a

		// p_x = gpx << FIXBITS; 16 bits shift
		ld  d, 0
		ld  e, a
		ld  l, FIXBITS
		call l_asl
		ld  (_p_x), hl

		ld  a, WLEFT
		ld  (_wall_h), a

		jr  _va_collision_checkevil

	._ha_collision_vx_positive

		ld  a, (_ptx2)
		ld  (_cx1), a
		ld  (_cx2), a

		call _cm_two_points

		// if ((at1 & 8) || (at2 & 8)) {
		ld  a, (_at1)
		and 8
		jr  nz, _ha_col_vx_pos_do

		ld  a, (_at2)
		and 8
		jr  z, _va_collision_checkevil

	._va_col_vx_pos_do

		#ifdef PLAYER_BOUNCE_WITH_WALLS
			ld  a, (_p_vx)
			sra a
			neg a
		#else
			xor a
		#endif 
		ld  (_p_vx), a

		ld  a, (_ptx2)
		dec a
		sla a
		sla a
		sla a
		sla a

		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
			add 4
		#endif

		ld (_gpx), a

		// p_x = gpx << FIXBITS; 16 bits shift
		ld  d, 0
		ld  e, a
		ld  l, FIXBITS
		call l_asl
		ld  (_p_x), hl

		ld  a, WRIGHT
		ld  (_wall_h), a

	._ha_collision_checkevil

		#ifdef DEACTIVATE_EVIL_TILE
			#ifndef ONLY_VERTICAL_EVIL_TILE
				#endasm
					hit_h = ((at1 IS_EVIL) || (at2 IS_EVIL));
				#asm
			#endif
		#endif

	._ha_collision_done
#endasm
	