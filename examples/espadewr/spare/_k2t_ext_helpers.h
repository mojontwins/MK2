// Key To Time 'Extern' helpers
// Various helper functions for custom extern actions
// Copyleft 2015 The Mojon Twins

// This file must be preprocessed by nicanor.exe to be usable
// nicanor.exe will fill in values for BASE_PORTRAITS and BASE_ITEMDESCS

#define K2T_MENU_X 			13
#define K2T_MENU_Y 			7
#define K2T_MENU_WIDTH 		6

#define TEXTS_RAM_PAGE		6
#define TEXTBUFF_ADDRESS	24200-256-168
#define TEXTBOX_X1			2
#define TEXTBOX_X2          29
#define TEXTBOX_Y1          9
#define TEXTBOX_Y2          14
#define TEXTBOX_X_SHIFT		5
#define FRAME_ATTRIBUTE		65

#define FLAGS_OFFSET		120
#define STORAGE_X			6
#define STORAGE_Y			9
#define STORAGE_NAME_X		2
#define STORAGE_NAME_Y		12
#define STORAGE_DESC_X		2
#define STORAGE_DESC_Y		13
#define STORAGE_MAX_ITEMS	7

#define FIRST_ITEM_IN_TS 	32

// Pattern in this line to be replaced by imanol.exe
#define BASE_PORTRAITS 		%%%base_portraits%%%
#define BASE_ITEMDESCS		%%%base_itemdescs%%%

extern unsigned char k2t_menu_text [0];
extern unsigned char k2t_code [0];
#asm
	._k2t_menu_text
		defm "000233"
		defm "001001"
		defm "003322"
		defm "005992"
		defm "006800"
		defm "010000"
		defm "050000"
		defm "THRUST"
	._k2t_code
		defb 0
#endasm

unsigned char *k2t_ptr;
unsigned char k2t_x, k2t_x0, k2t_y, k2t_length, k2t_i, k2t_color, k2t_selected, k2t_last_key;
unsigned char k2t_flag = 0;

unsigned char *k2t_gpp;
unsigned char k2t_stepbystep;
unsigned char k2t_is_cutscene = 0;
unsigned char k2t_last_character;
unsigned char k2t_time;

unsigned char k2t_cursor;

void __FASTCALL__ k2t_tint_middle_third (unsigned char attribute) {
	// Tint middle third to attribute 
	#asm
		; fastcall. Parameter is in L
		ld      a, l
		ld		hl, $5900
		ld		de, $5901
		ld		bc, $fe 
		ld		(hl), a
		ldir
	#endasm
}

void __FASTCALL__ k2t_tint (unsigned char c) {
	// Colour is in L

	#asm
		ld a, l
		ld de, 22561
		
		ld b, 20
		halt
	.k2t_bal1
		push bc
		push de
		pop hl
		ld	(hl), a
		inc de
		ld bc, 29
		ldir
		inc de
		inc de
		pop bc
		djnz k2t_bal1
	#endasm
}

// k2t_gpp must point to characters to print...
void k2t_print_limited_text (unsigned char x, unsigned char y, unsigned char n) {
	for (k2t_i = 0; k2t_i < n; k2t_i ++) sp_PrintAtInv (y, x ++, 71, *k2t_gpp ++ - 32);
}

void k2t_show_time (void) {
	// Current time age is stored in flags [127];
	// print 6 chars stored @ k2t_menu_text (6 * flags [127]);
	k2t_gpp = (unsigned char *) (k2t_menu_text + 6 * flags [127]);
	for (k2t_i = 13; k2t_i < 19; k2t_i ++) sp_PrintAtInv (0, k2t_i, 42, *k2t_gpp ++ - 32);
}

void k2t_cls (void) {
	hide_sprites (0);
	for (k2t_i = 0; k2t_i < 10; k2t_i ++) {
		for (k2t_x = k2t_i; k2t_x < 30 - k2t_i; k2t_x ++) {
			sp_PrintAtInv (VIEWPORT_Y + k2t_i, VIEWPORT_X + k2t_x, 0, 0);
			sp_PrintAtInv (VIEWPORT_Y + 19 - k2t_i, VIEWPORT_X + k2t_x, 0, 0);
			if (k2t_x < 19 - k2t_i) {
				sp_PrintAtInv (VIEWPORT_Y + k2t_x, VIEWPORT_X + k2t_i, 0, 0);
				sp_PrintAtInv (VIEWPORT_Y + k2t_x, VIEWPORT_X + 29 - k2t_i, 0, 0);
			}
		}

		#asm
			halt
		#endasm

		sp_UpdateNow ();
	}
}

