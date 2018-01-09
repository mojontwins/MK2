// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// arros/sprites.h
// Frame 0: arrow left. Frame 1: arrow right

extern unsigned char arrow_sprites [0];
#asm
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
._arrow_sprites
	BINARY "sparrow.bin"
#endasm
