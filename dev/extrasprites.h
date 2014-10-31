// Extrasprites.h
// Contiene sprites extra para el modo de matar enemigos de la churrera
// Sólo se incluirá (tras los sprites) si se define PLAYER_KILLS_ENEMIES
// Copyleft 2010 The Mojon Twins

// Frames extra por si se pueden eliminar los enemigos:

#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_KILLS_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
extern unsigned char sprite_17_a []; 
#endif
extern unsigned char sprite_18_a []; 
#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined (ENABLE_SHOOTERS)
extern unsigned char sprite_19_a [];
extern unsigned char sprite_19_b [];
#endif
#ifdef PLAYER_CAN_PUNCH
extern unsigned char sprite_20_a [];
extern unsigned char sprite_21_a [];
#endif

#if defined(PLAYER_CAN_FIRE) || defined(PLAYER_KILLS_ENEMIES) || defined(ENABLE_PURSUERS) || defined (MODE_128K)
#asm
    ._sprite_17_a
        defb 0, 128
        defb 56, 0
        defb 117, 0
        defb 123, 0
        defb 127, 0
        defb 57, 0
        defb 0, 0
        defb 96, 0
        defb 238, 0
        defb 95, 0
        defb 31, 0
        defb 62, 0
        defb 53, 128
        defb 42, 128
        defb 20, 128
        defb 0, 192
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_17_b
        defb 0, 3
        defb 240, 1
        defb 248, 0
        defb 236, 0
        defb 212, 0
        defb 248, 0
        defb 224, 1
        defb 24, 0
        defb 124, 0
        defb 120, 0
        defb 244, 0
        defb 168, 0
        defb 0, 1
        defb 0, 3
        defb 0, 63
        defb 0, 127
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
 
    ._sprite_17_c
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
        defb 0, 255
#endasm
#endif

#asm
	._sprite_18_a
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		
	._sprite_18_b
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		
	._sprite_18_c
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
		defb 0, 255, 0, 255, 0, 255, 0, 255
#endasm

#if defined(PLAYER_CAN_FIRE) || defined (MODE_128K) || defined (ENABLE_SHOOTERS)
#asm	              	
	._sprite_19_a
		defb 0, 255
		defb 0, 195
		defb 24, 129
		defb 60, 0
		defb 60, 0
		defb 24, 129
		defb 0, 195
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
	
	._sprite_19_b
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
#endasm
#endif

#ifdef PLAYER_CAN_PUNCH
#asm
	._sprite_20_a
		defb 0, 255
		defb 0, 0
		defb @10111110, 0
		defb @10110111, 0
		defb @10101011, 0
		defb @10101111, 0
		defb @00001110, 0
		defb 0, @11100000
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255		
	._sprite_21_a
		defb 0, 255
		defb 0, 0
		defb @01111101, 0
		defb @11101101, 0
		defb @11010101, 0
		defb @11110101, 0
		defb @01110000, 0
		defb 0, @00000111
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
		defb 0, 255
#endasm		
#endif