void k2t_effect (void) {
	if (flags [127] == k2t_time) return;
	k2t_time = flags [127];
	for (k2t_i = 0; k2t_i < 16; k2t_i ++) {
		k2t_tint (rand () & 7);
	}
}

unsigned char k2t_menu_display (unsigned char flag) {
	k2t_length = K2T_MENU_WIDTH * (7 + flag);
	k2t_ptr = k2t_menu_text;
	k2t_x = K2T_MENU_X;	k2t_y = K2T_MENU_Y;
	for (k2t_i = 0; k2t_i < k2t_length; k2t_i ++) {
		if (k2t_x == K2T_MENU_X) {
			if (k2t_y - K2T_MENU_Y == k2t_selected) k2t_color = 120; else k2t_color = 71;
		}
		sp_PrintAtInv (k2t_y, k2t_x ++, k2t_color, *k2t_ptr ++ - 32);
		if (k2t_x == K2T_MENU_X + K2T_MENU_WIDTH) {
			k2t_x = K2T_MENU_X; k2t_y ++;
		}
	}
}

unsigned char k2t_do_menu (unsigned char flag, unsigned char presel) {
	get_resource (TARDISMENU_BIN, 16384);
	k2t_show_time ();
	update_hud ();

	k2t_selected = presel;
	k2t_last_key = 1;
	while (1) {
		k2t_menu_display (flag);
		sp_UpdateNow ();

		k2t_i = (joyfunc) (&keys);

		if (0 == ((k2t_i & sp_UP) == 0 || (k2t_i & sp_DOWN) == 0)) k2t_last_key = 1;

		if ((k2t_i & sp_UP) == 0) {
			if (k2t_last_key) {
				if (k2t_selected) k2t_selected --;
				k2t_last_key = 0;
			}
		} 

		if ((k2t_i & sp_DOWN) == 0) {
			if (k2t_last_key) {
				k2t_selected += (k2t_selected < 6 + flag);
				k2t_last_key = 0;
			}
		} 
		
		if ((k2t_i & sp_FIRE) == 0) return k2t_selected;
		if ((sp_KeyPressed (key_jump))) return presel;
	}
	k2t_cls ();
}

void k2t_display_portrait (unsigned char index) {
	asm_int [0] = BASE_PORTRAITS + (index * 192);

	#asm
		; Display a 192 bytes portrait.
		; Set RAM page with texts file
		halt
		halt
		di
		ld		b, TEXTS_RAM_PAGE
		call	SetRAMBank
		
		ld 		a, (_asm_int)
		ld 		l, a
		ld 		a, (_asm_int + 1)
		ld 		h, a
		
		ld 		de, 18465
		ld 		b, 8

	.ptpl1
		ld 		c, b
		ld 		b, 6
		push 	de

	.ptpl2
		push 	bc

		ldi
		ldi
		ldi
		ldi
		
		ex 		de, hl		
		ld 		bc, 28
		add 	hl, bc
		ex 		de, hl

		pop 	bc
		djnz 	ptpl2

		pop 	de
		inc 	d

		ld 		b, c
		djnz 	ptpl1

		; Page back RAM 0
		ld		b, 0
		call	SetRAMBank
		ei

		; Paint white
		ld 		a, 71
		ld 		b, 6
		ld 		hl, 22817

	.ptpl3
		ld 		(hl), a
		inc 	l
		ld 		(hl), a
		inc 	l
		ld 		(hl), a
		inc 	l
		ld 		(hl), a
		ld 		d, b
		ld 		bc, 29
		add 	hl, bc
		ld 		b, d
		djnz ptpl3
	#endasm
}

