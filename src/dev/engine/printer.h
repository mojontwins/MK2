// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// printer.h
// Printing functions

#define MESSAGE_COLOUR 87
unsigned char *spacer = "            ";

#ifdef DEBUG
	unsigned char get_hex_digit (unsigned char v) {
		v = v & 0xf;
		return v < 10 ? 16 + v : 23 + v;
	}

	unsigned char debug_print_16bits (unsigned char x, unsigned char y, unsigned int var) {
		sp_PrintAtInv (y, x, 7, get_hex_digit (var >> 12));
		sp_PrintAtInv (y, x + 1, 7, get_hex_digit (var >> 8));
		sp_PrintAtInv (y, x + 2, 7, get_hex_digit (var >> 4));
		sp_PrintAtInv (y, x + 3, 7, get_hex_digit (var));
		sp_UpdateNow ();
	}
#endif

unsigned char attr (char x, char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	if (x < 0 || y < 0 || x > 14 || y > 9) return 0;
	return map_attr [x + (y << 4) - y];
}

unsigned char qtile (unsigned char x, unsigned char y) {
	// x + 15 * y = x + (16 - 1) * y = x + 16 * y - y = x + (y << 4) - y.
	return map_buff [x + (y << 4) - y];
}

#ifdef UNPACKED_MAP
	// Draw unpacked tile

	void draw_coloured_tile (void) {
		/*
		_t = 64 + (_t << 2);
		gen_pt = tileset + 2048 + _t;
		sp_PrintAtInv (_y, _x, *gen_pt ++, _t ++);
		sp_PrintAtInv (_y, _x + 1, *gen_pt ++, _t ++);
		sp_PrintAtInv (_y + 1, _x, *gen_pt ++, _t ++);
		sp_PrintAtInv (_y + 1, _x + 1, *gen_pt, _t);
		*/
		// Calculate address in the display list

			ld  a, (__x)
			ld  c, a
			ld  a, (__y)
			call SPCompDListAddr
			ex de, hl

			// Now write 4 attributes and 4 chars.

			// Make a pointer to the metatile colour array	
			ld  a, (__t)
			sla a
			sla a 				// A = _t * 4
	
			ld  hl, _tileset + 2048
			ld  b, 0
			ld  c, a
			add hl, bc 			// HL = metatile_attrs + _taux

			add 64 				// A = _t * 4 + 64
			ld  c, a 			// C = current pattern #

			// For each char: write colour, inc DE, write tile, inc DE*3
			
			ld  a, (hl) 		// read colour			
			ld  (de), a 		// write colour
			inc de
			inc hl 				// next colour

			ld  a, c  			// read tile
			ld  (de), a			// write tile
			inc de
			inc a 				// next tile
			ld  c, a 

			inc de
			inc de 				// next DisplayList cell

			ld  a, (hl) 		// read colour			
			ld  (de), a 		// write colour
			inc de
			inc hl 				// next colour

			ld  a, c  			// read tile
			ld  (de), a			// write tile
			inc a 				// next tile
			
			ex  de, hl
			ld  bc, 123
			add hl, bc
			ex  de, hl			// next DisplayList cell
			ld  c, a 

			ld  a, (hl) 		// read colour			
			ld  (de), a 		// write colour
			inc de
			inc hl 				// next colour

			ld  a, c  			// read tile
			ld  (de), a			// write tile
			inc de
			inc a 				// next tile
			ld  c, a 

			inc de
			inc de 				// next DisplayList cell

			ld  a, (hl) 		// read colour			
			ld  (de), a 		// write colour
			inc de

			ld  a, c  			// read tile
			ld  (de), a			// write tile
	#endasm
	}

