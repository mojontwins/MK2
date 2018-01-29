	// half-box collision. Check for tile behaviour in two points.
	// Which points? It depends on the type of collision configured:
	gpx = p_x >> 6;
	gpy = p_y >> 6;

#if defined (BOUNDING_BOX_8_BOTTOM)
	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 11) >> 4;
	pty1 = (gpy + 8) >> 4;
	pty2 = (gpy + 15) >> 4;
#elif defined (BOUNDING_BOX_8_CENTERED)
	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 11) >> 4;
	pty1 = (gpy + 4) >> 4;
	pty2 = (gpy + 11) >> 4;
#elif defined (BOUNDING_BOX_TINY_BOTTOM)
	ptx1 = (gpx + 4) >> 4;
	ptx2 = (gpx + 11) >> 4;
	pty1 = (gpy + 14) >> 4;
	pty2 = (gpy + 15) >> 4;
#else
	ptx1 = (gpx) >> 4;
	ptx2 = (gpx + 15) >> 4;
	pty1 = (gpy) >> 4;
	pty2 = (gpy + 15) >> 4;
#endif

	hit_v = 0;
#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
	if (p_vy < 0)
#else	
	if (p_vy + ptgmy < 0) 
#endif
	{
		pt1 = attr (ptx1, pty1);
		pt2 = attr (ptx2, pty1);
		if ((pt1 & 8) || (pt2 & 8)) {
#ifdef PLAYER_BOUNCE_WITH_WALLS
			p_vy = -(p_vy / 2);
#else
			p_vy = 0;
#endif
#if defined (BOUNDING_BOX_8_BOTTOM)
			p_y = ((pty1 + 1) << 10) - 512;
#elif defined (BOUNDING_BOX_8_CENTERED)
			p_y = ((pty1 + 1) << 10) - 256;
#elif defined (BOUNDING_BOX_TINY_BOTTOM)
			p_y = ((pty1 + 1) << 10) - 896;
#else
			p_y = ((pty1 + 1) << 10);
#endif
			wall_v = WTOP;
		} 
#ifndef DEACTIVATE_EVIL_TILE
		else if ((pt1 IS_EVIL) || (pt2 IS_EVIL)) {
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
		pt1 = attr (ptx1, pty2);
		pt2 = attr (ptx2, pty2);
#ifdef PLAYER_GENITAL
		if ((pt1 & 8) || (pt2 & 8))
#else
		// Greed Optimization tip! Remove this line and uncomment the next one:
		// (As long as you don't have type 8 blocks over type 4 blocks in your game, the short line is fine)
		if ((pt1 & 8) || (pt2 & 8) || (((gpy - 1) & 15) < 8 && ((pt1 & 4) || (pt2 & 4))))
		//if (((gpy - 1) & 15) < 7 && ((pt1 & 12) || (pt2 & 12))) {
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
			p_y = ((pty2 - 1) << 10);
#elif defined (BOUNDING_BOX_8_CENTERED)
			p_y = ((pty2 - 1) << 10) + 256;
#else
			p_y = ((pty2 - 1) << 10);
#endif
			wall_v = WBOTTOM;
		}
#ifndef DEACTIVATE_EVIL_TILE 
		else if ((pt1 IS_EVIL) || (pt2 IS_EVIL)) {
			hit_v = TILE_EVIL;
		}
#endif
	}
	
	gpy = p_y >> 6;
	gpxx = gpx >> 4;
	gpyy = gpy >> 4;
