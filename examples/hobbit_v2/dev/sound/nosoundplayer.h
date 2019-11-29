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
	// Do nothing
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
