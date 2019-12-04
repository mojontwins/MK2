// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// isr
#asm
	defw 0
#endasm

void ISR(void) {	
	++ isrc;
}
