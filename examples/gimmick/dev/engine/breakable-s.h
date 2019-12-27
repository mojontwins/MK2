// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// breakable-s.h
// Simple breakable tiles helper functions

void wall_broken (void) {
	gpd = 0;
	
	// gpaux = (_y << 4) - _y + _x;
	#asm
			ld  a, (__y)
			ld  c, a
			sla a
			sla a
			sla a
			sla a
			sub c
			ld  c, a
			ld  a, (__x)
			add c
			ld  (_gpaux), a
	#endasm

	#ifdef BREAKABLE_TILE_GET
		if (map_buff [gpaux] == BREAKABLE_TILE_GET &&
			(rand () & BREAKABLE_TILE_FREQ) <= BREAKABLE_TILE_FREQ_T) gpd = TILE_GET;
	#endif
	_n = 0; _t = gpd; update_tile ();

	// Persistent maps:
	#ifdef PERSISTENT_BREAKABLE
			// Modify map
		#ifdef UNPACKED_MAP			
			#asm
				._persistent_breakable_calc_pointer

					// asm_int = (n_pant << 7) + (n_pant << 4) + (n_pant << 2) + (n_pant << 1);

					ld  a, (_n_pant)
					sla a 				; A = n_pant << 1. Safe in 8 bits

					ld  h, 0
					ld  l, a 			; HL = n_pant << 1
					push hl

					add hl, hl 			; HL = n_pant << 2
					push hl

					add hl, hl
					add hl, hl 			; HL = n_pant << 4
					push hl

					add hl, hl
					add hl, hl
					add hl, hl 			; HL = n_pant << 7
					pop de 				; DE = n_pant << 4
					add hl, de 		 	; HL = (n_pant << 7) + (n_pant << 4)
					pop de 				; DE = n_pant << 2
					add hl, de 			; HL = (n_pant << 7) + (n_pant << 4) + (n_pant << 2)
					pop de 				; DE = n_pant << 1
					add hl, de 			; HL = (n_pant << 7) + (n_pant << 4) + (n_pant << 2) + (n_pant << 1)
					
					// map [asm_int + gpaux] = 0;

					ld  de, (_gpaux)
					ld  d, 0
					add hl, de
					ld  de, _map
					add hl, de
					xor a
					ld  (hl), 0
			#endasm			
		#else
			#asm				
				._persistent_breakable_calc_pointer

					// asm_int = (n_pant << 6) + (n_pant << 3) + (n_pant << 1) + (n_pant);

					ld  a, (_n_pant)
					ld  c, a 			; C = n_pant
					sla a 				; A = n_pant << 1. Safe in 8 bits

					ld  h, 0
					ld  l, a 			; HL = n_pant << 1
					push hl

					add hl, hl 			; 
					add hl, hl 			; HL = n_pant << 3
					push hl

					add hl, hl
					add hl, hl
					add hl, hl 			; HL = n_pant << 6
					
					pop de 				; DE = n_pant << 3
					add hl, de 		 	; HL = (n_pant << 6) + (n_pant << 3)
					pop de 				; DE = n_pant << 1
					add hl, de 			; HL = (n_pant << 6) + (n_pant << 3) + (n_pant << 1)
					ld  b, 0 			; BC = n_pant
					add hl, bc 			; HL = (n_pant << 6) + (n_pant << 3) + (n_pant << 1) + (n_pant)
					
					// map_pointer = map + asm_int + (gpaux >> 1);

					ld  a, (_gpaux)
					srl a
					ld  b, 0
					ld  c, a
					add hl, bc
					ld  de, _map
					add hl, de

					// *map_pointer = (gpaux & 1) ? ((*map_pointer) & 0xf0) : ((*map_pointer) & 0x0f);

					ld  a, (_gpaux)
					and 1
					jr  z, _modify_even

				._modify_odd
					ld  a, (hl)
					and 0xf0

					jr  _persistent_breakable_map_set

				._modify_even
					ld  a, (hl)
					and  0x0f

				._persistent_breakable_map_set

					ld  (hl), a
			#endasm
			
		#endif
	#endif
}

#ifdef BREAKABLE_ANIM
	void process_breakable (void) {
		unsigned char brkit;

		do_process_breakable = 0;

		for (brkit = 0; brkit < MAX_BREAKABLE; brkit ++) {
			if (breaking_f [brkit]) {
				if (! --breaking_f [brkit]) {
					#ifdef MODE_128K
						_AY_PL_SND (SFX_BREAK_WALL_ANIM);
					#endif
					_x = breaking_x [brkit]; _y = breaking_y [brkit]; wall_broken ();
				} else {
					do_process_breakable = 1;
				}
			}
		}
	}
#endif

void break_wall (void) {
	cx1 = _x; cy1 = _y; if (attr () & 16) {
		
		#asm
				// gpaux = (_y << 4) - _y + _x;

				ld  a, (__y)
				ld  c, a
				sla a
				sla a
				sla a
				sla a
				sub c
				ld  c, a
				ld  a, (__x)
				add c
				
				// map_attr [gpaux] &= 0xEF; // 11101111, remove "breakable" bit.
				ld  b, 0
				ld  c, a
				ld  hl, _map_attr
				add hl, bc
				ld  a, (hl)
				and 0xEF
				ld  (hl), a
		#endasm

		#ifdef BREAKABLE_ANIM
			// add this block to the "breaking" tile list
			
			#asm
					ld  bc, (_breaking_idx)
					ld  b, 0
					
					ld  hl, _breaking_f
					add hl, bc
					ld  a, MAX_BREAKABLE_FRAMES
					ld  (hl), a

					ld  hl, _breaking_x
					add hl, bc
					ld  a, (__x)
					ld  (hl), a

					ld  hl, _breaking_y
					add hl, bc
					ld  a, (__y)
					ld  (hl), a

					ld  a, BREAKABLE_TILE
					ld  (__t), a
					
					// This identifier is too long for z88dk 1.10 XD
					// call _draw_invalidate_coloured_tile_gamearea
			#endasm

			draw_invalidate_coloured_tile_gamearea ();

			#asm
					ld  a, (_breaking_idx)
					inc a
					cp  MAX_BREAKABLE
					jr  nz, _break_wall_anim_prep_set

					xor a

				._break_wall_anim_prep_set
					ld  (_breaking_idx), a

					ld  a, 1
					ld  (_do_process_breakable), a
		
			#endasm
		#else
			// break this block.
			wall_broken ();
		#endif
	
		#ifdef MODE_128K
			_AY_PL_SND (SFX_BREAK_WALL);
		#else
			beep_fx (SFX_BREAK_WALL);
		#endif
	}
}
