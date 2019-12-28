void hide_sprites (unsigned char which_ones) {
	if (which_ones == 0) {
		// sp_MoveSprAbs (sp_player, spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
		#asm
			ld  ix, (_sp_player)
			ld  iy, vpClipStruct
			ld  bc, 0
			ld  hl, 0xdede
			ld  de, 0
			call SPMoveSprAbs
		#endasm
	}

	/*
	for (gpit = 0; gpit < 3; gpit ++)
		sp_MoveSprAbs (sp_moviles [gpit], spritesClip, 0, VIEWPORT_Y + 30, VIEWPORT_X + 20, 0, 0);
	*/
	#asm
			xor a
		.hide_sprites_enems_loop
			ld  (_gpit), a

			sla a
			ld  c, a
			ld  b, 0
			ld  hl, _sp_moviles
			add hl, bc
			ld  e, (hl)
			inc hl
			ld  d, (hl)
			push de
			pop ix

			ld  iy, vpClipStruct
			ld  bc, 0
			ld  hl, 0xfefe	// -2, -2
			ld  de, 0

			call SPMoveSprAbs

			ld  a, (_gpit)
			inc a
			cp  3
			jr  nz, hide_sprites_enems_loop
	#endasm

	#ifdef PLAYER_CAN_FIRE
		/*
		for (gpit = 0; gpit < MAX_BULLETS; gpit ++)
			sp_MoveSprAbs (sp_bullets [gpit], spritesClip, 0, -2, -2, 0, 0);
		*/
		#asm
				xor a
			.hide_sprites_bullets_loop
				ld  (_gpit), a

				sla a
				ld  c, a
				ld  b, 0
				ld  hl, _sp_bullets
				add hl, bc
				ld  e, (hl)
				inc hl
				ld  d, (hl)
				push de
				pop ix

				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe	// -2, -2
				ld  de, 0

				call SPMoveSprAbs

				ld  a, (_gpit)
				inc a
				cp  MAX_BULLETS
				jr  nz, hide_sprites_bullets_loop
		#endasm
	#endif

	#ifdef ENABLE_SHOOTERS
		/*
		for (gpit = 0; gpit < MAX_COCOS; gpit ++)
			sp_MoveSprAbs (sp_cocos [gpit], spritesClip, 0, -2, -2, 0, 0);
		*/
		#asm
				xor a
			.hide_sprites_cocos_loop
				ld  (_gpit), a

				sla a
				ld  c, a
				ld  b, 0
				ld  hl, _sp_cocos
				add hl, bc
				ld  e, (hl)
				inc hl
				ld  d, (hl)
				push de
				pop ix

				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe	// -2, -2
				ld  de, 0

				call SPMoveSprAbs

				ld  a, (_gpit)
				inc a
				cp  3
				jr  nz, hide_sprites_cocos_loop
		#endasm
	#endif

	#if defined (PLAYER_CAN_PUNCH) || defined (PLAYER_HAZ_SWORD) || defined (PLAYER_HAZ_WHIP)
		// sp_MoveSprAbs (sp_hitter, spritesClip, 0, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_hitter)
				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm
	#endif
	
	#ifdef ENABLE_FO_CARRIABLE_BOXES
		// sp_MoveSprAbs (sp_carriable, spritesClip, 0, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_carriable)
				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm
	#endif
	
	#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
		// sp_MoveSprAbs (sp_shadow, spritesClip, 0, -2, -2, 0, 0);
		#asm
				ld  ix, (_sp_shadow)
				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe
				ld  de, 0
				call SPMoveSprAbs
		#endasm
	#endif
}
