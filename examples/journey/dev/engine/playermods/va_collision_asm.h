// half-box collision. Check for tile behaviour in two points.
// Which points? It depends on the type of collision configured:

#asm
		call _player_calc_bounding_box

		xor a 
		ld  (_hit_v), a

		ld  a, (_ptx1)
		ld  (_cx1), a
		ld  a, (_ptx2)
		ld  (_cx2), a

		// Calculate vertical velocity
		
		ld  a, (_p_vy)
		#if defined (ENABLE_CONVEYORS) || !defined (DISABLE_PLATFORMS)
			ld  c, a
			ld  a, (_ptgmy)
			add c
		#endif

		// Skip if not moving in the vertical axis

		or  a
		jp  z, _va_collision_done

		// Check sign

		bit 7, a
		jr  z, _va_collision_vy_positive

	._va_collision_vy_negative

		// Velocity negative (going upwards)

		ld  a, (_pty1)
		ld  (_cy1), a
		ld  (_cy2), a

		call _cm_two_points

		// if ((at1 & 8) || (at2 & 8)) {
		ld  a, (_at1)
		and 8
		jr  nz, _va_col_vy_neg_do

		ld  a, (_at2)
		and 8
		jr  z, _va_collision_checkevil

	._va_col_vy_neg_do

		#ifdef PLAYER_BOUNCE_WITH_WALLS
			ld  a, (_p_vy)
			sra a
			neg a
		#else
			xor a
		#endif 
		ld  (_p_vy), a

		ld  a, (_pty1)
		inc a
		sla a
		sla a
		sla a
		sla a		

		#if defined (BOUNDING_BOX_8_BOTTOM)			
			// gpy = ((pty1 + 1) << 4) - 8;
			sub 8
		#elif defined (BOUNDING_BOX_8_CENTERED)
			// gpy = ((pty1 + 1) << 4) - 4;
			sub 4
		#elif defined (BOUNDING_BOX_TINY_BOTTOM)
			// gpy = ((pty1 + 1) << 4) - 14;
			sub 14
		#else
			// gpy = ((pty1 + 1) << 4);
		#endif

		ld  (_gpy), a

		// p_y = gpy << FIXBITS; 16 bits shift
		ld  d, 0
		ld  e, a
		ld  l, FIXBITS
		call l_asl
		ld  (_p_y), hl

		ld  a, WTOP
		ld  (_wall_v), a

		jr  _va_collision_checkevil

	._va_collision_vy_positive

		// Velocity negative (going upwards)
		ld  a, (_pty2)
		ld  (_cy1), a
		ld  (_cy2), a

		call _cm_two_points

		#ifdef PLAYER_GENITAL
			// if ((at1 & 8) || (at2 & 8)) {
			ld  a, (_at1)
			and 8
			jr  nz, _va_col_vy_pos_do

			ld  a, (_at2)
			and 8
			jr  z, _va_collision_checkevil
		#else
			// if ((at1 & 8) || 
			ld  a, (_at1)
			and 8
			jr  nz, _va_col_vy_pos_do

			// (at2 & 8) || 
			ld  a, (_at2)
			and 8
			jr  nz, _va_col_vy_pos_do

			// (((gpy - 1) & 15) < 8 &&
			ld  a, (_gpy)
			dec a
			and 15
			cp  8 
			jr  nc, _va_collision_checkevil

			// ((at1 & 4) || (at2 & 4))))
			ld  a, (_at1)
			and 4
			jr  nz, _va_col_vy_pos_do

			ld  a, (_at2)
			and 4
			jr  z, _va_collision_checkevil
		#endif
	._va_col_vy_pos_do

		#if defined (ENABLE_FLOATING_OBJECTS) && defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_CORCHONETA)
			// Remember original p_vy to use with the corchoneta.
			// p_vlhit = p_vy;
			ld  a, (_pvy)
			ld  (_p_vlhit), a
		#endif

		#ifdef PLAYER_BOUNCE_WITH_WALLS
			ld  a, (_p_vy)
			sra a
			neg a
		#else
			xor a
		#endif 
		ld  (_p_vy), a	

		ld  a, (_pty2)
		dec a 
		sla a
		sla a
		sla a
		sla a

		#ifdef BOUNDING_BOX_8_CENTERED
			add 4
		#endif

		ld  (_gpy), a

		// p_y = gpy << FIXBITS; 16 bits shift
		ld  d, 0
		ld  e, a
		ld  l, FIXBITS
		call l_asl
		ld  (_p_y), hl

		ld  a, WBOTTOM
		ld  (_wall_v), a
		jr  _va_collision_done

	._va_collision_checkevil

		#ifndef DEACTIVATE_EVIL_TILE
			#endasm
				hit_v = ((at1 IS_EVIL) || (at2 IS_EVIL));
			#asm
		#endif

	._va_collision_done
#endasm
	
gpxx = gpx >> 4;
gpyy = gpy >> 4;
