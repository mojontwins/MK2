// messages.h
// Misc. messages

#ifdef MODE_128K
#else
unsigned char bs;
#endif
// =======[CUSTOM MODIFICATION]=======

/*
void game_ending (void) {
	sp_UpdateNow();
	//blackout ();
#ifdef MODE_128K
	// Resource 2 = ending
	get_resource (2, 16384);
#else
	unpack ((unsigned int) (s_ending), 16384);
#endif

#ifdef MODE_128K
#else
	bs = 4; do {
		peta_el_beeper (7);
		peta_el_beeper (2);
	} while (--bs);
	peta_el_beeper (9);
#endif
}

void game_over (void) {
	print_message (" GAME OVER! ");
	
#ifdef MODE_128K
#else
	bs = 4; do {
		peta_el_beeper (7);
		peta_el_beeper (2);
	} while (--bs);
	peta_el_beeper (9);
#endif
}
*/
#if defined(TIMER_ENABLE) && defined(SHOW_TIMER_OVER)
void time_over (void) {
	print_message (" TIME'S UP! ");
		
#ifdef MODE_128K
#else
	bs = 4; do {
		peta_el_beeper (1);
		peta_el_beeper (2);
	} while (--bs);
	peta_el_beeper (0);
#endif
}
#endif

#ifdef PAUSE_ABORT
/*
void pause_screen (void) {
	print_message ("   PAUSED   ");
}
*/
#endif
