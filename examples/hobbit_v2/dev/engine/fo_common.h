// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// Floating objects
// Common functions (included from fo_genital and fo_sideview)

unsigned char f_o_t [MAX_FLOATING_OBJECTS];
unsigned char f_o_x [MAX_FLOATING_OBJECTS];
unsigned char f_o_y [MAX_FLOATING_OBJECTS];
unsigned char f_o_s [MAX_FLOATING_OBJECTS];

unsigned char fo_it, fo_gp, fo_au, d_prs = 0;
unsigned char fo_idx;
unsigned char fo_x, fo_y, fo_st;
#ifdef CARRIABLE_BOXES_THROWABLE
	unsigned char fo_fly = 99, f_o_xp, f_o_yp;
	signed char f_o_mx;

	void draw_box_sprite (void) {
		// sp_MoveSprAbs (sp_carriable, spritesClip, 0, VIEWPORT_Y + (f_o_yp >> 3), VIEWPORT_X + (f_o_xp >> 3), f_o_xp & 7, f_o_yp & 7);
		#asm
			; enter: IX = sprite structure address 
			;        IY = clipping rectangle, set it to "ClipStruct" for full screen 
			;        BC = animate bitdef displacement (0 for no animation) 
			;         H = new row coord in chars 
			;         L = new col coord in chars 
			;         D = new horizontal rotation (0..7) ie horizontal pixel position 
			;         E = new vertical rotation (0..7) ie vertical pixel position

			ld  ix, (_sp_carriable)
			ld  iy, vpClipStruct
			ld  bc, 0

			ld  a, _f_o_yp
			srl a
			srl a
			srl a
			add VIEWPORT_Y
			ld  h, a

			ld  a, _f_o_xp
			srl a
			srl a
			srl a
			add VIEWPORT_X
			ld  l, a
			
			ld  a, _f_o_xp
			and 7
			ld  d, a 

			ld  a, _f_o_yp
			and 7
			ld  e, a 
			
			call SPMoveSprAbs
		#endasm
	}
#endif

#ifdef ENABLE_FO_CARRIABLE_BOXES
	void delete_box_sprite (void) {
		// sp_MoveSprAbs (sp_carriable, spritesClip, 0, -2, -2, 0, 0);
		#asm
			; enter: IX = sprite structure address 
			;        IY = clipping rectangle, set it to "ClipStruct" for full screen 
			;        BC = animate bitdef displacement (0 for no animation) 
			;         H = new row coord in chars 
			;         L = new col coord in chars 
			;         D = new horizontal rotation (0..7) ie horizontal pixel position 
			;         E = new vertical rotation (0..7) ie vertical pixel position

			ld  ix, (_sp_carriable)
			ld  iy, vpClipStruct
			ld  bc, 0
			ld  hl, 0xfefe
			ld  de, 0

			call SPMoveSprAbs
		#endasm
	}
#endif

void FO_clear (void) {
	fo_it = 0;
	while (fo_it < MAX_FLOATING_OBJECTS) f_o_t [fo_it ++] = 0;
	fo_idx = 0;
	#ifdef ENABLE_FO_CARRIABLE_BOXES
		p_hasbox = 99;
		#ifdef CARRIABLE_BOXES_ALTER_JUMP
			PLAYER_JMP_VY_MAX = PLAYER_JMP_VY_MAX;
		#endif
		#ifdef CARRIABLE_BOXES_THROWABLE
			fo_fly = 0;
		#endif
	#endif
	#ifdef CARRIABLE_BOXES_THROWABLE
		delete_box_sprite ();
	#endif
	#ifdef ENABLE_FO_SCRIPTING
		flags [FO_T_FLAG] = 0;
	#endif
}

unsigned char FO_add (unsigned char x, unsigned char y, unsigned char t) {
	f_o_t [fo_idx] = t;
	f_o_x [fo_idx] = x;
	f_o_y [fo_idx] = y;
	f_o_s [fo_idx] = 0;
	fo_idx ++;
	return fo_idx - 1;
}

void FO_paint (unsigned char idx) {
	fo_au = f_o_t [idx];
	#ifdef ENABLE_FO_OBJECT_CONTAINERS
		if (fo_au & 128) fo_au = flags [fo_au & 127];
	#endif
	#ifndef SHOW_EMPTY_CONTAINER
		if (fo_au == 0) return;
	#endif
	
	#if FT_FIREZONES == 48
		if (fo_au == FT_FIREZONES) return;
	#endif

	#ifdef SHOW_EMPTY_CONTAINER
		_x = f_o_x [idx]; _y = f_o_y [idx]; _t = fo_au ? fo_au : ITEM_EMPTY;
		draw_invalidate_coloured_tile_gamearea ();
	#else
		_x = f_o_x [idx]; _y = f_o_y [idx]; _t = fo_au;
		draw_invalidate_coloured_tile_gamearea ();
	#endif
	
	// Bit 7 marks this block as "floating". That way the player movement routine can identify it
	// and will never store this location as a "safe" one.
	map_attr [BUFFER_IDX (f_o_x [idx], f_o_y [idx])] = behs [fo_au] | 128;
}

void FO_unpaint (unsigned char idx) {
	fo_au = BUFFER_IDX (f_o_x [idx], f_o_y [idx]);
	_x = f_o_x [idx]; _y = f_o_y [idx]; _t = map_buff [fo_au];
	draw_invalidate_coloured_tile_gamearea ();
	map_attr [fo_au] = behs [map_buff [fo_au]];
}

void FO_paint_all (void) {
	fo_it = 0;
	while (fo_it < MAX_FLOATING_OBJECTS) {
		#ifdef ENABLE_FO_CARRIABLE_BOXES
			if (f_o_t [fo_it] && fo_it != p_hasbox) FO_paint (fo_it);
		#else
			if (f_o_t [fo_it]) FO_paint (fo_it);
		#endif
		fo_it ++;
	}
}

#ifdef ENABLE_SIM
	void sim_check (void);
#endif
