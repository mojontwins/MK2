// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// wraparound.h
// Uglier than Uwol, but should do.

void wrap_around (void) {
#ifdef PHANTOMAS_ENGINE	
	// TODO: Make this work for the Phantomas Engine (when needed!)
#else
	// Momentum engine edge screen detection
	if (p_x <= 0 && p_vx < 0) {
		p_x = 14336;
	}
	if (p_x >= 14336 && p_vx > 0) {
		p_x = 0;
	}
#endif	
}
