// 128K stuff

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