#else
	// Draw packed tile

	#ifdef USE_AUTO_TILE_SHADOWS
		unsigned char *gen_pt_alt;
		unsigned char t_alt;
	#endif
	unsigned char xx, yy;
	void draw_coloured_tile (void) {
		#ifdef USE_AUTO_SHADOWS
			xx = (_x - VIEWPORT_X) >> 1;
			yy = (_y - VIEWPORT_Y) >> 1;
			if (!(attr (xx, yy) & 8) && (_t < 16 || _t == 19)) {
				_t = 64 + (_t << 2);
				gen_pt = tileset + 2048 + _t;
				sp_PrintAtInv (_y, _x, attr (xx - 1, yy - 1) & 8 ? (gen_pt[0] & 7)-1 : gen_pt [0], _t);
				sp_PrintAtInv (_y, _x + 1, attr (xx, yy - 1) & 8 ? (gen_pt[1] & 7)-1 : gen_pt [1], _t + 1);
				sp_PrintAtInv (_y + 1, _x, attr (xx - 1, yy) & 8 ? (gen_pt[2] & 7)-1 : gen_pt [2], _t + 2);
				sp_PrintAtInv (_y + 1, _x + 1, gen_pt [3], _t + 3);
			} else 
		#elif defined (USE_AUTO_TILE_SHADOWS)
			xx = (_x - VIEWPORT_X) >> 1;
			yy = (_y - VIEWPORT_Y) >> 1;
			if (!(attr (xx, yy) & 8) && (_t < 16 || _t == 19)) {
				_t = 64 + (_t << 2);
				if (_t == 140) {
					gen_pt = (unsigned char *) &tileset [2188];
					t_alt = 192;
					gen_pt_alt = (unsigned char *) &tileset [2048 + 192];
				} else {
					gen_pt = (unsigned char *) &tileset [2048 + _t];
					t_alt = 128 + _t;
					gen_pt_alt = (unsigned char *) &tileset [2048 + _t + 128];
				}

				if (attr (xx - 1, yy - 1) & 8) {
					sp_PrintAtInv (_y, _x, gen_pt_alt [0], t_alt);
				} else {
					sp_PrintAtInv (_y, _x, gen_pt [0], _t);
				}
				if (attr (xx, yy - 1) & 8) {
					sp_PrintAtInv (_y, _x + 1, gen_pt_alt [1], t_alt + 1);
				} else {
					sp_PrintAtInv (_y, _x + 1, gen_pt [1], _t + 1);
				}
				if (attr (xx - 1, yy) & 8) {
					sp_PrintAtInv (_y + 1, _x, gen_pt_alt [2], t_alt + 2);
				} else {
					sp_PrintAtInv (_y + 1, _x, gen_pt [2], _t + 2);
				}
				sp_PrintAtInv (_y + 1, _x + 1, gen_pt [3], _t + 3);
			} else
		#endif
		{
			_t = 64 + (_t << 2);
			gen_pt = tileset + 2048 + _t;
			sp_PrintAtInv (_y, _x, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y, _x + 1, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y + 1, _x, *gen_pt ++, _t ++);
			sp_PrintAtInv (_y + 1, _x + 1, *gen_pt, _t);
		}
	}
#endif

void invalidate_tile (void) {
	#asm
			; Invalidate Rectangle
			;
			; enter:  B = row coord top left corner
			;         C = col coord top left corner
			;         D = row coord bottom right corner
			;         E = col coord bottom right corner
			;        IY = clipping rectangle, set it to "ClipStruct" for full screen

			ld  a, (__x)
			inc a
			ld  e, a
			ld  a, (__y)
			inc a
			ld  d, a
			ld  a, (__x)
			ld  c, a
			ld  a, (__y)
			ld  iy, vpClipStruct
			call SPInvalidate
			
	#endasm
}

void invalidate_viewport (void) {
	#asm
			; Invalidate Rectangle
			;
			; enter:  B = row coord top left corner
			;         C = col coord top left corner
			;         D = row coord bottom right corner
			;         E = col coord bottom right corner
			;        IY = clipping rectangle, set it to "ClipStruct" for full screen

			ld  b, VIEWPORT_Y
			ld  c, VIEWPORT_X
			ld  d, VIEWPORT_Y+19
			ld  e, VIEWPORT_X+29
			ld  iy, vpClipStruct
			call SPInvalidate
	#endasm
}

void draw_invalidate_coloured_tile_gamearea (void) {
	draw_coloured_tile_gamearea ();
	invalidate_tile ();
}

void draw_coloured_tile_gamearea (void) {
	_x = VIEWPORT_X + (_x << 1); _y = VIEWPORT_Y + (_y << 1); draw_coloured_tile ();
}

void print_number2 (unsigned char x, unsigned char y, unsigned char number) {
	sp_PrintAtInv (y, x, 7, 16 + (number / 10));
	sp_PrintAtInv (y, x + 1, 7, 16 + (number % 10));
}