void k2t_show_text (int index) {
	k2t_stepbystep = 1;
	
	asm_int [0] = (index - 1) << 1;

	#asm
		; Set RAM page with texts file
		halt
		halt
		di
		ld		b, TEXTS_RAM_PAGE
		call	SetRAMBank

		; First we get where to look for the packed string	
		ld		a, (_asm_int)
		ld		e, a
		ld		a, (_asm_int + 1)
		ld		d, a
		
		; Index is at $C000 in selected page.
		ld		hl, $C000
		add		hl, de
		ld		c, (hl)
		inc		hl
		ld		b, (hl)
		push	bc
		pop		hl

		; HL = Address of text line.
		
		; Read first byte (code) and store it.
		ld		a, (hl)
		inc		hl
		ld		(_k2t_code), a
		
		; Write to buffer
		ld de, TEXTBUFF_ADDRESS

		; 5-bit scaped depacker by na_th_an
		; Contains code by Antonio Villena
		ld		a, $80

	.fbsd_mainb
		call	fbsd_unpackc
		ld		c, a
		ld		a, b
		and		a
		jr		z, fbsd_fin
		call	fbsd_stor
		ld		a, c
		jr		fbsd_mainb	

	.fbsd_stor
		cp 		31
		jr 		z, fbsd_escaped
		add 	a, 64
		jr 		fbsd_stor2

	.fbsd_escaped
		ld 		a, c
		call 	fbsd_unpackc
		ld 		c, a
		ld 		a, b
		add 	a, 32

	.fbsd_stor2
		ld 		(de), a
		inc 	de
		ret

	.fbsd_unpackc
		ld		b, 0x08
	.fbsd_bucle
		call	fbsd_getbit
		rl		b
		jr		nc, fbsd_bucle
		ret

	.fbsd_getbit
		add 	a, a
		ret 	nz
		ld		a, (hl)
		inc 	hl
		rla
		ret 	   
		
	.fbsd_fin
		ld 		(de), a	

		; Page back RAM 0
		ld		b, 0
		call	SetRAMBank
		ei
	#endasm 

	// Move sprites out.
	hide_sprites (0);
	sp_UpdateNow ();

	// Show text 
	if (k2t_is_cutscene == 0) {
		if (k2t_last_character != k2t_code [0]) {
			k2t_last_character = k2t_code [0];

			// Prepare frame upon code.
			k2t_tint_middle_third (0);

			if (k2t_last_character == 0xff) {
				// General frame
				get_resource (TALKG_BIN, 18432);
				k2t_tint_middle_third (FRAME_ATTRIBUTE);
				k2t_x0 = TEXTBOX_X1;
			} else {
				// Character frame
				get_resource (TALKC_BIN, 18432);
				k2t_tint_middle_third (FRAME_ATTRIBUTE);
				k2t_display_portrait (k2t_last_character);
				k2t_x0 = TEXTBOX_X1 + TEXTBOX_X_SHIFT;
			}
		}

		k2t_y = TEXTBOX_Y1;
	} else {
		k2t_y = 13;
		k2t_x0 = 4;
	}
	
	active_sleep (10);
	
	// Draw text
	k2t_x = k2t_x0; 
	k2t_gpp = TEXTBUFF_ADDRESS + 1;
	k2t_last_key = 1;

	while (k2t_i = *k2t_gpp ++) {
		if (k2t_i == '%') {
			k2t_x = k2t_x0; k2t_y += (1 + k2t_is_cutscene);
		} else {
			sp_PrintAtInv (k2t_y, k2t_x, 71, k2t_i - 32);
			k2t_x ++;
		}
		if (k2t_stepbystep) {
#asm
			halt
#endasm
			if (k2t_i != 32 && k2t_is_cutscene == 0) _AY_PL_SND (10);
#asm
			halt
			halt
#endasm
			sp_UpdateNow ();
		}
		
		if (button_pressed ()) {
			if (k2t_last_key == 0) {
				k2t_stepbystep = 0;
			} 
		} else {
			k2t_last_key = 0;
		}
	}
	sp_UpdateNow ();
	sp_WaitForNoKey ();
	while (button_pressed ());
	active_sleep (5000);
	
	if (k2t_is_cutscene) {
		for (k2t_i = 11; k2t_i < 24; k2t_i ++) {
			print_str (3, k2t_i, 71, "						   ");
			sp_UpdateNow ();
		}
	} else {
		for (k2t_y = TEXTBOX_Y1; k2t_y <= TEXTBOX_Y2; k2t_y ++) {
			for (k2t_x = k2t_x0; k2t_x <= TEXTBOX_X2; k2t_x ++) {
				sp_PrintAtInv (k2t_y, k2t_x, 0, 0);
			}
		}
	}

	sp_UpdateNow ();
}

