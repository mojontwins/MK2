// MY FRIEND, YOU HAVE TO RECODE/REHASH/REWHATEVER THIS ASAP!
// This hasn't changed much since Churrera 1.0, for god's sake...

// AGAIN; FUCKING REWRITE THIS PIECE OF SHIT!!!

// Hotspot interaction.
//if (collide (gpx, gpy, hotspot_x, hotspot_y)) 
#asm
		// (gpx + 8 >= hotspot_x && gpx <= hotspot_x + 8 && gpy + 8 >= hotspot_y && gpy <= hotspot_y + 8)

		// gpx + 8 >= hotspot_x
		ld  a, (_hotspot_x)
		ld  c, a
		ld  a, (_gpx)
		#ifdef SMALL_COLLISION
			add 8
		#else
			add 12
		#endif
		cp  c
		jp  c, _hotspots_skip

		// gpx <= hotspot_x + 8; hotspot_x + 8 >= gpx
		ld  a, (_gpx)
		ld  c, a
		ld  a, (_hotspot_x)
		#ifdef SMALL_COLLISION
			add 8
		#else
			add 12
		#endif
		cp  c
		jp  c, _hotspots_skip

		// gpy + 8 >= hotspot_y
		ld  a, (_hotspot_y)
		ld  c, a
		ld  a, (_gpy)
		#ifdef SMALL_COLLISION
			add 8
		#else
			add 12
		#endif
		cp  c
		jp  c, _hotspots_skip

		// gpy <= hotspot_y + 8; hotspot_y + 8 >= gpy
		ld  a, (_gpy)
		ld  c, a
		ld  a, (_hotspot_y)
		#ifdef SMALL_COLLISION
			add 8
		#else
			add 12
		#endif
		cp  c
		jp  c, _hotspots_skip			
