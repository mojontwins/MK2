			if (fo_fly && killable) {
				//if (collide (f_o_xp, f_o_yp, gpen_cx, gpen_cy)) {
				if (f_o_xp + 15 >= gpen_cx && f_o_xp <= gpen_cx + 15 &&
					f_o_yp + 15 >= gpen_cy && f_o_yp <= gpen_cy + 15) {
					en_an_n_f [gpit] = sprite_17_a;
					en_an_state [gpit] = GENERAL_DYING;
					en_an_count [gpit] = 8;
#ifdef CARRIABLE_BOXES_COUNT_KILLS
					flags [CARRIABLE_BOXES_COUNT_KILLS] ++;
#endif
					baddies [enoffsmasi].t |= 128;
#ifdef BODY_COUNT_ON
					flags [BODY_COUNT_ON] ++;
#else					
					p_killed ++;
#endif					
#ifdef MODE_128K
#else
					sp_UpdateNow ();
					beep_fx (SFX_EXPLOSION);
#endif

#ifdef ACTIVATE_SCRIPTING
#ifdef RUN_SCRIPT_ON_KILL
					run_script (2 * MAP_W * MAP_H + 5);
#endif
#endif
					continue;
				}
			}
