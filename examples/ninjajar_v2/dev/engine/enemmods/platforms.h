#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
	if (gpt == 8) {
		if (pregotten && (p_gotten == 0) && (p_jmp_on == 0 || p_jmp_ct > 2)) {
			// Horizontal moving platforms
			if (_en_mx) {
				if (gpy + 16 >= _en_y && gpy + 10 <= _en_y) {
					p_gotten = 1;					
					ptgmx = _en_mx;
					p_x += ptgmx;
					p_y = (_en_y - 16); gpy = p_y;
					p_jmp_on = 0;					
				}
			}

			// Vertical moving platforms
			if (
				(_en_my < 0 && gpy + 18 >= _en_y && gpy + 10 <= _en_y) ||
				(_en_my > 0 && gpy + 17 + _en_my >= _en_y && gpy + 10 <= _en_y)
			) {
				p_gotten = 1;
				ptgmy = _en_my;
				p_y = _en_y - 16; gpy = p_y;
				p_jmp_on = 0;				
			}
		}
	} else 
#else

	/*
	if (pregotten && (p_gotten == 0)) {

		// Horizontal moving platforms
		if (_en_mx) {
			if (gpy + 16 >= _en_y && gpy + 10 <= _en_y) {
				p_gotten = 1;
				ptgmx = _en_mx << FIXBITS;
				gpy = (_en_y - 16); p_y = gpy << FIXBITS;
			}
		}

		// Vertical moving platforms
		if (
			(_en_my < 0 && gpy + 18 >= _en_y && gpy + 10 <= _en_y) ||
			(_en_my > 0 && gpy + 17 + _en_my >= _en_y && gpy + 10 <= _en_y)
		) {
			p_gotten = 1;
			ptgmy = _en_my << FIXBITS;
			gpy = (_en_y - 16); p_y = gpy << FIXBITS;						
		}

	}
	*/
	
	#asm
			ld  a, (_gpt)
			cp  8
			jp  nz, _enems_platforms_done

			ld  a, (_p_jmp_on)
			or  a
			jp  nz, _enems_platforms_done

			ld  a, (_pregotten)
			or  a
			jp  z, _enems_collision_skip

			ld  a, (_p_gotten)
			or  a
			jp  nz, _enems_collision_skip

			// Horizontal

			ld  a, (__en_mx)
			or  a
			jr  z, _enems_plats_horz_done

			// gpy + 16 >= _en_y
			ld  a, (__en_y)
			ld  c, a
			ld  a, (_gpy)
			add 16
			cp  c
			jr  c, _enems_plats_horz_done

			// gpy + 10 <= _en_y -> _en_y >= _gpy + 10
			ld  a, (_gpy)
			add 10
			ld  c, a
			ld  a, (__en_y)
			cp  c
			jr  c, _enems_plats_horz_done

		._enems_plats_horz_do
			ld  a, 1
			ld  (_p_gotten), a
			ld  a, (__en_mx)
			#if FIXBITS == 6
				sla a
				sla a
			#endif
			sla a
			sla a
			sla a
			sla a 	; times FIXBITS
			ld  (_ptgmx), a

			jr _enems_plats_gpy_set

		._enems_plats_horz_done

			// Vertical

			//(_en_my < 0 && gpy + 18 >= _en_y && gpy + 10 <= _en_y) ||
			//(_en_my > 0 && gpy + 17 + _en_my >= _en_y && gpy + 10 <= _en_y)

			// Has been rehashed to:

			//	if (_en_y >= gpy + 10) {
			//		if (_en_my < 0) {
			//			if (gpy + 18 >= _en_y) goto DO
			//		} else {
			//			if (gpy + 17 + _en_my >= _en_y) goto DO
			//		}
			//	}

		._enems_plats_vert_check_1

			// _en_y >= gpy + 10
			ld  a, (_gpy)
			add 10
			ld  c, a
			ld  a, (__en_y)
			cp  c
			jr  c, _enems_plats_vert_done

			// _en_my < 0
			ld  a, (__en_my)
			bit 7, a
			jr  z, _enems_plats_vert_check_2 	; _en_my is positive 

			// gpy + 17 >= _en_y
			ld  a, (__en_y)
			ld  c, a
			ld  a, (_gpy)
			add 17
			cp  c
			jr  nc, _enems_plats_vert_do

		._enems_plats_vert_check_2
			// _en_my > 0
			// (implied)

			// gpy + 17 + _en_my >= _en_y
			ld  a, (__en_y)
			ld  c, a
			ld  a, (__en_my)
			ld  b, a
			ld  a, (_gpy)
			add 17
			add b
			cp  c
			jr  c, _enems_plats_vert_done		

		._enems_plats_vert_do

			ld  a, 1
			ld  (_p_gotten), a
			ld  a, (__en_my)
			#if FIXBITS == 6
				sla a
				sla a
			#endif
			sla a
			sla a
			sla a
			sla a 	; times FIXBITS
			ld  (_ptgmy), a

			xor a
			ld  (_p_vy), a

		._enems_plats_gpy_set

			ld  a, (__en_y)
			sub 16
			ld  (_gpy), a

			// p_y = gpy << FIXBITS; 16 bits shift
			ld  d, 0
			ld  e, a
			ld  l, FIXBITS
			call l_asl
			ld  (_p_y), hl

		._enems_plats_vert_done
			jp  _enems_collision_skip

		._enems_platforms_done
	#endasm

#endif