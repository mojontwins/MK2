#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
	gpx = p_x >> 6;
	ptx1 = (gpx + 8) >> 4;
	pty1 = (gpy + 8) >> 4;
#ifdef PLAYER_GENITAL
	if (wall_v == WTOP) {
		// interact up			
#if defined (BOUNDING_BOX_8_BOTTOM)
		pty1 = (gpy + 7) >> 4;
#elif defined (BOUNDING_BOX_8_CENTERED)
		pty1 = (gpy + 3) >> 4;
#else
		pty1 = gpy >> 3;		
#endif
		if (attr (ptx1, pty1) == 10) process_tile (ptx1, pty1, ptx1, pty1 - 1);
	} else if (wall_v == WBOTTOM) {
		// interact down
#if defined (BOUNDING_BOX_8_BOTTOM)
		pty1 = (gpy + 16) >> 4;
#elif defined (BOUNDING_BOX_8_CENTERED)
		pty1 = (gpy + 12) >> 4;
#else
		pty1 = (gpy + 16) >> 3;				
#endif		
		if (attr (ptx1, pty1) == 10) process_tile (ptx1, pty1, ptx1, pty1 + 1);
	} else
#endif	
	if (wall_h == WLEFT) {		
		// interact left
#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
		ptx1 = (gpx + 3) >> 4;
#else
		ptx1 = gpx >> 4;		
#endif		
		if (attr (ptx1, pty1) == 10) process_tile (ptx1, pty1, ptx1 - 1, pty1);
	} else if (wall_h == WRIGHT) {
		// interact right
#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
		ptx1 = (gpx + 12) >> 4;
#else
		ptx1 = (gpx + 16) >> 4;		
#endif		
		if (attr (ptx1, pty1) == 10) process_tile (ptx1, pty1, ptx1 + 1, pty1);
	}
#endif
	