void k2t_init () {
	k2t_last_character = 0xfe;
	k2t_cursor = 0;
	k2t_time = flags [127];
}

void k2t_end_of_conversation () {
	k2t_init ();
}

void k2t_show_items () {
	for (k2t_i = 0; k2t_i < STORAGE_MAX_ITEMS; k2t_i ++) {
		draw_coloured_tile (STORAGE_X + (k2t_i << 1) + k2t_i, STORAGE_Y, flags [FLAGS_OFFSET + k2t_i]);
		// This function comes from msc-config.h
		draw_cursor (k2t_i, k2t_cursor, STORAGE_X + (k2t_i << 1) + k2t_i, STORAGE_Y + 2);
	}
}

void k2t_storage () {
	// position is remembered!

	// Setup
	hide_sprites (0);
	sp_UpdateNow ();

	// Show stuff
	k2t_tint_middle_third (0);
	get_resource (ARCON_BIN, 18432);
	k2t_tint_middle_third (FRAME_ATTRIBUTE);

	k2t_last_key = 1;
	k2t_flag = 1;

	while (k2t_flag) {
		// Show items in storage
		k2t_show_items ();

		// Show items in inventory
		display_items ();

		// Copy text to TEXTBUFF_ADDRESS
		if (flags [FLAGS_OFFSET + k2t_cursor]) {
			k2t_i = flags [FLAGS_OFFSET + k2t_cursor] - FIRST_ITEM_IN_TS;
			asm_int [0] = (BASE_ITEMDESCS + (k2t_i << 6) + (k2t_i << 4));
		} else {
			asm_int [0] = (BASE_ITEMDESCS + 1280);
		}
		#asm
			di
			ld		b, TEXTS_RAM_PAGE
			call	SetRAMBank

			ld 		a, (_asm_int)
			ld 		l, a
			ld 		a, (_asm_int + 1)
			ld 		h, a
			ld 		de, TEXTBUFF_ADDRESS
			ld 		bc, 80
			ldir

			ld		b, 0
			call	SetRAMBank
			ei
		#endasm

		// Display text
		k2t_gpp = TEXTBUFF_ADDRESS;
		k2t_print_limited_text (STORAGE_NAME_X, STORAGE_NAME_Y, 24);
		k2t_print_limited_text (STORAGE_DESC_X, STORAGE_DESC_Y, 28);
		k2t_print_limited_text (STORAGE_DESC_X, STORAGE_DESC_Y + 1, 28);
	
		while (1) {
			sp_UpdateNow ();

			// Move my cursor
			k2t_i = (joyfunc) (&keys);

			if (!((k2t_i & sp_LEFT) == 0 || (k2t_i & sp_RIGHT) == 0 || (k2t_i & sp_FIRE) == 0)) {
				k2t_last_key = 1;
			}

			if ((k2t_i & sp_LEFT) == 0) {
				if (k2t_last_key) {
					if (k2t_cursor) k2t_cursor --; else k2t_cursor = STORAGE_MAX_ITEMS -1;
					k2t_last_key = 0;
					break;
				}
			}

			if ((k2t_i & sp_RIGHT) == 0) {
				if (k2t_last_key) {
					k2t_cursor = (k2t_cursor + 1) % STORAGE_MAX_ITEMS;
					k2t_last_key = 0;
					break;
				}
			}

			// Move inventory cursor
			do_inventory_fiddling ();

			// interchange?
			if ((k2t_i & sp_FIRE) == 0) {
				if (k2t_last_key) {
					k2t_i = items [flags [FLAG_SLOT_SELECTED]];
					items [flags [FLAG_SLOT_SELECTED]] = flags [FLAGS_OFFSET + k2t_cursor];
					flags [FLAGS_OFFSET + k2t_cursor] = k2t_i;
					k2t_last_key = 0;
					break;
				}
			}

			// Exit?
			if (sp_KeyPressed (key_jump)) {
				k2t_flag = 0;
				break;
			}
		}
	}

	// Do stuff
}
