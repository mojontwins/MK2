#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
	gpx = p_x >> FIXBITS;
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

			if (attr () == 10) {
				x0 = x1 = cx1; y0 = cy1; y1 = cy1 - 1;
				process_tile ();
			}

		} else if (wall_v == WBOTTOM) {
			// interact down
			#if defined (BOUNDING_BOX_8_BOTTOM)
				cy1 = (gpy + 16) >> 4;
			#elif defined (BOUNDING_BOX_8_CENTERED)
				cy1 = (gpy + 12) >> 4;
			#else
				cy1 = (gpy + 16) >> 3;				
			#endif		
		
			if (attr () == 10) {
				x0 = x1 = cx1; y0 = cy1; y1 = cy1 + 1;
				process_tile ();
			}
		} else
	#endif	
	
	if (wall_h == WLEFT) {		
		// interact left
		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
			cx1 = (gpx + 3) >> 4;
		#else
			cx1 = gpx >> 4;		
		#endif		

		if (attr () == 10) {
			y0 = y1 = cy1; x0 = cx1; x1 = cx1 - 1;
			process_tile ();
		}
	} else if (wall_h == WRIGHT) {
		// interact right
		#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED)
			cx1 = (gpx + 12) >> 4;
		#else
			cx1 = (gpx + 16) >> 4;		
		#endif		
		if (attr () == 10) {
			y0 = y1 = cy1; x0 = cx1; x1 = cx1 + 1;
			process_tile ();
		}
	}
#endif
	