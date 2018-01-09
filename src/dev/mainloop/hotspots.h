// MY FRIEND, YOU HAVE TO RECODE/REHASH/REWHATEVER THIS ASAP!
// This hasn't changed much since Churrera 1.0, for god's sake...

// AGAIN; FUCKING REWRITE THIS PIECE OF SHIT!!!

			// Hotspot interaction.
			if (collide (gpx, gpy, hotspot_x, hotspot_y)) {
				// Deactivate hotspot
				draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), orig_tile);
				gpit = 0;
#ifndef USE_HOTSPOTS_TYPE_3
				// Was it an object, key or life boost?
				if (hotspots [n_pant].act == 0) {
					p_life += PLAYER_REFILL;
#ifndef DONT_LIMIT_LIFE
					if (p_life > PLAYER_LIFE)
						p_life = PLAYER_LIFE;
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
								draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
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

#ifdef TIMER_ENABLE
#ifdef TIMER_REFILL
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
					hotspots [n_pant].act = gpit;
				}
				hotspot_y = 240;
			}
#else
				// Modificaci?n para que los hotspots de tipo 3 sean recargas directas
				// Was it an object, key or life boost?
				if (hotspots [n_pant].act) {
					hotspots [n_pant].act = 0;
					switch (hotspots [n_pant].tipo) {
#ifndef DEACTIVATE_OBJECTS
						case 1:
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
								draw_coloured_tile (VIEWPORT_X + (hotspot_x >> 3), VIEWPORT_Y + (hotspot_y >> 3), 17);
								hotspots [n_pant].act = 1;
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
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS) && !defined (HANNA_LEVEL_MANAGER) && !defined (SIMPLE_LEVEL_MANAGER)
							if (level_data.max_objs > p_objs) {
#else
							if (PLAYER_MAX_OBJECTS > p_objs) {
#endif
								print_str (10, 11, 79, spacer);
#if defined (MODE_128K) && defined (COMPRESSED_LEVELS) && !defined (HANNA_LEVEL_MANAGER) && !defined (SIMPLE_LEVEL_MANAGER)
								gpjt = level_data.max_objs - p_objs;
#else
								gpjt = PLAYER_MAX_OBJECTS - p_objs;
#endif
								getxmore [8] = '0' + gpjt / 10;
								getxmore [9] = '0' + gpjt % 10;
								print_str (10, 12, 79, getxmore);
								print_str (10, 13, 79, spacer);
								sp_UpdateNow ();
								sp_WaitForNoKey ();
								active_sleep (100);
								draw_scr_background ();
							}
#endif
							break;
#endif
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
							if (p_life > PLAYER_LIFE)
								p_life = PLAYER_LIFE;
#endif
#ifdef MODE_128K
							_AY_PL_SND (SFX_REFILL);
#else
							beep_fx (SFX_REFILL);
#endif
							break;
#ifdef MAX_AMMO
#endif
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
#ifdef TIMER_ENABLE
#ifdef TIMER_REFILL
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
				hotspot_y = 240;
			}
#endif
