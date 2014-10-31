// newlevel.h
// Custom "new level" screen

unsigned char arrowcoords [] = {
	6, 16,	// Tutorial
	
	7, 14,	// Pueblo
	6, 11,	// Montaña
	7, 10,	// Lago
	8, 8,	// Tienda 1
	
	7, 6,	// Llanos 1
	6, 5,	// Pozo poroso
	8, 4,	// Bruja Sarollán
	12, 4,	// Tienda 2
	
	12, 6,	// Llanos 2
	10, 10,	// Cueva Kave
	11, 15,	// Bosque monos
	13, 13, // Tienda 3
	
	16, 16,	// Lago oscuro
	21, 13,	// Castillo 1
	24, 12,	// Tienda 4
	
	21, 10,	// Pit
	24, 8,	// Cave 2
	20, 7,	// Lava!
	19, 5,	// Tienda 5
	
	19, 4,	// Playa o montaña XD
	23, 5,	// Playa (mal)
	16, 4,	// Castillo 2 (bien)
	16, 4	// Finawl
};

void level_screen (void) {
	cortina ();
	get_resource (LEVEL_BIN, 16384);
	//print_number2 (LIFE_X, LIFE_Y, p_life);
	//print_number2 (FLAG_X, FLAG_Y, flags [PLAYER_SHOW_FLAG]);
	if (level > 0) {
		gen_password ();
		print_str (12, 20, 71, password_text);
	} else {
		print_str (12, 20, 71, "TUTORIAL");
	}
	gen_pt = arrowcoords + (level << 1);
	sp_PrintAtInv (*(gen_pt + 1), *gen_pt, 71 + 128, 30);
	//print_number2 (15, 23, level);
	sp_UpdateNow ();
	wyz_play_music (5);
	espera_activa (2500);
	do_extern_action (0);
	get_resource (1, 16384);
}
