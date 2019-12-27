
#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)	
	if ( (p_state & EST_PARP) == 0 || half_life == 0 ) {
		//sp_MoveSprAbs (sp_shadow, spritesClip, 0, VIEWPORT_Y + (gpy >> 3) + 1, VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
		#asm
				ld  ix, (_sp_shadow)
				ld  iy, vpClipStruct
				ld  bc, 0

				ld  a, (_gpy) 
				srl a
				srl a
				srl a
				inc a
				add VIEWPORT_Y
				ld  h, a 

				ld  a, (_gpx) 
				srl a
				srl a
				srl a
				add VIEWPORT_X
				ld  l, a

				ld  a, (_gpx) 
				and 7
				ld  d, a

				ld  a, (_gpy)
				and 7
				ld  e, a

				call SPMoveSprAbs
		#endasm
		gpz = gpy - ((-p_z) >> FIXBITS);
		//sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, VIEWPORT_Y + (gpz >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpz & 7);
		#asm
				ld  ix, (_sp_player)
				ld  iy, vpClipStruct

				ld  hl, (_p_n_f)
				ld  de, (_p_c_f)
				or  a
				sbc hl, de
				ld  b, h
				ld  c, l

				ld  a, (_gpz)
				srl a
				srl a
				srl a
				add VIEWPORT_Y
				ld  h, a 

				ld  a, (_gpx)
				srl a
				srl a
				srl a
				add VIEWPORT_X
				ld  l, a 
				
				ld  a, (_gpx)
				and 7
				ld  d, a

				ld  a, (_gpz)
				and 7
				ld  e, a

				call SPMoveSprAbs
		#endasm
	} else {
		//sp_MoveSprAbs (sp_shadow, spritesClip, 0, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_shadow)
				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm

		//sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_player)
				ld  iy, vpClipStruct

				ld  hl, (_p_n_f)
				ld  de, (_p_c_f)
				or  a
				sbc hl, de
				ld  b, h
				ld  c, l

				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm
		}
#else
	if ( (p_state & EST_PARP) == 0 || half_life == 0 ) {
		//sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, VIEWPORT_Y + (gpy >> 3), VIEWPORT_X + (gpx >> 3), gpx & 7, gpy & 7);
		#asm
				ld  ix, (_sp_player)
				ld  iy, vpClipStruct

				ld  hl, (_p_n_f)
				ld  de, (_p_c_f)
				or  a
				sbc hl, de
				ld  b, h
				ld  c, l

				ld  a, (_gpy)
				srl a
				srl a
				srl a
				add VIEWPORT_Y
				ld  h, a 

				ld  a, (_gpx)
				srl a
				srl a
				srl a
				add VIEWPORT_X
				ld  l, a 
				
				ld  a, (_gpx)
				and 7
				ld  d, a

				ld  a, (_gpy)
				and 7
				ld  e, a

				call SPMoveSprAbs
		#endasm
	} else {
		//sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_player)
				ld  iy, vpClipStruct

				ld  hl, (_p_n_f)
				ld  de, (_p_c_f)
				or  a
				sbc hl, de
				ld  b, h
				ld  c, l

				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm
	}
#endif

p_c_f = p_n_f;

#ifdef PLAYER_CAN_FIRE
	for (gpit = 0; gpit < MAX_BULLETS; gpit ++) {
		if (bullets_estado [gpit] == 1) {
			rdx = bullets_x [gpit]; rdy = bullets_y [gpit];
			//sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, VIEWPORT_Y + (bullets_y [gpit] >> 3), VIEWPORT_X + (bullets_x [gpit] >> 3), bullets_x [gpit] & 7, bullets_y [gpit] & 7);
			#asm
					ld  a, (_gpit)
					sla a
					ld  c, a
					ld  b, 0 				// BC = offset to [gpit] in 16bit arrays
					ld  hl, _sp_bullets
					add hl, bc
					ld  e, (hl)
					inc hl 
					ld  d, (hl)
					push de						
					pop ix

					ld  iy, vpClipStruct
					ld  bc, 0

					ld  a, (_rdy)
					srl a
					srl a
					srl a
					add VIEWPORT_Y
					ld  h, a

					ld  a, (_rdx)
					srl a
					srl a
					srl a
					add VIEWPORT_X
					ld  l, a

					ld  a, (_rdx)
					and 7
					ld  d, a 

					ld  a, (_rdy)
					and 7
					ld  e, a 
					
					call SPMoveSprAbs
			#endasm
		} else {
			//sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
			#asm
					ld  a, (_gpit)
					sla a
					ld  c, a
					ld  b, 0 				// BC = offset to [gpit] in 16bit arrays
					ld  hl, _sp_bullets
					add hl, bc
					ld  e, (hl)
					inc hl 
					ld  d, (hl)
					push de						
					pop ix

					ld  iy, vpClipStruct
					ld  bc, 0

					ld  hl, 0xfefe
					ld  de, 0 
					
					call SPMoveSprAbs
			#endasm
		}
	}
#endif
