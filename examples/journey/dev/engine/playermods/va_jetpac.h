#ifdef SWITCHABLE_ENGINES
	if (p_engine == SENG_JETP)
#endif
		if (BUTTON_JUMP) {
#ifdef JETPAC_DEPLETES
			if (p_fuel) {
#endif			
				p_vy -= PLAYER_JETPAC_VY_INCR;
				if (p_vy < -PLAYER_JETPAC_VY_MAX) p_vy = -PLAYER_JETPAC_VY_MAX;
#ifdef JETPAC_DEPLETES
				if (0 == (maincounter & (JETPAC_DEPLETES-1))) p_fuel --;
			}
		} else {
			if (0 == (maincounter & (JETPAC_AUTO_REFILLS-1)) && p_fuel < JETPAC_FUEL_MAX) p_fuel ++;
		}
#else
		}
#endif
