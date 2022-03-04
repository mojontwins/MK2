// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// isr
#asm
	defw 0
#endasm

void ISR(void) {	
	++ isrc;
	#ifdef SHOW_FPS
		++ tv_frame_counter;
		if (tv_frame_counter == 50) {
			_x = 0; _y = 0; _t = game_frame_counter; print_number2 ();
			tv_frame_counter = game_frame_counter = 0;
		}
	#endif
}
