
void run_entering_script (void) {
	#ifdef EXTENDED_LEVELS
		if (level_data.activate_scripting) 
	#endif
	{
		#ifdef LINE_OF_TEXT
			#ifdef LINE_OF_TEXT_SUBSTR
				#asm
						ld  a, 32 - LINE_OF_TEXT_SUBSTR
						ld  (_gpit), a
						ld  a, LINE_OF_TEXT_X
						ld  (__x), a
					._line_of_text_loop
						ld  hl, _gpit
						dec (hl)

						; enter:  A = row position (0..23)
						;         C = col position (0..31/63)
						;         D = pallette #
						;         E = graphic #

						ld hl, __x
						ld  a, (hl)
						ld  c, a
						inc (hl)

						ld  a, LINE_OF_TEXT

						ld  d, LINE_OF_TEXT_ATTR
						ld  e, 0

						call SPPrintAtInv

						ld  a, (_gpit)
						or  a
						jr  z, _line_of_text_loop
				#endasm
			#else
				_x = LINE_OF_TEXT_X; _y = LINE_OF_TEXT; _t = LINE_OF_TEXT_ATTR; gp_gen = "                              ";
				print_str ();
			#endif
		#endif
		// Ejecutamos los scripts de entrar en pantalla:
		run_script (2 * MAP_W * MAP_H + 1);
		run_script (n_pant + n_pant);
	}
}

void run_fire_script (void) {
	run_script (2 * MAP_W * MAP_H + 2);	// Press fire at any
	run_script (n_pant + n_pant + 1);	// Press fire at n_pant
}

void do_ingame_scripting (void) {
	if (
		#ifdef EXTENDED_LEVELS
			level_data.activate_scripting && 
		#endif
		#ifdef SCRIPTING_KEY_M
			sp_KeyPressed (KEY_M)
		#endif
		#ifdef SCRIPTING_DOWN
			(pad0 & sp_DOWN) == 0
		#endif
		#ifdef SCRIPTING_KEY_FIRE
			(pad0 & sp_FIRE) == 0
		#endif
	) {
		if (action_pressed == 0)  {
			action_pressed = 1;

			// Any scripts to run in this screen?
			run_fire_script ();
		}
	} else {
		action_pressed = 0;

		#ifdef ENABLE_FIRE_ZONE
			if (
				#ifdef EXTENDED_LEVELS
					level_data.activate_scripting &&
				#endif
				f_zone_ac
			) {
				if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
					run_fire_script ();
				}
			}
		#endif
	}
}
