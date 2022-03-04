// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// hitter-asm.h
// Hitter (punch/sword/whip) helper functions

#ifdef PLAYER_CAN_PUNCH
	//								H   H   H
	unsigned char hoffs_x [] = {12, 14, 16, 16, 12};
	#define HITTER_MAX_FRAME 5
#endif

#ifdef PLAYER_HAZ_SWORD
	//                                     H   H   H   H
	unsigned char hoffs_x [] = {8, 10, 12, 14, 15, 15, 14, 13, 10};
	unsigned char hoffs_y [] = {2,  2,  2, 3,  4,  4,  5,  6,  7};
	#define HITTER_MAX_FRAME 9
#endif

#ifdef PLAYER_HAZ_WHIP
	//                          H  H   H
	unsigned char hoffs_x [] = {8, 16, 16, 12, 8,  4, 0};
	unsigned char hoffs_y [] = {4, 4,  4,  6,  8, 10, 12};
	#define HITTER_MAX_FRAME 7
#endif

void hitter_render (void) {
	#ifdef PLAYER_CAN_PUNCH
		#asm
				ld  a, (_gpy)
				add 6
				ld  (_hitter_y), a

				ld  bc, (_hitter_frame)
				ld  b, 0
				ld  hl, _hoffs_x
				add hl, bc
				ld  c, (hl)

				ld  a, (_p_facing)
				or  a
				jr  z, _hitter_render_facing_left

			._hitter_render_facing_right
				ld  a, (_gpx)
				add c
				ld  (_hitter_x), a

				ld  hl, _sprite_20_a
				ld  (_hitter_n_f), hl

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					add 7
					srl a
					srl a
					srl a
					srl a
					ld  (__x), a
				#endif

				jr  _hitter_render_facing_done

			._hitter_render_facing_left
				ld  a, (_gpx)
				add 8
				sub c
				ld  (_hitter_x), a

				ld  hl, _sprite_21_a
				ld  (_hitter_n_f), hl

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					srl a
					srl a
					srl a
					srl a
					ld  (__x), a
				#endif

			._hitter_render_facing_done

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
						ld  a, (_hitter_y)
						add 3
						srl a
						srl a
						srl a
						srl a
						ld  (__y), a

						// if (hitter_frame >= 1 && hitter_frame <= 3)

						// hitter_frame >= 1
						ld  a, (_hitter_frame)
						cp  1
						jr  c, _hitter_break_tile_done

						// hitter_frame <= 3 -> hitter_frame < 4
						cp  4
						jr  nc, _hitter_break_tile_done

						call _break_wall

				._hitter_break_tile_done

				#endif
		#endasm
	#endif

	#ifdef PLAYER_HAZ_SWORD
		#asm
				ld  de, (_hitter_frame)
				ld  d, 0

				ld  hl, _hoffs_y
				add hl, de
				ld  b, (hl) 			; B = hoffs_y [hitter_frame]

				ld  hl, _hoffs_x
				add hl, de
				ld  c, (hl) 			; C = hoffs_x [hitter_frame]

				ld  a, (_p_up)
				or  a
				jr  z, _hitter_side

			._hitter_up
				ld  a, (_gpx)
				add b
				ld  (_hitter_x), a 		; hitter_x = gpx + hoffs_y [hitter_frame]

				ld  a, (_gpy)
				add 6
				sub c
				ld  (_hitter_y), a 		; hitter_y = gpy + 6 - hoffs_x [hitter_frame]

				ld  hl, _sprite_sword_u
				ld  (_hitter_n_f), hl

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					add 4
					srl a 
					srl a 
					srl a 
					srl a 
					ld  (__x), a

					ld  a, (_hitter_y)					
					srl a 
					srl a 
					srl a 
					srl a 
					ld  (__y), a
				#endif

				jp  _hitter_render_facing_done

			._hitter_side
				ld  a, (_gpy)
				add b
				ld  (_hitter_y), a 		; hitter_y = gpy + hoffs_y [hitter_frame]

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_y)
					add 4
					srl a 
					srl a 
					srl a 
					srl a 
					ld  (__y), a
				#endif

				ld  a, (_p_facing)
				or  a
				jr  z, _hitter_render_facing_left

			._hitter_render_facing_right
				ld  a, (_gpx)
				add c
				ld  (_hitter_x), a 		; hitter_x = gpx + hoffs_x [hitter_frame]

				ld  hl, _sprite_sword_r
				ld  (_hitter_n_f), hl

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					add 7
					srl a 
					srl a 
					srl a 
					srl a 
					ld  (__x), a
				#endif	

				jr _hitter_render_facing_done

			._hitter_render_facing_left
				ld  a, (_gpx)
				add 8
				sub c
				ld  (_hitter_x), a 		; hitter_x = gpx + 8 - hoffs_x [hitter_frame]

				ld  hl, _sprite_sword_l
				ld  (_hitter_n_f), hl

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					srl a 
					srl a 
					srl a 
					srl a 
					ld  (__x), a
				#endif	

			._hitter_render_facing_done

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
						ld  a, (_hitter_y)
						add 3
						srl a
						srl a
						srl a
						srl a
						ld  (__y), a

						// if (hitter_frame > 2 && hitter_frame < 7)

						// hitter_frame > 2 => hitter_frame >= 3
						ld  a, (_hitter_frame)
						cp  3
						jr  c, _hitter_break_tile_done

						// hitter_frame < 7
						cp  7
						jr  nc, _hitter_break_tile_done

						call _break_wall

				._hitter_break_tile_done

				#endif

		#endasm
	#endif

	#ifdef PLAYER_HAZ_WHIP
		#asm
				ld  de, (_hitter_frame)
				ld  d, 0
				
				ld  hl, _hoffs_y
				add hl, de
				ld  c, (hl)

				ld  a, (_gpy)
				add c
				ld  (_hitter_y), a

				ld  hl, _hoffs_x
				add hl, de
				ld  c, (hl)

				ld  a, (_p_facing)
				or  a
				jr  z, _hitter_render_facing_left

			._hitter_render_facing_right
				ld  a, (_gpx)
				add c
				ld  (_hitter_x), a

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					add 15
					srl a
					srl a
					srl a
					srl a
					ld  (__x), a
				#endif

				jr  _hitter_render_facing_done

			._hitter_render_facing_left
				ld  a, (_gpx)
				sub c
				ld  (_hitter_x), a

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					ld  a, (_hitter_x)
					srl a
					srl a
					srl a
					srl a
					ld  (__x), a
				#endif

			._hitter_render_facing_done

				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
						ld  a, (_hitter_y)
						add 3
						srl a
						srl a
						srl a
						srl a
						ld  (__y), a

						// if (hitter_frame < 3)
						ld  a, (_hitter_frame)
						cp  3
						jr  nc, _hitter_break_tile_done

						call _break_wall

				._hitter_break_tile_done

				#endif
		#endasm
	#endif

	// Now paint

	/*
		sp_MoveSprAbs (sp_hitter, spritesClip,
			hitter_n_f - hitter_c_f,
			VIEWPORT_Y + (hitter_y >> 3), VIEWPORT_X + (hitter_x >> 3),
			hitter_x & 7, hitter_y & 7);
		hitter_c_f = hitter_n_f;
	*/
	#asm
		; enter: IX = sprite structure address 
		;        IY = clipping rectangle, set it to "ClipStruct" for full screen 
		;        BC = animate bitdef displacement (0 for no animation) 
		;         H = new row coord in chars 
		;         L = new col coord in chars 
		;         D = new horizontal rotation (0..7) ie horizontal pixel position 
		;         E = new vertical rotation (0..7) ie vertical pixel position 

		ld  ix, (_sp_hitter)
		ld  iy, vpClipStruct
		
		ld  hl, (_hitter_n_f)
		ld  de, (_hitter_c_f)
		or  a
		sbc hl, de
		ld  b, h
		ld  c, l

		ld  a, (_hitter_y)
		srl a 
		srl a 
		srl a 
		add VIEWPORT_Y
		ld  h, a

		ld  a, (_hitter_x)
		srl a 
		srl a 
		srl a 
		add VIEWPORT_X
		ld  l, a

		ld  a, (_hitter_x)
		and 7
		ld  d, a

		ld  a, (_hitter_y)
		and 7
		ld  e, a
		
		call SPMoveSprAbs

		ld  hl, (_hitter_n_f)
		ld  (_hitter_c_f), hl
	#endasm

	hitter_frame ++;
	if (hitter_frame == HITTER_MAX_FRAME) {
		hitter_on = 0;
		// sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
		#asm
			ld  ix, (_sp_hitter)
			ld  iy, vpClipStruct
			ld  bc, 0
			ld  hl, 0xfefe
			ld  de, 0
			call SPMoveSprAbs
		#endasm
		p_hitting = 0;
	}			
}
