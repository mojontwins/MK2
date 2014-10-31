// cutscene.h

unsigned char cutscene0 [] = {
	0, ENDING4_BIN, 212, 213, 214, 0, ENDING3_BIN, 215, 216, 217, 218, 219, 220, 221, 222, 223, 0, ENDING4_BIN, 224, 225, 226, 0xff
};

unsigned char cutscene1 [] = {
	0, ENDING1_BIN, 206, 207, 208, 0, ENDING2_BIN, 209, 210, 211, 0xff
};

void do_cutscene (unsigned char *cuts) {
	is_cutscene = 1;
	while ( 0xff != (gpit = *cuts ++) ) {
		if (gpit == 0) {
			cortina ();
			get_resource (*cuts ++, 16384);
		} else {
			do_extern_action (gpit);
			for (gpit = 13; gpit < 21; gpit ++) {
				print_str (3, gpit, 71, "                          ");
				#asm
					halt
					halt
					halt
					halt
				#endasm
				sp_UpdateNow ();
			}
		}
	}
	cortina ();
}
