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

void draw_coloured_tile (void) {
	#if defined (USE_AUTO_TILE_SHADOWS) || defined (USE_AUTO_SHADOWS)		
		#asm
			// Undo screen coordinates -> buffer coordinates
				ld  a, (__x)
				sub VIEWPORT_X
				srl a
				ld  (_xx), a

				ld  a, (__y)
				sub VIEWPORT_Y
				srl a
				ld  (_yy), a
		#endasm

		// Nocast for tiles which never get shadowed
		cx1 = xx; cy1 = yy; nocast = !((attr () & 8) || (_t >= 16 && _t != 19));

		// Precalc 
		#asm
				ld  a, (__t)
				sla a 
				sla a 
				add 64
				ld  (__ta), a

				ld  hl, _tileset + 2048
				ld  b, 0
				ld  c, a
				add hl, bc
				ld  (_gen_pt), hl
		#endasm

		// Fill up c1, c2, c3, c4 then use them
		#ifdef USE_AUTO_SHADOWS			
			cx1 = xx - 1; cy1 = yy - 1; rda = *gen_pt; c1 = (nocast && (attr () & 8)) ? (rda & 7) - 1 : rda; t1 = _ta; ++ gen_pt; ++ _ta;
			cx1 = xx    ; cy1 = yy - 1; rda = *gen_pt; c2 = (nocast && (attr () & 8)) ? (rda & 7) - 1 : rda; t2 = _ta; ++ gen_pt; ++ _ta;
			cx1 = xx - 1; cy1 = yy    ; rda = *gen_pt; c3 = (nocast && (attr () & 8)) ? (rda & 7) - 1 : rda; t3 = _ta; ++ gen_pt; ++ _ta;			
		#endif
		#ifdef USE_AUTO_TILE_SHADOWS
			// Precalc
			
			if (_t == 19) {
				#asm
					ld  hl, _tileset + 2048 + 192
					ld  (_gen_pt_alt), hl
				#endasm
				t_alt = 192;
			} else {
				#asm
					ld  hl, _tileset + 2048 + 128
					ld  de, (__ta)
					ld  d, 0
					add hl, de
					ld  (_gen_pt_alt), hl
				#endasm
				t_alt = 128 + _ta;
			}
			
			gen_pt_alt = tileset + 2048 + t_alt;

			// cx1 = xx - 1; cy1 = yy ? yy - 1 : 0; a1 = (nocast && (attr () & 8));
			#asm
				// cx1 = xx - 1; 
					ld  a, (_xx)
					dec a
					ld  (_cx1), a

				// cy1 = yy ? yy - 1 : 0;
					ld  a, (_yy)
					or  a
					jr  z, _dct_1_set_yy
					dec a
				._dct_1_set_yy
					ld  (_cy1), a

				// a1 = (nocast && (attr () & 8));
					ld  a, (_nocast)
					or  a
					jr  z, _dct_a1_set

					call _attr
					ld  a, l
					and 8
					jr  z, _dct_a1_set

					ld  a, 1

				._dct_a1_set
					ld  (_a1), a
			#endasm			

			// cx1 = xx    ; cy1 = yy ? yy - 1 : 0; a2 = (nocast && (attr () & 8));
			#asm
									// cx1 = xx; 
					ld  a, (_xx)					
					ld  (_cx1), a

				// cy1 = yy ? yy - 1 : 0;
					ld  a, (_yy)
					or  a
					jr  z, _dct_2_set_yy
					dec a
				._dct_2_set_yy
					ld  (_cy1), a

				// a2 = (nocast && (attr () & 8))
					ld  a, (_nocast)
					or  a
					jr  z, _dct_a2_set

					call _attr
					ld  a, l
					and 8
					jr  z, _dct_a2_set

					ld  a, 1

				._dct_a2_set
					ld  (_a2), a
			#endasm

			// cx1 = xx - 1; cy1 = yy             ; a3 = (nocast && (attr () & 8));
			#asm
					// cx1 = xx - 1; 
					ld  a, (_xx)
					dec a
					ld  (_cx1), a

				// cy1 = yy;
					ld  a, (_yy)					
					ld  (_cy1), a

				// a3 = (nocast && (attr () & 8));
					ld  a, (_nocast)
					or  a
					jr  z, _dct_a3_set

					call _attr
					ld  a, l
					and 8
					jr  z, _dct_a3_set

					ld  a, 1

				._dct_a3_set
					ld  (_a3), a
			#endasm

			/*
			if (a1 || (a2 && a3)) { c1 = *gen_pt_alt; t1 = t_alt; }
				else { c1 = *gen_pt; t1 = _ta; }
			++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;
			*/
			#asm
					ld  a, (_a1)
					or  a
					jr  nz, _dct_1_shadow

					ld  a, (_a2)
					or  a
					jr  z, _dct_1_no_shadow

					ld  a, (_a3)
					or  a
					jr  z, _dct_1_no_shadow

				._dct_1_shadow
				// { c1 = *gen_pt_alt; t1 = t_alt; }
					ld  hl, (_gen_pt_alt)
					ld  a, (hl)
					ld  (_c1), a

					ld  a, (_t_alt)
					ld  (_t1), a

					jr  _dct_1_increment
				
				._dct_1_no_shadow
				// else { c1 = *gen_pt; t1 = _ta; }
					ld  hl, (_gen_pt)
					ld  a, (hl)
					ld  (_c1), a

					ld  a, (__ta)
					ld  (_t1), a

				._dct_1_increment
				// ++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;
					ld  hl, (_gen_pt)
					inc hl
					ld  (_gen_pt), hl

					ld  hl, (_gen_pt_alt)
					inc hl
					ld  (_gen_pt_alt), hl

					ld  hl, __ta
					inc (hl)

					ld  hl, _t_alt
					inc (hl)
			#endasm 

			/*		
			if (a2) { c2 = *gen_pt_alt; t2 = t_alt; }
				else { c2 = *gen_pt; t2 = _ta; }
			++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;
			*/
			#asm
					ld  a, (_a2)
					or  a
					jr  z, _dct_2_no_shadow

				._dct_2_shadow
				// { c1 = *gen_pt_alt; t1 = t_alt; }
					ld  hl, (_gen_pt_alt)
					ld  a, (hl)
					ld  (_c2), a

					ld  a, (_t_alt)
					ld  (_t2), a

					jr  _dct_2_increment
				
				._dct_2_no_shadow
				// else { c1 = *gen_pt; t1 = _ta; }
					ld  hl, (_gen_pt)
					ld  a, (hl)
					ld  (_c2), a

					ld  a, (__ta)
					ld  (_t2), a

				._dct_2_increment
				// ++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;
					ld  hl, (_gen_pt)
					inc hl
					ld  (_gen_pt), hl

					ld  hl, (_gen_pt_alt)
					inc hl
					ld  (_gen_pt_alt), hl

					ld  hl, __ta
					inc (hl)

					ld  hl, _t_alt
					inc (hl)
			#endasm 		

			/*
			if (a3) { c3 = *gen_pt_alt; t3 = t_alt; }
				else { c3 = *gen_pt; t3 = _ta; }
			++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;	
			*/

			#asm
					ld  a, (_a3)
					or  a
					jr  z, _dct_3_no_shadow

				._dct_3_shadow
				// { c1 = *gen_pt_alt; t1 = t_alt; }
					ld  hl, (_gen_pt_alt)
					ld  a, (hl)
					ld  (_c3), a

					ld  a, (_t_alt)
					ld  (_t3), a

					jr  _dct_3_increment
				
				._dct_3_no_shadow
				// else { c1 = *gen_pt; t1 = _ta; }
					ld  hl, (_gen_pt)
					ld  a, (hl)
					ld  (_c3), a

					ld  a, (__ta)
					ld  (_t3), a

				._dct_3_increment
				// ++ gen_pt; ++ gen_pt_alt; ++ _ta; ++ t_alt;
					ld  hl, (_gen_pt)
					inc hl
					ld  (_gen_pt), hl

					ld  hl, (_gen_pt_alt)
					inc hl
					ld  (_gen_pt_alt), hl

					ld  hl, __ta
					inc (hl)

					ld  hl, _t_alt
					inc (hl)
			#endasm 
			
		#endif

		// c4 = *gen_pt; t4 = _ta;
		#asm
				ld  hl, (_gen_pt)
				ld  a, (hl)
				ld  (_c4), a

				ld  a, (__ta)
				ld  (_t4), a
		#endasm	

		// Paint tile
		#asm
				// Calculate address in the display list

				ld  a, (__x)
				ld  c, a
				ld  a, (__y)
				call SPCompDListAddr
				
				// Now write 4 attributes and 4 chars.

				// For each char: write colour, inc DE, write tile, inc DE*3
				
				ld  a, (_c1) 		// read colour			
				ld  (hl), a 		// write colour
				inc hl

				ld  a, (_t1)		// read tile
				ld  (hl), a			// write tile
				inc hl
				
				inc hl
				inc hl 				// next DisplayList cell

				ld  a, (_c2) 		// read colour			
				ld  (hl), a 		// write colour
				inc hl				

				ld  a, (_t2)  		// read tile
				ld  (hl), a			// write tile
								
				ld  bc, 123
				add hl, bc 			// next DisplayList cell
				
				ld  a, (_c3) 		// read colour			
				ld  (hl), a 		// write colour
				inc hl				

				ld  a, (_t3)		// read tile
				ld  (hl), a			// write tile
				inc hl
				
				inc hl
				inc hl 				// next DisplayList cell

				ld  a, (_c4) 		// read colour			
				ld  (hl), a 		// write colour
				inc hl

				ld  a, (_t4)		// read tile
				ld  (hl), a			// write tile
		#endasm
	#else
		#asm
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
				add 64 				// A = _t * 4 + 64
				
				ld  hl, _tileset + 2048
				ld  b, 0
				ld  c, a
				add hl, bc 			// HL = tileset + _taux
				
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
	#endif
}

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
			ld  b, a
			ld  iy, fsClipStruct
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

