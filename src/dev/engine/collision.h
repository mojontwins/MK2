// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// collision.h
// Collision functions

unsigned char collide (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2) {
#ifdef SMALL_COLLISION
	return (x1 + 8 >= x2 && x1 <= x2 + 8 && y1 + 8 >= y2 && y1 <= y2 + 8);
#else
	return (x1 + 13 >= x2 && x1 <= x2 + 13 && y1 + 12 >= y2 && y1 <= y2 + 12);
#endif
}

unsigned char collide_pixel (unsigned char x, unsigned char y, unsigned char x1, unsigned char y1) {
	if (x >= x1 + 1 && x <= x1 + 14 && y >= y1 + 1 && y <= y1 + 14) return 1;
	return 0;
}

