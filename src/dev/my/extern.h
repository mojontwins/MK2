// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// extern.h
// External custom code to be run from a script

// =======[CUSTOM MODIFICATION]=======
unsigned char *textbuff = 23458;
unsigned char *extaddress;
unsigned char exti, extx, exty, exty2, extc, extl, keyp;
extern unsigned char textos_load [0];

// CUSTOM {
void read_print_text_line (void) {
	while (1) {
		exti = *extaddress ++;
		if (exti == 0 || exti == '%') return;
		// sp_PrintAtInv (exty, extx ++, extc, exti - 32);
		#asm
				; enter:  A = row position (0..23)
				;         C = col position (0..31/63)
				;         D = pallette #
				;         E = graphic #
				ld  a, (_exti)
				sub 32
				ld  e, a

				ld  a, (_extx)
				ld  c, a
				inc a
				ld  (_extx), a

				ld  a, (_exty)

				ld  d, (_extc)

				call SPPrintAtInv
		#endasm
	}
}
// } END_OF_CUSTOM

void do_extern_action (unsigned char n) {
// CUSTOM {		
	asm_int = (n - 1) << 1;
	#asm
		; First we get where to look for the packed string
	
		/*
		ld a, (_asm_int)
		ld e, a
		ld a, (_asm_int + 1)
		ld d, a
		*/
		ld  de, (_asm_int)

		ld hl, _textos_load
		add hl, de
		ld c, (hl)
		inc hl
		ld b, (hl)
		push bc
		pop de
		ld hl, _textos_load
		add hl, de
		
		ld de, 23458

		; 5-bit scaped depacker by na_th_an
		; Contains code by Antonio Villena
		
		ld a, $80

	.fbsd_mainb
        call fbsd_unpackc
        ld c, a
        ld a, b
        and a
        jr z, fbsd_fin
        call fbsd_stor
        ld a, c
        jr fbsd_mainb	

	.fbsd_stor
        cp 31
        jr z, fbsd_escaped
        add a, 64
        jr fbsd_stor2
	.fbsd_escaped
        ld a, c
        call fbsd_unpackc
        ld c, a
        ld a, b
        add a, 32
	.fbsd_stor2
        ld (de), a
        inc de
        ret

	.fbsd_unpackc
        ld      b, 0x08
	.fbsd_bucle
        call    fbsd_getbit
        rl      b
        jr      nc, fbsd_bucle
        ret

	.fbsd_getbit
        add     a, a
        ret     nz
        ld      a, (hl)
        inc     hl
        rla
        ret        
        
	.fbsd_fin
		ld (de), a	
		;
		;		
		
	#endasm	

	if (n < 31) {
		// Textstuffer2 for this game is patched.
		// it receives an extra parameter with a line offset
		// first byte for lines < offset is a precalculated
		// x coordinate the line of text to appear centered.
		for (exti = 1; exti < 31; exti ++) {
			// sp_PrintAtInv (22, exti, 23, 0);
			#asm
				; enter:  A = row position (0..23)
				;         C = col position (0..31/63)
				;         D = pallette #
				;         E = graphic #
				ld  a, (_exti)
				ld  c, a

				ld  a, 22
				ld  d, 23
				ld  e, 0

				call SPPrintAtInv			
			#endasm
		}
		extaddress = textbuff;
		extx = (*extaddress) - 64;
		exty = 22; extc = 23;
		extaddress ++;
		read_print_text_line ();
	} else {
		hide_sprites (0);

		// # of lines
		extaddress = textbuff;
		extl = (*extaddress) - 64;

		// Height of box
		exty2 = extl + extl - 1;

		// Vertical position, centered
		exty = 11 - (exty2 >> 1);

		// Title
		//sp_PrintAtInv (exty, 3, 2, 2);
		#asm
				ld  a, (_exty)
				ld  c, 3
				ld  de, 0x0202
				call SPPrintAtInv
		#endasm

		extx = 4; extc = 23;
		extaddress ++; read_print_text_line ();
		//sp_PrintAtInv (exty, extx ++, 2, 3);
		#asm
				ld  a, (_extx)
				ld  c, a
				inc a
				ld  (_extx), a
				ld  a, (_exty)			
				ld  de, 0x0203
				call SPPrintAtInv
		#endasm

		_x = 3; _y = exty + 1; _t = 71; gp_gen = "&                        %"; print_str ();
		for (exti = extx; exti < 28; exti ++) {
			//sp_PrintAtInv (exty + 1, exti, 71, 4);
			#asm
				ld  a, (_exti)
				ld  c, a
				ld  a, (_exty)
				inc a
				ld  d, 71
				ld  e, 4
				call SPPrintAtInv
			#endasm
		}

		// Frame
		for (exti = exty + 2; exti < exty + exty2; exti ++) {
			_x = 3; _y = exti; _t = 71; gp_gen = "&                        '"; print_str ();
		}
		_x = 3; _y = exty + exty2; _t = 71; gp_gen = "())))))))))))))))))))))))*"; print_str ();

		sp_UpdateNow ();
		active_sleep (10);

		// Show text
		keyp = 1;
		exty = exty + 2; extc = 71; extl --;
		while (extl --) {
			extx = 4; 
			read_print_text_line ();
			if (keyp) {
				sp_UpdateNow ();
#ifndef MODE_128K
				beep_fx (7 + ((rand () & 1) << 2));
#endif
			}
			if (button_pressed ()) keyp = 0;
			exty += 2; 
		}

		sp_UpdateNow ();
		sp_WaitForNoKey ();
		while (button_pressed ());
		active_sleep (5000);

		// REDRAW; SHOW
		sc_x = sc_y = 0;
		for (sc_c = 0; sc_c < 150; sc_c ++) {
			_x = sc_x; _y = sc_y; _n = map_attr [sc_c]; _t = map_buff [sc_c]; update_tile ();
			sc_x ++; if (sc_x == 15) { sc_x = 0; sc_y ++; }
		}
		sp_UpdateNow ();
	}
// } END_OF_CUSTOM	
}

// CUSTOM {
#ifndef INGLISHPITINGLISH
#asm
	._textos_load
		BINARY "../bin/texts.bin"
#endasm
#else
#asm
	._textos_load
		BINARY "../bin/texts-eng.bin"
#endasm
#endif		
// } END_OF_CUSTOM