#ifndef DEACTIVATE_OBJECTS
	void draw_objs () {
		#if defined (ONLY_ONE_OBJECT) && defined (ACTIVATE_SCRIPTING)
			if (p_objs) {
				sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X, 135, 132);
				sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X + 1, 135, 133);
				sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X, 135, 134);
				sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X + 1, 135, 135);
			} else {
				_x = OBJECTS_ICON_X; _y = OBJECTS_ICON_Y; _t = 17; 

				draw_coloured_tile ();
				invalidate_tile ();
			}
			print_number2 (OBJECTS_X, OBJECTS_Y, flags [OBJECT_COUNT]);
		#else
			print_number2 (OBJECTS_X, OBJECTS_Y, p_objs);
		#endif
	}
#endif

void print_str (unsigned char x, unsigned char y, unsigned char c, unsigned char *s) {
	while (*s) sp_PrintAtInv (y, x ++, c, (*s ++) - 32);
}

#if defined (COMPRESSED_LEVELS) || defined (SHOW_LEVEL_ON_SCREEN)
	void blackout_area (void) {
		// blackens gameplay area for LEVEL XX display
		asm_int = 22528 + 32 * VIEWPORT_Y + VIEWPORT_X;
		#asm
			/*
			ld	hl, _asm_int
			ld	a, (hl)
			ld	e, a
			inc	hl
			ld	a, (hl)
			ld	d, a
			*/
			ld  de, (_asm_int)
			ld  b, 20
		.bal1
			push bc
			ld  h, d 
			ld  l, e
			ld	(hl), 0
			inc de
			ld  bc, 29
			ldir
			inc de
			inc de
			pop bc
			djnz bal1
		#endasm
	}
#endif

unsigned char utaux = 0;
void update_tile (void) {
	/*
	utaux = (_y << 4) - _y + _x;
	map_attr [utaux] = _n;
	map_buff [utaux] = _t;
	draw_invalidate_coloured_tile_gamearea ();
	*/
	#asm
		ld  a, (__x)
		ld  c, a
		ld  a, (__y)
		ld  b, a
		sla a 
		sla a 
		sla a 
		sla a 
		sub b
		add c
		ld  b, 0
		ld  c, a
		ld  hl, _map_attr
		add hl, bc
		ld  a, (__n)
		ld  (hl), a
		ld  hl, _map_buff
		add hl, bc
		ld  a, (__t)
		ld  (hl), a

		call _draw_coloured_tile_gamearea

		ld  a, (_is_rendering)
		or  a
		ret nz

		call _invalidate_tile
	#endasm
}

void print_message (unsigned char *s) {
	print_str (10, 11, MESSAGE_COLOUR, spacer);
	print_str (10, 12, MESSAGE_COLOUR, s);
	print_str (10, 13, MESSAGE_COLOUR, spacer);
	sp_UpdateNow ();
	sp_WaitForNoKey ();
}

unsigned char button_pressed (void) {
	return (sp_GetKey () || ((((joyfunc) (&keys)) & sp_FIRE) == 0));
}

#if defined (ENABLE_HOLES)
	void main_spr_frame (unsigned char x, unsigned char y) {
		gpx = x; gpy = y;
		//sp_MoveSprAbs (sp_player, spritesClip, p_n_f - p_c_f, VIEWPORT_Y + (y >> 3), VIEWPORT_X + (x >> 3), x & 7, y & 7);
		//p_c_f = p_n_f;
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

			ld  hl, (_p_n_f)
			ld  (_p_c_f), hl 
		#endasm
		sp_UpdateNow ();
	}
#endif

#ifdef ENABLE_SUBTILESETS
	// Subtileset loader
	unsigned int offs_attr, offs_behs;
	unsigned char load_subtileset (unsigned char res, unsigned char n) {
		// Get offsets
		offs_attr = read_offset (res, 0);
		offs_behs = read_offset (res, 2);

		// Unpack patterns
		unpack_RAMn (resources [res].ramPage, resources [res].ramOffset + 4, (unsigned int) (tileset + (n << 9) + 512));
		// Unpack attributes
		unpack_RAMn (resources [res].ramPage, resources [res].ramOffset + offs_attr, (unsigned int) (tileset + (n << 6) + 2112));
		// Unpack behs
		unpack_RAMn (resources [res].ramPage, resources [res].ramOffset + offs_behs, (unsigned int) (behs + (n << 4)));
	}
#endif
