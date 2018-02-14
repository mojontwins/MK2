			
			if (p_killme) {
				p_state = EST_PARP;
				sp_UpdateNow ();
				//wyz_play_sample (0);
				active_sleep (50);
#ifdef PLAYER_HAS_SWIM
				if (p_engine != SENG_SWIM) {
#endif
					if (n_pant != p_safe_pant) {
						o_pant = n_pant = p_safe_pant;
						draw_scr ();
					}
#if !defined (DISABLE_AUTO_SAFE_SPOT) && !defined (PLAYER_GENITAL)
					gpjt = p_safe_x; gpit = 15; while (
						gpit -- && 
						(!(attr (p_safe_x, p_safe_y + 1) & 12) ||
						(attr (p_safe_x, p_safe_y) & 8))
					) gpjt ++;
					if (gpit) p_safe_x = gpjt;
#endif
#if defined (PHANTOMAS_ENGINE) || defined (HANNA_ENGINE)
					p_x = p_safe_x << 4;
					p_y = p_safe_y << 4;
#elif defined (PLAYER_GENITAL)
					p_x = p_safe_x << 6;
					p_y = p_safe_y << 6;
#else
					p_x = p_safe_x << 10;
					p_y = p_safe_y << 10;
#endif
					p_vx = 0;
					p_vy = 0;
					p_jmp_on = 0;
#ifdef PLAYER_HAS_SWIM
				}
#endif

				p_killme = 0;
#ifdef MODE_128K
				// Play music
#ifdef COMPRESSED_LEVELS
				//_AY_PL_MUS (level_data->music_id);
#else
				//_AY_PL_MUS (1);
#endif
				_AY_PL_SND (18);
#endif
			}
