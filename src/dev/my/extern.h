// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// extern.h
// External custom code to be run from a script

unsigned char textbuff [150] @ SAFE_MEMORY_POOL;	// Max. 150 characters.
unsigned char exti, extx, exty, stepbystep, keyp;
unsigned char is_cutscene = 0;

extern unsigned char textos_load [0];
#asm
	._textos_load
		BINARY "../bin/texts.bin"
#endasm

void do_extern_action (unsigned char n) {
	// Add custom code here.
	
	gpt = n;
	if (gpt == 0) {
		// Cortina
		
		for (exti = 0; exti < 10; exti ++) {
			for (extx = exti; extx < 30 - exti; extx ++) {
				#asm
						// sp_PrintAtInv (VIEWPORT_Y + exti, VIEWPORT_X + extx, 71, 0);
						ld  de, 0x4700
						ld  a, (_extx)
						add VIEWPORT_X
						ld  c, a
						ld  a, (_exti)
						add VIEWPORT_Y
						call SPPrintAtInv
					
						// sp_PrintAtInv (VIEWPORT_Y + 19 - exti, VIEWPORT_X + extx, 71, 0);
						ld  de, 0x4700
						ld  a, (_extx)
						add VIEWPORT_X
						ld  c, a
						ld  a, (_exti)
						ld  b, a
						ld  a, VIEWPORT_Y + 19
						sub b
						call SPPrintAtInv
				#endasm

				if (extx < 19 - exti) {
					#asm
							// sp_PrintAtInv (VIEWPORT_Y + extx, VIEWPORT_X + exti, 71, 0);
							ld  de, 0x4700
							ld  a, (_exti)
							add VIEWPORT_X
							ld  c, a
							ld  a, (_extx)
							add VIEWPORT_Y
							call SPPrintAtInv

							// sp_PrintAtInv (VIEWPORT_Y + extx, VIEWPORT_X + 29 - exti, 71, 0);
							ld  de, 0x4700
							ld  a, (_exti)
							ld  b, a
							ld  a, VIEWPORT_X + 29
							sub b
							ld  c, a
							ld  a, (_extx)
							add VIEWPORT_Y							
							call SPPrintAtInv
					#endasm
				}
			}
			#ifdef MODE_128K
				#asm
					halt
				#endasm
			#endif
			sp_UpdateNowEx (0);
		}
		return;
	} else if (n < 250) {
		
		// Show text gpt
		stepbystep = 1;
		
		asm_int = (gpt - 1) << 1;
		#asm
		._extern_depack_text
				; First we get where to look for the packed string
				
				ld  hl, (_asm_int)
				ld  de, _textos_load
				add hl, de
				ld  a, (hl)
				inc hl
				ld  h, (hl)
				ld  l, a
				add hl, de

				ld de, _textbuff

				; 5-bit scaped depacker by na_th_an
				; Contains code by Antonio Villena
				
				ld  a, $80

		.fbsd_mainb
				call fbsd_unpackc

				ld  c, a
				ld  a, b
				and a
				jr  z, fbsd_fin

				call fbsd_stor

				ld  a, c
				jr  fbsd_mainb	

		.fbsd_stor
				cp  31
				jr  z, fbsd_escaped
				add a, 64
				jr  fbsd_stor2

		.fbsd_escaped
				ld  a, c

				call fbsd_unpackc
				
				ld  c, a
				ld  a, b
				add a, 32
		.fbsd_stor2
				ld  (de), a
				inc de
				ret

		.fbsd_unpackc
				ld  b, 0x08
		.fbsd_bucle
				call fbsd_getbit

				rl  b
				jr  nc, fbsd_bucle
				ret

		.fbsd_getbit
				add a, a
				ret nz
				ld  a, (hl)
				inc hl
				rla
				ret        
				
		.fbsd_fin
				ld (de), a	
				;
				;		

		#endasm	
		
		if (is_cutscene == 0) {
			// Show
			exti = textbuff [0] - 64;
			
			// Draw empty frame
			extx = 3 + exti + exti;		
		
			_x = 3; _y = 3; _t = 1; gp_gen = (unsigned char *) ("#$$$$$$$$$$$$$$$$$$$$$$$$%"); print_str ();
			_x = 3; _t = 1; gp_gen = (unsigned char *) ("&                        '");
			for (_y = 4; _y < extx; ++ _y) { _x = 3; print_str (); }
			_x = 3; _y = extx; _t = 1; gp_gen = (unsigned char *) ("())))))))))))))))))))))))*"); print_str ();
			
			exty = 4;
		} else {
			exty = 13;
		}
		
		// Draw text
		extx = 4; 
		gp_gen = textbuff + 1;
		keyp = 1;
		while (exti = *gp_gen ++) {
			if (exti == '%') {
				extx = 4; exty += 2;
			} else {
				// sp_PrintAtInv (exty, extx, 71, exti - 32);
				#asm
					ld  a, (_exti)
					sub 32
					ld  e, a
					ld  a, (_extx)
					ld  c, a
					ld  a, (_exty)
					ld  d, 71				
					call SPPrintAtInv
				#endasm
				++ extx;
				if (extx == 28) {
					extx = 4; exty += 2;
				}
			}
			if (stepbystep) {
				#ifdef MODE_128K
					#asm
						halt
					#endasm
					if (exti != 32 && is_cutscene == 0) _AY_PL_SND (8);
					#asm
						halt
						halt
					#endasm
				#else
					beep_fx (2);
				#endif
				sp_UpdateNowEx (0);
			}
			
			if (button_pressed ()) {
				if (keyp == 0) {
					stepbystep = 0;
				} 
			} else {
				keyp = 0;
			}
		}

		sp_UpdateNowEx (0);
		sp_WaitForNoKey ();
		while (button_pressed ());
		active_sleep (5000);

		if (is_cutscene) {
			for (exti = 11; exti < 24; exti ++) {
				_x = 3; _y = exti; _t = 71; gp_gen = (unsigned char *) ("                          "); print_str ();			
				sp_UpdateNow ();
			}
		}
	} else if (n == 251) {
		is_cutscene = 1;
		sp_UpdateNow ();	
	} else if (n == 250) {
		is_cutscene = 0;
	} else if (n == 255) {
		for (gpit = 0; gpit < 3; gpit ++) {
			enoffsmasi = enoffs + gpit;
			baddies [enoffsmasi].x = baddies [enoffsmasi].x1;
			baddies [enoffsmasi].y = baddies [enoffsmasi].y1;
		}
	}
}
