			if ((p_life == 0 && p_killme)
#ifdef ACTIVATE_SCRIPTING
				|| script_result == 2
#endif
#if defined (TIMER_ENABLE) && defined (TIMER_GAMEOVER_0)
				|| ctimer.zero
#endif
			) {
				playing = 0;
			}
