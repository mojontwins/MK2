// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// drops/sprites.h
// Frame 0: falling drop, frames 1-3: exploding drop.

extern unsigned char drop_sprites [0];
#asm
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
	defb 0, 255
._drop_sprites
	BINARY "spdrop.bin"
#endasm
