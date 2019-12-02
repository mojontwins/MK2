			if (sp_KeyPressed (key_h)) {
				sp_WaitForNoKey ();
#ifdef MODE_128K
				_AY_ST_ALL ();
				_AY_PL_SND (8);
#endif
				//hide_sprites (0);
				//pause_screen ();
				while (sp_KeyPressed (key_h) == 0);
				sp_WaitForNoKey ();
				//draw_scr_background ();
#ifdef ACTIVATE_SCRIPTING
				//run_entering_script ();
#endif
#ifdef MODE_128K
				// Play music
#ifdef COMPRESSED_LEVELS
				//_AY_PL_MUS (level_data->music_id);
#else
				//_AY_PL_MUS (1);
#endif
#endif
			}
			if (sp_KeyPressed (key_y)) {
				playing = 0;
			}
