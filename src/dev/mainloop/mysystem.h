#if defined MODE_128K || defined MIN_FAPS_PER_FRAME
	// Install ISR

	sp_InitIM2(0xf1f1);
	sp_CreateGenericISR(0xf1f1);
	sp_RegisterHook(255, ISR);
#endif

	// splib2 initialization
	sp_Initialize (0, 0);
	sp_Border (BLACK);

	// Reserve memory blocks for sprites
	sp_AddMemory(0, NUMBLOCKS, 14, AD_FREE);

	joyfunc = sp_JoyKeyboard;

	// Load tileset
	gen_pt = tileset;
	gpit = 0; do {
		sp_TileArray (gpit, gen_pt);
		gen_pt += 8;
		gpit ++;
	} while (gpit);
