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

#ifndef ONLY_VERTICAL_EVIL_TILE
	hit_h = 0;
#endif 

#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
	if (p_vx < 0)
#else	
	if (p_vx + ptgmx < 0)
#endif
	{
		pt1 = attr (ptx1, pty1);
		pt2 = attr (ptx1, pty2);
		if ((pt1 & 8) || (pt2 & 8)) {
#ifdef PLAYER_BOUNCE_WITH_WALLS
			p_vx = -(p_vx / 2);
#else
			p_vx = 0;
#endif
#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)
			p_x = ((ptx1 + 1) << 10) - 256;
#else
			p_x = ((ptx1 + 1) << 10);
#endif
			wall_h = WLEFT;
		}
#ifndef DEACTIVATE_EVIL_TILE
#ifndef ONLY_VERTICAL_EVIL_TILE
		else if ((pt1 IS_EVIL) || (pt2 IS_EVIL)) {
			hit_h = TILE_EVIL;
		}
#endif
#endif
	}
#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
	if (p_vx > 0)
#else	
	if (p_vx + ptgmx > 0)
#endif
	{
		pt1 = attr (ptx2, pty1);
		pt2 = attr (ptx2, pty2);
		if ((pt1 & 8) || (pt2 & 8)) {
#ifdef PLAYER_BOUNCE_WITH_WALLS
			p_vx = -(p_vx / 2);
#else
			p_vx = 0;
#endif
#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)
			p_x = ((ptx2 - 1) << 10) + 256;
#else
			p_x = ((ptx2 - 1) << 10);
#endif
			wall_h = WRIGHT;
		}

#ifndef DEACTIVATE_EVIL_TILE
#ifndef ONLY_VERTICAL_EVIL_TILE
		else if ((pt1 IS_EVIL) || (pt2 IS_EVIL)) {
			hit_h = TILE_EVIL;
		}
#endif
#endif
	}
	
	gpx = p_x >> 6;
	