void validate_viewport (void) {
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
			call SPValidate
	#endasm
}

void draw_invalidate_coloured_tile_gamearea (void) {
	draw_coloured_tile_gamearea ();
	invalidate_tile ();
}

void draw_coloured_tile_gamearea (void) {
	#ifdef ENABLE_TILANIMS
		if (IS_TILANIM (_t)) {
			#asm				
				ld  a, (__x)
				sla a
				sla a
				sla a
				sla a
				ld  c, a
				ld  a, (__y)
				add c
				ld  (__n), a
			#endasm
			tilanims_add (); 
		}
	#endif	
	_x = VIEWPORT_X + (_x << 1); _y = VIEWPORT_Y + (_y << 1); draw_coloured_tile ();
}

void print_number2 (void) {
	rda = 16 + (_t / 10); rdb = 16 + (_t % 10);
	#asm
			; enter:  A = row position (0..23)
			;         C = col position (0..31/63)
			;         D = pallette #
			;         E = graphic #

			ld  a, (_rda)
			ld  e, a

			ld  d, 7
			
			ld  a, (__x)
			ld  c, a

			ld  a, (__y)

			call SPPrintAtInv

			ld  a, (_rdb)
			ld  e, a

			ld  d, 7
			
			ld  a, (__x)
			inc a
			ld  c, a

			ld  a, (__y)

			call SPPrintAtInv
	#endasm
}

