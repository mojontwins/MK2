// credits.h

// Lee desde el recurso CREDITS_BIN e imprime.

void credits_read_line (void) {
	#asm
		di
		ld	a, (_asm_number)
		ld	b, a
		call SetRAMBank
		ld	hl, (_asm_int)
		ld	de, 23296
		ld	bc, 32
		ldir
		ex 	de, hl
		ld	(hl), 0
		ld	b, 0
		call SetRAMBank
		ei
	#endasm
	asm_int [0] += 32;
}

void credits (void) {
	asm_number [0] = resources [CREDITS_BIN].ramPage;
	asm_int [0] = resources [CREDITS_BIN].ramOffset;
	gpit = 28; while (--gpit) {
		credits_read_line ();
		print_str (0, 10, 71, (unsigned char *) (23296));
		credits_read_line ();
		print_str (0, 13, 71, (unsigned char *) (23296));
		sp_UpdateNow ();
		if (gpit > 1) espera_activa (200); else espera_activa (9999);
		cortina ();
	}
}
