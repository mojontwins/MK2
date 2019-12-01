	// 128K
	if (
		#if defined (MODE_128K) && defined (COMPRESSED_LEVELS) && !(defined (SIMPLE_LEVEL_MANAGER) || defined (HANNA_LEVEL_MANAGER))
			(level_data->win_condition == 0 && p_objs == level_data->max_objs) ||
			(level_data->win_condition == 1 && n_pant == level_data->scr_fin)
			#ifdef ACTIVATE_SCRIPTING
				|| (level_data->win_condition == 2 && script_result == 1)
			#endif
		#elif defined (MODE_128K) && (defined (HANNA_LEVEL_MANAGER) || defined (SIMPLE_LEVEL_MANAGER))
			script_result == 1
		#elif !defined (MODE_128K) && defined (COMPRESSED_LEVELS)
			(win_condition == 0 && p_objs == PLAYER_MAX_OBJECTS) ||
			(win_condition == 1 && n_pant == SCR_END)
			#ifdef ACTIVATE_SCRIPTING
				|| (win_condition == 2 && script_result == 1)
			#endif	
		#else
			// 48K, legacy
			#if WIN_CONDITION == 0
				p_objs == PLAYER_MAX_OBJECTS
			#elif WIN_CONDITION == 1
				n_pant == SCR_END
			#elif WIN_CONDITION == 2
				script_result == 1 || script_result > 2
			#elif WIN_CONDITION == 3
				flags [FLAG_SLOT_ALLDONE]
			#endif
		#endif
	) {
		success = 1;	// Next
		playing = 0;
	}
