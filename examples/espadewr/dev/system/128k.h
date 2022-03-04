// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// 128.h
// Paging routine.
// Includes a simple workaround for ula snow issues which usually works.

void SetRAMBank(void) {
#asm
	.SetRAMBank
			ld	a, b
			or	a
			jp	z, restISR
			xor	a
			ld	i, a
			jp	keepGoing
	.restISR
			ld	a, $f0
			ld	i, a
	.keepGoing
			ld	a, 16
			or	b
			ld	bc, $7ffd
			out (C), a
#endasm
}
