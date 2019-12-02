#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
	gpx = p_x >> 6;
	cx1 = (gpx + 8) >> 4;
	cy1 = (gpy + 8) >> 4;
	#ifdef PLAYER_GENITAL
		if (wall_v == WTOP) {
			// interact up			
			#if defined (BOUNDING_BOX_8_BOTTOM)
				cy1 = (gpy + 7) >> 4;
			#elif defined (BOUNDING_BOX_8_CENTERED)
				cy1 = (gpy + 3) >> 4;
			#else
				cy1 = gpy >> 3;		
			#endif

			if (attr () == 10) process_tile (cx1, cy1, cx1, cy1 - 1);

		} else if (wall_v == WBOTTOM) {
			// interact down
			#if defined (BOUNDING_BOX_8_BOTTOM)
				cy1 = (gpy + 16) >> 4;
			#elif defined (BOUNDING_BOX_8_CENTERED)
				cy1 = (gpy + 12) >> 4;
			#else
				cy1 = (gpy + 16) >> 3;				
			#endif		
		
			if (attr () == 10) process_tile (cx1, cy1, cx1, cy1 + 1);
		} else
	#endif	
	
	if (wall_h == WLEFT) {		
		// interact left
		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
			cx1 = (gpx + 3) >> 4;
		#else
			cx1 = gpx >> 4;		
		#endif		

		if (attr () == 10) process_tile (cx1, cy1, cx1 - 1, cy1);
	} else if (wall_h == WRIGHT) {
		// interact right
		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
			cx1 = (gpx + 12) >> 4;
		#else
			cx1 = (gpx + 16) >> 4;		
		#endif		
		if (attr () == 10) process_tile (cx1, cy1, cx1 + 1, cy1);
	}
#endif
	