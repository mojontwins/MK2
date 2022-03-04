// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// messages.h
// Misc. messages

#ifdef MODE_128K
#else
unsigned char bs;
#endif

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
		beep_fx (SFX_ENDING_LAME_1);
		beep_fx (SFX_ENDING_LAME_2);
	} while (--bs);
	beep_fx (SFX_ENDING_LAME_WIN);
#endif
}

void game_over (void) {
	_x = LIFE_X; _y = LIFE_Y; _t = p_life; print_number2 ();	
	gp_gen = (unsigned char *) (" GAME OVER! "); print_message ();
	
#ifdef MODE_128K
#else
	bs = 4; do {
		beep_fx (SFX_ENDING_LAME_1);
		beep_fx (SFX_ENDING_LAME_2);
	} while (--bs);
	beep_fx (SFX_ENDING_LAME_LOSE);
#endif
}

#if defined (TIMER_ENABLE) && defined (SHOW_TIMER_OVER)
void time_over (void) {
	gp_gen = (unsigned char *) ("  TIME UP!  "); print_message ();
		
#ifdef MODE_128K
#else
	bs = 4; do {
		beep_fx (SFX_ENDING_LAME_1);
		beep_fx (SFX_ENDING_LAME_2);
	} while (--bs);
	beep_fx (SFX_ENDING_LAME_LOSE);
#endif
}
#endif

#ifdef PAUSE_ABORT
/*
void pause_screen (void) {
	gp_gen = (unsigned char *) ("   PAUSED   "); print_message ();
}
*/
#endif
