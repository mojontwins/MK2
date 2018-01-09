// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// extraprints.h
// Adds extra prints to screens

// Somewhat custom. You better use scripting if scripting is active.
// this is to somewhat embellish non-scripted games.

// The format is two bytes. XY and tile. XY = 0xFF is the end marker.
// Each screen with prints is an array. A final array has a pointer
// for each screen with prints, 0 otherwise.

const unsigned char scr1 [] = {0x73, 34, 0x43, 26, 0xA3, 26, 0x42, 25, 0xA2, 25, 0x62, 32, 0x82, 33, 0xff};
const unsigned char scr4 [] = {0x66, 32, 0x86, 33, 0xff};
const unsigned char scr7 [] = {0x66, 35, 0x86, 39, 0xff};
const unsigned char scr10 [] = {0x84, 36, 0x75, 23, 0x76, 23, 0x77, 23, 0x78, 24, 0xff};
const unsigned char scr13 [] = {0x95, 27, 0xff};
const unsigned char scr15 [] = {0x94, 37, 0xff};
const unsigned char scr17 [] = {0x64, 38, 0xff};

const unsigned char *prints [] = {
	0, scr1, 0,
	0, scr4, 0,
	0, scr7, 0,
	0, scr10, 0,
	0, scr13, 0,
	scr15, 0, scr17
};

unsigned char *ep_pt;

void extra_prints (void) {
	if (prints [n_pant] != 0) {
		ep_pt = prints [n_pant];
		while ((gpit = *ep_pt ++) != 0xff) {
			gpc = *ep_pt ++;
			update_tile (gpit >> 4, gpit & 15, behs [gpc], gpc);
		}
	}
}
