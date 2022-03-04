// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// random.h
// New random routines. Code by Patrik Rak, adapted by na_th_an

extern unsigned int seed1 [0];
extern unsigned int seed2 [0];
extern unsigned char randres [0];
#asm
	._seed1 defw 0
	._seed2 defw 0
	._randres defb 0
#endasm

unsigned char rand (void) {
	#asm
		.rnd 
			ld  hl,0xA280
	        ld  de,0xC0DE
	        ld  a,h         ; t = x ^ (x << 1)
	        add a,a
	        xor h
	        ld  h,l         ; x = y
	        ld  l,d         ; y = z
	        ld  d,e         ; z = w
	        ld  e,a
	        rra             ; t = t ^ (t >> 1)
	        xor e
	        ld  e,a
	        ld  a,d         ; w = w ^ ( w << 3 ) ^ t
	        add a,a
	        add a,a
	        add a,a
	        xor d
	        xor e
	        ld  e,a
	        ld  (rnd+1),hl
	        ld  (rnd+4),de
	        ld	(_randres), a
	#endasm
	return randres [0];
}

void srand (void) {
	#asm
			ld	hl, (_seed1)
			ld	(rnd+1),hl
			ld	hl, (_seed2)			
			ld	(rnd+4),hl
	#endasm
}
