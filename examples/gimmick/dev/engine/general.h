// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// engine.h
// Well, self explanatory innit?

#ifndef PLAYER_MIN_KILLABLE
#define PLAYER_MIN_KILLABLE 0
#endif

void read_controller (void) {
	// Thanks for this, Nicole & nesdev!
	// https://forums.nesdev.com/viewtopic.php?p=179315#p179315
	// This version is the same but with negative logic
	// as splib2's functions are active low
	pad_this_frame = pad0;
	pad0 = ((joyfunc) (&keys));			// Read pads here.
	pad_this_frame = ((~(pad_this_frame ^ pad0)) | pad0) | 0x70;
}

unsigned char button_pressed (void) {
	//return (sp_GetKey () || ((((joyfunc) (&keys)) & sp_FIRE) == 0));
	read_controller (); return (pad_this_frame != 0xff);
}

#ifdef PLAYER_STEP_SOUND
void step (void) {
	#asm
		ld a, 16
		out (254), a
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		xor 16
		out (254), a
	#endasm
}
#endif

void cortina (void) {
	#asm
		ld b, 7
	.fade_out_extern
		push bc

		ld   e, 3               ; 3 tercios
		ld   hl, 22528          ; aqu� empiezan los atributos
	#endasm
#ifdef MODE_128K
	#asm
		halt                    ; esperamos retrazo.
	#endasm
#endif
	#asm
	.fade_out_bucle
		ld   a, (hl )           ; nos traemos el atributo actual

		ld   d, a               ; tomar atributo
		and  7                  ; aislar la tinta
		jr   z, ink_done        ; si vale 0, no se decrementa
		dec  a                  ; decrementamos tinta
	.ink_done
		ld   b, a               ; en b tenemos ahora la tinta ya procesada.

		ld   a, d               ; tomar atributo
		and  56                 ; aislar el papel, sin modificar su posición en el byte
		jr   z, paper_done      ; si vale 0, no se decrementa
		sub  8                  ; decrementamos papel restando 8
	.paper_done
		ld   c, a               ; en c tenemos ahora el papel ya procesado.
		ld   a, d
		and  192                ; nos quedamos con bits 6 y 7 (BRIGHT y FLASH)
		or   c                  ; a�adimos paper
		or   b                  ; e ink, con lo que recompuesto el atributo
		ld   (hl),a             ; lo escribimos,
		inc  l                  ; e incrementamos el puntero.
		jr   nz, fade_out_bucle ; continuamos hasta acabar el tercio (cuando L valga 0)
		inc  h                  ; siguiente tercio
		dec  e
		jr   nz, fade_out_bucle ; repetir las 3 veces
		pop bc
		djnz fade_out_extern
	#endasm
}

signed int addsign (signed int n, signed int value) {
	//if (n >= 0) return value; else return -value;
	return n == 0 ? 0 : n > 0 ? value : -value;
}

unsigned int abs (int n) {
	if (n < 0)
		return (unsigned int) (-n);
	else
		return (unsigned int) n;
}

void active_sleep (int espera) {
	do {
		#ifndef MODE_128K
			gpjt = 250; do { gpit = 1; } while (--gpjt);
		#else
			#asm
				halt
			#endasm
		#endif
		#ifdef DIE_AND_RESPAWN
			if (p_killme == 0 && button_pressed ()) break;
		#else
			if (button_pressed ()) break;
		#endif
	} while (--espera);
	sp_Border (0);
}

void select_joyfunc (void) {
#ifdef PHANTOMAS_ENGINE
	joyfunc = sp_JoyKeyboard;
	keys.up    = 0x01fb;	// Q
	keys.down  = 0x01fd;	// A
	keys.left  = 0x02df;	// O
	keys.right = 0x01df;	// P
	keys.fire  = 0x017f;	// SPACE
	#asm
		; Music generated by beepola
		; call musicstart
	#endasm
	while (0 == sp_GetKey ());
#else
	#ifdef MODE_128K
	#else
		#asm
			; Music generated by beepola
			call musicstart
		#endasm
	#endif

	while (1) {
		gpit = sp_GetKey ();
		
		if (gpit == '1' || gpit == '2') {
			joyfunc = sp_JoyKeyboard;
			gpjt = (gpit - '1') ? 6 : 0;
			#ifdef USE_TWO_BUTTONS
				keys.up = keyscancodes [gpjt ++];
				keys.down = keyscancodes [gpjt ++];
				keys.left = keyscancodes [gpjt ++];
				keys.right = keyscancodes [gpjt ++];
				key_fire = keys.fire = keyscancodes [gpjt ++];
				key_jump = keyscancodes [gpjt];
			#else
				keys.up = keyscancodes [gpjt ++];		// UP
				keys.down = keyscancodes [gpjt ++];		// DOWN
				keys.left = keyscancodes [gpjt ++];		// LEFT
				keys.right = keyscancodes [gpjt ++];	// RIGHT
				keys.fire = keyscancodes [gpjt ++];		// FIRE				
			#endif
				break;
			} else if (gpit == '3') {
				joyfunc = sp_JoyKempston;
				break;
			} else if (gpit == '4') {
				joyfunc = sp_JoySinclair1;
				break;
			}
		}
	#ifdef MODE_128K
		_AY_PL_SND (0);
		sp_WaitForNoKey ();
	#endif
#endif
}