#ifndef DEACTIVATE_OBJECTS
	void draw_objs () {
		#if defined (ONLY_ONE_OBJECT) && defined (ACTIVATE_SCRIPTING)
			#if OBJECTS_ICON_X != 99
				if (p_objs) {
					// Make tile 17 flash
					/*
					sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X, 135, 132);
					sp_PrintAtInv (OBJECTS_ICON_Y, OBJECTS_ICON_X + 1, 135, 133);
					sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X, 135, 134);
					sp_PrintAtInv (OBJECTS_ICON_Y + 1, OBJECTS_ICON_X + 1, 135, 135);
					*/
					#asm
							// Calculate address in the display list

							ld  a, (OBJECTS_ICON_X)
							ld  (__x), a
							ld  c, a
							ld  a, (OBJECTS_ICON_Y)
							ld  (__y), a
							call SPCompDListAddr // -> HL

							ld  a, 135
							ld  (hl), a 		// Colour 1
							inc hl
							ld  a, 132
							ld  (hl), a 		// Tile 1

							inc hl
							inc hl 				// Next cell

							ld  a, 135
							ld  (hl), a 		// Colour 2
							inc hl
							ld  a, 133
							ld  (hl), a 		// Tile 2

							ld  bc, 123
							add hl, bc 			// Next cell

							ld  a, 135
							ld  (hl), a 		// Colour 3
							inc hl
							ld  a, 134
							ld  (hl), a 		// Tile 3

							inc hl
							inc hl 				// Next cell

							ld  a, 135
							ld  (hl), a 		// Colour 4
							inc hl
							ld  a, 135
							ld  (hl), a 		// Tile 4

							// Invalidate
							call _invalidate_tile
					#endasm						
				} else {
					_x = OBJECTS_ICON_X; _y = OBJECTS_ICON_Y; _t = 17; 
					draw_coloured_tile ();
					invalidate_tile ();
				}
			#endif
				
			#if OBJECTS_X != 99
				_x = OBJECTS_X; _y = OBJECTS_Y; _t = flags [OBJECT_COUNT]; print_number2 ();
			#endif
		#else
			#if OBJECTS_X != 99
				_x = OBJECTS_X; _y = OBJECTS_Y; 
				#ifdef REVERSE_OBJECTS_COUNT
					_t = 
						#ifdef COMPRESSED_LEVELS
							level_data.max_objs
						#else						
							PLAYER_MAX_OBJECTS
						#endif
						- p_objs;
				#else
					_t = p_objs; 
				#endif
				print_number2 ();
			#endif
		#endif
	}
#endif

void print_str (void) {
	#asm
		ld  hl, (_gp_gen)
		.print_str_loop
			ld  a, (hl)
			or  a
			ret z 

			inc hl
			
			sub 32
			ld  e, a

			ld  a, (__t)
			ld  d, a

			ld  a, (__x)
			ld  c, a
			inc a
			ld  (__x), a
			
			ld  a, (__y)

			push hl
			call SPPrintAtInv
			pop  hl
			
			jr  print_str_loop
	#endasm
}

#if defined (COMPRESSED_LEVELS) || defined (SHOW_LEVEL_ON_SCREEN)
	void blackout_area (void) {
		#asm
			ld  de, 22528 + 32 * VIEWPORT_Y + VIEWPORT_X
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

void print_message (void) {	
	_x = 10; _y = 12; _t = MESSAGE_COLOUR; print_str ();
	_x = 10; _y = 11; _t = MESSAGE_COLOUR; gp_gen = spacer; print_str ();
	_x = 10; _y = 13; _t = MESSAGE_COLOUR; gp_gen = spacer; print_str ();
	
	sp_UpdateNow ();
	sp_WaitForNoKey ();
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
