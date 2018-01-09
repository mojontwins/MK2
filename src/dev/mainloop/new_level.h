			if (!silent_level) {
				blackout_area ();
				print_str (12, 12, 71, "LEVEL");
				print_number2 (18, 12, level + 1);
/*
				if (level > 0) {
					gen_password ();
					print_str (12, 14, 71, password_text);
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
			