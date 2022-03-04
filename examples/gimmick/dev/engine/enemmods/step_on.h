// Step over enemy
if (
	#ifdef PLAYER_CAN_KILL_FLAG
		flags [PLAYER_CAN_KILL_FLAG] &&
	#endif
	#if defined (PLAYER_HAS_SWIM) && defined (SWITCHABLE_ENGINES)
		p_engine != SENG_SWIM &&
	#endif
	gpy < _en_y - 2 && p_vy >= 0 && _en_t >= PLAYER_MIN_KILLABLE && killable
) {
	en_an_n_f [enit] = sprite_17_a;
	#ifdef MODE_128K
		_AY_PL_SND (SFX_KILL_ENEMY);
		en_an_state [enit] = GENERAL_DYING;
		en_an_count [enit] = 8;
	#else
		//sp_MoveSprAbs (sp_moviles [enit], spritesClip, en_an_n_f [enit] - en_an_c_f [enit], VIEWPORT_Y + (_en_y >> 3), VIEWPORT_X + (_en_x >> 3), _en_x & 7, _en_y & 7);
		//en_an_c_f [enit] = en_an_n_f [enit];
		enems_move_spr_abs ();
		
		sp_UpdateNow ();
		beep_fx (SFX_KILL_ENEMY);
		en_an_n_f [enit] = sprite_18_a;
	#endif
	_en_t |= 128;			// Mark as dead
	#ifdef BODY_COUNT_ON
		flags [BODY_COUNT_ON] ++;
	#else
		p_killed ++;
	#endif					
	#ifdef ACTIVATE_SCRIPTING
		#ifdef RUN_SCRIPT_ON_KILL
			#ifdef EXTENDED_LEVELS
				if (level_data.activate_scripting)
			#endif
			{
				run_script (2 * MAP_W * MAP_H + 5);
			}
		#endif
	#endif
	continue;
} else  