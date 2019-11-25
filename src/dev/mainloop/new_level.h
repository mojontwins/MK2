			if (!silent_level) {
				blackout_area ();
				_x = 12; _y = 12; _t = 71; gp_gen = "LEVEL"; print_str ();
				_x = 18; _y = 12; _t = level + 1; print_number2 ();
/*
				if (level > 0) {
					gen_password ();
					_x = 12; _y = 14; _t = 71; gp_gen = password_text; print_str ();
				}
*/
				sp_UpdateNow ();

#ifdef MODE_128K
				//_AY_PL_MUS (5);
#else
				_AY_PL_SND (8);
#endif
				//active_sleep (2500);
				active_sleep (250);

			}
			silent_level = 0;
			