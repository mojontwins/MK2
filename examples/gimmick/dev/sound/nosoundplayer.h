// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// nosoundplayer.h

// Sound player which does nothing.
// Use this while developing (at least, until your musician delivers)

// isr
#asm
	defw 0
#endasm

void ISR(void) {	
	// Do nothing but...
	#ifdef MIN_FAPS_PER_FRAME
		++ isrc;
	#endif
	#ifdef SHOW_FPS
		++ tv_frame_counter;
		if (tv_frame_counter == 50) {
			_x = 0; _y = 0; _t = game_frame_counter; print_number2 ();
			tv_frame_counter = game_frame_counter = 0;
		}
	#endif
}

void __FASTCALL__ nosound_play_sound (unsigned char fx_number) {
	// Do nothing
}

void __FASTCALL__ nosound_play_music (unsigned char song_number) {
	// Do nothing
}

void nosound_stop_sound (void)
{
	// Do nothing
}
