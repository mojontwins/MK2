#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	// Very perliminar 2.5D
	cy1 = (gpy + 15) >> 4;
	cx1 = (gpx + 8) >> 4;
	possee = (p_z == 0) && (attr () != 3);
#else	
	cy1 = cy2 = (gpy + 16) >> 4;
	cx1 = ptx1; cx2 = ptx2;
	cm_two_points ();
	possee = ((at1 & 12) || (at2 & 12)) && (gpy & 15) < 8;

	#if defined (DIE_AND_RESPAWN) && !defined DISABLE_AUTO_SAFE_SPOT
		// Store a "safe spot" to be respawned to if we die after the next jump.
		// Works a threat and it's pretty simple :)
		#ifdef SWITCHABLE_ENGINES
			if (p_engine != SENG_SWIM)
		#endif
		
		if (possee) {
			#ifdef ENABLE_FLOATING_OBJECTS
				// This prevents floating objects from being considered "safe spots"
				if (0 == ((at1 & 128) || (at2 & 128)))
			#endif
			{
				p_safe_pant = n_pant;
				p_safe_x = gpxx;
				p_safe_y = gpyy;
			}
		}			
	#endif
#endif
