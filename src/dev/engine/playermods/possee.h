#if defined (PLAYER_GENITAL) && defined (PLAYER_HAS_JUMP)
	// Very perliminar 2.5D
	pty1 = (gpy + 15) >> 4;
	ptx1 = (gpx + 8) >> 4;
	possee = (p_z == 0) && (attr (ptx1, pty1) != 3);
#else	
	pty3 = (gpy + 16) >> 4;
	possee = ((attr (ptx1, pty3) & 12) || (attr (ptx2, pty3) & 12)) && (gpy & 15) < 8;

	#if defined (DIE_AND_RESPAWN) && !defined DISABLE_AUTO_SAFE_SPOT

		// Store a "safe spot" to be respawned to if we die after the next jump.
		// Works a threat and it's pretty simple :)
		#ifdef SWITCHABLE_ENGINES
			if (p_engine != SENG_SWIM)
		#endif
				if (possee) {
		#ifdef ENABLE_FLOATING_OBJECTS
					// This prevents floating objects from being considered "safe spots"
					if (0 == ((attr (ptx1, pty3) & 128) || (attr (ptx2, pty3) & 128))) {
		#else
					{
		#endif
					p_safe_pant = n_pant;
					p_safe_x = gpxx;
					p_safe_y = gpyy;
				}
			}			
	#endif
#endif
