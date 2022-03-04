#if defined (ENABLE_ARROWS)
unsigned char addons_between (unsigned char x, unsigned char a, unsigned char b, unsigned char h1, unsigned char h2) {
	return ((a < b ? a : b) <= x + h1 && x <= (a < b ? b : a) + h2);
}
#endif
