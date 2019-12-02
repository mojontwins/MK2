// MT Engine MK2 v0.90b
// Copyleft 2016 the Mojon Twins

// blocks.h
// Block processing helper

#ifdef FIRE_TO_PUSH
	unsigned char pushed_any;
#endif

#if defined (PLAYER_PUSH_BOXES) || !defined (DEACTIVATE_KEYS)
	void process_tile (unsigned char x0, unsigned char y0, signed char x1, signed char y1) {
		#ifdef PLAYER_PUSH_BOXES
			#ifdef FIRE_TO_PUSH
				gpit = (joyfunc) (&keys);
				#ifdef USE_TWO_BUTTONS
					if ((gpit & sp_FIRE) == 0 || sp_KeyPressed (key_fire))
				#else
					if ((gpit & sp_FIRE) == 0)
				#endif
			#endif
			{
				cx1 = x0; cy1 = y0; at1 = qtile (); cx1 = x1; cy1 = y1; at2 = attr ();
				if (at1 == 14 && at2 == 0 && x1 >= 0 && x1 < 15 && y1 >= 0 && y1 < 10) {								
					#if defined (ACTIVATE_SCRIPTING) && defined (ENABLE_PUSHED_SCRIPTING)
						flags [MOVED_TILE_FLAG] = map_buff [15 * y1 + x1];
						flags [MOVED_X_FLAG] = x1;
						flags [MOVED_Y_FLAG] = y1;
					#endif
					_x = x1; _y = y1; _n = 10; _t = 14; update_tile ();
					_x = x0; _y = y0; _n = 0;  _t = 0;  update_tile ();
					// Sonido
					#ifdef MODE_128K
						_AY_PL_SND (SFX_PUSH_BOX);
					#else
						beep_fx (SFX_PUSH_BOX);
					#endif
					#ifdef FIRE_TO_PUSH
						// Para no disparar...
						pushed_any = 1;
					#endif
					#if defined (ACTIVATE_SCRIPTING) && defined (ENABLE_PUSHED_SCRIPTING) && defined (PUSHING_ACTION)
						// Call scripting
						just_pushed = 1;
						run_fire_script ();
						just_pushed = 0;
					#endif
				}
			}
		#endif

		#ifndef DEACTIVATE_KEYS
			cx1 = x0; cy1 = y0;	if (qtile () == 15 && p_keys) {
				_x = x0; _y = y0; _n = 0; _t = 0; update_tile ();
				for (gpit = 0; gpit < MAX_BOLTS; gpit ++) {
					if (bolts [gpit].x == x0 && bolts [gpit].y == y0 && bolts [gpit].np == n_pant) {
						bolts [gpit].st = 0;
						break;
					}
				}
				p_keys --;
				#ifdef MODE_128K
					_AY_PL_SND (SFX_LOCK);
				#else
					beep_fx (SFX_LOCK);
				#endif
			}
		#endif
	}
#endif
