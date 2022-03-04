	// half-box collision. Check for tile behaviour in two points.
	// Which points? It depends on the type of collision configured:

	player_calc_bounding_box ();

	hit_v = 0;
	cx1 = ptx1; cx2 = ptx2;
	#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
		if (p_vy < 0)
	#else	
		if (p_vy + ptgmy < 0) 
	#endif
	{		
		cy1 = cy2 = pty1;
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vy = -(p_vy / 2);
			#else
				p_vy = 0;
			#endif

			#if defined (BOUNDING_BOX_8_BOTTOM)			
				gpy = ((pty1 + 1) << 4) - 8;
			#elif defined (BOUNDING_BOX_8_CENTERED)
				gpy = ((pty1 + 1) << 4) - 4;
			#elif defined (BOUNDING_BOX_TINY_BOTTOM)
				gpy = ((pty1 + 1) << 4) - 14;
			#else
				gpy = ((pty1 + 1) << 4);
			#endif

			p_y = gpy << FIXBITS;
			wall_v = WTOP;
		} 
		#ifndef DEACTIVATE_EVIL_TILE
			else if ((at1 IS_EVIL) || (at2 IS_EVIL)) {
				hit_v = TILE_EVIL;
			}
		#endif
	}

	#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
		if (p_vy > 0)
	#else	
		if (p_vy + ptgmy > 0)
	#endif
	{
		cy1 = cy2 = pty2;
		cm_two_points ();

		#ifdef PLAYER_GENITAL
			if ((at1 & 8) || (at2 & 8))
		#else
			// Greed Optimization tip! Remove this line and uncomment the next one:
			// (As long as you don't have type 8 blocks over type 4 blocks in your game, the short line is fine)
			if ((at1 & 8) || (at2 & 8) || (((gpy - 1) & 15) < 8 && ((at1 & 4) || (at2 & 4))))
			//if (((gpy - 1) & 15) < 7 && ((at1 & 12) || (at2 & 12))) {
		#endif			
		{
			#if defined (ENABLE_FLOATING_OBJECTS) && defined (ENABLE_FO_CARRIABLE_BOXES) && defined (CARRIABLE_BOXES_CORCHONETA)
				// Remember original p_vy to use with the corchoneta.
				p_vlhit = p_vy;
			#endif			
			
			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vy = -(p_vy / 2);
			#else
				p_vy = 0;
			#endif
				
			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_TINY_BOTTOM)
				gpy = (pty2 - 1) << 4;
			#elif defined (BOUNDING_BOX_8_CENTERED)				
				gpy = ((pty2 - 1) << 4) + 4;
			#else
				gpy = (pty2 - 1) << 4;				
			#endif

			p_y = gpy << FIXBITS;

			wall_v = WBOTTOM;
		}
#ifndef DEACTIVATE_EVIL_TILE 
		else if ((at1 IS_EVIL) || (at2 IS_EVIL)) {
			hit_v = TILE_EVIL;
		}
#endif
	}
		
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
