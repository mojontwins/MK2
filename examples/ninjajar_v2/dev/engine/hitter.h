// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// hitter_h
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

	// Punching main code

	#ifdef PLAYER_CAN_PUNCH
		hitter_y = gpy + 6;
		if (p_facing) {
			hitter_x = gpx + hoffs_x [hitter_frame];
			hitter_n_f = sprite_20_a;
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_x = (hitter_x + 7) >> 4; 
			#endif
		} else {
			hitter_x = gpx + 8 - hoffs_x [hitter_frame];
			hitter_n_f = sprite_21_a;
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_x = (hitter_x) >> 4; 
			#endif
		}
		#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)			
			_y = (hitter_y + 3) >> 4;
			if (hitter_frame >= 1 && hitter_frame <= 3) 
				break_wall ();
		#endif		
	#endif

	// Sword main code

	#ifdef PLAYER_HAZ_SWORD
		if (p_up) {
			hitter_x = gpx + hoffs_y [hitter_frame];
			hitter_y = gpy + 6 - hoffs_x [hitter_frame];
			hitter_n_f = sprite_sword_u;
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_x = (hitter_x + 4) >> 4; _y = (hitter_y) >> 4;
			#endif		
		} else {
			hitter_y = gpy + hoffs_y [hitter_frame];
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_y = (hitter_y + 4) >> 4;
			#endif
			if (p_facing) {
				hitter_x = gpx + hoffs_x [hitter_frame];
				hitter_n_f = sprite_sword_r;
				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					_x = (hitter_x + 7) >> 4; 
				#endif
			} else {
				hitter_x = gpx + 8 - hoffs_x [hitter_frame];
				hitter_n_f = sprite_sword_l;
				#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
					_x = (hitter_x) >> 4; 
				#endif			
			}
		}
		#if defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)
			if (hitter_frame > 2 && hitter_frame < 7)
				break_wall ();
		#endif
	#endif

	// Whippo main code

	#ifdef PLAYER_HAZ_WHIP
		hitter_y = gpy + hoffs_y [hitter_frame];
		if (p_facing) {
			hitter_x = gpx + hoffs_x [hitter_frame];
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_x = (hitter_x + 15) >> 4; 
			#endif
		} else {
			hitter_x = gpx - hoffs_x [hitter_frame];
			#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
				_x = (hitter_x) >> 4; 
			#endif			
		}
		#if (defined (BREAKABLE_WALLS) || defined (BREAKABLE_WALLS_SIMPLE)) && defined (HITTER_BREAKS_WALLS)
			_y = (hitter_y + 3) >> 4;
			if (hitter_frame < 3) break_wall ();
		#endif
	#endif

	// End of main codes.

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
