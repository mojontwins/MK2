#ifdef TIMER_ENABLE
			// Timer
			if (ctimer.on) {
				ctimer.count ++;
				if (ctimer.count == ctimer.frames) {
					ctimer.count = 0;
					if (ctimer.t) {
						ctimer.t --;
					} else {
						ctimer.zero = 1;
					}
				}
			}

#if defined (TIMER_SCRIPT_0) && defined (ACTIVATE_SCRIPTING)
			if (ctimer.zero) {
				ctimer.zero = 0;
#ifdef SHOW_TIMER_OVER
				hide_sprites (0);
				time_over ();
				active_sleep (500);
#endif
#ifdef EXTENDED_LEVELS
				if (level_data->activate_scripting) {
#endif
					run_script (MAP_W * MAP_H * 2 + 3);
#ifdef EXTENDED_LEVELS
				}
#endif
			}
#endif

#ifdef TIMER_KILL_0
			if (ctimer.zero) {
#ifdef SHOW_TIMER_OVER
#ifndef TIMER_SCRIPT_0
				hide_sprites (0);
				time_over ();
				active_sleep (500);
#endif
#endif
				ctimer.zero = 0;
#ifdef TIMER_AUTO_RESET
				ctimer.t = TIMER_INITIAL;
#endif
				kill_player (SFX_PLAYER_DEATH_TIME);
#if defined (TIMER_WARP_TO_X) && defined (TIMER_WARP_TO_Y)
				p_x = TIMER_WARP_TO_X << 10;
				p_y = TIMER_WARP_TO_Y << 10;
#endif
#ifdef TIMER_WARP_TO
				n_pant = TIMER_WARP_TO;
				draw_scr ();
#endif
			}
#endif
#endif
