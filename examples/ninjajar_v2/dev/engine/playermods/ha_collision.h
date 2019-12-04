	// half-box collision. Check for tile behaviour in two points.
	// Which points? It depends on the type of collision configured:

	player_calc_bounding_box ();

	#ifndef ONLY_VERTICAL_EVIL_TILE
		hit_h = 0;
	#endif 

	cy1 = pty1; cy2 = pty2;

	#if defined (DISABLE_PLATFORMS) && !defined (ENABLE_CONVEYORS)
		if (p_vx < 0)
	#else	
		if (p_vx + ptgmx < 0)
	#endif
	{
		cx1 = cx2 = ptx1;
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vx = -(p_vx / 2);
			#else
				p_vx = 0;
			#endif

			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
				gpx = ((ptx1 + 1) << 4) - 4;
			#else
				gpx = ((ptx1 + 1) << 4);
			#endif

			p_x = gpx << FIXBITS;
			wall_h = WLEFT;
		}
		#ifndef DEACTIVATE_EVIL_TILE
			#ifndef ONLY_VERTICAL_EVIL_TILE
				else if ((at1 IS_EVIL) || (at2 IS_EVIL)) {
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
		cx1 = cx2 = ptx2; 
		cm_two_points ();

		if ((at1 & 8) || (at2 & 8)) {
			#ifdef PLAYER_BOUNCE_WITH_WALLS
				p_vx = -(p_vx / 2);
			#else
				p_vx = 0;
			#endif

			#if defined (BOUNDING_BOX_8_BOTTOM) || defined (BOUNDING_BOX_8_CENTERED) || defined (BOUNDING_BOX_TINY_BOTTOM)				
				gpx = ((ptx2 - 1) << 4) + 4;
			#else
				gpx = ((ptx2 - 1) << 4);
			#endif

			p_x = gpx << FIXBITS;
			wall_h = WRIGHT;
		}
		#ifndef DEACTIVATE_EVIL_TILE
			#ifndef ONLY_VERTICAL_EVIL_TILE
				else if ((at1 IS_EVIL) || (at2 IS_EVIL)) {
					hit_h = TILE_EVIL;
				}
			#endif
		#endif
	}
	