#endasm
{
	gpit = 0;
	#ifndef USE_HOTSPOTS_TYPE_3
		// Was it an object, key or life boost?
		if (hotspots [n_pant].act == 0) {
			p_life += PLAYER_REFILL;
			#ifndef DONT_LIMIT_LIFE
				if (p_life > PLAYER_LIFE) p_life = PLAYER_LIFE;
			#endif
			hotspots [n_pant].act = 2;
			#ifdef MODE_128K
				_AY_PL_SND (SFX_REFILL);
			#else
				beep_fx (SFX_REFILL);
			#endif
		} else {
			switch (hotspots [n_pant].tipo) {
				#ifndef DEACTIVATE_OBJECTS
					case 1:
						#ifdef OBJECTS_COLLECTABLE_IF
							if (flags [OBJECTS_COLLECTABLE_IF] == 0) {
								gpit = 1;
								break;
							}
						#endif
							
						#ifdef ONLY_ONE_OBJECT
							if (p_objs == 0) {
								p_objs ++;
								#ifdef MODE_128K
									_AY_PL_SND (SFX_OBJECT);
								#else
									beep_fx (SFX_OBJECT);
								#endif
							} else {
								gpit = 1;
							}
						#else
							p_objs ++;
							#ifdef OBJECT_COUNT
								flags [OBJECT_COUNT] = p_objs;
							#endif

							#ifdef MODE_128K
								_AY_PL_SND (SFX_OBJECT);
							#else
								beep_fx (SFX_OBJECT);
							#endif
						#endif
						break;
				#endif

				#ifndef DEACTIVATE_KEYS
					case 2:
						p_keys ++;
						#ifdef MODE_128K
							_AY_PL_SND (SFX_KEY);
						#else
							beep_fx (SFX_KEY);
						#endif
						break;
				#endif

				#ifdef MAX_AMMO
					case 4:
						if (MAX_AMMO - p_ammo > AMMO_REFILL)
							p_ammo += AMMO_REFILL;
						else
							p_ammo = MAX_AMMO;
						
						#ifdef MODE_128K
							_AY_PL_SND (SFX_AMMO);
						#else
							beep_fx (SFX_AMMO);
						#endif
						break;
				#endif

				#if defined (TIMER_ENABLE) && defined (TIMER_REFILL)
					case 5:
						if (99 - ctimer.t > TIMER_REFILL)
							ctimer.t += TIMER_REFILL;
						else
							ctimer.t = 99;
						
						#ifdef MODE_128K
							_AY_PL_SND (SFX_TIME);
						#else
							beep_fx (SFX_TIME);
						#endif
						break;
				#endif

				#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (JETPAC_REFILLS)
					case 6:
						p_fuel += JETPAC_FUEL_REFILL;
						if (p_fuel > JETPAC_FUEL_MAX) p_fuel = JETPAC_FUEL_MAX;
						
						#ifdef MODE_128K
							_AY_PL_SND (SFX_FUEL);
						#else
							beep_fx (SFX_FUEL);
						#endif
						break;
				#endif
			}
		}
	#else
		// Was it an object, key or life boost?
		if (hotspots [n_pant].act) {
			switch (hotspots [n_pant].tipo) {
				#ifndef DEACTIVATE_OBJECTS
					case 1:
						#ifdef OBJECTS_COLLECTABLE_IF
							if (flags [OBJECTS_COLLECTABLE_IF] == 0) {
								gpit = 1;
								break;
							}
						#endif

						#ifdef ONLY_ONE_OBJECT
							if (p_objs == 0) {
								p_objs ++;
								
								#ifdef MODE_128K
									_AY_PL_SND (SFX_OBJECT);
								#else
									beep_fx (SFX_OBJECT);
								#endif
							} else {
								#ifdef MODE_128K
									_AY_PL_SND (SFX_WRONG);
								#else
									beep_fx (SFX_WRONG);
								#endif
								gpit = 1;
							}
						#else
							p_objs ++;
							#ifdef OBJECT_COUNT
								flags [OBJECT_COUNT] = player.objs;
							#endif

							#ifdef MODE_128K
								_AY_PL_SND (SFX_OBJECT);
							#else
								beep_fx (SFX_OBJECT);
							#endif
							
							#ifdef GET_X_MORE
								#if defined (COMPRESSED_LEVELS) && !defined (HANNA_LEVEL_MANAGER) && !defined (SIMPLE_LEVEL_MANAGER)
									if (level_data.max_objs > p_objs)
								#else
									if (PLAYER_MAX_OBJECTS > p_objs)
								#endif
								{
									_x = 10; _y = 11; _t = 79; gp_gen = spacer; print_str ();
									#if defined (COMPRESSED_LEVELS) && !defined (HANNA_LEVEL_MANAGER) && !defined (SIMPLE_LEVEL_MANAGER)
										gpjt = level_data.max_objs - p_objs;
									#else
										gpjt = PLAYER_MAX_OBJECTS - p_objs;
									#endif
									getxmore [8] = '0' + gpjt / 10;
									getxmore [9] = '0' + gpjt % 10;
									_x = 10; _y = 12; _t = 79; gp_gen = getxmore; print_str ();
									_x = 10; _y = 13; _t = 79; gp_gen = spacer; print_str ();
									sp_UpdateNow ();
									sp_WaitForNoKey ();
									active_sleep (100);
									draw_scr_background ();
									invalidate_viewport ();
								}
							#endif		
						#endif				
						break;
				#endif

				#ifndef DEACTIVATE_KEYS
					case 2:
						p_keys ++;
						#ifdef MODE_128K
							_AY_PL_SND (SFX_KEY);
						#else
							beep_fx (SFX_KEY);
						#endif
						break;
				#endif

				#ifndef DEACTIVATE_REFILLS
					case 3:
						p_life += PLAYER_REFILL;
						#ifndef DONT_LIMIT_LIFE
							if (p_life > PLAYER_LIFE) p_life = PLAYER_LIFE;
						#endif
						
						#ifdef MODE_128K
							_AY_PL_SND (SFX_REFILL);
						#else
							beep_fx (SFX_REFILL);
						#endif
						break;
				#endif

				#ifdef MAX_AMMO
					case 4:
						if (MAX_AMMO - p_ammo > AMMO_REFILL) {
							p_ammo += AMMO_REFILL;
						} else {
							p_ammo = MAX_AMMO;
						}

						#ifdef MODE_128K
							_AY_PL_SND (SFX_AMMO);
						#else
							beep_fx (SFX_AMMO);
						#endif
						break;
				#endif

				#if defined (TIMER_ENABLE) && defined (TIMER_REFILL)
					case 5:
						if (99 - ctimer.t > TIMER_REFILL) {
							ctimer.t += TIMER_REFILL;
						} else {
							ctimer.t = 99;
						}

						#ifdef MODE_128K
							_AY_PL_SND (SFX_TIME);
						#else
							beep_fx (SFX_TIME);
						#endif
						break;
				#endif

				#if defined (PLAYER_HAS_JETPAC) && defined (JETPAC_DEPLETES) && defined (JETPAC_REFILLS)
					case 6:
						p_fuel += JETPAC_FUEL_REFILL;
						if (p_fuel > JETPAC_FUEL_MAX) p_fuel = JETPAC_FUEL_MAX;
						#ifdef MODE_128K
							_AY_PL_SND (SFX_FUEL);
						#else
							beep_fx (SFX_FUEL);
						#endif
						break;
				#endif
			}
		}
	#endif

	if (gpit == 0) {
		// Deactivate hotspot				
		_x = hotspot_x >> 4;
		_y = hotspot_y >> 4;
		_t = orig_tile;
		draw_invalidate_coloured_tile_gamearea ();
		hotspots [n_pant].act = 0;
	} else {
		#ifdef MODE_128K
			_AY_PL_SND (SFX_WRONG);
		#else
			beep_fx (SFX_WRONG);
		#endif
	}
	hotspot_y = 240;
}

#asm
	._hotspots_skip
#endasm
