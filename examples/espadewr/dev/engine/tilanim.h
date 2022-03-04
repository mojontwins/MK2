// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// tilanim.h

void tilanim_reset (void) {
	#asm		
			ld  hl, _tilanims_ft
			ld  de, _tilanims_ft + 1 
			ld  bc, MAX_TILANIMS - 1
			xor a
			ld  (hl), a
			ldir
			ld  (_tacount), a
			ld  (_tait), a
			ld  (_max_tilanims), a
	#endasm
}

void tilanims_add (void) {
	#asm
			ld  de, (_max_tilanims)
			ld  d, 0

			ld  a, (__n)			
			ld  hl, _tilanims_xy
			add hl, de
			ld  (hl), a

			ld  a, (__t)
			ld  hl, _tilanims_ft
			add hl, de
			ld  (hl), a

			ld  a, e
			inc a
			ld  (_max_tilanims), a
	#endasm
}

void tilanims_do (void) {
	#asm
			ld  a, (_max_tilanims)
			or  a
			ret z
	#endasm

	#ifdef TILANIMS_PERIOD
		if (tilanims_counter) { -- tilanims_counter; return; }
		else tilanims_counter = TILANIMS_PERIOD; // And execute.
	#endif

	#ifdef TILANIMS_TYPE_ONE
		#ifdef TILANIMS_SEVERAL_TYPES
			if (
				#ifdef TILANIMS_TYPE_SELECT_FLAG
					flags [TILANIMS_TYPE_SELECT_FLAG] == 1
				#else
					tilanims_type_select == 1
				#endif
			)
		#endif
		{
			#asm
			ld  a, (_tait)
			add TILANIMS_PRIME
			cp  MAX_TILANIMS
			jr  c, _tilanims_tait_0_skip
			sub MAX_TILANIMS
		._tilanims_tait_0_skip
			ld  (_tait), a

			// Check counter for tilanim #tait
			ld  d, 0
			ld  e, a

			// Check of active
			ld  hl, _tilanims_ft
			add hl, de
			ld  a, (hl)
			or  a
			ret z

			// Flip bit 7
					;ld  hl, _tilanims_ft
					;add hl, de
					;ld  a, (hl)
			xor 128
			ld  (hl), a			
			
			// Which tile?
			bit 7, a
			jr  z, _tilanims_no_flick

			inc a
		._tilanims_no_flick
			and 127
			ld  (__t), a

			// Draw tile
			ld  hl, _tilanims_xy
			add hl, de
			ld  a, (hl)
			ld  c, a
			srl a
			srl a
			srl a
			and 0xfe
			add VIEWPORT_X
			ld  (__x), a

			ld  a, c
			and 15
			sla a
			add VIEWPORT_Y
			ld  (__y), a

			call _draw_coloured_tile
			call _invalidate_tile
	#endasm
		}
	#endif

	#ifdef TILANIMS_TYPE_ALL
		#ifdef TILANIMS_SEVERAL_TYPES
			if (
				#ifdef TILANIMS_TYPE_SELECT_FLAG
					flags [TILANIMS_TYPE_SELECT_FLAG] == 1
				#else
					tilanims_type_select == 1
				#endif
			)
		#endif
		{
			#asm
				// Flick & paint all tilanims
				ld  de, (_max_tilanims)
				ld  d, 0

			._tilanims_update_loop
				dec e				

				ld  hl, _tilanims_ft
				add hl, de
				ld  a, (hl)
				xor 128
				ld  (hl), a

				bit 7, a
				jr  z, _tilanims_no_flick_all

				inc a

			._tilanims_no_flick_all
				and 127
				ld  (__t), a
				
				// Draw tile
				ld  hl, _tilanims_xy
				add hl, de
				ld  a, (hl)
				ld  c, a
				srl a
				srl a
				srl a
				and 0xfe
				add VIEWPORT_X
				ld  (__x), a

				ld  a, c
				and 15
				sla a
				add VIEWPORT_Y
				ld  (__y), a

				push de
				call _draw_coloured_tile
				call _invalidate_tile
				pop  de

				xor a
				or  e
				ret z

				jr  _tilanims_update_loop

			#endasm
		}
	#endif
}
