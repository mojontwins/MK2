#ifdef MODE_128K
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

#ifdef SCRIPTING_KEY_M
	key_m = 0x047f;
#endif
#ifdef PAUSE_ABORT
	key_h = 0x08bf;
	key_y = 0x10df;
#endif
#if defined (MSC_MAXITEMS) || defined (ENABLE_SIM)
	key_z = 0x02fe;
#endif
	joyfunc = sp_JoyKeyboard;

	// Load tileset
	gen_pt = tileset;
	gpit = 0; do {
		sp_TileArray (gpit, gen_pt);
		gen_pt += 8;
		gpit ++;
	} while (gpit);

	// Clipping rectangle
	spritesClipValues.row_coord = VIEWPORT_Y;
	spritesClipValues.col_coord = VIEWPORT_X;
	spritesClipValues.height = 20;
	spritesClipValues.width = 30;
	spritesClip = &spritesClipValues;
	