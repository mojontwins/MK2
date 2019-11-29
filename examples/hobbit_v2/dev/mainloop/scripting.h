			gpit = (joyfunc) (&keys);

#ifdef ACTIVATE_SCRIPTING
#ifdef EXTENDED_LEVELS
			if (level_data->activate_scripting) {
#endif
#ifdef SCRIPTING_KEY_M
				if (sp_KeyPressed (key_m)) {
#endif
#ifdef SCRIPTING_DOWN
				if ((gpit & sp_DOWN) == 0) {
#endif
#ifdef SCRIPTING_KEY_FIRE
				if ((gpit & sp_FIRE) == 0) {
#endif
					if (action_pressed == 0)  {
						action_pressed = 1;
						// Any scripts to run in this screen?
						run_fire_script ();
					}
				} else {
					action_pressed = 0;
				}
#ifdef EXTENDED_LEVELS
			}
#endif
#endif

#ifdef ACTIVATE_SCRIPTING
#ifdef ENABLE_FIRE_ZONE
#ifdef EXTENDED_LEVELS
			if (level_data->activate_scripting) {
#endif
				if (f_zone_ac) {
					if (gpx >= fzx1 && gpx <= fzx2 && gpy >= fzy1 && gpy <= fzy2) {
						run_fire_script ();
					}
				}
#ifdef EXTENDED_LEVELS
			}
#endif
#endif
#endif
			