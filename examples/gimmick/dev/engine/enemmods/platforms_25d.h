	// Platforms: 2.5d foundation stuff
	
	/*
	if (gpt == 8) {
		if (pregotten && p_gotten == 0 && p_z == 0) {
			p_gotten = 1;
			ptgmx = _en_mx << FIXBITS;
			ptgmy = _en_my << FIXBITS;
		}
	} else
	*/

	
	#asm
			ld  a, (_gpt)
			cp  8
			jr  nz, _enems_platforms_25d_done

			ld  a, (_pregotten)
			and a
			jp  z, _enems_collision_skip

			ld  a, (_p_gotten)
			jp  nz, _enems_collision_skip

			ld  a, (_p_z)
			jp  nz, _enems_collision_skip

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
			sla a 	; TIMES FIXBITS
			ld  (_ptgmx), a

			ld  a, (__en_my)
			#if FIXBITS == 6
				sla a
				sla a
			#endif
			sla a
			sla a
			sla a
			sla a 	; TIMES FIXBITS
			ld  (_ptgmy), a

			jp _enems_collision_skip
		._enems_platforms_25d_done
	#endasm
		